/**
 * @brief       main.c
 * @details     This firmware changes the state of the LEDs depending on which button
 *              was pressed.
 *
 *              GPIOTE will be associated with the BTNs to generate an interruption.
 *
 *              The microcontroller will remain in low power until it occurs an event.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        16/June/2017
 * @version     16/June/2017   The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     Softdevice S310 was used although the file's name is S130. The softdevice
 *              is not used in this example anyway because of Bluetooth was not used.
 */

#include "nrf.h"
#include "ble.h"
#include "variables.h"
#include "functions.h"


int main( void )
{
    conf_GPIO   ();
    conf_GPIOTE ();

    while( 1 )
    {
        //NRF_POWER->SYSTEMOFF = 1;
        NRF_POWER->TASKS_LOWPWR = 1;        // Sub power mode: Low power.
        __SEV();
        __WFI();
        __WFI();
    }
}
