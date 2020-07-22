/**
 * @brief       SFM4100.h
 * @details     Low-cost Digital Mass Flow Meter for Gases.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/July/2020
 * @version     22/July/2020    The ORIGIN
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
  SFM4100_ADDRESS_GND   =   0b1001000,       /*!<   I2C slave address byte, ADDR = GND        */
  SFM4100_ADDRESS_VDD   =   0b1001001,       /*!<   I2C slave address byte, ADDR = VDD        */
  SFM4100_ADDRESS_SDA   =   0b1001010,       /*!<   I2C slave address byte, ADDR = SDA        */
  SFM4100_ADDRESS_SCL   =   0b1001011        /*!<   I2C slave address byte, ADDR = SCL        */
} SFM4100_addresses_t;



/**
  * @brief   REGISTER MAP
  */
typedef enum
{
  SFM4100_CONVERSION    =   0x00,           /*!<  Conversion register                           */
  SFM4100_CONFIG        =   0x01,           /*!<  Config register                               */
  SFM4100_LO_THRESH     =   0x02,           /*!<  Lo threshold register                         */
  SFM4100_HI_THRESH     =   0x03,           /*!<  Hi threshold register                         */
  SFM4100_RESET_COMMAND =   0x06            /*!<  Reset command ( with a general call )         */
} SFM4100_register_map_t;



/**
  * @brief   DEVICE.
  *           NOTE: The user MUST define which device to use: ADS1013, ADS1014 or ADS1015.
  */
typedef enum
{
    DEVICE_ADS1113    =   0x00,             /*!<  Device: ADS1113                                */
    DEVICE_ADS1114    =   0x01,             /*!<  Device: ADS1114                                */
    DEVICE_ADS1115    =   0x02              /*!<  Device: ADS1115                                */
} SFM4100_device_t;



/**
  * @brief   CONFIG REGISTER. ( Default: 0x8583 )
  *           NOTE: The 16-bit Config register is used to control the operating mode, input selection, data rate, full-scale range, and
  *                 comparator modes.
  */
/* OS <15>
 *    NOTE: Operational status or single-shot conversion start.
 */
typedef enum
{
    CONFIG_OS_MASK      =   ( 1U << 15U ),            /*!<  OS mask                                                     													*/
    CONFIG_OS_BUSY      =   ( 1U << 15U ),            /*!<  Device is not currently performing a conversion/Start a single conversion (when in power-down state) [Default]	*/
    CONFIG_OS_NOT_BUSY  =   ( 0U << 15U )             /*!<  Device is currently performing a conversion	 																	*/
} SFM4100_config_os_t;


/* MUX <14:12>
 *    NOTE: Input multiplexer configuration ( ADS1115 only ).
 */
typedef enum
{ 
    CONFIG_MUX_MASK                     =   ( 0b111 << 12U ),   /*!<  MUX mask                                                     */
    CONFIG_MUX_AINP_AIN0_AND_AINN_AIN1  =   ( 0b000 << 12U ),   /*!<  AINP = AIN0 and AINN = AIN1                      [ Default ] */
    CONFIG_MUX_AINP_AIN0_AND_AINN_AIN3  =   ( 0b001 << 12U ),   /*!<  AINP = AIN0 and AINN = AIN3                                  */
    CONFIG_MUX_AINP_AIN1_AND_AINN_AIN3  =   ( 0b010 << 12U ),   /*!<  AINP = AIN1 and AINN = AIN3                                  */
    CONFIG_MUX_AINP_AIN2_AND_AINN_AIN3  =   ( 0b011 << 12U ),   /*!<  AINP = AIN2 and AINN = AIN3                                  */
    CONFIG_MUX_AINP_AIN0_AND_AINN_GND   =   ( 0b100 << 12U ),   /*!<  AINP = AIN0 and AINN = GND                                   */
    CONFIG_MUX_AINP_AIN1_AND_AINN_GND   =   ( 0b101 << 12U ),   /*!<  AINP = AIN1 and AINN = GND                                   */
    CONFIG_MUX_AINP_AIN2_AND_AINN_GND   =   ( 0b110 << 12U ),   /*!<  AINP = AIN2 and AINN = GND                                   */
    CONFIG_MUX_AINP_AIN3_AND_AINN_GND   =   ( 0b111 << 12U )    /*!<  AINP = AIN3 and AINN = GND                                   */
} SFM4100_config_mux_t;


/* PGA <11:9>
 *    NOTE: Programmable gain amplifier configuration ( These bits serve NO function on the ADS1113 ).
 */
