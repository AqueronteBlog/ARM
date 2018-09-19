/**
 * @brief       functions.c
 * @details     Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        18/September/2018
 * @version     18/September/2018   The ORIGIN
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
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        18/September/2018
 * @version     18/September/2018   The ORIGIN
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
 * @details     It configures GPIO to work with the LEDs and UART
 *
 * 				- LED1:		PA_5
 * 				- USART2:
 * 					-- TX:	PA_2
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        18/September/2018
 * @version		18/September/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void Conf_GPIO  ( void )
{
	/* GPIOA and GPIOC Peripheral clock enable	 */
//	RCC->AHBENR 	|= 	 ( RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIODEN );
	RCC->AHBENR 	|= 	 ( RCC_AHBENR_GPIOAEN );


    /* Configure LED1	 */
    GPIOA->MODER	|=	 GPIO_MODER_MODER5_0;					// General purpose output mode
    GPIOA->OTYPER	&=	~GPIO_OTYPER_OT_5; 						// Output push-pull
    GPIOA->OSPEEDR	&=	~GPIO_OSPEEDER_OSPEEDR5;				// Low speed
    GPIOA->PUPDR	&=	~GPIO_PUPDR_PUPDR5;						// No pull-up, pull-down


    /* Configure USART2 pinout	 */
	/* TX pin	 */
    GPIOA->MODER	|=	 GPIO_MODER_MODER2_1;					// Alternate function mode
    GPIOA->OTYPER	&=	~GPIO_OTYPER_OT_2;						// Output push-pull
    GPIOA->OSPEEDR	|=	 GPIO_OSPEEDER_OSPEEDR2_0;				// Medium speed
    GPIOA->PUPDR	&=	~GPIO_PUPDR_PUPDR2_Msk;					// No pull-up, pull-down
    GPIOA->AFR[0]	&=	~GPIO_AFRL_AFSEL2;						// Mask Alternate function AFIO7 on PA_2
    GPIOA->AFR[0]	 =	 ( 0b0111 << GPIO_AFRL_AFSEL2_Pos );	// UART2_TX: AF7 on PA_2
}


/**
 * @brief       void Conf_RTC  ( void )
 * @details     It configures the RTC peripheral.
 *
 * 				Periodic Auto Wake-up Timer:
 * 					- RTC clock: 				ck_spre ( usually 1 Hz )
 * 					- Wake-up timer interrupt:	Enabled
 * 					- Wake-up timer overflow: 	~ 1s ( WUTR / ck_spre = 1 / 1 = 1s )
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        18/September/2018
 * @version		18/September/2018   The ORIGIN
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
	RTC->CR		&=	~( RTC_CR_WUCKSEL_Msk );								// Reset Clock
	RTC->CR		|=	 ( RTC_CR_WUTIE | RTC_CR_WUCKSEL_2 );					// Enable Wake-up timer interrupt, ck_spre (usually 1 Hz) clock is selected

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



/**
 * @brief       void Conf_USART  ( uint32_t myCK, uint32_t myBaudRate )
 * @details     It configures the UARTs.
 *
 * 				- USART2
 * 					-- Tx Interrupt ENABLED
 *
 * @param[in]    myCK: 			UART Clock ( f_CK ).
 * @param[in]    myBaudRate: 	UART baud rate.
 *
 * @param[out]   N/A.
 *
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        18/September/2018
 * @version     18/September/2018   The ORIGIN
 * @pre         OVER8 is calculated automatically.
 * @pre         Rx is disabled, Tx is used only.
 * @warning     N/A
 */
void Conf_USART  ( uint32_t myCK, uint32_t myBaudRate )
{
	float 		myCalculatedData	=	 0.0f;
	uint32_t	myOVER8	 			=	 0UL;

	/* USART2 Peripheral clock enable	 */
	RCC->APB1ENR	|=	 RCC_APB1ENR_USART2EN;

	USART2->CR1	&=	~( USART_CR1_OVER8 | USART_CR1_UE | USART_CR1_M | 			// Oversampling by 16,  USART disabled, 1 Start bit, 8 Data bits n Stop bit
					   USART_CR1_PCE | USART_CR1_TE | USART_CR1_RE );			// Parity control disabled, Transmitter is disabled, Receiver is disabled

	USART2->CR2	&=	~( USART_CR2_STOP_1 | USART_CR2_STOP_0 | USART_CR2_CLKEN |	// 1 Stop bit, CK pin disabled,
					   USART_CR2_CPOL | USART_CR2_CPHA );						// CPOL = 0, CPHA = 0

	/* Calculate Mantissa	 */
	/* Check if oversamplig by 16 is correct	 */
	myCalculatedData	=	 myCK / ( myBaudRate * 8.0f * ( 2.0f - myOVER8 ) );

	if ( myCalculatedData < 1.0f )
	{
	/* if not, change it to oversampling by 8	 */
		myOVER8	 			=	 1UL;
		myCalculatedData	=	 myCK / ( myBaudRate * 8.0f * ( 2.0f - myOVER8 ) );
	}

	/* Update oversampling	 */
	if ( myOVER8 == 0UL )
	{
		myOVER8	 =	 16.0f;
	}
	else
	{
		myOVER8	 =	 8.0f;
	}


	/* BaudRate: Update Mantissa	 */
	USART2->BRR	 =	 ( ( ( uint32_t )( myCalculatedData ) << USART_BRR_DIV_MANTISSA_Pos ) & USART_BRR_DIV_MANTISSA_Msk );

	/* Calculate Fraction	 */
	myCalculatedData	 =	 myCalculatedData - ( uint32_t )myCalculatedData;
	myCalculatedData	*=	 myOVER8;
	myCalculatedData	 =	 _ROUND32U ( myCalculatedData );

	/* BaudRate: Update Fraction	 */
	USART2->BRR	|=	 ( ( ( uint32_t )( myCalculatedData ) << USART_BRR_DIV_FRACTION_Pos ) & USART_BRR_DIV_FRACTION_Msk );


	/* Enable Interrupt	 */
	NVIC_SetPriority ( USART2_IRQn, 1 ); 									// Set Priority to 1
	NVIC_EnableIRQ   ( USART2_IRQn );  										// Enable UART2_IRQn interrupt in NVIC


	/* Activate interrupts, and UART	 */
	USART2->SR	&=	~( USART_SR_TXE | USART_SR_TC | USART_SR_RXNE );		// Clear flags
	USART2->CR1	|=	 ( USART_CR1_UE | USART_CR1_TCIE );				 		// USART enabled, Transmission complete interrupt enabled


//	while ( ( USART2->SR & USART_SR_TC ) != USART_SR_TC );					// Wait until Idle frame is sent
																			// [TODO] Dangerous!!! Insert a delay, the uC may get stuck here otherwise.
	USART2->SR	&=	~( USART_SR_TC | USART_SR_RXNE );						// Clear flags

	USART2->CR1	|=	 ( USART_CR1_TCIE );									// Transmission complete interrupt enabled
}



/**
 * @brief       void Conf_ADC  ( void )
 * @details     It configures the ADC to work with the internal temperature sensor.
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
 * @date        18/September/2018
 * @version		18/September/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void Conf_ADC  ( void )
{

}
