/**
 * @brief       AS7263.h
 * @details     6-Channel NIR Spectral_ID Device with Electronic Shutter and Smart Interface.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        01/April/2020
 * @version     01/April/2020    The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "math.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESS
  */
typedef enum
{
	AS7263_ADDRESS			=   0b1001001      /*!<   Address		                */
} AS7263_addresses_t;



/**
  * @brief   COMMAND REGISTER FORMAT
  */
typedef enum
{
  AS7263_HW_VERSION    		=   0x00,		/*!<  Hardware version					*/
  AS7263_FW_VERSION		    =   0x02,   	/*!<  Firmware version					*/
  AS7263_CONTROL_SETUP     	=   0x04,   	/*!<  Control setup						*/
  AS7263_INT_T			    =   0x05,   	/*!<  Integration time				    */
  AS7263_DEVICE_TEMP    	=   0x06,   	/*!<  Device temperature				*/
  AS7263_LED_CONTROL		=   0x07,   	/*!<  LED control						*/
  AS7263_R_HIGH			 	=   0x08,   	/*!<  Channel R High Data Byte			*/
  AS7263_R_LOW			 	=   0x09,   	/*!<  Channel R Low Data Byte			*/
  AS7263_S_HIGH			 	=   0x0A,   	/*!<  Channel S high Data Byte			*/
  AS7263_S_LOW			 	=   0x0B,   	/*!<  Channel S low Data Byte			*/
  AS7263_T_HIGH			 	=   0x0C,   	/*!<  Channel T high Data Byte			*/
  AS7263_T_LOW			 	=   0x0D,   	/*!<  Channel T low Data Byte			*/
  AS7263_U_HIGH			 	=   0x0E,   	/*!<  Channel U high Data Byte			*/
  AS7263_U_LOW			 	=   0x0F,   	/*!<  Channel U low Data Byte			*/
  AS7263_V_HIGH			 	=   0x10,   	/*!<  Channel V high Data Byte			*/
  AS7263_V_LOW			 	=   0x11,   	/*!<  Channel V low Data Byte			*/
  AS7263_W_HIGH			 	=   0x12,   	/*!<  Channel W high Data Byte			*/
  AS7263_W_LOW			 	=   0x13,   	/*!<  Channel W low Data Byte			*/
  AS7263_R_CAL			 	=   0x14,   	/*!<  Channel R Calibrated Data			*/
  AS7263_S_CAL			 	=   0x18,   	/*!<  Channel S Calibrated Data			*/
  AS7263_T_CAL			 	=   0x1C,   	/*!<  Channel T Calibrated Data			*/
  AS7263_U_CAL			 	=   0x20,   	/*!<  Channel U Calibrated Data			*/
  AS7263_V_CAL			 	=   0x24,   	/*!<  Channel V Calibrated Data			*/
  AS7263_W_CAL			 	=   0x28    	/*!<  Channel W Calibrated Data			*/
} AS7263_command_register_set_t;



/**
  * @brief   HARDWARE VERSION
 */
/* DEVICE_TYPE <7:0>
 *    NOTE: Device type number.
 */
typedef enum
{
	HW_VERSION_DEVICE_TYPE			=   0b0100000					/*!<  Device type number    			    	*/
} AS7263_hw_version_device_type;


/* HW_VERSION <7:0>
 *    NOTE: Hardware version.
 */
typedef enum
{
	HW_VERSION_HW_VERSION			=   0b00111111					/*!<  Hardware version	    			    	*/
} AS7263_hw_version_hw_version;







#ifndef AS7263_VECTOR_STRUCT_H
#define AS7263_VECTOR_STRUCT_H
typedef struct
{
	/* Raw ALS high resolution output data	 */
	uint16_t als_high_resolution_output_data;				/*!< Raw ALS high resolution output data							*/

	/* Raw WHITE output data	 */
	uint16_t white_channel_output_data;						/*!< Raw WHITE channel output data									*/

	/* Raw threshold windows setting	 */
	uint16_t high_threshold_windows_setting;				/*!< Raw ALS high threshold window setting							*/
	uint16_t low_threshold_windows_setting;					/*!< Raw ALS low threshold window setting							*/
} AS7263_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    AS7263_SUCCESS     =       0,
    AS7263_FAILURE     =       1
} AS7263_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
AS7263_status_t AS7263_Init               		( I2C_parameters_t myI2Cparameters                              					);

/** It sets the sensitivity value.
  */
AS7263_status_t AS7263_SetSensitivity			( I2C_parameters_t myI2Cparameters, AS7263_data_t mySENS							);

/** It gets the sensitivity value.
  */
AS7263_status_t AS7263_GetSensitivity			( I2C_parameters_t myI2Cparameters, AS7263_data_t* mySENS							);

/** It sets the DG value.
  */
