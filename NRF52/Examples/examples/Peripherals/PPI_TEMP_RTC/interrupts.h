/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/July/2018
 * @version     14/July/2018   The ORIGIN
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
extern volatile uint8_t  myMessage[];
extern volatile uint8_t  *myPtr;
extern volatile uint32_t myTEMP;
extern volatile uint32_t myState;
extern volatile uint32_t myTEMPFlag;


#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */