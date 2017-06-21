/**
 * @brief       variables.h
 * @details     Constants and variables used by the example.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        2/June/2017
 * @version     21/June/2017    Variables to handle both the UART and the TEMP added.
 *              2/June/2017     The ORIGIN
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



/* VARIABLES */
uint32_t myTEMP;                         /*!<   It will store the temperature data from the internal temperature sensor             */
uint8_t  dataToBeTX;                     /*!<   A counter. It indicates how many data it will be transmitted through the UART       */
