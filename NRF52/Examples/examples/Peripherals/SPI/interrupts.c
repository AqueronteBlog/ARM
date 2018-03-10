/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/March/2018
 * @version     10/March/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "interrupts.h"



/**
 * @brief       void WDT_IRQHandler ()
 * @details     WDT interruption. Turn all the LEDs on before the system reset.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        18/February/2018
 * @version     18/February/2018   The ORIGIN
 * @pre         The LEDs are connected like Common Anode.
 * @warning     N/A
 */
void WDT_IRQHandler()
{
    NRF_P0->OUTCLR |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );
}