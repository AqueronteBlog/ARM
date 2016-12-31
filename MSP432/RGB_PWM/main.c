/**
* @file		main.c
* @author	Manuel Caballero
* @date 	25/10/2016
* @brief 	Archivo principal.
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


#include "msp.h"
#include "variables.h"
#include "functions.h"
#include "interrupts.h"


/**
 *  \brief     void main( void )
 *  \details   We are going to play with: MSP432P401R LaunchPad.
 *
 *  		   [TODO] This firmware will change the state of the LED1 and LED2 ( RGB LED ) by using
 *  		   the switches SW1 ( LED1 ) and SW2 ( RGB LED2 ).
 *
 *			   Every time that one of the switches is pressed, we will notice the case of bouncing,
 *			   that is why we are going to use the TimerA0 to generate a short delay trying to
 *			   get rid of this fenomenon.
 *
 *  		   The rest of the time, the uC will be in LPM0 low power
 *
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      25/10/2016
 *  \pre	   Code Composer Studio, Version: 6.1.3.00034.
 *  \pre	   C Compiler, MSP432 TI v16.6.0.STS.
 */

void main(void)
{
	conf_CLK	();
	conf_WDT	();
	conf_IO 	();
	conf_TA		();
	conf_UCA2	();

	
	__enable_irq();


	while (1){
		// Do not wake up on exit from ISR
		SCB->SCR	|=	 SCB_SCR_SLEEPONEXIT_Msk;
		__sleep	();

		mapRGB ( ledsRGB );
	}
}
