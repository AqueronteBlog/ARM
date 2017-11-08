/**
 * @brief       main.c
 * @details     [todo].
 *
 *              The rest of the time, the microcontroller is in low power.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        8/November/2017
 * @version     8/November/2017    The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     Softdevice S310 was used although the file's name is S130. The softdevice
 *              is not used in this example anyway because of Bluetooth was not used.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "nrf.h"
#include "nrf_delay.h"
#include "ble.h"
#include "variables.h"
#include "functions.h"


int main( void )
{
    conf_GPIO   ();
    conf_GPIOTE ();
    conf_TIMER0 ();



    NRF_TIMER0->TASKS_START  =   1;                 // Start Timer0

    while( 1 )
    {
        //NRF_POWER->SYSTEMOFF = 1;
        NRF_POWER->TASKS_LOWPWR = 1;                // Sub power mode: Low power.

        // Enter System ON sleep mode
    	__WFE();
    	// Make sure any pending events are cleared
    	__SEV();
    	__WFE();
    }
}
