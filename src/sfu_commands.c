/*
 * sfu_commands.c
 *
 *  Created on: 08 ���� 2016 �.
 *      Author: Easy
 */

#include "stm32kiss.h"
#include "hw_init.h"
#include "usart_mini.h"
#include "packet_receiver.h"

#ifdef USE_STDPERIPH_DRIVER
#include "stm32f4xx_flash.h"
#include "stm32f4xx_crc_inline.h"
#include "stm32f4xx_flash_inline.h"
#endif

#define SFU_VER 0x0100

#define SFU_CMD_ERASE_PART   0xB3
#define SFU_CMD_INFO    0x97
#define SFU_CMD_ERASE   0xC5
#define SFU_CMD_WRITE   0x38
#define SFU_CMD_START   0x26
#define SFU_CMD_TIMEOUT 0xAA
#define SFU_CMD_WRERROR 0x55
#define SFU_CMD_HWRESET 0x11

static void sfu_command_info(uint8_t code, uint8_t *body, uint32_t size);
static void sfu_command_erase(uint8_t code, uint8_t *body, uint32_t size);
static void sfu_command_write(uint8_t code, uint8_t *body, uint32_t size);
static void sfu_command_start(uint8_t code, uint8_t *body, uint32_t size);

static uint32_t write_addr = 0;

void sfu_command_init()
{
	uint32_t temp;
	packet_send(SFU_CMD_HWRESET, (void*)&temp, 0);
}

void sfu_command_timeout()
{
	if (write_addr == 0) return;
	write_addr = 0;
	packet_send(SFU_CMD_TIMEOUT, (uint8_t*)&write_addr, sizeof(write_addr));
}

