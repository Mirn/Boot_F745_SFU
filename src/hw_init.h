/*
 * hw_init.h
 *
 *  Created on: 01 сент. 2016 г.
 *      Author: Easy
 */

#ifndef HW_INIT_H_
#define HW_INIT_H_

extern UART_HandleTypeDef huart1;
extern CRC_HandleTypeDef hcrc;

void hw_init();

__attribute__ ((long_call))
void itcm_test(uint8_t * const test);
#endif /* HW_INIT_H_ */
