/**
 * @brief       functions.h
 * @details     Functions's header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/July/2018
 * @version     17/July/2018   The ORIGIN
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


/**@brief Function prototypes.
 */
void conf_LFCLK  ( void );
void conf_GPIO   ( void );
void conf_PPI    ( void );
void conf_RTC1   ( void );
void conf_GPIOTE ( void );



#ifdef __cplusplus
}
#endif

#endif /* FUNCTION_H_ */