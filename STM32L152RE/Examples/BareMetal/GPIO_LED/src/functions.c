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
 * @brief       void conf_GPIO  ( void )
 * @details     It configures GPIO to work with the LEDs.
 *
 * 				- LED1:	PA_5
 *
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
void conf_GPIO  ( void )
{
	// GPIOC Periph clock enable
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    // Configure LED1
    GPIOA->MODER	|=	 GPIO_MODER_MODER5_0;			// General purpose output mode
    GPIOA->OTYPER	&=	~GPIO_OTYPER_OT_5; 				// Output push-pull
    GPIOA->OSPEEDR	&=	~GPIO_OSPEEDER_OSPEEDR5_Msk;	// Low speed
    GPIOA->PUPDR	&=	~GPIO_PUPDR_PUPDR5_Msk;			// No pull-up, pull-down
}
