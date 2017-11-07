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
    PCA9685_ADDRESS_0     =   0x40                    /*!<   A5 A4 A3 A2 A1 A0: 000 000                            */
} PCA9685_address_t;


// REGISTERS
/**
  * @brief   REGISTER DEFINITIONS
  */
typedef enum
{
    MODE1           =   0x00,                         /*!<  Mode register 1                                         */
    MODE2           =   0x01,                         /*!<  Mode register 2                                         */
    SUBADR1         =   0x02,                         /*!<  I2C-bus subaddress 1                                    */
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



// LED Sub Call I2C-bus addresses
/**
  * @brief   SUBADDRESS. NOTE:  At power-up, Sub Call I 2 C-bus addresses are disabled. PCA9685 does not send an
  *                             ACK when E2h (R/W = 0) or E3h (R/W = 1), E4h (R/W = 0) or E5h (R/W = 1), or
  *                             E8h (R/W = 0) or E9h (R/W = 1) is sent by the master.
  */
typedef enum
{
    SUBADR1_REG               =   0xE2,               /*!<  Subaddress 1                                                  */
    SUBADR2_REG               =   0xE4,               /*!<  Subaddress 2                                                  */
    SUBADR3_REG               =   0xE8                /*!<  Subaddress 3                                                  */
} PCA9685_subaddresses_t;




// Software Reset I2C-bus address
/**
  * @brief   SWRST. NOTE:   The Software Reset address (SWRST Call) must be used with
  *                         R/#W = logic 0. If R/#W = logic 1, the PCA9685 does not acknowledge the SWRST.
  */
typedef enum
{
    GENERAL_CALL_ADDRESS  =   0x00,                     /*!<  Software reset                                                */
    SWRST                 =   0x06                      /*!<  Software reset                                                */
} PCA9685_software_reset_t;




// MODE REGISTER 1, MODE1
/**
  * @brief   RESTART
  */
typedef enum
{
    MODE1_RESTART_MASK      =   ( 1 << 7 ),             /*!<  RESTART bit mask                                              */
    MODE1_RESTART_ENABLED   =   ( 1 << 7 ),             /*!<  Restart enabled                                               */
    MODE1_RESTART_DISABLED  =   ( 0 << 7 )              /*!<  Restart disabled ( default )                                  */
} PCA9685_mode1_restart_t;


/**
  * @brief   EXTCLK
  */
typedef enum
{
    MODE1_EXTCLK_MASK       =   ( 1 << 6 ),             /*!<  EXTCLK bit mask                                               */
    MODE1_EXTCLK_ENABLED    =   ( 1 << 6 ),             /*!<  Use EXTERNAL clock                                            */
    MODE1_EXTCLK_DISABLED   =   ( 0 << 6 )              /*!<  Use INTERNAL clock ( default )                                */
} PCA9685_mode1_extclk_t;


/**
  * @brief   AI
  */
typedef enum
{
    MODE1_AI_MASK           =   ( 1 << 5 ),             /*!<  AI bit mask                                                   */
    MODE1_AI_ENABLED        =   ( 1 << 5 ),             /*!<  Auto-Increment enabled                                        */
    MODE1_AI_DISABLED       =   ( 0 << 5 )              /*!<  Auto-Increment disabled ( default )                           */
} PCA9685_mode1_ai_t;


/**
  * @brief   SLEEP
  */
typedef enum
{
    MODE1_SLEEP_MASK        =   ( 1 << 4 ),             /*!<  SLEEP bit mask                                                */
    MODE1_SLEEP_ENABLED     =   ( 1 << 4 ),             /*!<  Low power mode. Oscillator off ( default )                    */
    MODE1_SLEEP_DISABLED    =   ( 0 << 4 )              /*!<  Normal mode                                                   */
} PCA9685_mode1_sleep_t;


/**
  * @brief   SUB1
  */
typedef enum
{
    MODE1_SUB1_MASK         =   ( 1 << 3 ),             /*!<  SUB1 bit mask                                                 */
    MODE1_SUB1_ENABLED      =   ( 1 << 3 ),             /*!<  PCA9685 responds to I2C-bus subaddress 1                      */
    MODE1_SUB1_DISABLED     =   ( 0 << 3 )              /*!<  PCA9685 does not respond to I2C-bus subaddress 1 ( default )  */
} PCA9685_mode1_sub1_t;


/**
  * @brief   SUB2
  */
typedef enum
{
    MODE1_SUB2_MASK         =   ( 1 << 2 ),             /*!<  SUB2 bit mask                                                 */
    MODE1_SUB2_ENABLED      =   ( 1 << 2 ),             /*!<  PCA9685 responds to I2C-bus subaddress 2                      */
    MODE1_SUB2_DISABLED     =   ( 0 << 2 )              /*!<  PCA9685 does not respond to I2C-bus subaddress 2 ( default )  */
} PCA9685_mode1_sub2_t;


/**
  * @brief   SUB3
  */
typedef enum
{
    MODE1_SUB3_MASK         =   ( 1 << 1 ),             /*!<  SUB1 bit mask                                                 */
    MODE1_SUB3_ENABLED      =   ( 1 << 1 ),             /*!<  PCA9685 responds to I2C-bus subaddress 3                      */
    MODE1_SUB3_DISABLED     =   ( 0 << 1 )              /*!<  PCA9685 does not respond to I2C-bus subaddress 3 ( default )  */
} PCA9685_mode1_sub3_t;


/**
  * @brief   ALLCALL
  */
typedef enum
{
    MODE1_ALLCALL_MASK      =   ( 1 << 0 ),             /*!<  ALLCALL bit mask                                              */
    MODE1_ALLCALL_ENABLED   =   ( 1 << 0 ),             /*!<  PCA9685 responds to LED All Call I2C-bus address ( default )  */
    MODE1_ALLCALL_DISABLED  =   ( 0 << 0 )              /*!<  PCA9685 does not respond to LED All Call I2C-bus address      */
} PCA9685_mode1_allcall_t;



// MODE REGISTER 2, MODE2
/**
  * @brief   INVRT
  */
typedef enum
{
    MODE2_INVRT_MASK      =   ( 1 << 4 ),               /*!<  INVRT bit mask                                                                                                */
    MODE2_INVRT_ENABLED   =   ( 1 << 4 ),               /*!<  Output logic state inverted. Value to use when no external driver used. Applicable when OE = 0                */
    MODE2_INVRT_DISABLED  =   ( 0 << 4 )                /*!<  Output logic state not inverted. Value to use when external driver used. Applicable when OE = 0. ( default )  */
} PCA9685_mode2_invrt_t;


/**
  * @brief   OCH
  */
typedef enum
{
    MODE2_OCH_MASK                      =   ( 1 << 3 ),     /*!<  ALLCALL bit mask                                              */
    MODE2_OCH_OUTPUT_CHANGE_STOP_CMD    =   ( 0 << 3 ),     /*!<  Outputs change on STOP command ( default )                    */
    MODE2_OCH_OUTPUT_CHANGE_ACK_CMD     =   ( 1 << 3 )      /*!<  Outputs change on ACK                                         */
} PCA9685_mode2_och_t;


/**
  * @brief   OUTDRV
  */
typedef enum
{
    MODE2_OUTDRV_MASK                   =   ( 1 << 2 ),     /*!<  OUTDRV bit mask                                                                */
    MODE2_OUTDRV_TOTEM_POLE_STRUCTURE   =   ( 1 << 2 ),     /*!<  The 16 LEDn outputs are configured with a totem pole structure ( default )     */
    MODE2_OUTDRV_OPEN_DRAIN_STRUCTURE   =   ( 0 << 2 )      /*!<  The 16 LEDn outputs are configured with an open-drain structure                */
} PCA9685_mode2_outdrv_t;


/**
  * @brief   OUTNE
  */
typedef enum
{
    MODE2_OUTNE_MASK                    =   ( 3 << 0 ),     /*!<  OUTNE bit mask                                                                */
    MODE2_OUTNE_LEDn_LOW                =   ( 0 << 0 ),     /*!<  When #OE = 1 (output drivers not enabled), LEDn = 0 ( default )               */
    MODE2_OUTNE_LEDn_HIGH               =   ( 1 << 0 ),     /*!<  When #OE = 1 (output drivers not enabled): LEDn = 1 when OUTDRV = 1
                                                                  LEDn = high-impedance when OUTDRV = 0 (same as OUTNE[1:0] = 10)               */
    MODE2_OUTNE_LEDn_HIGH_IMPEDANCE     =   ( 2 << 0 )      /*!<  When #OE = 1 (output drivers not enabled), LEDn = high-impedance              */
} PCA9685_mode2_outne_t;





/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    PCA9685_INTERNAL_CLOCK  =   25000000,       /*!<  Internal clock frequency                                                      */
    PCA9685_ADC_STEPS       =   4096            /*!<  ADC 12-bits                                                                   */
} PCA9685_internal_parameters_t;


typedef enum
{
    PCA9685_LED0   =   0x00,                    /*!<  LED0 channel                                                                  */
    PCA9685_LED1   =   0x01,                    /*!<  LED1 channel                                                                  */
    PCA9685_LED2   =   0x02,                    /*!<  LED2 channel                                                                  */
    PCA9685_LED3   =   0x03,                    /*!<  LED3 channel                                                                  */
    PCA9685_LED4   =   0x04,                    /*!<  LED4 channel                                                                  */
    PCA9685_LED5   =   0x05,                    /*!<  LED5 channel                                                                  */
    PCA9685_LED6   =   0x06,                    /*!<  LED6 channel                                                                  */
    PCA9685_LED7   =   0x07,                    /*!<  LED7 channel                                                                  */
    PCA9685_LED8   =   0x08,                    /*!<  LED8 channel                                                                  */
    PCA9685_LED9   =   0x09,                    /*!<  LED9 channel                                                                  */
    PCA9685_LED10  =   0x0A,                    /*!<  LED10 channel                                                                 */
    PCA9685_LED11  =   0x0B,                    /*!<  LED11 channel                                                                 */
    PCA9685_LED12  =   0x0C,                    /*!<  LED12 channel                                                                 */
    PCA9685_LED13  =   0x0D,                    /*!<  LED13 channel                                                                 */
    PCA9685_LED14  =   0x0E,                    /*!<  LED14 channel                                                                 */
    PCA9685_LED15  =   0x0F                     /*!<  LED15 channel                                                                 */
} PCA9685_led_channel_t;


typedef enum
{
    PCA9685_SUCCESS     =       0,
    PCA9685_FAILURE     =       1
} PCA9685_status_t;



// MACRO: round function
#define _MYROUND( x ) ({        \
        uint32_t aux_pre;       \
        float    aux_x;         \
                                \
        aux_x    =   (x);       \
        aux_pre  =   (x);       \
        aux_x   -=   aux_pre;   \
        aux_x   *=   10;        \
                                \
        if ( aux_x >= 5 )       \
            aux_pre++;          \
                                \
        aux_pre;                \
        })




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
PCA9685_status_t  PCA9685_Init                      ( I2C_parameters_t myI2Cparameters );

/** It resets the device by software.
  */
PCA9685_status_t  PCA9685_SoftReset                 ( I2C_parameters_t myI2Cparameters );

/** It configures the mode of the device: Sleep or Normal operation mode.
  */
PCA9685_status_t  PCA9685_SetMode                   ( I2C_parameters_t myI2Cparameters, PCA9685_mode1_sleep_t myMode );

/** It configures a new PWM frequency.
  */
PCA9685_status_t  PCA9685_SetPWM_Freq               ( I2C_parameters_t myI2Cparameters, float myNewFrequency );

/** It configures a new PWM duty cycle on a given LED.
  */
PCA9685_status_t  PCA9685_SetPWM_DutyCycle          ( I2C_parameters_t myI2Cparameters, PCA9685_led_channel_t myLEDchannel, uint8_t myDelay, uint8_t myPWM_DutyCycle );

/** It configures a new PWM duty cycle on all LEDs.
  */
PCA9685_status_t  PCA9685_SetPWM_DutyCycle_AllLEDs  ( I2C_parameters_t myI2Cparameters, uint8_t myDelay, uint8_t myPWM_DutyCycle );

/** It sets the LEDn ON.
  */
PCA9685_status_t  PCA9685_SetLED_ON                 ( I2C_parameters_t myI2Cparameters, PCA9685_led_channel_t myLEDchannel );

/** It sets the LEDn OFF.
  */
PCA9685_status_t  PCA9685_SetLED_OFF                ( I2C_parameters_t myI2Cparameters, PCA9685_led_channel_t myLEDchannel );

/** It sets All LEDs ON.
  */
PCA9685_status_t  PCA9685_SetAllLED_ON              ( I2C_parameters_t myI2Cparameters );

/** It sets All LEDs OFF.
  */
PCA9685_status_t  PCA9685_SetAllLED_OFF             ( I2C_parameters_t myI2Cparameters );

/** It sets SUB1 mode.
  */
PCA9685_status_t  PCA9685_SetSUB1                   ( I2C_parameters_t myI2Cparameters, PCA9685_mode1_sub1_t mySUB1_mode );

/** It sets SUB2 mode.
  */
PCA9685_status_t  PCA9685_SetSUB2                   ( I2C_parameters_t myI2Cparameters, PCA9685_mode1_sub2_t mySUB2_mode );

/** It sets SUB3 mode.
  */
PCA9685_status_t  PCA9685_SetSUB3                   ( I2C_parameters_t myI2Cparameters, PCA9685_mode1_sub3_t mySUB3_mode );

/** It sets ALLCALL mode.
  */
PCA9685_status_t  PCA9685_SetALLCALL                ( I2C_parameters_t myI2Cparameters, PCA9685_mode1_allcall_t myALLCALL_mode );

/** It sets INVERT mode.
  */
PCA9685_status_t  PCA9685_SetINVERT                 ( I2C_parameters_t myI2Cparameters, PCA9685_mode2_invrt_t myINVERT_mode );

/** It sets OCH mode.
  */
PCA9685_status_t  PCA9685_SetOCH                    ( I2C_parameters_t myI2Cparameters, PCA9685_mode2_och_t myOCH_mode );

/** It sets OUTDRV mode.
  */
PCA9685_status_t  PCA9685_SetOUTDRV                 ( I2C_parameters_t myI2Cparameters, PCA9685_mode2_outdrv_t myOUTDRV_mode );
