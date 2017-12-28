/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        26/December/2017
 * @version     26/December/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */


#include "functions.h"

/**
 * @brief       void conf_CLK  ( void )
 * @details     It configures MCO.
 *
 * 				- MCO ( SYSCLK/1 ):	PA_8
 *
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        28/December/2017
 * @version     28/December/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
void conf_CLK  ( void )
{
	RCC->CFGR	&=	 0xF8FFFFFF;											// MCO output disabled, no clock on MCO
	RCC->CFGR	|=	 ( RCC_CFGR_MCOPRE_DIV1 | RCC_CFGR_MCOSEL_SYSCLK );		// MCO = SYSCLK/1 | MCO ENABLED
}



/**
 * @brief       void conf_GPIO  ( void )
 * @details     It configures GPIO to work with the LEDs and
 * 				MCO ( SYSCLK/1 ).
 *
 * 				- LED1:	PA_5
 * 				- MCO:  PA_8
 *
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        26/December/2017
 * @version		28/December/2017   MCO added.
 * 				26/December/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
void conf_GPIO  ( void )
{
	// GPIOC Periph clock enable
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // Configure LED1
    GPIOA->MODER	|=	 GPIO_MODER_MODER5_0;			// General purpose output mode
    GPIOA->OTYPER	&=	~GPIO_OTYPER_OT_5; 				// Output push-pull
    GPIOA->OSPEEDR	&=	~GPIO_OSPEEDER_OSPEEDR5_Msk;	// Low speed
    GPIOA->PUPDR	&=	~GPIO_PUPDR_PUPDR5_Msk;			// No pull-up, pull-down

    // Configure MCO
    GPIOA->MODER	|=	 GPIO_MODER_MODER8_1;			// Alternate function mode
    GPIOA->OTYPER	&=	~GPIO_OTYPER_OT_8;				// Output push-pull
    GPIOA->OSPEEDR	|=	 GPIO_OSPEEDER_OSPEEDR8_0;		// Medium speed
    GPIOA->PUPDR	&=	~GPIO_PUPDR_PUPDR5_Msk;			// No pull-up, pull-down
}
