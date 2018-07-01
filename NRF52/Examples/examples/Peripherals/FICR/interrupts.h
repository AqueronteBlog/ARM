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
void RTC0_IRQHandler ( void );


/* VARIABLES */
extern uint32_t writeNVMC;


#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */