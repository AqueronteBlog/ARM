/**
 * @brief       PCF8591.h
 * @details     8-bit A/D and D/A converter.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        22/September/2017
 * @version     22/September/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
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
    PCF8591_ADDRESS_0     =   0x48,                   /*!<   A2 A1 A0: 000                                            */
    PCF8591_ADDRESS_1     =   0x49,                   /*!<   A2 A1 A0: 001                                            */
    PCF8591_ADDRESS_2     =   0x4A,                   /*!<   A2 A1 A0: 010                                            */
    PCF8591_ADDRESS_3     =   0x4B,                   /*!<   A2 A1 A0: 011                                            */
    PCF8591_ADDRESS_4     =   0x4C,                   /*!<   A2 A1 A0: 100                                            */
    PCF8591_ADDRESS_5     =   0x4D,                   /*!<   A2 A1 A0: 101                                            */
    PCF8591_ADDRESS_6     =   0x4E,                   /*!<   A2 A1 A0: 110                                            */
    PCF8591_ADDRESS_7     =   0x4F                    /*!<   A2 A1 A0: 111                                            */
} PCF8591_address_t;


// CONTROL BYTE
/**
  * @brief   ANALOG OUTPUT ENABLE FLAG
  */
typedef enum
{
    PCF8591_DAC_ENABLED        =   1,                                /*!<  PCF8591 DAC is enabled.                                */
    PCF8591_DAC_DISABLE        =   0                                 /*!<  PCF8591 DAC is disabled                                */
} PCF8591_dac_status_t;



/**
  * @brief   ANALOG INPUT PROGRAMMING
  */
typedef enum
{
    PCF8591_FOUR_SINGLE_ENDED_INPUTS             =   0,              /*!<  PCF8591 Scale in kg.                                   */
    PCF8591_THREE_DIFFERENTIAL_INPUTS            =   1,              /*!<  PCF8591 Scale in  g.                                   */
    PCF8591_SINGLE_ENDED_AND_DIFFERENTIAL_MIXED  =   2,              /*!<  PCF8591 Scale in mg.                                   */
    PCF8591_TWO_DIFFERENTIAL_INPUTS              =   3               /*!<  PCF8591 Scale in ug.                                   */
} PCF8591_analog_input_programming_t;



/**
  * @brief   AUTO-INCREMENT FLAG
  */
typedef enum
{
    PCF8591_AUTO_INCREMENT_ENABLED               =   1,              /*!<  PCF8591 Auto-increment is enabled.                     */
    PCF8591_AUTO_INCREMENT_DISABLED              =   0               /*!<  PCF8591 Auto-increment is disabled                     */
} PCF8591_auto_increment_status_t;



/**
  * @brief   A/D CHANNEL NUMBER
  */
typedef enum
{
    PCF8591_CHANNEL_0                            =   0,              /*!<  PCF8591 Channel 0 Active                               */
    PCF8591_CHANNEL_1                            =   1,              /*!<  PCF8591 Channel 1 Active                               */
    PCF8591_CHANNEL_2                            =   2,              /*!<  PCF8591 Channel 2 Active                               */
    PCF8591_CHANNEL_3                            =   3               /*!<  PCF8591 Channel 3 Active                               */
} PCF8591_channel_number_t;



#ifndef VECTOR_STRUCT_H
#define VECTOR_STRUCT_H
typedef struct
{
    uint8_t ADC_Channel_0;
    uint8_t ADC_Channel_1;
    uint8_t ADC_Channel_2;
    uint8_t ADC_Channel_3;
} PCF8591_vector_data_t;

typedef struct
{
    uint32_t DAC_New_Value;
} PCF8591_vector_new_dac_value_t;
#endif




uint8_t _ANALOG_INPUT_PROGRAMMING;
uint8_t _AUTO_INCREMENT_STATUS;
uint8_t _CHANNEL_NUMBER;
uint8_t _DAC_STATUS;


/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    PCF8591_SUCCESS     =       0,
    PCF8591_FAILURE     =       1
} PCF8591_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
PCF8591_status_t  PCF8591_SetADC                ( NRF_TWI_Type* myinstance, PCF8591_address_t myPCF8591Addr, PCF8591_analog_input_programming_t myAnalogInputs, PCF8591_auto_increment_status_t myAutoIncrement, PCF8591_channel_number_t myADCchannel );
PCF8591_status_t  PCF8591_ReadADC               ( NRF_TWI_Type* myinstance, PCF8591_address_t myPCF8591Addr, PCF8591_vector_data_t* myADC_Data );

PCF8591_status_t  PCF8591_SetDAC                ( NRF_TWI_Type* myinstance, PCF8591_address_t myPCF8591Addr, PCF8591_dac_status_t myDAC_Status );
PCF8591_status_t  PCF8591_NewDACValue           ( NRF_TWI_Type* myinstance, PCF8591_address_t myPCF8591Addr, uint8_t myNewDACValue );
