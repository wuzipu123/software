/*
 * misc.c
 *
 *  Created on: 27.06.2019
 *      Author: tolotos
 */

#include "misc.h"

static HAL_StatusTypeDef miscRCCOscConfig(RCC_OscInitTypeDef  *RCC_OscInitStruct);

/**
 * \brief Interrupt handler for the SysTick timer.
 */
void SysTick_Handler(void)
{
	HAL_IncTick();
}

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
		miscErrorHandler();
	}*/
	if (miscRCCOscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		// Initialization Error
		miscErrorHandler();
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
		miscErrorHandler();
	}

	RCC->APB1ENR|= RCC_APB1ENR_TIM2EN;

	/* The voltage scaling allows optimizing the power consumption when the device is
	   clocked below the maximum system frequency, to update the voltage scaling value
	   regarding system frequency refer to product datasheet.
	*/
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
}

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

void miscLEDInit()
{
	GPIO_InitTypeDef  GPIO_InitStructLED;

	// Enable the GPIO_LED Clock
	LED_GPIO_CLK_ENABLE();

	// Configure the GPIO_LED pin
	GPIO_InitStructLED.Pin = LED_PIN;
	GPIO_InitStructLED.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructLED.Pull = GPIO_NOPULL;
	GPIO_InitStructLED.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructLED);
	HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_SET);
}

void miscLEDOn()
{
	HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET);
}

void miscLEDOff()
{
	HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_SET);
}

void miscLEDToggle()
{
	HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
}

/**
 * \brief The error handler sets the CP0 Pin on high and then runs in an infinite loop.
 */
void miscErrorHandler()
{
	GPIO_InitTypeDef  Error;
	Error.Pin = (GPIO_PIN_11);
	Error.Mode = GPIO_MODE_AF_PP;
	HAL_GPIO_Init(GPIOA, &Error);
    while (1) /* Error if LED is slowly blinking (1 sec. period) */
    {
    	/*miscLEDToggle();
    	HAL_Delay(1000);*/
    }
}

uint8_t CalcCrc(const uint8_t *data, uint32_t len)
{
	uint8_t crc = 0xff; // calculated checksum
	for (int i = 0; i < len; i++)
	{
		crc ^= data[i];
		for(uint8_t bit = 8; bit > 0; --bit)
		{
			if (crc & 0x80)
			{
				crc = (crc << 1) ^ 0x31u;
			}
			else
			{
				crc = (crc << 1);
			}
		}
	 }
	 return crc;
}
