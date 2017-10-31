/**
 * @brief       PCA9685.h
 * @details     16-channel, 12-bit PWM Fm+ I2C-bus LED controller.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        31/October/2017
 * @version     31/October/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESSES.  NOTE:  There are a maximum of 64 possible programmable addresses using the 6 hardware
  *                                     address pins. Two of these addresses, Software Reset and LED All Call, cannot be used
  *                                     because their default power-up state is ON, leaving a maximum of 62 addresses. Using
  *                                     other reserved addresses, as well as any other subcall address, will reduce the total
  *                                     number of possible addresses even further.
  *
  *                                     To access to a certain address just use the following method:  PCA9685_ADDRESS_0 + Counter_Address
  *                                     Ex:
  *                                         PCA9685_ADDRESS_0 + 1 = 0x40 + 1  = 0x41 ( 0b1000001 )
  *                                         PCA9685_ADDRESS_0 + 1 = 0x40 + 10 = 0x41 ( 0b1001010 )
  *                                         and so on...
  */
typedef enum
{
    PCA9685_ADDRESS_0     =   0x40                           /*!<   A5 A4 A3 A2 A1 A0: 000 000                              */
} PCA9685_address_t;


// REGISTERS
/**
  * @brief   REGISTER DEFINITIONS
  */
