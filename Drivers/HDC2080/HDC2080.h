/**
 * @brief       HDC2080.h
 * @details     Low-Power Humidity and Temperature Digital Sensor.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/October/2019
 * @version     10/October/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( https://www.nimbus.cit.ie ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESSES
  */
typedef enum
{
  HDC2080_ADDRESS_GND  =   0b1000000,         	/*!<   ADDR connected to GND                        */
  HDC2080_ADDRESS_VDD  =   0b1000001          	/*!<   ADDR connected to VDD                        */
} HDC2080_addresses_t;



/**
  * @brief   REGISTER MAP
  */
typedef enum
{
  HDC2080_TEMPERATURE_LOW        	=   0x00,	/*!<  Temperature [7:0]		                         						*/
  HDC2080_TEMPERATURE_HIGH         	=   0x01,   /*!<  Temperature [15:8]							     					*/
  HDC2080_HUMIDITY_LOW      		=   0x02,   /*!<  Humidity [7:0]                        								*/
  HDC2080_HUMIDITY_HIGH	         	=   0x03,   /*!<  Humidity [15:8]	                             						*/
  HDC2080_INTERRUPT_DRDY    		=   0x04,   /*!<  DataReady and interrupt configuration                        			*/
  HDC2080_TEMPERATURE_MAX		    =   0x05,   /*!<  Maximum measured temperature (Not supported in Auto Measurement Mode)	*/
  HDC2080_HUMIDITY_MAX    			=   0x06,   /*!<  Maximum measured humidity (Not supported in Auto Measurement Mode)	*/
  HDC2080_INTERRUPT_ENABLE    		=   0x07,   /*!<  Interrupt Enable	                 									*/
  HDC2080_TEMP_OFFSET_ADJUST   		=   0x08,   /*!<  Temperature offset adjustment	                 						*/
  HDC2080_HUM_OFFSET_ADJUST 		=   0x09,   /*!<  Humidity offset adjustment                      						*/
  HDC2080_TEMP_THR_L 				=   0x0A,   /*!<  Temperature Threshold Low                      						*/
  HDC2080_TEMP_THR_H 				=   0x0B,   /*!<  Temperature Threshold High                        					*/
  HDC2080_RH_THR_L 					=   0x0C,   /*!<  Humidity threshold Low                       							*/
  HDC2080_RH_THR_H 					=   0x0D,   /*!<  Humidity threshold High                       						*/
  HDC2080_RESET_DRDY_INT_CONF 		=   0x0E,   /*!<  Soft Reset and Interrupt Configuration                        		*/
  HDC2080_MEASUREMENT_CONFIGURATION	=   0x0F,   /*!<  Measurement configuration                       						*/
  HDC2080_MANUFACTURER_ID_LOW 		=   0xFC,   /*!<  Manufacturer ID Low                       							*/
  HDC2080_MANUFACTURER_ID_HIGH 		=   0xFD,   /*!<  Manufacturer ID High                      							*/
  HDC2080_DEVICE_ID_LOW 			=   0xFE,   /*!<  Device ID Low                       									*/
  HDC2080_DEVICE_ID_HIGH 			=   0xFF    /*!<  Device ID High                      									*/
} HDC2080_register_map_t;



/**
  * @brief   INTERRUPT/DRDY REGISTER
  */
/* DRDY_STATUS <7>
 *    NOTE: DataReady bit status. DRDY_STATUS is cleared to 0 when read.
 */
typedef enum
{
    INTERRUPT_DRDY_DRDY_STATUS_MASK				=   ( 1U << 7U ),	/*!<  DRDY_STATUS mask                          */
	INTERRUPT_DRDY_DRDY_STATUS_DATA_NOT_READY	=   ( 0U << 7U ),	/*!<  DRDY_STATUS data not ready                */
	INTERRUPT_DRDY_DRDY_STATUS_DATA_READY		=   ( 1U << 7U )	/*!<  DRDY_STATUS data ready 		            */
} HDC2080_interrupt_drdy_drdy_status_t;


