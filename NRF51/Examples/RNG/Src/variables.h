/**
 * @brief       variables.h
 * @details     Constants and variables used by the example.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        22/June/2017
 * @version     22/June/2017    The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     NaN
 */

#include "nrf.h"
#include "nrf51_bitfields.h"
#include "board.h"

/* CONSTANTS */
#define TX_ENABLE       1
#define TX_DISABLE      0

#define YES             1
#define NO              0



/* VARIABLES */
uint8_t myRX_buff;                      /*!<   It collects the data from the UART         */
uint8_t myRandomNumber;                 /*!<   It gets the random number                  */

