/**
 * @brief       variables.h
 * @details     Constants and variables used by the example.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        2/June/2017
 * @version     2/June/2017    The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     NaN
 */

#include "nrf.h"
#include "nrf51_bitfields.h"
#include "board.h"

/* CONSTANTS */
#define ON  1
#define OFF 0

#define RX_BUFF_SIZE    32


/* VARIABLES */
uint32_t changeLEDsSTATE;               /*!<   changeLEDsSTATE = ON:     [todo].
                                               changeLEDsSTATE = OFF:    [todo]         */

uint8_t myRX_buff [ RX_BUFF_SIZE ];     /*!<   counter for the Timer2 to generate a
                                               delay of 0.375s                         */


char *myString1; //[ RX_BUFF_SIZE ];

//const char *pp =  "Hola\r\n";
