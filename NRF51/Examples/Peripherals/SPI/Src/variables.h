/**
 * @brief       variables.h
 * @details     Constants and variables used by the example.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        27/June/2017
 * @version     27/June/2017    The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "nrf.h"
#include "nrf51_bitfields.h"
#include "board.h"

/* CONSTANTS */
#define ON  1
#define OFF 0


/* VARIABLES */
uint32_t changeDataSPIToBeTX;       /*!<   changeDataSPIToBeTX  = 1:     MOSI = 0x01
                                           changeDataSPIToBeTX  = 0:     MOSI = 0x10    */
uint8_t   mySPI_RX;                 /*!<   Receiver buffer for SPI                      */
uint8_t   mySPI_TX;                 /*!<   Transmitter buffer for SPI                   */

uint32_t mySPIS_RX;                 /*!<   Receiver buffer for SPIS                     */
uint32_t mySPIS_TX;                 /*!<   Transmitter buffer for SPIS                  */
