/*
 * main.c
 *
 *  Created on: 10.07.2019
 *      Author: mknoll
 */

#include "main.h"
#include "defines.h"
#include "conversion.h"
#include "stdbool.h"
#include "Error_Handler.h"

//USART_HandleTypeDef UartHandle;
UART_HandleTypeDef UartHandle;


extern uint8_t readDataFromOpc;
extern uint8_t Uart_RxBuffer[UART_RECEIVE_MAX_LENGTH];
__IO ITStatus UartReady = RESET;
__IO ITStatus UartReceived = RESET;
static uint8_t card_address = 0;

volatile uint8_t mainboard_command = 0; //modified by uart-interrupt

/**
 * \brief  Initialization and general program sequence with state machine
 * @return
 */
int main (void)
{

	static uint8_t aRxBuffer[MAXSIZE];
	/*
	 * s_n 		sensor name
	 * s_t		sensor type
	 * n_o_d		number of datasets
	 * d_n 		data name
	 * u			unit
	 * su_t		startup time in seconds
	 * p_v		protocoll version
	 */

	static const char Info_String[] = {
			"\x02""{\"s_n\":\"OPC-N3\","
			"\"s_t\":\"Particle Sensor\","
			"\"n_o_d\":\"27\",\"datasets\""
			":[{\"d_n\":\"Bin0 350nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin1 460nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin2 660nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin3 1000nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin4 1300nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin5 1700nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin6 2300nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin7 3000nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin8 4000nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin9 5200nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin10 6500nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin11 8000nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin12 10000nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin13 12000nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin14 14000nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin15 16000nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin16 18000nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin17 20000nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin18 22000nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin19 25000nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin20 28000nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin21 31000nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin22 34000nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"Bin23 37000nm\",\"u\":\"#/s\"},"
			"{\"d_n\":\"t\",\"u\":\"C_raw\"},"
			"{\"d_n\":\"h\",\"u\":\"%_raw\"}],"
			"{\"d_n\":\"flow rate\",\"u\":\"ml/s\"},"
			"\"su_t\":\"30\",\"p_v\":\"1.0\"}""\x03"};

	static char valueString[2][19]={"{\"v\":\"          \"},","{\"v\":\"          \"},"};
	static inst_t inst;
	static SPI_HandleTypeDef SpiHandle;

	static uint16_t Histogram[NOD]={0};
	static uint32_t temperatur=0;
	static uint32_t humidity=0;

	uint8_t count_measure=0;
	uint8_t init_completed=0;
	_Bool swapping_buffer = 0;
	uint8_t pos_json=0;
	char bracket_o[]={"\x02""{\"v\":["};
	char bracket_c[]={"]}""\x03"};

	//initialisation
	HW_init_CLK();
	//SystemClock_Config();
	HAL_Init();

	HW_init_GPIO(&card_address);
	//card_address=4; //for older mainboard versions
	HW_init_SPI(&SpiHandle);
	HW_init_TIMER21();
	HW_init_UART(&UartHandle);
	UartReady = RESET;
	mainboard_command = WAITING_FOR_COMMAND;
	while(1)
	{
		switch (mainboard_command)
		{
			case GET_SENSOR_INFO:
				UartReady=RESET;
				HAL_Delay(1);  //waiting: mainboard needs time to be ready for receiving
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
				HAL_UART_Transmit_IT(&UartHandle, (uint8_t*)Info_String, sizeof(Info_String));
				while(UartReady==RESET);
				UartReady=RESET;
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);
				HAL_Delay(10);
				mainboard_command=WAITING_FOR_COMMAND;
				break;

			case INIT_SENSOR_AND_START_MEASURING:
				IS_OPC_N3_start(&SpiHandle, &inst, aRxBuffer);
				IS_OPC_N3_read_data(&SpiHandle, &inst, aRxBuffer, Histogram, &temperatur, &humidity); //to discard invalid data, first dataset is invalid
				//Reset_Histogram(Histogram, &temperatur, &humidity);
				//count_measure=0;
				init_completed=1;
				mainboard_command=SENSOR_MEASURING;
				break;

			case SENSOR_MEASURING:

				if(readDataFromOpc)
				{
					uint8_t request_counter = 0;
					uint8_t is_data_valid = 0;
					do
					{
                        IS_OPC_N3_read_data(&SpiHandle, &inst, aRxBuffer, Histogram, &temperatur, &humidity);
                        request_counter++;
                        is_data_valid = IS_OPC_N3_valid_data(aRxBuffer);
					}while(!is_data_valid && request_counter < MAX_NUM_FAIL_DATA_REQ);
					if(is_data_valid)
						count_measure++;
					readDataFromOpc = 0;
				}
				break;

			case TRANSMITT_DATA_TO_MAINBOARD:
				//Average_Histogram(Histogram, &count_measure, &temperatur, &humidity);
				swapping_buffer=0;
				HAL_Delay(5);//waiting: mainboard needs time to be ready for receiving
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
				UartReady=RESET;
				HAL_UART_Transmit_IT(&UartHandle, (uint8_t*)(bracket_o),7);
				pos_json=0;
				writeInt(Histogram[pos_json], (NUM_DIGITS), &valueString[(uint8_t)swapping_buffer][6]);
				while(UartReady == RESET);
				UartReady=RESET;
				while(pos_json<(NOD-1))
				{
					HAL_UART_Transmit_IT(&UartHandle, (uint8_t*)(&valueString[(uint8_t)swapping_buffer][0]), 19);
					swapping_buffer = (!swapping_buffer);
					pos_json++;
					writeInt(Histogram[pos_json], (NUM_DIGITS), &valueString[(uint8_t)swapping_buffer][6]);
					while(UartReady == RESET);
					UartReady=RESET;

				}
				HAL_UART_Transmit_IT(&UartHandle, (uint8_t*)(&valueString[(uint8_t)swapping_buffer][0]), 18);
				while(UartReady == RESET);
				UartReady=RESET;
				HAL_UART_Transmit_IT(&UartHandle, (uint8_t*)(bracket_c),3);
				while(UartReady == RESET);
				UartReady=RESET;
				HAL_Delay(1);
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);
				Reset_Histogram(Histogram, &temperatur, &humidity);
				count_measure=0;
				if(init_completed)
					mainboard_command=SENSOR_MEASURING;
				else
					mainboard_command=INIT_SENSOR_AND_START_MEASURING;
				break;

			case STOP_MEASURING:
				IS_OPC_N3_stop(&SpiHandle, &inst, aRxBuffer);
				init_completed=0;
				mainboard_command=WAITING_FOR_COMMAND;
				break;

			case WAITING_FOR_COMMAND:
				HAL_Delay(1);
				break;

			case TESTMODE: // program flow for continuous measuring of data with start and stop routine for testing
				//HAL_Delay(1);//test_full_measurement();
				mainboard_command=WAITING_FOR_COMMAND;
				break;

			default:
				mainboard_command=WAITING_FOR_COMMAND;
				break;
		}
		if(UartReceived == SET)
		{
			HAL_UART_Receive_IT(&UartHandle, Uart_RxBuffer, UART_RECEIVE_MAX_LENGTH);
			UartReceived = RESET;
		}
	}
}

