/**
 * @brief       MAX7219.h
 * @details     Serially Interfaced, 8-Digit LED Display Drivers.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        28/September/2017
 * @version     28/September/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "spi.h"


/* General Call Commands */
/**
  * @brief   REGISTER ADDRESS MAP
  */
typedef enum
{
    NO_OP           =   0x00,           /*!<  No operation.              */
    DIGIT_0         =   0x01,           /*!<  Digit 0.                   */
    DIGIT_1         =   0x02,           /*!<  Digit 1.                   */
    DIGIT_2         =   0x03,           /*!<  Digit 2.                   */
    DIGIT_3         =   0x04,           /*!<  Digit 3.                   */
    DIGIT_4         =   0x05,           /*!<  Digit 4.                   */
    DIGIT_5         =   0x06,           /*!<  Digit 5.                   */
    DIGIT_6         =   0x07,           /*!<  Digit 6.                   */
    DIGIT_7         =   0x08,           /*!<  Digit 7.                   */
    DECODE_MODE     =   0x09,           /*!<  Decode Mode.               */
    INTENSITY       =   0x0A,           /*!<  Intensity.                 */
    SCAN_LIMIT      =   0x0B,           /*!<  Scan Limit.                */
    SHUTDOWN        =   0x0C,           /*!<  Shutdown.                  */
    DISPLAY_TEST    =   0x0F            /*!<  Display test.              */
} MAX7219_register_address_map_t;



/* Shutdown Register Data */
/**
  * @brief   Shutdown Register Format
  */
typedef enum
{
    SHUTDOWN_MODE       =   0x00,        /*!<  Device in shutdown mode    */
    NORMAL_OPERATION    =   0x01         /*!<  Device in normal mode      */
} MAX7219_shutdown_reg_t;


/* Display-Test Register Data */
/**
  * @brief   Display-Test Register Format
  */
typedef enum
{
    DISPLAY_TEST_MODE           =   0x01,        /*!<  All the LEDs are ON         */
    DISPLAY_NORMAL_OPERATION    =   0x00         /*!<  Normal operation            */
} MAX7219_display_test_reg_t;



/* Decode-Mode Register Data */
/**
  * @brief   Decode-Mode Register
  */
typedef enum
{
    NO_DECODE           =   0x00,        /*!<  No decode for digits 7-0                                 */
    DECODE_DIGIT_0      =   0x01,        /*!<  Code B decode for digit 0. No decode for digits 7-1      */
    DECODE_DIGITS_3_0   =   0x0F,        /*!<  Code B decode for digits 3-0. No decode for digits 7-4   */
    DECODE_DIGITS_7_0   =   0xFF         /*!<  Code B decode for digits 7-0                             */
} MAX7219_decode_mode_reg_t;



/* Code B Font Register Data */
/**
  * @brief   Code B Font
  */
typedef enum
{
    CHARACTER_0         =   0x00,        /*!<  0                                                        */
    CHARACTER_1         =   0x01,        /*!<  1                                                        */
    CHARACTER_2         =   0x02,        /*!<  2                                                        */
    CHARACTER_3         =   0x03,        /*!<  3                                                        */
    CHARACTER_4         =   0x04,        /*!<  4                                                        */
    CHARACTER_5         =   0x05,        /*!<  5                                                        */
    CHARACTER_6         =   0x06,        /*!<  6                                                        */
    CHARACTER_7         =   0x07,        /*!<  7                                                        */
    CHARACTER_8         =   0x08,        /*!<  8                                                        */
    CHARACTER_9         =   0x09,        /*!<  9                                                        */
    CHARACTER_HYPHEN    =   0x0A,        /*!<  -                                                        */
    CHARACTER_E         =   0x0B,        /*!<  E                                                        */
    CHARACTER_H         =   0x0C,        /*!<  H                                                        */
    CHARACTER_L         =   0x0D,        /*!<  L                                                        */
    CHARACTER_P         =   0x0E,        /*!<  P                                                        */
    CHARACTER_BLANK     =   0x0F         /*!<  Blank                                                    */
} MAX7219_code_b_font_reg_t;



typedef enum
{
    DP_ENABLED          =   0x01,         /*!<  DP ON                                                    */
    DP_DISABLED         =   0x00          /*!<  DP OFF                                                   */
} MAX7219_code_b_dp_t;



/* Intensity Register Format Data */
/**
  * @brief   Intensity Register Format
  */
typedef enum
{
    DUTY_CICLE_1_32     =   0x00,        /*!<  Duty cycle 1/32 ( min )      */
    DUTY_CICLE_3_32     =   0x01,        /*!<  Duty cycle 3/32              */
    DUTY_CICLE_5_32     =   0x02,        /*!<  Duty cycle 5/32              */
    DUTY_CICLE_7_32     =   0x03,        /*!<  Duty cycle 7/32              */
    DUTY_CICLE_9_32     =   0x04,        /*!<  Duty cycle 9/32              */
    DUTY_CICLE_11_32    =   0x05,        /*!<  Duty cycle 11/32             */
    DUTY_CICLE_13_32    =   0x06,        /*!<  Duty cycle 13/32             */
    DUTY_CICLE_15_32    =   0x07,        /*!<  Duty cycle 15/32             */
    DUTY_CICLE_17_32    =   0x08,        /*!<  Duty cycle 17/32             */
    DUTY_CICLE_19_32    =   0x09,        /*!<  Duty cycle 19/32             */
    DUTY_CICLE_21_32    =   0x0A,        /*!<  Duty cycle 21/32             */
    DUTY_CICLE_23_32    =   0x0B,        /*!<  Duty cycle 23/32             */
    DUTY_CICLE_25_32    =   0x0C,        /*!<  Duty cycle 25/32             */
    DUTY_CICLE_27_32    =   0x0D,        /*!<  Duty cycle 27/32             */
    DUTY_CICLE_29_32    =   0x0E,        /*!<  Duty cycle 29/32             */
    DUTY_CICLE_31_32    =   0x0F         /*!<  Duty cycle 31/32 ( max )     */
} MAX7219_intensity_reg_t;


/* Scan-Limit Register Format Data */
/**
  * @brief   Scan-Limit Register Format
  */
typedef enum
{
    DISPLAY_DIGIT_0                 =   0x00,        /*!<  Display digit 0 only             */
    DISPLAY_DIGIT_0_1               =   0x01,        /*!<  Display digits 0 & 1             */
    DISPLAY_DIGIT_0_1_2             =   0x02,        /*!<  Display digits 0 1 2             */
    DISPLAY_DIGIT_0_1_2_3           =   0x03,        /*!<  Display digits 0 1 2 3           */
    DISPLAY_DIGIT_0_1_2_3_4         =   0x04,        /*!<  Display digits 0 1 2 3 4         */
    DISPLAY_DIGIT_0_1_2_3_4_5       =   0x05,        /*!<  Display digits 0 1 2 3 4 5       */
    DISPLAY_DIGIT_0_1_2_3_4_5_6     =   0x06,        /*!<  Display digits 0 1 2 3 4 5 6     */
    DISPLAY_DIGIT_0_1_2_3_4_5_6_7   =   0x07         /*!<  Display digits 0 1 2 3 4 5 6 7   */
} MAX7219_scan_limit_reg_t;



/**
  * @brief   Select digits
  */
typedef enum
{
    SET_DIGIT_0     =   0x00,        /*!<  Digit 0 selected   */
    SET_DIGIT_1     =   0x01,        /*!<  Digit 1 selected   */
    SET_DIGIT_2     =   0x02,        /*!<  Digit 2 selected   */
    SET_DIGIT_3     =   0x03,        /*!<  Digit 3 selected   */
    SET_DIGIT_4     =   0x04,        /*!<  Digit 4 selected   */
    SET_DIGIT_5     =   0x05,        /*!<  Digit 5 selected   */
    SET_DIGIT_6     =   0x06,        /*!<  Digit 6 selected   */
    SET_DIGIT_7     =   0x07         /*!<  Digit 7 selected   */
} MAX7219_digit_t;



#ifndef MAX7219_VECTOR_STRUCT_H
#define MAX7219_VECTOR_STRUCT_H
/* No-Decode Mode Data Bits */
typedef struct
{
    uint8_t mySEG;                  /*!<  D7: DP | D6: A | D5: B | D4: C | D3: D | D2: E | D1: F | D0: G   */
} MAX7219_no_decode_b_t;
#endif



/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    MAX7219_SUCCESS     =       0,
    MAX7219_FAILURE     =       1
} MAX7219_status_t;





/**
  * @brief   FUNCTION PROTOTYPES
  */
MAX7219_status_t  MAX7219_Init              ( SPI_parameters_t mySPI_parameters                                                         );
MAX7219_status_t  MAX7219_Mode              ( SPI_parameters_t mySPI_parameters, MAX7219_shutdown_reg_t myMAX7219mode                   );
MAX7219_status_t  MAX7219_DisplayTest       ( SPI_parameters_t mySPI_parameters, MAX7219_display_test_reg_t myMAX7219DisplayTestMode    );
MAX7219_status_t  MAX7219_DecodeMode        ( SPI_parameters_t mySPI_parameters, MAX7219_decode_mode_reg_t myMAX7219DecodeMode          );
MAX7219_status_t  MAX7219_SetIntensity      ( SPI_parameters_t mySPI_parameters, MAX7219_intensity_reg_t myMAX7219Intensity             );
MAX7219_status_t  MAX7219_SetScanLimit      ( SPI_parameters_t mySPI_parameters, MAX7219_scan_limit_reg_t myMAX7219ScanLimit            );
MAX7219_status_t  MAX7219_SetDigit          ( SPI_parameters_t mySPI_parameters, MAX7219_digit_t myMAX7219Digit, MAX7219_code_b_font_reg_t myCharacter );
