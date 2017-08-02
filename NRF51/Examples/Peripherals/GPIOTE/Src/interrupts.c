/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        12/April/2017
 * @version     12/April/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */

#include "interrupts.h"


/**
 * @brief       void GPIOTE_IRQHandler ()
 * @details     It changes the state of the LEDs depending on which button was pressed.
 *
 *              changeLEDsSTATE = 0x01: LED1 --> BTN1.
 *              changeLEDsSTATE = 0x02: LED2 --> BTN2.
 *              changeLEDsSTATE = 0x04: LED3 --> BTN3.
 *              changeLEDsSTATE = 0x08: LED4 --> BTN4.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        20/June/2017
 * @version     20/June/2017   The ORIGIN
 * @pre         The LEDs are connected like Common Anode.
 * @warning     NaN
 */
void GPIOTE_IRQHandler()
{
    // Channel 0
    if ( ( NRF_GPIOTE->EVENTS_IN[0] != 0 ) && ( ( NRF_GPIOTE->INTENSET & GPIOTE_INTENSET_IN0_Msk ) != 0 ) )
    {
		if ( ( changeLEDsSTATE & 0x01 ) == 0x01 )
        {
        // Turn off LED1
            NRF_GPIO->OUTSET  = ( 1 << LED1 );
            changeLEDsSTATE  &=  ~0x01;
        }
		else
        {
        // Turn on LED1
            NRF_GPIO->OUTCLR  = ( 1 << LED1 );
            changeLEDsSTATE  |=  0x01;
        }

        NRF_GPIOTE->EVENTS_IN[0] = 0;                      // Clear ( flag )
    }

    // Channel 1
    if ( ( NRF_GPIOTE->EVENTS_IN[1] != 0 ) && ( ( NRF_GPIOTE->INTENSET & GPIOTE_INTENSET_IN1_Msk ) != 0 ) )
    {
		if ( ( changeLEDsSTATE & 0x02 ) == 0x02 )
        {
        // Turn off LED2
            NRF_GPIO->OUTSET  = ( 1 << LED2 );
            changeLEDsSTATE  &=  ~0x02;
        }
		else
        {
        // Turn on LED2
            NRF_GPIO->OUTCLR  = ( 1 << LED2 );
            changeLEDsSTATE  |=  0x02;
        }

        NRF_GPIOTE->EVENTS_IN[1] = 0;                      // Clear ( flag )
    }

    // Channel 2
    if ( ( NRF_GPIOTE->EVENTS_IN[2] != 0 ) && ( ( NRF_GPIOTE->INTENSET & GPIOTE_INTENSET_IN2_Msk ) != 0 ) )
    {
		if ( ( changeLEDsSTATE & 0x04 ) == 0x04 )
        {
        // Turn off LED3
            NRF_GPIO->OUTSET  = ( 1 << LED3 );
            changeLEDsSTATE  &=  ~0x04;
        }
		else
        {
        // Turn on LED3
            NRF_GPIO->OUTCLR  = ( 1 << LED3 );
            changeLEDsSTATE  |=  0x04;
        }

        NRF_GPIOTE->EVENTS_IN[2] = 0;                      // Clear ( flag )
    }

    // Channel 3
    if ( ( NRF_GPIOTE->EVENTS_IN[3] != 0 ) && ( ( NRF_GPIOTE->INTENSET & GPIOTE_INTENSET_IN3_Msk ) != 0 ) )
    {
		if ( ( changeLEDsSTATE & 0x08 ) == 0x08 )
        {
        // Turn off LED4
            NRF_GPIO->OUTSET  = ( 1 << LED4 );
            changeLEDsSTATE  &=  ~0x08;
        }
		else
        {
        // Turn on LED4
            NRF_GPIO->OUTCLR  = ( 1 << LED4 );
            changeLEDsSTATE  |=  0x08;
        }

        NRF_GPIOTE->EVENTS_IN[3] = 0;                      // Clear ( flag )
    }
}
