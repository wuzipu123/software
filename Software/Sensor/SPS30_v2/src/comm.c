/*
 * comm.c
 *
 *  Created on: 25.07.2019
 *      Author: tolotos
 */

#include "comm.h"
#include "conversion.h"
#include "misc.h"

// UART handler declaration--------------------------------------------------
UART_HandleTypeDef uart;

uint8_t Uart_RxBuffer[UART_RECEIVE_MAX_LENGTH];

// Function prototype--------------------------------------------------------
void HAL_UART_MspInit(UART_HandleTypeDef *uart);

uint8_t commUartInit(UART_HandleTypeDef *uart)
{
	uart->Instance = USART2;
	uart->Init.BaudRate = UART_BAUDRATE;
	uart->Init.WordLength = UART_WORDLENGTH_8B;
	uart->Init.StopBits = UART_STOPBITS_1;
	uart->Init.Parity = UART_PARITY_NONE;
	uart->Init.Mode = UART_MODE_TX_RX;
	uart->Init.OverSampling = UART_OVERSAMPLING_16;
	uart->Init.HwFlowCtl = UART_HWCONTROL_NONE;

	HAL_UART_MspInit(uart);

	if (HAL_UART_Init(uart) != HAL_OK) // Initialize the UART peripherals
	{
		miscErrorHandler();
	}

	if (HAL_UART_Receive_IT(uart, Uart_RxBuffer, UART_RECEIVE_MAX_LENGTH) != HAL_OK)
	{
		miscErrorHandler();
	}

	NVIC_EnableIRQ(USART2_IRQn);

	return 0;
}

/**
 * \brief Initialize the MCU support package by enabling the GPIO and LPUART clock and configure the pins.
 *
 * \param uart Pointer to the UART handler.
 */
void HAL_UART_MspInit(UART_HandleTypeDef *uart)
{
	GPIO_InitTypeDef  GPIO_InitStructUART;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();

	GPIO_InitStructUART.Pin = GPIO_PIN_15;
	GPIO_InitStructUART.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructUART.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructUART);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);

	/* UART RX GPIO pin configuration  */ //Configurations also valid for following
	GPIO_InitStructUART.Pin = UARTx_RX_PIN;
	GPIO_InitStructUART.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructUART.Pull = GPIO_PULLUP;
	GPIO_InitStructUART.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStructUART.Alternate = UARTx_RX_TX_AF;
	HAL_GPIO_Init(UARTx_RX_GPIO_PORT, &GPIO_InitStructUART);

	/* UART TX GPIO pin configuration  */
	GPIO_InitStructUART.Pin = UARTx_TX_PIN;
	HAL_GPIO_Init(UARTx_TX_GPIO_PORT, &GPIO_InitStructUART);
}

/**
 * Due to startup errors the IRQ for LPUART was not executed properly
 * it has been necessary to overwrite the ISR
 */
void USART2_IRQHandler (void)
{
	HAL_UART_IRQHandler(&uart);
}

uint8_t commAddressInit(int *address)
{
	GPIO_InitTypeDef  GPIO_InitStructADR;

	/* Enable the GPIO_ADR Clock */
	// Uncomment if not already enabled.
	//ADR_GPIO_CLK_ENABLE();

	/* Configure the GPIO_ADRx pins */
	GPIO_InitStructADR.Pin = ADR0_PIN;
	GPIO_InitStructADR.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructADR.Pull = GPIO_PULLUP;
	GPIO_InitStructADR.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(ADR0_GPIO_PORT, &GPIO_InitStructADR);

	GPIO_InitStructADR.Pin = ADR1_PIN;
	HAL_GPIO_Init(ADR1_GPIO_PORT, &GPIO_InitStructADR);

	GPIO_InitStructADR.Pin = ADR2_PIN;
	HAL_GPIO_Init(ADR2_GPIO_PORT, &GPIO_InitStructADR);

	*address = commGetPinState(ADR0_GPIO_PORT, ADR0_PIN) + (commGetPinState(ADR1_GPIO_PORT, ADR1_PIN) << 1) + (commGetPinState(ADR2_GPIO_PORT, ADR2_PIN) << 2);

	GPIO_InitStructADR.Pin = ADR0_PIN;
	GPIO_InitStructADR.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(ADR0_GPIO_PORT, &GPIO_InitStructADR);

	GPIO_InitStructADR.Pin = ADR1_PIN;
	HAL_GPIO_Init(ADR1_GPIO_PORT, &GPIO_InitStructADR);

	GPIO_InitStructADR.Pin = ADR2_PIN;
	HAL_GPIO_Init(ADR2_GPIO_PORT, &GPIO_InitStructADR);

	return 0;
}

uint8_t commGetPinState(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_SET)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
