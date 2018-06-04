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
#include "nrf.h"
#include "nrf51_bitfields.h"


/* INTERRUPT PRTOTYPES */
void TIMER0_IRQHandler ( void );



/* VARIABLES */
//extern uint8_t   dataToBeTX;
extern uint32_t volatile mySTATE;
//extern uint32_t  TX_inProgress;
//extern uint8_t   TX_buff[];
//extern uint8_t   *myPtr;
