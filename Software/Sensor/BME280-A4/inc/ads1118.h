#include "stm32l0xx.h"

int IS_ADS1118_read (SPI_HandleTypeDef* SpiHandle, uint8_t* aRxBuffer, uint8_t CSS_Adress);
int ads1118_start(SPI_HandleTypeDef* SpiHandle, uint8_t Sensor_number, uint8_t pair_number, int16_t* conversion_data);
