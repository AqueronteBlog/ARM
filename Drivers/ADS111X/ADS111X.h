/**
 * @brief       ADS111X.h
 * @details     Ultra-Small, Low-Power, I2C-Compatible, 860-SPS, 16-Bit ADCs With Internal Reference, Oscillator, and Programmable Comparator.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        12/June/2020
 * @version     12/June/2020    The ORIGIN
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
  ADS111X_ADDRESS_GND   =   0b1001000,       /*!<   I2C slave address byte, ADDR = GND        */
  ADS111X_ADDRESS_VDD   =   0b1001001,       /*!<   I2C slave address byte, ADDR = VDD        */
  ADS111X_ADDRESS_SDA   =   0b1001010,       /*!<   I2C slave address byte, ADDR = SDA        */
  ADS111X_ADDRESS_SCL   =   0b1001011        /*!<   I2C slave address byte, ADDR = SCL        */
} ADS111X_addresses_t;



/**
  * @brief   REGISTER MAP
  */
typedef enum
{
  ADS111X_CONVERSION    =   0x00,           /*!<  Conversion register                           */
  ADS111X_CONFIG        =   0x01,           /*!<  Config register                               */
  ADS111X_LO_THRESH     =   0x02,           /*!<  Lo threshold register                         */
  ADS111X_HI_THRESH     =   0x03,           /*!<  Hi threshold register                         */
  ADS111X_RESET_COMMAND =   0x06            /*!<  Reset command ( with a general call )         */
} ADS111X_register_map_t;



/**
  * @brief   DEVICE.
  *           NOTE: The user MUST define which device to use: ADS1013, ADS1014 or ADS1015.
  */
typedef enum
{
    DEVICE_ADS1113    =   0x00,             /*!<  Device: ADS1113                                */
    DEVICE_ADS1114    =   0x01,             /*!<  Device: ADS1114                                */
    DEVICE_ADS1115    =   0x02              /*!<  Device: ADS1115                                */
} ADS111X_device_t;



/**
  * @brief   CONVERSION REGISTER. ( Default: 0x0000 )
  *           NOTE: The 16-bit Conversion register contains the result of the last conversion in binary two's complement format.
					Following power-up, the Conversion register is cleared to 0, and remains 0 until the first conversion is completed.
  */
/* D <15:4>
 *    NOTE: 16-bit conversion result.
 */
typedef enum
{
    CONVERSION_D_MASK   =   0xFFFF  	/*!<  D mask                                                    */
} ADS111X_conversion_t;



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
} ADS111X_config_os_t;


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
} ADS111X_config_mux_t;


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
} ADS111X_config_pga_t;


/* MODE <8>
 *    NOTE: Device operating mode.
 */
typedef enum
{ 
    CONFIG_MODE_MASK                    =   ( 1U << 8U ),       /*!<  MODE mask                                                    */
    CONFIG_MODE_CONTINUOUS_CONVERSION   =   ( 0U << 8U ),       /*!<  Continuous-conversion mode                                   */
    CONFIG_MODE_SINGLE_SHOT             =   ( 1U << 8U )        /*!<  Single-shot mode or power-down state             [ Default ] */
} ADS111X_config_mode_t;


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
} ADS111X_config_dr_t;


/* COMP_MODE <4>
 *    NOTE: Comparator mode ( ADS1114 and ADS1115 only )
 */
typedef enum
{ 
    CONFIG_COMP_MODE_MASK                   =   ( 1U << 4U ),   /*!<  COMP_MODE mask                                                */
    CONFIG_COMP_MODE_TRADITIONAL_COMPARATOR =   ( 0U << 4U ),   /*!<  Traditional comparator                            [ Default ] */
    CONFIG_COMP_MODE_WINDOW_COMPARATOR      =   ( 1U << 4U )    /*!<  Window comparator                                             */
} ADS111X_config_comp_mode_t;


/* COMP_POL <3>
 *    NOTE: Comparator polarity ( ADS1114 and ADS1115 only )
 */
typedef enum
{ 
    CONFIG_COMP_POL_MASK                    =   ( 1U << 3U ),   /*!<  COMP_POL mask                                                 */
    CONFIG_COMP_POL_ACTIVE_LOW              =   ( 0U << 3U ),   /*!<  Active low                                        [ Default ] */
    CONFIG_COMP_POL_ACTIVE_HIGH             =   ( 1U << 3U )    /*!<  Active high                                                   */
} ADS111X_config_comp_pol_t;


/* COMP_LAT <2>
 *    NOTE: Latching comparator ( ADS1114 and ADS1115 only )
 */
typedef enum
{ 
    CONFIG_COMP_LAT_MASK                    =   ( 1U << 2U ),   /*!<  COMP_LAT mask                                                 */
    CONFIG_COMP_LAT_NONLATCHING_COMPARATOR  =   ( 0U << 2U ),   /*!<  Nonlatching comparator                            [ Default ] */
    CONFIG_COMP_LAT_LATCHING_COMPARATOR     =   ( 1U << 2U )    /*!<  Latching comparator                                           */
} ADS111X_config_comp_lat_t;


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
} ADS111X_config_comp_que_t;



/**
  * @brief   LO_THRESH REGISTER. ( Default: 0x8000 )
  */
/* LO_THRESH <15:0>
 *    NOTE: N/A.
 */
typedef enum
{
    LO_THRESH_MASK      =   0xFFFF            /*!<  LO_THRESH mask                                                */
} ADS111X_lo_thresh_t;



/**
  * @brief   HI_THRESH REGISTER. ( Default: 0x7FFF )
  */
/* HI_THRESH <15:0>
 *    NOTE: N/A.
 */
typedef enum
{
    HI_THRESH_MASK      =   0xFFFF            /*!<  HI_THRESH mask                                                */
} ADS111X_hi_thresh_t;





#ifndef ADS111X_VECTOR_STRUCT_H
#define ADS111X_VECTOR_STRUCT_H
typedef struct
{
  /* Output  */
  float     conversion;                     /*!<  Conversion value                                        */
  int16_t   raw_conversion;                 /*!<  Raw conversion value                                    */

  /* Configuration  */
  ADS111X_config_os_t         os;           /*!<  Operational status                                      */
  ADS111X_config_mux_t        mux;          /*!<  Input multiplexer configuration (ADS1015 only)          */
  ADS111X_config_pga_t        pga;          /*!<  Programmable gain amplifier configuration (not ADS1013) */
  ADS111X_config_mode_t       mode;         /*!<  Device operating mode                                   */
  ADS111X_config_dr_t         dr;           /*!<  Data rate                                               */
  ADS111X_config_comp_mode_t  comp_mode;    /*!<  Comparator mode (ADS1014 and ADS1015 only)              */
  ADS111X_config_comp_pol_t   comp_pol;     /*!<  Comparator polarity (ADS1014 and ADS1015 only)          */
  ADS111X_config_comp_lat_t   comp_lat;     /*!<  Latching comparator (ADS1014 and ADS1015 only)          */
  ADS111X_config_comp_que_t   comp_que;     /*!<  Comparator queue and disable (ADS1014 and ADS1015 only) */

  /* Thresholds  */
  int16_t           lo_thresh;              /*!<  Low threshold value                                     */
  int16_t           hi_thresh;              /*!<  High threshold value                                    */

  /* Device identification   */
  ADS111X_device_t  device;                 /*!<  Device. The user MUST identify the device               */
} ADS111X_data_t;
#endif




/**
  * @brief   ERROR STATUS. INTERNAL CONSTANTS
  */
typedef enum
{
    ADS111X_SUCCESS               =   0U,   /*!<  I2C communication success                       */
    ADS111X_FAILURE               =   1U,   /*!<  I2C communication failure                       */
    ADS111X_DEVICE_NOT_SUPPORTED  =   2U,   /*!<  Device not supported                            */
    ADS111X_VALUE_OUT_OF_RANGE    =   3U,   /*!<  Value out of range                              */
    ADS111X_DATA_CORRUPTED        =   4U    /*!<  D and lo/hi threshold data                      */
} ADS111X_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
ADS111X_status_t ADS111X_Init                   ( I2C_parameters_t myI2Cparameters, ADS111X_data_t myADS111X  );

