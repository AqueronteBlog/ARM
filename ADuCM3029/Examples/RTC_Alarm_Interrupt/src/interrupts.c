/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        25/June/2019
 * @version     25/June/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "interrupts.h"


/**
 * @brief       void RTC1_Int_Handler  ( void )
 * @details     RTC1 subroutine.
 *
 *
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        25/June/2019
 * @version     26/June/2019    Pending status of posted writes was added
 * 				25/June/2019    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void RTC1_Int_Handler ( void )
{
	/* Check if RTC1 interrupt pending	 */
	if ( ( pADI_RTC1->SR0 & ( 1U << BITP_RTC_SR0_ALMINT ) ) == ( 1U << BITP_RTC_SR0_ALMINT ) )
	{
		/* Next action	 */
		myState	 =	 1UL;

		/* Reset RTC1 counter register	 */
		pADI_RTC1->CNT0	 =	 0U;			// Lower 16 bits of the RTC counter
		pADI_RTC1->CNT1	 =	 0U;			// Upper 16 bits of the RTC counter

		/* Pending Status of Posted Writes to CR0
		 *  - NOTE:
		 *  	This is dangerous!, the uC may get stuck here, add a counter to avoid that circumstance.
		 */
		while ( ( pADI_RTC1->SR1 & ( 1U << BITP_RTC_SR1_WPNDCR0 ) ) == ( 1U << BITP_RTC_SR1_WPNDCR0 ) );


		/* Clear Alarm Interrupt Source	 */
		pADI_RTC1->SR0	|=	 ( 1U << BITP_RTC_SR0_ALMINT );

		/* Pending Status of Posted Writes to ALMINT
		 *  - NOTE:
		 *  	This is dangerous!, the uC may get stuck here, add a counter to avoid that circumstance.
		 */
		while ( ( pADI_RTC1->SR3 & ( 1U << BITP_RTC_SR3_ALMINTMIR ) ) == ( 1U << BITP_RTC_SR3_ALMINTMIR ) );
	}
}
