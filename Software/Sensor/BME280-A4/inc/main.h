/*
 * main.h
 *
 *  Created on: 18.12.2019
 *      Author: mknoll
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "stm32l0xx.h"
#include "HW_init.h"
#include "defines.h"
#include "bme280_defs.h"
#include "bme280.h"


void Average_Data(uint16_t* Data, uint8_t* count_measure);
void Reset_Data(uint16_t* Data);

#endif /* MAIN_H_ */
