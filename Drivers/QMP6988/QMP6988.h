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
  * @brief   DEFAULT ADDRESS
  */
typedef enum
{
    QMP6988_ADDRESS     =   0x38                		/*!<   QMP6988 I2C Address                  	*/
} QMP6988_address_t;




/**
  * @brief   COMMAND REGISTERS
  */
typedef enum
{
    QMP6988_TRIGGER_MEASUREMENT	=   0xAC,			/*!<  Trigger measurement command			*/
    QMP6988_STATUS         		=   0x71,      		/*!<  Status command                       	*/
    QMP6988_INITIALIZATION   		=   0xBE,     		/*!<  Initialization                    	*/
    QMP6988_SOFTRESET      		=   0xBA         	/*!<  Soft reset	                    	*/
} QMP6988_basic_commands_t;



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
