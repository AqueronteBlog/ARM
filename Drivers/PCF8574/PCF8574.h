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
  * @brief   DEFAULT ADDRESSES. NOTE: There are two version: PCF8574 and PCF8574A with different address only,
  *                             its functionality remains the same.
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
  * @brief   PIN NUMBER
  */
typedef enum
{
    PCF8574_P0              =   0,                            /*!<  PCF8574 P0 INPUT                                       */
    PCF8574_P1              =   1,                            /*!<  PCF8574 P1 INPUT                                       */
    PCF8574_P2              =   2,                            /*!<  PCF8574 P2 INPUT                                       */
    PCF8574_P3              =   3,                            /*!<  PCF8574 P3 INPUT                                       */
    PCF8574_P4              =   4,                            /*!<  PCF8574 P4 INPUT                                       */
    PCF8574_P5              =   5,                            /*!<  PCF8574 P5 INPUT                                       */
    PCF8574_P6              =   6,                            /*!<  PCF8574 P6 INPUT                                       */
    PCF8574_P7              =   7                             /*!<  PCF8574 P7 INPUT                                       */
} PCF8574_pin_number_t;


/**
  * @brief   PIN MASK
  */
typedef enum
{
    PCF8574_P0_MASK          =   0b00000001,                  /*!<  PCF8574 P0 INPUT                                       */
    PCF8574_P1_MASK          =   0b00000010,                  /*!<  PCF8574 P1 INPUT                                       */
    PCF8574_P2_MASK          =   0b00000100,                  /*!<  PCF8574 P2 INPUT                                       */
    PCF8574_P3_MASK          =   0b00001000,                  /*!<  PCF8574 P3 INPUT                                       */
    PCF8574_P4_MASK          =   0b00010000,                  /*!<  PCF8574 P4 INPUT                                       */
    PCF8574_P5_MASK          =   0b00100000,                  /*!<  PCF8574 P5 INPUT                                       */
    PCF8574_P6_MASK          =   0b01000000,                  /*!<  PCF8574 P6 INPUT                                       */
    PCF8574_P7_MASK          =   0b10000000                   /*!<  PCF8574 P7 INPUT                                       */
} PCF8574_pin_mask_t;



/**
  * @brief   PIN CONFIGURATION
  */
typedef enum
{
    PCF8574_P0_INPUT        =   ( 1 << PCF8574_P0 ),           /*!<  PCF8574 P0 INPUT                                       */
    PCF8574_P0_OUTPUT_HIGH  =   ( 1 << PCF8574_P0 ),           /*!<  PCF8574 P0 OUTPUT HIGH                                 */
    PCF8574_P0_OUTPUT_LOW   =   ( 0 << PCF8574_P0 ),           /*!<  PCF8574 P0 OUTPUT LOW                                  */

    PCF8574_P1_INPUT        =   ( 1 << PCF8574_P1 ),           /*!<  PCF8574 P1 INPUT                                       */
    PCF8574_P1_OUTPUT_HIGH  =   ( 1 << PCF8574_P1 ),           /*!<  PCF8574 P1 OUTPUT HIGH                                 */
    PCF8574_P1_OUTPUT_LOW   =   ( 0 << PCF8574_P1 ),           /*!<  PCF8574 P1 OUTPUT LOW                                  */

    PCF8574_P2_INPUT        =   ( 1 << PCF8574_P2 ),           /*!<  PCF8574 P2 INPUT                                       */
    PCF8574_P2_OUTPUT_HIGH  =   ( 1 << PCF8574_P2 ),           /*!<  PCF8574 P2 OUTPUT HIGH                                 */
    PCF8574_P2_OUTPUT_LOW   =   ( 0 << PCF8574_P2 ),           /*!<  PCF8574 P2 OUTPUT LOW                                  */

    PCF8574_P3_INPUT        =   ( 1 << PCF8574_P3 ),           /*!<  PCF8574 P3 INPUT                                       */
    PCF8574_P3_OUTPUT_HIGH  =   ( 1 << PCF8574_P3 ),           /*!<  PCF8574 P3 OUTPUT HIGH                                 */
    PCF8574_P3_OUTPUT_LOW   =   ( 0 << PCF8574_P3 ),           /*!<  PCF8574 P3 OUTPUT LOW                                  */

    PCF8574_P4_INPUT        =   ( 1 << PCF8574_P4 ),           /*!<  PCF8574 P4 INPUT                                       */
    PCF8574_P4_OUTPUT_HIGH  =   ( 1 << PCF8574_P4 ),           /*!<  PCF8574 P4 OUTPUT HIGH                                 */
    PCF8574_P4_OUTPUT_LOW   =   ( 0 << PCF8574_P4 ),           /*!<  PCF8574 P4 OUTPUT LOW                                  */

    PCF8574_P5_INPUT        =   ( 1 << PCF8574_P5 ),           /*!<  PCF8574 P5 INPUT                                       */
    PCF8574_P5_OUTPUT_HIGH  =   ( 1 << PCF8574_P5 ),           /*!<  PCF8574 P5 OUTPUT HIGH                                 */
    PCF8574_P5_OUTPUT_LOW   =   ( 0 << PCF8574_P5 ),           /*!<  PCF8574 P5 OUTPUT LOW                                  */

    PCF8574_P6_INPUT        =   ( 1 << PCF8574_P6 ),           /*!<  PCF8574 P6 INPUT                                       */
    PCF8574_P6_OUTPUT_HIGH  =   ( 1 << PCF8574_P6 ),           /*!<  PCF8574 P6 OUTPUT HIGH                                 */
    PCF8574_P6_OUTPUT_LOW   =   ( 0 << PCF8574_P6 ),           /*!<  PCF8574 P6 OUTPUT LOW                                  */

    PCF8574_P7_INPUT        =   ( 1 << PCF8574_P7 ),           /*!<  PCF8574 P7 INPUT                                       */
    PCF8574_P7_OUTPUT_HIGH  =   ( 1 << PCF8574_P7 ),           /*!<  PCF8574 P7 OUTPUT HIGH                                 */
    PCF8574_P7_OUTPUT_LOW   =   ( 0 << PCF8574_P7 )            /*!<  PCF8574 P7 OUTPUT LOW                                  */
} PCF8574_pin_configuration_t;



/**
  * @brief   PIN STATUS
  */
typedef enum
{
    PCF8574_P0_HIGH  =   ( 1 << PCF8574_P0 ),                  /*!<  PCF8574 P0 STATUS HIGH                                 */
    PCF8574_P0_LOW   =   ( 0 << PCF8574_P0 ),                  /*!<  PCF8574 P0 STATUS LOW                                  */

    PCF8574_P1_HIGH  =   ( 1 << PCF8574_P1 ),                  /*!<  PCF8574 P1 STATUS HIGH                                 */
    PCF8574_P1_LOW   =   ( 0 << PCF8574_P1 ),                  /*!<  PCF8574 P1 STATUS LOW                                  */

    PCF8574_P2_HIGH  =   ( 1 << PCF8574_P2 ),                  /*!<  PCF8574 P2 STATUS HIGH                                 */
    PCF8574_P2_LOW   =   ( 0 << PCF8574_P2 ),                  /*!<  PCF8574 P2 STATUS LOW                                  */

    PCF8574_P3_HIGH  =   ( 1 << PCF8574_P3 ),                  /*!<  PCF8574 P3 STATUS HIGH                                 */
    PCF8574_P3_LOW   =   ( 0 << PCF8574_P3 ),                  /*!<  PCF8574 P3 STATUS LOW                                  */

    PCF8574_P4_HIGH  =   ( 1 << PCF8574_P4 ),                  /*!<  PCF8574 P4 STATUS HIGH                                 */
    PCF8574_P4_LOW   =   ( 0 << PCF8574_P4 ),                  /*!<  PCF8574 P4 STATUS LOW                                  */

    PCF8574_P5_HIGH  =   ( 1 << PCF8574_P5 ),                  /*!<  PCF8574 P5 STATUS HIGH                                 */
    PCF8574_P5_LOW   =   ( 0 << PCF8574_P5 ),                  /*!<  PCF8574 P5 STATUS LOW                                  */

    PCF8574_P6_HIGH  =   ( 1 << PCF8574_P6 ),                  /*!<  PCF8574 P6 STATUS HIGH                                 */
    PCF8574_P6_LOW   =   ( 0 << PCF8574_P6 ),                  /*!<  PCF8574 P6 STATUS LOW                                  */

    PCF8574_P7_HIGH  =   ( 1 << PCF8574_P7 ),                  /*!<  PCF8574 P7 STATUS HIGH                                 */
    PCF8574_P7_LOW   =   ( 0 << PCF8574_P7 )                   /*!<  PCF8574 P7 STATUS LOW                                  */
} PCF8574_pin_status_t;





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
PCF8574_status_t  PCF8574_Init      ( I2C_parameters_t myI2Cparameters );
PCF8574_status_t  PCF8574_SetPins   ( I2C_parameters_t myI2Cparameters, PCF8574_vector_data_t  myConfDATA );
PCF8574_status_t  PCF8574_ReadPins  ( I2C_parameters_t myI2Cparameters, PCF8574_vector_data_t* myReadDATA );
