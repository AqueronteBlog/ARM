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
 * @details     It disabled MCO ans enables the LSI for IWDG
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
