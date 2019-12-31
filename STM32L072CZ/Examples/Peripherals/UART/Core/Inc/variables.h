/**
 * @brief       variables.h
 * @details     Constants and variables used by the example.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        18/December/2019
 * @version     18/December/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "stm32l0xx_hal.h"

#ifndef VARIABLES_H_
#define VARIABLES_H_

/**
  * @brief   UART. INTERNAL CONSTANTS
  */
typedef enum
{
    UART_SUCCESS  	     			=   0x00,
    UART_FAILURE  		 			=   0x01,
	UART_OVERSAMPLING_INCOMPATIBLE	=   0x02
} uart_status_t;


#endif /* VARIABLES_H_ */
