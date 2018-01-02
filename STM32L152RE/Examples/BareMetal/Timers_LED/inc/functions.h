/**
 * @brief       functions.h
 * @details     Functions's header.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/December/2017
 * @version     29/December/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
#include "stm32l1xx.h"


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* FUNCTION PROTOTYPES */
void Conf_CLK  	   ( void );
void Conf_GPIO 	   ( void );
void Conf_SYSTICK  ( uint32_t myticks );

#ifdef __cplusplus
}
#endif

#endif /* FUNCTIONS_H_ */
