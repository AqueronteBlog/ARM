/**
 * @brief       main.c
 * @details     This example shows how the software interrupts work. Every software interrupt
 *              will be linked to an LED but SI4 which is linked to all the LEDs.
 *
 *              Every 125ms, the state of the LEDs will change depending on the following:
 *
 *                  - SWI0: Turn on the LED1.
 *                  - SWI1: Turn on the LED2.
 *                  - SWI2: Turn on the LED3.
 *                  - SWI3: Turn on the LED4.
 *                  - SWI4: Turn off all the LEDs.
 *
 *
 *              This firmware is just an example about how to use the SWIs on the nrf51422.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/June/2017
 * @version     29/June/2017    The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     Softdevice S310 was used although the file's name is S130. The softdevice
 *              is not used in this example anyway because of Bluetooth was not used.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "nrf.h"
#include "ble.h"
#include "variables.h"
#include "functions.h"


int main( void )
{
    conf_GPIO   ();
    conf_LFCLK  ();
    conf_SWI    ();
    conf_RTC0   ();

    NRF_RTC0->TASKS_START = 1;              // Start RTC0

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

