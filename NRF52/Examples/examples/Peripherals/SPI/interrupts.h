/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/March/2018
 * @version     10/March/2018   The ORIGIN
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
void WDT_IRQHandler ( void );


/* VARIABLES */


#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */