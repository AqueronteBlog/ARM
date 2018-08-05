/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        4/August/2018
 * @version     4/August/2018   The ORIGIN
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
 * @date        4/August/2018
 * @version     4/August/2018   The ORIGIN
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
		if ( myLEDstate	 ==	 0 )
		{
			GPIOA->BSRR	 =	 ( 1 << LED_1 );				// LED1 ON
			myLEDstate	 =	 1;
		}
		else
		{
			GPIOA->BRR	 =	 ( 1 << LED_1 );				// LED1 OFF
			myLEDstate	 =	 0;
		}

		RTC->ISR	&=	~( RTC_ISR_WUTF | RTC_ISR_INIT );	// Clear flag
	}

	/* Enable the write protection for RTC registers */
	RTC->WPR   	 =	 0xFF;
	RTC->WPR   	 =	 0xFF;

	/* Access to RTC, RTC Backup and RCC CSR registers disabled */
	PWR->CR &= ~PWR_CR_DBP;
}



/**
 * @brief       void UART5_IRQHandler ()
 * @details     UART5 subroutine.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        4/August/2018
 * @version     4/August/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void UART5_IRQHandler(void)
{
	/* TX: TRANSMISSION COMPLETE	*/
	if ( ( UART5->SR & USART_SR_TC ) == USART_SR_TC )
	{
		UART5->SR	&=	~USART_SR_TC ;									// Clear flag

		UART5->CR1	&=	~USART_CR1_TE;									// Transmitter Disabled
	}
}
