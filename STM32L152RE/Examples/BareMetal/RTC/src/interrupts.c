/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/March/2018
 * @version     9/March/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "interrupts.h"



/**
 * @brief       void RTC_WKUP_IRQHandler ( void )
 * @details     RTC Wake-up timer subroutine.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        26/March/2018
 * @version     26/March/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
uint32_t myLEDstate	 =	 0;
void RTC_WKUP_IRQHandler ( void )
{
	if ( ( RTC->ISR & RTC_ISR_WUTF_Msk ) == RTC_ISR_WUTF )
	{
		if ( myLEDstate	 ==	 0 )
		{
			GPIOA->BSRR	 =	 ( 1 << LED_1 );			// LED1 ON
			myLEDstate	 =	 1;
		}
		else
		{
			GPIOA->BRR	 =	 ( 1 << LED_1 );			// LED1 OFF
			myLEDstate	 =	 0;
		}

		RTC->ISR	=	(~((RTC_ISR_WUTF) | RTC_ISR_INIT)|(RTC->ISR & RTC_ISR_INIT));

		//RTC->ISR	&=	~( RTC_ISR_WUTF | RTC_ISR_INIT );
	}

	EXTI->PR	|=	 EXTI_PR_PR20;
}
