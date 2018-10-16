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
 * @version		12/October/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void Conf_GPIO  ( void )
{
	/* GPIOA Peripheral clock enable	 */
	RCC->AHBENR 	|= 	 ( RCC_AHBENR_GPIOAEN );


    /* Configure PA5 ( LED1 )	 */
    GPIOA->MODER	|=	 ( GPIO_MODER_MODER5_1 | GPIO_MODER_MODER5_0 );	// Analog mode
    GPIOA->OTYPER	|=	 GPIO_OTYPER_OT_5; 								// Output open-drain
    GPIOA->OSPEEDR	&=	~GPIO_OSPEEDER_OSPEEDR5;						// Low speed
    GPIOA->PUPDR	&=	~GPIO_PUPDR_PUPDR5;								// No pull-up, pull-down
}


/**
 * @brief       void Conf_DAC  ( void )
 * @details     It configures the DAC as Triangular-wave generation.
 *
 * 					- [todo]
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
 * @version		12/October/2018   The ORIGIN
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
	DAC->CR	&=	~( DAC_CR_EN1 | DAC_CR_TEN1 | DAC_CR_WAVE1 | DAC_CR_DMAEN1 | DAC_CR_DMAUDRIE1 | DAC_CR_BOFF2 | DAC_CR_TEN2 );
	DAC->CR	|=	 ( DAC_CR_TEN2 | DAC_CR_TSEL2_2 | DAC_CR_TSEL2_1 | DAC_CR_TSEL2_0 | DAC_CR_MAMP2_3 | DAC_CR_MAMP2_1 | DAC_CR_MAMP2_0 | DAC_CR_WAVE2_1 | DAC_CR_WAVE2_0 );
	DAC->CR	|=	 ( DAC_CR_EN2 );

	/* DAC channel2 Software trigger enabled	 */
	DAC->SWTRIGR	|=	 DAC_SWTRIGR_SWTRIG2;
}
