/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/May/2017
 * @version     23/May/2017   my375msDelay variable and TIMER2_IRQHandler added
 *              5/May/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */

#include "variables.h"


/* INTERRUPT PRTOTYPES */
void TIMER0_IRQHandler ( void );
void TIMER2_IRQHandler ( void );


/* VARIABLES */
extern uint32_t changeLEDsSTATE;
extern uint32_t my375msDelay;
