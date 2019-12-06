/**
 * @brief       VEML6030.h
 * @details     High Accuracy Ambient Light Sensor With I2C Interface.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        29/November/2019
 * @version     29/November/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESSES
  */
typedef enum
{
	VEML6030_ADDRESS_GND  =   0b0010000,     /*!<   ADDR = GND                   	*/
	VEML6030_ADDRESS_VDD  =   0b1001000      /*!<   ADDR = VDD                   	*/
} VEML6030_addresses_t;



/**
  * @brief   COMMAND REGISTER FORMAT
  */
typedef enum
{
  VEML6030_ALS_CONF     		=   0x00,	/*!<  Configuration register            */
  VEML6030_ALS_WH			    =   0x01,   /*!<  High Threshold Windows Setting	*/
  VEML6030_ALS_WL		      	=   0x02,   /*!<  Low Threshold Windows Setting		*/
  VEML6030_POWER_SAVING		    =   0x03,   /*!<  Power Saving Mode: PSM		    */
  VEML6030_ALS			    	=   0x04,   /*!<  ALS High Resolution Output Data   */
  VEML6030_WHITE				=   0x05,   /*!<  White Channel Output Data			*/
  VEML6030_ALS_INT			 	=   0x06    /*!<  Interrupt status				    */
} VEML6030_command_register_format_t;



/**
  * @brief   CONFIGURATION REGISTER
 */
/* ALS_GAIN <12:11>
 *    NOTE: Gain selection.
 */
typedef enum
{
	ALS_CONF_ALS_GAIN_MASK					=   ( 0b11 << 11U ),	/*!<  ALS_GAIN mask       	    			    */
	ALS_CONF_ALS_GAIN_X1					=   ( 0b00 << 11U ),	/*!<  ALS gain x 1								*/
	ALS_CONF_ALS_GAIN_X2					=   ( 0b01 << 11U ), 	/*!<  ALS gain x 2					 			*/
	ALS_CONF_ALS_GAIN_X1_8					=   ( 0b10 << 11U ), 	/*!<  ALS gain x 1/8				 			*/
	ALS_CONF_ALS_GAIN_X1_4					=   ( 0b11 << 11U ) 	/*!<  ALS gain x 1/4				 			*/
} VEML6030_als_conf_als_gain_t;


/* ALS_IT <9:6>
 *    NOTE: ALS integration time setting.
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
} VEML6030_als_conf_als_it_t;


/* ALS_PERS <5:4>
 *    NOTE: ALS persistence protect number setting.
 */
typedef enum
{
	ALS_CONF_ALS_PERS_MASK					=   ( 0b11 << 4U ),		/*!<  ALS_PERS mask       	    			    */
	ALS_CONF_ALS_PERS_1	  					=   ( 0b00 << 4U ),		/*!<  ALS 1										*/
	ALS_CONF_ALS_PERS_2						=   ( 0b01 << 4U ), 	/*!<  ALS 2					 					*/
	ALS_CONF_ALS_PERS_4						=   ( 0b10 << 4U ), 	/*!<  ALS 4							 			*/
	ALS_CONF_ALS_PERS_8						=   ( 0b11 << 4U ) 		/*!<  ALS 8							 			*/
} VEML6030_als_conf_als_pers_t;


/* ALS_INT_EN <1>
 *    NOTE: ALS interrupt enable setting.
 */
typedef enum
{
	ALS_CONF_ALS_INT_EN_MASK				=   ( 1U << 1U ),		/*!<  ALS_INT_EN mask      	    			    */
	ALS_CONF_ALS_INT_EN_DISABLE  			=   ( 0U << 1U ),		/*!<  ALS INT disable							*/
	ALS_CONF_ALS_INT_EN_ENABLE				=   ( 1U << 1U )  		/*!<  ALS INT enable		 					*/
} VEML6030_als_conf_als_int_en_t;


/* ALS_SD <0>
 *    NOTE: ALS shut down setting.
 */
typedef enum
{
	ALS_CONF_ALS_SD_MASK					=   ( 1U << 0U ),		/*!<  ALS_SD mask      		    			    */
	ALS_CONF_ALS_SD_POWER_ON  				=   ( 0U << 0U ),		/*!<  ALS power on								*/
	ALS_CONF_ALS_SD_SHUTDOWN				=   ( 1U << 0U )  		/*!<  ALS shut down			 					*/
} VEML6030_als_conf_als_sd_t;



/**
  * @brief   POWER SAVING MODES
 */
/* PSM <2:1>
 *    NOTE: Power saving mode; see table "Refresh time".
 */
typedef enum
{
	POWER_SAVING_PSM_MASK					=   ( 0b11 << 1U ),		/*!<  PSM mask  	     	    			    */
	POWER_SAVING_PSM_MODE_1					=   ( 0b00 << 1U ),		/*!<  mode 1									*/
	POWER_SAVING_PSM_MODE_2					=   ( 0b01 << 1U ), 	/*!<  mode 2					 				*/
	POWER_SAVING_PSM_MODE_3					=   ( 0b10 << 1U ), 	/*!<  mode 3				 					*/
	POWER_SAVING_PSM_MODE_4					=   ( 0b11 << 1U ) 		/*!<  mode 4						 			*/
} VEML6030_power_saving_psm_t;


/* PSM_EN <0>
 *    NOTE: Power saving mode; see table "Refresh time".
 */
typedef enum
{
	POWER_SAVING_PSM_EN_MASK				=   ( 1U << 0U ),		/*!<  PSM_EN mask  	     	    			    */
	POWER_SAVING_PSM_EN_DISABLE				=   ( 0U << 0U ),		/*!<  Disable									*/
	POWER_SAVING_PSM_EN_ENABLE				=   ( 1U << 0U )  		/*!<  Enable					 				*/
} VEML6030_power_saving_psm_en_t;



/**
  * @brief   INTERRUPT STATUS
 */
/* INT_TH_LOW <15>
 *    NOTE: Read bit. Indicated a low threshold exceed.
 */
typedef enum
{
	ALS_INT_INT_TH_LOW_MASK					=   ( 1U << 15U ),		/*!<  INT_TH_LOW mask  	   	    			    */
	ALS_INT_INT_TH_LOW_NO_EXCEEDED			=   ( 0U << 15U ),		/*!<  A low threshold no exceed					*/
	ALS_INT_INT_TH_LOW_EXCEEDED				=   ( 1U << 15U ) 		/*!<  Indicated a low threshold exceed 			*/
} VEML6030_als_int_int_th_low_t;


/* INT_TH_HIGH <14>
 *    NOTE: Read bit. Indicated a high threshold exceed.
 */
typedef enum
{
	ALS_INT_INT_TH_HIGH_MASK				=   ( 1U << 14U ),		/*!<  INT_TH_HIGH mask  		   			    */
	ALS_INT_INT_TH_HIGH_NO_EXCEEDED			=   ( 0U << 14U ),		/*!<  A high threshold no exceed				*/
	ALS_INT_INT_TH_HIGH_EXCEEDED			=   ( 1U << 14U ) 		/*!<  Indicated a high threshold exceed 		*/
} VEML6030_als_int_int_th_high_t;




#ifndef VEML6030_VECTOR_STRUCT_H
#define VEML6030_VECTOR_STRUCT_H
typedef struct
{
	/* Raw ALS high resolution output data	 */
	uint16_t als_high_resolution_output_data;				/*!< Raw ALS high resolution output data			*/

	/* Raw WHITE output data	 */
	uint16_t white_output_data;								/*!< Raw WHITE output data							*/

	/* Raw threshold windows setting	 */
	uint16_t high_threshold_windows_setting;				/*!< Raw ALS high threshold window setting			*/
	uint16_t low_threshold_windows_setting;					/*!< Raw ALS low threshold window setting			*/

	/* Configuration register	 */
	VEML6030_als_conf_als_gain_t	als_gain;				/*!< Gain selection									*/
	VEML6030_als_conf_als_it_t		als_it;					/*!< ALS integration time setting					*/
	VEML6030_als_conf_als_pers_t	als_pers;				/*!< ALS persistence protect number setting			*/
	VEML6030_als_conf_als_int_en_t	als_int_en;				/*!< ALS interrupt enable setting					*/
	VEML6030_als_conf_als_sd_t		als_sd;					/*!< ALS shut down setting							*/

	/* Power saving modes	 */
	VEML6030_power_saving_psm_t		psm;					/*!< Power saving mode								*/
	VEML6030_power_saving_psm_en_t	psm_en;					/*!< Power saving mode enable setting				*/

	/* Interrupt status	 */
	VEML6030_als_int_int_th_low_t	int_th_low;				/*!< Indicated if a low threshold exceed			*/
	VEML6030_als_int_int_th_high_t	int_th_high;			/*!< Indicated if a high threshold exceed			*/
} VEML6030_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    VEML6030_SUCCESS     =       0,
    VEML6030_FAILURE     =       1
} VEML6030_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
VEML6030_status_t VEML6030_Init               	( I2C_parameters_t myI2Cparameters                                		);

/** It sets the configuration register.
  */
VEML6030_status_t VEML6030_SetConfiguration		( I2C_parameters_t myI2Cparameters, VEML6030_data_t myALS_Conf			);

/** It gets the configuration register value.
  */
VEML6030_status_t VEML6030_GetConfiguration		( I2C_parameters_t myI2Cparameters, VEML6030_data_t* myALS_Conf			);

