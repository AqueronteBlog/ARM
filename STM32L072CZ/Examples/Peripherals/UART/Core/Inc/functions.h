/**
 * @brief       functions.h
 * @details     Functions' header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        18/December/2019
 * @version     18/December/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "board.h"
#include "variables.h"


/**@brief Functions prototypes.
 */
void 			Conf_GPIO 	( void );
uart_status_t	Conf_UART2	( uint32_t myCK, uint32_t myBaudRate );
void 			Conf_Range ( void );


#endif /* FUNCTIONS_H_ */
