/**
 * @brief       main.c
 * @details     This example shows how to generate PWM signal using the Timer, GPTIOE
 *              and the PPI peripherals. The output PWM signal ( P0.21 ) has a frequency
 *              of 1kHz and a 35% duty cycle.
 *
 *              The external 16MHz clock is used to get better results. The microcontroller
 *              is in low power all the time.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        10/November/2017
 * @version     10/November/2017    The ORIGIN
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
    conf_CLK    ();
    conf_GPIO   ();
    conf_GPIOTE ();
    conf_TIMER0 ();
    conf_PPI    ();


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
