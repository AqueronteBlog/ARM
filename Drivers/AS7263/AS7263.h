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
} AS7263_command_register_format_t;



/**
  * @brief   CONFIGURATION REGISTER
 */
/* SENS <12>
 *    NOTE: Sensitivity.
 */
typedef enum
{
	ALS_CONF_SENS_MASK					=   ( 1UL << 12U ),			/*!<  SENS mask       	    			    	*/
	ALS_CONF_SENS_HIGH_SENSITIVITY		=   ( 0UL << 12U ),			/*!<  High sensitivity (1 x)					*/
	ALS_CONF_SENS_LOW_SENSITIVITY		=   ( 1UL << 12U ) 			/*!<  Low sensitivity (1/8 x)			 		*/
} AS7263_als_conf_sens_t;


/* DG <11>
 *    NOTE: Digital gain.
 */
typedef enum
{
	ALS_CONF_DG_MASK					=   ( 1UL << 11U ),			/*!<  DG mask       	    			    	*/
	ALS_CONF_DG_NORMAL					=   ( 0UL << 11U ),			/*!<  Normal									*/
	ALS_CONF_DG_DOUBLE					=   ( 1UL << 11U ) 			/*!<  Double							 		*/
} AS7263_als_conf_dg_t;


/* GAIN <10>
 *    NOTE: Gain.
 */
typedef enum
{
	ALS_CONF_GAIN_MASK					=   ( 1UL << 10U ),			/*!<  GAIN mask       	    			    	*/
	ALS_CONF_GAIN_NORMAL_SENSITIVITY	=   ( 0UL << 10U ),			/*!<  Normal sensitivity						*/
	ALS_CONF_GAIN_DOUBLE_SENSITIVITY	=   ( 1UL << 10U ) 			/*!<  Double sensitivity				 		*/
} AS7263_als_conf_gain_t;


/* ALS_IT <9:6>
 *    NOTE: ALS integration time setting which represents how long ALS can update the readout value.
 */
typedef enum
{
	ALS_CONF_ALS_IT_MASK					=   ( 0b1111 << 6U ),	/*!<  ALS_IT mask       	    			    */
	ALS_CONF_ALS_IT_25MS					=   ( 0b1100 << 6U ),	/*!<   25 ms	 								*/
	ALS_CONF_ALS_IT_50MS					=   ( 0b1000 << 6U ), 	/*!<   50 ms						 			*/
	ALS_CONF_ALS_IT_100MS					=   ( 0b0000 << 6U ), 	/*!<  100 ms						 			*/
	ALS_CONF_ALS_IT_200MS					=   ( 0b0001 << 6U ), 	/*!<  200 ms						 			*/
	ALS_CONF_ALS_IT_400MS					=   ( 0b0010 << 6U ), 	/*!<  400 ms						 			*/
	ALS_CONF_ALS_IT_800MS					=   ( 0b0011 << 6U )  	/*!<  800 ms						 			*/
} AS7263_als_conf_als_it_t;


/* ALS_PERS <5:4>
 *    NOTE: ALS interrupt persistence setting. The interrupt pin is triggered while sensor reading is out of threshold windows
 *    		after consecutive number of measurement cycle.
 */
typedef enum
{
	ALS_CONF_ALS_PERS_MASK					=   ( 0b11 << 4U ),		/*!<  ALS_PERS mask       	    			    */
	ALS_CONF_ALS_PERS_1	  					=   ( 0b00 << 4U ),		/*!<  ALS 1										*/
	ALS_CONF_ALS_PERS_2						=   ( 0b01 << 4U ), 	/*!<  ALS 2					 					*/
	ALS_CONF_ALS_PERS_4						=   ( 0b10 << 4U ), 	/*!<  ALS 4							 			*/
	ALS_CONF_ALS_PERS_8						=   ( 0b11 << 4U ) 		/*!<  ALS 8							 			*/
} AS7263_als_conf_als_pers_t;


/* INT_CHANNEL <3>
 *    NOTE: Selection for which channel the interrupt should trigger.
 */
