/**
 * @brief       PCF8574.h
 * @details     Remote 8-bit I/O expander for I2C-bus with interrupt.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        11/October/2017
 * @version     11/October/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESSES. NOTE: There are two version: PCF8574 and PCF8574A with different address only.
  */
typedef enum
{
    PCF8574_ADDRESS_0     =   0x20,                   /*!<   A2 A1 A0: 000                                            */
    PCF8574_ADDRESS_1     =   0x21,                   /*!<   A2 A1 A0: 001                                            */
    PCF8574_ADDRESS_2     =   0x22,                   /*!<   A2 A1 A0: 010                                            */
    PCF8574_ADDRESS_3     =   0x23,                   /*!<   A2 A1 A0: 011                                            */
    PCF8574_ADDRESS_4     =   0x24,                   /*!<   A2 A1 A0: 100                                            */
    PCF8574_ADDRESS_5     =   0x25,                   /*!<   A2 A1 A0: 101                                            */
    PCF8574_ADDRESS_6     =   0x26,                   /*!<   A2 A1 A0: 110                                            */
    PCF8574_ADDRESS_7     =   0x27,                   /*!<   A2 A1 A0: 111                                            */

    PCF8574A_ADDRESS_0    =   0x38,                   /*!<   A2 A1 A0: 000                                            */
    PCF8574A_ADDRESS_1    =   0x39,                   /*!<   A2 A1 A0: 001                                            */
    PCF8574A_ADDRESS_2    =   0x3A,                   /*!<   A2 A1 A0: 010                                            */
    PCF8574A_ADDRESS_3    =   0x3B,                   /*!<   A2 A1 A0: 011                                            */
    PCF8574A_ADDRESS_4    =   0x3C,                   /*!<   A2 A1 A0: 100                                            */
    PCF8574A_ADDRESS_5    =   0x3D,                   /*!<   A2 A1 A0: 101                                            */
    PCF8574A_ADDRESS_6    =   0x3E,                   /*!<   A2 A1 A0: 110                                            */
    PCF8574A_ADDRESS_7    =   0x3F                    /*!<   A2 A1 A0: 111                                            */
} PCF8574_address_t;


// DATA BYTE
/**
  * @brief   PIN STATUS
  */
typedef enum
{
    PCF8574_INPUT        =   1,                        /*!<  PCF8574 INPUT                                          */
    PCF8574_OUTPUT_HIGH  =   1,                        /*!<  PCF8574 OUTPUT HIGH                                    */
    PCF8574_OUTPUT_LOW   =   0                         /*!<  PCF8574 OUTPUT LOW                                     */
} PCF8574_pin_status_t;


/**
  * @brief   PIN NUMBER
  */
typedef enum
{
    PCF8574_P0           =   0,                        /*!<  PCF8574 P0 pin                                         */
    PCF8574_P1           =   1,                        /*!<  PCF8574 P1 pin                                         */
    PCF8574_P2           =   2,                        /*!<  PCF8574 P2 pin                                         */
    PCF8574_P3           =   3,                        /*!<  PCF8574 P3 pin                                         */
    PCF8574_P4           =   4,                        /*!<  PCF8574 P4 pin                                         */
    PCF8574_P5           =   5,                        /*!<  PCF8574 P5 pin                                         */
    PCF8574_P6           =   6,                        /*!<  PCF8574 P6 pin                                         */
    PCF8574_P7           =   7,                        /*!<  PCF8574 P7 pin                                         */
} PCF8574_pin_number_t;





#ifndef PCF8574_VECTOR_STRUCT_H
#define PCF8574_VECTOR_STRUCT_H
typedef struct
{
    uint8_t data;
} PCF8574_vector_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    PCF8574_SUCCESS     =       0,
    PCF8574_FAILURE     =       1
} PCF8574_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
PCF8574_status_t  PCF8574_SetADC                ( NRF_TWI_Type* myinstance, PCF8574_address_t myPCF8574Addr, PCF8574_analog_input_programming_t myAnalogInputs, PCF8574_auto_increment_status_t myAutoIncrement, PCF8574_channel_number_t myADCchannel );
PCF8574_status_t  PCF8574_ReadADC               ( NRF_TWI_Type* myinstance, PCF8574_address_t myPCF8574Addr, PCF8574_vector_data_t* myADC_Data );
PCF8574_status_t  PCF8574_SetDAC                ( NRF_TWI_Type* myinstance, PCF8574_address_t myPCF8574Addr, PCF8574_dac_status_t myDAC_Status );
PCF8574_status_t  PCF8574_NewDACValue           ( NRF_TWI_Type* myinstance, PCF8574_address_t myPCF8574Addr, uint8_t myNewDACValue );