typedef enum
{ 
    CONFIG_PGA_MASK                     =   ( 0b111 << 9U ),   /*!<  PGA mask                                                     */
    CONFIG_PGA_FSR_6_144_V              =   ( 0b000 << 9U ),   /*!<  FSR = ±6.144 V                                               */
    CONFIG_PGA_FSR_4_096_V              =   ( 0b001 << 9U ),   /*!<  FSR = ±4.096 V                                               */
    CONFIG_PGA_FSR_2_048_V              =   ( 0b010 << 9U ),   /*!<  FSR = ±2.048 V                                   [ Default ] */
    CONFIG_PGA_FSR_1_024_V              =   ( 0b011 << 9U ),   /*!<  FSR = ±1.024 V                                               */
    CONFIG_PGA_FSR_0_512_V              =   ( 0b100 << 9U ),   /*!<  FSR = ±0.512 V                                               */
    CONFIG_PGA_FSR_0_256_V              =   ( 0b101 << 9U )    /*!<  FSR = ±0.256 V                                               */
} SFM4100_config_pga_t;


/* MODE <8>
 *    NOTE: Device operating mode.
 */
typedef enum
{ 
    CONFIG_MODE_MASK                    =   ( 1U << 8U ),       /*!<  MODE mask                                                    */
    CONFIG_MODE_CONTINUOUS_CONVERSION   =   ( 0U << 8U ),       /*!<  Continuous-conversion mode                                   */
    CONFIG_MODE_SINGLE_SHOT             =   ( 1U << 8U )        /*!<  Single-shot mode or power-down state             [ Default ] */
} SFM4100_config_mode_t;


/* DR <7:5>
 *    NOTE: Data rate.
 */
typedef enum
{ 
    CONFIG_DR_MASK                      =   ( 0b111 << 5U ),    /*!<  DR mask                                                       */
    CONFIG_DR_8_SPS                   	=   ( 0b000 << 5U ),    /*!<    8 SPS                                                       */
    CONFIG_DR_16_SPS                   	=   ( 0b001 << 5U ),    /*!<   16 SPS                                                       */
    CONFIG_DR_32_SPS                   	=   ( 0b010 << 5U ),    /*!<   32 SPS                                                       */
    CONFIG_DR_64_SPS                   	=   ( 0b011 << 5U ),    /*!<   64 SPS                                                       */
    CONFIG_DR_128_SPS                  	=   ( 0b100 << 5U ),    /*!<  128 SPS                                          	[ Default ] */
    CONFIG_DR_250_SPS                  	=   ( 0b101 << 5U ),    /*!<  250 SPS                                           	        */
    CONFIG_DR_475_SPS                  	=   ( 0b110 << 5U ),    /*!<  475 SPS                                               	    */
	CONFIG_DR_860_SPS                  	=   ( 0b111 << 5U )     /*!<  860 SPS                                                      	*/
} SFM4100_config_dr_t;


/* COMP_MODE <4>
 *    NOTE: Comparator mode ( ADS1114 and ADS1115 only )
 */
typedef enum
{ 
    CONFIG_COMP_MODE_MASK                   =   ( 1U << 4U ),   /*!<  COMP_MODE mask                                                */
    CONFIG_COMP_MODE_TRADITIONAL_COMPARATOR =   ( 0U << 4U ),   /*!<  Traditional comparator                            [ Default ] */
    CONFIG_COMP_MODE_WINDOW_COMPARATOR      =   ( 1U << 4U )    /*!<  Window comparator                                             */
} SFM4100_config_comp_mode_t;


/* COMP_POL <3>
 *    NOTE: Comparator polarity ( ADS1114 and ADS1115 only )
 */
typedef enum
{ 
    CONFIG_COMP_POL_MASK                    =   ( 1U << 3U ),   /*!<  COMP_POL mask                                                 */
    CONFIG_COMP_POL_ACTIVE_LOW              =   ( 0U << 3U ),   /*!<  Active low                                        [ Default ] */
    CONFIG_COMP_POL_ACTIVE_HIGH             =   ( 1U << 3U )    /*!<  Active high                                                   */
} SFM4100_config_comp_pol_t;


/* COMP_LAT <2>
 *    NOTE: Latching comparator ( ADS1114 and ADS1115 only )
 */
