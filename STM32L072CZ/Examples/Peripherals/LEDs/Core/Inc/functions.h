/**
 * @brief       functions.h
 * @details     Functions' header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        29/September/2019
 * @version     29/September/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "stm32l0xx_hal.h"


/**@brief Functions prototypes.
 */
void Conf_CLK  	   ( void );
void Conf_GPIO 	   ( void );
void Conf_SYSTICK  ( uint32_t myticks );



#endif /* FUNCTIONS_H_ */
