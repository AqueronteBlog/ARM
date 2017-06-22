/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        21/June/2017
 * @version     21/June/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */

#include "variables.h"


/* INTERRUPT PRTOTYPES */
void UART0_IRQHandler ( void );


/* VARIABLES */
extern uint8_t myRX_buff;
extern uint8_t myRandomNumber;
extern uint8_t TX_inProgress;
