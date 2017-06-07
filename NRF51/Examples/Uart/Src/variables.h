/**
 * @brief       variables.h
 * @details     Constants and variables used by the example.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        2/June/2017
 * @version     7/June/2017    Variables to handle the UART added.
 *              2/June/2017    The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     NaN
 */

#include "nrf.h"
#include "nrf51_bitfields.h"
#include "board.h"

/* CONSTANTS */
#define ON              1
#define OFF             0

#define YES             1
#define NO              0


#define TX_BUFF_SIZE    32


/* VARIABLES */
uint8_t myRX_buff;                      /*!<   It collects the data from the UART   */
uint8_t myMessage[ TX_BUFF_SIZE ];      /*!<   Message to be transmitted through the UART   */
uint8_t *myPtr;                         /*!<   Pointer to point out myMessage   */
uint8_t TX_inProgress;                  /*!<   It indicates if a transmission is in progress   */
