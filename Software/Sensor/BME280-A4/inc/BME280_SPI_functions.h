/*
 * BME280_SPI_functions.h
 *
 *  Created on: 15.01.2020
 *      Author: floriansommer
 */

#ifndef BME280_SPI_FUNCTIONS_H_
#define BME280_SPI_FUNCTIONS_H_
#include"stdint.h"
#include "defines.h"




int8_t user_spi_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
void user_delay_ms(uint32_t period);
int8_t user_spi_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);

#endif /* BME280_SPI_FUNCTIONS_H_ */
