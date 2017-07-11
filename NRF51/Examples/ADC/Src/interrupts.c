/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        2/June/2017
 * @version     2/June/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "interrupts.h"


/**
 * @brief       void UART0_IRQHandler ()
 * @details     It sends the data from the ADC through the UART.
 *
 *              The LED1 will be turned off to indicate that the whole
 *              process ( Read ADC + transmission ) was completed.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        11/July/2017
 * @version     11/July/2017   The ORIGIN
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
        NRF_GPIO->OUTSET             =   ( 1UL << LED1 );
    }
}


/**
 * @brief       void TIMER0_IRQHandler ()
 * @details     It starts a new ADC measurement ( VDD ) every
 *              1 second.
 *
 *              Turn the LED1 on to indicate that the process has just been started.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        11/July/2017
 * @version     11/July/2017   The ORIGIN
 * @pre         The LED1 will be turned off again when the process is finished.
 * @warning     NaN
 */
void TIMER0_IRQHandler()
{
    if ( ( NRF_TIMER0->EVENTS_COMPARE[0] != 0 ) && ( ( NRF_TIMER0->INTENSET & TIMER_INTENSET_COMPARE0_Msk ) != 0 ) )
    {
        NRF_GPIO->OUTCLR         =   ( 1UL << LED1 );       // Turn the LED1 on
        NRF_ADC->TASKS_START     =   1;                     // Start another ADC measurement ( one-shot )


        NRF_TIMER0->EVENTS_COMPARE[0] = 0;                  // Clear ( flag ) compare register 0 event
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
 * @date        11/July/2017
 * @version     11/July/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
void ADC_IRQHandler()
{
    if ( ( NRF_ADC->EVENTS_END != 0 ) && ( NRF_ADC->BUSY == 0 ) )
    {
        myADCvalue                   =   ( NRF_ADC->RESULT & 0x000000FF);   // Read raw ADC

        NRF_ADC->EVENTS_END          =   0;                                 // Clear ( flag )


        NRF_UART0->TASKS_STARTTX     =   1;                                 // Start transmission
        NRF_UART0->TXD               =   myADCvalue;
    }
}

