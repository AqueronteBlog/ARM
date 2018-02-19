/**
 * @brief       variables.h
 * @details     Constants and variables used by the example.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        19/February/2018
 * @version     19/February/2018     The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     N/A
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
uint32_t mySTATE;                       /*!<   It indicates the next action to be performed                                       */
uint8_t  dataToBeTX;                    /*!<   A counter. It indicates how many data it will be transmitted through the UART      */
uint32_t TX_inProgress;                 /*!<   It indicates if a transmission is in progress                                      */
uint8_t *myPtr;                         /*!<   Pointer to point out the data from the external sensor                             */

