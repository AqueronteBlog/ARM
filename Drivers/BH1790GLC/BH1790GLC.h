/**
 * @brief       BH1790GLC.h
 * @details     Optical Sensor for Heart Rate Monitor IC.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        04/November/2019
 * @version     04/November/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESS
  */
typedef enum
{
  BH1790GLC_ADDRESS  =   0b1011011          /*!<   ADDR                         	*/
} BH1790GLC_address_t;



/**
  * @brief   REGISTER MAP
  */
typedef enum
{
  BH1790GLC_MANUFACTURER_ID     =   0x0F,	/*!<  Manufacturer ID                   */
  BH1790GLC_PART_ID			    =   0x10,   /*!<  Part ID							*/
  BH1790GLC_RESET		      	=   0x40,   /*!<  SWRESET                       	*/
  BH1790GLC_MEAS_CONTROL1	    =   0x41,   /*!<  Measurement setting Control       */
  BH1790GLC_MEAS_CONTROL2    	=   0x42,   /*!<  Measurement setting Control       */
  BH1790GLC_MEAS_START			=   0x43,   /*!<  Start Measurement					*/
  BH1790GLC_DATAOUT_LEDOFF_LSB 	=   0x54,   /*!<  Measurement Data LSB (LED OFF)	*/
  BH1790GLC_DATAOUT_LEDOFF_MSB	=   0x55,   /*!<  Measurement Data MSB (LED OFF)	*/
  BH1790GLC_DATAOUT_LEDON_LSB   =   0x56,   /*!<  Measurement Data LSB (LED ON)     */
  BH1790GLC_DATAOUT_LEDON_MSB 	=   0x57    /*!<  Measurement Data MSB (LED ON)     */
} BH1790GLC_register_map_t;



/**
  * @brief   MANUFACTOR ID REGISTER
  */
typedef enum
{
    MANUFACTOR_ID_MANUFACTURER_ID				=   0xE0			/*!<  Manufacturer ID                         	*/
} BH1790GLC_manufactor_id_manufacturer_id_t;


/**
  * @brief   PART ID REGISTER
  */
typedef enum
{
	PART_ID_PART_ID								=   0x0D			/*!<  Part ID					 		        */
} BH1790GLC_part_id_part_id_t;


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
} BH1790GLC_reset_swreset_t;


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
	MEAS_CONTROL1_RDY_OSC_BLOCK_ACTIVE			=   ( 1U << 0U ) 	/*!<  OSC block clock to internal block			*/
} BH1790GLC_meas_control1_rdy_t;


/* LED_LIGHTING_FREQ <2>
 *    NOTE: Select LED emitting frequency.
 */
typedef enum
{
	MEAS_CONTROL1_LED_LIGHTING_FREQ_MASK		=   ( 1U << 2U ),		/*!<  LED_LIGHTLING_FREQ mask      				*/
	MEAS_CONTROL1_LED_LIGHTING_FREQ_128HZ_MODE	=   ( 0U << 2U ),		/*!<  128Hz Mode								*/
	MEAS_CONTROL1_LED_LIGHTING_FREQ_64HZ_MODE	=   ( 1U << 2U ) 		/*!<  64Hz Mode									*/
} BH1790GLC_meas_control1_led_lighting_freq_t;


/* RCYCLE <1:0>
 *    NOTE: Select Data reading frequency.
 */
typedef enum
{
	MEAS_CONTROL1_RCYCLE_MASK					=   ( 0b11 << 0U ),		/*!<  RCYCLE mask      							*/
	MEAS_CONTROL1_RCYCLE_64HZ_MODE				=   ( 0b01 << 0U ),		/*!<  128Hz Mode								*/
	MEAS_CONTROL1_RCYCLE_32HZ_MODE				=   ( 0b10 << 0U ) 		/*!<  64Hz Mode									*/
} BH1790GLC_meas_control1_rcycle_t;







#ifndef BH1790GLC_VECTOR_STRUCT_H
#define BH1790GLC_VECTOR_STRUCT_H
typedef struct
{


    /* Device identifications   */
    uint8_t manufacturer_id;        					/*!<  Manufacturer ID              */
    uint8_t PART_id;        							/*!<  Part ID                      */
} BH1790GLC_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    BH1790GLC_SUCCESS     =       0,
    BH1790GLC_FAILURE     =       1
} BH1790GLC_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
BH1790GLC_status_t BH1790GLC_Init               		( I2C_parameters_t myI2Cparameters                                		);

/** It gets the raw temperature.
  */
BH1790GLC_status_t BH1790GLC_GetRawTemperature  		( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myRawTemperature	);

/** It gets the current temperature.
  */
BH1790GLC_status_t BH1790GLC_GetTemperature  			( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myTemperature		);

/** It gets the raw humidity.
  */
BH1790GLC_status_t BH1790GLC_GetRawHumidity  			( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myRawHumidity		);

/** It gets the current humidity.
  */
BH1790GLC_status_t BH1790GLC_GetHumidity	  			( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myHumidity			);

/** It gets the interrupt DRDY status.
  */
BH1790GLC_status_t BH1790GLC_GetInterrupt_DRDY_Status	( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myStatus			);

/** It writes the temperature max register ( raw value ).
  */
