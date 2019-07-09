/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        09/July/2019
 * @version     09/July/2019   The ORIGIN
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
 * @date        09/July/2019
 * @version     09/July/2019      The ORIGIN
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
 * @date        09/July/2019
 * @version     09/July/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO  ( void )
{
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
 * @brief       void conf_WDT  ( void )
 * @details     It configures the WDT as watchdog mode.
 *
 * 					WDT:
 * 					 - Overflow every 1s
 * 					 - Watchdog mode: It generates a reset.
 * 					 - Source clock: Source clock/1 ( 32768/1 = 32768Hz
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
 * @date        09/July/2019
 * @version     09/July/2019      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_WDT  ( void )
{
	/* Disable WDT	 */
	pADI_WDT0->CTL	&=	~( 1U << BITP_WDT_CTL_EN );

	/*
	 * WDT Configuration:
	 * 	- Prescaler: Source clock/1 ( 32768/1 = 32768Hz )
	 * 	- Timer Mode: Periodic mode
	 * 	- IRQ: WDT generates reset when timed out
	 */
	pADI_WDT0->CTL	&=	~( ( 0b11 << BITP_WDT_CTL_PRE ) | ( 1U << BITP_WDT_CTL_IRQ ) );
	pADI_WDT0->CTL	|=	 ( ( 0b00 << BITP_WDT_CTL_PRE ) | ( 1U << BITP_WDT_CTL_MODE ) );

	/* Load WDT: Overflow every 1s ( 32768 * ( 1 / 32768Hz ) )	 */
	pADI_WDT0->LOAD	 =	 32768U;

	/* Enable WDT	 */
	pADI_WDT0->CTL	|=	 ( 1U << BITP_WDT_CTL_EN );
}

