/**
 * @brief       main.c
 * @details     [TODO] It changes the state of the LEDs using the Timers.
 *
 *                  - LED1. Timer0: 32-bit, Channel 0, Interrupt ON.    Blinks every 0.125s.
 *                  - LED2. Timer1: 16-bit, Channel 0, Interrupt OFF.   Blinks every 0.25s.
 *                  - LED3. Timer2:  8-bit, Channel 0, Interrupt ON.    Blinks every 0.375s.
 *                  - LED4. Timer0: 32-bit, Channel 1, Interrupt ON.    Blinks every 0.5s.
 *
 *              This firmware is just an example about how to use the timers on the nrf51822. On
 *              polling mode or by Interrupts with different channels.
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
