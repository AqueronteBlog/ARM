/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/July/2020
 * @version     22/July/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "functions.h"



/**
 * @brief       void conf_CLK  ( void )
 * @details     It activates the external HFOSC crystal oscillator ( 26MHz ).
 *
 * 					- ACLK: HFOSC/4 = 6.4MHz
 * 					- HCLK: HFOSC/4 = 6.4MHz
 * 					- PCLK: HFOSC/4 = 6.4MHz
 *
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/July/2020
 * @version     22/July/2020      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_CLK  ( void )
{
	/* Disable key protection for clock oscillator	 */
	pADI_CLKG0_OSC->KEY	 =	 0xCB14U;

	/*
	 * - Internal 32 kHz oscillator is selected
	 * - The HFOSC oscillator ( 26MHz ) is enabled
	 */
	pADI_CLKG0_OSC->CTL	&=	~( 1U << BITP_CLKG_OSC_CTL_LFCLKMUX );
	pADI_CLKG0_OSC->CTL	|=	 ( 1U << BITP_CLKG_OSC_CTL_HFOSCEN  );

	/* Configure dividers
	 *  - ACLK/4 = 26MHz/4 = 6.5MHz
	 *  - HCLK/4 = 26MHz/4 = 6.5MHz
	 *  - PCLK/4 = 26MHz/4 = 6.5MHz
	 */
	pADI_CLKG0_CLK->CTL1	&=	~( ( 0b11111111 << BITP_CLKG_CLK_CTL1_ACLKDIVCNT ) | ( 0b111111 << BITP_CLKG_CLK_CTL1_PCLKDIVCNT ) | ( 0b111111 << BITP_CLKG_CLK_CTL1_HCLKDIVCNT ) );
	pADI_CLKG0_CLK->CTL1	|=	 ( ( 0b00000100 << BITP_CLKG_CLK_CTL1_ACLKDIVCNT ) | ( 0b000100 << BITP_CLKG_CLK_CTL1_PCLKDIVCNT ) | ( 0b000100 << BITP_CLKG_CLK_CTL1_HCLKDIVCNT ) );

	/* Wait for HFOSC and LFXTAL to stabilize */
	while ( ( pADI_CLKG0_OSC->CTL & ( ( 1U << BITP_CLKG_OSC_CTL_HFOSCOK ) | ( 1U << BITP_CLKG_OSC_CTL_LFOSCOK ) ) ) != ( ( 1U << BITP_CLKG_OSC_CTL_HFOSCOK ) | ( 1U << BITP_CLKG_OSC_CTL_LFOSCOK ) ) )
	{
	}

	/* Block registers	 */
	pADI_CLKG0_OSC->KEY	 =	 0x0000U;
}



/**
 * @brief       void conf_GPIO  ( void )
 * @details     It configures GPIOs.
 *
 * 				- PORT0:
 * 					UART_Tx: P0_10
 * 					UART_Rx: P0_11
 *
 * 				- PORT1:
 * 					DS4 ( LED2 ): P1_15
 *
 * 				- PORT2:
 * 					DS2 ( LED1 ): P2_00
 *
 *
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/July/2020
 * @version     22/July/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO  ( void )
{
	/* UART pins: Multiplexed function 1	 */
	pADI_GPIO0->CFG	&=	~( ( 0b11 << BITP_GPIO_CFG_PIN10 ) | ( 0b11 << BITP_GPIO_CFG_PIN11 ) );
	pADI_GPIO0->CFG	|=	 ( ( 0b01 << BITP_GPIO_CFG_PIN10 ) | ( 0b01 << BITP_GPIO_CFG_PIN11 ) );

	/* Both pins as GPIOs	 */
	pADI_GPIO2->CFG	&=	~( 0b11 << BITP_GPIO_CFG_PIN00 );
	pADI_GPIO1->CFG	&=	~( 0b11 << BITP_GPIO_CFG_PIN15 );

	/* Drive Strength Select: Normal	 */
	pADI_GPIO2->DS	&=	~( DS3 );
	pADI_GPIO1->DS	&=	~( DS4 );

	/* Disable pull-up/pull-down for each pin	 */
	pADI_GPIO2->PE	&=	~( DS3 );
	pADI_GPIO1->PE	&=	~( DS4 );

	/* Interrupt A and B disabled	 */
	pADI_GPIO2->IENA	&=	~( DS3 );
	pADI_GPIO1->IENA	&=	~( DS4 );

	pADI_GPIO2->IENB	&=	~( DS3 );
	pADI_GPIO1->IENB	&=	~( DS4 );

	/* Configure output pins	 */
	pADI_GPIO2->IEN	&=	~( DS3 );
	pADI_GPIO1->IEN	&=	~( DS4 );

	pADI_GPIO2->OEN	|=	 DS3;
	pADI_GPIO1->OEN	|=	 DS4;
}