/** It triggers a softreset.
  */
ADS111X_status_t ADS111X_SoftReset              ( I2C_parameters_t myI2Cparameters                            );

/** It gets the raw conversion value.
  */
ADS111X_status_t ADS111X_GetRawConversion       ( I2C_parameters_t myI2Cparameters, ADS111X_data_t* myRawD    );

/** It gets the conversion value.
  */
ADS111X_status_t ADS111X_GetConversion          ( I2C_parameters_t myI2Cparameters, ADS111X_data_t* myD       );

/** It starts a new single conversion.
  */
ADS111X_status_t ADS111X_StartSingleConversion  ( I2C_parameters_t myI2Cparameters                            );

/** It checks if the device is not currently performing a conversion.
  */
ADS111X_status_t ADS111X_GetOS                  ( I2C_parameters_t myI2Cparameters, ADS111X_data_t* myADS111X );

/** It sets input multiplexer configuration ( ADS1015 only ).
  */
ADS111X_status_t ADS111X_SetMux                 ( I2C_parameters_t myI2Cparameters, ADS111X_data_t myADS111X  );

/** It gets input multiplexer configuration ( ADS1015 only ).
  */
ADS111X_status_t ADS111X_GetMux                 ( I2C_parameters_t myI2Cparameters, ADS111X_data_t* myADS111X );

/** It sets programmable gain amplifier ( not ADS1013 ).
  */
ADS111X_status_t ADS111X_SetGain                ( I2C_parameters_t myI2Cparameters, ADS111X_data_t myPGA      );

/** It gets programmable gain amplifier ( not ADS1013 ).
  */
ADS111X_status_t ADS111X_GetGain                ( I2C_parameters_t myI2Cparameters, ADS111X_data_t* myPGA     );

/** It sets the device operating mode.
  */
ADS111X_status_t ADS111X_SetMode                ( I2C_parameters_t myI2Cparameters, ADS111X_data_t myMode     );

/** It gets the device operating mode.
  */
ADS111X_status_t ADS111X_GetMode                ( I2C_parameters_t myI2Cparameters, ADS111X_data_t* myMode    );

/** It sets the data rate.
  */
ADS111X_status_t ADS111X_SetDataRate            ( I2C_parameters_t myI2Cparameters, ADS111X_data_t myDR       );

/** It gets the data rate.
  */
ADS111X_status_t ADS111X_GetDataRate            ( I2C_parameters_t myI2Cparameters, ADS111X_data_t* myDR      );

/** It sets the comparator configuration.
  */
ADS111X_status_t ADS111X_SetComparator          ( I2C_parameters_t myI2Cparameters, ADS111X_data_t myCOMP     );

/** It gets the comparator configuration.
  */
ADS111X_status_t ADS111X_GetComparator          ( I2C_parameters_t myI2Cparameters, ADS111X_data_t* myCOMP    );

/** It sets the low threshold value.
  */
ADS111X_status_t ADS111X_SetLowThresholdValue   ( I2C_parameters_t myI2Cparameters, ADS111X_data_t myLoThres  );

/** It gets the low threshold value.
  */
ADS111X_status_t ADS111X_GetLowThresholdValue   ( I2C_parameters_t myI2Cparameters, ADS111X_data_t* myLoThres );

/** It sets the high threshold value.
  */
ADS111X_status_t ADS111X_SetHighThresholdValue  ( I2C_parameters_t myI2Cparameters, ADS111X_data_t myHiThres  );

/** It gets the high threshold value.
  */
ADS111X_status_t ADS111X_GetHighThresholdValue  ( I2C_parameters_t myI2Cparameters, ADS111X_data_t* myHiThres );


