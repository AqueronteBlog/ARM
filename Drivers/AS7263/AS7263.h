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
 * @pre         This code belongs to Nimbus Centre ( https://www.nimbus.cit.ie ).
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
	AS7263_ADDRESS			=   0b1001001   /*!<   Address		                	*/
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



/**
  * @brief   FIRMWARE VERSION
 */
/* MINOR_VERSION_1_0 <7:6>
 *    NOTE: Minor Version [1:0].
 */
typedef enum
{
	FW_VERSION_MINOR_VERSION_1_0_MASK	=   ( 0b11 << 6U )			/*!<  Minor Version [1:0]				    	*/
} AS7263_fw_version_minor_version_1_0;


/* SUB_VERSION <5:0>
 *    NOTE: Sub Version
 */
typedef enum
{
	FW_VERSION_SUB_VERSION_MASK			=   ( 0b111111 << 0U )		/*!<  Sub version	    			    		*/
} AS7263_fw_version_sub_version;


/* MAJOR_VERSION <7:4>
 *    NOTE: Major Version.
 */
typedef enum
{
	FW_VERSION_MAJOR_VERSION_MASK		=   ( 0b1111 << 4U )		/*!<  Major Version						    	*/
} AS7263_fw_version_major_version;


/* MINOR_VERSION_5_2 <3:0>
 *    NOTE: Minor Version [1:0].
 */
typedef enum
{
	FW_VERSION_MINOR_VERSION_5_2_MASK	=   ( 0b1111 << 0U )		/*!<  Minor Version [5:2]				    	*/
} AS7263_fw_version_minor_version_5_2;



/**
  * @brief   CONTROL SETUP
 */
/* RST <7>
 *    NOTE: Soft Reset, Set to 1 for soft reset, goes to 0 automatically after the reset.
 */
typedef enum
{
	CONTROL_SETUP_RST_MASK				=   ( 1U << 7U ),			/*!<  RST Mask							    	*/
	CONTROL_SETUP_RST_SOFTRESET			=   ( 1U << 7U ),			/*!<  Soft reset						    	*/
	CONTROL_SETUP_RST_NORMAL			=   ( 0U << 7U ) 			/*!<  Normal operation					    	*/
} AS7263_control_setup_rst;


/* INT <6>
 *    NOTE: Enable interrupt pin output (INT).
 */
typedef enum
{
	CONTROL_SETUP_INT_MASK				=   ( 1U << 6U ),			/*!<  INT Mask							    	*/
	CONTROL_SETUP_INT_ENABLE			=   ( 1U << 6U ),			/*!<  Pin interrupt enabled				    	*/
	CONTROL_SETUP_INT_DISABLE			=   ( 0U << 6U ) 			/*!<  Pin interrupt disabled 			    	*/
} AS7263_control_setup_int;


/* GAIN <5:4>
 *    NOTE: Sensor Channel Gain Setting (all channels).
 */
typedef enum
{
	CONTROL_SETUP_GAIN_MASK				=   ( 0b11 << 4U ),			/*!<  GAIN Mask							    	*/
	CONTROL_SETUP_GAIN_1X				=   ( 0b00 << 4U ),			/*!<  Gain: 1x						[Default]   */
	CONTROL_SETUP_GAIN_3_7X				=   ( 0b01 << 4U ),			/*!<  Gain: 3.7x						    	*/
	CONTROL_SETUP_GAIN_16X				=   ( 0b10 << 4U ),			/*!<  Gain: 16x							    	*/
	CONTROL_SETUP_GAIN_64X				=   ( 0b11 << 4U ) 			/*!<  Gain: 64x							    	*/
} AS7263_control_setup_gain;


/* BANK <3:2>
 *    NOTE: Data Conversion Type (continuous).
 */
typedef enum
{
	CONTROL_SETUP_BANK_MASK				=   ( 0b11 << 2U ),			/*!<  BANK Mask							    	*/
	CONTROL_SETUP_BANK_MODE_0			=   ( 0b00 << 2U ),			/*!<  Mode 0							    	*/
	CONTROL_SETUP_BANK_MODE_1			=   ( 0b01 << 2U ),			/*!<  Mode 1							    	*/
	CONTROL_SETUP_BANK_MODE_2			=   ( 0b10 << 2U ),			/*!<  Mode 2						[Default]   */
	CONTROL_SETUP_BANK_MODE_3			=   ( 0b11 << 2U ) 			/*!<  Mode 3: One-shot					    	*/
} AS7263_control_setup_bank;


/* DATA_RDY <1>
 *    NOTE: Data Ready to Read, sets INT active if interrupt is enabled. Can be polled if not using INT.
 */
typedef enum
{
	CONTROL_SETUP_DATA_RDY_MASK			=   ( 1U << 1U ),			/*!<  DATA_RDY Mask						    	*/
	CONTROL_SETUP_DATA_RDY_READY		=   ( 1U << 1U ),			/*!<  Data ready						    	*/
	CONTROL_SETUP_DATA_RDY_BUSY			=   ( 0U << 1U ) 			/*!<  Data no ready			 			    	*/
} AS7263_control_setup_data_rdy;



/**
  * @brief   LED CONTROL
 */
/* ICL_DRV <5:4>
 *    NOTE: LED_DRV current limit.
 */
typedef enum
{
	LED_CONTROL_ICL_DRV_MASK			=   ( 0b11 << 4U ),			/*!<  ICL_DRV Mask						    	*/
	LED_CONTROL_ICL_DRV_12_5_MA			=   ( 0b00 << 4U ),			/*!<  LED_DRV current limit: 12.5mA	[Default]   */
	LED_CONTROL_ICL_DRV_25_MA			=   ( 0b01 << 4U ),			/*!<  LED_DRV current limit: 25mA		    	*/
	LED_CONTROL_ICL_DRV_50_MA			=   ( 0b10 << 4U ),			/*!<  LED_DRV current limit: 50mA		    	*/
	LED_CONTROL_ICL_DRV_100_MA			=   ( 0b11 << 4U )			/*!<  LED_DRV current limit: 100mA		    	*/
} AS7263_led_control_icl_drv;


/* LED_DRV <3>
 *    NOTE: Enable LED_DRV.
 */
typedef enum
{
	LED_CONTROL_LED_DRV_MASK			=   ( 1U << 3U ),			/*!<  LED_DRV Mask						    	*/
	LED_CONTROL_LED_DRV_ENABLED			=   ( 1U << 3U ),			/*!<  LED_DRV enabled						    */
	LED_CONTROL_LED_DRV_DISABLED		=   ( 0U << 3U )			/*!<  LED_DRV disabled				[Default]   */
} AS7263_led_control_led_drv;


/* ICL_IND <2:1>
 *    NOTE: LED_IND current limit.
 */
typedef enum
{
	LED_CONTROL_ICL_IND_MASK			=   ( 0b11 << 1U ),			/*!<  ICL_IND Mask						    	*/
	LED_CONTROL_ICL_IND_1_MA			=   ( 0b00 << 1U ),			/*!<  LED_IND current limit: 1mA	[Default]   */
	LED_CONTROL_ICL_IND_2_MA			=   ( 0b01 << 1U ),			/*!<  LED_IND current limit: 2mA		    	*/
	LED_CONTROL_ICL_IND_4_MA			=   ( 0b10 << 1U ),			/*!<  LED_IND current limit: 4mA		    	*/
	LED_CONTROL_ICL_IND_8_MA			=   ( 0b11 << 1U )			/*!<  LED_IND current limit: 8mA		    	*/
} AS7263_led_control_icl_ind;


/* LED_IND <0>
 *    NOTE: Enable LED_IND.
 */
typedef enum
{
	LED_CONTROL_LED_IND_MASK			=   ( 1U << 0U ),			/*!<  LED_IND Mask						    	*/
	LED_CONTROL_LED_IND_ENABLED			=   ( 1U << 0U ),			/*!<  LED_IND enabled						    */
	LED_CONTROL_LED_IND_DISABLED		=   ( 0U << 0U )			/*!<  LED_IND disabled				[Default]   */
} AS7263_led_control_led_ind;





#ifndef AS7263_VECTOR_STRUCT_H
#define AS7263_VECTOR_STRUCT_H
/* Hardware version	 */
typedef struct
{
	uint8_t device_type;				/*!< Hardware: Device type number									*/
	uint8_t hw_version;					/*!< Hardware: Hardware version										*/
} AS7263_hw_version;


/* Firmware version	 */
typedef struct
{
	uint8_t minor_version;				/*!< Firmware: Minor version										*/
	uint8_t major_version;				/*!< Firmware: Major version										*/
	uint8_t subversion;					/*!< Firmware: Subversion											*/
} AS7263_fw_version;


/* USER: User´s global variables	 */
typedef struct
{
	/* Raw ALS high resolution output data	 */
	uint16_t als_high_resolution_output_data;				/*!< Raw ALS high resolution output data							*/

	/* Raw WHITE output data	 */
	uint16_t white_channel_output_data;						/*!< Raw WHITE channel output data									*/

	/* Hardware version	 */
	AS7263_hw_version hw_version;							/*!< Hardware parameters											*/

	/* Firmware version	 */
	AS7263_fw_version fw_version;							/*!< Firmware parameters											*/
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


