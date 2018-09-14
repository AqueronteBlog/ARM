/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/September/2018
 * @version     14/September/2018    The ORIGIN
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
void RTC1_IRQHandler   ( void );



/**@brief Constants.
 */



/**@brief Variables.
 */
extern volatile uint32_t myState;
extern volatile uint8_t  *myPtr;



#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */
