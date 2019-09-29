/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/September/2019
 * @version     29/September/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */


#include "functions.h"

/**
 * @brief       void Conf_CLK  ( void )
 * @details     It configures MCO.
 *
 * 				- MCO ( SYSCLK/1 ):	PA_8
 *
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/September/2019
 * @version     29/September/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void Conf_CLK  ( void )
{
	RCC->CFGR	&=	 0xF8FFFFFF;											// MCO output disabled, no clock on MCO
	RCC->CFGR	|=	 ( RCC_CFGR_MCOPRE_DIV1 | RCC_CFGR_MCOSEL_SYSCLK );		// MCO = SYSCLK/1 | MCO ENABLED
}



/**
 * @brief       void Conf_SYSTICK  ( uint32_t )
 * @details     It configures the SysTick at 1ms.
 *
 * @param[in]    myticks:	Value of the CLK to generate ticks every 1ms.
 *
 * @param[out]   NaN.
 *
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/September/2019
 * @version     29/September/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void Conf_SYSTICK  ( uint32_t myticks )
{
	SysTick->CTRL	&=	 ~SysTick_CTRL_ENABLE_Msk;										// SysTick DISABLED

	SysTick->LOAD	 =	 (uint32_t)(myticks - 1UL);										// Load the value
	SysTick->VAL	 =	 0UL;															// Reset current Counter value

	/* Set the PRIGROUP[10:8] bits according to the PriorityGroup parameter value */
	//NVIC_SetPriorityGrouping	( NVIC_PRIORITYGROUP_4 );
	NVIC_SetPriority 			( SysTick_IRQn, ( 1UL << __NVIC_PRIO_BITS ) - 1UL );	// Set Priority for Systick Interrupt
	NVIC_EnableIRQ				( SysTick_IRQn );										// Enable interrupt

	SysTick->CTRL  	 = 	( SysTick_CTRL_CLKSOURCE_Msk |
	                   	  SysTick_CTRL_TICKINT_Msk   |
						  SysTick_CTRL_ENABLE_Msk );                    				// Enable SysTick IRQ and SysTick Timer
}



/**
 * @brief       void Conf_GPIO  ( void )
 * @details     It configures GPIO to work with the LEDs and MCO ( SYSCLK/1 ).
 *
 * 				- LED1:	PA_5
 * 				- MCO:  PA_8
 *
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/September/2019
 * @version		29/September/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void Conf_GPIO  ( void )
{
	// GPIOC Periph clock enable
	/*RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // Configure LED1
    GPIOA->MODER	|=	 GPIO_MODER_MODER5_0;			// General purpose output mode
    GPIOA->OTYPER	&=	~GPIO_OTYPER_OT_5; 				// Output push-pull
    GPIOA->OSPEEDR	&=	~GPIO_OSPEEDER_OSPEEDR5_Msk;	// Low speed
    GPIOA->PUPDR	&=	~GPIO_PUPDR_PUPDR5_Msk;			// No pull-up, pull-down

    // Configure MCO
    GPIOA->MODER	|=	 GPIO_MODER_MODER8_1;			// Alternate function mode
    GPIOA->OTYPER	&=	~GPIO_OTYPER_OT_8;				// Output push-pull
    GPIOA->OSPEEDR	|=	 GPIO_OSPEEDER_OSPEEDR8_0;		// Medium speed
    GPIOA->PUPDR	&=	~GPIO_PUPDR_PUPDR5_Msk;			// No pull-up, pull-down*/
}
