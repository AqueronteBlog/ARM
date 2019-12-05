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
  * @brief   MANUFACTOR ID REGISTER
  */
typedef enum
{
    MANUFACTOR_ID_MANUFACTURER_ID				=   0xE0			/*!<  Manufacturer ID                         	*/
} VEML6030_manufactor_id_manufacturer_id_t;


/**
  * @brief   PART ID REGISTER
  */
typedef enum
{
	PART_ID_PART_ID								=   0x0D			/*!<  Part ID					 		        */
} VEML6030_part_id_part_id_t;


/**
  * @brief   RESET REGISTER
 */
/* SWRESET <7>
 *    NOTE: Software reset.
 */
typedef enum
{
	RESET_SWRESET_MASK							=   ( 1U << 7U ),	/*!<  SWRESET mask       	    			    */
	RESET_SWRESET_ENABLED						=   ( 1U << 7U ),	/*!<  Software reset is performed				*/
	RESET_SWRESET_DISABLED						=   ( 0U << 7U ) 	/*!<  Software reset is completed	 			*/
} VEML6030_reset_swreset_t;


/**
  * @brief   MEAS_CONTROL1 REGISTER
  *
 */
/* RDY <7>
 *    NOTE: OSC block.
 */
typedef enum
{
	MEAS_CONTROL1_RDY_MASK						=   ( 1U << 7U ),	/*!<  RDY mask       	        				*/
	MEAS_CONTROL1_RDY_PROHIBITED				=   ( 0U << 7U ),	/*!<  Prohibited								*/
	MEAS_CONTROL1_RDY_OSC_BLOCK_ACTIVE			=   ( 1U << 7U ) 	/*!<  OSC block clock to internal block			*/
} VEML6030_meas_control1_rdy_t;


/* LED_LIGHTING_FREQ <2>
 *    NOTE: Select LED emitting frequency.
 */
typedef enum
{
	MEAS_CONTROL1_LED_LIGHTING_FREQ_MASK		=   ( 1U << 2U ),		/*!<  LED_LIGHTLING_FREQ mask      				*/
	MEAS_CONTROL1_LED_LIGHTING_FREQ_128HZ_MODE	=   ( 0U << 2U ),		/*!<  128Hz Mode								*/
	MEAS_CONTROL1_LED_LIGHTING_FREQ_64HZ_MODE	=   ( 1U << 2U ) 		/*!<  64Hz Mode									*/
} VEML6030_meas_control1_led_lighting_freq_t;


/* RCYCLE <1:0>
 *    NOTE: Select Data reading frequency.
 */
typedef enum
{
	MEAS_CONTROL1_RCYCLE_MASK					=   ( 0b11 << 0U ),		/*!<  RCYCLE mask      							*/
	MEAS_CONTROL1_RCYCLE_64HZ_MODE				=   ( 0b01 << 0U ),		/*!<  128Hz Mode								*/
	MEAS_CONTROL1_RCYCLE_32HZ_MODE				=   ( 0b10 << 0U ) 		/*!<  64Hz Mode									*/
} VEML6030_meas_control1_rcycle_t;


/**
  * @brief   MEAS_CONTROL2 REGISTER
  *
 */
/* LED_EN <7:6>
 *    NOTE: Select LED driver mode.
 */
typedef enum
{
	MEAS_CONTROL2_LED_EN_MASK					=   ( 0b11 << 6U ),		/*!<  LED_EN mask     	        				*/
	MEAS_CONTROL2_LED_EN_0						=   ( 0b00 << 6U ),		/*!<  LED1 and LED2 pulsed light emit			*/
	MEAS_CONTROL2_LED_EN_1						=   ( 0b01 << 6U ), 	/*!<  LED1 constant light LED2 pulsed light emit*/
	MEAS_CONTROL2_LED_EN_2						=   ( 0b10 << 6U ), 	/*!<  LED1 pulsed light emit LED2 constant light*/
	MEAS_CONTROL2_LED_EN_3						=   ( 0b11 << 6U )  	/*!<  LED1 and LED2 constant light 				*/
} VEML6030_meas_control2_led_en_t;


/* LED_ON_TIME <5>
 *    NOTE: Select LED emitting time.
 */
