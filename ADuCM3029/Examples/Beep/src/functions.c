/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        21/September/2019
 * @version     21/September/2019   The ORIGIN
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
 * @date        21/September/2019
 * @version     21/September/2019      The ORIGIN
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
 * 					UART_Tx: 	P0_10
 * 					UART_Rx: 	P0_11
 * 					BEEP_POS:	P0_08
 * 					BEEP_NEG:	P0_09
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
 * @date        21/September/2019
 * @version     25/September/2019   Beep pins were added
 * 				21/September/2019   The ORIGIN
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

	/* BEEP pins: Multiplexed function 1	 */
	pADI_GPIO0->CFG	&=	~( ( 0b11 << BITP_GPIO_CFG_PIN08 ) | ( 0b11 << BITP_GPIO_CFG_PIN09 ) );
	pADI_GPIO0->CFG	|=	 ( ( 0b01 << BITP_GPIO_CFG_PIN08 ) | ( 0b01 << BITP_GPIO_CFG_PIN09 ) );
}



/**
 * @brief       void conf_BEEP  ( void )
 * @details     It configures the Beep peripheral.
 *
 * 					Beep:
 * 					 - ToneA Enabled generating an interrupt once ToneA has ended.
 * 					 - ToneA frequency: 1s ( 32kHz/32 = 1s --> FREQ = 32 ( 0x20 ) )
 * 					 - ToneA duration: 100ms ( DUR = 100ms/4ms = 25 ( 0x19 ) )
 * 					 - ToneA output enabled.
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
 * @date        21/September/2019
 * @version     25/September/2019      It generates an interruption once ToneA has ended.
 * 				21/September/2019      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_BEEP  ( void )
{
	/* Disable Beep	 */
	pADI_BEEP0->CFG	&=	~( 1U << BITP_BEEP_CFG_EN );

	/* ToneA
	 * 	- FREQ = 1s
	 * 	- DUR = 100ms
	 * 	- Output enabled
	 */
	pADI_BEEP0->TONEA	&=	~( ( 0b1111111 << BITP_BEEP_TONEA_FREQ ) | ( 0xFF << BITP_BEEP_TONEA_DUR ) | ( 1U << BITP_BEEP_TONEA_DIS ) );
	pADI_BEEP0->TONEA	|=	 ( (0x20 << BITP_BEEP_TONEA_FREQ ) | ( 0x19 << BITP_BEEP_TONEA_DUR ) );

	/* Enable interrupt	 */
	NVIC_SetPriority ( BEEP_EVT_IRQn, 0UL );
	NVIC_EnableIRQ   ( BEEP_EVT_IRQn );

	/* Generate an interrupt once ToneA has ended	 */
	pADI_BEEP0->CFG	|=	 ( 1U << BITP_BEEP_CFG_AENDIRQ );
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
 * @date        23/September/2019
 * @version     23/September/2019      The ORIGIN
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
