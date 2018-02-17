/**
 * @brief       functions.h
 * @details     Functions header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/February/2018
 * @version     17/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "nrf.h"
#include "nrf52_bitfields.h"
#include "variables.h"

#ifndef FUNCTION_H_
#define FUNCTION_H_

#ifdef __cplusplus
extern "C" {
#endif


/* FUNCTION PROTOTYPES */
void conf_GPIO      ( void );
void conf_TIMER0    ( void );
void conf_TIMER1    ( void );
void conf_TIMER2    ( void );
void delay          ( void );


#ifdef __cplusplus
}
#endif

#endif /* FUNCTION_H_ */