/**
 * @brief       variables.h
 * @details     Constants and variables used by the example.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/January/2018
 * @version     5/January/2018   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
#include "stm32l1xx.h"

#ifndef VARIABLES_H_
#define VARIABLES_H_

#ifdef __cplusplus
extern "C" {
#endif

#define _ROUND32U( x )  ( uint32_t )( x + 0.5 )

/**
      * @brief   GENERAL VARIABLES
      */
uint32_t mySystemCoreClock;					/*!<  System CLK in MHz  		   */
uint32_t myUARTClock;						/*!<  UART CLK in MHz  		   	   */


#ifdef __cplusplus
}
#endif

#endif /* VARIABLES_H_ */
