/**
 * @brief       MCP41XXX_42XXX.h
 * @details     Single/Dual Digital Potentiometer with SPI™ Interface.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        21/August/2018
 * @version     21/August/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "spi.h"


#ifndef MCP41XXX_42XXX_H_
#define MCP41XXX_42XXXH_

#ifdef __cplusplus
extern "C" {
#endif


/* Command Byte */
/**
  * @brief   COMMAND SELECTION BITS
  */
typedef enum{
    MCP41XXX_42XXX_COMMAND_NONE         =   ( 0b00 << 4 ),      /*!<   No Command will be executed                                                                                                          */
    MCP41XXX_42XXX_COMMAND_WRITE_DATA   =   ( 0b01 << 4 ),      /*!<   Write the data contained in Data Byte to the potentiometer(s) determined by the potentiometer selection bits                         */
    MCP41XXX_42XXX_COMMAND_SHUTDOWN     =   ( 0b10 << 4 )       /*!<   Potentiometer(s) determined by potentiometer selection bits will enter Shutdown Mode. Data bits for this command are 'don't cares'   */
} MCP41XXX_42XXX_command_selection_bits_t;


/**
  * @brief   POTENTIOMETER SELECTION BITS
  */
typedef enum{
    MCP41XXX_42XXX_POTENTIOMETER_DUMMY_CODE                     =   ( 0b00 << 0 ),      /*!<   Dummy Code: Neither Potentiometer affected               */
    MCP41XXX_42XXX_POTENTIOMETER_COMMAND_POTENTIOMETER_0        =   ( 0b01 << 0 ),      /*!<   Command executed on Potentiometer 0                      */
    MCP41XXX_42XXX_POTENTIOMETER_COMMAND_POTENTIOMETER_1        =   ( 0b10 << 0 ),      /*!<   Command executed on Potentiometer 1                      */
    MCP41XXX_42XXX_POTENTIOMETER_COMMAND_BOTH_POTENTIOMETERS    =   ( 0b11 << 0 )       /*!<   Command executed on both Potentiometers */
} MCP41XXX_42XXX_potentiometer_selection_bits_t;





#ifndef MCP41XXX_42XXX_VECTOR_STRUCT_H
#define MCP41XXX_42XXX_VECTOR_STRUCT_H
typedef struct{
    uint8_t Dn;
} MCP41XXX_42XXX_vector_data_t;
#endif



/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum{
    MCP41XXX_42XXX_SUCCESS     =       0,
    MCP41XXX_42XXX_FAILURE     =       1
} MCP41XXX_42XXX_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the SPI peripheral.
    */
MCP41XXX_42XXX_status_t  MCP41XXX_42XXX_Init                ( SPI_parameters_t mySPIparameters                                                                                                     );

/** It updates the wiper value on the given channel.
    */
MCP41XXX_42XXX_status_t  MCP41XXX_42XXX_SetWiper            ( SPI_parameters_t mySPIparameters, MCP41XXX_42XXX_potentiometer_selection_bits_t myChannel, MCP41XXX_42XXX_vector_data_t myWiperValue );

/** It performs a software shutdown.
    */
MCP41XXX_42XXX_status_t  MCP41XXX_42XXX_SoftwareShutdown    ( SPI_parameters_t mySPIparameters, MCP41XXX_42XXX_potentiometer_selection_bits_t myChannel                                            );


#ifdef __cplusplus
}
#endif

#endif /* MCP41XXX_42XXX_H_ */
