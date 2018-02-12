/**
 * @brief       variables.h
 * @details     Constants and variables used by the example.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        12/February/2018
 * @version     12/February/2018   The ORIGIN
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
static uint32_t changeLEDsSTATE;       /*!<   changeLEDsSTATE = ON:     Turn off all the LEDs.
                                              changeLEDsSTATE = OFF:    Turn on all the LEDs       */


#ifdef __cplusplus
}
#endif

#endif /* VARIABLES_H_ */