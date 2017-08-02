/**
 * @brief       variables.h
 * @details     Constants and variables used by the example.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/June/2017
 * @version     29/June/2017    The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "nrf.h"
#include "nrf51_bitfields.h"
#include "board.h"

/* CONSTANTS */
#define LED1_ON  0x01
#define LED2_ON  ( LED1_ON << 1 )
#define LED3_ON  ( LED2_ON << 1 )
#define LED4_ON  ( LED3_ON << 1 )


/* VARIABLES */
uint32_t chooseLEDON;       /*!<   it turns on the right LED   */