typedef enum
{
	MEAS_CONTROL2_LED_ON_TIME_MASK				=   ( 1U << 5U ),		/*!<  LED_ON_TIME mask  						*/
	MEAS_CONTROL2_LED_ON_TIME_0_3_MS_MODE		=   ( 0U << 5U ),		/*!<  0.3ms Mode								*/
	MEAS_CONTROL2_LED_ON_TIME_0_6_MS_MODE		=   ( 1U << 5U ) 		/*!<  0.6ms Mode								*/
} VEML6030_meas_control2_led_on_time_t;


/* LED_CURRENT <3:0>
 *    NOTE: Select LED lighting current.
 */
typedef enum
{
	MEAS_CONTROL2_LED_CURRENT_MASK				=   ( 0b1111 << 0U ),	/*!<  LED_CURRENT mask  						*/
	MEAS_CONTROL2_LED_CURRENT_0_MA_MODE			=   ( 0x0 << 0U ),		/*!<  0mA Mode									*/
	MEAS_CONTROL2_LED_CURRENT_1_MA_MODE			=   ( 0x8 << 0U ),		/*!<  1mA Mode									*/
	MEAS_CONTROL2_LED_CURRENT_2_MA_MODE			=   ( 0x9 << 0U ),		/*!<  2mA Mode									*/
	MEAS_CONTROL2_LED_CURRENT_3_MA_MODE			=   ( 0xA << 0U ),		/*!<  3mA Mode									*/
	MEAS_CONTROL2_LED_CURRENT_6_MA_MODE			=   ( 0xB << 0U ),		/*!<  6mA Mode									*/
	MEAS_CONTROL2_LED_CURRENT_10_MA_MODE		=   ( 0xC << 0U ),		/*!<  10mA Mode									*/
	MEAS_CONTROL2_LED_CURRENT_20_MA_MODE		=   ( 0xD << 0U ),		/*!<  20mA Mode									*/
	MEAS_CONTROL2_LED_CURRENT_30_MA_MODE		=   ( 0xE << 0U ),		/*!<  30mA Mode									*/
	MEAS_CONTROL2_LED_CURRENT_60_MA_MODE		=   ( 0xF << 0U ) 		/*!<  60mA Mode									*/
} VEML6030_meas_control2_led_current_t;


/**
  * @brief   MEAS_START REGISTER
  *
 */
/* LED_EN <0>
 *    NOTE: Flag of start measurement. Start measurement by writing 'MEAS_ST=1' after writing 'RDY=1'. Measurement doesn’t restart if writing
 *    		'MEAS_ST=1' after start measurement. When stop measurement, write 'SWRESET=1' without writing 'MEAS_ST=0'.
 */
typedef enum
{
	MEAS_START_MEAS_ST_MASK						=   ( 1U << 0U ),		/*!<  MEAS_ST mask     	        				*/
	MEAS_START_MEAS_ST_MEASUREMENT_START		=   ( 1U << 0U )  		/*!<  Measurement start							*/
} VEML6030_meas_start_meas_st_t;




#ifndef VEML6030_VECTOR_STRUCT_H
#define VEML6030_VECTOR_STRUCT_H
typedef struct
{
	/* Raw dataout	 */
	uint16_t dataOut_LED_OFF;										/*!<  Green Data Count Value when LED no emitting	*/
	uint16_t dataOut_LED_ON;										/*!<  Green Data Count Value when LED emitting		*/

	/* System control setting	 */
	VEML6030_meas_control1_rdy_t 				rdy;				/*!<  OSC block is supply clock to internal block	*/
	VEML6030_meas_control1_led_lighting_freq_t led_lighting_freq;	/*!<  Select LED emitting frequency					*/
	VEML6030_meas_control1_rcycle_t			rcycle;				/*!<  Select Measurement time 						*/

	/* Measurement control setting	 */
	VEML6030_meas_control2_led_en_t			led_en;				/*!<  Select LED driver mode						*/
	VEML6030_meas_control2_led_on_time_t		led_on_time;		/*!<  Select LED emitting time						*/
	VEML6030_meas_control2_led_current_t		led_current;		/*!<  Select LED driver current						*/

    /* Device identifications   */
    uint8_t manufacturer_id;        								/*!<  Manufacturer ID              					*/
    uint8_t part_id;        										/*!<  Part ID                      					*/
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

/** It gets the manufacturer ID.
  */
VEML6030_status_t VEML6030_GetManufacturerID		( I2C_parameters_t myI2Cparameters, VEML6030_data_t* myManufacturerID	);