void sfu_command_parser(uint8_t code, uint8_t *body, uint32_t size)
{
	if (code == SFU_CMD_INFO)  sfu_command_info(code, body, size);
	if (code == SFU_CMD_ERASE) sfu_command_erase(code, body, size);
	if (code == SFU_CMD_WRITE) sfu_command_write(code, body, size);
	if (code == SFU_CMD_START) sfu_command_start(code, body, size);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static inline void serialize_uint32(uint8_t *body, uint32_t value)
{
#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
	*((uint32_t *)body) = value;
#else
	body[0] = (value >>  0) & 0xFF;
	body[1] = (value >>  8) & 0xFF;
	body[2] = (value >> 16) & 0xFF;
	body[3] = (value >> 24) & 0xFF;
#endif
}

static inline void serialize_uint16(uint8_t *body, uint16_t value)
{
#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
	*((uint16_t *)body) = value;
#else
	body[0] = (value >>  0) & 0xFF;
	body[1] = (value >>  8) & 0xFF;
#endif
}

static inline uint32_t deserialize_uint32(uint8_t *body)
{
#if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
	return *((uint32_t *)body);
#else
	return  ((uint32_t)body[0] <<  0) |
			((uint32_t)body[1] <<  8) |
			((uint32_t)body[2] << 16) |
			((uint32_t)body[3] << 24);
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void sfu_command_info(uint8_t code, UNUSED_A uint8_t *body, UNUSED_A uint32_t size)
{
	const uint32_t CPU_TYPE = DBGMCU->IDCODE & 0xFFFF0FFF; //7..4 bits reserved

	for (uint32_t index = 0; index < 12; index++)
		body[index] = DEVICE_ID_BLOCK_PTR[index];

	serialize_uint32(body + 12, CPU_TYPE);
	serialize_uint16(body + 16, FLASH_SIZE_CORRECT);
	serialize_uint16(body + 18, SFU_VER);
	serialize_uint32(body + 20, recive_size());
	serialize_uint32(body + 24, MAIN_START_FROM);
	serialize_uint32(body + 28, MAIN_RUN_FROM);

	packet_send(code, body, 32);
}

typedef struct {
	uint8_t sector_id;
	uint8_t total_size;
} tFLASH_sectors;

#define ADDR_COMPRESS 0x00004000

#ifdef USE_STDPERIPH_DRIVER
const tFLASH_sectors sectors[] = {
		{FLASH_Sector_2, (0x00004000 / ADDR_COMPRESS)},
		{FLASH_Sector_3, (0x00008000 / ADDR_COMPRESS)},
		{FLASH_Sector_4, (0x00018000 / ADDR_COMPRESS)},
		{FLASH_Sector_5, (0x00038000 / ADDR_COMPRESS)},
		{FLASH_Sector_6, (0x00058000 / ADDR_COMPRESS)},
		{FLASH_Sector_7, (0x00078000 / ADDR_COMPRESS)},
		{FLASH_Sector_8, (0x00098000 / ADDR_COMPRESS)},
		{FLASH_Sector_9, (0x000B8000 / ADDR_COMPRESS)},
		{FLASH_Sector_10,(0x000D8000 / ADDR_COMPRESS)},
		{FLASH_Sector_11,(0x000F8000 / ADDR_COMPRESS)},
};
#endif

#ifdef STM32F745xx
#define FLASH_COMPLETE HAL_OK
const tFLASH_sectors sectors[] = {
		{FLASH_SECTOR_1, (0x00008000 / ADDR_COMPRESS)},
		{FLASH_SECTOR_2, (0x00010000 / ADDR_COMPRESS)},
		{FLASH_SECTOR_3, (0x00018000 / ADDR_COMPRESS)},
		{FLASH_SECTOR_4, (0x00038000 / ADDR_COMPRESS)},
		{FLASH_SECTOR_5, (0x00058000 / ADDR_COMPRESS)},
		{FLASH_SECTOR_6, (0x00078000 / ADDR_COMPRESS)},
		{FLASH_SECTOR_7, (0x00098000 / ADDR_COMPRESS)},
};
#endif

static void sfu_command_erase(uint8_t code, uint8_t *body, uint32_t size)
{
	if (size != 4) return;

	uint32_t firmware_size = deserialize_uint32(body);

	if (firmware_size > 0)
	{
#ifdef USE_STDPERIPH_DRIVER
		FLASH_Status status = FLASH_BUSY;
		FLASH_Unlock_inline();
		FLASH_ClearFlag_inline(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
	                    FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
#endif

#ifdef STM32F745xx
		HAL_StatusTypeDef status = HAL_ERROR;
		HAL_FLASH_Unlock();
#endif

		for (uint32_t pos = 0; pos < LENGTH(sectors); pos++)
		{
#ifdef USE_STDPERIPH_DRIVER
			if ((FLASH_SIZE == 512) && (sectors[pos].sector_id == FLASH_Sector_7)) break;

			status = FLASH_EraseSector_inline(sectors[pos].sector_id, VoltageRange_3);
			if (status != FLASH_COMPLETE)
				break;
#endif

#ifdef STM32F745xx
			FLASH_EraseInitTypeDef erase_info = {
					.TypeErase = FLASH_TYPEERASE_SECTORS,
					.Sector = sectors[pos].sector_id,
					.NbSectors = 1,
					.VoltageRange = FLASH_VOLTAGE_RANGE_3,
			};
			uint32_t error = 0;

			status = HAL_FLASHEx_Erase(&erase_info, &error);
			if (status != HAL_OK)
				break;
#endif

			packet_send(SFU_CMD_ERASE_PART, (uint8_t *)&pos, sizeof(pos));

			uint32_t erased_size = ((uint32_t)sectors[pos].total_size) * ADDR_COMPRESS;
			if (erased_size >= firmware_size)
				break;
		}

#ifdef USE_STDPERIPH_DRIVER
		FLASH_Lock_inline();
#endif

#ifdef STM32F745xx
		HAL_FLASH_Lock();
#endif

		if (status == FLASH_COMPLETE)
		{
			write_addr = MAIN_START_FROM;
			packet_send(code, body, size);
			return;
		}
	}

	packet_send(code, body, 0);
}

#ifdef USE_STDPERIPH_DRIVER
__attribute__ ((long_call, section(".data")))
FLASH_Status flash_block_write(uint32_t wr_addr, uint32_t *data, uint32_t count)
{
	FLASH_Status status = FLASH_BUSY;
	FLASH_Unlock_inline();

	FLASH_ClearFlag_inline(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
                    FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);

	while (count--)
	{
		status = FLASH_ProgramWord_inline(wr_addr, *data);
		if (status != FLASH_COMPLETE) break;

		wr_addr += 4;
		data++;
	}
	FLASH_Lock_inline();
	return status;
}
#endif

#ifdef STM32F745xx
HAL_StatusTypeDef flash_block_write(uint32_t wr_addr, uint32_t *data, uint32_t count)
{
	HAL_StatusTypeDef status = HAL_ERROR;
	HAL_FLASH_Unlock();


	while (count--)
	{
		status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, wr_addr, *data);
		if (status != FLASH_COMPLETE) break;

		wr_addr += 4;
		data++;
	}
	HAL_FLASH_Lock();
	return status;
}
#endif

static void sfu_command_write(uint8_t code, uint8_t *body, uint32_t size)
{
	if (size > 4)
	{
		uint32_t body_addr = deserialize_uint32(body);

		if ((write_addr & 0xFF000000) != FLASH_BASE)
		{
			packet_send(SFU_CMD_WRERROR, body, 0);
			return;
		}

		uint32_t *word_data = (uint32_t*)&(body[4]);
		uint32_t word_count = (size - 4) / 4;

		//printf("WR:\t%08X\t%08X\t%u\r", body_addr, write_addr, word_count);		//send_str("WR\r");

		if ((body_addr == write_addr) && (word_count > 0))
		{
			if (flash_block_write(write_addr, word_data, word_count) != FLASH_COMPLETE)
			{
				write_addr = 0;
				packet_send(SFU_CMD_WRERROR, body, 0);
				return;
			};

			write_addr += (word_count * 4);
		}
	}

	serialize_uint32(body + 0, write_addr);
	serialize_uint32(body + 4, recive_count());

	packet_send(code, body, 8);
}

__attribute__( ( naked ) )
void jump_main(uint32_t stack, uint32_t func)
{
	__set_MSP(stack);
	(*(void (*)())(func))();
}

void main_start()
{
	uint32_t *boot_from = (uint32_t*)MAIN_RUN_FROM;

	if (((boot_from[0] >> 24) != (SRAM_BASE >> 24)) &&
		((boot_from[0] >> 24) != (CCMDATARAM_BASE >> 24)))
		return send_str("SRAM ERROR\r");

	if (((boot_from[1] >> 24) != (FLASH_BASE >> 24)) && (boot_from[1] > MAIN_RUN_FROM))
		return send_str("FLASH ERROR\r");

	send_str("CONTEXT OK\r\r");

#ifdef USE_STDPERIPH_DRIVER
	usart_deinit();
	RCC_DeInit();
#endif

#ifdef STM32F745xx
	HAL_UART_DeInit(&huart1);
	HAL_CRC_DeInit(&hcrc);
	HAL_RCC_DeInit();
	HAL_DeInit();
	SysTick_Config(SysTick_LOAD_RELOAD_Msk);
	SysTick->CTRL = 0x00000000;
#endif

	jump_main(boot_from[0], boot_from[1]);
}

static void sfu_command_start(uint8_t code, uint8_t *body, uint32_t size)
{
	if (size != 4) return;

	uint32_t *from = (uint32_t*)MAIN_START_FROM;
	uint32_t count = (write_addr - MAIN_START_FROM);

	uint32_t crc = crc_block(from, count / 4);
	uint32_t need = deserialize_uint32(body);

	serialize_uint32(body + 0, (uint32_t)from);
	serialize_uint32(body + 4, count);
	serialize_uint32(body + 8, crc);

	packet_send(code, body, 12);

	if (crc == need)
	{
		write_addr = 0;

		send('\r');
		send_str("CRC OK\r");

		main_start();
	}
	else
		send_str("CRC != NEED\r");
}
