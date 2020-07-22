/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/July/2020
 * @version     22/July/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "board.h"


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "board.h"


/**@brief Subroutine prototypes.
 */
extern void UART_Int_Handler 	( void );
extern void GP_Tmr0_Int_Handler ( void );


/**@brief Constants.
 */



/**@brief Variables.
 */
extern volatile uint32_t  myState;
extern volatile uint8_t   *myPtr;


#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */
