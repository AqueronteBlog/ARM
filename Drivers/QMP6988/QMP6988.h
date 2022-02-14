/**
 * @brief       QMP6988.h
 * @details     Digital Barometric Pressure Sensor.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        12/February/2022
 * @version     12/February/2022    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESSES
  */
typedef enum
{
    QMP6988_ADDRESS_SDO_HIGH    =   0x56,                		/*!<   QMP6988 I2C Address, SDO High           	*/
	QMP6988_ADDRESS_SDO_LOW     =   0x70                		/*!<   QMP6988 I2C Address, SDO Low           	*/
} QMP6988_addresses_t;




/**
  * @brief   COMMAND REGISTERS
  */
typedef enum
{
	QMP6988_TEMP_TXD0		=   0xFC,			/*!<  Temperature DATA[8:1] in 24bit		*/
    QMP6988_TEMP_TXD1     	=   0xFB,      		/*!<  Temperature DATA[16:9] in 24bit      	*/
    QMP6988_TEMP_TXD2   	=   0xFA,     		/*!<  Temperature DATA[24:17] in 24bit     	*/
    QMP6988_PRESS_TXD0		=   0xF9,        	/*!<  Pressure DATA[8:1] in 24bit          	*/
	QMP6988_PRESS_TXD1		=   0xF8,        	/*!<  Pressure DATA[16:9] in 24bit         	*/
	QMP6988_PRESS_TXD2		=   0xF7,        	/*!<  Pressure DATA[24:17] in 24bit        	*/
	QMP6988_IO_SETUP		=   0xF5,        	/*!<  Set-up		                    	*/
	QMP6988_CTRL_MEAS		=   0xF4,        	/*!<  Control		                    	*/
	QMP6988_DEVICE_STAT		=   0xF3,        	/*!<  Stat			                    	*/
	QMP6988_I2C_SET			=   0xF2,        	/*!<  Master code setting at I2C HS mode   	*/
	QMP6988_IIR_CNT			=   0xF1,        	/*!<  IIR filter co-efficient setting      	*/
	QMP6988_RESET			=   0xE0,        	/*!<  Soft reset	                    	*/
	QMP6988_CHIP_ID			=   0xD1,        	/*!<  CHIP_ID: 5D		                  	*/
	QMP6988_COE_B00_A0_EX	=   0xB8,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_A2_0		=   0xB7,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_A2_1		=   0xB6,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_A1_0		=   0xB5,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_A1_1		=   0xB4,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_A0_0		=   0xB3,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_A0_1		=   0xB2,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_BP3_0		=   0xB1,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_BP3_1		=   0xB0,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_B21_0		=   0xAF,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_B21_1		=   0xAE,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_B12_0		=   0xAD,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_B12_1		=   0xAC,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_BP2_0		=   0xAB,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_BP2_1		=   0xAA,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_B11_0		=   0xA9,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_B11_1		=   0xA8,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_BP1_0		=   0xA7,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_BP1_1		=   0xA6,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_BT2_0		=   0xA5,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_BT2_1		=   0xA4,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_BT1_0		=   0xA3,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_BT1_1		=   0xA2,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_B00_0		=   0xA1,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_B00_1		=   0xA0        	/*!<  Compensation Coefficient             	*/
} QMP6988_register_list_t;



// TRIGGER MESUREMENT
/**
  * @brief   DATA
  * 			NOTE: N/A
  */
typedef enum
{
    TRIGGER_MEASUREMENT_DATA_1	=   0x33,           /*!<  Data 1                       			*/
	TRIGGER_MEASUREMENT_DATA_2	=   0x00            /*!<  Data 2                    			*/
} QMP6988_trigger_measurement_t;



// STATUS
/**
  * @brief   BUS_INDICATION <7>
  * 			NOTE: N/A
  */
typedef enum
{
    STATUS_BUS_INDICATION_MASK	=   ( 1U << 7U ),	/*!<  BUS_INDICATION mask                	*/
    STATUS_BUS_INDICATION_BUSY	=   ( 1U << 7U ),	/*!<  Busy in measurement                	*/
	STATUS_BUS_INDICATION_FREE	=   ( 0U << 7U ) 	/*!<  Free in dormant state                	*/
} QMP6988_status_bus_indication_t;



/**
  * @brief   CAL <3>
  * 			NOTE: N/A
  */
typedef enum
{
    STATUS_CAL_MASK				=   ( 1U << 3U ),	/*!<  CAL mask                				*/
	STATUS_CAL_CALIBRATED    	=   ( 1U << 3U ),	/*!<  Calibrated					       	*/
	STATUS_CAL_UNCALIBRATED 	=   ( 0U << 3U ) 	/*!<  Uncalibrated			              	*/
} QMP6988_status_cal_t;



// INITIALIZATION
/**
  * @brief   INITIALIZATION
  * 			NOTE: N/A
  */
typedef enum
{
    INITIALIZATION_DATA_1		=   0x08,			/*!<  Data 1               					*/
    INITIALIZATION_DATA_2		=   0x00 			/*!<  Data 2                				*/
} QMP6988_initialization_t;






#ifndef QMP6988_VECTOR_STRUCT_H
#define QMP6988_VECTOR_STRUCT_H
/* Temperature data	*/
typedef struct
{
	uint32_t raw_temperature;						/*!<  Raw temperature data 					*/
	float	 temperature;							/*!<  Temperature          					*/
} QMP6988_temperature_data_t;


/* Humidity data	*/
typedef struct
{
	uint32_t raw_humidity;							/*!<  Raw humidity data 					*/
	float	 humidity;								/*!<  Humidity          					*/
} QMP6988_humidity_data_t;


/* User's variables	*/
typedef struct
{
	QMP6988_temperature_data_t	temperature;		/*!<  Temperature variables					*/
	QMP6988_humidity_data_t	    humidity;			/*!<  Humidity variables   					*/

    uint8_t  					state;				/*!<  State              					*/

    uint8_t  					crc;				/*!<  CRC	              					*/
} QMP6988_user_data_t;
#endif





/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    QMP6988_SUCCESS     =       0,
    QMP6988_FAILURE     =       1
} QMP6988_status_t;



/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C bus.
 */
QMP6988_status_t  QMP6988_Init               	( I2C_parameters_t myI2Cparameters 									);

/** It calibrates the device.
 */
QMP6988_status_t  QMP6988_Calibrate          	( I2C_parameters_t myI2Cparameters 									);

/** It performs a soft-reset.
 */
QMP6988_status_t  QMP6988_SoftReset          	( I2C_parameters_t myI2Cparameters 									);

/** It triggers a new measurement data (raw data).
 */
QMP6988_status_t  QMP6988_TriggerMeasurement	( I2C_parameters_t myI2Cparameters 									);

/** It triggers the state byte.
 */
QMP6988_status_t  QMP6988_TriggerStatus		    ( I2C_parameters_t myI2Cparameters					 				);

/** It gets the state byte.
 */
QMP6988_status_t  QMP6988_GetStatus		     	( I2C_parameters_t myI2Cparameters, uint8_t* myState 				);

/** It gets all the raw data.
 */
QMP6988_status_t  QMP6988_GetAllData	    	( I2C_parameters_t myI2Cparameters, QMP6988_user_data_t* myAllData	);

/** It processes the temperature data.
 */
float  QMP6988_ProcessTemperature 			( uint32_t myRawTemperature											);

/** It processes the humidity data.
 */
float  QMP6988_ProcessHumidity    			( uint32_t myRawHumidity 											);