typedef enum
{ 
    CONFIG_COMP_LAT_MASK                    =   ( 1U << 2U ),   /*!<  COMP_LAT mask                                                 */
    CONFIG_COMP_LAT_NONLATCHING_COMPARATOR  =   ( 0U << 2U ),   /*!<  Nonlatching comparator                            [ Default ] */
    CONFIG_COMP_LAT_LATCHING_COMPARATOR     =   ( 1U << 2U )    /*!<  Latching comparator                                           */
} SFM4100_config_comp_lat_t;


/* COMP_QUE <1:0>
 *    NOTE: Comparator queue and disable ( ADS1114 and ADS1115 only )
 */
typedef enum
{ 
    CONFIG_COMP_QUE_MASK                          =   ( 0b11 << 0U ), /*!<  COMP_QUE mask                                                           */
    CONFIG_COMP_QUE_ASSERT_AFTER_ONE_CONVERSION   =   ( 0b00 << 0U ), /*!<  Assert after one conversion                                             */
    CONFIG_COMP_QUE_ASSERT_AFTER_TWO_CONVERSION   =   ( 0b01 << 0U ), /*!<  Assert after two conversions                                            */
    CONFIG_COMP_QUE_ASSERT_AFTER_FOUR_CONVERSION  =   ( 0b10 << 0U ), /*!<  Assert after four conversions                                           */
    CONFIG_COMP_QUE_DISABLED                      =   ( 0b11 << 0U )  /*!<  Disable comparator and set ALERT/RDY pin to high-impedance  [ Default ] */
} SFM4100_config_comp_que_t;



/**
  * @brief   LO_THRESH REGISTER. ( Default: 0x8000 )
  */
/* LO_THRESH <15:0>
 *    NOTE: N/A.
 */
typedef enum
{
    LO_THRESH_MASK      =   0xFFFF            /*!<  LO_THRESH mask                                                */
} SFM4100_lo_thresh_t;



/**
  * @brief   HI_THRESH REGISTER. ( Default: 0x7FFF )
  */
/* HI_THRESH <15:0>
 *    NOTE: N/A.
 */
typedef enum
{
    HI_THRESH_MASK      =   0xFFFF            /*!<  HI_THRESH mask                                                */
} SFM4100_hi_thresh_t;





#ifndef SFM4100_VECTOR_STRUCT_H
#define SFM4100_VECTOR_STRUCT_H
/* Configuration parameters	 */
typedef struct
{
  SFM4100_config_os_t         os;           /*!<  Operational status                                      */
  SFM4100_config_mux_t        mux;          /*!<  Input multiplexer configuration (ADS1015 only)          */
  SFM4100_config_pga_t        pga;          /*!<  Programmable gain amplifier configuration (not ADS1013) */
  SFM4100_config_mode_t       mode;         /*!<  Device operating mode                                   */
  SFM4100_config_dr_t         dr;           /*!<  Data rate                                               */
  SFM4100_config_comp_mode_t  comp_mode;    /*!<  Comparator mode (ADS1014 and ADS1015 only)              */
  SFM4100_config_comp_pol_t   comp_pol;     /*!<  Comparator polarity (ADS1014 and ADS1015 only)          */
  SFM4100_config_comp_lat_t   comp_lat;     /*!<  Latching comparator (ADS1014 and ADS1015 only)          */
  SFM4100_config_comp_que_t   comp_que;     /*!<  Comparator queue and disable (ADS1014 and ADS1015 only) */
} SFM4100_config_t;


/* Thresholds: High and low thresholds	 */
typedef struct
{
	int16_t		lo_thresh;       			/*!<  Low threshold value                        	*/
	int16_t		hi_thresh;       			/*!<  High threshold value                     		*/
} SFM4100_thresh_t;


/* Result Conversion: Raw value and conversion value	 */
typedef struct
{
	float     conversion;               	/*!<  Conversion value                         		*/
	int16_t   raw_conversion;       		/*!<  Raw conversion value                        	*/
} SFM4100_conversion_t;



/* USER: User's global variables	 */
typedef struct
{
  /* Output  */
  SFM4100_conversion_t	conversion;       	/*!<  Conversion values                        		*/

  /* Configuration  */
  SFM4100_config_t		config;           	/*!<  Configuration register                     	*/

  /* Thresholds  */
  SFM4100_thresh_t		thresh;       		/*!<  High/Low threshold values                		*/

  /* Device identification   */
  SFM4100_device_t  	device;          	/*!<  Device. The user MUST identify the device		*/
} SFM4100_data_t;
#endif




/**
  * @brief   ERROR STATUS. INTERNAL CONSTANTS
  */
