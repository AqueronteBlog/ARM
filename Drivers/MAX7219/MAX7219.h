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
  * @brief   GENERAL CALL COMMANDS
  */
#define MAX7219_SHUTDOWN                 0x0C              /*!<  [TODO].                          */




/* Commands Registers */
/**
  * @brief   WRITE COMMAND TYPE
  */
typedef enum{
    FAST_MODE                              =   0,           /*!<  This command is used to change the DAC register. EEPROM is not affected.              */
    WRITE_DAC_REGISTER_MODE                =   1,           /*!<  Load configuration bits and data code to the DAC Register.                            */
    WRITE_DAC_AND_EEPROM_REGISTER_MODE     =   2            /*!<  Load configuration bits and data code to the DAC Register and also write the EEPROM.  */
} MAX7219_write_command_type_t;





#ifndef VECTOR_STRUCT_H
#define VECTOR_STRUCT_H
typedef struct{
    uint16_t EEPROM_Data;
    uint16_t DAC_Data;
} MAX7219_Vector_data_t;
#endif



/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum{
    MAX7219_SUCCESS     =       0,
    MAX7219_FAILURE     =       1
} MAX7219_status_t;



typedef struct{
    uint32_t MOSI;
    uint32_t MISO;
    uint32_t SCLK;
    uint32_t CS;

    uint32_t Freq;

    NRF_SPI_Type* SPIinstance;
} MAX7219_spi_parameters_t;


/**
  * @brief   FUNCTION PROTOTYPES
  */
MAX7219_status_t  MAX7219_Init       ( MAX7219_spi_parameters_t mySPI_parameters );
MAX7219_status_t  MAX7219_Shutdown   ( MAX7219_spi_parameters_t mySPI_parameters );
