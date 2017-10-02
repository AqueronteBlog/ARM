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



/* Decode-Mode Register Data */
/**
  * @brief   Decode-Mode Register
  */
typedef enum
{
    NO_DECODE           =   0x00,        /*!<  No decode for digits 7–0                                 */
    DECODE_DIGIT_0      =   0x01,        /*!<  Code B decode for digit 0. No decode for digits 7–1      */
    DECODE_DIGITS_3_0   =   0x0F,        /*!<  Code B decode for digits 3–0. No decode for digits 7–4   */
    DECODE_DIGITS_7_0   =   0xFF         /*!<  Code B decode for digits 7–0                             */
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



/* No-Decode Mode Data Bits */
typedef struct
{
    uint8_t mySEG       =   0x00;         /*!<  D7: DP | D6: A | D5: B | D4: C | D3: D | D2: E | D1: F | D0: G   */
} MAX7219_no_decode_b_t;




#ifndef VECTOR_STRUCT_H
#define VECTOR_STRUCT_H
typedef struct
{
    uint16_t EEPROM_Data;
    uint16_t DAC_Data;
} MAX7219_Vector_data_t;
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
MAX7219_status_t  MAX7219_Init              ( SPI_parameters_t mySPI_parameters );
MAX7219_status_t  MAX7219_Mode              ( SPI_parameters_t mySPI_parameters, MAX7219_shutdown_reg_t myMAX7219mode );
