/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        18/January/2018
 * @version     18/January/2018    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "variables.h"


/* INTERRUPT PRTOTYPES */
void TIMER0_IRQHandler ( void );
void UART0_IRQHandler  ( void );


/* VARIABLES */
extern uint8_t   dataToBeTX;
extern uint32_t  mySTATE;
extern uint32_t  TX_inProgress;
extern uint8_t   TX_buff[];
extern uint8_t   *myPtr;
