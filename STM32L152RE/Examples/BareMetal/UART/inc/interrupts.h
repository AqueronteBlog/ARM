/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        3/January/2018
 * @version     3/January/2018   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
#include "variables.h"
#include "board.h"

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#ifdef __cplusplus
extern "C" {
#endif

// PROTOTYPES
void TIM5_IRQHandler  (void);
void UART5_IRQHandler (void);


// VARIABLES


#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */
