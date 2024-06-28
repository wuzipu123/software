/*
 * main.c
 *
 *  Created on: 18.12.2019
 *      Author: mknoll
 */

#include "main.h"
#include "bme280_defs.h"
#include "bme280.h"
#include "bme280_SPI_functions.h"
#include "stm32l0xx.h"
#include "ads1118.h"

#include "defines.h"
#include "conversion.h"
#include "stdbool.h"
#include "Error_Handler.h"

UART_HandleTypeDef UartHandle;

#define SPI_MODE_AD1118 1
#define SPI_MODE_BME280 0


uint8_t readDataFromSensor;
extern uint8_t Uart_RxBuffer[UART_RECEIVE_MAX_LENGTH];
__IO ITStatus UartReady = RESET;
__IO ITStatus UartReceived = RESET;
static uint8_t card_address = 0;
SPI_HandleTypeDef SpiHandle;

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
			"\x02""{\"s_n\":\"BME280-A4\","
			"\"s_t\":\"Gas\","
			"\"n_o_d\":\"7\",\"datasets\""
			":[{\"d_n\":\"rel_hum\",\"u\":\"perc\"},"
			"{\"d_n\":\"baro_pres\",\"u\":\"Pa\"},"
			"{\"d_n\":\"amb-temp\",\"u\":\"degC\"},"
			"{\"d_n\":\"NO2\",\"u\":\"ppbraw\"},"
			"{\"d_n\":\"O3\",\"u\":\"ppbraw\"},"
			"{\"d_n\":\"NO\",\"u\":\"ppbraw\"},"
			"{\"d_n\":\"PID\",\"u\":\"ppbraw\"}],"
			"\"su_t\":\"30\",\"p_v\":\"1.0\"}""\x03"};

	static char valueString[2][19]={"{\"v\":\"          \"},","{\"v\":\"          \"},"};
	char bracket_o[]={"\x02""{\"v\":["};
	char bracket_c[]={"]}""\x03"};
	uint8_t swapping_buffer=0;

	int16_t conversion_data[4]={1,2,3,4};


	static uint32_t Data[NOD]={0};

	uint8_t count_measure	=	0;
	uint8_t init_completed	=	0;
	uint8_t pos_json		=	0;
	uint8_t BME280_mode		=	3; //normal mode
	int8_t 	rslt 			= 	BME280_OK;
	uint8_t settings_sel;
	struct bme280_data comp_data;
	struct bme280_dev dev;
	struct bme280_calib_data bme_data;

	//initialisation
	SystemClock_Config();
	HAL_Init();

	HW_init_GPIO(&card_address);
	//card_address=4; //for older mainboard versions
	HW_init_SPI(&SpiHandle, SPI_MODE_AD1118);
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
				HW_init_set_SPI(&SpiHandle, SPI_MODE_BME280);

				dev.dev_id = 0;
				dev.intf = BME280_SPI_INTF;
				dev.read = user_spi_read;
				dev.write = user_spi_write;
				dev.delay_ms = user_delay_ms;
				rslt = bme280_init(&dev);
				bme280_get_sensor_settings(&dev);

				dev.settings.osr_h = BME280_OVERSAMPLING_1X;
				dev.settings.osr_p = BME280_OVERSAMPLING_16X;
				dev.settings.osr_t = BME280_OVERSAMPLING_2X;
				dev.settings.filter = BME280_FILTER_COEFF_16;

			    settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;
			    rslt = bme280_set_sensor_settings(settings_sel, &dev);

				count_measure=0;
				init_completed=1;
				mainboard_command=SENSOR_MEASURING;
				break;

			case SENSOR_MEASURING:

				if(readDataFromSensor)
				{
					rslt = bme280_set_sensor_mode(BME280_FORCED_MODE, &dev);
					dev.delay_ms(40);
					bme280_get_sensor_data(BME280_ALL, &comp_data, &dev);

					//change settings for ADS1118, read both channels of both adc, set back to normal SPI mode
					HW_init_set_SPI(&SpiHandle, SPI_MODE_AD1118);
					ads1118_start(&SpiHandle, 0, 0, &conversion_data[0]);
					ads1118_start(&SpiHandle, 0, 1, &conversion_data[1]);
					ads1118_start(&SpiHandle, 1, 0, &conversion_data[2]);
					ads1118_start(&SpiHandle, 1, 1, &conversion_data[3]);
					//change settings for BME
					HW_init_set_SPI(&SpiHandle, SPI_MODE_BME280);
					Data[0]=comp_data.humidity;
					Data[1]=comp_data.pressure;
					Data[2]=comp_data.temperature;
					Data[3]=(int32_t)(conversion_data[0]);
					Data[4]=(int32_t)(conversion_data[1]);
					Data[5]=(int32_t)(conversion_data[2]);
					Data[6]=(int32_t)(conversion_data[3]);
					readDataFromSensor = 0;
				}
				break;

			case TRANSMITT_DATA_TO_MAINBOARD:
				swapping_buffer=0;
				HAL_Delay(5);//waiting: mainboard needs time to be ready for receiving
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
				UartReady=RESET;
				HAL_UART_Transmit_IT(&UartHandle, (uint8_t*)(bracket_o),7);
				pos_json=0;
				writeInt(Data[pos_json], (NUM_DIGITS), &valueString[(uint8_t)swapping_buffer][6]);
				while(UartReady == RESET);
				UartReady=RESET;
				while(pos_json<(NOD-1))
				{
					HAL_UART_Transmit_IT(&UartHandle, (uint8_t*)(&valueString[(uint8_t)swapping_buffer][0]), 19);
					swapping_buffer = (!swapping_buffer);
					pos_json++;
					writeInt(Data[pos_json], (NUM_DIGITS), &valueString[(uint8_t)swapping_buffer][6]);
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
				Reset_Data(Data);
				count_measure=0;
				if(init_completed)
					mainboard_command=SENSOR_MEASURING;
				else
					mainboard_command=INIT_SENSOR_AND_START_MEASURING;
				break;

			case STOP_MEASURING:
				//IS_OPC_N3_stop(&SpiHandle, &inst, aRxBuffer);
				init_completed=0;
				mainboard_command=WAITING_FOR_COMMAND;
				break;

			case WAITING_FOR_COMMAND:
				HAL_Delay(1);
				break;

			case TESTMODE: // program flow for continuous measuring of data with start and stop routine for testing
				HAL_Delay(1);//test_full_measurement();
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
	HAL_UART_StateTypeDef uartState =   HAL_UART_GetState(UartHandle);
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
					break;
				case 's':
					mainboard_command=STOP_MEASURING;
					break;
				case 'd':
					mainboard_command=TRANSMITT_DATA_TO_MAINBOARD;
					break;
				case 'i':
					mainboard_command=GET_SENSOR_INFO;
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
void Average_Data(uint16_t* Data, uint8_t* count_measure)
{
	uint8_t cnt =0;
	for(cnt=0;cnt<NOD;cnt++)
		Data[cnt]/=(*count_measure);
	//Data[cnt++]=(uint16_t)(*temperature/((uint32_t)(*count_measure)));
	//Data[cnt]=(uint16_t)(*humidity/((uint32_t)(*count_measure)));
}

/**
 * \brief resets Histogram to 0 for all Bins
 * @param Histogram is the data added up
 */
void Reset_Data(uint16_t* Data)
{
	uint8_t cnt=0;
	for(cnt=0;cnt<NOD;cnt++)
		Data[cnt]=0;
}
