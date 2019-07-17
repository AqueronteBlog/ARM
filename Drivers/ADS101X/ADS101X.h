/**
 * @brief       ADS101X.h
 * @details     Ultra-Small, Low-Power, I2C-Compatible, 3.3-kSPS, 12-Bit ADCs. With Internal Reference, Oscillator, and Programmable Comparator.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/July/2019
 * @version     17/July/2019    The ORIGIN
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
  ADS101X_ADDRESS_GND   =   0b1001000,       /*!<   I2C slave address byte, ADDR = GND        */
  ADS101X_ADDRESS_VDD   =   0b1001001,       /*!<   I2C slave address byte, ADDR = VDD        */
  ADS101X_ADDRESS_SDA   =   0b1001010,       /*!<   I2C slave address byte, ADDR = SDA        */
  ADS101X_ADDRESS_SCL   =   0b1001011        /*!<   I2C slave address byte, ADDR = SCL        */
} ADS101X_addresses_t;



/**
  * @brief   REGISTER MAP
  */
typedef enum
{
  ADS101X_CONVERSION  =   0x00,             /*!<  Conversion register                           */
  ADS101X_CONFIG      =   0x01,             /*!<  Config register                               */
  ADS101X_LO_THRESH   =   0x02,             /*!<  Lo threshold register                         */
  ADS101X_HI_THRESH   =   0x03              /*!<  Hi threshold register                         */
} ADS101X_register_map_t;



/**
  * @brief   CONVERSION REGISTER. ( Default: 0x0000 )
  *           NOTE: The 16-bit Conversion register contains the result of the last conversion in binary two's complement format.
  *                 Following power-up, the Conversion register is cleared to 0, and remains 0 until the first conversion is completed.
  */
/* D <15:4>
 *    NOTE: 12-bit conversion result.
 */
typedef enum
{
    CONVERSION_D_MASK   =   ( 0b111111111111 << 4U )  /*!<  D mask                                                    */
} ADS101X_conversion_t;



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
    CONFIG_OS_MASK      =   ( 1U << 15U ),            /*!<  OS mask                                                     */
    CONFIG_OS_BUSY      =   ( 1U << 15U ),            /*!<  Device is currently performing a conversion                 */
    CONFIG_OS_NOT_BUSY  =   ( 0U << 15U )             /*!<  Device is not currently performing a conversion [ Default ] */
} ADS101X_config_os_t;


/* MUX <14:12>
 *    NOTE: Input multiplexer configuration ( ADS1015 only ).
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
} ADS101X_config_mux_t;







#ifndef ADS101X_VECTOR_STRUCT_H
#define ADS101X_VECTOR_STRUCT_H
typedef struct
{
  /* Output registers  */
  int32_t   rawPressure;                      /*!<  Raw pressure                      */
  int16_t   rawTemperature;                   /*!<  Raw temperature                   */

  float     pressure;                         /*!<  Pressure in mbar                  */
  float     temperature;                      /*!<  Temperature in Celsius degree     */

  

  /* Device identification   */
  uint8_t                       deviceID;     /*!<  Device ID                                         */
} ADS101X_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    ADS101X_SUCCESS     =       0,
    ADS101X_FAILURE     =       1
} ADS101X_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
ADS101X_status_t ADS101X_Init                     ( I2C_parameters_t myI2Cparameters                                        );


