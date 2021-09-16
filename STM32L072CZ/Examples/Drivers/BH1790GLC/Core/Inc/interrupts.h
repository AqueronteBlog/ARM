/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/January/2020
 * @version     16/January/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "board.h"


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_


/**@brief Subroutine prototypes.
 */
extern void USART2_IRQHandler 	(void);
extern void TIM2_IRQHandler 	(void);

/**@brief Constants.
 */



/**@brief Variables.
 */
extern volatile uint8_t  myRX;
extern volatile uint8_t  *myPtr;
extern volatile uint32_t myUART_TxEnd;
extern volatile uint32_t myState;

#endif /* INTERRUPTS_H_ */
