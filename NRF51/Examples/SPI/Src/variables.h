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
uint32_t changeLEDsSTATE;       /*!<   changeLEDsSTATE = ON:     [todo].
                                       changeLEDsSTATE = OFF:    [todo]         */


uint8_t   mySPI_RX;
uint8_t   mySPI_TX;
