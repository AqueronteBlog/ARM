/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        30/June/2018
 * @version     30/June/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "nrf.h"
#include "nrf52_bitfields.h"
#include "board.h"
#include "variables.h"


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#ifdef __cplusplus
extern "C" {
#endif


/* INTERRUPT PRTOTYPES */



/* CONSTANTS */
void GPIOTE_IRQHandler ( void );
void UART0_IRQHandler  ( void );


/* VARIABLES */
extern uint32_t volatile startCycle;
extern uint32_t volatile myTX;
extern uint8_t  volatile TX_inProgress;
extern uint8_t  volatile dataToBeTX;                    



#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */