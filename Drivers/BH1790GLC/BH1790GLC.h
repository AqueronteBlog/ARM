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
  * @brief   MANUFACTOR ID
  */
typedef enum
{
    MANUFACTOR_ID_MANUFACTURER_ID	=   0xE0	/*!<  Manufacturer ID                         	*/
} BH1790GLC_manufactor_id_manufacturer_id_t;


/**
  * @brief   PART ID
  */
typedef enum
{
    PART_ID							=   0x0D	/*!<  Part ID					 		        */
} BH1790GLC_part_id_t;


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
} BH1790GLC_temp_offset_adjust_t;


/**
  * @brief   HUM_OFFSET_ADJUST REGISTER
  *				NOTE: Humidity offset adjustment. Added to the converted Humidity value.
 */
typedef enum
{
	HUM_OFFSET_ADJUST_MASK				=   0xFF,						/*!<  HUM_OFFSET_ADJUST mask       	        	*/
	HUM_OFFSET_ADJUST_MINUS_25_RH		=   ( 1U << 7U ),				/*!<  HUM_OFFSET_ADJUST: –25   %RH  			*/
	HUM_OFFSET_ADJUST_12_5_RH			=   ( 1U << 6U ),				/*!<  HUM_OFFSET_ADJUST:  12.5 %RH  			*/
	HUM_OFFSET_ADJUST_6_3_RH			=   ( 1U << 5U ),				/*!<  HUM_OFFSET_ADJUST:   6.3 %RH 				*/
	HUM_OFFSET_ADJUST_3_1_RH			=   ( 1U << 4U ),				/*!<  HUM_OFFSET_ADJUST:   3.1 %RH  			*/
	HUM_OFFSET_ADJUST_1_6_RH			=   ( 1U << 3U ),				/*!<  HUM_OFFSET_ADJUST:   1.6 %RH  			*/
	HUM_OFFSET_ADJUST_0_8_RH			=   ( 1U << 2U ),				/*!<  HUM_OFFSET_ADJUST:   0.8 %RH  			*/
	HUM_OFFSET_ADJUST_0_4_RH			=   ( 1U << 1U ),				/*!<  HUM_OFFSET_ADJUST:   0.4 %RH 				*/
	HUM_OFFSET_ADJUST_0_2_RH			=   ( 1U << 0U ) 				/*!<  HUM_OFFSET_ADJUST:   0.2 %RH  			*/
} BH1790GLC_hum_offset_adjust_t;



/**
  * @brief   RESET_DRDY_INT_CONF REGISTER
  */
/* SOFT_RES <7>
 *    NOTE: EEPROM value reload and registers reset.
 */
typedef enum
{
	RESET_DRDY_INT_CONF_SOFT_RES_MASK	=   ( 1U << 7U ),				/*!<  SOFT_RES mask                          			*/
	RESET_DRDY_INT_CONF_SOFT_RES_NORMAL	=   ( 0U << 7U ),				/*!<  Normal Operation mode, this bit is self-clear		*/
	RESET_DRDY_INT_CONF_SOFT_RES_RESET	=   ( 1U << 7U )				/*!<  Soft Reset 		        						*/
} BH1790GLC_reset_drdy_int_conf_soft_res_t;


/* AMM <6:4>
 *    NOTE: EEPROM value reload and registers reset.
 */
typedef enum
{
	RESET_DRDY_INT_CONF_AMM_MASK		=   ( 0b111 << 4U ),			/*!<  AMM mask                          		*/
	RESET_DRDY_INT_CONF_AMM_DISABLED	=   ( 0b000 << 4U ),			/*!<  Disabled. Initiate measurement via I2C	*/
	RESET_DRDY_INT_CONF_AMM_0_008_HZ	=   ( 0b001 << 4U ),			/*!<  1/120Hz (1 samples every 2 minutes)		*/
	RESET_DRDY_INT_CONF_AMM_0_017_HZ	=   ( 0b010 << 4U ),			/*!<  1/60Hz (1 samples every minute)			*/
	RESET_DRDY_INT_CONF_AMM_0_1_HZ		=   ( 0b011 << 4U ),			/*!<  0.1Hz (1 samples every 10 seconds)		*/
	RESET_DRDY_INT_CONF_AMM_0_2_HZ		=   ( 0b100 << 4U ),			/*!<  0.2 Hz (1 samples every 5 second)			*/
	RESET_DRDY_INT_CONF_AMM_1_HZ		=   ( 0b101 << 4U ),			/*!<  1Hz (1 samples every second)				*/
	RESET_DRDY_INT_CONF_AMM_2_HZ		=   ( 0b110 << 4U ),			/*!<  2Hz (2 samples every second)				*/
	RESET_DRDY_INT_CONF_AMM_5_HZ		=   ( 0b111 << 4U ) 			/*!<  5Hz (5 samples every second)				*/
} BH1790GLC_reset_drdy_int_conf_amm_t;


/* HEAT_EN <3>
 *    NOTE: N/A.
 */
typedef enum
{
	RESET_DRDY_INT_CONF_HEAT_EN_MASK	=   ( 1U << 3U ),				/*!<  HEAT_EN mask                        		*/
	RESET_DRDY_INT_CONF_HEAT_EN_OFF		=   ( 0U << 3U ),				/*!<  Heater off								*/
	RESET_DRDY_INT_CONF_HEAT_EN_ON		=   ( 1U << 3U )				/*!<  Heater on									*/
} BH1790GLC_reset_drdy_int_conf_heat_en_t;


