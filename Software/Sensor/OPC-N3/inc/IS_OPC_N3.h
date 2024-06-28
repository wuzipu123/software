/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef IS_OPC_N3_H
#define IS_OPC_N3_H

#include "stm32l0xx.h"
#include "defines.h"


//valid commands for opc
typedef enum
{
  Write_peripheral_power_status  	= 0x03U,
  Read_DAC_and_power_status    		= 0x13U,
  //Set_Fan_or_Laser_digital_pot    = 0x42U, //should not be modified because of calibration
  //Set_Bin_Weighting_Index			= 0x05U, //should not be modified because of calibration
  Read_information_string  			= 0x3FU,
  Read_serial_number_string 		= 0x10U,
  Read_Configuration_Variables		= 0x3CU,
  //Write_Configuration_Variables	= 0x3AU, //should not be modified because of calibration
  Read_Histogram_data				= 0x30U,
  Read_PM_data						= 0x32U,
  Check_Status						= 0xCFU,
  Reset								= 0x06U
} command_t;


//option byte for opc power settings
typedef enum
{
	No_option 			= 0x00,
	Fan_on	 			= 0x03,
	Fan_off  			= 0x02,
	Laser_digit_pot_on  = 0x05,
	Laser_digit_pot_off = 0x04,
	Laser_switch_on     = 0x07,
	Laser_switch_off	= 0x06,
	Gain_high			= 0x09,
	Gain_low			= 0x08
}option_cmd_t;

typedef struct
{
	command_t cmd;
	option_cmd_t option_byte;
}inst_t;

//function prototypes
void HW_init_TIMER21(void);
int IS_OPC_N3_Instruction (SPI_HandleTypeDef* SpiHandle, inst_t* inst, uint8_t* aRxBuffer);
void IS_OPC_N3_fill_tx_buffer_one_inst(inst_t* inst, uint8_t* aTxBuffer, uint8_t cnt);
void IS_OPC_N3_delay_us(uint32_t delaytime);
void SysTick_Handler(void);
int IS_OPC_N3_ready(SPI_HandleTypeDef* SpiHandle, inst_t* inst);
int IS_OPC_N3_start (SPI_HandleTypeDef* SpiHandle, inst_t* inst, uint8_t* aRxBuffer);
int IS_OPC_N3_stop(SPI_HandleTypeDef* SpiHandle, inst_t* inst, uint8_t* aRxBuffer);
int IS_OPC_N3_read_data (SPI_HandleTypeDef* SpiHandle, inst_t* inst, uint8_t* aRxBuffer, uint16_t* Histogram, uint32_t* temperatur, uint32_t* humidity);
void IS_OPC_N3_save_info(SPI_HandleTypeDef* SpiHandle, inst_t* inst, uint8_t* aRxBuffer, uint8_t* Info_String);
void IS_OPC_N3_str_cpy(uint8_t *target, uint8_t *source, uint8_t length);
int IS_OPC_N3_info_str_cmp(uint8_t *aRxBuffer);
int IS_OPC_N3_valid_data(uint8_t* data);
#endif