typedef enum
{
    MODE1           =   0x00,                         /*!<  Mode register 1                                         */
    MODE2           =   0x01,                         /*!<  Mode register 2                                         */
    SUDADR1         =   0x02,                         /*!<  I2C-bus subaddress 1                                    */
    SUBADR2         =   0x03,                         /*!<  I2C-bus subaddress 2                                    */
    SUBADR3         =   0x04,                         /*!<  I2C-bus subaddress 3                                    */
    ALLCALLADR      =   0x05,                         /*!<  LED All Call I2C-bus address                            */
    LED0_ON_L       =   0x06,                         /*!<  LED0 output and brightness control byte 0               */
    LED0_ON_H       =   0x07,                         /*!<  LED0 output and brightness control byte 1               */
    LED0_OFF_L      =   0x08,                         /*!<  LED0 output and brightness control byte 2               */
    LED0_OFF_H      =   0x09,                         /*!<  LED0 output and brightness control byte 3               */
    LED1_ON_L       =   0x0A,                         /*!<  LED1 output and brightness control byte 0               */
    LED1_ON_H       =   0x0B,                         /*!<  LED1 output and brightness control byte 1               */
    LED1_OFF_L      =   0x0C,                         /*!<  LED1 output and brightness control byte 2               */
    LED1_OFF_H      =   0x0D,                         /*!<  LED1 output and brightness control byte 3               */
    LED2_ON_L       =   0x0E,                         /*!<  LED2 output and brightness control byte 0               */
    LED2_ON_H       =   0x0F,                         /*!<  LED2 output and brightness control byte 1               */
    LED2_OFF_L      =   0x10,                         /*!<  LED2 output and brightness control byte 2               */
    LED2_OFF_H      =   0x11,                         /*!<  LED2 output and brightness control byte 3               */
    LED3_ON_L       =   0x12,                         /*!<  LED3 output and brightness control byte 0               */
    LED3_ON_H       =   0x13,                         /*!<  LED3 output and brightness control byte 1               */
    LED3_OFF_L      =   0x14,                         /*!<  LED3 output and brightness control byte 2               */
    LED3_OFF_H      =   0x15,                         /*!<  LED3 output and brightness control byte 3               */
    LED4_ON_L       =   0x16,                         /*!<  LED4 output and brightness control byte 0               */
    LED4_ON_H       =   0x17,                         /*!<  LED4 output and brightness control byte 1               */
    LED4_OFF_L      =   0x18,                         /*!<  LED4 output and brightness control byte 2               */
    LED4_OFF_H      =   0x19,                         /*!<  LED4 output and brightness control byte 3               */
    LED5_ON_L       =   0x1A,                         /*!<  LED5 output and brightness control byte 0               */
    LED5_ON_H       =   0x1B,                         /*!<  LED5 output and brightness control byte 1               */
    LED5_OFF_L      =   0x1C,                         /*!<  LED5 output and brightness control byte 2               */
    LED5_OFF_H      =   0x1D,                         /*!<  LED5 output and brightness control byte 3               */
    LED6_ON_L       =   0x1E,                         /*!<  LED6 output and brightness control byte 0               */
    LED6_ON_H       =   0x1F,                         /*!<  LED6 output and brightness control byte 1               */
    LED6_OFF_L      =   0x20,                         /*!<  LED6 output and brightness control byte 2               */
    LED6_OFF_H      =   0x21,                         /*!<  LED6 output and brightness control byte 3               */
    LED7_ON_L       =   0x22,                         /*!<  LED7 output and brightness control byte 0               */
    LED7_ON_H       =   0x23,                         /*!<  LED7 output and brightness control byte 1               */
    LED7_OFF_L      =   0x24,                         /*!<  LED7 output and brightness control byte 2               */
    LED7_OFF_H      =   0x25,                         /*!<  LED7 output and brightness control byte 3               */
    LED8_ON_L       =   0x26,                         /*!<  LED8 output and brightness control byte 0               */
    LED8_ON_H       =   0x27,                         /*!<  LED8 output and brightness control byte 1               */
    LED8_OFF_L      =   0x28,                         /*!<  LED8 output and brightness control byte 2               */
    LED8_OFF_H      =   0x29,                         /*!<  LED8 output and brightness control byte 3               */
    LED9_ON_L       =   0x2A,                         /*!<  LED9 output and brightness control byte 0               */
    LED9_ON_H       =   0x2B,                         /*!<  LED9 output and brightness control byte 1               */
    LED9_OFF_L      =   0x2C,                         /*!<  LED9 output and brightness control byte 2               */
    LED9_OFF_H      =   0x2D,                         /*!<  LED9 output and brightness control byte 3               */
    LED10_ON_L      =   0x2E,                         /*!<  LED10 output and brightness control byte 0              */
    LED10_ON_H      =   0x2F,                         /*!<  LED10 output and brightness control byte 1              */
    LED10_OFF_L     =   0x30,                         /*!<  LED10 output and brightness control byte 2              */
    LED10_OFF_H     =   0x31,                         /*!<  LED10 output and brightness control byte 3              */
    LED11_ON_L      =   0x32,                         /*!<  LED11 output and brightness control byte 0              */
    LED11_ON_H      =   0x33,                         /*!<  LED11 output and brightness control byte 1              */
    LED11_OFF_L     =   0x34,                         /*!<  LED11 output and brightness control byte 2              */
    LED11_OFF_H     =   0x35,                         /*!<  LED11 output and brightness control byte 3              */
    LED12_ON_L      =   0x36,                         /*!<  LED12 output and brightness control byte 0              */
    LED12_ON_H      =   0x37,                         /*!<  LED12 output and brightness control byte 1              */
    LED12_OFF_L     =   0x38,                         /*!<  LED12 output and brightness control byte 2              */
    LED12_OFF_H     =   0x39,                         /*!<  LED12 output and brightness control byte 3              */
    LED13_ON_L      =   0x3A,                         /*!<  LED13 output and brightness control byte 0              */
    LED13_ON_H      =   0x3B,                         /*!<  LED13 output and brightness control byte 1              */
    LED13_OFF_L     =   0x3C,                         /*!<  LED13 output and brightness control byte 2              */
    LED13_OFF_H     =   0x3D,                         /*!<  LED13 output and brightness control byte 3              */
    LED14_ON_L      =   0x3E,                         /*!<  LED14 output and brightness control byte 0              */
    LED14_ON_H      =   0x3F,                         /*!<  LED14 output and brightness control byte 1              */
    LED14_OFF_L     =   0x40,                         /*!<  LED14 output and brightness control byte 2              */
    LED14_OFF_H     =   0x41,                         /*!<  LED14 output and brightness control byte 3              */
    LED15_ON_L      =   0x42,                         /*!<  LED15 output and brightness control byte 0              */
    LED15_ON_H      =   0x43,                         /*!<  LED15 output and brightness control byte 1              */
    LED15_OFF_L     =   0x44,                         /*!<  LED15 output and brightness control byte 2              */
    LED15_OFF_H     =   0x45,                         /*!<  LED15 output and brightness control byte 3              */
    ALL_LED_ON_L    =   0xFA,                         /*!<  load all the LEDn_ON registers, byte 0                  */
    ALL_LED_ON_H    =   0xFB,                         /*!<  load all the LEDn_ON registers, byte 1                  */
    ALL_LED_OFF_L   =   0xFC,                         /*!<  load all the LEDn_OFF registers, byte 0                 */
    ALL_LED_OFF_H   =   0xFD,                         /*!<  load all the LEDn_OFF registers, byte 1                 */
    PRE_SCALE       =   0xFE,                         /*!<  prescaler for PWM output frequency                      */
    TESTMODE        =   0xFF                          /*!<  defines the test mode to be entered                     */
} PCA9685_registers_t;



