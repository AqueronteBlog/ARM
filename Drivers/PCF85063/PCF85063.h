/**
 * @brief       PCF85063.h
 * @details     Tiny Real-Time Clock/calendar.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/January/2019
 * @version     22/January/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ). All rights reserved.
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESSES. NOTE: There are two version: PCF85063 and PCF85063A with different address only,
  *                             its functionality remains the same.
  */
typedef enum
{
    PCF85063_ADDRESS_0     =   0x20,                   /*!<   A2 A1 A0: 000                                            */
    PCF85063_ADDRESS_1     =   0x21,                   /*!<   A2 A1 A0: 001                                            */
    PCF85063_ADDRESS_2     =   0x22,                   /*!<   A2 A1 A0: 010                                            */
    PCF85063_ADDRESS_3     =   0x23,                   /*!<   A2 A1 A0: 011                                            */
    PCF85063_ADDRESS_4     =   0x24,                   /*!<   A2 A1 A0: 100                                            */
    PCF85063_ADDRESS_5     =   0x25,                   /*!<   A2 A1 A0: 101                                            */
    PCF85063_ADDRESS_6     =   0x26,                   /*!<   A2 A1 A0: 110                                            */
    PCF85063_ADDRESS_7     =   0x27,                   /*!<   A2 A1 A0: 111                                            */

    PCF85063A_ADDRESS_0    =   0x38,                   /*!<   A2 A1 A0: 000                                            */
    PCF85063A_ADDRESS_1    =   0x39,                   /*!<   A2 A1 A0: 001                                            */
    PCF85063A_ADDRESS_2    =   0x3A,                   /*!<   A2 A1 A0: 010                                            */
    PCF85063A_ADDRESS_3    =   0x3B,                   /*!<   A2 A1 A0: 011                                            */
    PCF85063A_ADDRESS_4    =   0x3C,                   /*!<   A2 A1 A0: 100                                            */
    PCF85063A_ADDRESS_5    =   0x3D,                   /*!<   A2 A1 A0: 101                                            */
    PCF85063A_ADDRESS_6    =   0x3E,                   /*!<   A2 A1 A0: 110                                            */
    PCF85063A_ADDRESS_7    =   0x3F                    /*!<   A2 A1 A0: 111                                            */
} PCF85063_address_t;


// DATA BYTE
/**
  * @brief   PIN NUMBER
  */
typedef enum
{
    PCF85063_P0              =   0,                            /*!<  PCF85063 P0 INPUT                                       */
    PCF85063_P1              =   1,                            /*!<  PCF85063 P1 INPUT                                       */
    PCF85063_P2              =   2,                            /*!<  PCF85063 P2 INPUT                                       */
    PCF85063_P3              =   3,                            /*!<  PCF85063 P3 INPUT                                       */
    PCF85063_P4              =   4,                            /*!<  PCF85063 P4 INPUT                                       */
    PCF85063_P5              =   5,                            /*!<  PCF85063 P5 INPUT                                       */
    PCF85063_P6              =   6,                            /*!<  PCF85063 P6 INPUT                                       */
    PCF85063_P7              =   7                             /*!<  PCF85063 P7 INPUT                                       */
} PCF85063_pin_number_t;


/**
  * @brief   PIN MASK
  */
typedef enum
{
    PCF85063_P0_MASK          =   0b00000001,                  /*!<  PCF85063 P0 INPUT                                       */
    PCF85063_P1_MASK          =   0b00000010,                  /*!<  PCF85063 P1 INPUT                                       */
    PCF85063_P2_MASK          =   0b00000100,                  /*!<  PCF85063 P2 INPUT                                       */
    PCF85063_P3_MASK          =   0b00001000,                  /*!<  PCF85063 P3 INPUT                                       */
    PCF85063_P4_MASK          =   0b00010000,                  /*!<  PCF85063 P4 INPUT                                       */
    PCF85063_P5_MASK          =   0b00100000,                  /*!<  PCF85063 P5 INPUT                                       */
    PCF85063_P6_MASK          =   0b01000000,                  /*!<  PCF85063 P6 INPUT                                       */
    PCF85063_P7_MASK          =   0b10000000                   /*!<  PCF85063 P7 INPUT                                       */
} PCF85063_pin_mask_t;



/**
  * @brief   PIN CONFIGURATION
  */
typedef enum
{
    PCF85063_P0_INPUT        =   ( 1 << PCF85063_P0 ),           /*!<  PCF85063 P0 INPUT                                       */
    PCF85063_P0_OUTPUT_HIGH  =   ( 1 << PCF85063_P0 ),           /*!<  PCF85063 P0 OUTPUT HIGH                                 */
    PCF85063_P0_OUTPUT_LOW   =   ( 0 << PCF85063_P0 ),           /*!<  PCF85063 P0 OUTPUT LOW                                  */

    PCF85063_P1_INPUT        =   ( 1 << PCF85063_P1 ),           /*!<  PCF85063 P1 INPUT                                       */
    PCF85063_P1_OUTPUT_HIGH  =   ( 1 << PCF85063_P1 ),           /*!<  PCF85063 P1 OUTPUT HIGH                                 */
    PCF85063_P1_OUTPUT_LOW   =   ( 0 << PCF85063_P1 ),           /*!<  PCF85063 P1 OUTPUT LOW                                  */

    PCF85063_P2_INPUT        =   ( 1 << PCF85063_P2 ),           /*!<  PCF85063 P2 INPUT                                       */
    PCF85063_P2_OUTPUT_HIGH  =   ( 1 << PCF85063_P2 ),           /*!<  PCF85063 P2 OUTPUT HIGH                                 */
    PCF85063_P2_OUTPUT_LOW   =   ( 0 << PCF85063_P2 ),           /*!<  PCF85063 P2 OUTPUT LOW                                  */

    PCF85063_P3_INPUT        =   ( 1 << PCF85063_P3 ),           /*!<  PCF85063 P3 INPUT                                       */
    PCF85063_P3_OUTPUT_HIGH  =   ( 1 << PCF85063_P3 ),           /*!<  PCF85063 P3 OUTPUT HIGH                                 */
    PCF85063_P3_OUTPUT_LOW   =   ( 0 << PCF85063_P3 ),           /*!<  PCF85063 P3 OUTPUT LOW                                  */

    PCF85063_P4_INPUT        =   ( 1 << PCF85063_P4 ),           /*!<  PCF85063 P4 INPUT                                       */
    PCF85063_P4_OUTPUT_HIGH  =   ( 1 << PCF85063_P4 ),           /*!<  PCF85063 P4 OUTPUT HIGH                                 */
    PCF85063_P4_OUTPUT_LOW   =   ( 0 << PCF85063_P4 ),           /*!<  PCF85063 P4 OUTPUT LOW                                  */

    PCF85063_P5_INPUT        =   ( 1 << PCF85063_P5 ),           /*!<  PCF85063 P5 INPUT                                       */
    PCF85063_P5_OUTPUT_HIGH  =   ( 1 << PCF85063_P5 ),           /*!<  PCF85063 P5 OUTPUT HIGH                                 */
    PCF85063_P5_OUTPUT_LOW   =   ( 0 << PCF85063_P5 ),           /*!<  PCF85063 P5 OUTPUT LOW                                  */

    PCF85063_P6_INPUT        =   ( 1 << PCF85063_P6 ),           /*!<  PCF85063 P6 INPUT                                       */
    PCF85063_P6_OUTPUT_HIGH  =   ( 1 << PCF85063_P6 ),           /*!<  PCF85063 P6 OUTPUT HIGH                                 */
    PCF85063_P6_OUTPUT_LOW   =   ( 0 << PCF85063_P6 ),           /*!<  PCF85063 P6 OUTPUT LOW                                  */

    PCF85063_P7_INPUT        =   ( 1 << PCF85063_P7 ),           /*!<  PCF85063 P7 INPUT                                       */
    PCF85063_P7_OUTPUT_HIGH  =   ( 1 << PCF85063_P7 ),           /*!<  PCF85063 P7 OUTPUT HIGH                                 */
    PCF85063_P7_OUTPUT_LOW   =   ( 0 << PCF85063_P7 )            /*!<  PCF85063 P7 OUTPUT LOW                                  */
} PCF85063_pin_configuration_t;



/**
  * @brief   PIN STATUS
  */
typedef enum
{
    PCF85063_P0_HIGH  =   ( 1 << PCF85063_P0 ),                  /*!<  PCF85063 P0 STATUS HIGH                                 */
    PCF85063_P0_LOW   =   ( 0 << PCF85063_P0 ),                  /*!<  PCF85063 P0 STATUS LOW                                  */

    PCF85063_P1_HIGH  =   ( 1 << PCF85063_P1 ),                  /*!<  PCF85063 P1 STATUS HIGH                                 */
    PCF85063_P1_LOW   =   ( 0 << PCF85063_P1 ),                  /*!<  PCF85063 P1 STATUS LOW                                  */

    PCF85063_P2_HIGH  =   ( 1 << PCF85063_P2 ),                  /*!<  PCF85063 P2 STATUS HIGH                                 */
    PCF85063_P2_LOW   =   ( 0 << PCF85063_P2 ),                  /*!<  PCF85063 P2 STATUS LOW                                  */

    PCF85063_P3_HIGH  =   ( 1 << PCF85063_P3 ),                  /*!<  PCF85063 P3 STATUS HIGH                                 */
    PCF85063_P3_LOW   =   ( 0 << PCF85063_P3 ),                  /*!<  PCF85063 P3 STATUS LOW                                  */

    PCF85063_P4_HIGH  =   ( 1 << PCF85063_P4 ),                  /*!<  PCF85063 P4 STATUS HIGH                                 */
    PCF85063_P4_LOW   =   ( 0 << PCF85063_P4 ),                  /*!<  PCF85063 P4 STATUS LOW                                  */

    PCF85063_P5_HIGH  =   ( 1 << PCF85063_P5 ),                  /*!<  PCF85063 P5 STATUS HIGH                                 */
    PCF85063_P5_LOW   =   ( 0 << PCF85063_P5 ),                  /*!<  PCF85063 P5 STATUS LOW                                  */

    PCF85063_P6_HIGH  =   ( 1 << PCF85063_P6 ),                  /*!<  PCF85063 P6 STATUS HIGH                                 */
    PCF85063_P6_LOW   =   ( 0 << PCF85063_P6 ),                  /*!<  PCF85063 P6 STATUS LOW                                  */

    PCF85063_P7_HIGH  =   ( 1 << PCF85063_P7 ),                  /*!<  PCF85063 P7 STATUS HIGH                                 */
    PCF85063_P7_LOW   =   ( 0 << PCF85063_P7 )                   /*!<  PCF85063 P7 STATUS LOW                                  */
} PCF85063_pin_status_t;





#ifndef PCF85063_VECTOR_STRUCT_H
#define PCF85063_VECTOR_STRUCT_H
typedef struct
{
    uint8_t data;
} PCF85063_vector_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    PCF85063_SUCCESS     =       0,
    PCF85063_FAILURE     =       1
} PCF85063_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
PCF85063_status_t  PCF85063_Init      ( I2C_parameters_t myI2Cparameters );
PCF85063_status_t  PCF85063_SetPins   ( I2C_parameters_t myI2Cparameters, PCF85063_vector_data_t  myConfDATA );
PCF85063_status_t  PCF85063_ReadPins  ( I2C_parameters_t myI2Cparameters, PCF85063_vector_data_t* myReadDATA );
