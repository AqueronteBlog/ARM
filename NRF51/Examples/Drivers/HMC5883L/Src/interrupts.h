/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        22/September/2017
 * @version     22/September/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "variables.h"


/* INTERRUPT PRTOTYPES */
void TIMER0_IRQHandler ( void );
void GPIOTE_IRQHandler ( void );


/* VARIABLES */
extern uint32_t  mySTATE;
extern uint32_t  myPCF8574INT;
