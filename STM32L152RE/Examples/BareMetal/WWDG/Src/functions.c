/**
 * @brief       functions.c
 * @details     Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/October/2018
 * @version     9/October/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */


#include "functions.h"

/**
 * @brief       void Conf_CLK  ( void )
 * @details     It configures the CLK.
 *
 * 				- HSI ON
 * 				- SYSCLK = HSI/1 = 16MHz
 * 				- Rest CLK = SYSCLK = 16MHz
 * 				- MSI OFF
 * 				- LSI ON
 * 				- MCO DISABLED
 *
 *
 * @param[in]    N/A.
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/October/2018
 * @version     9/October/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void Conf_CLK  ( void )
{
	/* Enable HSI	 */
	RCC->CR		|=	  RCC_CR_HSION;
	/* Wait until HSI is stable	 */
	while ( ( RCC->CR & RCC_CR_HSIRDY ) != RCC_CR_HSIRDY );					// [TODO] Dangerous!!! Insert a delay, the uC may get stuck
																			// if something goes wrong otherwise.
	/* HSI -> SYSCLK	 */
	RCC->CFGR	|=	 RCC_CFGR_SW_HSI;
	/* Wait until it is stable	 */
	while ( ( RCC->CFGR & RCC_CFGR_SWS ) != RCC_CFGR_SWS_HSI );				// [TODO] Dangerous!!! Insert a delay, the uC may get stuck
																			// if something goes wrong otherwise.
	/* Stop MSI	 */
	RCC->CR		&=	 ~RCC_CR_MSION;
	/* Wait until MSI is off	 */
	while ( ( RCC->CR & RCC_CR_MSIRDY ) == RCC_CR_MSIRDY );					// [TODO] Dangerous!!! Insert a delay, the uC may get stuck
																			// if something goes wrong otherwise.

	RCC->CFGR	&=	 0xF8FFFFFF;											// MCO output disabled, no clock on MCO
	//	RCC->CFGR	|=	 ( RCC_CFGR_MCOPRE_DIV1 | RCC_CFGR_MCOSEL_SYSCLK );		// MCO = SYSCLK/1 | MCO ENABLED

	PWR->CR		|=	 ( PWR_CR_DBP );										// Unlock registers ( As these bits are write protected after reset )
	RCC->CSR	|=	 ( RCC_CSR_LSION );
	while ( ( RCC->CSR & RCC_CSR_LSIRDY_Msk ) != RCC_CSR_LSIRDY );			// Wait until LSI is ready
																			// [TODO] 		This is dangerous! the uC may get stuck here
																			// [WORKAROUND] Insert a counter.
	PWR->CR		&=  ~( PWR_CR_DBP );										// Lock registers ( As these bits are write protected after reset )
}




/**
 * @brief       void Conf_GPIO  ( void )
 * @details     It configures GPIOs.
 *
 * 				- LED1:		PA_5
 *
 *
 * @param[in]    N/A.
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/October/2018
 * @version		9/October/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void Conf_GPIO  ( void )
{
	/* GPIOA Peripheral clock enable	 */
	RCC->AHBENR 	|= 	 ( RCC_AHBENR_GPIOAEN );


    /* Configure LED1	 */
    GPIOA->MODER	|=	 GPIO_MODER_MODER5_0;					// General purpose output mode
    GPIOA->OTYPER	&=	~GPIO_OTYPER_OT_5; 						// Output push-pull
    GPIOA->OSPEEDR	&=	~GPIO_OSPEEDER_OSPEEDR5;				// Low speed
    GPIOA->PUPDR	&=	~GPIO_PUPDR_PUPDR5;						// No pull-up, pull-down
}


/**
 * @brief       void Conf_WWDG  ( void )
 * @details     It configures the window watchdog ( WWDG ).
 *
 * 					- Early wakeup interrupt enabled
 * 					- Overflow ( t_WWDG = t_PCLK1 * 4096 * 2^WDGTB[1:0] * ( T[5:0] + 1 ) = ( 16MHz )^-1 * 4096 * 2^3 * ( 63 + 1 ) ~ 131.07ms )
 *
 *
 * @param[in]    N/A.
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/October/2018
 * @version		9/October/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void Conf_WWDG  ( void )
{
	/* Turn on the WWDG clock	 */
	RCC->APB1ENR	|=	 RCC_APB1ENR_WWDGEN;

	/* WWDG:
	* 	- Early wakeup interrupt enabled
	* 	- Timer base: Counter_Clock/8
	*/
	WWDG->CFR	|=	 ( WWDG_CFR_EWI | WWDG_CFR_WDGTB_0 | WWDG_CFR_WDGTB_1 );

	/* Enable WWDG WakeUp IRQ  */
	NVIC_EnableIRQ ( WWDG_IRQn );

	/* Configure 7-bit counter: T[5:0] = 63 and turn on the WWDG	 */
	WWDG->CR	|=	 ( WWDG_CR_WDGA | WWDG_CR_T_0 | WWDG_CR_T_1 | WWDG_CR_T_2 | WWDG_CR_T_3 | WWDG_CR_T_4 | WWDG_CR_T_5 | WWDG_CR_T_6 );
}