// REGISTER COMMANDS
/**
  * @brief   MODE REGISTER 1, MODE1
  */
typedef enum
{
    MODE1_RESTART_MASK      =   0x80,                   /*!<  RESTART bit mask                                              */
    MODE1_RESTART_ENABLED   =   0x80,                   /*!<  Restart enabled                                               */
    MODE1_RESTART_DISABLED  =   0x00,                   /*!<  Restart disabled ( default )                                  */

    MODE1_EXTCLK_MASK       =   0x40,                   /*!<  EXTCLK bit mask                                               */
    MODE1_EXTCLK_ENABLED    =   0x40,                   /*!<  Use EXTERNAL clock                                            */
    MODE1_EXTCLK_DISABLED   =   0x00,                   /*!<  Use INTERNAL clock ( default )                                */

    MODE1_AI_MASK           =   0x20,                   /*!<  AI bit mask                                                   */
    MODE1_AI_ENABLED        =   0x20,                   /*!<  Auto-Increment enabled                                        */
    MODE1_AI_DISABLED       =   0x00,                   /*!<  Auto-Increment disabled ( default )                           */

    MODE1_SLEEP_MASK        =   0x10,                   /*!<  SLEEP bit mask                                                */
    MODE1_SLEEP_ENABLED     =   0x10,                   /*!<  Low power mode. Oscillator off ( default )                    */
    MODE1_SLEEP_DISABLED    =   0x00,                   /*!<  Normal mode                                                   */

    MODE1_SUB1_MASK         =   0x08,                   /*!<  SUB1 bit mask                                                 */
    MODE1_SUB1_ENABLED      =   0x08,                   /*!<  PCA9685 responds to I2C-bus subaddress 1                      */
    MODE1_SUB1_DISABLED     =   0x00,                   /*!<  PCA9685 does not respond to I2C-bus subaddress 1 ( default )  */

    MODE1_SUB2_MASK         =   0x04,                   /*!<  SUB2 bit mask                                                 */
    MODE1_SUB2_ENABLED      =   0x04,                   /*!<  PCA9685 responds to I2C-bus subaddress 2                      */
    MODE1_SUB2_DISABLED     =   0x00,                   /*!<  PCA9685 does not respond to I2C-bus subaddress 2 ( default )  */

    MODE1_SUB3_MASK         =   0x02,                   /*!<  SUB1 bit mask                                                 */
    MODE1_SUB3_ENABLED      =   0x02,                   /*!<  PCA9685 responds to I2C-bus subaddress 3                      */
    MODE1_SUB3_DISABLED     =   0x00,                   /*!<  PCA9685 does not respond to I2C-bus subaddress 3 ( default )  */

    MODE1_SUB3_MASK         =   0x02,                   /*!<  SUB1 bit mask                                                 */
    MODE1_SUB3_ENABLED      =   0x02,                   /*!<  PCA9685 responds to I2C-bus subaddress 3                      */
    MODE1_SUB3_DISABLED     =   0x00,                   /*!<  PCA9685 does not respond to I2C-bus subaddress 3 ( default )  */
} PCA9685_mode1_reg_t;


/**
  * @brief   PIN MASK
  */
typedef enum
{
    PCA9685_P0_MASK          =   0b00000001,                  /*!<  PCA9685 P0 INPUT                                       */
    PCA9685_P1_MASK          =   0b00000010,                  /*!<  PCA9685 P1 INPUT                                       */
    PCA9685_P2_MASK          =   0b00000100,                  /*!<  PCA9685 P2 INPUT                                       */
    PCA9685_P3_MASK          =   0b00001000,                  /*!<  PCA9685 P3 INPUT                                       */
    PCA9685_P4_MASK          =   0b00010000,                  /*!<  PCA9685 P4 INPUT                                       */
    PCA9685_P5_MASK          =   0b00100000,                  /*!<  PCA9685 P5 INPUT                                       */
    PCA9685_P6_MASK          =   0b01000000,                  /*!<  PCA9685 P6 INPUT                                       */
    PCA9685_P7_MASK          =   0b10000000                   /*!<  PCA9685 P7 INPUT                                       */
} PCA9685_pin_mask_t;



/**
  * @brief   PIN CONFIGURATION
  */
typedef enum
{
    PCA9685_P0_INPUT        =   ( 1 << PCA9685_P0 ),           /*!<  PCA9685 P0 INPUT                                       */
    PCA9685_P0_OUTPUT_HIGH  =   ( 1 << PCA9685_P0 ),           /*!<  PCA9685 P0 OUTPUT HIGH                                 */
    PCA9685_P0_OUTPUT_LOW   =   ( 0 << PCA9685_P0 ),           /*!<  PCA9685 P0 OUTPUT LOW                                  */

    PCA9685_P1_INPUT        =   ( 1 << PCA9685_P1 ),           /*!<  PCA9685 P1 INPUT                                       */
    PCA9685_P1_OUTPUT_HIGH  =   ( 1 << PCA9685_P1 ),           /*!<  PCA9685 P1 OUTPUT HIGH                                 */
    PCA9685_P1_OUTPUT_LOW   =   ( 0 << PCA9685_P1 ),           /*!<  PCA9685 P1 OUTPUT LOW                                  */

    PCA9685_P2_INPUT        =   ( 1 << PCA9685_P2 ),           /*!<  PCA9685 P2 INPUT                                       */
    PCA9685_P2_OUTPUT_HIGH  =   ( 1 << PCA9685_P2 ),           /*!<  PCA9685 P2 OUTPUT HIGH                                 */
    PCA9685_P2_OUTPUT_LOW   =   ( 0 << PCA9685_P2 ),           /*!<  PCA9685 P2 OUTPUT LOW                                  */

    PCA9685_P3_INPUT        =   ( 1 << PCA9685_P3 ),           /*!<  PCA9685 P3 INPUT                                       */
    PCA9685_P3_OUTPUT_HIGH  =   ( 1 << PCA9685_P3 ),           /*!<  PCA9685 P3 OUTPUT HIGH                                 */
    PCA9685_P3_OUTPUT_LOW   =   ( 0 << PCA9685_P3 ),           /*!<  PCA9685 P3 OUTPUT LOW                                  */

    PCA9685_P4_INPUT        =   ( 1 << PCA9685_P4 ),           /*!<  PCA9685 P4 INPUT                                       */
    PCA9685_P4_OUTPUT_HIGH  =   ( 1 << PCA9685_P4 ),           /*!<  PCA9685 P4 OUTPUT HIGH                                 */
    PCA9685_P4_OUTPUT_LOW   =   ( 0 << PCA9685_P4 ),           /*!<  PCA9685 P4 OUTPUT LOW                                  */

    PCA9685_P5_INPUT        =   ( 1 << PCA9685_P5 ),           /*!<  PCA9685 P5 INPUT                                       */
    PCA9685_P5_OUTPUT_HIGH  =   ( 1 << PCA9685_P5 ),           /*!<  PCA9685 P5 OUTPUT HIGH                                 */
    PCA9685_P5_OUTPUT_LOW   =   ( 0 << PCA9685_P5 ),           /*!<  PCA9685 P5 OUTPUT LOW                                  */

    PCA9685_P6_INPUT        =   ( 1 << PCA9685_P6 ),           /*!<  PCA9685 P6 INPUT                                       */
    PCA9685_P6_OUTPUT_HIGH  =   ( 1 << PCA9685_P6 ),           /*!<  PCA9685 P6 OUTPUT HIGH                                 */
    PCA9685_P6_OUTPUT_LOW   =   ( 0 << PCA9685_P6 ),           /*!<  PCA9685 P6 OUTPUT LOW                                  */

    PCA9685_P7_INPUT        =   ( 1 << PCA9685_P7 ),           /*!<  PCA9685 P7 INPUT                                       */
    PCA9685_P7_OUTPUT_HIGH  =   ( 1 << PCA9685_P7 ),           /*!<  PCA9685 P7 OUTPUT HIGH                                 */
    PCA9685_P7_OUTPUT_LOW   =   ( 0 << PCA9685_P7 )            /*!<  PCA9685 P7 OUTPUT LOW                                  */
} PCA9685_pin_configuration_t;



/**
  * @brief   PIN STATUS
  */
typedef enum
{
    PCA9685_P0_HIGH  =   ( 1 << PCA9685_P0 ),                  /*!<  PCA9685 P0 STATUS HIGH                                 */
    PCA9685_P0_LOW   =   ( 0 << PCA9685_P0 ),                  /*!<  PCA9685 P0 STATUS LOW                                  */

    PCA9685_P1_HIGH  =   ( 1 << PCA9685_P1 ),                  /*!<  PCA9685 P1 STATUS HIGH                                 */
    PCA9685_P1_LOW   =   ( 0 << PCA9685_P1 ),                  /*!<  PCA9685 P1 STATUS LOW                                  */

    PCA9685_P2_HIGH  =   ( 1 << PCA9685_P2 ),                  /*!<  PCA9685 P2 STATUS HIGH                                 */
    PCA9685_P2_LOW   =   ( 0 << PCA9685_P2 ),                  /*!<  PCA9685 P2 STATUS LOW                                  */

    PCA9685_P3_HIGH  =   ( 1 << PCA9685_P3 ),                  /*!<  PCA9685 P3 STATUS HIGH                                 */
    PCA9685_P3_LOW   =   ( 0 << PCA9685_P3 ),                  /*!<  PCA9685 P3 STATUS LOW                                  */

    PCA9685_P4_HIGH  =   ( 1 << PCA9685_P4 ),                  /*!<  PCA9685 P4 STATUS HIGH                                 */
    PCA9685_P4_LOW   =   ( 0 << PCA9685_P4 ),                  /*!<  PCA9685 P4 STATUS LOW                                  */

    PCA9685_P5_HIGH  =   ( 1 << PCA9685_P5 ),                  /*!<  PCA9685 P5 STATUS HIGH                                 */
    PCA9685_P5_LOW   =   ( 0 << PCA9685_P5 ),                  /*!<  PCA9685 P5 STATUS LOW                                  */

    PCA9685_P6_HIGH  =   ( 1 << PCA9685_P6 ),                  /*!<  PCA9685 P6 STATUS HIGH                                 */
    PCA9685_P6_LOW   =   ( 0 << PCA9685_P6 ),                  /*!<  PCA9685 P6 STATUS LOW                                  */

    PCA9685_P7_HIGH  =   ( 1 << PCA9685_P7 ),                  /*!<  PCA9685 P7 STATUS HIGH                                 */
    PCA9685_P7_LOW   =   ( 0 << PCA9685_P7 )                   /*!<  PCA9685 P7 STATUS LOW                                  */
} PCA9685_pin_status_t;





#ifndef PCA9685_VECTOR_STRUCT_H
#define PCA9685_VECTOR_STRUCT_H
typedef struct
{
    uint8_t data;
} PCA9685_vector_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    PCA9685_SUCCESS     =       0,
    PCA9685_FAILURE     =       1
} PCA9685_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
PCA9685_status_t  PCA9685_Init      ( I2C_parameters_t myI2Cparameters );
PCA9685_status_t  PCA9685_SetPins   ( I2C_parameters_t myI2Cparameters, PCA9685_vector_data_t  myConfDATA );
PCA9685_status_t  PCA9685_ReadPins  ( I2C_parameters_t myI2Cparameters, PCA9685_vector_data_t* myReadDATA );
