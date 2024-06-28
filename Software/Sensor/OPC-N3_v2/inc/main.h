/*
 * main.h
 *
 *  Created on: 10.07.2019
 *      Author: mknoll
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "stm32l0xx.h"
#include "HW_init.h"
#include "IS_OPC_N3.h"
#include "defines.h"


void Average_Histogram(uint16_t* Histogram, uint8_t* count_measure, uint32_t* temperature, uint32_t* humidity);
void Reset_Histogram(uint16_t* Histogram, uint32_t* temperature, uint32_t* humidity);
void HW_init_Error_Handler(void);


#endif /* MAIN_H_ */
