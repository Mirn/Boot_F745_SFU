#include "stm32kiss.h"
#include "hw_init.h"
#include "usart_mini.h"
#include "packet_receiver.h"
#include "sfu_commands.h"

//#define SIMPLE_TEST
//#define TEST_PRINTF

#if !defined(SIMPLE_TEST) && !defined(TEST_PRINTF)

void main(void)
{
	hw_init();

#ifdef SystemCoreClockUpdate_ENABLED
	SystemCoreClockUpdate();
#endif

	ticks_init();
	usart_init();

#ifdef SystemCoreClockUpdate_ENABLED
	printf("SystemCoreClock\t%i\r\n", SystemCoreClock);
#endif

	recive_packets_init();
	sfu_command_init();

	while (1)
	{
		stat_error_timeout = 0;
		while ((stat_error_timeout * PACKET_TIMEOUT_mS) < 2000)
		{
			recive_packets_worker();
			recive_packets_print_stat();
		}
		main_start();
	}
}
#endif

#ifdef TEST_PRINTF

#pragma GCC diagnostic ignored "-Wformat" //for simple printf without format %l modificator

volatile uint32_t testvalue = 12345677; //test data section initialization

void main(void)
{
	//SystemCoreClockUpdate();
	hw_init();
	usart_init();
	ticks_init();
	delay_ms(1000);
	printf("SystemCoreClock\t%i\tHz\r\n", SystemCoreClock);

	while (1)
	{
		delay_ms(1000); //test delay and systemclock
		testvalue++;
		printf("testvalue\t%i\r\n", testvalue);
	}
}
#endif

#ifdef SIMPLE_TEST

void main(void)
{
	hw_init();

	usart_init();
    ticks_init();

    delay_ms(1000);
    SystemCoreClockUpdate();
    printf("SystemCoreClock\t%i\r\n", SystemCoreClock);

	while (1)
	{
//		HAL_Delay(100);
//		send_block("12345\r", 6);

		delay_ms(100); //test delay and systemclock
		if (recive_count() > 100)
			send('!');

		uint8_t rx = 0;
		if (recive_byte(&rx))
			send(rx);
	}
}
#endif
