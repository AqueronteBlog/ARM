/**
* @file		variables.h
* @author	Manuel Caballero
* @date 	25/10/2016
* @brief 	Variables header.
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

#ifndef VARIABLES_H_
#define VARIABLES_H_


/**
 *  \brief     Global variables
 *  \details
 *  			- cledRGB:	It is useful to select which RGB LED to choose.
 *  							* cledRGB	=	1:	RGB LED2: RED colour
 *  							* cledRGB	=	2:	RGB LED2: GREEN colour
 *  							* cledRGB	=	3:	RGB LED2: BLUE colour
 */
uint8_t	ledsRGB[]	=	{ 0, 0, 0 };
uint8_t RGBcounter  =   0;

#endif /* VARIABLES_H_ */
