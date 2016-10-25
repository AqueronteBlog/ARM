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
 *  \brief     PORT1_IRQHandler(void) PORT1 interrupt service routine
 *  \details   Every time that SW1 or SW2 is pressed, it will generate an interruption
 *  		   and it will turn on the associated LED.
 *
 *  		   It will turn on the TimerA0 trying to eliminate the bouncing
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      25/10/2016
 */
void PORT1_IRQHandler(void)
{
    // LED1
    if ( ( P1->IFG & BIT1 ) == BIT1 )
    {
    	P1->OUT	^=	 BIT0;
    	P1->IFG	&=	~BIT1;
    }

    // RGB LED2
    if ( ( P1->IFG & BIT4 ) == BIT4 )
    {
    	switch ( cledRGB ){
        case	1:
        	P2->OUT	&=	~( BIT0 | BIT1 | BIT2 );
            P2->OUT	|=	 BIT0;
            cledRGB	 =	 2;
            break;

        case	2:
        	P2->OUT	&=	~( BIT0 | BIT1 | BIT2 );
            P2->OUT	|=	 BIT1;
            cledRGB	 =	 3;
            break;

        case	3:
           	P2->OUT	&=	~( BIT0 | BIT1 | BIT2 );
           	P2->OUT	|=	 BIT2;
           	cledRGB	 =	 1;
           	break;

        default:
          	P2->OUT	&=	~( BIT0 | BIT1 | BIT2 );
          	cledRGB	 =	 1;
           	break;
    	}

    	P1->IFG	&=	~BIT4;

    }

    NVIC_DisableIRQ	( PORT1_IRQn );
    TIMER_A0->CTL	|=	 TIMER_A_CTL_MC_1;		// TimerA0 ON: Try to get rid of the swicth bouncing
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
