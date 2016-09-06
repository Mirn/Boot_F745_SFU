/*
 * hw_init.c
 *
 *  Created on: 01 сент. 2016 г.
 *      Author: Easy
 */
#include "stm32kiss.h"

CRC_HandleTypeDef hcrc;

void SystemClock_Config(void)
{
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  RCC_OscInitTypeDef RCC_OscInitStruct = {
		  .OscillatorType = RCC_OSCILLATORTYPE_HSI,
		  .HSIState = RCC_HSI_ON,
		  .HSICalibrationValue = 16,
		  .PLL.PLLState  = RCC_PLL_ON,
		  .PLL.PLLSource = RCC_PLLSOURCE_HSI,
		  .PLL.PLLM = 16,
		  .PLL.PLLN = 295,
		  .PLL.PLLP = RCC_PLLP_DIV2,
		  .PLL.PLLQ = 2,
  };
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitTypeDef RCC_ClkInitStruct = {
		  .ClockType      = RCC_CLOCKTYPE_HCLK |
		  	  	  	  	    RCC_CLOCKTYPE_SYSCLK |
		  	  	  	  	    RCC_CLOCKTYPE_PCLK1 |
		  	  	  	  	    RCC_CLOCKTYPE_PCLK2,
		  .SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK,
		  .AHBCLKDivider  = RCC_SYSCLK_DIV1,
		  .APB1CLKDivider = RCC_HCLK_DIV4,
		  .APB2CLKDivider = RCC_HCLK_DIV2,
  };
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4);

  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {
		  .PeriphClockSelection = RCC_PERIPHCLK_USART1,
		  .Usart1ClockSelection = RCC_USART1CLKSOURCE_SYSCLK,
  };
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
}

//void HAL_MspInit(void)
//{
//	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
//
//	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
//	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
//	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
//	HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
//	HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
//	HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
//	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
//}

void HAL_CRC_MspInit(CRC_HandleTypeDef* hcrc1)
{
	if(hcrc1->Instance !=CRC) return;
	__HAL_RCC_CRC_CLK_ENABLE();
}

void HAL_CRC_MspDeInit(CRC_HandleTypeDef* hcrc1)
{
	if(hcrc1->Instance != CRC) return;
	__HAL_RCC_CRC_CLK_DISABLE();
}

void MX_CRC_Init(void)
{
	hcrc.Instance = CRC;
	hcrc.Init.DefaultPolynomialUse    = DEFAULT_POLYNOMIAL_ENABLE;
	hcrc.Init.DefaultInitValueUse     = DEFAULT_INIT_VALUE_ENABLE;
	hcrc.Init.InputDataInversionMode  = CRC_INPUTDATA_INVERSION_NONE;
	hcrc.Init.OutputDataInversionMode = CRC_OUTPUTDATA_INVERSION_DISABLE;
	hcrc.InputDataFormat              = CRC_INPUTDATA_FORMAT_WORDS;

	HAL_CRC_Init(&hcrc);
}

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
	//USART1->TDR = '.';
}

void hw_init()
{
	SCB_EnableICache();
	SCB_EnableDCache();

	HAL_Init();

	SystemClock_Config();

	MX_CRC_Init();
}

/*	delay_ms(1000);
	printf("itcm_test_func \t%08X\n", (uint32_t)itcm_test);
	printf("itcm_test_flash\t%08X\n", (uint32_t)(&_itcm_copy));
	printf("itcm_imgae_from\t%08X\n", (uint32_t)(&_itcm_image_from));
	printf("itcm_imgae_to  \t%08X\n", (uint32_t)(&_itcm_image_to));

	uint32_t *itcm_src = &_itcm_copy;
	uint32_t *itcm_dst = &_itcm_image_from;
	while (itcm_dst < &_itcm_image_to)
		*(itcm_dst++) = *(itcm_src++);

	uint8_t test[16] = {0};
	printf("itcm_test\t");
	itcm_test(test);
	printf(test);
	printf("\r\n");

__attribute__ ((long_call, section(".itcm_data")))
void itcm_test_char(uint8_t **test, char c)
{
	**test = c;
	(*test)++;
}

__attribute__ ((long_call, section(".itcm_data")))
void itcm_test(uint8_t * test)
{
	const uint8_t info[] = "info: ";
	const uint8_t *ptr = info;
	while (*ptr)
		*(test++) = *(ptr++);

	itcm_test_char(&test, 't');
	itcm_test_char(&test, 'e');
	itcm_test_char(&test, 's');
	itcm_test_char(&test, 't');
	itcm_test_char(&test, 0);
}
*/
