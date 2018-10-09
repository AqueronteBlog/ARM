/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/October/2018
 * @version     9/October/2018   The ORIGIN
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
 * @date        9/October/2018
 * @version     9/October/2018   The ORIGIN
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
		myState	 =	 STATE_TRIGGER_INTERNAL_TEMPERATURE;

		/* Clear flags	 */
		RTC->ISR	&=	~( RTC_ISR_WUTF | RTC_ISR_INIT );
		EXTI->PR	|=	 EXTI_PR_PR20;
	}

	/* Enable the write protection for RTC registers */
	RTC->WPR	 =	 0xFF;
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
 * @date        9/October/2018
 * @version     9/October/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void USART2_IRQHandler ( void )
{
	/* TX: TRANSMISSION COMPLETE	*/
	if ( ( USART2->SR & USART_SR_TC_Msk ) == USART_SR_TC )
	{
		USART2->SR	&=	~USART_SR_TC ;							// Clear flag

		/* Stop transmitting data when that character is found */
		if ( *myPtr  == '\n' )
		{
			USART2->CR1	&=	~USART_CR1_TE;						// Transmitter Disabled

			/* Enable RTC WakeUp IRQ  */
			NVIC_EnableIRQ ( RTC_WKUP_IRQn );

			/* LED1 off to indicate that all the process was finished ( reading data from sensor and all data were transmitted	 */
			myState		 =	 STATE_SLEEP_MODE;
			GPIOA->BRR	 =	( 1UL << LED_1 );					// Turn it OFF
		}
		else
		{
			USART2->DR    =   *++myPtr;
		}
	}
}



/**
 * @brief       void ADC1_IRQHandler ()
 * @details     ADC1 subroutine.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/October/2018
 * @version     9/October/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void ADC1_IRQHandler ( void )
{
	/* EOC: END OF CONVERSION	*/
	if ( ( ADC1->SR & ADC_SR_EOCS_Msk ) == ADC_SR_EOCS )
	{
		if ( myNextADC_Measurement == INTERNAL_TEMPERATURE_TRIGGERED )
		{
		/* Internal Temperature Triggered, new state -> Get Raw Internal Temperature value	 */
			myState	 				 =	 STATE_GET_RAW_TEMPERATURE_DATA;
			myNextADC_Measurement	 =	 VDD_TRIGGERED;
		}
		else
		{
		/* VDD Triggered, new state -> Get Raw VDD value	 */
			myState	 				 =	 STATE_GET_RAW_VDD_DATA;
			myNextADC_Measurement	 =	 INTERNAL_TEMPERATURE_TRIGGERED;
		}

		myRawADC_value	 =	 ( ADC1->DR & ADC_DR_DATA_Msk );		// Read raw ADC value
		ADC1->SR		&=	~ADC_SR_EOCS ;							// Clear flag
	}
}