/* DRDY/INT_EN <2>
 *    NOTE: DRDY/INT_EN pin configuration.
 */
typedef enum
{
	RESET_DRDY_INT_CONF_DRDY_INT_EN_MASK	=   ( 1U << 2U ),			/*!<  DRDY/INT_EN mask                     		*/
	RESET_DRDY_INT_CONF_DRDY_INT_EN_HIGH_Z	=   ( 0U << 2U ),			/*!<  High Z									*/
	RESET_DRDY_INT_CONF_DRDY_INT_EN_ENABLED	=   ( 1U << 2U )			/*!<  Enable									*/
} BH1790GLC_reset_drdy_int_conf_drdr_int_en_t;


/* INT_POL <1>
 *    NOTE: Interrupt polarity.
 */
typedef enum
{
	RESET_DRDY_INT_CONF_INT_POL_MASK		=   ( 1U << 1U ),			/*!<  INT_POL mask                        		*/
	RESET_DRDY_INT_CONF_INT_POL_ACTIVE_LOW	=   ( 0U << 1U ),			/*!<  Active Low								*/
	RESET_DRDY_INT_CONF_INT_POL_ACTIVE_HIGH	=   ( 1U << 1U )			/*!<  Active High								*/
} BH1790GLC_reset_drdy_int_conf_int_pol_t;


/* INT_MODE <0>
 *    NOTE: Interrupt mode.
 */
typedef enum
{
	RESET_DRDY_INT_CONF_INT_MODE_MASK				=   ( 1U << 0U ),	/*!<  INT_MODE mask                        		*/
	RESET_DRDY_INT_CONF_INT_MODE_LEVEL_SENSITIVE	=   ( 0U << 0U ),	/*!<  Level sensitive							*/
	RESET_DRDY_INT_CONF_INT_MODE_COMPARATOR_MODE	=   ( 1U << 0U )	/*!<  Comparator mode							*/
} BH1790GLC_reset_drdy_int_conf_int_mode_t;



/**
  * @brief   MEASUREMENT CONFIGURATION REGISTER
  */
/* TRES <7:6>
 *    NOTE: Temperature resolution.
 */
typedef enum
{
    MEASUREMENT_CONF_TRES_MASK				=   ( 0b11 << 6U ),			/*!<  TRES mask                          		*/
	MEASUREMENT_CONF_TRES_14_BIT			=   ( 0b00 << 6U ),			/*!<  14 bit						            */
	MEASUREMENT_CONF_TRES_11_BIT			=   ( 0b01 << 6U ),			/*!<  11 bit						            */
	MEASUREMENT_CONF_TRES_9_BIT				=   ( 0b10 << 6U )  		/*!<   9 bit						            */
} BH1790GLC_measurement_configuration_tres_t;



/* HRES <5:4>
 *    NOTE: Humidity resolution.
 */
typedef enum
{
    MEASUREMENT_CONF_HRES_MASK				=   ( 0b11 << 4U ),			/*!<  HRES mask                          		*/
	MEASUREMENT_CONF_HRES_14_BIT			=   ( 0b00 << 4U ),			/*!<  14 bit						            */
	MEASUREMENT_CONF_HRES_11_BIT			=   ( 0b01 << 4U ),			/*!<  11 bit						            */
	MEASUREMENT_CONF_HRES_9_BIT				=   ( 0b10 << 4U )  		/*!<   9 bit						            */
} BH1790GLC_measurement_configuration_hres_t;



/* MEAS_CONF <2:1>
 *    NOTE: Measurement configuration.
 */
typedef enum
{
    MEASUREMENT_CONF_MEAS_CONF_MASK					=   ( 0b11 << 1U ),	/*!<  MEAS_CONF mask                       		*/
	MEASUREMENT_CONF_MEAS_CONF_HUMIDITY_TEMPERATURE	=   ( 0b00 << 1U ),	/*!<  Humidity + Temperature		            */
	MEASUREMENT_CONF_MEAS_CONF_TEMPERATURE_ONLY		=   ( 0b01 << 1U )	/*!<  Temperature only				            */
} BH1790GLC_measurement_configuration_meas_conf_t;



/* MEAS_TRIG <0>
 *    NOTE: Self-clearing bit when measurement completed.
 */
typedef enum
{
    MEASUREMENT_CONF_MEAS_TRIG_MASK					=   ( 1U << 0U ),	/*!<  MEAS_TRIG mask                       		*/
	MEASUREMENT_CONF_MEAS_TRIG_NO_ACTION			=   ( 0U << 0U ),	/*!<  no action						            */
	MEASUREMENT_CONF_MEAS_TRIG_START_MEASUREMENT	=   ( 1U << 0U )	/*!<  Start measurement				            */
} BH1790GLC_measurement_configuration_meas_trig_t;



/**
  * @brief   MANUFACTURER ID REGISTERS
  */
typedef enum
{
	MANUFACTURER_ID_LOW				=   0x49,							/*!<  MANUFACTURER ID low	              		*/
	MANUFACTURER_ID_HIGH			=   0x54							/*!<  MANUFACTURER ID high			            */
} BH1790GLC_manufacturer_ids_t;



/**
  * @brief   DEVICE ID REGISTERS
  */
typedef enum
{
	DEVICE_ID_LOW					=   0xD0,							/*!<  DEVICE ID low	              				*/
	DEVICE_ID_HIGH					=   0x07							/*!<  DEVICE ID high			           		*/
} BH1790GLC_device_ids_t;





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


