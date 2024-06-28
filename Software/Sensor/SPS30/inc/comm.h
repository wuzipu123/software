/*
 * comm.h
 *
 *  Created on: 25.07.2019
 *      Author: tolotos
 */

#ifndef COMM_H_
#define COMM_H_

#include "stm32l0xx_hal.h"
#include <stdint.h>

/* Definition for UARTx Pins */
#define UARTx_RX_PIN GPIO_PIN_3
#define UARTx_RX_GPIO_PORT GPIOA
#define UARTx_TX_PIN GPIO_PIN_4
#define UARTx_TX_GPIO_PORT GPIOA
#define UARTx_RX_TX_AF GPIO_AF6_LPUART1

/* defines for UART-Communication */
#define UART_BAUDRATE 115200
#define UART_RECEIVE_MAX_LENGTH 35 //number of inst bytes sent by mainboard
#define ADDRESS_UART 12 //position of address in uart receive buffer
#define INST_UART 27 //position of instruction in uart receive buffer

/* Definition for ADRx Pins */
#define ADR0_PIN GPIO_PIN_8
#define ADR0_GPIO_PORT GPIOA
#define ADR1_PIN GPIO_PIN_9
#define ADR1_GPIO_PORT GPIOA
#define ADR2_PIN GPIO_PIN_10
#define ADR2_GPIO_PORT GPIOA
#define ADR_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()

// Function prototypes
/**
 * \brief Initialize the UART resources.
 *
 * \param uart Pointer to the UART handler.
 * \return No error value.
 */
extern uint8_t commUartInit(UART_HandleTypeDef *uart);

/**
 * \brief Initialize and configure the address pins.
 *
 * \param address Pointer to the address integer value.
 * \return No error value.
 */
extern uint8_t commAddressInit(int *address);

/**
 * \brief Get the status of the address pins.
 *
 * \param GPIOx Pointer to the GPIO port.
 * \param GPIO_Pin Pointer to the GPIO pin.
 * \return Value for the set or reset pin.
 */
extern uint8_t commGetPinState(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif /* COMM_H_ */