/* TH_STATUS <6>
 *    NOTE: Temperature threshold HIGH Interrupt status. TH_STATUS is cleared to 0 when read.
 */
typedef enum
{
    INTERRUPT_DRDY_TH_STATUS_MASK				=   ( 1U << 6U ),	/*!<  TH_STATUS mask 	                        */
	INTERRUPT_DRDY_TH_STATUS_NO_INTERRUPT		=   ( 0U << 6U ),	/*!<  No interrupt				                */
	INTERRUPT_DRDY_TH_STATUS_INTERRUPT			=   ( 1U << 6U )	/*!<  Interrupt				 		            */
} HDC2080_interrupt_drdy_th_status_t;


/* TL_STATUS <5>
 *    NOTE: Temperature threshold LOW Interrupt status. TL_STATUS is cleared to 0 when read.
 */
typedef enum
{
    INTERRUPT_DRDY_TL_STATUS_MASK				=   ( 1U << 5U ),	/*!<  TL_STATUS mask 	                        */
	INTERRUPT_DRDY_TL_STATUS_NO_INTERRUPT		=   ( 0U << 5U ),	/*!<  No interrupt				                */
	INTERRUPT_DRDY_TL_STATUS_INTERRUPT			=   ( 1U << 5U )	/*!<  Interrupt				 		            */
} HDC2080_interrupt_drdy_tl_status_t;


/* HH_STATUS <4>
 *    NOTE: Humidity threshold HIGH Interrupt status. HH_STATUS is cleared to 0 when read.
 */
typedef enum
{
    INTERRUPT_DRDY_HH_STATUS_MASK				=   ( 1U << 4U ),	/*!<  HH_STATUS mask 	                        */
	INTERRUPT_DRDY_HH_STATUS_NO_INTERRUPT		=   ( 0U << 4U ),	/*!<  No interrupt				                */
	INTERRUPT_DRDY_HH_STATUS_INTERRUPT			=   ( 1U << 4U )	/*!<  Interrupt				 		            */
} HDC2080_interrupt_drdy_hh_status_t;


/* HL_STATUS <3>
 *    NOTE: Humidity threshold LOW Interrupt status. HL_STATUS is cleared to 0 when read.
 */
typedef enum
{
    INTERRUPT_DRDY_HL_STATUS_MASK				=   ( 1U << 3U ),	/*!<  HL_STATUS mask 	                        */
	INTERRUPT_DRDY_HL_STATUS_NO_INTERRUPT		=   ( 0U << 3U ),	/*!<  No interrupt				                */
	INTERRUPT_DRDY_HL_STATUS_INTERRUPT			=   ( 1U << 3U ) 	/*!<  Interrupt				 		            */
} HDC2080_interrupt_drdy_hl_status_t;



/**
  * @brief   INTERRUPT CONFIGURATION REGISTER
  */
/* DRDY_STATUS <7>
 *    NOTE: DataReady interrupt enable.
 */
typedef enum
{
    INTERRUPT_DRDY_DRDY_ENABLE_MASK					=   ( 1U << 7U ),	/*!<  DRDY_ENABLE mask                          */
	INTERRUPT_DRDY_DRDY_ENABLE_INTERRUPT_DISABLE	=   ( 0U << 7U ),	/*!<  DRDY_ENABLE interrupt disable             */
	INTERRUPT_DRDY_DRDY_ENABLE_INTERRUPT_ENABLE		=   ( 1U << 7U )	/*!<  DRDY_ENABLE interrupt enable 		        */
} HDC2080_interrupt_enable_drdy_enable_t;


/* TH_ENABLE <6>
 *    NOTE: Temperature threshold HIGH Interrupt enable.
 */
typedef enum
{
    INTERRUPT_DRDY_TH_ENABLE_MASK					=   ( 1U << 6U ),	/*!<  TH_ENABLE mask 	                        */
	INTERRUPT_DRDY_TH_ENABLE_INTERRUPT_DISABLE		=   ( 0U << 6U ),	/*!<  Interrupt disable			                */
	INTERRUPT_DRDY_TH_ENABLE_INTERRUPT_ENABLE		=   ( 1U << 6U ),	/*!<  Interrupt	enable		 		            */
} HDC2080_interrupt_enable_th_enable_t;


