/**
 * @brief       functions.c
 * @details     Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/March/2018
 * @version     9/March/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */


#include "functions.h"

/**
 * @brief       void Conf_CLK  ( void )
 * @details     It disabled MCO ans enables the LSI for RTC
 *
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/March/2018
 * @version     9/March/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void Conf_CLK  ( void )
{
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
 * @brief       void Conf_SYSTICK  ( uint32_t )
 * @details     It disables the SysTick.
 *
 * @param[in]    myticks:	Value of the SYSCLK..
 *
 * @param[out]   N/A.
 *
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        29/December/2017
 * @version     29/December/2017   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void Conf_SYSTICK  ( uint32_t myticks )
{
	SysTick->CTRL	&=	 ~SysTick_CTRL_ENABLE_Msk;										// SysTick DISABLED


//	SysTick->LOAD	 =	 (uint32_t)(myticks - 1UL);										// Load the value
//	SysTick->VAL	 =	 0UL;															// Reset current Counter value
//
//	// Set the PRIGROUP[10:8] bits according to the PriorityGroup parameter value
//	NVIC_SetPriorityGrouping	( NVIC_PRIORITYGROUP_4 );
//	NVIC_SetPriority 			( SysTick_IRQn, ( 1UL << __NVIC_PRIO_BITS ) - 1UL );	// Set Priority for Systick Interrupt
//	NVIC_EnableIRQ				( SysTick_IRQn );										// Enable interrupt
//
//	SysTick->CTRL  	 = 	( SysTick_CTRL_CLKSOURCE_Msk |
//	                   	  SysTick_CTRL_TICKINT_Msk   |
//						  SysTick_CTRL_ENABLE_Msk );                    				// Enable SysTick IRQ and SysTick Timer

}



/**
 * @brief       void Conf_GPIO  ( void )
 * @details     It configures GPIO to work with the LEDs
 *
 * 				- LED1:			PA_5
 *
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/March/2018
 * @version		3/March/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void Conf_GPIO  ( void )
{
	// GPIOA Periph clock enable
	RCC->AHBENR 	|= 	 ( RCC_AHBENR_GPIOAEN );


    // Configure LED1
    GPIOA->MODER	|=	 GPIO_MODER_MODER5_0;			// General purpose output mode
    GPIOA->OTYPER	&=	~GPIO_OTYPER_OT_5; 				// Output push-pull
    GPIOA->OSPEEDR	&=	~GPIO_OSPEEDER_OSPEEDR5;		// Low speed
    GPIOA->PUPDR	&=	~GPIO_PUPDR_PUPDR5;				// No pull-up, pull-down
}



/**
 * @brief       void Conf_RTC  ( void )
 * @details     [todo]
 *
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        15/March/2018
 * @version		15/March/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void Conf_RTC  ( void )
{
	/* Enable the PWR peripheral */
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

	PWR->CR		|=	 PWR_CR_DBP;

	/* Disable the write protection for RTC registers */
	RTC->WPR   	 =	 0xCA;
    RTC->WPR	 = 	 0x53;


	RTC->CR		&=	~( RTC_CR_WUTE );										// Disable Wakeup timer

	while ( ( RTC->ISR & RTC_ISR_WUTF_Msk ) != RTC_ISR_WUTF );				// Wait until wakeup auto-reload counter and to WUCKSEL[2:0] bits is allowed
																			// [TODO] 		This is dangerous! the uC may get stuck here
																			// [WORKAROUND] Insert a counter.

	RTC->PRER	 =	 ( 127 << RTC_PRER_PREDIV_A_Pos ) | ( 255 << RTC_PRER_PREDIV_S_Pos );



	RTC->WUTR	 =	 0;
	RTC->ISR	&=	 ~RTC_ISR_WUTF;											// Reset Wakeup timer flag

	RTC->CR		|=	 ( RTC_CR_WUTIE | RTC_CR_WUTE | RTC_CR_WUCKSEL_2 );		// Enable Wakeup timer interrupt, Wakeup timer enable, ck_spre (usually 1 Hz) clock is selected

	/* Enable the write protection for RTC registers */
	RTC->WPR   	 =	 0xFF;

	/* Access to RTC, RTC Backup and RCC CSR registers disabled */
	PWR->CR &= ~PWR_CR_DBP;


	NVIC_EnableIRQ ( RTC_WKUP_IRQn );       								/* Enable RTC WakeUp IRQ              */
}
