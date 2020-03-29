/**
 * @brief       VEML6035.h
 * @details     Low Power, High Sensitivity, I2C Ambient Light Sensor.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/March/2020
 * @version     17/March/2020    The ORIGIN
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
	VEML6035_ADDRESS			=   0b0101001      /*!<   Address		                   	*/
} VEML6035_addresses_t;



/**
  * @brief   COMMAND REGISTER FORMAT
  */
typedef enum
{
  VEML6035_ALS_CONF     		=   0x00,	/*!<  ALS gain, integration time, interrupt, and shut down	*/
  VEML6035_ALS_WH			    =   0x01,   /*!<  High Threshold Windows Setting						*/
  VEML6035_ALS_WL		      	=   0x02,   /*!<  Low Threshold Windows Setting							*/
  VEML6035_POWER_SAVING		    =   0x03,   /*!<  Power Saving Mode: PSM		    					*/
  VEML6035_ALS			    	=   0x04,   /*!<  ALS High Resolution Output Data   					*/
  VEML6035_WHITE				=   0x05,   /*!<  White Channel Output Data								*/
  VEML6035_ALS_INT			 	=   0x06    /*!<  Crossing threshold INT trigger event		    		*/
} VEML6035_command_register_format_t;



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
} VEML6035_als_conf_sens_t;


/* DG <11>
 *    NOTE: Digital gain.
 */
typedef enum
{
	ALS_CONF_DG_MASK					=   ( 1UL << 11U ),			/*!<  DG mask       	    			    	*/
	ALS_CONF_DG_NORMAL					=   ( 0UL << 11U ),			/*!<  Normal									*/
	ALS_CONF_DG_DOUBLE					=   ( 1UL << 11U ) 			/*!<  Double							 		*/
} VEML6035_als_conf_dg_t;


/* GAIN <10>
 *    NOTE: Gain.
 */
typedef enum
{
	ALS_CONF_GAIN_MASK					=   ( 1UL << 10U ),			/*!<  GAIN mask       	    			    	*/
	ALS_CONF_GAIN_NORMAL_SENSITIVITY	=   ( 0UL << 10U ),			/*!<  Normal sensitivity						*/
	ALS_CONF_GAIN_DOUBLE_SENSITIVITY	=   ( 1UL << 10U ) 			/*!<  Double sensitivity				 		*/
} VEML6035_als_conf_gain_t;


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
} VEML6035_als_conf_als_it_t;


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
} VEML6035_als_conf_als_pers_t;


/* INT_CHANNEL <3>
 *    NOTE: Selection for which channel the interrupt should trigger.
 */
typedef enum
{
	ALS_CONF_ALS_INT_CHANNEL_MASK			=   ( 1U << 3U ),		/*!<  ALS_INT_EN mask      	    			    */
	ALS_CONF_ALS_INT_CHANNEL_ALS_CHANNEL	=   ( 0U << 3U ),		/*!<  ALS CH interrupt							*/
	ALS_CONF_ALS_INT_CHANNEL_WHITE_CHANNEL	=   ( 1U << 3U )  		/*!<  WHITE CH interrupt	 					*/
} VEML6035_als_conf_als_int_channel_t;


/* CHANNEL_EN <2>
 *    NOTE: Channel enable function.
 */
typedef enum
{
	ALS_CONF_ALS_CHANNEL_EN_MASK			=   ( 1U << 2U ),		/*!<  CHANNEL_EN mask  		    			    */
	ALS_CONF_ALS_CHANNEL_EN_ALS_CH_ONLY		=   ( 0U << 2U ),		/*!<  ALS CH enable only						*/
	ALS_CONF_ALS_CHANNEL_EN_ALS_WHITE_CH	=   ( 1U << 2U )  		/*!<  ALS and WHITE CH enable					*/
} VEML6035_als_conf_als_channel_en_t;


/* INT_EN <1>
 *    NOTE: Interrupt enable setting.
 */
typedef enum
{
	ALS_CONF_ALS_INT_EN_MASK				=   ( 1U << 1U ),		/*!<  INT_EN mask  			    			    */
	ALS_CONF_ALS_INT_EN_INT_DISABLE			=   ( 0U << 1U ),		/*!<  INT disable								*/
	ALS_CONF_ALS_INT_EN_INT_ENABLE			=   ( 1U << 1U )  		/*!<  INT enable								*/
} VEML6035_als_conf_als_int_en_t;


/* SD <0>
 *    NOTE: Shut down setting.
 */
