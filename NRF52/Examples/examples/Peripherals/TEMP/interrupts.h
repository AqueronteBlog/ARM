/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        6/July/2018
 * @version     6/July/2018   The ORIGIN
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



/* VARIABLES */
extern uint8_t myMessage[];
extern uint8_t *myPtr;



#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */