/**
 * @brief       functions.h
 * @details     Functions's header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/October/2018
 * @version     9/October/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "stm32l1xx.h"
#include "variables.h"


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* FUNCTION PROTOTYPES */
void Conf_CLK  	   ( void );
void Conf_GPIO 	   ( void );
void Conf_RTC 	   ( void );
void Conf_SYSTICK  ( uint32_t myticks );
void Conf_USART	   ( uint32_t myCK, uint32_t myBaudRate );
void Conf_ADC 	   ( void );


#ifdef __cplusplus
}
#endif

#endif /* FUNCTIONS_H_ */