typedef enum
{
    SFM4100_SUCCESS               =   0U,   /*!<  I2C communication success                       */
    SFM4100_FAILURE               =   1U,   /*!<  I2C communication failure                       */
    SFM4100_DEVICE_NOT_SUPPORTED  =   2U,   /*!<  Device not supported                            */
    SFM4100_VALUE_OUT_OF_RANGE    =   3U,   /*!<  Value out of range                              */
    SFM4100_DATA_CORRUPTED        =   4U    /*!<  D and lo/hi threshold data                      */
} SFM4100_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
SFM4100_status_t SFM4100_Init                   ( I2C_parameters_t myI2Cparameters, SFM4100_data_t mySFM4100  		);

/** It triggers a softreset.
  */
SFM4100_status_t SFM4100_SoftReset              ( I2C_parameters_t myI2Cparameters                            		);

/** It gets the raw conversion value.
  */
SFM4100_status_t SFM4100_GetRawConversion       ( I2C_parameters_t myI2Cparameters, SFM4100_conversion_t* myRawD	);

/** It gets the conversion value.
  */
SFM4100_status_t SFM4100_GetConversion          ( I2C_parameters_t myI2Cparameters, SFM4100_data_t* myD       		);

/** It starts a new single conversion.
  */
SFM4100_status_t SFM4100_StartSingleConversion  ( I2C_parameters_t myI2Cparameters                            		);

/** It checks if the device is not currently performing a conversion.
  */
SFM4100_status_t SFM4100_GetOS                  ( I2C_parameters_t myI2Cparameters, SFM4100_config_t* mySFM4100 	);

/** It sets input multiplexer configuration ( ADS1015 only ).
  */
SFM4100_status_t SFM4100_SetMux                 ( I2C_parameters_t myI2Cparameters, SFM4100_data_t mySFM4100  		);

/** It gets input multiplexer configuration ( ADS1015 only ).
  */
SFM4100_status_t SFM4100_GetMux                 ( I2C_parameters_t myI2Cparameters, SFM4100_data_t* mySFM4100 		);

/** It sets programmable gain amplifier ( not ADS1013 ).
  */
SFM4100_status_t SFM4100_SetGain                ( I2C_parameters_t myI2Cparameters, SFM4100_data_t myPGA      		);

/** It gets programmable gain amplifier ( not ADS1013 ).
  */
SFM4100_status_t SFM4100_GetGain                ( I2C_parameters_t myI2Cparameters, SFM4100_data_t* myPGA     		);

/** It sets the device operating mode.
  */
SFM4100_status_t SFM4100_SetMode                ( I2C_parameters_t myI2Cparameters, SFM4100_config_t myMode     	);

/** It gets the device operating mode.
  */
SFM4100_status_t SFM4100_GetMode                ( I2C_parameters_t myI2Cparameters, SFM4100_config_t* myMode   		);

/** It sets the data rate.
  */
SFM4100_status_t SFM4100_SetDataRate            ( I2C_parameters_t myI2Cparameters, SFM4100_config_t myDR       	);

/** It gets the data rate.
  */
SFM4100_status_t SFM4100_GetDataRate            ( I2C_parameters_t myI2Cparameters, SFM4100_config_t* myDR     		);

/** It sets the comparator configuration.
  */
SFM4100_status_t SFM4100_SetComparator          ( I2C_parameters_t myI2Cparameters, SFM4100_data_t myCOMP     		);

/** It gets the comparator configuration.
  */
SFM4100_status_t SFM4100_GetComparator          ( I2C_parameters_t myI2Cparameters, SFM4100_data_t* myCOMP    		);

/** It sets the low threshold value.
  */
SFM4100_status_t SFM4100_SetLowThresholdValue   ( I2C_parameters_t myI2Cparameters, SFM4100_thresh_t myLoThres  	);

/** It gets the low threshold value.
  */
SFM4100_status_t SFM4100_GetLowThresholdValue   ( I2C_parameters_t myI2Cparameters, SFM4100_thresh_t* myLoThres 	);

/** It sets the high threshold value.
  */
SFM4100_status_t SFM4100_SetHighThresholdValue  ( I2C_parameters_t myI2Cparameters, SFM4100_thresh_t myHiThres  	);

/** It gets the high threshold value.
  */
SFM4100_status_t SFM4100_GetHighThresholdValue  ( I2C_parameters_t myI2Cparameters, SFM4100_thresh_t* myHiThres 	);