/* TL_ENABLE <5>
 *    NOTE: Temperature threshold LOW Interrupt enable.
 */
typedef enum
{
    INTERRUPT_DRDY_TL_ENABLE_MASK					=   ( 1U << 5U ),	/*!<  TL_ENABLE mask 	                        */
	INTERRUPT_DRDY_TL_ENABLE_INTERRUPT_DISABLE		=   ( 0U << 5U ),	/*!<  Interrupt disable			                */
	INTERRUPT_DRDY_TL_ENABLE_INTERRUPT_ENABLE		=   ( 1U << 5U ),	/*!<  Interrupt	enable		 		            */
} HDC2080_interrupt_enable_tl_enable_t;


/* HH_ENABLE <4>
 *    NOTE: Humidity threshold HIGH Interrupt enable.
 */
typedef enum
{
    INTERRUPT_DRDY_HH_ENABLE_MASK					=   ( 1U << 4U ),	/*!<  HH_ENABLE mask 	                        */
	INTERRUPT_DRDY_HH_ENABLE_INTERRUPT_DISABLE		=   ( 0U << 4U ),	/*!<  Interrupt disable			                */
	INTERRUPT_DRDY_HH_ENABLE_INTERRUPT_ENABLE		=   ( 1U << 4U ),	/*!<  Interrupt	enable		 		            */
} HDC2080_interrupt_enable_hh_enable_t;


/* HL_ENABLE <3>
 *    NOTE: Humidity threshold LOW Interrupt enable.
 */
typedef enum
{
    INTERRUPT_DRDY_HL_ENABLE_MASK					=   ( 1U << 3U ),	/*!<  HL_ENABLE mask 	                        */
	INTERRUPT_DRDY_HL_ENABLE_INTERRUPT_DISABLE		=   ( 0U << 3U ),	/*!<  Interrupt disable			                */
	INTERRUPT_DRDY_HL_ENABLE_INTERRUPT_ENABLE		=   ( 1U << 3U ),	/*!<  Interrupt	enable		 		            */
} HDC2080_interrupt_enable_hl_enable_t;


/**
  * @brief   TEMP_OFFSET_ADJUST REGISTER
  *				NOTE: Temperature offset adjustment. Added to the converted temperature value.
 */
typedef enum
{
	TEMP_OFFSET_ADJUST_MASK				=   0xFF,						/*!<  TEMP_OFFSET_ADJUST mask       	        */
	TEMP_OFFSET_ADJUST_MINUS_20_62_C	=   ( 1U << 7U ),				/*!<  TEMP_OFFSET_ADJUST: –20.62°C  			*/
	TEMP_OFFSET_ADJUST_10_32_C			=   ( 1U << 6U ),				/*!<  TEMP_OFFSET_ADJUST:  10.32°C  			*/
	TEMP_OFFSET_ADJUST_5_16_C			=   ( 1U << 5U ),				/*!<  TEMP_OFFSET_ADJUST:   5.16°C  			*/
	TEMP_OFFSET_ADJUST_2_58_C			=   ( 1U << 4U ),				/*!<  TEMP_OFFSET_ADJUST:   2.58°C  			*/
	TEMP_OFFSET_ADJUST_1_28_C			=   ( 1U << 3U ),				/*!<  TEMP_OFFSET_ADJUST:   1.28°C  			*/
	TEMP_OFFSET_ADJUST_0_64_C			=   ( 1U << 2U ),				/*!<  TEMP_OFFSET_ADJUST:   0.64°C  			*/
	TEMP_OFFSET_ADJUST_0_32_C			=   ( 1U << 1U ),				/*!<  TEMP_OFFSET_ADJUST:   0.32°C  			*/
	TEMP_OFFSET_ADJUST_0_16_C			=   ( 1U << 0U ) 				/*!<  TEMP_OFFSET_ADJUST:   0.16°C  			*/
} HDC2080_temp_offset_adjust_t;









