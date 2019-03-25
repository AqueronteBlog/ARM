/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        25/March/2019
 * @version     25/March/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "nrf.h"
#include "nrf52_bitfields.h"
#include "board.h"

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#ifdef __cplusplus
extern "C" {
#endif


/* INTERRUPT PRTOTYPES */
void UART0_IRQHandler ( void );


/* CONSTANTS */
extern const uint32_t  NO;
extern const uint32_t  YES;

/* VARIABLES */
extern uint8_t myRX_buff;
extern uint8_t myMessage[];
extern uint8_t *myPtr;
extern uint8_t TX_inProgress;


#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */