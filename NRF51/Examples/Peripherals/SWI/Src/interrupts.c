/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/June/2017
 * @version     29/June/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "interrupts.h"


/**
 * @brief       void RTC0_IRQHandler ()
 * @details     RTC0 subroutine. It enables one of the software interrupts
 *              according to the 'chooseLEDON' variable every 125ms.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/June/2017
 * @version     29/June/2017   The ORIGIN
 * @pre         All the LEDs are connected like Common Anode.
 * @warning     NaN
 */
void RTC0_IRQHandler()
{
    if ( ( NRF_RTC0->EVENTS_TICK != 0 ) && ( ( NRF_RTC0->INTENSET & RTC_INTENSET_TICK_Enabled ) != 0 ) )
    {
        NRF_RTC0->EVENTS_TICK    =   0;                                     // Reset flag

        // Enable the right software interrupt
        switch ( chooseLEDON ){
        // LED1 ON
        case LED1_ON:
            chooseLEDON  =   LED2_ON;
            NVIC_SetPendingIRQ ( SWI0_IRQn );
            break;

        case LED2_ON:
        // LED2 ON
            chooseLEDON  =   LED3_ON;
            NVIC_SetPendingIRQ ( SWI1_IRQn );
            break;

        case LED3_ON:
        // LED3 ON
            chooseLEDON  =   LED4_ON;
            NVIC_SetPendingIRQ ( SWI2_IRQn );
            break;

        case LED4_ON:
        // LED4 ON
            chooseLEDON  =   0xFF;
            NVIC_SetPendingIRQ ( SWI3_IRQn );
            break;

        default:
        // All the LEDs OFF
            chooseLEDON  =   LED1_ON;
            NVIC_SetPendingIRQ ( SWI4_IRQn );
            break;
        }
    }
}



/**
 * @brief       void SWI0_IRQHandler ()
 * @details     SWI0 subroutine. It turns the LED1 on.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/June/2017
 * @version     29/June/2017   The ORIGIN
 * @pre         The LED1 is connected like Common Anode.
 * @warning     NaN
 */
void SWI0_IRQHandler()
{
    NRF_GPIO->OUTCLR =  ( 1UL << LED1 );

    NVIC_ClearPendingIRQ ( SWI0_IRQn );             // Clear flag
}


/**
 * @brief       void SWI1_IRQHandler ()
 * @details     SWI1 subroutine. It turns the LED2 on.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/June/2017
 * @version     29/June/2017   The ORIGIN
 * @pre         The LED2 is connected like Common Anode.
 * @warning     NaN
 */
void SWI1_IRQHandler()
{
    NRF_GPIO->OUTCLR =  ( 1UL << LED2 );

    NVIC_ClearPendingIRQ ( SWI1_IRQn );             // Clear flag
}


/**
 * @brief       void SWI2_IRQHandler ()
 * @details     SWI2 subroutine. It turns the LED3 on.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/June/2017
 * @version     29/June/2017   The ORIGIN
 * @pre         The LED3 is connected like Common Anode.
 * @warning     NaN
 */
void SWI2_IRQHandler()
{
    NRF_GPIO->OUTCLR =  ( 1UL << LED3 );

    NVIC_ClearPendingIRQ ( SWI2_IRQn );             // Clear flag
}


/**
 * @brief       void SWI3_IRQHandler ()
 * @details     SWI3 subroutine. It turns the LED4 on.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/June/2017
 * @version     29/June/2017   The ORIGIN
 * @pre         The LED4 is connected like Common Anode.
 * @warning     NaN
 */
void SWI3_IRQHandler()
{
    NRF_GPIO->OUTCLR =  ( 1UL << LED4 );

    NVIC_ClearPendingIRQ ( SWI3_IRQn );             // Clear flag
}


/**
 * @brief       void SWI4_IRQHandler ()
 * @details     SWI4 subroutine. It turns all the LEDs off.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/June/2017
 * @version     29/June/2017   The ORIGIN
 * @pre         The LED1, LED2, LED3 and LED4 are connected like Common Anode.
 * @warning     NaN
 */
void SWI4_IRQHandler()
{
    NRF_GPIO->OUTSET =  ( ( 1UL << LED1 ) | ( 1UL << LED2 ) | ( 1UL << LED3 ) | ( 1UL << LED4 ) );

    NVIC_ClearPendingIRQ ( SWI4_IRQn );             // Clear flag
}
