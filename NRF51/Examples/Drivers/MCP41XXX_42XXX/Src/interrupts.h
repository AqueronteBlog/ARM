/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        21/August/2018
 * @version     21/August/2018    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "board.h"
#include "variables.h"
#include "nrf.h"
#include "nrf51_bitfields.h"

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#ifdef __cplusplus
extern "C" {
#endif


/**@brief Subroutine prototypes.
 */
void TIMER0_IRQHandler ( void );



/**@brief Constants.
 */



/**@brief Variables.
 */
extern volatile uint32_t myState;




#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */
