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

#define UART_BIN_HEADER_LENGTH 4
#define UART_BIN_ADDRESS_POS 1
#define UART_BIN_MESSAGE_LENGTH_POS 2
#define UART_BIN_INST_POS 4
#define UART_BIN_CRC_POS 5

#define UART_BIN_DATA_RESPONSE_LENGTH  (1 + 1 + 2 + SPS30_NUM_READ_VALUES * 4 + 2)
#define UART_BIN_DATA_RESPONSE_DATA_POS 4;

#define UART_BIN_INST_SEND_INFO 0x00U
#define UART_BIN_INST_INIT_MEAS 0x01U
#define UART_BIN_INST_STOP_MEAS 0x02U
#define UART_BIN_INST_SEND_DATA 0x03U

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
