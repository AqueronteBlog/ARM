/**
 * @brief       variables.h
 * @details     Constants and variables used by the example.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        7/March/2018
 * @version     7/March/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "nrf.h"
#include "nrf52_bitfields.h"
#include "board.h"

#ifndef VARIABLES_H_
#define VARIABLES_H_

#ifdef __cplusplus
extern "C" {
#endif


/* CONSTANTS */
#define ON  1
#define OFF 0


/* VARIABLES */
static uint32_t changeLEDsSTATE;       /*!<   0x01 = LED1
                                              0x02 = LED2
                                              0x04 = LED3
                                              0x08 = LED4       */

#ifdef __cplusplus
}
#endif

#endif /* VARIABLES_H_ */