/**
* @file		functions.c
* @author	Manuel Caballero
* @date 	25/10/2016
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
 *  \date      25/10/2016
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
 *  \date      25/10/2016
 */
void conf_WDT (void)
{
	WDTCTL = WDTPW + WDTHOLD;     // Stop watchdog timer
}



/**
 *  \brief     void conf_IO (void)
 *  \details   Configuring all GPIO for this project.
 *  				- Port 1: LED1 & UART.
 *  					- P1.0: OUT ( LED1: RED ).
 *  				- Port 2: LED2 RGB & TA0.1, TA0.2 and TA0.3 OUTPUT.
 *  					- P2.0: OUT ( LED2 RGB: RED ).
 *  					- P2.1: OUT ( LED2 RGB: GREEN ).
 *  					- P2.2: OUT ( LED2 RGB: BLUE ).
 *  					- P2.4: TA0.1.
 *  					- P2.5: TA0.2.
 *  					- P2.6: TA0.3.
 *  				- Port 3: UART.
 *  					- P3.2: IN  ( UART: UCA2RXD ).
 *  					- P3.3: OUT ( UART: UCA2TXD ).
 *
 *  		   The rest GPIO as OUT for low power.
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      11/12/2016
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


	// LED1	( Digital GIPO )
	P1->SEL0	&=	~( BIT0 | BIT1 | BIT4 );
	P1->SEL1	&=	~( BIT0 | BIT1 | BIT4 );

	// UART: UCA2
	P3->SEL0	|=	 ( BIT2 | BIT3 );
	P3->SEL1	&=	~( BIT2 | BIT3 );

	// LED2 RGB	( Digital GIPO )
	P2->SEL0	&=	~( BIT0 | BIT1 | BIT2 );
	P2->SEL1	&=	~( BIT0 | BIT1 | BIT2 );

	// TA0.1, TA0.2 and TA0.3 output
	P2->SEL1	&=	~( BIT4 | BIT5 |BIT6 );
	P2->SEL0	|=	 ( BIT4 | BIT5 |BIT6 );
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
 *  \date      25/10/2016
 */
void conf_TA (void)
{
	TIMER_A0->CCR[0]  =	 94;														// [todo]
	TIMER_A0->CCTL[1] =  TIMER_A_CCTLN_OUTMOD_6; 									// CCR0  Toggle/Set
	TIMER_A0->CCR[1]  =	 95;														// [todo]
	TIMER_A0->CCTL[2] =  TIMER_A_CCTLN_OUTMOD_6; 									// CCR0  Toggle/Set
	TIMER_A0->CCR[2]  =	 52;														// [todo]
	TIMER_A0->CCTL[3] =  TIMER_A_CCTLN_OUTMOD_6; 									// CCR0  Toggle/Set
	TIMER_A0->CCR[3]  =	 0;														// [todo]
	TIMER_A0->CTL	  =	 TIMER_A_CTL_TASSEL_1 | TIMER_A_CTL_MC_1 | TIMER_A_CTL_CLR;	// ACLK, TA0

	//NVIC_EnableIRQ		( TA0_N_IRQn );
	//NVIC_SetPriority	( TA0_N_IRQn, 0 );
}



/**
 *  \brief     void conf_UCA2 (void)
 *  \details   Configura el módulo UART a 9600 Baud Rate.
 *
 * 		· Reloj UART: SMCLK ~ 3 MHz.
 * 		· Buad Rate ~ 9600:
 *
 *     		N = f_BRCLK/BaudRate = 3MHz/9600 ~ 312.5 = {Parte entera} = 312
 *
 *      	N >= 16 -->  Oversampling ON (UCOS16 = 1)
 *
 * 		Por lo tanto:
 *
 *     		UCBRx = INT(N/16) = INT(312/16) = 19
 *     		UCBRFx = ROUND[((N/16) - INT(N/16))·16] = ROUND[((3MHz/9600)/16 - INT((3MHz/9600)/16))·16] ~ 8.5 = 9
 *
 * 		· Activamos UART
 * 	\pre	   [todo] Para ampliar información: Documentos slau144j.pdf, apartado 15 Universal Serial Comunication
 *			   se pueden encontrar datos tabulados a distintas frecuencias.
 * 	\pre	   El reloj SMCLK debe estar a 3 MHz.
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      [todo] 2/2/2015
 */
void conf_UCA2 (void)
{
  EUSCI_A2->CTLW0	|=	 EUSCI_A_CTLW0_SWRST; 										// eUSCI in RESET
  EUSCI_A2->CTLW0	 = 	 ( EUSCI_A_CTLW0_SWRST | EUSCI_A_CTLW0_SSEL__SMCLK );      	// Select clock source from SMCLK ~ 4MHz
  // Baud Rate calculation
  // 3000000/9600/16 = 19.53125
  // Fractional portion = 0.53125
  // User's Guide Table 21-4: UCBRSx = 0xAA ( 170 )
  // UCBRFx = int ( ( 19.53125 - 19 ) * 16 ) = 8.5 ~ 9
  EUSCI_A2->BRW 	 = 	 19;                     									// 3000000/16/9600 = 19.53125
  EUSCI_A2->MCTLW 	 = 	 ( 170 << EUSCI_A_MCTLW_BRS_OFS ) | ( 9 << EUSCI_A_MCTLW_BRF_OFS ) | EUSCI_A_MCTLW_OS16;
  EUSCI_A2->CTLW0 	&= 	~EUSCI_A_CTLW0_SWRST;										// Initialize eUSCI

  EUSCI_A2->IFG 	&= 	~EUSCI_A_IFG_RXIFG;    										// Clear eUSCI RX interrupt flag
  EUSCI_A2->IE 		|= 	 EUSCI_A_IE_RXIE;        									// Enable USCI_A0 RX interrupt

  NVIC_EnableIRQ	( EUSCIA2_IRQn );
  NVIC_SetPriority	( EUSCIA2_IRQn, 0 );
}



void mapRGB ( uint8_t cmd[3] )
{
	uint8_t i = 0;

	for ( i = 0; i < 3; i++ )
		TIMER_A0->CCR[ i + 1 ]  =	 ( ( cmd[i] )*( 95 ) )/( 255 );

}

