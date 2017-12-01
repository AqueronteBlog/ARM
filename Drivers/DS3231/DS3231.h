/**
 * @brief       DS3231.h
 * @details     Extremely Accurate I2C-Integrated RTC/TCXO/Crystal.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        1/December/2017
 * @version     1/December/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESSES. NOTE: There are two version: DS3231 and DS3231A with different address only,
  *                             its functionality remains the same.
  */
typedef enum
{
    DS3231_ADDRESS_0     =   0x20,                   /*!<   A2 A1 A0: 000                                            */
    DS3231_ADDRESS_1     =   0x21,                   /*!<   A2 A1 A0: 001                                            */
    DS3231_ADDRESS_2     =   0x22,                   /*!<   A2 A1 A0: 010                                            */
    DS3231_ADDRESS_3     =   0x23,                   /*!<   A2 A1 A0: 011                                            */
    DS3231_ADDRESS_4     =   0x24,                   /*!<   A2 A1 A0: 100                                            */
    DS3231_ADDRESS_5     =   0x25,                   /*!<   A2 A1 A0: 101                                            */
    DS3231_ADDRESS_6     =   0x26,                   /*!<   A2 A1 A0: 110                                            */
    DS3231_ADDRESS_7     =   0x27,                   /*!<   A2 A1 A0: 111                                            */

    DS3231A_ADDRESS_0    =   0x38,                   /*!<   A2 A1 A0: 000                                            */
    DS3231A_ADDRESS_1    =   0x39,                   /*!<   A2 A1 A0: 001                                            */
    DS3231A_ADDRESS_2    =   0x3A,                   /*!<   A2 A1 A0: 010                                            */
    DS3231A_ADDRESS_3    =   0x3B,                   /*!<   A2 A1 A0: 011                                            */
    DS3231A_ADDRESS_4    =   0x3C,                   /*!<   A2 A1 A0: 100                                            */
    DS3231A_ADDRESS_5    =   0x3D,                   /*!<   A2 A1 A0: 101                                            */
    DS3231A_ADDRESS_6    =   0x3E,                   /*!<   A2 A1 A0: 110                                            */
    DS3231A_ADDRESS_7    =   0x3F                    /*!<   A2 A1 A0: 111                                            */
} DS3231_address_t;


// DATA BYTE
/**
  * @brief   PIN NUMBER
  */
typedef enum
{
    DS3231_P0              =   0,                            /*!<  DS3231 P0 INPUT                                       */
    DS3231_P1              =   1,                            /*!<  DS3231 P1 INPUT                                       */
    DS3231_P2              =   2,                            /*!<  DS3231 P2 INPUT                                       */
    DS3231_P3              =   3,                            /*!<  DS3231 P3 INPUT                                       */
    DS3231_P4              =   4,                            /*!<  DS3231 P4 INPUT                                       */
    DS3231_P5              =   5,                            /*!<  DS3231 P5 INPUT                                       */
    DS3231_P6              =   6,                            /*!<  DS3231 P6 INPUT                                       */
    DS3231_P7              =   7                             /*!<  DS3231 P7 INPUT                                       */
} DS3231_pin_number_t;


/**
  * @brief   PIN MASK
  */
typedef enum
{
    DS3231_P0_MASK          =   0b00000001,                  /*!<  DS3231 P0 INPUT                                       */
    DS3231_P1_MASK          =   0b00000010,                  /*!<  DS3231 P1 INPUT                                       */
    DS3231_P2_MASK          =   0b00000100,                  /*!<  DS3231 P2 INPUT                                       */
    DS3231_P3_MASK          =   0b00001000,                  /*!<  DS3231 P3 INPUT                                       */
    DS3231_P4_MASK          =   0b00010000,                  /*!<  DS3231 P4 INPUT                                       */
    DS3231_P5_MASK          =   0b00100000,                  /*!<  DS3231 P5 INPUT                                       */
    DS3231_P6_MASK          =   0b01000000,                  /*!<  DS3231 P6 INPUT                                       */
    DS3231_P7_MASK          =   0b10000000                   /*!<  DS3231 P7 INPUT                                       */
} DS3231_pin_mask_t;



/**
  * @brief   PIN CONFIGURATION
  */
typedef enum
{
    DS3231_P0_INPUT        =   ( 1 << DS3231_P0 ),           /*!<  DS3231 P0 INPUT                                       */
    DS3231_P0_OUTPUT_HIGH  =   ( 1 << DS3231_P0 ),           /*!<  DS3231 P0 OUTPUT HIGH                                 */
    DS3231_P0_OUTPUT_LOW   =   ( 0 << DS3231_P0 ),           /*!<  DS3231 P0 OUTPUT LOW                                  */

    DS3231_P1_INPUT        =   ( 1 << DS3231_P1 ),           /*!<  DS3231 P1 INPUT                                       */
    DS3231_P1_OUTPUT_HIGH  =   ( 1 << DS3231_P1 ),           /*!<  DS3231 P1 OUTPUT HIGH                                 */
    DS3231_P1_OUTPUT_LOW   =   ( 0 << DS3231_P1 ),           /*!<  DS3231 P1 OUTPUT LOW                                  */

    DS3231_P2_INPUT        =   ( 1 << DS3231_P2 ),           /*!<  DS3231 P2 INPUT                                       */
    DS3231_P2_OUTPUT_HIGH  =   ( 1 << DS3231_P2 ),           /*!<  DS3231 P2 OUTPUT HIGH                                 */
    DS3231_P2_OUTPUT_LOW   =   ( 0 << DS3231_P2 ),           /*!<  DS3231 P2 OUTPUT LOW                                  */

    DS3231_P3_INPUT        =   ( 1 << DS3231_P3 ),           /*!<  DS3231 P3 INPUT                                       */
    DS3231_P3_OUTPUT_HIGH  =   ( 1 << DS3231_P3 ),           /*!<  DS3231 P3 OUTPUT HIGH                                 */
    DS3231_P3_OUTPUT_LOW   =   ( 0 << DS3231_P3 ),           /*!<  DS3231 P3 OUTPUT LOW                                  */

    DS3231_P4_INPUT        =   ( 1 << DS3231_P4 ),           /*!<  DS3231 P4 INPUT                                       */
    DS3231_P4_OUTPUT_HIGH  =   ( 1 << DS3231_P4 ),           /*!<  DS3231 P4 OUTPUT HIGH                                 */
    DS3231_P4_OUTPUT_LOW   =   ( 0 << DS3231_P4 ),           /*!<  DS3231 P4 OUTPUT LOW                                  */

    DS3231_P5_INPUT        =   ( 1 << DS3231_P5 ),           /*!<  DS3231 P5 INPUT                                       */
    DS3231_P5_OUTPUT_HIGH  =   ( 1 << DS3231_P5 ),           /*!<  DS3231 P5 OUTPUT HIGH                                 */
    DS3231_P5_OUTPUT_LOW   =   ( 0 << DS3231_P5 ),           /*!<  DS3231 P5 OUTPUT LOW                                  */

    DS3231_P6_INPUT        =   ( 1 << DS3231_P6 ),           /*!<  DS3231 P6 INPUT                                       */
    DS3231_P6_OUTPUT_HIGH  =   ( 1 << DS3231_P6 ),           /*!<  DS3231 P6 OUTPUT HIGH                                 */
    DS3231_P6_OUTPUT_LOW   =   ( 0 << DS3231_P6 ),           /*!<  DS3231 P6 OUTPUT LOW                                  */

    DS3231_P7_INPUT        =   ( 1 << DS3231_P7 ),           /*!<  DS3231 P7 INPUT                                       */
    DS3231_P7_OUTPUT_HIGH  =   ( 1 << DS3231_P7 ),           /*!<  DS3231 P7 OUTPUT HIGH                                 */
    DS3231_P7_OUTPUT_LOW   =   ( 0 << DS3231_P7 )            /*!<  DS3231 P7 OUTPUT LOW                                  */
} DS3231_pin_configuration_t;



/**
  * @brief   PIN STATUS
  */
typedef enum
{
    DS3231_P0_HIGH  =   ( 1 << DS3231_P0 ),                  /*!<  DS3231 P0 STATUS HIGH                                 */
    DS3231_P0_LOW   =   ( 0 << DS3231_P0 ),                  /*!<  DS3231 P0 STATUS LOW                                  */

    DS3231_P1_HIGH  =   ( 1 << DS3231_P1 ),                  /*!<  DS3231 P1 STATUS HIGH                                 */
    DS3231_P1_LOW   =   ( 0 << DS3231_P1 ),                  /*!<  DS3231 P1 STATUS LOW                                  */

    DS3231_P2_HIGH  =   ( 1 << DS3231_P2 ),                  /*!<  DS3231 P2 STATUS HIGH                                 */
    DS3231_P2_LOW   =   ( 0 << DS3231_P2 ),                  /*!<  DS3231 P2 STATUS LOW                                  */

    DS3231_P3_HIGH  =   ( 1 << DS3231_P3 ),                  /*!<  DS3231 P3 STATUS HIGH                                 */
    DS3231_P3_LOW   =   ( 0 << DS3231_P3 ),                  /*!<  DS3231 P3 STATUS LOW                                  */

    DS3231_P4_HIGH  =   ( 1 << DS3231_P4 ),                  /*!<  DS3231 P4 STATUS HIGH                                 */
    DS3231_P4_LOW   =   ( 0 << DS3231_P4 ),                  /*!<  DS3231 P4 STATUS LOW                                  */

    DS3231_P5_HIGH  =   ( 1 << DS3231_P5 ),                  /*!<  DS3231 P5 STATUS HIGH                                 */
    DS3231_P5_LOW   =   ( 0 << DS3231_P5 ),                  /*!<  DS3231 P5 STATUS LOW                                  */

    DS3231_P6_HIGH  =   ( 1 << DS3231_P6 ),                  /*!<  DS3231 P6 STATUS HIGH                                 */
    DS3231_P6_LOW   =   ( 0 << DS3231_P6 ),                  /*!<  DS3231 P6 STATUS LOW                                  */

    DS3231_P7_HIGH  =   ( 1 << DS3231_P7 ),                  /*!<  DS3231 P7 STATUS HIGH                                 */
    DS3231_P7_LOW   =   ( 0 << DS3231_P7 )                   /*!<  DS3231 P7 STATUS LOW                                  */
} DS3231_pin_status_t;





#ifndef DS3231_VECTOR_STRUCT_H
#define DS3231_VECTOR_STRUCT_H
typedef struct
{
    uint8_t data;
} DS3231_vector_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    DS3231_SUCCESS     =       0,
    DS3231_FAILURE     =       1
} DS3231_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
DS3231_status_t  DS3231_Init      ( I2C_parameters_t myI2Cparameters );
DS3231_status_t  DS3231_SetPins   ( I2C_parameters_t myI2Cparameters, DS3231_vector_data_t  myConfDATA );
DS3231_status_t  DS3231_ReadPins  ( I2C_parameters_t myI2Cparameters, DS3231_vector_data_t* myReadDATA );
