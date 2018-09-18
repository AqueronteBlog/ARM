/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        18/September/2018
 * @version     18/September/2018   The ORIGIN
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
 * @date        18/September/2018
 * @version     18/September/2018   The ORIGIN
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
		myState	 		 =	 1UL;

		/* Clear flags	 */
		RTC->ISR	&=	~( RTC_ISR_WUTF | RTC_ISR_INIT );
		EXTI->PR	|=	 EXTI_PR_PR20;
	}

	/* Enable the write protection for RTC registers */
	RTC->WPR   	 =	 0xFF;
	RTC->WPR   	 =	 0xFF;

	/* Access to RTC, RTC Backup and RCC CSR registers disabled */
	PWR->CR &= ~PWR_CR_DBP;
}



/**
 * @brief       void USART2_IRQHandler ()
 * @details     USART2 subroutine.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        18/September/2018
 * @version     18/September/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void USART2_IRQHandler ( void )
{
	/* TX: TRANSMISSION COMPLETE	*/
	if ( ( USART2->SR & USART_SR_TC ) == USART_SR_TC )
	{
		USART2->SR	&=	~USART_SR_TC ;								// Clear flag

		/* Stop transmitting data when that character is found */
		if ( *myPtr  == '\n' )
		{
			myUART_TxEnd	 =	 1UL;
			USART2->CR1		&=	~USART_CR1_TE;						// Transmitter Disabled
		}
		else
		{
			USART2->DR    =   *++myPtr;
		}
	}
}