typedef enum
{
	ALS_CONF_ALS_INT_CHANNEL_MASK			=   ( 1U << 3U ),		/*!<  ALS_INT_EN mask      	    			    */
	ALS_CONF_ALS_INT_CHANNEL_ALS_CHANNEL	=   ( 0U << 3U ),		/*!<  ALS CH interrupt							*/
	ALS_CONF_ALS_INT_CHANNEL_WHITE_CHANNEL	=   ( 1U << 3U )  		/*!<  WHITE CH interrupt	 					*/
} AS7263_als_conf_als_int_channel_t;


/* CHANNEL_EN <2>
 *    NOTE: Channel enable function.
 */
typedef enum
{
	ALS_CONF_ALS_CHANNEL_EN_MASK			=   ( 1U << 2U ),		/*!<  CHANNEL_EN mask  		    			    */
	ALS_CONF_ALS_CHANNEL_EN_ALS_CH_ONLY		=   ( 0U << 2U ),		/*!<  ALS CH enable only						*/
	ALS_CONF_ALS_CHANNEL_EN_ALS_WHITE_CH	=   ( 1U << 2U )  		/*!<  ALS and WHITE CH enable					*/
} AS7263_als_conf_als_channel_en_t;


/* INT_EN <1>
 *    NOTE: Interrupt enable setting.
 */
typedef enum
{
	ALS_CONF_ALS_INT_EN_MASK				=   ( 1U << 1U ),		/*!<  INT_EN mask  			    			    */
	ALS_CONF_ALS_INT_EN_INT_DISABLE			=   ( 0U << 1U ),		/*!<  INT disable								*/
	ALS_CONF_ALS_INT_EN_INT_ENABLE			=   ( 1U << 1U )  		/*!<  INT enable								*/
} AS7263_als_conf_als_int_en_t;


/* SD <0>
 *    NOTE: Shut down setting.
 */
typedef enum
{
	ALS_CONF_ALS_SD_MASK					=   ( 1U << 0U ),		/*!<  SD mask  				    			    */
	ALS_CONF_ALS_SD_POWER_ON				=   ( 0U << 0U ),		/*!<  Power on									*/
	ALS_CONF_ALS_SD_SHUTDOWN				=   ( 1U << 0U )  		/*!<  Shutdown									*/
} AS7263_als_conf_als_sd_t;



/**
  * @brief   POWER SAVING MODES
 */
/* PSM_WAIT <2:1>
 *    NOTE: Power saving mode; see table "Refresh time".
 */
typedef enum
{
	POWER_SAVING_PSM_WAIT_MASK				=   ( 0b11 << 1U ),		/*!<  PSM_WAIT mask       	    			    */
	POWER_SAVING_PSM_WAIT_0_4_S				=   ( 0b00 << 1U ),		/*!<  0.4 s										*/
	POWER_SAVING_PSM_WAIT_0_8_S				=   ( 0b01 << 1U ), 	/*!<  0.8 s						 				*/
	POWER_SAVING_PSM_WAIT_1_6_S				=   ( 0b10 << 1U ), 	/*!<  1.6 s					 					*/
	POWER_SAVING_PSM_WAIT_3_2_S				=   ( 0b11 << 1U ) 		/*!<  3.2 s							 			*/
} AS7263_power_saving_psm_wait_t;


/* PSM_EN <0>
 *    NOTE: Power saving mode; see table "Refresh time".
 */
typedef enum
{
	POWER_SAVING_PSM_EN_MASK				=   ( 1U << 0U ),		/*!<  PSM_EN mask  	     	    			    */
	POWER_SAVING_PSM_EN_DISABLE				=   ( 0U << 0U ),		/*!<  Disable									*/
	POWER_SAVING_PSM_EN_ENABLE				=   ( 1U << 0U )  		/*!<  Enable					 				*/
} AS7263_power_saving_psm_en_t;



/**
  * @brief   INTERRUPT STATUS
 */
/* INT_TH_LOW <15>
 *    NOTE: Read bit. Low threshold interrupt flag.
 */
