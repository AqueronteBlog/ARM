/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        8/June/2017
 * @version     8/June/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */

#include "variables.h"


/* INTERRUPT PRTOTYPES */
void RTC0_IRQHandler ( void );
void RTC1_IRQHandler ( void );


/* VARIABLES */
extern uint32_t changeLEDsSTATE;
