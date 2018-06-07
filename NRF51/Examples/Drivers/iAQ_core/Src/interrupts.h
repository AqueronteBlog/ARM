/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        4/June/2018
 * @version     4/June/2018    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "board.h"
#include "variables.h"
#include "nrf.h"
#include "nrf51_bitfields.h"

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* INTERRUPT PRTOTYPES */
void TIMER0_IRQHandler ( void );
void UART0_IRQHandler   ( void );



/* VARIABLES */
extern uint8_t  volatile dataToBeTX;
extern uint32_t volatile mySTATE;
extern uint32_t volatile TX_inProgress;
extern uint8_t  volatile *myPtr;


#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */
