/**
* @file		functions.c
* @author	Manuel Caballero
* @date 	10/9/2016
* @brief 	Funciones del sistema.
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
 *  \details   Configura los relojes del MCU.
 *  				- Reloj Principal:  MCLK  = DCO    ~ 20 MHz.
 *  				- Reloj Secundario: SMCLK = DCO    ~ 20 MHz.
 *  				- Reloj Auxiliar: 	ACLK  = VLOCLK ~ 8.3 kHz ( datasheet msp430FR5739 5.14. Internal Very-Low-Power Low-Frequency Oscillator ).
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      20/3/2015
 */
/*
void conf_CLK (void)
{
  CSCTL0_H	 =	CSKEY_H;				// Unlock register
  CSCTL1     =	DCORSEL + DCOFSEL_1;	// DC0 ~ 20 MHz
  CSCTL3	 =	DIVS_0 + DIVM_0;
  CSCTL2    |=	SELA_1;					// ACLK = VLOCLK
  CSCTL0_H 	 =	0x01;					// Lock register
}
*/


/**
 *  \brief     void conf_WDT (void)
 *  \details   Desactiva el Watchdog del MCU.
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
 *  \details   Configura los pines del MCU a usar en este proyecto.
 *  				- Puerto 2: UART.
 *  					- P2.0: Salida  ( TX UART ).
 *  					- P2.1: Entrada ( RX UART ).
 *  				- Puerto 3: LEDs.
 *  					- P3.4: Salida ( LED5 ).
 *  					- P3.5: Salida ( LED6 ).
 *  					- P3.6: Salida ( LED7 ).
 *  					- P3.7: Salida ( LED8 ).
 *  				- Puerto J: LEDs.
 *  					- PJ.0: Salida ( LED1 ).
 *  					- PJ.1: Salida ( LED2 ).
 *  					- PJ.2: Salida ( LED3 ).
 *  					- PJ.3: Salida ( LED4 ).
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      11/5/2015
 */
void conf_IO (void)
{
	// SW 1 & 2
	P1DIR	&=	~( BIT1 | BIT4 );
	P1OUT	|=	 ( BIT1 | BIT4 );
	P1REN	|=	 ( BIT1 | BIT4 );

	// LED1
	P1DIR	|=	 BIT0;
	P1OUT	&=	~BIT0;

	P1SEL0	&=	~( BIT0 | BIT1 | BIT4 );
	P1SEL1	&=	~( BIT0 | BIT1 | BIT4 );

	// LED2 ( RGB )
	P2DIR	|=	 ( BIT0 | BIT1 | BIT2 );
	P2OUT	&=	~( BIT0 | BIT1 | BIT2 );

	P2SEL0	&=	~( BIT0 | BIT1 | BIT2 );
	P2SEL1	&=	~( BIT0 | BIT1 | BIT2 );


	P1IES	|=	 ( BIT1 | BIT4 );
	P1IFG	&=	~( BIT1 | BIT4 );

	NVIC_EnableIRQ		( PORT1_IRQn );
	//NVIC->ISER[1] = 1 << ( PORT1_IRQn );


	NVIC_SetPriority	( PORT1_IRQn, 0 );


	P1IE	|=	 ( BIT1 | BIT4 );


	//PJOUT	&= 	~( BIT0 + BIT1 + BIT2 + BIT3 );		// reset PINs
	//PJDIR	|=	 BIT0 + BIT1 + BIT2 + BIT3;


	  // Configure UART pins P2.0 ( Tx ) & P2.1 ( Rx )
	//P2SEL1 	|= 	 BIT0 + BIT1;
	//P2SEL0 	&= 	~( BIT0 + BIT1 );
}


/*
    // Terminate all remaining pins on the device
    P2->DIR |= 0xFF; P2->OUT = 0;
    P3->DIR |= 0xFF; P3->OUT = 0;
    P4->DIR |= 0xFF; P4->OUT = 0;
    P5->DIR |= 0xFF; P5->OUT = 0;
    P6->DIR |= 0xFF; P6->OUT = 0;
    P7->DIR |= 0xFF; P7->OUT = 0;
    P8->DIR |= 0xFF; P8->OUT = 0;
    P9->DIR |= 0xFF; P9->OUT = 0;
    P10->DIR |= 0xFF; P10->OUT = 0;

    // Configure Port J
    PJ->DIR |= (BIT0| BIT1 | BIT2 | BIT3);
    PJ->OUT &= ~(BIT0 | BIT1 | BIT2 | BIT3);

    // Enable PCM rude mode, which allows to device to enter LPM3 without waiting for peripherals
    PCM->CTL1 = PCM_CTL0_KEY_VAL | PCM_CTL1_FORCE_LPM_ENTRY;

    // Enable global interrupt
    __enable_irq();

    // Do not wake up on exit from ISR
    SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;

    // Setting the sleep deep bit
    SCB->SCR |= (SCB_SCR_SLEEPDEEP_Msk);
    // Go to LPM4
    __sleep();



*/


/**
 *  \brief     void conf_TimerA (void)
 *  \details   Configura el timer TA0 como Up Mode.
 *
 * 			   El TA0 será encargado de despertar al MCU del estado
 * 			   bajo consumo en, aproximadamente 3 s (24900/(~8.3kHz) ~ 3s).
 *
 * 	\pre	   El reloj ACLK debe estar a 8.3 kHz.
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      11/5/2015
 */
void conf_TA (void)
{
  TA0CCR0 = 24900;		                	// TAIFG on around ~ 3s
  TA0CTL  = TASSEL_1 + MC_1 + TACLR + TAIE;	// ACLK, upmode, TA0 interrupt ON
}

