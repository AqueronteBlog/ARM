/*
 * interrupts.c
 *
 *  Created on: 10 Sep 2016
 *      Author: Manuel
 */
#include "interrupts.h"



/* Port1 ISR */
uint8_t	hola	=	1;
void PORT1_IRQHandler(void)
{
    // Toggling the output on the LED		P1IFG	&=	~( BIT1 | BIT4 );
    if ( ( P1IFG & BIT1 ) == BIT1 )
    {
    	P1OUT	^=	BIT0;
    	P1IFG	&=	~BIT1;
    }

    if ( ( P1IFG & BIT4 ) == BIT4 )
    {
    	switch ( hola ){
        case	1:
        	P2OUT	&=	~( BIT0 | BIT1 | BIT2 );
            P2OUT	|=	 BIT0;
            hola	 =	 2;
            break;

        case	2:
        	P2OUT	&=	~( BIT0 | BIT1 | BIT2 );
            P2OUT	|=	 BIT1;
            hola	 =	 3;
            break;

        case	3:
           	P2OUT	&=	~( BIT0 | BIT1 | BIT2 );
           	P2OUT	|=	 BIT2;
           	hola	 =	 1;
           	break;

        default:
          	P2OUT	&=	~( BIT0 | BIT1 | BIT2 );
           	hola	 =	 1;
           	break;
    	}

    	P1IFG	&=	~BIT4;

    }
}
