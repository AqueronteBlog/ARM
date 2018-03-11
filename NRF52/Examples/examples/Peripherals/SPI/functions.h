/**
 * @brief       functions.h
 * @details     Functions header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/March/2018
 * @version     10/March/2018   The ORIGIN
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
void conf_SPI0      ( void );
void conf_SPIS1     ( void );
void conf_TIMER0    ( void );


/* VARIABLES */
extern uint32_t  mySPIS_RX;
extern uint32_t  mySPIS_TX;


#ifdef __cplusplus
}
#endif

#endif /* FUNCTION_H_ */