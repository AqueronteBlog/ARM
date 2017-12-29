/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/December/2017
 * @version     29/December/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
#include "variables.h"


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#ifdef __cplusplus
extern "C" {
#endif

void SysTick_Handler (void);

// VARIABLES
extern uint32_t myDelay;

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */
