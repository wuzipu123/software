/*
 * HW_init.c
 *
 *  Created on: 09.10.2019
 *      Author: fsommer
 */

#include "Error_Handler.h"
#include "defines.h"

void Error_Handler(void)
{
	GPIO_InitTypeDef  Error;
	Error.Pin 		= (GPIO_PIN_11);
	Error.Mode      = GPIO_MODE_AF_PP;
	HAL_GPIO_Init(GPIOA, &Error);
	while (1);
}
