/*
 * HW_init.c
 *
 *  Created on: 12.07.2019
 *      Author: floriansommer
 */

#include "HW_init.h"
#include "defines.h"
#include "Error_Handler.h"

extern USART_HandleTypeDef UartHandle;
extern uint8_t readDataFromSensor;
uint8_t Uart_RxBuffer[UART_RECEIVE_MAX_LENGTH];
TIM_HandleTypeDef TIM_Struct21;

//GPIO Settings
/**
 * \brief Initialize GPIO Pins for card_address, status led an prepared initialization for CP0 and CP1,
 * enable Clock for GPIO Port A and Port B
 * \param card_address is used for communication with the mainboard, it is hardware-defined and unique
 */
void HW_init_GPIO(uint8_t *card_address)
{
	 __HAL_RCC_GPIOA_CLK_ENABLE();
	 __HAL_RCC_GPIOB_CLK_ENABLE();
	 GPIO_InitTypeDef  GPIO_InitStruct;

	 //PA1 output - active low led for testing only
	GPIO_InitStruct.Pin = (GPIO_PIN_1);
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);

	// read card adress via hardware, reset pins for low power consumption
	//PA8 input - add0 - card address bit0
	GPIO_InitStruct.Pin = (GPIO_PIN_8);
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	*card_address = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8);

	//PA9 input - add1 - card address bit1
	GPIO_InitStruct.Pin = (GPIO_PIN_9);
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	*card_address |= ((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9))<<1);

	//PA10 input - add2 - card address bit2
	GPIO_InitStruct.Pin = (GPIO_PIN_10);
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	*card_address |= ((HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10))<<2);

	//PA8 input - add0 - card address bit0 set to low power
	GPIO_InitStruct.Pin = (GPIO_PIN_8);
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	//PA9 input - add1 - card address bit1 set to low power
	GPIO_InitStruct.Pin = (GPIO_PIN_9);
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	//PA10 input - add2 - card address bit2 set to low power
	GPIO_InitStruct.Pin = (GPIO_PIN_10);
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*use controll pins if necessary, otherwise leave unconfigured
	//PA11 input - cp0 - control bit0
	GPIO_InitStruct.Pin = (GPIO_PIN_11);
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	//PA12 input - cp1 - control bit1
	GPIO_InitStruct.Pin = (GPIO_PIN_12);
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	*/

}

//Configure the SPI peripheral
/**
 * \brief Initialize SPI1 as Slave with 500kHz, Mode1
 * \param SpiHandle is used from HAL-Functions to initialize all SPI Parameters at once
 */
void HW_init_SPI(SPI_HandleTypeDef* SpiHandle, uint8_t SPIMode)
 {

	/* SPI for communication with OPC-N3: Mode 1 CPOL 0, CPHA 1;*/
	/*##-1- Enable GPIO and SPI Clocks #################################*/

	/* Enable GPIOB clock */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__SPI1_CLK_ENABLE();

	GPIO_InitTypeDef  GPIO_Init_SPI;

	/*##-2- Configure peripheral GPIO ##########################################*/

	/* SPI MISO GPIO pin configuration  */
	GPIO_Init_SPI.Pin 		= (GPIO_PIN_4);
	GPIO_Init_SPI.Mode      = GPIO_MODE_AF_PP;
	GPIO_Init_SPI.Alternate = GPIO_AF0_SPI1;
	HAL_GPIO_Init(GPIOB, &GPIO_Init_SPI);

	/* SPI MOSI GPIO pin configuration  */
	GPIO_Init_SPI.Pin = (GPIO_PIN_5);
	GPIO_Init_SPI.Mode      = GPIO_MODE_AF_PP;
	GPIO_Init_SPI.Alternate = GPIO_AF0_SPI1;
	HAL_GPIO_Init(GPIOB, &GPIO_Init_SPI);

	/* SPI NSS GPIO pin configuration BME280*/
	GPIO_Init_SPI.Pin 		= (GPIO_PIN_15);
	GPIO_Init_SPI.Pull 		= GPIO_PULLUP;
	GPIO_Init_SPI.Mode      = GPIO_MODE_OUTPUT_PP;
	GPIO_Init_SPI.Alternate = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOA, &GPIO_Init_SPI);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);

	/* SPI NSS GPIO pin configuration ADC1 (SN1-SN2)*/
	GPIO_Init_SPI.Pin 		= (GPIO_PIN_0);
	GPIO_Init_SPI.Pull 		= GPIO_PULLUP;
	GPIO_Init_SPI.Mode      = GPIO_MODE_OUTPUT_PP;
	GPIO_Init_SPI.Alternate = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOB, &GPIO_Init_SPI);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);

	/* SPI NSS GPIO pin configuration ADC2 (SN3-PID*/
	GPIO_Init_SPI.Pin 		= (GPIO_PIN_1);
	GPIO_Init_SPI.Pull 		= GPIO_PULLUP;
	GPIO_Init_SPI.Mode      = GPIO_MODE_OUTPUT_PP;
	GPIO_Init_SPI.Alternate = GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOB, &GPIO_Init_SPI);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

	/* SPI SCK GPIO pin configuration  */
	GPIO_Init_SPI.Pin       = (GPIO_PIN_3);
	GPIO_Init_SPI.Mode      = GPIO_MODE_AF_PP;
	GPIO_Init_SPI.Pull      = GPIO_PULLDOWN;
	GPIO_Init_SPI.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_Init_SPI.Alternate = GPIO_AF0_SPI1;
	HAL_GPIO_Init(GPIOB, &GPIO_Init_SPI);

	HW_init_set_SPI (SpiHandle, SPIMode);

}

void HW_init_set_SPI (SPI_HandleTypeDef* SpiHandle, uint8_t SPIMode)
{
/* Set the SPI parameters */
	SpiHandle->Instance               = SPI1;
	SpiHandle->Init.Mode			  = SPI_MODE_MASTER;
	SpiHandle->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32; //internal clock 16mhz -> spi freq 500khz
	SpiHandle->Init.Direction         = SPI_DIRECTION_2LINES;
	if(SPIMode)
	{
		SpiHandle->Init.CLKPhase          = SPI_PHASE_2EDGE;	//CPHA 1
		SpiHandle->Init.CLKPolarity       = SPI_POLARITY_LOW;	//CPOL 0
		SpiHandle->Init.DataSize          = SPI_DATASIZE_16BIT;
	}
	else
	{
		SpiHandle->Init.CLKPhase          = SPI_PHASE_1EDGE;	//CPHA 0
		SpiHandle->Init.CLKPolarity       = SPI_POLARITY_LOW;	//CPOL 0
		SpiHandle->Init.DataSize          = SPI_DATASIZE_8BIT;
	}
	SpiHandle->Init.FirstBit          = SPI_FIRSTBIT_MSB;
	SpiHandle->Init.TIMode            = SPI_TIMODE_DISABLE;
	SpiHandle->Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
	SpiHandle->Init.CRCPolynomial     = 7;
	SpiHandle->Init.NSS               = SPI_NSS_SOFT; //uC is master, three participants on nss

	if(HAL_SPI_Init(SpiHandle) != HAL_OK)
	{
		Error_Handler();
	}
}

	// Clock init for internal high clk
/**
 * \brief Initialize the clock sources for HSI 16MHz via HAL
 */
void HW_init_CLK(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};

	/* Enable HSI Oscillator */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI; //16mhz internal
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue=RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
	{
	   Error_Handler();
	}

	/* Select HSI as system clock source and configure the HCLK, PCLK1 and PCLK2
	clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0)!= HAL_OK)
	{
	  Error_Handler();
	}
	RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;

	/* The voltage scaling allows optimizing the power consumption when the device is
	   clocked below the maximum system frequency, to update the voltage scaling value
	   regarding system frequency refer to product datasheet.
	*/
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
}

/**
 * \brief not used at the moment because of memory problems
 * could be used to initialize the clock source for HSI 16MHz
 */
void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};

	/* Enable HSI Oscillator */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI; //16mhz internal
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue=RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
	/*if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
	{
		// Initialization Error
		Error_Handler();
	}*/
	if (miscRCCOscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		// Initialization Error
		Error_Handler();
	}

	/* Select HSI as system clock source and configure the HCLK, PCLK1 and PCLK2
	clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0)!= HAL_OK)
	{
		// Initialization Error
		Error_Handler();
	}

	RCC->APB1ENR|= RCC_APB1ENR_TIM2EN;

	/* The voltage scaling allows optimizing the power consumption when the device is
	   clocked below the maximum system frequency, to update the voltage scaling value
	   regarding system frequency refer to product datasheet.
	*/
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
}

/**
 *\brief is used in the \ref SystemClock_Config function
 * @param RCC_OscInitStruct is used to set clock parameters via HAL-Functions
 * @return HAL_OK, HAL_TIMEOUT or HAL_ERROR
 */
HAL_StatusTypeDef miscRCCOscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct)
{
	uint32_t tickstart;
	uint32_t hsi_state;

	/* Check the parameters */
	if(RCC_OscInitStruct == NULL)
	{
		return HAL_ERROR;
	}

	/*----------------------------- HSI Configuration --------------------------*/

	hsi_state = RCC_OscInitStruct->HSIState;

	/* Enable the Internal High Speed oscillator (HSI or HSIdiv4) */
	__HAL_RCC_HSI_CONFIG(hsi_state);

	/* Get Start Tick */
	tickstart = HAL_GetTick();

	/* Wait till HSI is ready */
	while(__HAL_RCC_GET_FLAG(RCC_FLAG_HSIRDY) == 0U)
	{
		if((HAL_GetTick() - tickstart ) > HSI_TIMEOUT_VALUE)
	    {
	    	return HAL_TIMEOUT;
	    }
	}

	/* Adjusts the Internal High Speed oscillator (HSI) calibration value.*/
	__HAL_RCC_HSI_CALIBRATIONVALUE_ADJUST(RCC_OscInitStruct->HSICalibrationValue);

	/*-------------------------------- PLL Configuration -----------------------*/

	/* Disable the main PLL. */
	__HAL_RCC_PLL_DISABLE();

  	/* Get Start Tick */
    tickstart = HAL_GetTick();

    /* Wait till PLL is disabled */
    while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY)  != 0U)
    {
    	if((HAL_GetTick() - tickstart ) > PLL_TIMEOUT_VALUE)
    	{
    		return HAL_TIMEOUT;
    	}
    }

    /* Configure the main PLL clock source, multiplication and division factors. */
    __HAL_RCC_PLL_CONFIG(RCC_OscInitStruct->PLL.PLLSource,
    RCC_OscInitStruct->PLL.PLLMUL,
    RCC_OscInitStruct->PLL.PLLDIV);
    /* Enable the main PLL. */
    __HAL_RCC_PLL_ENABLE();

    /* Get Start Tick */
	tickstart = HAL_GetTick();

	/* Wait till PLL is ready */
	while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY)  == 0U)
	{
	   	if((HAL_GetTick() - tickstart ) > PLL_TIMEOUT_VALUE)
	   	{
	   		return HAL_TIMEOUT;
	   	}
	}

	return HAL_OK;
}

//Configure the UART1 peripheral for RS485 ######################################
/**
 * \brief Initialize UART1 at 500kH via HAL
 * \param UartHandle is used from HAL-Functions to initialize all UART Parameters at once
 */
