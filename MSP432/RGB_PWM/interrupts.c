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
 *  \details   [todo]Generate a short delay trying to get rid of the bouncing
 *
 *  		   [todo]It will turn on the PORT1 interruption when the bouncing has been eliminated
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      [todo] 25/10/2016
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
        	SCB->SCR 	&= 	~SCB_SCR_SLEEPONEXIT_Msk;
        }

    }
}



/**
 *  \brief     TA0_N_IRQHandler(void) TIMERA0 IFG interrupt service routine
 *  \details   Generate a short delay trying to get rid of the bouncing
 *
 *  		   It will turn on the PORT1 interruption when the bouncing has been eliminated
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      25/10/2016
 */
/*
void TA0_N_IRQHandler(void)
{
	switch ( TIMER_A0->IV ){
		case	0x00:
		// Vector 0:	No interrupts
			break;

		case	0x02:
		// Vector 2:	 Interrupt Source: Capture/compare 1; Interrupt Flag: TAxCCR1 CCIFG  Interrupt Priority: Highest
			break;

		case	0x04:
		// Vector 4:	 Interrupt Source: Capture/compare 2; Interrupt Flag: TAxCCR2 CCIFG
			break;

		case	0x06:
		// Vector 6:	 Interrupt Source: Capture/compare 3; Interrupt Flag: TAxCCR3 CCIFG
			break;

		case	0x08:
		// Vector 8:	 Interrupt Source: Capture/compare 4; Interrupt Flag: TAxCCR4 CCIFG
			break;

		case	0x0A:
		// Vector A:	 Interrupt Source: Capture/compare 5; Interrupt Flag: TAxCCR5 CCIFG
			break;

		case	0x0C:
		// Vector C:	 Interrupt Source: Capture/compare 6; Interrupt Flag: TAxCCR6 CCIFG
			break;

		case	0x0E:
		// Vector E:	 Interrupt Source: Timer overflow; Interrupt Flag: TAxCTL TAIFG; Interrupt Priority: Lowest
			TIMER_A0->CTL	&=	 ~TIMER_A_CTL_IFG;
			break;

		default:
			break;
	}


	// Try to get rid of the switch bouncing
	if ( ( ( P1->IFG & BIT4 ) == BIT4 ) || ( ( P1->IFG & BIT1 ) == BIT1 ) )
	{
		 P1->IFG	&=	~( BIT1 | BIT4 );
	}
	else
	{
		TIMER_A0->CTL	&=	 ~TIMER_A_CTL_MC_1;
		NVIC_EnableIRQ	( PORT1_IRQn );
	}
}
*/