typedef enum
{
	ALS_CONF_ALS_SD_MASK					=   ( 1U << 0U ),		/*!<  SD mask  				    			    */
	ALS_CONF_ALS_SD_POWER_ON				=   ( 0U << 0U ),		/*!<  Power on									*/
	ALS_CONF_ALS_SD_SHUTDOWN				=   ( 1U << 0U )  		/*!<  Shutdown									*/
} VEML6035_als_conf_als_sd_t;



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
} VEML6035_power_saving_psm_wait_t;


/* PSM_EN <0>
 *    NOTE: Power saving mode; see table "Refresh time".
 */
typedef enum
{
	POWER_SAVING_PSM_EN_MASK				=   ( 1U << 0U ),		/*!<  PSM_EN mask  	     	    			    */
	POWER_SAVING_PSM_EN_DISABLE				=   ( 0U << 0U ),		/*!<  Disable									*/
	POWER_SAVING_PSM_EN_ENABLE				=   ( 1U << 0U )  		/*!<  Enable					 				*/
} VEML6035_power_saving_psm_en_t;



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
} VEML6035_als_int_int_th_low_t;


/* INT_TH_HIGH <14>
 *    NOTE: Read bit. High threshold interrupt flag.
 */
typedef enum
{
	ALS_INT_INT_TH_HIGH_MASK				=   ( 1U << 14U ),		/*!<  INT_TH_HIGH mask  		   			    */
	ALS_INT_INT_TH_HIGH_INT_NOT_TRIGGERED	=   ( 0U << 14U ),		/*!<  Interrupt not triggered					*/
	ALS_INT_INT_TH_HIGH_INT_OCCURRED		=   ( 1U << 14U ) 		/*!<  Interrupt occurred			 			*/
} VEML6035_als_int_int_th_high_t;



/**
  * @brief   APPLICATION
 */
#define VEML6035_MAXIMUM_RESOLUTION	(float)0.0004					/*!<  Maximum resolution    							*/




#ifndef VEML6035_VECTOR_STRUCT_H
#define VEML6035_VECTOR_STRUCT_H
/* Configuration register	 */
typedef struct
{
	VEML6035_als_conf_sens_t			als_sens;			/*!< ALS Sensitivity selection										*/
	VEML6035_als_conf_dg_t				als_dg;				/*!< ALS digital gain												*/
	VEML6035_als_conf_gain_t			als_gain;			/*!< ALS gain														*/
	VEML6035_als_conf_als_it_t			als_it;				/*!< ALS integration time											*/
	VEML6035_als_conf_als_pers_t		als_pers;			/*!< ALS interrupt persistence setting								*/
	VEML6035_als_conf_als_int_channel_t	als_int_channel;	/*!< ALS selection for which channel the interrupt should trigger	*/
	VEML6035_als_conf_als_channel_en_t	als_channel_en;		/*!< ALS channel enable function									*/
	VEML6035_als_conf_als_int_en_t		als_int_en;			/*!< ALS interrupt enable setting									*/
	VEML6035_als_conf_als_sd_t			als_sd;				/*!< ALS Shut down setting											*/
} VEML6035_configuration_register_t;



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
	VEML6035_configuration_register_t	configuration;		/*!< Configuration parameters										*/

	/* Power saving modes	 */
	VEML6035_power_saving_psm_wait_t	psm_wait;			/*!< Defines the wait time between the measurements					*/
	VEML6035_power_saving_psm_en_t		psm_en;				/*!< Power saving mode enable setting								*/

	/* Interrupt status	 */
	VEML6035_als_int_int_th_low_t		int_th_low;			/*!< Low threshold interrupt flag									*/
	VEML6035_als_int_int_th_high_t		int_th_high;		/*!< High threshold interrupt flag									*/

	/* Application information	 */
	float	light_level;									/*!< Light level [lux]												*/
	float	resolution;										/*!< Resolution regarding the integration time and the gain			*/
} VEML6035_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    VEML6035_SUCCESS     =       0,
    VEML6035_FAILURE     =       1
} VEML6035_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
VEML6035_status_t VEML6035_Init               		( I2C_parameters_t myI2Cparameters                              					);

/** It reads the configuration register.
  */
VEML6035_status_t VEML6035_GetConfigurationRegister	( I2C_parameters_t myI2Cparameters, VEML6035_configuration_register_t* myConfReg	);

/** It writes the configuration register.
  */
VEML6035_status_t VEML6035_SetConfigurationRegister	( I2C_parameters_t myI2Cparameters, VEML6035_configuration_register_t myConfReg		);

/** It sets the sensitivity value.
  */
