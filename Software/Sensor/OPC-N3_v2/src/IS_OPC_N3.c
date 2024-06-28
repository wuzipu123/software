#include "IS_OPC_N3.h"
#include "defines.h"
#include "Error_Handler.h"

TIM_HandleTypeDef TIM_Struct21;
uint8_t readDataFromOpc = 0;

/**
 * \brief sends an instruction via SPI1 when the OPC-N3 is ready to communicate
 * @param SpiHandle is used for the HAL-Functions for SPI transmissions
 * @param inst is used for the instruction to be sent
 * @param aRxBuffer is the receive buffer for answers from the OPC-N3
 * @return 0 for error, high for success
 */
int IS_OPC_N3_Instruction (SPI_HandleTypeDef *SpiHandle, inst_t *inst, uint8_t* aRxBuffer)
{
	static uint8_t aTxBuffer[NUM_IBY_READ_HISTOGRAM_DATA];

	switch(inst->cmd)
	{
		case Write_peripheral_power_status:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
			HAL_Delay(1);
			if(IS_OPC_N3_ready(SpiHandle, inst))
			{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
				return 0;
				break;
			}
			else
			{
				HAL_Delay(1);
				HAL_SPI_TransmitReceive(SpiHandle, &(inst->option_byte), aRxBuffer, 1, DEL_TIMEOUT);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 1);
				return 1;
			}
			break;

		case Read_information_string:
			IS_OPC_N3_fill_tx_buffer_one_inst(inst, aTxBuffer, (NUM_IBY_READ_INFORMATION_STRING-2));
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 0);
			HAL_Delay(1);
			if(IS_OPC_N3_ready(SpiHandle, inst))
			{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 1);
				return 0;
				break;
			}
			else
			{
				HAL_Delay(1);
				HAL_SPI_TransmitReceive(SpiHandle, aTxBuffer, aRxBuffer, (NUM_IBY_READ_INFORMATION_STRING-2), DEL_TIMEOUT);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 1);
				return 2;
				break;
			}
			break;


		case Read_Histogram_data:
			IS_OPC_N3_fill_tx_buffer_one_inst(inst, aTxBuffer, (NUM_IBY_READ_HISTOGRAM_DATA-2));
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 0);
			HAL_Delay(1);
			if(IS_OPC_N3_ready(SpiHandle, inst))
			{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 1);
				return 0;
				break;
			}
			else
			{
				HAL_Delay(1);
				HAL_SPI_TransmitReceive(SpiHandle, aTxBuffer, aRxBuffer, NUM_IBY_READ_HISTOGRAM_DATA-2, DEL_TIMEOUT);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 1);
				return 3;
				break;
			}
			break;

		case Read_Configuration_Variables:
			IS_OPC_N3_fill_tx_buffer_one_inst(inst, aTxBuffer, (NUM_IBY_READ_CONFIGURATION_VARIABLES-2));
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 0);
			HAL_Delay(1);
			if(IS_OPC_N3_ready(SpiHandle, inst))
			{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 1);
				return 0;
				break;
			}
			else
			{
				HAL_Delay(1);
				HAL_SPI_TransmitReceive(SpiHandle, aTxBuffer, aRxBuffer, NUM_IBY_READ_CONFIGURATION_VARIABLES-2, DEL_TIMEOUT);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 1);
				return 4;
				break;
			}
			break;

		case Read_serial_number_string:
			IS_OPC_N3_fill_tx_buffer_one_inst(inst, aTxBuffer, (NUM_IBY_READ_SERIAL_NUMBER-2));
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 0);
			HAL_Delay(1);
			if(IS_OPC_N3_ready(SpiHandle, inst))
			{
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 1);
				return 0;
				break;
			}
			else
			{
				HAL_Delay(1);
				HAL_SPI_TransmitReceive(SpiHandle, aTxBuffer, aRxBuffer, NUM_IBY_READ_SERIAL_NUMBER-2, DEL_TIMEOUT);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 1);
				return 5;
				break;
			}
			break;

		case Reset:
			IS_OPC_N3_fill_tx_buffer_one_inst(inst, aTxBuffer, (NUM_IBY_RESET-1));
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, 0);
			HAL_Delay(1);
			IS_OPC_N3_ready(SpiHandle, inst);
			return 6;
			break;

		/* should not be modified because of calibration
		 case Set_Fan_or_Laser_digital_pot:
			break;
		*/

		/* should not be modified because of calibration
		case Set_Bin_Weighting_Index:
			break;
		*/

		/* should not be changed because of calibration
		case Write_Configuration_Variables:
			break;
		*/

		default:
			return 0;
			//ungültiger Befehl
			break;
	}
}

/**
 * \brief fills the transmit buffer for SPI communication, it fills the buffer with a number of same instructions
 * @param inst is used for the instruction to be sent
 * @param aTxBuffer is the transmit buffer to be filled
 * @param cnt number of bytes to be filled in buffer
 */
void IS_OPC_N3_fill_tx_buffer_one_inst(inst_t* inst, uint8_t* aTxBuffer, uint8_t cnt)
{
	uint8_t i=0;
	while(cnt)
	{
		aTxBuffer[i]=inst->cmd;
		i++;
		cnt--;
	}
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
	readDataFromOpc++;

	//HAL_TIM_IRQHandler(&TIM_Struct21);
	__HAL_TIM_CLEAR_IT(&TIM_Struct21, TIM_IT_UPDATE);
}

/**
 * \brief OPC-N3 retruns 0xF3 when it is ready to communicate via SPI
 * @param SpiHandle is used from HAL-Functions to set up the communications
 * @param inst is used to transmit the instruction to be sent
 * @return 1 for error, 0 for success
 */
int IS_OPC_N3_ready(SPI_HandleTypeDef *SpiHandle, inst_t *inst)
{
	uint8_t received = 0x00U;
	uint8_t tries = MAX_TRIES;
	uint8_t cmd = (uint8_t)inst->cmd;
	do
	{
		if (!tries)
			return 1;
		HAL_SPI_TransmitReceive(SpiHandle, &cmd, &received, 1, DEL_TIMEOUT);
		tries--;
		HAL_Delay(10);
	}while(received!=0xF3);
	return 0;
}

/**
 * \brief needed for SPI with HAL-Functions
 */
void SysTick_Handler(void)
{
  HAL_IncTick();
}
/**
 * \brief starts the OPC-N3 and sets up laser and fan for on-mode
 * @param SpiHandle needed for SPI communication via HAL-Functions
 * @param inst is the instruction to be sent via SPI
 * @param aRxBuffer is the Buffer for sending instructions
 * @return1 for success
 */
int IS_OPC_N3_start (SPI_HandleTypeDef* SpiHandle, inst_t* inst, uint8_t* aRxBuffer)
{
	inst->cmd=Write_peripheral_power_status;
	inst->option_byte=Laser_digit_pot_on;
	if(IS_OPC_N3_Instruction(SpiHandle, inst, aRxBuffer)==0)
	{
		Error_Handler();
	}
	HAL_Delay(OPC_N3_WAIT_CMD_MS);

	inst->cmd=Write_peripheral_power_status;
	inst->option_byte=Laser_switch_on;
	if(IS_OPC_N3_Instruction(SpiHandle, inst, aRxBuffer)==0)
	{
		Error_Handler();
	}
	HAL_Delay(OPC_N3_WAIT_CMD_MS);

	inst->cmd=Write_peripheral_power_status;
	inst->option_byte=Gain_high;
	if(IS_OPC_N3_Instruction(SpiHandle, inst, aRxBuffer)==0)
	{
		Error_Handler();
	}
	HAL_Delay(OPC_N3_WAIT_CMD_LONG_MS);

	inst->cmd=Write_peripheral_power_status;
	inst->option_byte=Fan_on;
	if(IS_OPC_N3_Instruction(SpiHandle, inst, aRxBuffer)==0)
	{
		Error_Handler();
	}
	HAL_Delay(OPC_N3_WAIT_FAN_MS);

	inst->cmd=Read_Histogram_data; //first data sets has to be ignored as written in the opc-n3 datasheet
	inst->option_byte=No_option;
	if(IS_OPC_N3_Instruction(SpiHandle, inst, aRxBuffer)==0)
	{
		Error_Handler();
	}
	HAL_Delay(OPC_N3_WAIT_HIST_MS);
	return 1;
}

/**
 * \brief stops the OPC-N3 and sets up laser and fan for off-mode
 * @param SpiHandle needed for SPI communication via HAL-Functions
 * @param inst is the instruction to be sent via SPI
 * @param aRxBuffer is the Buffer for received answers
 * @return1 for success
 */
int IS_OPC_N3_stop(SPI_HandleTypeDef* SpiHandle, inst_t* inst, uint8_t* aRxBuffer)
{
	inst->cmd=Write_peripheral_power_status;
	inst->option_byte=Laser_digit_pot_off;
	if(IS_OPC_N3_Instruction(SpiHandle, inst, aRxBuffer)==0)
	{
		Error_Handler();
	}

	HAL_Delay(50);

	inst->cmd=Write_peripheral_power_status;
	inst->option_byte=Laser_switch_off;
	if(IS_OPC_N3_Instruction(SpiHandle, inst, aRxBuffer)==0)
	{
		Error_Handler();
	}
	HAL_Delay(50);

	inst->cmd=Write_peripheral_power_status;
	inst->option_byte=Gain_low;
	if(IS_OPC_N3_Instruction(SpiHandle, inst, aRxBuffer)==0)
	{
		Error_Handler();
	}
	HAL_Delay(50);

	inst->cmd=Write_peripheral_power_status;
	inst->option_byte=Fan_off;
	if(IS_OPC_N3_Instruction(SpiHandle, inst, aRxBuffer)==0)
	{
		Error_Handler();
	}
	HAL_Delay(50);
	return 1;
}

/**
 * \brief reads data from OPC and adds them up to save memory
 * @param SpiHandle is neede for SPI communication via HAL-Functions
 * @param inst is the instruction to be sent
 * @param aRxBuffer is the Buffer for received data
 * @param Histogram is the replied data from OPC added up
 * @param count_measure indicates how many measurements have been added up
 * @return 1 for success
 */
int IS_OPC_N3_read_data(SPI_HandleTypeDef* SpiHandle, inst_t* inst, uint8_t* aRxBuffer, uint16_t* Histogram, uint32_t* temperatur, uint32_t* humidity)
{
	uint8_t hist_cnt = 0;
	//uint8_t buff_cnt = 0;
	inst->cmd=Read_Histogram_data;
	if(IS_OPC_N3_Instruction(SpiHandle, inst, aRxBuffer)==0)
		Error_Handler();

	for(hist_cnt=0;hist_cnt<BINS;hist_cnt++)
		Histogram[hist_cnt] = (uint16_t)(((uint16_t)aRxBuffer[(hist_cnt<<1)+1]<<8) | aRxBuffer[hist_cnt<<1]);
	Histogram[24] = (uint16_t)(((uint16_t)aRxBuffer[57]<<8) | aRxBuffer[56]);
	Histogram[25] = (uint16_t)(((uint16_t)aRxBuffer[59]<<8) | aRxBuffer[58]);
	Histogram[26] = (uint16_t)(((uint16_t)aRxBuffer[55]<<8) | aRxBuffer[54]);
	return 1;
}

/**
 * \brief has been used for testing, copies the string from source to target within a length of length
 * @param target is the string to be filled
 * @param source is the string containing data
 * @param length is the length of the string to be copied
 */
void IS_OPC_N3_str_cpy(uint8_t *target, uint8_t *source, uint8_t length)
{
	uint8_t i	=	0;
	for(i=0; i<length; i++)
		target[i]=source[i];
}

/**
 * \brief has been used for testing, checks if the received Data is an valid info string
 * @param aRxBuffer is the Buffer for received data
 * @return 1 for valid string, 0 for invalid string
 */
int IS_OPC_N3_info_str_cmp(uint8_t *aRxBuffer)
{
	if((aRxBuffer[0]=='O')&&(aRxBuffer[1]=='P')&&(aRxBuffer[2]=='C')&&(aRxBuffer[3]=='-')&&(aRxBuffer[4]=='N')&&(aRxBuffer[5]=='3'))
		return 1;
	else
		return 0;
}

/**
 * \brief checks if all the recieved data is 0
 * @param Histogram received data added up
 * @return
 */
int IS_OPC_N3_valid_data(uint8_t* data)
{
	uint8_t sum=0;
	for(uint8_t i=0;i<BINS;i++)
	{
		sum+=data[i];
	}
	if(sum==0)
		return 0;

	return 1;
}