void HW_init_UART(UART_HandleTypeDef *UartHandle)
{
	GPIO_InitTypeDef GPIO_Init_UART;

	/*##-1- Enable peripherals and GPIO Clocks #################################*/
	/* Enable GPIO TX/RX clock */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();

	/* GPIO for transmittion enable*/
	GPIO_Init_UART.Pin = GPIO_PIN_15;
	GPIO_Init_UART.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_Init_UART.Pull=GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC, &GPIO_Init_UART);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);

	//PA3 configured as RX
	GPIO_Init_UART.Pin = GPIO_PIN_3;
	GPIO_Init_UART.Mode=GPIO_MODE_AF_PP;
	GPIO_Init_UART.Pull=GPIO_PULLUP;
	GPIO_Init_UART.Speed    = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_Init_UART.Alternate = GPIO_AF4_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_Init_UART);

	//PA4 configured as TX
	GPIO_Init_UART.Pin 			= GPIO_PIN_2;
	GPIO_Init_UART.Mode      	= GPIO_MODE_AF_PP;
	GPIO_Init_UART.Pull			= GPIO_PULLUP;
	GPIO_Init_UART.Speed     	= GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_Init_UART.Alternate 	= GPIO_AF4_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_Init_UART);

	UartHandle->Instance        = USART2;
	UartHandle->Init.BaudRate   = BAUDRATE_UART;
	UartHandle->Init.WordLength = USART_WORDLENGTH_8B;
	UartHandle->Init.StopBits   = USART_STOPBITS_1;
	UartHandle->Init.Parity     = USART_PARITY_NONE;
//	UartHandle->Init.HwFlowCtl  = UART_HWCONTROL_NONE;
//	UartHandle->Init.OverSampling = UART_OVERSAMPLING_16;
	UartHandle->Init.Mode       = USART_MODE_TX_RX;

	if(HAL_UART_Init(UartHandle) != HAL_OK)
	{
		Error_Handler();
	}
	HAL_UART_Receive_IT(UartHandle, Uart_RxBuffer, UART_RECEIVE_MAX_LENGTH);
	NVIC_EnableIRQ(USART2_IRQn);
}

/**
 * Due to startup errors the IRQ for LPUART was not executed properly
 * it has been necessary to overwrite the ISR
 */
void USART2_IRQHandler (void)
{
	HAL_UART_IRQHandler(&UartHandle);
}

/**
 * \brief to set TIM21 to generate an interrupt every second
 */
void HW_init_TIMER21(void)
{
	__HAL_RCC_TIM21_CLK_ENABLE();
	TIM_ClockConfigTypeDef sClockSourceConfig21;
	sClockSourceConfig21.ClockSource=TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(&TIM_Struct21, &sClockSourceConfig21);

	TIM_Struct21.Init.CounterMode=TIM_COUNTERMODE_UP;
	TIM_Struct21.Init.ClockDivision=0;
	TIM_Struct21.Init.Prescaler=7999;
	TIM_Struct21.Init.Period=10000;
	TIM_Struct21.Instance=TIM21;
	if(HAL_TIM_Base_Init(&TIM_Struct21))
	{
		Error_Handler();
	}

	if(HAL_TIM_Base_Start_IT(&TIM_Struct21) != HAL_OK)
	{
	    Error_Handler();
	}

	__NVIC_SetPriority(TIM21_IRQn, 4);
	NVIC_EnableIRQ(TIM21_IRQn);
}

/**
 * \brief addes one to the global variable readDataFromOpc
 * to signal that new data is readable at the opc
 */
void TIM21_IRQHandler (void)
{
	readDataFromSensor++;

	//HAL_TIM_IRQHandler(&TIM_Struct21);
	__HAL_TIM_CLEAR_IT(&TIM_Struct21, TIM_IT_UPDATE);
}

/**
 * \brief needed for SPI with HAL-Functions
 */
void SysTick_Handler(void)
{
  HAL_IncTick();
}