AS7263_status_t AS7263_SetDG					( I2C_parameters_t myI2Cparameters, AS7263_data_t myDG							);

/** It gets the DG value.
  */
AS7263_status_t AS7263_GetDG					( I2C_parameters_t myI2Cparameters, AS7263_data_t* myDG							);

/** It sets the gain value.
  */
AS7263_status_t AS7263_SetGain					( I2C_parameters_t myI2Cparameters, AS7263_data_t myGain							);

/** It gets the gain value.
  */
AS7263_status_t AS7263_GetGain					( I2C_parameters_t myI2Cparameters, AS7263_data_t* myGain							);

/** It sets the integration time value.
  */
AS7263_status_t AS7263_SetIntegrationTime		( I2C_parameters_t myI2Cparameters, AS7263_data_t myALS_IT						);

/** It gets the integration time value.
  */
AS7263_status_t AS7263_GetIntegrationTime		( I2C_parameters_t myI2Cparameters, AS7263_data_t* myALS_IT						);

/** It sets the interrupt persistence value.
  */
AS7263_status_t AS7263_SetInterruptPersistence	( I2C_parameters_t myI2Cparameters, AS7263_data_t myALS_PERS						);

/** It gets the interrupt persistence value.
  */
AS7263_status_t AS7263_GetInterruptPersistence	( I2C_parameters_t myI2Cparameters, AS7263_data_t* myALS_PERS						);

/** It sets the channel interrupt value.
  */
AS7263_status_t AS7263_SetChannelInterrupt		( I2C_parameters_t myI2Cparameters, AS7263_data_t myINT_CHANNEL					);

/** It gets the channel interrupt value.
  */
AS7263_status_t AS7263_GetChannelInterrupt		( I2C_parameters_t myI2Cparameters, AS7263_data_t* myINT_CHANNEL					);

/** It sets the channel enable value.
  */
AS7263_status_t AS7263_SetChannelEnable			( I2C_parameters_t myI2Cparameters, AS7263_data_t myCHANNEL_EN					);

/** It gets the channel enable value.
  */
AS7263_status_t AS7263_GetChannelEnable			( I2C_parameters_t myI2Cparameters, AS7263_data_t* myCHANNEL_EN					);

/** It sets the interrupt enable value.
  */
AS7263_status_t AS7263_SetInterruptEnable		( I2C_parameters_t myI2Cparameters, AS7263_data_t myINT_EN						);

/** It gets the interrupt enable value.
  */
AS7263_status_t AS7263_GetInterruptEnable		( I2C_parameters_t myI2Cparameters, AS7263_data_t* myINT_EN						);

/** It sets the shutdown mode.
  */
AS7263_status_t AS7263_SetShutDownMode			( I2C_parameters_t myI2Cparameters, AS7263_data_t mySD							);

/** It gets the shutdown mode.
  */
AS7263_status_t AS7263_GetShutDownMode			( I2C_parameters_t myI2Cparameters, AS7263_data_t* mySD							);

/** It sets the high threshold value.
  */
AS7263_status_t AS7263_SetHighThreshold			( I2C_parameters_t myI2Cparameters, AS7263_data_t myHighThreshold					);

/** It gets the high threshold value.
  */
AS7263_status_t AS7263_GetHighThreshold			( I2C_parameters_t myI2Cparameters, AS7263_data_t* myHighThreshold				);

/** It sets the low threshold value.
  */
AS7263_status_t AS7263_SetLowThreshold			( I2C_parameters_t myI2Cparameters, AS7263_data_t myLowThreshold					);

/** It gets the low threshold value.
  */
AS7263_status_t AS7263_GetLowThreshold			( I2C_parameters_t myI2Cparameters, AS7263_data_t* myLowThreshold					);

/** It sets the power safe mode register.
  */
AS7263_status_t AS7263_SetPowerSafeMode			( I2C_parameters_t myI2Cparameters, AS7263_data_t myPowerSafeMode					);

/** It gets the power safe mode register.
  */
AS7263_status_t AS7263_GetPowerSafeMode			( I2C_parameters_t myI2Cparameters, AS7263_data_t* myPowerSafeMode				);

/** It gets the ALS high resolution output data ( raw data ).
  */
AS7263_status_t AS7263_GetALS_HighResOutputData	( I2C_parameters_t myI2Cparameters, AS7263_data_t* myALS							);

/** It gets the white channel output data ( raw data ).
  */
AS7263_status_t AS7263_GetWhiteChannelOutputData( I2C_parameters_t myI2Cparameters, AS7263_data_t* myWhite						);

/** It gets the interrupt status.
  */
AS7263_status_t AS7263_GetInterruptStatus		( I2C_parameters_t myI2Cparameters, AS7263_data_t* myIF							);

/** It calculates the lux level and the current resolution.
  */
void AS7263_CalculateLuxLevel						( AS7263_data_t* myLux															);


