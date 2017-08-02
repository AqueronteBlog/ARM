/**
 * @brief       variables.h
 * @details     Constants and variables used by the example.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        2/August/2017
 * @version     2/August/2017     The ORIGIN
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
uint32_t mySTATE;                       /*!<   It will store the temperature data from the internal temperature sensor             */
uint8_t  dataToBeTX;                    /*!<   A counter. It indicates how many data it will be transmitted through the UART       */
uint32_t TX_inProgress;                 /*!<   It indicates if a transmission is in progress   */
uint8_t  TX_buff[6];                    /*!<   UART TX buffer   */
uint8_t *myPtr;                         /*!<   Pointer to point out myMessage   */
