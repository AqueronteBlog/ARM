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
 * @date        21/September/2019
 * @version     21/September/2019   The ORIGIN
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
 * @brief       void conf_BEEP  ( void )
 * @details     It configures the Beep peripheral.
 *
 * 					Beep:[todo]
 * 					 - xxx
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
 * @version     21/September/2019      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_BEEP  ( void )
{
	/* Disable Beep	 */
	pADI_BEEP0->CFG	&=	~( 1U << BITP_BEEP_CFG_EN );



	/* Enable Beep	 */
	pADI_BEEP0->CFG	|=	 ( 1U << BITP_BEEP_CFG_EN );
}

