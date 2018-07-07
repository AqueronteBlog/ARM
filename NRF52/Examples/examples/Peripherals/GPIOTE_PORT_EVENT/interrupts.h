/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/July/2018
 * @version     3/July/2018   The ORIGIN
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
void GPIOTE_IRQHandler ( void );

/* VARIABLES */
extern volatile uint32_t changeLEDsSTATE;



#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */