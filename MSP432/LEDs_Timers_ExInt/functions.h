/**
* @file		functions.h
* @author	Manuel Caballero
* @date 	10/9/2016
* @brief 	Prototipo de funciones.
* \copyright
* 	AqueronteBlog@gmail.com
*
* Este archivo es propiedad intelectual del blog Aqueronte,
* cuya direccion web, es la siguiente:
*
* 	http://unbarquero.blogspot.com/
*
* Se permite cualquier modificacion del archivo siempre y cuando
* se mantenga la autoria del autor.
*/

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_


#include "msp.h"
#include <stdint.h>


// PROTOTIPO DE FUNCIONES
//void conf_CLK           (void);
void conf_WDT           (void);
void conf_IO            (void);
void conf_TA	        (void);


// VARIABLES EXTERNAS
// extern volatile uint8_t 	ADC10_Buffer [3];




#endif /* FUNCTIONS_H_ */
