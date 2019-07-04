/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        04/July/2019
 * @version     04/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "functions.h"



/**
 * @brief       void conf_CLK  ( void )
 * @details     It activates the internal HFOSC crystal oscillator ( 26MHz ) and the internal
 * 				LFOSC ( 32768Hz ) oscillator.
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
 * @date        04/July/2019
 * @version     04/July/2019      The ORIGIN
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
 * @details     It configures GPIO to work with the LEDs.
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
 * @date        04/July/2019
 * @version     04/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO  ( void )
{
	/* Both pins as GPIOs	 */
	pADI_GPIO2->CFG	&=	~( 0b11 << BITP_GPIO_CFG_PIN00 );
	pADI_GPIO1->CFG	&=	~( 0b11 << BITP_GPIO_CFG_PIN15 );

	/* Set the Output Low for DS3 and High for DS4	 */
	pADI_GPIO2->CLR	 =	 DS3;
	pADI_GPIO1->SET	 =	 DS4;

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
 * @brief       void conf_RTC  ( void )
 * @details     It configures the RTC.
 *
 *					RTC1:
 * 						- RTC1_CLK: LFOSC/2 = 32768Hz/2 = 16384Hz
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
 * @date        04/July/2019
 * @version     04/July/2019    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_RTC ( void )
{
	/* Make sure that RTC1 registers can be modified
	 *  - NOTE:
	 *  	This is dangerous!, the uC may get stuck here, add a counter to avoid that circumstance.
	 */
	while ( ( pADI_RTC1->SR1 & ( ( 1U << BITP_RTC_SR1_WPNDTRM ) | ( 1U << BITP_RTC_SR1_WPNDALM1 ) | ( 1U << BITP_RTC_SR1_WPNDALM0 ) | ( 1U << BITP_RTC_SR1_WPNDCNT1 ) | ( 1U << BITP_RTC_SR1_WPNDCNT0 ) | ( 1U << BITP_RTC_SR1_WPNDSR0 ) | ( 1U << BITP_RTC_SR1_WPNDCR0 ) ) ) != 0x00 );

	/* Disable RTC1	 */
	pADI_RTC1->CR0	&=	~( 1U << BITP_RTC_CR0_CNTEN );

	/* Pending Status of Posted Writes to CR0
	 *  - NOTE:
	 *  	This is dangerous!, the uC may get stuck here, add a counter to avoid that circumstance.
	 */
	while ( ( pADI_RTC1->SR1 & ( 1U << BITP_RTC_SR1_WPNDCR0 ) ) == ( 1U << BITP_RTC_SR1_WPNDCR0 ) );


	/* RTC1
	 *  - Enable the RTC Alarm (Absolute) Operation
	 *  - Enable ALMINT Sourced Alarm Interrupts to the CPU
	 */
	pADI_RTC1->CR0	|=	 ( ( 1U << BITP_RTC_CR0_ALMINTEN ) | ( 1U << BITP_RTC_CR0_ALMEN ) );

	/* Pending Status of Posted Writes to CR0
	 *  - NOTE:
	 *  	This is dangerous!, the uC may get stuck here, add a counter to avoid that circumstance.
	 */
	while ( ( pADI_RTC1->SR1 & ( 1U << BITP_RTC_SR1_WPNDCR0 ) ) == ( 1U << BITP_RTC_SR1_WPNDCR0 ) );

	/* RTC1
	 *  - Prescale the RTC base clock by 2^1 = 2 ( 32768Hz/2 = 16384Hz )
	 *  - Disable for the RTC Modulo-60 Count Roll-Over Interrupt Source
	 *  - Disable for the RTC Count Roll-Over Interrupt Source
	 *  - Disable for the RTC Trim Interrupt Source
	 *  - Disable for the Prescaled, Modulo-1 Interrupt Source
	 *  - Disable for the RTC Count Interrupt Source
	 */
	pADI_RTC1->CR1	&=	~( ( 0b1111 << BITP_RTC_CR1_PRESCALE2EXP ) | ( 1U << BITP_RTC_CR1_CNTMOD60ROLLINTEN ) | ( 1U << BITP_RTC_CR1_CNTROLLINTEN ) | ( 1U << BITP_RTC_CR1_TRMINTEN ) | ( 1U << BITP_RTC_CR1_PSINTEN ) | ( 1U << BITP_RTC_CR1_CNTINTEN ) );
	pADI_RTC1->CR1	|=	~( 0b0001 << BITP_RTC_CR1_PRESCALE2EXP );


	/* RTC1
	 *  - Overflow every ~ 1 second ( 16384 * ( 1/ 16384 ) = 1s )
	 */
	pADI_RTC1->ALM0	 =	 16384U;		// Lower 16 bits of the non-fractional (prescaled) RTC alarm target time value
	pADI_RTC1->ALM1	 =	 0U;			// Upper 16 bits of the non-fractional (prescaled) RTC alarm target time value
	pADI_RTC1->ALM2	 =	 0U;			// Fractional (non-prescaled) bits of the RTC alarm target time value

	/* Pending Status of Posted Writes to ALM0
	 *  - NOTE:
	 *  	This is dangerous!, the uC may get stuck here, add a counter to avoid that circumstance.
	 */
	while ( ( pADI_RTC1->SR1 & ( 1U << BITP_RTC_SR1_WPNDALM1 ) ) == ( 1U << BITP_RTC_SR1_WPNDALM1 ) );


	/* Reset RTC1 counter register	 */
	pADI_RTC1->CNT0	 =	 0U;			// Lower 16 bits of the RTC counter
	pADI_RTC1->CNT1	 =	 0U;			// Upper 16 bits of the RTC counter

	/* Pending Status of Posted Writes to CNT0
	 *  - NOTE:
	 *  	This is dangerous!, the uC may get stuck here, add a counter to avoid that circumstance.
	 */
	while ( ( pADI_RTC1->SR1 & ( 1U << BITP_RTC_SR1_WPNDCNT0 ) ) == ( 1U << BITP_RTC_SR1_WPNDCNT0 ) );

	/* Clear Alarm Interrupt Source	 */
	pADI_RTC1->SR0	|=	 ( 1U << BITP_RTC_SR0_ALMINT );

	/* Enable interrupt	 */
	NVIC_SetPriority ( RTC1_EVT_IRQn, 0UL );
	NVIC_EnableIRQ   ( RTC1_EVT_IRQn );

	/* Enable RTC1	 */
	pADI_RTC1->CR0	|=	 ( 1U << BITP_RTC_CR0_CNTEN );

	/* Pending Status of Posted Writes to CR0
	 *  - NOTE:
	 *  	This is dangerous!, the uC may get stuck here, add a counter to avoid that circumstance.
	 */
	while ( ( pADI_RTC1->SR1 & ( 1U << BITP_RTC_SR1_WPNDCR0 ) ) == ( 1U << BITP_RTC_SR1_WPNDCR0 ) );
}
