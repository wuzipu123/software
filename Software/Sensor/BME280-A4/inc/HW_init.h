

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HW_INIT_H
#define HW_INIT_H

#include "stm32l0xx_hal.h"
#include "defines.h"

//function prototypes
void HW_init_GPIO(uint8_t*card_address);
void HW_init_SPI(SPI_HandleTypeDef*, uint8_t SPIMode);
void HW_init_CLK(void);
void HW_init_TIMER2(void);
void HW_init_TIMER21(void);
void HW_init_UART(UART_HandleTypeDef*);
void SystemClock_Config(void);
HAL_StatusTypeDef miscRCCOscConfig(RCC_OscInitTypeDef*);
void HW_init_set_SPI (SPI_HandleTypeDef* SpiHandle, uint8_t SPIMode);

#endif