/**
 * @brief       void conf_UART  ( void )
 * @details     It configures the UART peripheral.
 *
 * 					UART:
 * 					 - Bypass the fractional divider
 * 					 - BaudRate = PCLK/[ 2^( OSR + 2 ) * DIV ] = 6500000/[ 2^( 1 + 2 ) * 7 ] ~ 116071.43
 * 					 - Rx interrupt enabled.
 *
 *
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/July/2020
 * @version     22/July/2020      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_UART  ( void )
{
	/* Disable auto baud	 */
	pADI_UART0->ACR	&=	~( 1U << BITP_UART_ACR_ABE );

	/* UART:
	 * 	- UCLK automatically gated
	 * 	- Don't invert receiver line (idling high).
	*/
	pADI_UART0->CTL	&=	~( ( 1U << BITP_UART_CTL_RXINV ) | ( 1U << BITP_UART_CTL_FORCECLK ) );

	/* UART:
	 *  - No parity
	 *  - 1 Stop bit
	 *  - 8-bit length
	*/
	pADI_UART0->LCR	&=	~( ( 1U << BITP_UART_LCR_BRK ) | ( 1U << BITP_UART_LCR_SP ) | ( 1U << BITP_UART_LCR_PEN ) | ( 1U << BITP_UART_LCR_STOP ) | ( 0b11 << BITP_UART_LCR_WLS ) );
	pADI_UART0->LCR	|=	 ( 0b11 << BITP_UART_LCR_WLS );

	/* UART:
	 * 	- Rx FIFO Trigger Level: 1 byte to trigger RX interrupt
	 * 	- Clear Tx and Rx FIFO
	 * 	- FIFO as to Work in 16550 Mode: Disabled
	*/
	pADI_UART0->FCR	&=	~( ( 1U << BITP_UART_FCR_RFTRIG ) | ( 1U << BITP_UART_FCR_TFCLR ) | ( 1U << BITP_UART_FCR_RFCLR ) | ( 1U << BITP_UART_FCR_FIFOEN ) );

	/*	Disable Rx When Transmitting	 */
	pADI_UART0->RSC	|=	 ( 1U << BITP_UART_RSC_DISRX );

	/* UART Baud Rate: BaudRate = 6500000/[ 2^( 1 + 2 ) * 7 ] ~ 116071.43
	 *  - Bypass the fractional divider
	 *   	Baud Rate = PCLK/[ 2^( OSR + 2 ) * DIV ]
	 *  - OSR: 1 ( Over sample by 8 )
	 *  - DIV: 7
	*/
	pADI_UART0->FBR		&=	~( 1U << BITP_UART_FBR_FBEN );
	pADI_UART0->LCR2	&=	~( 0b11 << BITP_UART_LCR2_OSR );
	pADI_UART0->LCR2	|=	 ( 0b01 << BITP_UART_LCR2_OSR );
	pADI_UART0->DIV		 =	 ( 7U << BITP_UART_DIV_DIV );

	/* UART interrupts:
	 * 	- Rx interruptReceive Buffer Full Interrupt: Enabled
	 * 	- The rest: Disabled
	*/
	pADI_UART0->IEN	&=	~( ( 1U << BITP_UART_IEN_EDMAR ) | ( 1U << BITP_UART_IEN_EDMAT ) | ( 1U << BITP_UART_IEN_EDSSI ) | ( 1U << BITP_UART_IEN_ELSI ) | ( 1U << BITP_UART_IEN_ETBEI ) | ( 1U << BITP_UART_IEN_ERBFI ) );
	pADI_UART0->IEN	|=	 ( 1U << BITP_UART_IEN_ERBFI );

	/* Enable interrupt	 */
	NVIC_SetPriority ( UART_EVT_IRQn, 0UL );
	NVIC_EnableIRQ   ( UART_EVT_IRQn );
}



/**
 * @brief       void conf_Timer0  ( void )
 * @details     It configures the Timer0.
 *
 *					TMR0:
 * 						- TMR0_CLK: LFOSC/4 = 32768Hz/4 = 8192Hz
 * 						- Count down
 * 						- Periodic mode
 * 						- Interrupt enabled
 * 						- Overflow: 1s ( 8192 / 8192Hz = 1s )
 *
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/July/2020
 * @version     22/July/2020      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_Timer0  ( void )
{
	/* Timer0 must be released before is configured	 */
	while ( ( pADI_TMR0->STAT & ( 1U << BITP_TMR_STAT_BUSY ) ) == ( 1U << BITP_TMR_STAT_BUSY ) );

	/* Timer0
	 *  - Synchronization bypass is disabled
	 *  - Event will not be captured
	 *  - TMR0 disabled
	 *  - TMR0 CLK: LFOSC ( 32768 Hz )
	 *  - TMR0 Prescaler: TMR0_CLK/4 ( 32768Hz / 4 = 8192Hz )
	 *  - Timer is set to count down
	 *	- Timer runs in periodic mode
	 */
	pADI_TMR0->CTL	&=	~( ( 1U << BITP_TMR_CTL_SYNCBYP ) | ( 1U << BITP_TMR_CTL_EVTEN ) | ( 0b11 << BITP_TMR_CTL_CLK ) | ( 1U << BITP_TMR_CTL_EN ) | ( 0b11 << BITP_TMR_CTL_PRE ) );
	pADI_TMR0->CTL	|=	 ( ( 0b10 << BITP_TMR_CTL_CLK ) | ( 1U << BITP_TMR_CTL_MODE ) );

	/* Timer0
	 *  - Overflow every ~ 1 second ( 8192 * ( 1/ 8192 ) = 1s )
	 */
	pADI_TMR0->LOAD	 =	 8192U;

	/* Clear interrupt: Timeout	 */
	pADI_TMR0->CLRINT	|=	 ( 1U << BITP_TMR_CLRINT_TIMEOUT );

	/* Enable interrupt	 */
	NVIC_SetPriority ( TMR0_EVT_IRQn, 0UL );
	NVIC_EnableIRQ   ( TMR0_EVT_IRQn );
}
