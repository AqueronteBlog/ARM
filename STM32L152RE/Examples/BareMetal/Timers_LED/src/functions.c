/**
 * @brief       functions.c
 * @details     Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        2/January/2018
 * @version     2/January/2018   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */


#include "functions.h"

/**
 * @brief       void Conf_CLK  ( void )
 * @details     It disabled MCO.
 *
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        30/December/2017
 * @version     30/December/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
void Conf_CLK  ( void )
{
	RCC->CFGR	&=	 0xF8FFFFFF;											// MCO output disabled, no clock on MCO
//	RCC->CFGR	|=	 ( RCC_CFGR_MCOPRE_DIV1 | RCC_CFGR_MCOSEL_SYSCLK );		// MCO = SYSCLK/1 | MCO ENABLED
}



/**
 * @brief       void Conf_SYSTICK  ( uint32_t )
 * @details     It disables the SysTick.
 *
 * @param[in]    myticks:	Value of the SYSCLK..
 *
 * @param[out]   NaN.
 *
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/December/2017
 * @version     29/December/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
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
 * @details     It configures GPIO to work with the LEDs and
 * 				User Button.
 *
 * 				- LED1:			PA_5
 * 				- User Button:  PC_13 ( Interrupt ENABLED )
 *
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/December/2017
 * @version		30/December/2017   User Button added.
 * 				29/December/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
void Conf_GPIO  ( void )
{
	// GPIOA & GPIOC Peripheral clock enable
	RCC->AHBENR 	|= 	 ( RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN );

	// SYSCFG Peripheral clock enable
	RCC->APB2ENR	|=	 RCC_APB2RSTR_SYSCFGRST;



    // Configure LED1
    GPIOA->MODER	|=	 GPIO_MODER_MODER5_0;			// General purpose output mode
    GPIOA->OTYPER	&=	~GPIO_OTYPER_OT_5; 				// Output push-pull
    GPIOA->OSPEEDR	&=	~GPIO_OSPEEDER_OSPEEDR5_Msk;	// Low speed
    GPIOA->PUPDR	&=	~GPIO_PUPDR_PUPDR5_Msk;			// No pull-up, pull-down

    // Configure User Button
    GPIOC->MODER	&=	~( GPIO_MODER_MODER13_1 | GPIO_MODER_MODER13_0 );	// Input mode
    GPIOC->PUPDR	&=	~( GPIO_PUPDR_PUPDR13_1 | GPIO_PUPDR_PUPDR13_0 );	// Floating input

    // User Button generates an interrupt
    SYSCFG->EXTICR[3]	|=	 SYSCFG_EXTICR4_EXTI13_PC;						// Map EXTI13 ( PC_13 ) Line to NVIC
    EXTI->IMR			|=	 EXTI_IMR_MR13;
    EXTI->RTSR			&=	~EXTI_RTSR_TR13;								// Rising edge trigger disabled
    EXTI->FTSR			|=	 EXTI_FTSR_TR13;								// Falling edge trigger enabled

    NVIC_SetPriority ( EXTI15_10_IRQn, 1 ); 								// Set Priority to 1
    NVIC_EnableIRQ   ( EXTI15_10_IRQn );  									// Enable EXTI15_10_IRQn interrupt in NVIC
}


/**
 * @brief       void Conf_TIMERS  ( uint32_t )
 * @details     It configures the Timers.
 *
 * 				-TIM5:
 * 					-- f_TIM5 = myCLK / ( PSC + 1 ) = 2.097MHz / ( 999 + 1 ) = 2.097 kHz
 * 					-- Overflow: Every 1 second ( 2097 / f_TIM5 ) = ( 2097 / 2097 ) = 1
 * 						--- Downcounter.
 * 						--- Prescaler = 999.
 * 						--- ARR = 2097.
 *
 * @param[in]    myCLK:	Internal Clock.
 *
 * @param[out]   NaN.
 *
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        2/January/2018
 * @version     2/January/2018   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
void Conf_TIMERS  ( uint32_t myCLK )
{
	// Timer5 Peripheral clock enable
	RCC->APB1ENR	|=	 RCC_APB1ENR_TIM5EN;

	// Disable TIM5 and configure it
	TIM5->SMCR	&=	~( TIM_SMCR_SMS_0 | TIM_SMCR_SMS_1 | TIM_SMCR_SMS_2 );	// Slave mode disabled - if CEN = ‘1 then the prescaler is clocked directly by the internal clock.
	TIM5->CR1	&=	~( TIM_CR1_CEN | TIM_CR1_CMS_1 | TIM_CR1_CMS_0 );		// Counter disabled ( Timer DISABLED ), Edge-aligned mode. The counter counts up or down depending on the direction bit (DIR)

	TIM5->CNT	 =	 0;														// Reset counter
	TIM5->PSC	 =	 ( 1000 - 1 );											// Prescaler = 999
	TIM5->ARR	 =	 myCLK / ( TIM5->PSC + 1 );								// Overflow every ~ 1s: f_Timer5: myCLK / ( PSC + 1 ) = 2.097MHz / ( 999 + 1 ) = 2.097 kHz

	// Enable Interrupt
	NVIC_SetPriority ( TIM5_IRQn, 1 ); 										// Set Priority to 1
	NVIC_EnableIRQ   ( TIM5_IRQn );  										// Enable TIM5_IRQn interrupt in NVIC

	// Finish configuring TIM5 ( it will be enabled in the main )
	TIM5->CR1	|=	 ( TIM_CR1_ARPE | TIM_CR1_DIR | TIM_CR1_URS );			// Auto-reload preload enable
																			// Counter used as downcounter
																			// Only counter overflow/underflow generates an update interrupt or DMA request if enabled
}
