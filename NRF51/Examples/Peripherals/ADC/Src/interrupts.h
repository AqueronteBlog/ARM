/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        2/June/2017
 * @version     7/June/2017    Variables to handle the UART added.
 *              2/June/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "variables.h"


/* INTERRUPT PRTOTYPES */
void UART0_IRQHandler  ( void );
void TIMER0_IRQHandler ( void );
void ADC_IRQHandler    ( void );



/* VARIABLES */
extern uint8_t myADCvalue;
