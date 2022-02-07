/**
 * @brief       AHT20.h
 * @details     Humidity and Temperature Sensor.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        31/January/2022
 * @version     31/January/2022    The ORIGIN
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
    AHT20_ADDRESS     =   0x38                		/*!<   AHT20 I2C Address                  	*/
} AHT20_address_t;




/**
  * @brief   COMMAND REGISTERS
  */
typedef enum
{
    AHT20_TRIGGER_MEASUREMENT	=   0xAC,			/*!<  Trigger measurement command			*/
    AHT20_STATUS         		=   0x71,      		/*!<  Status command                       	*/
    AHT20_INITIALIZATION   		=   0xBE,     		/*!<  Initialization                    	*/
    AHT20_SOFTRESET      		=   0xBA         	/*!<  Soft reset	                    	*/
} AHT20_basic_commands_t;



// TRIGGER MESUREMENT
/**
  * @brief   DATA
  * 			NOTE: N/A
  */
typedef enum
{
    TRIGGER_MEASUREMENT_DATA_1	=   0x33,           /*!<  Data 1                       			*/
	TRIGGER_MEASUREMENT_DATA_2	=   0x00            /*!<  Data 2                    			*/
} AHT20_trigger_measurement_t;



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
} AHT20_status_bus_indication_t;



/**
  * @brief   CAL <3>
  * 			NOTE: N/A
  */
typedef enum
{
    STATUS_CAL_MASK				=   ( 1U << 3U ),	/*!<  CAL mask                				*/
	STATUS_CAL_CALIBRATED    	=   ( 1U << 3U ),	/*!<  Calibrated					       	*/
	STATUS_CAL_UNCALIBRATED 	=   ( 0U << 3U ) 	/*!<  Uncalibrated			              	*/
} AHT20_status_cal_t;



// INITIALIZATION
/**
  * @brief   INITIALIZATION
  * 			NOTE: N/A
  */
typedef enum
{
    INITIALIZATION_DATA_1		=   0x08,			/*!<  Data 1               					*/
    INITIALIZATION_DATA_2		=   0x00 			/*!<  Data 2                				*/
} AHT20_initialization_t;






#ifndef AHT20_VECTOR_STRUCT_H
#define AHT20_VECTOR_STRUCT_H
/* Temperature data	*/
typedef struct
{
	uint32_t raw_temperature;						/*!<  Raw temperature data 					*/
	float	 temperature;							/*!<  Temperature          					*/
} AHT20_temperature_data_t;


/* Humidity data	*/
typedef struct
{
	uint32_t raw_humidity;							/*!<  Raw humidity data 					*/
	float	 humidity;								/*!<  Humidity          					*/
} AHT20_humidity_data_t;


/* User's variables	*/
typedef struct
{
	AHT20_temperature_data_t	temperature;		/*!<  Temperature variables					*/
	AHT20_humidity_data_t	    humidity;			/*!<  Humidity variables   					*/

    uint8_t  					state;				/*!<  State              					*/

    uint8_t  					crc;				/*!<  CRC	              					*/
} AHT20_user_data_t;
#endif





/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    AHT20_SUCCESS     =       0,
    AHT20_FAILURE     =       1
} AHT20_status_t;



/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C bus.
 */
AHT20_status_t  AHT20_Init               	( I2C_parameters_t myI2Cparameters 									);

/** It calibrates the device.
 */
AHT20_status_t  AHT20_Calibrate          	( I2C_parameters_t myI2Cparameters 									);

/** It performs a soft-reset.
 */
AHT20_status_t  AHT20_SoftReset          	( I2C_parameters_t myI2Cparameters 									);

/** It triggers a new measurement data (raw data).
 */
AHT20_status_t  AHT20_TriggerMeasurement	( I2C_parameters_t myI2Cparameters 									);

/** It triggers the state byte.
 */
AHT20_status_t  AHT20_TriggerStatus		    ( I2C_parameters_t myI2Cparameters					 				);

/** It gets the state byte.
 */
AHT20_status_t  AHT20_GetStatus		     	( I2C_parameters_t myI2Cparameters, uint8_t* myState 				);

/** It gets all the raw data.
 */
AHT20_status_t  AHT20_GetAllData	    	( I2C_parameters_t myI2Cparameters, AHT20_user_data_t* myAllData	);

/** It processes the temperature data.
 */
float  AHT20_ProcessTemperature 			( uint32_t myRawTemperature											);

/** It processes the humidity data.
 */
float  AHT20_ProcessHumidity    			( uint32_t myRawHumidity 											);
