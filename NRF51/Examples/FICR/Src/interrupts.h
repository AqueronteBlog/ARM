/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        26/June/2017
 * @version     26/June/2017   The ORIGIN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 * @pre         NaN
 * @warning     NaN
 */

#include "variables.h"


/* INTERRUPT PRTOTYPES */
void GPIOTE_IRQHandler ( void );
void UART0_IRQHandler  ( void );


/* VARIABLES */
extern uint32_t  myTX;
extern uint8_t   TX_inProgress;
extern uint8_t   startCycle;
