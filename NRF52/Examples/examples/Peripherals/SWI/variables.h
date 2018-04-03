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
typedef enum{
  LED1_ON = 0x01,
  LED2_ON = ( LED1_ON << 1 ),
  LED3_ON = ( LED2_ON << 1 ),
  LED4_ON = ( LED3_ON << 1 )
}state_leds_t;


/* VARIABLES */



#ifdef __cplusplus
}
#endif

#endif /* VARIABLES_H_ */