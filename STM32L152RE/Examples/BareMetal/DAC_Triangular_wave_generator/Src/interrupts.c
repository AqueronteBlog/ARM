/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        12/October/2018
 * @version     12/October/2018   The ORIGIN
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
 * @date        1/November/2018
 * @version     1/November/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void RTC_WKUP_IRQHandler ( void )
{
	/* Disable backup write protection	*/
	PWR->CR		|=	 PWR_CR_DBP;

	/* Disable the write protection for RTC registers */
	RTC->WPR   	 =	 ( 0xCA & RTC_WPR_KEY_Msk );
	RTC->WPR	 = 	 ( 0x53 & RTC_WPR_KEY_Msk );

	/* WAKE-UP Interrupt	 */
	if ( ( RTC->ISR & RTC_ISR_WUTF_Msk ) == RTC_ISR_WUTF )
	{
		/* DAC channel2 Software trigger enabled	 */
		DAC->SWTRIGR	|=	 DAC_SWTRIGR_SWTRIG2;

		RTC->ISR	&=	~( RTC_ISR_WUTF | RTC_ISR_INIT );	// Clear flag
		EXTI->PR	|=	 EXTI_PR_PR20;
	}

	/* Enable the write protection for RTC registers */
	RTC->WPR   	 =	 0xFF;
	RTC->WPR   	 =	 0xFF;

	/* Access to RTC, RTC Backup and RCC CSR registers disabled */
	PWR->CR &= ~PWR_CR_DBP;
}
