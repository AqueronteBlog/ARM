/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        14/November/2017
 * @version     14/November/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "interrupts.h"


/**
 * @brief       void UART0_IRQHandler ()
 * @details     It sends the data from the ADC through the UART.
 *
 *              The LED2 will be turned off to indicate that the whole
 *              process ( Read ADC + transmission ) was completed.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        17/November/2017
 * @version     17/November/2017   The ORIGIN
 * @pre         The data to be transmitted is raw data from the ADC, that data needs
 *              to be processed: ( 3.0 * 1.2 * myADCvalue )/( 2^8 - 1 ).
 *
 *              VBG:        1.2V
 *              Prescaler:  3.0
 *              Resolution: 8-bits ( 2^8 )
 *
 *              Example: myADCvalue = 201 ( 0xC9 )
 *
 *                  Voltage = ( 3.0 * 1.2 * 201 )/( 2^8 - 1 ) ~ 2.8376V
 *
 * @warning     NaN
 */
void UART0_IRQHandler(void)
{
    /* Transmission */
    if ( ( NRF_UART0->EVENTS_TXDRDY != 0 ) && ( NRF_UART0->INTENSET & UART_INTENSET_TXDRDY_Msk ) )
    {
        // Clear UART TX event flag.
        NRF_UART0->EVENTS_TXDRDY = 0;

        // Everything was transmitted, stop the UART and turn the LED1 off
        NRF_UART0->TASKS_STOPTX      =   1;
        NRF_GPIO->OUTSET             =   ( 1UL << LED2 );
    }
}


/**
 * @brief       void ADC_IRQHandler ()
 * @details     ADC measurement is completed, data ready.
 *
 *              Start transmitting the data through the UART.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        17/November/2017
 * @version     17/November/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
void ADC_IRQHandler()
{
    if ( ( NRF_ADC->EVENTS_END != 0 ) && ( NRF_ADC->BUSY == 0 ) )
    {
        myADCvalue                   =   ( NRF_ADC->RESULT & 0x000000FF);   // Read raw ADC

        NRF_ADC->EVENTS_END          =   0;                                 // Clear ( flag )


        NRF_GPIO->OUTCLR             =   ( 1UL << LED2 );                   // Turn LED2 on, it will be turned off when the data is sent through the UART
        NRF_UART0->TASKS_STARTTX     =   1;                                 // Start transmission
        NRF_UART0->TXD               =   myADCvalue;
    }
}




/**
 * @brief       void RTC1_IRQHandler ()
 * @details     RTC1 interruption. It checks if there is an interruption
 *              of RTC1.
 *
 *
 * @return      NaN
 *
 * @author      Manuel Caballero
 * @date        17/November/2017
 * @version     17/November/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 */
void RTC1_IRQHandler()
{
    if ( ( NRF_RTC1->EVENTS_COMPARE[0] != 0 ) && ( ( NRF_RTC1->INTENSET & RTC_INTENSET_COMPARE0_Msk ) != 0 ) )
    {

        NRF_RTC1->CC[0]             +=   200;             // New interruption on 2s
        NRF_RTC1->EVENTS_COMPARE[0]  =   0;               // Clear ( flag ) compare register 0 event
    }
}
