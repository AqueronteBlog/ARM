/**
 * @brief       functions.h
 * @details     Functions's header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        6/July/2018
 * @version     6/July/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "nrf.h"
#include "nrf52_bitfields.h"
#include "board.h"

#ifndef FUNCTION_H_
#define FUNCTION_H_

#ifdef __cplusplus
extern "C" {
#endif


/* FUNCTION PROTOTYPES */
void conf_CLK     ( void );
void conf_LFCLK   ( void );
void conf_GPIO    ( void );
void conf_UART0   ( void );
void conf_TEMP    ( void );
void conf_RTC2    ( void );



#ifdef __cplusplus
}
#endif

#endif /* FUNCTION_H_ */