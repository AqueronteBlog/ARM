/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        14/November/2017
 * @version     14/November/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "variables.h"


/* INTERRUPT PRTOTYPES */
void UART0_IRQHandler  ( void );
void ADC_IRQHandler    ( void );
void RTC1_IRQHandler   ( void );



/* VARIABLES */
extern uint8_t myADCvalue;

