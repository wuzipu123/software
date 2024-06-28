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
static uint8_t mainWriteValuesToString(sps30_data_t *averageValues);

static uint8_t mainSumCurrentValues(sps30_data_t *averageValues, sps30_data_t *currentValues);
static uint8_t mainCalculateAverageValues(sps30_data_t *averageValues, int nmbMeasurements);
static uint8_t mainResetAverageValues(sps30_data_t *averageValues);

// Slave address-------------------------------------------------------------
int address = 0;

extern UART_HandleTypeDef uart;
extern uint8_t Uart_RxBuffer[UART_RECEIVE_MAX_LENGTH];

__IO ITStatus UartReady = RESET;
__IO ITStatus UartReceived = RESET;

uint8_t init_completed = 0;

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
static const char infoString[] = {"\x02"
								  "{"
										"\"s_n\":\"SPS30\","
										"\"s_t\":\"Particle Sensor\","
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
										"\"p_v\":\"1.0\""
								  "}"
								  "\x03"};

/**
 * \brief ValueString for the motherboard.
 *
 * \param valueString
 * v value
 */
char valueString[] = {"\x02"
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

int main(void)
{
	SystemClock_Config();
	HAL_Init(); // STM32L0xx HAL library initialization
	commUartInit(&uart);
	commAddressInit(&address);
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
				HAL_Delay(1); //waiting: mainboard needs time to be ready for receiving
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
				mainWriteValuesToString(&averageValues);
				HAL_Delay(1); //waiting: mainboard needs time to be ready for receiving
				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_SET);
				UartReady = RESET;
				HAL_UART_Transmit_IT(&uart, (uint8_t*)valueString, sizeof(valueString));
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
			HAL_UART_Receive_IT(&uart, Uart_RxBuffer, UART_RECEIVE_MAX_LENGTH);
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
	UartReceived = SET;

	if ((Uart_RxBuffer[1] == '{') && (Uart_RxBuffer[UART_RECEIVE_MAX_LENGTH - 3] == '}')) // valid json message
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
}

/**
 * \brief Converse the float \ref averageValues to a string and populate the \ref valueString.
 *
 * \param averageValues Pointer to the stored average values.
 * \return No error value.
 */
uint8_t mainWriteValuesToString(sps30_data_t *averageValues)
{
	int cnt;

	for(cnt = 0; cnt < SPS30_NUM_READ_VALUES; cnt++)
	{
		writeFloat(averageValues->raw_values[cnt], 10, &valueString[13 + cnt * 19]);
	}

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
