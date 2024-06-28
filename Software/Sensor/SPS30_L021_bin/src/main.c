/*
 * main.c
 *
 *  Created on: 06.06.2019
 *      Author: mknoll
 */

#include "main.h"
#include "sps30.h"
#include "misc.h"
#include "comm.h"
#include "conversion.h"

// Function prototypes-------------------------------------------------------
void SystemClock_Config(void);

static uint8_t mainSendCMDtoSensor();
static uint8_t mainConstructDataResponse(sps30_data_t *averageValues);

static uint8_t mainSumCurrentValues(sps30_data_t *averageValues, sps30_data_t *currentValues);
static uint8_t mainCalculateAverageValues(sps30_data_t *averageValues, int nmbMeasurements);
static uint8_t mainResetAverageValues(sps30_data_t *averageValues);
void writeCRC16HexString(char *outString);

// Slave address-------------------------------------------------------------
int address = 0;

extern UART_HandleTypeDef uart;
extern uint8_t Uart_RxBuffer[UART_RECEIVE_MAX_LENGTH];
CRC_HandleTypeDef hcrc;

__IO ITStatus UartReady = RESET;
__IO ITStatus UartReceived = RESET;

uint8_t init_completed = 0;

uint16_t uart_receive_counter = 0;
uint16_t uart_num_receive_bytes = 4;

// Counter for number of measurements----------------------------------------
static int nmbMeasurements = 0;

// Current and average values of the measured data---------------------------
static sps30_data_t currentValues = {0};
static sps30_data_t averageValues = {0};

// Command from motherboard--------------------------------------------------
sps30_cmd_t cmd;

/**
 * \brief InfoString for the motherboard.
 *
 * \param infoString
 * s_n sensor_name
 * s_t sensor_type
 * n_o_d number_of_datasets
 * d_n data_name
 * u unit
 */
static char infoString[] = {"\x02"
								  "{"
										"\"s_n\":\"SPS30\","
										"\"s_t\":\"Particle Sensor\","
										"\"s_k_a\":\"true\","
										"\"n_o_d\":\"10\","
										"\"datasets\":["
											"{\"d_n\":\"Mass PM1.0\",\"u\":\"ug/m^3\"},"
											"{\"d_n\":\"Mass PM2.5\",\"u\":\"ug/m^3\"},"
											"{\"d_n\":\"Mass PM4.0\",\"u\":\"ug/m^3\"},"
											"{\"d_n\":\"Mass PM10.0\",\"u\":\"ug/m^3\"},"
											"{\"d_n\":\"Number PM0.5\",\"u\":\"#/cm^3\"},"
											"{\"d_n\":\"Number PM1.0\",\"u\":\"#/cm^3\"},"
											"{\"d_n\":\"Number PM2.5\",\"u\":\"#/cm^3\"},"
											"{\"d_n\":\"Number PM4.0\",\"u\":\"#/cm^3\"},"
											"{\"d_n\":\"Number PM10.0\",\"u\":\"#/cm^3\"},"
											"{\"d_n\":\"Typical Particle Size\",\"u\":\"um\"}"
										"],"
										"\"su_t\":\"30\","
										"\"p_v\":\"2.0\""
								  "}"
								  "CRCV"
								  "\x03"};

/**
 * \brief ValueString for the motherboard.
 *
 * \param valueString
 * v value
 */
/*char valueString[] = {"\x02"
					  "{"
							"\"v\":["
								"{\"v\":\"          \"},"
								"{\"v\":\"          \"},"
								"{\"v\":\"          \"},"
								"{\"v\":\"          \"},"
								"{\"v\":\"          \"},"
								"{\"v\":\"          \"},"
								"{\"v\":\"          \"},"
								"{\"v\":\"          \"},"
								"{\"v\":\"          \"},"
								"{\"v\":\"          \"}"
							"]"
					  "}"
					  "\x03"};
*/

uint8_t data_response[UART_BIN_DATA_RESPONSE_LENGTH];

int main(void)
{
	SystemClock_Config();
	HAL_Init(); // STM32L0xx HAL library initialization
	commUartInit(&uart);
	commAddressInit(&address);
	miscCRCInit(&hcrc);
	//miscLEDInit();

	UartReady = RESET;

	mainSendCMDtoSensor();
	return 0;
}

/**
 * \brief Process the commands from the motherboard.
 *
 * \return No error value.
 */
uint8_t mainSendCMDtoSensor()
{
	cmd = SPS30_WAITING_FOR_CMD;
	while (1)
	{
		switch (cmd)
		{
			case SPS30_SENSOR_INFO:
				UartReady = RESET;
				writeCRC16HexString(infoString + sizeof(infoString) - 6);
				HAL_Delay(3); //waiting: mainboard needs time to be ready for receiving
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
				HAL_UART_Transmit_IT(&uart, (uint8_t*)infoString, sizeof(infoString));
				while (UartReady == RESET);
				UartReady = RESET;
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);
				cmd = SPS30_WAITING_FOR_CMD;
				break;

			case SPS30_SENSOR_INIT:
				if (sps30Init()) // SPS30 Sensor initialization
				{
					miscErrorHandler();
				}
				init_completed = 1;
				cmd = SPS30_START_MEAS;
				break;

			case SPS30_START_MEAS:
				if (sps30StartMeasurement())
				{
					miscErrorHandler();
				}
				HAL_Delay(SPS30_WAIT_READ_MEAS);
				cmd = SPS30_READ_MEAS;
				break;

			case SPS30_READ_MEAS:
				if(!sps30ReadReadyFlag())
				{
					if (sps30ReadMeasurement(&currentValues))
					{
						miscErrorHandler();
					}
					nmbMeasurements++;
					mainSumCurrentValues(&averageValues, &currentValues);
				}
				HAL_Delay(10);
				break;

			case SPS30_TRANSMIT_DATA:
				mainCalculateAverageValues(&averageValues, nmbMeasurements);
				mainConstructDataResponse(&averageValues);
				HAL_Delay(3); //waiting: mainboard needs time to be ready for receiving
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
				UartReady = RESET;
				HAL_UART_Transmit_IT(&uart, data_response, sizeof(data_response));
				while (UartReady == RESET);
				UartReady = RESET;
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);

				mainResetAverageValues(&averageValues);
				nmbMeasurements = 0;

				if (init_completed)
				{
					cmd = SPS30_READ_MEAS;
				}
				else
				{
					cmd = SPS30_SENSOR_INIT;
				}
				//cmd = SPS30_STOP_MEAS;
				break;

			case SPS30_STOP_MEAS:
				if (sps30StopMeasurement())
				{
					miscErrorHandler();
				}
				init_completed = 0;
				cmd = SPS30_WAITING_FOR_CMD;
				break;

			case SPS30_WAITING_FOR_CMD:
				HAL_Delay(1);
				break;

			default:
				cmd = SPS30_WAITING_FOR_CMD;
				break;
		}

		if (UartReceived == SET)
		{
			HAL_UART_Receive_IT(&uart, Uart_RxBuffer, UART_BIN_HEADER_LENGTH);
			UartReceived = RESET;
		}
	}

	return 0;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *uart)
{
	HAL_UART_StateTypeDef uartState =  HAL_UART_GetState(uart);
	if ((uartState & 0x01) == 0)
	{
		UartReady = SET;
	}

	return;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *uart)
{
	if (uart_receive_counter == 0)
	{
		uart_receive_counter = UART_BIN_HEADER_LENGTH;
		if (Uart_RxBuffer[0] == '\x02')
		{
			HAL_UART_Receive_IT(uart, Uart_RxBuffer + UART_BIN_HEADER_LENGTH, UART_RECEIVE_MAX_LENGTH - UART_BIN_HEADER_LENGTH);
			return;
		} else if (Uart_RxBuffer[0] == '\xA5' && Uart_RxBuffer[UART_BIN_ADDRESS_POS] == address)
		{
			uint16_t message_length = *((uint16_t *)(Uart_RxBuffer + UART_BIN_MESSAGE_LENGTH_POS));
			HAL_UART_Receive_IT(uart, Uart_RxBuffer + UART_BIN_HEADER_LENGTH, message_length - UART_BIN_HEADER_LENGTH);
			return;
		}
		else
		{
			uart_receive_counter = 0;
			UartReceived = SET;
			return;
		}
	}

	if ((Uart_RxBuffer[0] == '\x02')
			&& (Uart_RxBuffer[1] == '{')
			&& (Uart_RxBuffer[UART_RECEIVE_MAX_LENGTH - 3] == '}')) // valid json message
	{
		if (address == (Uart_RxBuffer[ADDRESS_UART] - 0x30))
		{
			switch ((char)(Uart_RxBuffer[INST_UART]))
			{
				case 'i':
					cmd = SPS30_SENSOR_INFO;
					break;
				case 'm':
					cmd = SPS30_SENSOR_INIT;
					break;
				case 'd':
					cmd = SPS30_TRANSMIT_DATA;
					break;
				case 's':
					cmd = SPS30_STOP_MEAS;
					break;
				default:
					break;
			}
		}
	}
	else if(Uart_RxBuffer[0] == '\xA5')
	{
		if (Uart_RxBuffer[UART_BIN_ADDRESS_POS] == address)
		{
			switch (Uart_RxBuffer[UART_BIN_INST_POS])
			{
				case UART_BIN_INST_SEND_INFO:
					cmd = SPS30_SENSOR_INFO;
					break;
				case UART_BIN_INST_INIT_MEAS:
					cmd = SPS30_SENSOR_INIT;
					break;
				case UART_BIN_INST_SEND_DATA:
					cmd = SPS30_TRANSMIT_DATA;
					break;
				case UART_BIN_INST_STOP_MEAS:
					cmd = SPS30_STOP_MEAS;
					break;
				default:
					break;
			}
		}
	}

	uart_receive_counter = 0;
	UartReceived = SET;
}

/**
 * \brief Write the start byte, the \ref address, the message length,
 * the float \ref averageValues and the computed crc value into the
 * \ref data_response array.
 *
 * \param averageValues Pointer to the stored average values.
 * \return No error value.
 */
uint8_t mainConstructDataResponse(sps30_data_t *averageValues)
{
	int cnt;

	data_response[0] = 0xA5;
	data_response[1] = (uint8_t)address;
	data_response[2] = (uint8_t)(UART_BIN_DATA_RESPONSE_LENGTH & 0x00FF);
	data_response[3] = (uint8_t)((UART_BIN_DATA_RESPONSE_LENGTH & 0xFF00) >> 8U);

	float *data = (float *)(data_response + UART_BIN_HEADER_LENGTH);
	for(cnt = 0; cnt < SPS30_NUM_READ_VALUES; cnt++)
	{
		data[cnt] = averageValues->raw_values[cnt];
	}

	uint16_t crc = (uint16_t)HAL_CRC_Calculate(&hcrc, (uint32_t *)data_response, UART_BIN_DATA_RESPONSE_LENGTH - sizeof(uint16_t));
	data_response[UART_BIN_DATA_RESPONSE_LENGTH - 2] = (uint8_t)(crc & 0x00FF);
	data_response[UART_BIN_DATA_RESPONSE_LENGTH - 1] = (uint8_t)((crc & 0xFF00) >> 8U);

	return 0;
}

/**
 * \brief Add the \ref currentValues up.
 *
 * \param averageValues Pointer to the stored average values.
 * \param currentValues Pointer to the stored newest values.
 * \return No error value.
 */
uint8_t mainSumCurrentValues(sps30_data_t *averageValues, sps30_data_t *currentValues)
{
	int cnt;

	for(cnt = 0; cnt < SPS30_NUM_READ_VALUES; cnt++)
	{
		averageValues->raw_values[cnt] += currentValues->raw_values[cnt];
	}

	return 0;
}

/**
 * \brief Calculate the average values by dividing the added up values through the number of measurements.
 *
 * \param averageValues Pointer to the stored average values.
 * \param nmbMeasurements Integer of the number of measurements.
 * \return No error value.
 */
uint8_t mainCalculateAverageValues(sps30_data_t *averageValues, int nmbMeasurements)
{
	int cnt;

	for(cnt = 0; cnt < SPS30_NUM_READ_VALUES; cnt++)
	{
		averageValues->raw_values[cnt] = averageValues->raw_values[cnt] / nmbMeasurements;
	}

	return 0;
}

/**
 * \brief Reset the \ref averageValues.
 *
 * \param averageValues Pointer to the stored average values.
 * \return No error value.
 */
uint8_t mainResetAverageValues(sps30_data_t *averageValues)
{
	int cnt;

	for(cnt = 0; cnt < SPS30_NUM_READ_VALUES; cnt++)
	{
		averageValues->raw_values[cnt] = 0.0;
	}

	return 0;
}

/**
 * \brief Calculate CRC value and write CRC value as hex string
 * into the \ref infoString before the stop byte.
 *
 * \param outString Pointer to the position where the string should be written to.
 */
void writeCRC16HexString(char *outString)
{
	uint16_t crc = (uint16_t)HAL_CRC_Calculate(&hcrc, (uint32_t *)(infoString + 1), sizeof(infoString) - 7);
	static const char hexDigits[] = "0123456789ABCDEF";
	for(int i = 3; i >= 0; i--) {
		outString[i] = hexDigits[crc % 16];
		crc /= 16;
	}
}


