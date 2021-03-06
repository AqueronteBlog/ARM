/**
 * @brief       functions.h
 * @details     Functions's header.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        26/December/2017
 * @version     26/December/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "stm32l1xx.h"


/* FUNCTION PROTOTYPES */
void Conf_CLK  	   ( void );
void Conf_GPIO 	   ( void );
void Conf_SYSTICK  ( uint32_t myticks );

#endif /* FUNCTIONS_H_ */
