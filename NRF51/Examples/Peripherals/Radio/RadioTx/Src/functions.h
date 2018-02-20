/**
 * @brief       functions.h
 * @details     Functions's header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        19/January/2018
 * @version     19/January/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "nrf.h"
#include "nrf51_bitfields.h"
#include "variables.h"

/* FUNCTION PROTOTYPES */
void conf_GPIO      ( void );
void conf_TIMER0    ( void );
void conf_RADIO     ( uint8_t* myPacketPointer );

