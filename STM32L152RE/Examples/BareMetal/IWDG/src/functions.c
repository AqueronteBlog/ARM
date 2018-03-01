/**
 * @brief       functions.c
 * @details     Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        1/March/2018
 * @version     1/March/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
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
	// GPIOA & GPIOC Periph clock enable
	RCC->AHBENR 	|= 	 ( RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN );

	// SYSCFG Periph clock enable
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
