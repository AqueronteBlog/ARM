/**
 * @brief       functions.h
 * @details     Functions's header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        6/April/2018
 * @version     6/April/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */

#include "nrf.h"
#include "nrf51_bitfields.h"
#include "variables.h"

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif


/* FUNCTION PROTOTYPES */
void conf_GPIO      ( void );
void conf_UART      ( void );
void conf_GPIOTE    ( void );

#ifdef __cplusplus
}
#endif

#endif /* FUNCTIONS_H_ */
