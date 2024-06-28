/*
 * sps30.h
 *
 *  Created on: 27.06.2019
 *      Author: tolotos
 */

#ifndef SPS30_H_
#define SPS30_H_

#include "stm32l0xx_hal.h"
#include <stdint.h>

// Definition for I2Cx Pins--------------------------------------------------
#define I2Cx_SCL_PIN GPIO_PIN_6
#define I2Cx_SCL_GPIO_PORT GPIOB
#define I2Cx_SDA_PIN GPIO_PIN_7
#define I2Cx_SDA_GPIO_PORT GPIOB
#define I2Cx_SCL_SDA_AF GPIO_AF1_I2C1

// #define I2C Address-------------------------------------------------------
#define SPS30_I2C_ADDR 0xd2 // 1101 0010 SPS30 I2C Address, left shifted by 1 bit from 0x69

// #define SPS30 commands----------------------------------------------------
#define SPS30_AUTO_CLEAN 0x8004 // Read/Write Auto Cleaning Interval
#define SPS30_FAN_CLEAN 0x5607 // Start Fan Cleaning
#define SPS30_ARTCL_CODE 0xD025 // Read Article Code
#define SPS30_SRL_NRB 0xD033 // Read Serial Number
#define SPS30_RESET 0xD304 // Reset

// #define for different command options-------------------------------------
#define SPS30_START_MEAS_MODE 0x0300

// #define send and receive length-------------------------------------------
#define	MAX_SEND_LENGTH 10
#define	MAX_RECEIVE_LENGTH 60

// #define position of the particle mass concentration values in receiveBuffer
#define MASS_CONC_PM1_0 0
#define MASS_CONC_PM2_5 6
#define MASS_CONC_PM4_0 12
#define MASS_CONC_PM10_0 18

// #define position of the particle number concentration values in receiveBuffer
#define NMBR_CONC_PM0_5 24
#define NMBR_CONC_PM1_0 30
#define NMBR_CONC_PM2_5 36
#define NMBR_CONC_PM4_0 42
#define NMBR_CONC_PM10_0 48

//#define position of the typical particle size value in receiveBuffer
#define TYP_PM_SIZE 54

//#define times in ms for HAL_Delay
#define SPS30_WAIT_NEXT_MEAS 1000 // Wait 1sec before taking new values
#define SPS30_WAIT_READ_MEAS 1000//60000 // Wait 1min before taking the measured values

#define SPS30_NUM_READ_VALUES 10

// Define SPS30 commands for switch case
typedef enum sps30_cmd_ {
	GET_BOARD_ADR,
	SPS30_SENSOR_INFO,
	SPS30_SENSOR_INIT,
	SPS30_TRANSMIT_DATA,
	SPS30_START_MEAS = 0x0010,
	SPS30_STOP_MEAS = 0x0104,
	SPS30_RDY_FLAG = 0x0202,
	SPS30_READ_MEAS = 0x0300,
	SPS30_WAITING_FOR_CMD
} sps30_cmd_t;

typedef struct
{
	union
	{
		struct
		{
			float mass_pm1_0; // Float member of Mass Conc of PM1.0
			float mass_pm2_5; // Float member of Mass Conc of PM2.5
			float mass_pm4_0; // Float member of Mass Conc of PM4.0
			float mass_pm10_0; // Float member of Mass Conc of PM10
                              //
			float nmbr_pm0_5; // Float member of Number Conc PM0.5
			float nmbr_pm1_0; // Float member of Number Conc PM1.0
			float nmbr_pm2_5; // Float member of Number Conc PM2.5
			float nmbr_pm4_0; // Float member of Number Conc PM4.0
			float nmbr_pm10_0; // Float member of Number Conc PM10

			float typ_pm_size; // Float member of Typical Particle Size

			// uint16_t clean_interval;	/**< 16 bit word of Auto Clean Interval */
		} humanReadable;

		float raw_values[SPS30_NUM_READ_VALUES];
	};
} sps30_data_t;

// Function prototypes-------------------------------------------------------
/**
 * \brief Starting the measurement on the sensor.
 *
 * \return Error or no error value.
 */
extern uint8_t sps30StartMeasurement(void);

/**
 * \brief Stopping the measurement on the sensor.
 *
 * \return Error or no error value.
 */
extern uint8_t sps30StopMeasurement(void);

/**
 * \brief Read the data ready-flag.
 *
 * \return Error or no error value.
 */
extern uint8_t sps30ReadReadyFlag(void);

/**
 * \brief Read the measured data from the sensor.
 *
 * \param currentValues Pointer to the stored newest values.
 * \return Error or no error value.
 */
extern uint8_t sps30ReadMeasurement(sps30_data_t *currentValues);

/**
 * \brief Initialize the SPS30 sensor by initializing the i2c resources.
 *
 * @return Busy or not busy value.
 */
extern uint8_t sps30Init(void);

#endif /* SPS30_H_ */
