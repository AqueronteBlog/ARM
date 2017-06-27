/**
 * @brief       variables.h
 * @details     Constants and variables used by the example.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        12/April/2017
 * @version     26/June/2017    New variables added to handle the UART transmission.
 *              12/April/2017   The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "nrf.h"
#include "nrf51_bitfields.h"
#include "board.h"

/* CONSTANTS */
#define ON              1
#define OFF             0

#define YES             1
#define NO              0


/* VARIABLES */
uint32_t myTX;                           /*!<   It will store the data from the registers ( FICR ) to be transmitted                */
uint8_t  dataToBeTX;                     /*!<   A counter. It indicates how many data it will be transmitted through the UART       */
uint8_t  TX_inProgress;                  /*!<   It indicates if a transmission is in progress                                       */
uint8_t  startCycle;                     /*!<   It starts a new cycle of reading and transmitting data through the UART             */
