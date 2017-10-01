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