/**
 * \brief transmit callback for completed transmission
 * the TxCpltCallback is executed for every byte, not for the whole transmission,
 * the uartState status bit has to be checked for every byte
 * @param UartHandle is used for UART communication via HAL Functions
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	HAL_UART_StateTypeDef uartState =  HAL_UART_GetState(UartHandle);
	if((uartState & 0x01) == 0)
		UartReady = SET;
	return;
}

/**
 * \brief the recive callback is executed for every fully received mainboard command via UART
 * it checks validity and sets the switching variable for the main program procedure
 * @param UartHandle is used for UART communication via HAL Functions
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
	UartReceived=SET;
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
	if((Uart_RxBuffer[1]=='{')&&(Uart_RxBuffer[UART_RECEIVE_MAX_LENGTH-3]=='}')) //valid json message
	{
		if(card_address==((Uart_RxBuffer[ADDRESS_UART])-CHAR_OFFSET))
		{
			switch((Uart_RxBuffer[INST_UART]))
			{
				case 'm':
					mainboard_command=INIT_SENSOR_AND_START_MEASURING;
					//UartReady = SET;
					break;
				case 's':
					mainboard_command=STOP_MEASURING;
					//UartReady = SET;
					break;
				case 'd':
					mainboard_command=TRANSMITT_DATA_TO_MAINBOARD;
					//UartReady = SET;
					break;
				case 'i':
					mainboard_command=GET_SENSOR_INFO;
					//UartReady = SET;
					break;
				default:
					//invalid command
					break;
			}
		}
	}
}

/**
 * \brief it generates the average of the datasets
 * @param Histogram is the data added up
 * @param count_measure signals how many datasets have been added up in Histogram
 */
void Average_Histogram(uint16_t* Histogram, uint8_t* count_measure, uint32_t* temperature, uint32_t* humidity)
{
	uint8_t cnt =0;
	for(cnt=0;cnt<BINS;cnt++)
		Histogram[cnt]/=(*count_measure);
	Histogram[cnt++]=(uint16_t)(*temperature/((uint32_t)(*count_measure)));
	Histogram[cnt]=(uint16_t)(*humidity/((uint32_t)(*count_measure)));
}

/**
 * \brief resets Histogram to 0 for all Bins
 * @param Histogram is the data added up
 */
void Reset_Histogram(uint16_t* Histogram, uint32_t* temperature, uint32_t* humidity)
{
	uint8_t cnt=0;
	for(cnt=0;cnt<NOD;cnt++)
		Histogram[cnt]=0;
	*temperature=0;
	*humidity=0;
}





















