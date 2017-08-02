/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/June/2017
 * @version     29/June/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "variables.h"


/* INTERRUPT PRTOTYPES */
void RTC0_IRQHandler ( void );
void SWI0_IRQHandler ( void );
void SWI1_IRQHandler ( void );
void SWI2_IRQHandler ( void );
void SWI3_IRQHandler ( void );
void SWI4_IRQHandler ( void );
// void SWI5_IRQHandler ( void );


/* VARIABLES */
extern uint32_t chooseLEDON;
