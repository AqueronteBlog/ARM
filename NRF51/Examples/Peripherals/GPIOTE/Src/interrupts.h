/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        12/April/2017
 * @version     12/April/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */

#include "variables.h"


/* INTERRUPT PRTOTYPES */
void GPIOTE_IRQHandler ( void );

/* VARIABLES */
extern uint32_t changeLEDsSTATE;
