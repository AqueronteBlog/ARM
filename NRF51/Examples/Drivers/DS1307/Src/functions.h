/**
 * @brief       functions.h
 * @details     Functions's header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        30/July/2018
 * @version     30/July/2018   The ORIGIN
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


/**@brief Function prototypes.
 */
void conf_CLK    ( void );
void conf_GPIO   ( void );
void conf_TIMER0 ( void );
void conf_UART   ( void );


/**@brief Constants.
 */



/**@brief Variables.
 */



#ifdef __cplusplus
}
#endif

#endif /* FUNCTIONS_H_ */
