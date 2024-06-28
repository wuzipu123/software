/*
 * sps30.c
 *
 *  Created on: 27.06.2019
 *      Author: tolotos
 */

#include "sps30.h"
#include "misc.h"
#include "comm.h"
#include "stdio.h"
#include "conversion.h"

// Declarations--------------------------------------------------------------
I2C_HandleTypeDef hi2c; // I2C handler declaration
uint8_t sendBuffer[MAX_SEND_LENGTH]; // Buffer used for transmission
uint8_t receiveBuffer[MAX_RECEIVE_LENGTH]; // Buffer used for reception

// Function prototypes-------------------------------------------------------
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c);
static float sps30GetParticleValueFromReceiveBuffer(const uint8_t *receiveBuffer, int pos);
static uint8_t sps30CheckReceiveBufferReadValuesCrcs(const uint8_t *receiveBuffer);

// Initialization------------------------------------------------------------
uint8_t sps30Init()
{
	hi2c.Instance = I2C1;
	hi2c.Init.Timing = 0xF0A13E56;
	hi2c.Init.OwnAddress1 = 0x30F;
	hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c.Init.OwnAddress2 = 0xFF;
	hi2c.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	HAL_I2C_MspInit(&hi2c);

	if (HAL_I2C_Init(&hi2c) != HAL_OK) // Initialize the I2C peripherals
	{
		miscErrorHandler();
	}

	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c,I2C_ANALOGFILTER_ENABLE) == HAL_BUSY)
	{
		return 1;
	}

	return 0;
}

/**
 * \brief Initialize the MCU support package by enabling the GPIO and I2C clock and configure the pins.
 *
 * \param hi2c Pointer to the I2C handler.
 */
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
	GPIO_InitTypeDef  GPIO_InitStructI2C;
	RCC_PeriphCLKInitTypeDef  RCC_PeriphCLKInitStruct;

	/*##-1- Configure the I2C clock source. The clock is derived from the SYSCLK #*/
	RCC_PeriphCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2Cx;
	RCC_PeriphCLKInitStruct.I2c1ClockSelection = RCC_I2CxCLKSOURCE_SYSCLK;
	HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInitStruct);

	/*##-2- Enable peripherals and GPIO Clocks #################################*/
	/* Enable GPIO TX/RX clock */
	__HAL_RCC_GPIOB_CLK_ENABLE();
	//I2Cx_SCL_GPIO_CLK_ENABLE();
	//I2Cx_SDA_GPIO_CLK_ENABLE();
	/* Enable I2Cx clock */
	I2Cx_CLK_ENABLE();

	/*##-3- Configure peripheral GPIO ##########################################*/
	/* I2C TX GPIO pin configuration  */
	GPIO_InitStructI2C.Pin = I2Cx_SCL_PIN;
	GPIO_InitStructI2C.Mode = GPIO_MODE_AF_OD;
	GPIO_InitStructI2C.Pull = GPIO_PULLUP;
	GPIO_InitStructI2C.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStructI2C.Alternate = I2Cx_SCL_SDA_AF;
	HAL_GPIO_Init(I2Cx_SCL_GPIO_PORT, &GPIO_InitStructI2C);

	/* I2C RX GPIO pin configuration  */
	GPIO_InitStructI2C.Pin = I2Cx_SDA_PIN;
	GPIO_InitStructI2C.Alternate = I2Cx_SCL_SDA_AF;
	HAL_GPIO_Init(I2Cx_SDA_GPIO_PORT, &GPIO_InitStructI2C);

	/*##-4- Configure the NVIC for I2C ########################################*/
	/* NVIC for I2Cx */
	//HAL_NVIC_SetPriority(I2C1_IRQn, 0, 1);
	//HAL_NVIC_EnableIRQ(I2C1_IRQn);
}