typedef enum
{
	ALS_INT_INT_TH_LOW_MASK					=   ( 1U << 15U ),		/*!<  INT_TH_LOW mask  	   	    			    */
	ALS_INT_INT_TH_LOW_INT_NOT_TRIGGERED	=   ( 0U << 15U ),		/*!<  Interrupt not triggered					*/
	ALS_INT_INT_TH_LOW_INT_OCCURRED			=   ( 1U << 15U ) 		/*!<  Interrupt occurred			 			*/
} AS7263_als_int_int_th_low_t;


/* INT_TH_HIGH <14>
 *    NOTE: Read bit. High threshold interrupt flag.
 */
typedef enum
{
	ALS_INT_INT_TH_HIGH_MASK				=   ( 1U << 14U ),		/*!<  INT_TH_HIGH mask  		   			    */
	ALS_INT_INT_TH_HIGH_INT_NOT_TRIGGERED	=   ( 0U << 14U ),		/*!<  Interrupt not triggered					*/
	ALS_INT_INT_TH_HIGH_INT_OCCURRED		=   ( 1U << 14U ) 		/*!<  Interrupt occurred			 			*/
} AS7263_als_int_int_th_high_t;



/**
  * @brief   APPLICATION
 */
#define AS7263_MAXIMUM_RESOLUTION	(float)0.0004					/*!<  Maximum resolution    							*/




#ifndef AS7263_VECTOR_STRUCT_H
#define AS7263_VECTOR_STRUCT_H
/* Configuration register	 */
typedef struct
{
	AS7263_als_conf_sens_t			als_sens;			/*!< ALS Sensitivity selection										*/
	AS7263_als_conf_dg_t				als_dg;				/*!< ALS digital gain												*/
	AS7263_als_conf_gain_t			als_gain;			/*!< ALS gain														*/
	AS7263_als_conf_als_it_t			als_it;				/*!< ALS integration time											*/
	AS7263_als_conf_als_pers_t		als_pers;			/*!< ALS interrupt persistence setting								*/
	AS7263_als_conf_als_int_channel_t	als_int_channel;	/*!< ALS selection for which channel the interrupt should trigger	*/
	AS7263_als_conf_als_channel_en_t	als_channel_en;		/*!< ALS channel enable function									*/
	AS7263_als_conf_als_int_en_t		als_int_en;			/*!< ALS interrupt enable setting									*/
	AS7263_als_conf_als_sd_t			als_sd;				/*!< ALS Shut down setting											*/
} AS7263_configuration_register_t;



typedef struct
{
	/* Raw ALS high resolution output data	 */
	uint16_t als_high_resolution_output_data;				/*!< Raw ALS high resolution output data							*/

	/* Raw WHITE output data	 */
	uint16_t white_channel_output_data;						/*!< Raw WHITE channel output data									*/

	/* Raw threshold windows setting	 */
	uint16_t high_threshold_windows_setting;				/*!< Raw ALS high threshold window setting							*/
	uint16_t low_threshold_windows_setting;					/*!< Raw ALS low threshold window setting							*/

	/* Configuration register	 */
	AS7263_configuration_register_t	configuration;		/*!< Configuration parameters										*/

	/* Power saving modes	 */
	AS7263_power_saving_psm_wait_t	psm_wait;			/*!< Defines the wait time between the measurements					*/
	AS7263_power_saving_psm_en_t		psm_en;				/*!< Power saving mode enable setting								*/

	/* Interrupt status	 */
	AS7263_als_int_int_th_low_t		int_th_low;			/*!< Low threshold interrupt flag									*/
	AS7263_als_int_int_th_high_t		int_th_high;		/*!< High threshold interrupt flag									*/

	/* Application information	 */
	float	light_level;									/*!< Light level [lux]												*/
	float	resolution;										/*!< Resolution regarding the integration time and the gain			*/
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

/** It reads the configuration register.
  */
AS7263_status_t AS7263_GetConfigurationRegister	( I2C_parameters_t myI2Cparameters, AS7263_configuration_register_t* myConfReg	);

/** It writes the configuration register.
  */
AS7263_status_t AS7263_SetConfigurationRegister	( I2C_parameters_t myI2Cparameters, AS7263_configuration_register_t myConfReg		);

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


