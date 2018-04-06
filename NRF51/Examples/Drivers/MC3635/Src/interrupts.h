/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        6/April/2018
 * @version     6/April/2018    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */

#include "variables.h"

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#ifdef __cplusplus
extern "C" {
#endif


/* INTERRUPT PRTOTYPES */
void UART0_IRQHandler  ( void );
void GPIOTE_IRQHandler ( void );


/* VARIABLES */
extern uint8_t   dataToBeTX;
extern uint32_t  mySTATE;
extern uint32_t  TX_inProgress;
extern uint8_t   TX_buff[];
extern uint8_t   *myPtr;

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */
