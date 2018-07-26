/**
 * @brief       functions.h
 * @details     Functions's header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        4/June/2018
 * @version     4/June/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "nrf.h"
#include "nrf51_bitfields.h"
#include "board.h"

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif


/* FUNCTION PROTOTYPES */
void conf_GPIO      ( void );
void conf_TIMER0    ( void );
void conf_UART      ( void );


#ifdef __cplusplus
}
#endif

#endif /* FUNCTIONS_H_ */
