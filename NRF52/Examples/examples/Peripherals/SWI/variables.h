/**
 * @brief       variables.h
 * @details     Constants and variables used by the example.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/April/2018
 * @version     3/April/2018   The ORIGIN
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
/* VARIABLES */
static uint32_t changeLEDsSTATE;       /*!<   changeLEDsSTATE = ON     
                                              changeLEDsSTATE = OFF      */


#ifdef __cplusplus
}
#endif

#endif /* VARIABLES_H_ */