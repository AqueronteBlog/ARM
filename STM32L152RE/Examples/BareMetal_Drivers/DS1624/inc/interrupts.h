/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/January/2018
 * @version     5/January/2018   The ORIGIN
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
void UART5_IRQHandler (void);


// VARIABLES
NUCLEOL152_led_pinout_t myLED1;


#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */
