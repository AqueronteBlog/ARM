/**
 * @brief       MicroForce_FMA.h
 * @details     MicroForce Sensors, Compensated/Amplified.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        29/June/2021
 * @version     29/June/2021    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( https://www.nimbus.cit.ie ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "spi.h"


#ifndef MicroForce_FMA_H_
#define MicroForce_FMAH_

#ifdef __cplusplus
extern "C" {
#endif


/* Command Byte */
/**
  * @brief   COMMAND SELECTION BITS
  */
typedef enum{
    MicroForce_FMA_COMMAND_NONE         =   ( 0b00 << 4 ),      /*!<   No Command will be executed                                                                                                          */
    MicroForce_FMA_COMMAND_WRITE_DATA   =   ( 0b01 << 4 ),      /*!<   Write the data contained in Data Byte to the potentiometer(s) determined by the potentiometer selection bits                         */
    MicroForce_FMA_COMMAND_SHUTDOWN     =   ( 0b10 << 4 )       /*!<   Potentiometer(s) determined by potentiometer selection bits will enter Shutdown Mode. Data bits for this command are 'don't cares'   */
} MicroForce_FMA_command_selection_bits_t;


/**
  * @brief   POTENTIOMETER SELECTION BITS
  */
typedef enum{
    MicroForce_FMA_POTENTIOMETER_DUMMY_CODE                     =   ( 0b00 << 0 ),      /*!<   Dummy Code: Neither Potentiometer affected               */
    MicroForce_FMA_POTENTIOMETER_COMMAND_POTENTIOMETER_0        =   ( 0b01 << 0 ),      /*!<   Command executed on Potentiometer 0                      */
    MicroForce_FMA_POTENTIOMETER_COMMAND_POTENTIOMETER_1        =   ( 0b10 << 0 ),      /*!<   Command executed on Potentiometer 1                      */
    MicroForce_FMA_POTENTIOMETER_COMMAND_BOTH_POTENTIOMETERS    =   ( 0b11 << 0 )       /*!<   Command executed on both Potentiometers */
} MicroForce_FMA_potentiometer_selection_bits_t;





#ifndef MicroForce_FMA_VECTOR_STRUCT_H
#define MicroForce_FMA_VECTOR_STRUCT_H
typedef struct{
    uint8_t Dn;
} MicroForce_FMA_vector_data_t;
#endif



/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum{
    MicroForce_FMA_SUCCESS     =       0,
    MicroForce_FMA_FAILURE     =       1
} MicroForce_FMA_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the SPI peripheral.
    */
MicroForce_FMA_status_t  MicroForce_FMA_Init                ( SPI_parameters_t mySPIparameters                                                                                                     );

/** It updates the wiper value on the given channel.
    */
MicroForce_FMA_status_t  MicroForce_FMA_SetWiper            ( SPI_parameters_t mySPIparameters, MicroForce_FMA_potentiometer_selection_bits_t myChannel, MicroForce_FMA_vector_data_t myWiperValue );

/** It performs a software shutdown.
    */
MicroForce_FMA_status_t  MicroForce_FMA_SoftwareShutdown    ( SPI_parameters_t mySPIparameters, MicroForce_FMA_potentiometer_selection_bits_t myChannel                                            );


#ifdef __cplusplus
}
#endif

#endif /* MicroForce_FMA_H_ */
