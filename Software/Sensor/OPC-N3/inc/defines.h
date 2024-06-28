/*
 * defines.h
 *
 *  Created on: 12.08.2019
 *      Author: floriansommer
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#define MAXSIZE					170
#define READING 				10
#define OPC_N3_WAIT_CMD_MS		200
#define OPC_N3_WAIT_CMD_LONG_MS 600
#define OPC_N3_WAIT_HIST_MS		750
#define OPC_N3_WAIT_FAN_MS		5000

#define SENSOR_INFO_STRING_LENGTH 32

#define GET_SENSOR_INFO						0
#define INIT_SENSOR_AND_START_MEASURING		1
#define SENSOR_MEASURING					2
#define TRANSMITT_DATA_TO_MAINBOARD			3
#define STOP_MEASURING						4
#define WAITING_FOR_COMMAND					5
#define TESTMODE 							6

#define SIZEOF_INFO_STRING					60


//defines for SPI-Communication
#define DEL_TIMEOUT	 50			//spi timeout in ms
#define MAX_TRIES 	 5			//max tries for sending one instruction

//number of instruction bytes to be sent for SPI-Communication with OPC-N3
#define NUM_IBY_WRITE_PERIPHERAL_POWER_STATUS 	3
#define NUM_IBY_READ_DAC_AND_POWER_STATUS 		8
//#define NUM_IBY_SET_FAN_OR_LASER_DIGITAL_POT 	4 	//should not be changed because of calibration
//#define NUM_IBY_SET_BIN_WEIGHTING_INDEX 		3 	//should not be changed because of calibration
#define NUM_IBY_READ_INFORMATION_STRING			62
#define NUM_IBY_READ_SERIAL_NUMBER 				62
#define NUM_IBY_READ_CONFIGURATION_VARIABLES 	170
//#define NUM_IBY_WRITE_CONFIGURATION_VARIABLES 169 //should not be changed because of calibration
#define NUM_IBY_READ_HISTOGRAM_DATA 			88
#define NUM_IBY_READ_PM_DATA 					16
#define NUM_IBY_CHECK_STATUS 					2
#define NUM_IBY_RESET 							2

//command bytes of OPC-N3 as defined in datasheet
#define CMD_WRITE_PERIPHERAL_POWER_STATUS   0x03U
#define CMD_READ_DAC_AND_POWER_STATUS    	0x13U
//define cmd_Set_Fan_or_Laser_digital_pot   0x42U //should not be modified because of calibration
//define cmd_Set_Bin_Weighting_Index		0x05U //should not be modified because of calibratioon
#define CMD_READ_INFORMATION_STRING  		0x3FU
#define CMD_READ_SERIALNUMBER_STRING 		0x10U
#define CMD_READ_CONFIGURATION_VARIABLES	0x3CU
//#define cmd_Write_Configuration_Variables	0x3AU //should not be modified because of calibration
#define CMD_READ_HISTOGRAM_DATA				0x30U
#define CMD_READ_PM_DATA					0x32U
#define CMD_CHECK_STATUS					0xCFU
#define CMD_RESET							0x06U

#define POWER_FAN_OFF						0x02
#define POWER_FAN_ON						0x03


//defines for UART-Communication
#define JSON_TIMEOUT						150
#define BAUDRATE_UART	115200
#define UART_RECEIVE_MAX_LENGTH		35		//number of inst bytes sent by mainboard
#define ADDRESS_UART	12		//position of address in uart receive buffer
#define INST_UART		27		//position of instruction in uart recieve buffer
#define CHAR_OFFSET		48		//offset for numbers in ascii char format

#define NUM_DIGITS 10
#define BINS 24
#define NOD 27
#define LENGTH_VALUE_STRING 18

#define MAX_NUM_FAIL_DATA_REQ	5




#endif /* DEFINES_H_ */