// SPS30 Commands------------------------------------------------------------
uint8_t sps30StartMeasurement()
{
	sendBuffer[0] = SPS30_START_MEAS >> 8;
	sendBuffer[1] = SPS30_START_MEAS & 0x00FF;
	sendBuffer[2] = SPS30_START_MEAS_MODE >> 8;
	sendBuffer[3] = SPS30_START_MEAS_MODE & 0x00FF;
	sendBuffer[4] = CalcCrc(&sendBuffer[2], 2);

	if (HAL_I2C_Master_Transmit(&hi2c, SPS30_I2C_ADDR, sendBuffer, 5, 1000) == HAL_ERROR)
	{
		return 1;
	}

	return 0;
}

uint8_t sps30StopMeasurement()
{
	sendBuffer[0] = SPS30_STOP_MEAS >> 8;
	sendBuffer[1] = SPS30_STOP_MEAS & 0x00FF;

	if (HAL_I2C_Master_Transmit(&hi2c, SPS30_I2C_ADDR, sendBuffer, 2, 1000) == HAL_ERROR)
	{
		return 1;
	}

	//miscLEDOff();

	return 0;
}

uint8_t sps30ReadReadyFlag()
{
	sendBuffer[0] = SPS30_RDY_FLAG >> 8;
	sendBuffer[1] = SPS30_RDY_FLAG & 0x00FF;

	if (HAL_I2C_Master_Transmit(&hi2c, SPS30_I2C_ADDR, sendBuffer, 2, 1000) == HAL_ERROR)
	{
		return 1;
	}

	if (HAL_I2C_Master_Receive(&hi2c, SPS30_I2C_ADDR, receiveBuffer, 3, 1000) == HAL_ERROR)
	{
		return 1;
	}

	uint16_t stat = (receiveBuffer[0] << 8) | receiveBuffer[1];
	receiveBuffer[2] = CalcCrc(receiveBuffer, 2);
	if (stat == 1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

uint8_t sps30ReadMeasurement(sps30_data_t *currentValues)
{
	int cnt;

	sendBuffer[0] = SPS30_READ_MEAS >> 8;
	sendBuffer[1] = SPS30_READ_MEAS & 0x00FF;
	sendBuffer[2] = CalcCrc(sendBuffer, 2);

	if (HAL_I2C_Master_Transmit(&hi2c, SPS30_I2C_ADDR, sendBuffer, 2, 1000) == HAL_ERROR)
	{
		return 1;
	}

	if (HAL_I2C_Master_Receive(&hi2c, SPS30_I2C_ADDR, receiveBuffer, MAX_RECEIVE_LENGTH, 1000) == HAL_ERROR)
	{
		return 1;
	}

	if (sps30CheckReceiveBufferReadValuesCrcs(receiveBuffer) == 1)
	{
		return 1;
	}

	for(cnt = 0; cnt < SPS30_NUM_READ_VALUES; cnt++)
	{
		currentValues->raw_values[cnt] = sps30GetParticleValueFromReceiveBuffer(receiveBuffer, cnt * 6);
	}

	return 0;
}

// Calculations--------------------------------------------------------------
/**
 * \brief Check the Crc from the \ref receiveBuffer.
 *
 * \param receiveBuffer Buffer for holding the received data from the sensor.
 * \return Error or no error value.
 */
uint8_t sps30CheckReceiveBufferReadValuesCrcs(const uint8_t *receiveBuffer)
{
	int cnt;

	for (cnt = 0; cnt < 20; cnt++)
	{
		if (CalcCrc(receiveBuffer, 2) != *(receiveBuffer + 2))
		{
			return 1;
		}

		receiveBuffer += 3;
	}

	return 0;
}

/**
 * \brief Reads the particle value from the \ref receiveBuffer.
 *
 * \param receiveBuffer Buffer for holding the received data from the sensor.
 * \param pos Locate a specific position in \ref receiveBuffer.
 * \return The extracted particle \ref currentValues.
 */
float sps30GetParticleValueFromReceiveBuffer(const uint8_t *receiveBuffer, int pos)
{
	uint32_t higherBytes = (receiveBuffer[pos] << 8) | receiveBuffer[pos+1];
	uint32_t lowerBytes = (receiveBuffer[pos+3] << 8) | receiveBuffer[pos+4];
	uint32_t rawValue = (higherBytes << 16) | lowerBytes;
	float *floatValue = (float*)&rawValue;

	return *floatValue;
}


