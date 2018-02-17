/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/February/2018
 * @version     17/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "variables.h"

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#ifdef __cplusplus
extern "C" {
#endif


/* INTERRUPT PRTOTYPES */
void TIMER0_IRQHandler ( void );
void TIMER2_IRQHandler ( void );


/* VARIABLES */
extern uint32_t changeLEDsSTATE;
extern uint32_t my375msDelay;


#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */