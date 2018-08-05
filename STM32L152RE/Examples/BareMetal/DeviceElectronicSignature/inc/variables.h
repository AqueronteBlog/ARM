/**
 * @brief       variables.h
 * @details     Constants and variables used by the example.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        4/August/2018
 * @version     4/August/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "stm32l1xx.h"

#ifndef VARIABLES_H_
#define VARIABLES_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   GENERAL MACROS
 */
#define _ROUND32U( x )  ( uint32_t )( x + 0.5 )

/**
 * @brief   GENERAL VARIABLES
 */
volatile uint32_t mySystemCoreClock;			/*!<  System CLK in MHz  		   */
volatile uint32_t myUARTClock;					/*!<  UART CLK in MHz  		   	   */


#ifdef __cplusplus
}
#endif

#endif /* VARIABLES_H_ */
