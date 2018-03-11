/**
 * @brief       variables.h
 * @details     Constants and variables used by the example.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/March/2018
 * @version     10/March/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "nrf.h"
#include "nrf52_bitfields.h"
#include "board.h"

#ifndef VARIABLES_H_
#define VARIABLES_H_

#ifdef __cplusplus
extern "C" {
#endif


/* CONSTANTS */
#define ON  1
#define OFF 0


/* VARIABLES */
static uint32_t changeDataSPIToBeTX;       /*!<   changeDataSPIToBeTX  = 1:     MOSI = 0x01
                                                  changeDataSPIToBeTX  = 0:     MOSI = 0x10    */
static uint8_t   mySPI_RX;                 /*!<   Receiver buffer for SPI                      */
static uint8_t   mySPI_TX;                 /*!<   Transmitter buffer for SPI                   */

static uint32_t mySPIS_RX;                 /*!<   Receiver buffer for SPIS                     */
static uint32_t mySPIS_TX;                 /*!<   Transmitter buffer for SPIS                  */

#ifdef __cplusplus
}
#endif

#endif /* VARIABLES_H_ */