/**
* @file		functions.c
* @author	Manuel Caballero
* @date 	10/9/2016
* @brief 	Functions.
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
#include "functions.h"


/**
 *  \brief     void conf_CLK (void)
 *  \details   Configuring the CLKs for the uC.
 *  				- MCLK:  MCLK  = DCO    ~ 3 MHz ( default ).
 *  				- ACLK:  ACLK  = VLOCLK ~ 9.4 kHz ( reference manual slau356d 5.1 Clock System Introduction ).
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      11/9/2016
 */

void conf_CLK (void)
{
	CS->KEY = CS_KEY_VAL;                   // Unlock CS module for register access
	//CS->CLKEN	|=	CS_CLKEN_VLO_EN;
	CS->CTL1 |= CS_CTL1_SELA_1;				// Select ACLK = VLOCLK
	CS->KEY = 0;                            // Lock CS module from unintended accesses
}



/**
 *  \brief     void conf_WDT (void)
 *  \details   Turning down the Watchdog.
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      10/9/2016
 */
void conf_WDT (void)
{
	WDTCTL = WDTPW + WDTHOLD;     // Stop watchdog timer
}



/**
 *  \brief     void conf_IO (void)
 *  \details   Configuring all GPIO for this project.
 *  				- Port 1: LED1 & SW1 & SW2.
 *  					- P1.0: OUT ( LED1: RED ).
 *  					- P1.1: IN  ( SW1).		Interruption ON
 *  					- P1.2: IN  ( SW2 ).	Interruption ON
 *  				- Port 2: LED2 RGB.
 *  					- P2.0: OUT ( LED2 RGB: RED ).
 *  					- P2.1: OUT ( LED2 RGB: GREEN ).
 *  					- P2.2: OUT ( LED2 RGB: BLUE ).
 *
 *  		   The rest GPIO as OUT for low power.
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      11/5/2015
 */
void conf_IO (void)
{
	// GPIO Port Configuration for lowest power configuration
	P1->OUT  = 0x00; 	P1->DIR  = 0xFF;
	P2->OUT  = 0x00; 	P2->DIR  = 0xFF;
	P3->OUT  = 0x00; 	P3->DIR  = 0xFF;
	P4->OUT  = 0x00; 	P4->DIR  = 0xFF;
	P5->OUT  = 0x00; 	P5->DIR  = 0xFF;
	P6->OUT  = 0x00; 	P6->DIR  = 0xFF;
	P7->OUT  = 0x00; 	P7->DIR  = 0xFF;
	P8->OUT  = 0x00; 	P8->DIR  = 0xFF;
	P9->OUT  = 0x00; 	P9->DIR  = 0xFF;
	P10->OUT = 0x00;	P10->DIR = 0xFF;
	PJ->OUT	 = 0x00;	PJ->DIR	 = 0xFF;


	// SW 1 & 2
	P1->DIR	&=	~( BIT1 | BIT4 );
	P1->OUT	|=	 ( BIT1 | BIT4 );
	P1->REN	|=	 ( BIT1 | BIT4 );

	// LED1	( Digital GIPO )
	P1->SEL0	&=	~( BIT0 | BIT1 | BIT4 );
	P1->SEL1	&=	~( BIT0 | BIT1 | BIT4 );

	// LED2 RGB	( Digital GIPO )
	P2->SEL0	&=	~( BIT0 | BIT1 | BIT2 );
	P2->SEL1	&=	~( BIT0 | BIT1 | BIT2 );


	P1->IES	|=	 ( BIT1 | BIT4 );
	P1->IFG	&=	~( BIT1 | BIT4 );

	P1->IE	|=	 ( BIT1 | BIT4 );


	NVIC_EnableIRQ		( PORT1_IRQn );
	NVIC_SetPriority	( PORT1_IRQn, 0 );
}




/**
 *  \brief     void conf_TimerA (void)
 *  \details   Configuring the TimerA0.
 *
 * 			   TimerA0 will carry out the task trying to eliminate the switch´s bouncing
 * 			   by using a short delay about 100 ms ( 1410/(~9.4kHz) ~ 150ms ).
 *
 * 	\pre	   ACK clock must be at 9.4 kHz.
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      11/9/2016
 */
void conf_TA (void)
{
	TIMER_A0->CCR[0] =	 1410;														// TAIFG on around ~ 150ms
	TIMER_A0->CTL	 =	 TIMER_A_CTL_TASSEL_1 | TIMER_A_CTL_CLR | TIMER_A_CTL_IE;	// ACLK, TA0 interrupt ON

	NVIC_EnableIRQ		( TA0_N_IRQn );
	NVIC_SetPriority	( TA0_N_IRQn, 0 );
}

