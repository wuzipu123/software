/*
 * misc.h
 *
 *  Created on: 27.06.2019
 *      Author: tolotos
 */

#ifndef MISC_H_
#define MISC_H_

#include "stm32l0xx_hal.h"
#include <stdint.h>

#define SPS30_INIT_CRC 0xff // CRC Initialization

// Definition for I2Cx clock resources---------------------------------------
#define I2Cx I2C1
#define RCC_PERIPHCLK_I2Cx RCC_PERIPHCLK_I2C1
#define RCC_I2CxCLKSOURCE_SYSCLK RCC_I2C1CLKSOURCE_SYSCLK
#define I2Cx_CLK_ENABLE() __HAL_RCC_I2C1_CLK_ENABLE()
#define I2Cx_SDA_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2Cx_SCL_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()

#define I2Cx_FORCE_RESET() __HAL_RCC_I2C1_FORCE_RESET()
#define I2Cx_RELEASE_RESET() __HAL_RCC_I2C1_RELEASE_RESET()

// Definition for the LED Pin------------------------------------------------
#define LED_PIN GPIO_PIN_1
#define LED_GPIO_PORT GPIOA
#define LED_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define LED_GPIO_CLK_DISABLE() __HAL_RCC_GPIOA_CLK_DISABLE()

// Function prototypes-------------------------------------------------------
extern void SystemClock_Config(void); // System clock configuration

/**
 * \brief Calculate the checksum.
 *
 * \param data Pointer to the \ref receiveBuffer or \ref sendBuffer.
 * \param len Number of data for the checksum calculation.
 * \return The checksum value.
 */
extern uint8_t CalcCrc(const uint8_t *data, uint32_t len);

/**
 * \brief Error handler which runs in a never ending loop.
 */
extern void miscErrorHandler(void);

extern void miscInitTIMER21(void);

// Functions for initialization and controlling the LED----------------------
/**
 * \brief Initialize the LED by enabling the GPIO clock and configure the pins.
 */
extern void miscLEDInit(void);
extern void miscLEDOn(void);
extern void miscLEDOff(void);
extern void miscLEDToggle(void);

#endif /* MISC_H_ */