/**
  * @brief   POWER_DOWN REGISTER
  */
/* PWR_DOWN <0>
 *    NOTE: Power down or active mode.
 */
typedef enum
{
	POWER_DOWN_PWR_DOWN_MASK       	=   ( 1U << 0U ),    /*!<  POWER_DOWN mask                          		*/
	POWER_DOWN_PWR_DOWN_POWER_DOWN	=   ( 0U << 0U ),    /*!<  Power down				    		[ Default ] */
	POWER_DOWN_PWR_DOWN_ACTIVE      =   ( 1U << 0U )     /*!<  Active					                		*/
} HDC2080_power_down_pwr_down_t;


/**
  * @brief   RESET REGISTER
  */
/* RSTB <0>
 *    NOTE: N/A.
 */
typedef enum
{
	RESET_RSTB_MASK       			=   ( 1U << 0U ),    /*!<  RSTB mask                          		       	*/
	RESET_RSTB_RESET          		=   ( 0U << 0U ),    /*!<  Measurement control block is reset  	[ Default ] */
	RESET_RSTB_ACTIVE          		=   ( 1U << 0U )     /*!<  Measurement control block is active  		   	*/
} HDC2080_reset_rstb_t;



/**
  * @brief   MODE_CONTROL REGISTER
  */
/* AVE_NUM <7:5>
 *    NOTE: Set the average number of measurement data.
 */
typedef enum
{
	MODE_CONTROL_AVE_NUM_MASK     	=   ( 0b111 << 5U ), /*!<  AVE_NUM mask                                     */
	MODE_CONTROL_AVE_NUM_SINGLE     =   ( 0b000 << 5U ), /*!<  AVE_NUM: Single                                  */
	MODE_CONTROL_AVE_NUM_AVERAGE_2  =   ( 0b001 << 5U ), /*!<  AVE_NUM: Average of  2 times         [ Default ] */
	MODE_CONTROL_AVE_NUM_AVERAGE_4  =   ( 0b010 << 5U ), /*!<  AVE_NUM: Average of  4 times                     */
	MODE_CONTROL_AVE_NUM_AVERAGE_8  =   ( 0b011 << 5U ), /*!<  AVE_NUM: Average of  8 times                     */
	MODE_CONTROL_AVE_NUM_AVERAGE_16 =   ( 0b100 << 5U ), /*!<  AVE_NUM: Average of 16 times                     */
	MODE_CONTROL_AVE_NUM_AVERAGE_32 =   ( 0b101 << 5U ), /*!<  AVE_NUM: Average of 32 times                     */
	MODE_CONTROL_AVE_NUM_AVERAGE_64 =   ( 0b110 << 5U )  /*!<  AVE_NUM: Average of 64 times                     */
} HDC2080_mode_control_ave_num_t;


/* DREN <4>
 *    NOTE: DRDY pin Enable.
 */
typedef enum
{
	MODE_CONTROL_DREN_MASK     		=   ( 1U << 4U ), 	/*!<  DREN mask                             	        */
	MODE_CONTROL_DREN_DRDY_DISABLE	=   ( 0U << 4U ), 	/*!<  DRDY pin Disable                     	[ Default ] */
	MODE_CONTROL_DREN_DRDY_ENABLE 	=   ( 1U << 4U )  	/*!<  DRDY pin Enable                     				*/
} HDC2080_mode_control_dren_t;


/* MODE <1:0>
 *    NOTE: Set measurement mode.
 */
typedef enum
{
	MODE_CONTROL_MODE_MASK     		=   ( 0b11 << 0U ), /*!<  MODE mask                                        */
	MODE_CONTROL_MODE_STAND_BY      =   ( 0b00 << 0U ), /*!<  Stand by                             [ Default ] */
	MODE_CONTROL_MODE_ONE_SHOT		=   ( 0b01 << 0U ), /*!<  One shot                    					   */
	MODE_CONTROL_MODE_CONTINUOUS    =   ( 0b10 << 0U )  /*!<  Continuous				                       */
} HDC2080_mode_control_mode_t;


