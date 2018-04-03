/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/April/2018
 * @version     3/April/2018   The ORIGIN
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
void RTC0_IRQHandler      ( void );
void SWI5_EGU5_IRQHandler ( void );
void SWI1_EGU1_IRQHandler ( void );
void SWI3_EGU3_IRQHandler ( void );
void SWI4_EGU4_IRQHandler ( void );


/* VARIABLES */
extern uint32_t chooseLEDON;


#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */