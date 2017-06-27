/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        27/June/2017
 * @version     27/June/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "variables.h"


/* INTERRUPT PRTOTYPES */
void SPI0_IRQHandler    ( void );
void SPIS1_IRQHandler   ( void );


/* VARIABLES */
extern uint32_t changeLEDsSTATE;
extern uint32_t my375msDelay;