/**
  * @brief   STATUS REGISTER
  */
/* RD_DRDY <0>
 *    NOTE: Pressure and temperature measurement data ready bit.
 */
typedef enum
{
	STATUS_RD_DRDY_MASK       		=   ( 1U << 0U ),    /*!<  RD_DRDY mask                      		       						*/
	STATUS_RD_DRDY_DATA_MEASURING   =   ( 0U << 0U ),    /*!<  Measurement data output is not yet available (measuring)	[ Default ] */
	STATUS_RD_DRDY_DATA_AVAILABLE	=   ( 1U << 0U )     /*!<  Measurement data output is available								   	*/
} HDC2080_reset_rd_drdy_t;





#ifndef HDC2080_VECTOR_STRUCT_H
#define HDC2080_VECTOR_STRUCT_H
typedef struct
{
    /* Output registers  */
    int32_t rawPressure;     						/*!<  Raw pressure                  */
    int16_t	rawTemperature;  						/*!<  Raw temperature               */

    float   pressure;        						/*!<  Pressure value                */
    float   temperature;     						/*!<  Temperature value             */

    /* Mode control	 */
    HDC2080_mode_control_ave_num_t ave_num;		/*!<  Average number of measurement */
    HDC2080_mode_control_dren_t	  dren;			/*!<  DRDY pin Enable	            */
    HDC2080_mode_control_mode_t	  mode;			/*!<  Set measurement mode	        */

    /* Device status	 */
    HDC2080_power_down_pwr_down_t pwr_down;		/*!<  Power mode		            */
    HDC2080_reset_rstb_t			 rstb;			/*!<  Reset				            */
    HDC2080_reset_rd_drdy_t		 rd_drdy;		/*!<  Status flag		            */

    /* Device identification   */
    uint8_t id1;        							/*!<  Device ID1                    */
    uint8_t id2;        							/*!<  Device ID2                    */
} HDC2080_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    HDC2080_SUCCESS     =       0,
    HDC2080_FAILURE     =       1
} HDC2080_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
HDC2080_status_t HDC2080_Init               ( I2C_parameters_t myI2Cparameters                                );

/** It gets the device identifications.
  */
HDC2080_status_t HDC2080_GetDeviceID        ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myDeviceID	);

/** It sets the power-down mode.
  */
HDC2080_status_t HDC2080_SetPowerDown       ( I2C_parameters_t myI2Cparameters, HDC2080_data_t myPwrDown	);

/** It gets the power-down mode.
  */
HDC2080_status_t HDC2080_GetPowerDown       ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myPwrDown	);

/** It sets the soft-reset.
  */
HDC2080_status_t HDC2080_SetSoftReset       ( I2C_parameters_t myI2Cparameters, HDC2080_data_t myRSTB		);

/** It gets the reset flag.
  */
HDC2080_status_t HDC2080_GetSoftResetFlag   ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myRSTB		);

/** It sets the mode control.
  */
HDC2080_status_t HDC2080_SetModeControl     ( I2C_parameters_t myI2Cparameters, HDC2080_data_t myModeCont	);

/** It gets the mode control.
  */
HDC2080_status_t HDC2080_GetModeControl	  ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myModeCont	);

/** It gets the status flag.
  */
HDC2080_status_t HDC2080_GetStatus		  ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myRD_DRDY	);

/** It gets the raw pressure.
  */
HDC2080_status_t HDC2080_GetRawPressure     ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myRawP		);

/** It gets the raw temperature.
  */
HDC2080_status_t HDC2080_GetRawTemperature  ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myRawT		);

/** It gets the pressure.
  */
HDC2080_status_t HDC2080_GetPressure     	  ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myP		);

/** It gets the temperature.
  */
HDC2080_status_t HDC2080_GetTemperature  	  ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myT		);
