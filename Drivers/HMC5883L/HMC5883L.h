/**
 * @brief       HMC5883L.h
 * @details     3-Axis Digital Compass IC.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        12/October/2017
 * @version     12/October/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESSES.
  */
typedef enum
{
    HMC5883L_ADDRESS    =   0x1E                              /*!<   HMC5883L address                                       */
} HMC5883L_address_t;


// REGISTER LIST
/**
  * @brief   REGISTERS
  */
typedef enum
{
    HMC5883L_CONFIGURATION_REGISTER_A   =   0x00,           /*!<  Configuration Register A      Read/Write              */
    HMC5883L_CONFIGURATION_REGISTER_B   =   0x01,           /*!<  Configuration Register B      Read/Write              */
    HMC5883L_MODE_REGISTER              =   0x02,           /*!<  Mode Register                 Read/Write              */
    HMC5883L_DATA_OUTPUT_X_MSB          =   0x03,           /*!<  Data Output X MSB Register    Read                    */
    HMC5883L_DATA_OUTPUT_X_LSB          =   0x04,           /*!<  Data Output X LSB Register    Read                    */
    HMC5883L_DATA_OUTPUT_Z_MSB          =   0x05,           /*!<  Data Output Z MSB Register    Read                    */
    HMC5883L_DATA_OUTPUT_Z_LSB          =   0x06,           /*!<  Data Output Z LSB Register    Read                    */
    HMC5883L_DATA_OUTPUT_Y_MSB          =   0x07,           /*!<  Data Output Y MSB Register    Read                    */
    HMC5883L_DATA_OUTPUT_Y_LSB          =   0x08,           /*!<  Data Output Y LSB Register    Read                    */
    HMC5883L_STATUS_REGISTER            =   0x09,           /*!<  Status Register               Read                    */
    HMC5883L_IDENTIFICATION_REGISTER_A  =   0x0A,           /*!<  Identification Register A     Read                    */
    HMC5883L_IDENTIFICATION_REGISTER_B  =   0x0B,           /*!<  Identification Register B     Read                    */
    HMC5883L_IDENTIFICATION_REGISTER_C  =   0x0C            /*!<  Identification Register C     Read                    */
} HMC5883L_register_list_t;



// REGISTER BYTES
/**
  * @brief   CONFIGURATION REGISTER A
  */
// [ MA1 to MA0 ] Select number of samples averaged
typedef enum
{
    CONF_REG_A_SAMPLE_MASK       =   0x60,                      /*!<  Number of samples averaged mask                        */
    CONF_REG_A_SAMPLE_1          =   ( 0x00 << 5 ),             /*!<  Number of samples averaged 1 ( default )               */
    CONF_REG_A_SAMPLE_2          =   ( 0x01 << 5 ),             /*!<  Number of samples averaged 2                           */
    CONF_REG_A_SAMPLE_4          =   ( 0x02 << 5 ),             /*!<  Number of samples averaged 4                           */
    CONF_REG_A_SAMPLE_8          =   ( 0x03 << 5 )              /*!<  Number of samples averaged 8                           */
} HMC5883L_conf_reg_a_samples_t;


// [ DO2 to DO0 ] Data Output Rate Bits.
typedef enum
{
    CONF_REG_A_DATARATE_MASK        =   0x1C,                   /*!<  Typical Data Output Rate mask                           */
    CONF_REG_A_DATARATE_0_75_HZ     =   ( 0x00 << 2 ),          /*!<  Typical Data Output Rate 0.75Hz                         */
    CONF_REG_A_DATARATE_1_5_HZ      =   ( 0x01 << 2 ),          /*!<  Typical Data Output Rate 1.5Hz                          */
    CONF_REG_A_DATARATE_3_HZ        =   ( 0x02 << 2 ),          /*!<  Typical Data Output Rate 3Hz                            */
    CONF_REG_A_DATARATE_7_5_HZ      =   ( 0x03 << 2 ),          /*!<  Typical Data Output Rate 7.5Hz                          */
    CONF_REG_A_DATARATE_15_HZ       =   ( 0x04 << 2 ),          /*!<  Typical Data Output Rate 15Hz ( default )               */
    CONF_REG_A_DATARATE_30_HZ       =   ( 0x05 << 2 ),          /*!<  Typical Data Output Rate 30Hz                           */
    CONF_REG_A_DATARATE_75_HZ       =   ( 0x06 << 2 )           /*!<  Typical Data Output Rate 75Hz                           */
} HMC5883L_conf_reg_a_dor_t;


// [ MS1 to MS0 ] Measurement Configuration Bits.
typedef enum
{
    CONF_REG_A_MODE_MASK            =   0x03,                   /*!<  Measurement Configuration mask                           */
    CONF_REG_A_MODE_NORMAL          =   0x00,                   /*!<  Normal measurement configuration ( default )             */
    CONF_REG_A_MODE_POSITIVE_BIAS   =   0x01,                   /*!<  Positive bias configuration for X, Y, and Z axes         */
    CONF_REG_A_MODE_NEGATIVE_BOAS   =   0x02                    /*!<  Negative bias configuration for X, Y and Z axes          */
} HMC5883L_conf_reg_a_measurement_mode_t;




/**
  * @brief   CONFIGURATION REGISTER B
  */
// [ GN2 to GN0 ] Gain Configuration Bits. NOTE: The new gain setting is effective from the second measurement and on.
typedef enum
{
    CONF_REG_B_GAIN_MASK            =   0xE0,                   /*!<  Gain Configuration mask                                   */
    CONF_REG_B_GAIN_0_88_GA         =   ( 0x00 << 5 ),          /*!<  ± 0.88 Ga Digital Resolution: 0.73                        */
    CONF_REG_B_GAIN_1_3_GA          =   ( 0x01 << 5 ),          /*!<  ± 1.3 Ga  Digital Resolution: 0.92 ( default )            */
    CONF_REG_B_GAIN_1_9_GA          =   ( 0x02 << 5 ),          /*!<  ± 1.9 Ga  Digital Resolution: 1.22                        */
    CONF_REG_B_GAIN_2_5_GA          =   ( 0x03 << 5 ),          /*!<  ± 2.5 Ga  Digital Resolution: 1.52                        */
    CONF_REG_B_GAIN_4_0_GA          =   ( 0x04 << 5 ),          /*!<  ± 4.0 Ga  Digital Resolution: 2.27                        */
    CONF_REG_B_GAIN_4_7_GA          =   ( 0x05 << 5 ),          /*!<  ± 4.7 Ga  Digital Resolution: 2.56                        */
    CONF_REG_B_GAIN_5_6_GA          =   ( 0x06 << 5 ),          /*!<  ± 5.6 Ga  Digital Resolution: 3.03                        */
    CONF_REG_B_GAIN_8_1_GA          =   ( 0x07 << 5 )           /*!<  ± 8.1 Ga  Digital Resolution: 4.35                        */
} HMC5883L_conf_reg_b_gain_t;




/**
  * @brief   MODE REGISTER
  */
// [ HS ] Enable High Speed I2C, 3400kHz
typedef enum
{
    MODE_REG_HIGH_SPEED_I2C_MASK        =   0x80,               /*!<  High Speed I2C mask                                       */
    MODE_REG_HIGH_SPEED_I2C_ENABLED     =   ( 0x01 << 7 ),      /*!<  High Speed I2C enabled                                    */
    MODE_REG_HIGH_SPEED_I2C_DISABLED    =   ( 0x00 << 7 )       /*!<  High Speed I2C disabled                                   */
} HMC5883L_mode_register_high_speed_t;


// [ MD1 to MD0 ] Mode Select Bits
typedef enum
{
    MODE_REG_MODE_MASK              =   0x03,                   /*!<  Mode selection mask                                       */
    MODE_REG_MODE_CONTINUOUS        =   0x00,                   /*!<  Continuous-Measurement Mode                               */
    MODE_REG_MODE_SINGLE            =   0x01,                   /*!<  Single-Measurement Mode ( default )                       */
    MODE_REG_MODE_IDLE              =   0x02                    /*!<  Idle Mode                                                 */
} HMC5883L_mode_register_operation_mode_t;




/**
  * @brief   STATUS REGISTER
  */
// [ LOCK ] Data output register lock
typedef enum
{
    STATUS_REG_LOCK_ENABLED     =   ( 0x01 << 1 ),              /*!<  This bit is set                                           */
    STATUS_REG_LOCK_DISABLED    =   0xFD                        /*!<  This bit is not set                                       */
} HMC5883L_status_lock_t;


// [ RDY ] Ready Bit
typedef enum
{
    STATUS_REG_RDY_ENABLED     =   0x01,                       /*!<  This bit is set                                           */
    STATUS_REG_RDY_DISABLED    =   0xFE                        /*!<  This bit is not set                                       */
} HMC5883L_status_ready_t;




/**
  * @brief   IDENTIFICATION REGISTERS
  */
typedef enum
{
    ID_REGISTER_A       =       0x48,                       /*!<  Identification Register A: 'H'                            */
    ID_REGISTER_B       =       0x34,                       /*!<  Identification Register B: '4'                            */
    ID_REGISTER_C       =       0x33                        /*!<  Identification Register C: '3'                            */
} HMC5883L_identification_registers_t;






#ifndef HMC5883L_VECTOR_STRUCT_H
#define HMC5883L_VECTOR_STRUCT_H
typedef struct
{
    uint16_t DataOutput_X;
    uint16_t DataOutput_Y;
    uint16_t DataOutput_Z;

    uint8_t  IdentificationRegisterA;
    uint8_t  IdentificationRegisterB;
    uint8_t  IdentificationRegisterC;

    uint8_t  Status;
} HMC5883L_vector_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    HMC5883L_SUCCESS     =       0,
    HMC5883L_FAILURE     =       1
} HMC5883L_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
HMC5883L_status_t  HMC5883L_Conf                      ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_conf_reg_a_samples_t  mySamples, HMC5883L_conf_reg_a_dor_t myDataRate,
                                                        HMC5883L_conf_reg_a_measurement_mode_t myMeasurementMode, HMC5883L_conf_reg_b_gain_t myGain, HMC5883L_mode_register_high_speed_t myI2CMode,
                                                        HMC5883L_mode_register_operation_mode_t myOperationMode );
HMC5883L_status_t  HMC5883L_GetIdentificationRegister ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_register_list_t myID_reg, HMC5883L_vector_data_t* myID );
HMC5883L_status_t  HMC5883L_GetDataOutput             ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_vector_data_t* myData );
HMC5883L_status_t  HMC5883L_GetStatus                 ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_vector_data_t* myStatus );
HMC5883L_status_t  HMC5883L_ReadRegister              ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_register_list_t myRegister, uint8_t* myRegisterData );
HMC5883L_status_t  HMC5883L_SetNumSample              ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_conf_reg_a_samples_t mySamples );
HMC5883L_status_t  HMC5883L_SetDataRate               ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_conf_reg_a_dor_t myDataRate );
HMC5883L_status_t  HMC5883L_SetMeasurementConf        ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_conf_reg_a_measurement_mode_t myMeasurementMode );
HMC5883L_status_t  HMC5883L_SetGain                   ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_conf_reg_b_gain_t myGain );
HMC5883L_status_t  HMC5883L_SetMode                   ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_mode_register_operation_mode_t myOperationMode );
