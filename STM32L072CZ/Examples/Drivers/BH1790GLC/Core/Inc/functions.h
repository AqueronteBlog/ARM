/**
 * @brief       functions.h
 * @details     Functions' header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/January/2020
 * @version     16/January/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "board.h"
#include "variables.h"


/**@brief Functions prototypes.
 */
void 			Conf_GPIO 		( void );
uart_status_t	Conf_UART2		( uint32_t myCK, uint32_t myBaudRate );
void 			Conf_Range 		( void );
void 			Conf_TimerTIM2 	( uint32_t myCLK );

#endif /* FUNCTIONS_H_ */
