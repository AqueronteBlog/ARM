/**
 * @brief       functions.h
 * @details     Functions's header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        25/March/2019
 * @version     25/March/2019   The ORIGIN
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
void conf_GPIO    ( void );
void conf_UARTE   ( void );


#ifdef __cplusplus
}
#endif

#endif /* FUNCTION_H_ */