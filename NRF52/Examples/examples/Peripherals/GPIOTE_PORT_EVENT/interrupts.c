/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/July/2018
 * @version     3/July/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
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
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/July/2018
 * @version     3/July/2018   The ORIGIN
 * @pre         The LEDs are connected like Common Anode.
 * @warning     N/A
 */
void GPIOTE_IRQHandler()
{
  /* Port Event  */
  if ( ( NRF_GPIOTE->EVENTS_PORT != 0 ) && ( ( NRF_GPIOTE->INTENSET & GPIOTE_INTENSET_PORT_Msk ) == ( GPIOTE_INTENSET_PORT_Enabled << GPIOTE_INTENSET_PORT_Pos ) ) )
  {
    /* Button 1  */
    if ( ( NRF_P0->IN & GPIO_IN_PIN13_Msk ) == ( GPIO_IN_PIN13_Low << GPIO_IN_PIN13_Pos ) )
    {
      if ( ( changeLEDsSTATE & 0x01 ) == 0x01 )
      {
        // Turn off LED1
        NRF_P0->OUTSET  = ( 1 << LED1 );
        changeLEDsSTATE  &=  ~0x01;
      }
      else
      {
        // Turn on LED1
        NRF_P0->OUTCLR  = ( 1 << LED1 );
        changeLEDsSTATE  |=  0x01;
      }
    }
    
    /* Button 2  */
    if ( ( NRF_P0->IN & GPIO_IN_PIN14_Msk ) == ( GPIO_IN_PIN14_Low << GPIO_IN_PIN14_Pos ) )
    {
      if ( ( changeLEDsSTATE & 0x02 ) == 0x02 )
      {
        // Turn off LED2
        NRF_P0->OUTSET  = ( 1 << LED2 );
        changeLEDsSTATE  &=  ~0x02;
      }
      else
      {
        // Turn on LED2
        NRF_P0->OUTCLR  = ( 1 << LED2 );
        changeLEDsSTATE  |=  0x02;
      }
    }
    
    /* Button 3  */
    if ( ( NRF_P0->IN & GPIO_IN_PIN15_Msk ) == ( GPIO_IN_PIN15_Low << GPIO_IN_PIN15_Pos ) )
    {
      if ( ( changeLEDsSTATE & 0x04 ) == 0x04 )
      {
        // Turn off LED3
        NRF_P0->OUTSET  = ( 1 << LED3 );
        changeLEDsSTATE  &=  ~0x04;
      }
      else
      {
        // Turn on LED3
        NRF_P0->OUTCLR  = ( 1 << LED3 );
        changeLEDsSTATE  |=  0x04;
      }
    }

    /* Button 4  */
    if ( ( NRF_P0->IN & GPIO_IN_PIN16_Msk ) == ( GPIO_IN_PIN16_Low << GPIO_IN_PIN16_Pos ) )
    {
      if ( ( changeLEDsSTATE & 0x08 ) == 0x08 )
      {
        // Turn off LED4
        NRF_P0->OUTSET  = ( 1 << LED4 );
        changeLEDsSTATE  &=  ~0x08;
      }
      else
      {
        // Turn on LED4
        NRF_P0->OUTCLR  = ( 1 << LED4 );
        changeLEDsSTATE  |=  0x08;
      }
    }

    NRF_GPIOTE->EVENTS_PORT = 0;                      // Clear ( flag )
  }
}