VEML6035_status_t VEML6035_SetSensitivity			( I2C_parameters_t myI2Cparameters, VEML6035_data_t mySENS							);

/** It gets the sensitivity value.
  */
VEML6035_status_t VEML6035_GetSensitivity			( I2C_parameters_t myI2Cparameters, VEML6035_data_t* mySENS							);

/** It sets the DG value.
  */
VEML6035_status_t VEML6035_SetDG					( I2C_parameters_t myI2Cparameters, VEML6035_data_t myDG							);

/** It gets the DG value.
  */
VEML6035_status_t VEML6035_GetDG					( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myDG							);

/** It sets the gain value.
  */
VEML6035_status_t VEML6035_SetGain					( I2C_parameters_t myI2Cparameters, VEML6035_data_t myGain							);

/** It gets the gain value.
  */
VEML6035_status_t VEML6035_GetGain					( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myGain							);

/** It sets the integration time value.
  */
VEML6035_status_t VEML6035_SetIntegrationTime		( I2C_parameters_t myI2Cparameters, VEML6035_data_t myALS_IT						);

/** It gets the integration time value.
  */
VEML6035_status_t VEML6035_GetIntegrationTime		( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myALS_IT						);

/** It sets the interrupt persistence value.
  */
VEML6035_status_t VEML6035_SetInterruptPersistence	( I2C_parameters_t myI2Cparameters, VEML6035_data_t myALS_PERS						);

/** It gets the interrupt persistence value.
  */
VEML6035_status_t VEML6035_GetInterruptPersistence	( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myALS_PERS						);

/** It sets the channel interrupt value.
  */
VEML6035_status_t VEML6035_SetChannelInterrupt		( I2C_parameters_t myI2Cparameters, VEML6035_data_t myINT_CHANNEL					);

/** It gets the channel interrupt value.
  */
VEML6035_status_t VEML6035_GetChannelInterrupt		( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myINT_CHANNEL					);

/** It sets the channel enable value.
  */
VEML6035_status_t VEML6035_SetChannelEnable			( I2C_parameters_t myI2Cparameters, VEML6035_data_t myCHANNEL_EN					);

/** It gets the channel enable value.
  */
VEML6035_status_t VEML6035_GetChannelEnable			( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myCHANNEL_EN					);

/** It sets the interrupt enable value.
  */
VEML6035_status_t VEML6035_SetInterruptEnable		( I2C_parameters_t myI2Cparameters, VEML6035_data_t myINT_EN						);

/** It gets the interrupt enable value.
  */
VEML6035_status_t VEML6035_GetInterruptEnable		( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myINT_EN						);

/** It sets the shutdown mode.
  */
VEML6035_status_t VEML6035_SetShutDownMode			( I2C_parameters_t myI2Cparameters, VEML6035_data_t mySD							);

/** It gets the shutdown mode.
  */
VEML6035_status_t VEML6035_GetShutDownMode			( I2C_parameters_t myI2Cparameters, VEML6035_data_t* mySD							);

/** It sets the high threshold value.
  */
VEML6035_status_t VEML6035_SetHighThreshold			( I2C_parameters_t myI2Cparameters, VEML6035_data_t myHighThreshold					);

/** It gets the high threshold value.
  */
VEML6035_status_t VEML6035_GetHighThreshold			( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myHighThreshold				);

/** It sets the low threshold value.
  */
VEML6035_status_t VEML6035_SetLowThreshold			( I2C_parameters_t myI2Cparameters, VEML6035_data_t myLowThreshold					);

/** It gets the low threshold value.
  */
VEML6035_status_t VEML6035_GetLowThreshold			( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myLowThreshold					);

/** It sets the power safe mode register.
  */
VEML6035_status_t VEML6035_SetPowerSafeMode			( I2C_parameters_t myI2Cparameters, VEML6035_data_t myPowerSafeMode					);

/** It gets the power safe mode register.
  */
VEML6035_status_t VEML6035_GetPowerSafeMode			( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myPowerSafeMode				);

/** It gets the ALS high resolution output data ( raw data ).
  */
VEML6035_status_t VEML6035_GetALS_HighResOutputData	( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myALS							);

/** It gets the white channel output data ( raw data ).
  */
VEML6035_status_t VEML6035_GetWhiteChannelOutputData( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myWhite						);

/** It gets the interrupt status.
  */
VEML6035_status_t VEML6035_GetInterruptStatus		( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myIF							);

/** It calculates the lux level and the current resolution.
  */
void VEML6035_CalculateLuxLevel						( VEML6035_data_t* myLux															);


