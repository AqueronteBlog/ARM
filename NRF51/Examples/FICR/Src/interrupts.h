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
 * @pre         NaN
 * @warning     NaN
 */

#include "variables.h"


/* INTERRUPT PRTOTYPES */
void GPIOTE_IRQHandler ( void );

/* VARIABLES */
extern uint32_t changeLEDsSTATE;
