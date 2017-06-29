/**
 * @brief       main.c
 * @details     It changes the state of the LED1 and LED4 using the RTCs.
 *
 *                  - LED1. RTC0: Tick, Interrupt ON.           Blinks every 125ms.
 *                  - LED4. RTC1: Channel 0, Interrupt ON.      Blinks every 2s.
 *
 *              This firmware is just an example about how to use the RTCs on the nrf51422.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        8/June/2017
 * @version     8/June/2017    The ORIGIN
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
    conf_LFCLK  ();
    conf_RTC0   ();
    conf_RTC1   ();

    NRF_RTC0->TASKS_START = 1;    // Start RTC0
    NRF_RTC1->TASKS_START = 1;    // Start RTC1

    while( 1 )
    {
        // NRF_POWER->SYSTEMOFF    = 1;
        NRF_POWER->TASKS_LOWPWR = 1;        // Sub power mode: Low power.

        // Enter System ON sleep mode
		__WFE();
		// Make sure any pending events are cleared
		__SEV();
		__WFE();
    }
}
