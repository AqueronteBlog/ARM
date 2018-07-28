/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        27/July/2018
 * @version     27/July/2018   The ORIGIN
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


/**@brief Subroutine prototypes.
 */
void TIMER0_IRQHandler ( void );
void UART0_IRQHandler  ( void );
void SAADC_IRQHandler  ( void );


/**@brief Constants.
 */



/**@brief Variables.
 */
extern volatile uint32_t myState;         
extern volatile uint8_t  myMessage[];
extern volatile uint8_t  *myPtr;
extern volatile uint32_t myADCDoneFlag;


#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */