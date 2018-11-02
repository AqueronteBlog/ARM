/**
 * @brief       functions.c
 * @details     Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        12/October/2018
 * @version     12/October/2018   The ORIGIN
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
 * @date        12/October/2018
 * @version     12/October/2018   The ORIGIN
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
 * 				- DAC:	LED1 ( PA_5 )
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
 * @date        12/October/2018
 * @version		17/October/2018   Output push-pull instead of open-drain
 * 				12/October/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void Conf_GPIO  ( void )
{
	/* GPIOA Peripheral clock enable	 */
	RCC->AHBENR 	|= 	 ( RCC_AHBENR_GPIOAEN );


    /* Configure PA5 ( LED1 )	 */
    GPIOA->MODER	|=	 ( GPIO_MODER_MODER5_1 | GPIO_MODER_MODER5_0 );	// Analog mode
    GPIOA->OTYPER	&=	~GPIO_OTYPER_OT_5; 								// Output push-pull
    GPIOA->OSPEEDR	&=	~GPIO_OSPEEDER_OSPEEDR5;						// Low speed
    GPIOA->PUPDR	&=	~GPIO_PUPDR_PUPDR5;								// No pull-up, pull-down
}


/**
 * @brief       void Conf_DAC  ( void )
 * @details     It configures the DAC as Triangular-wave generation.
 *
 * 					Channel 2:
 * 					 - Software triggered
 * 					 - Output buffer enabled
 * 					 - DMA disabled
 * 					 - Triangle wave generation enabled
 * 					 - Triangle amplitude ( DOR ): 4095 ( DAC_output = V_REF * ( DOR / 4096 ) )
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
 * @date        12/October/2018
 * @version		1/November/2018   The comments were improved.
 * 				17/October/2018   The comments were improved.
 * 				12/October/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void Conf_DAC  ( void )
{
	/* Turn on the DAC clock	 */
	RCC->APB1ENR	|=	 RCC_APB1ENR_DACEN;

	/* DAC configuration:
	 * 	- DAC channel1 disabled
	 * 	- DAC channel1 trigger disabled
	 * 	- Channel2 Wave generation enabled: Triangle wave generation
	 * 	- DAC channel1 DMA mode disabled
	 * 	- DAC channel1 DMA Underrun Interrupt disabled
	 * 	- DAC channel2 enabled
	 * 	- DAC channel2 output buffer enabled
	 * 	- DAC channel2 trigger enabled
	 * 	- DAC channel2 trigger selection: Software trigger
	 * 	- Channel2 Unmask bits[11:0] of LFSR/ triangle amplitude equal to 4095	 */
	DAC->CR	&=	~( DAC_CR_EN1 | DAC_CR_TEN1 | DAC_CR_WAVE1 | DAC_CR_DMAEN1 | DAC_CR_DMAUDRIE1 | DAC_CR_BOFF2 | DAC_CR_TEN2 | DAC_CR_MAMP2 );
	DAC->CR	|=	 ( DAC_CR_TEN2 | DAC_CR_TSEL2_2 | DAC_CR_TSEL2_1 | DAC_CR_TSEL2_0 | DAC_CR_MAMP2_3 | DAC_CR_MAMP2_1 | DAC_CR_MAMP2_0 |  DAC_CR_WAVE2_1 | DAC_CR_WAVE2_0 );
	DAC->CR	|=	 ( DAC_CR_EN2 );

	/* DAC channel2 Software trigger enabled	 */
	DAC->SWTRIGR	|=	 DAC_SWTRIGR_SWTRIG2;
}



/**
 * @brief       void Conf_RTC  ( void )
 * @details     It configures the RTC peripheral.
 *
 * 				Periodic Auto Wake-up Timer:
 * 					- RTC clock: 				RTC/2 ( = LSI/2 = 37kHz/2 = 18.5kHz )
 * 					- Wake-up timer interrupt:	Enabled
 * 					- Wake-up timer overflow: 	~ 54.05us ( WUTR / RTC/2 = 1 / ( 37kHz / 2 ) = 54.05us )
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        1/November/2018
 * @version		1/November/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void Conf_RTC  ( void )
{
	/* Enable the PWR peripheral */
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

	/* Disable backup write protection	*/
	PWR->CR		|=	 PWR_CR_DBP;

	/* Enable the RTC clock and choose the LSI clock for RTC */
	RCC->CSR 	|= 	 ( RCC_CSR_RTCEN | RCC_CSR_RTCSEL_LSI );

	/* Disable the write protection for RTC registers */
	RTC->WPR   	 =	 ( 0xCA & RTC_WPR_KEY_Msk );
    RTC->WPR	 = 	 ( 0x53 & RTC_WPR_KEY_Msk );

    /* Steps for programming the wake-up timer	*/
	RTC->CR		&=	~( RTC_CR_WUTE );										// Disable wake-up timer

	while ( ( RTC->ISR & RTC_ISR_WUTWF_Msk ) != RTC_ISR_WUTWF );			// Wait until wake-up auto-reload counter and to WUCKSEL[2:0] bits is allowed
																			// [TODO] 		This is dangerous! the uC may get stuck here
																			// [WORKAROUND] Insert a counter.

	/* Select the RTC clock and Reset flag  */
	RTC->CR		&=	~( RTC_CR_WUCKSEL_Msk );									// Reset Clock
	RTC->CR		|=	 ( RTC_CR_WUTIE | RTC_CR_WUCKSEL_0 | RTC_CR_WUCKSEL_1 );	// Enable Wake-up timer interrupt, RTC/2 clock is selected

	RTC->WUTR	 =	 1;
	RTC->ISR	&=	 ~RTC_ISR_WUTF;											// Reset Wake-up timer flag


	/* Enable the RTC Wake-up interrupt */
	EXTI->IMR	|=	 ( EXTI_IMR_MR20 );
	EXTI->RTSR	|=	 ( EXTI_RTSR_TR20 );

	/* Activate the RTC WAKEUP timer */
	RTC->CR		|=	 ( RTC_CR_WUTE );										// Wake-up timer enable

	/* Enable the write protection for RTC registers */
	RTC->WPR   	 =	 0xFF;
	RTC->WPR   	 =	 0xFF;

	/* Access to RTC, RTC Backup and RCC CSR registers disabled */
	PWR->CR &= ~PWR_CR_DBP;


	/* Enable RTC WakeUp IRQ  */
	NVIC_EnableIRQ ( RTC_WKUP_IRQn );
}
