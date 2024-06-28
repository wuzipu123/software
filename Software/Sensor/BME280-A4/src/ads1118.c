#include "ads1118.h"
#include "stm32l0xx.h"
#include "stdbool.h"
#include "defines.h"


int IS_ADS1118_read (SPI_HandleTypeDef* SpiHandle, uint8_t* aRxBuffer, uint8_t CSS_Adress)
{
	return 0;
}

int ads1118_start(SPI_HandleTypeDef* SpiHandle, uint8_t Sensor_number, uint8_t pair_number, int16_t* conversion_data)
{
	uint16_t ads1118_1_config; //1 000 111 1 100 0 1 01 0; Single Shot, Input-Mux, gain, operating mode, DataRate, adc mode, pullup,
	uint16_t ads1118_1_noconfig	= 0;
	uint16_t chipSelect;

	if(!Sensor_number)
	{
		chipSelect = GPIO_PIN_0;
	}
	else
	{
		chipSelect = GPIO_PIN_1;
	}

	if(!pair_number)
	{
		ads1118_1_config = 0x8F8A;
	}
	else
	{
		ads1118_1_config = 0xBF8A;
	}

	//SPI_HandleTypeDef *hspi, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size, uint32_t Timeout
	HAL_GPIO_WritePin(GPIOB, chipSelect, GPIO_PIN_RESET); //select active low NSS
	HAL_Delay(1);
	HAL_SPI_TransmitReceive(SpiHandle, (uint8_t*)&ads1118_1_config, (uint8_t*)conversion_data, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOB, chipSelect, GPIO_PIN_SET); //reset active low NSS

	HAL_Delay(50);
	HAL_GPIO_WritePin(GPIOB, chipSelect, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_SPI_TransmitReceive(SpiHandle, (uint8_t*)&ads1118_1_noconfig, (uint8_t*)conversion_data, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOB, chipSelect, GPIO_PIN_SET);

	return 0;
	//write 1 to ss and 000 in config register... 0 000 010 1 100 0 1 01 0
	//one conversion will be executed from ain0 and ain1
	//write 1 to ss and 011 in config register... 0 011 010 1 100 0 1 01 0
	//one conversion will be executed from ain2 and ain3
}
