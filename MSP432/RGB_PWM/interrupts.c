/**
* @file		interrupts.c
* @author	Manuel Caballero
* @date 	25/10/2016
* @brief 	Interruptions.
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
#include "interrupts.h"


/**
 *  \brief     EUSCIA2_IRQHandler(void) UART interrupt service routine
 *  \details   Store the data from the UART, we will have to receive at least three parameters.
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      31/12/2016
 */
void EUSCIA2_IRQHandler (void)
{
    if (EUSCI_A2->IFG & EUSCI_A_IFG_RXIFG)
    {
        if ( RGBcounter < 2 )
        {
        	ledsRGB[RGBcounter] = EUSCI_A2->RXBUF;
        	RGBcounter++;
        }
        else
        {
        	ledsRGB[2] 	 = 	 EUSCI_A2->RXBUF;
        	RGBcounter	 =	 0;
        	SCB->SCR 	&= 	~SCB_SCR_SLEEPONEXIT_Msk;	// Wake the uC up!
        }

    }
}