BH1790GLC_status_t BH1790GLC_ConfTemperatureMax			( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myTemperatureMax		);

/** It writes the humidity max register ( raw value ).
  */
BH1790GLC_status_t BH1790GLC_ConfHumidityMax			( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myHumidityMax		);

/** It sets the interrupt configuration.
  */
BH1790GLC_status_t BH1790GLC_SetInterruptConfiguration	( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myIntConfiguration	);

/** It gets the interrupt configuration.
  */
BH1790GLC_status_t BH1790GLC_GetInterruptConfiguration	( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myIntConfiguration	);

/** It sets the temperature offset.
  */
BH1790GLC_status_t BH1790GLC_SetTemperatureOffset		( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myTemperatureOffset	);

/** It gets the temperature offset ( raw value ).
  */
BH1790GLC_status_t BH1790GLC_GetTemperatureOffset		( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myTemperatureOffset	);

/** It sets the humidity offset.
  */
BH1790GLC_status_t BH1790GLC_SetHumidityOffset			( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myHumidityOffset		);

/** It gets the humidity offset ( raw value ).
  */
BH1790GLC_status_t BH1790GLC_GetHumidityOffset			( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myHumidityOffset	);

/** It sets the temperature threshold low value ( raw value ).
  */
BH1790GLC_status_t BH1790GLC_SetTemperatureThresLow		( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myTempThresLow		);

/** It gets the temperature threshold low value ( raw value ).
  */
BH1790GLC_status_t BH1790GLC_GetTemperatureThresLow		( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myTempThresLow		);

/** It sets the temperature threshold high value ( raw value ).
  */
BH1790GLC_status_t BH1790GLC_SetTemperatureThresHigh	( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myTempThresLow		);

/** It gets the temperature threshold high value ( raw value ).
  */
BH1790GLC_status_t BH1790GLC_GetTemperatureThresHigh	( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myTempThresHigh		);

/** It sets the humidity threshold low value ( raw value ).
  */
BH1790GLC_status_t BH1790GLC_SetHumidityThresLow		( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myHumThresLow		);

/** It gets the humidity threshold low value ( raw value ).
  */
BH1790GLC_status_t BH1790GLC_GetHumidityThresLow		( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myHumThresLow		);

/** It sets the humidity threshold high value ( raw value ).
  */
BH1790GLC_status_t BH1790GLC_SetHumidityThresHigh		( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myHumThresLow		);

/** It gets the humidity threshold high value ( raw value ).
  */
BH1790GLC_status_t BH1790GLC_GetHumidityThresHigh		( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myHumThresLow		);

/** It makes a soft reset.
  */
BH1790GLC_status_t BH1790GLC_SetSoftReset				( I2C_parameters_t myI2Cparameters										);

/** It checks the soft reset flag.
  */
BH1790GLC_status_t BH1790GLC_GetSoftReset				( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* mySoftResetFlag		);

/** It sets auto measurement mode ( AMM ).
  */
BH1790GLC_status_t BH1790GLC_SetAutoMeasurementMode		( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myAMM				);

/** It gets auto measurement mode ( AMM ).
  */
BH1790GLC_status_t BH1790GLC_GetAutoMeasurementMode		( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myAMM				);

/** It sets the heater.
  */
BH1790GLC_status_t BH1790GLC_SetHeaterMode				( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myHeatEn				);

/** It gets the heater status.
  */
BH1790GLC_status_t BH1790GLC_GetHeaterMode				( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myHeatEn			);

/** It sets the DRDY/INT_EN pin configuration.
  */
BH1790GLC_status_t BH1790GLC_SetPinConfifuration		( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myPinConfiguration	);

/** It gets the DRDY/INT_EN pin configuration.
  */
BH1790GLC_status_t BH1790GLC_GetPinConfiguration		( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myPinConfiguration	);

/** It sets the interrupt polarity.
  */
BH1790GLC_status_t BH1790GLC_SetInterruptPolarity		( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myIntPol				);

/** It gets the interrupt polarity.
  */
BH1790GLC_status_t BH1790GLC_GetInterruptPolarity		( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myIntPol			);

/** It sets the interrupt mode.
  */
BH1790GLC_status_t BH1790GLC_SetInterruptMode			( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myIntMode			);

/** It gets the interrupt mode.
  */
BH1790GLC_status_t BH1790GLC_GetInterruptMode			( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myIntMode			);

/** It sets the measurement configuration.
  */
BH1790GLC_status_t BH1790GLC_SetMeasurementConf			( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myMeasConf			);

/** It gets the measurement configuration.
  */
BH1790GLC_status_t BH1790GLC_GetMeasurementConf			( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myMeasConf			);

/** It triggers a new measurement.
  */
BH1790GLC_status_t BH1790GLC_StartMeasurementTrigger	( I2C_parameters_t myI2Cparameters										);

/** It gets the measurement trigger flag.
  */
BH1790GLC_status_t BH1790GLC_GetMeasurementTrigger		( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myMeasTrig			);

/** It gets the manufacturer ID.
  */
BH1790GLC_status_t BH1790GLC_GetManufacturerID			( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myManufacturerID	);

/** It gets the device ID.
  */
BH1790GLC_status_t BH1790GLC_GetDeviceID				( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myDeviceID			);


