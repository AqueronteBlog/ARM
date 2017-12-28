/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        26/December/2017
 * @version     26/December/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
#include "variables.h"


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_


void SysTick_Handler (void);

// VARIABLES
extern uint32_t myDelay;

#endif /* INTERRUPTS_H_ */
