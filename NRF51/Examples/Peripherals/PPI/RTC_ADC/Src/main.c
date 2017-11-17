/**
 * @brief       main.c
 * @details     This example shows how to work with the peripherals PPI and ADC. There are
 *              two PPI channels:
 *
 *                  --- Channel0:
 *                       * Event: NRF_RTC1->EVENTS_COMPARE[0].
 *                       * Task:  NRF_ADC->TASKS_START.
 *
 *                  --- Channel 1:
 *                      * Event: NRF_ADC->EVENTS_END.
 *                      * Task:  NRF_GPIOTE->TASKS_OUT[0].
 *
 *              Every 2 seconds, the RTC1 will produce an event making the ADC to perform
 *              a new Battery voltage measurement. When the ADC finishes, the raw data is sent
 *              through the UART.
 *
 *              The LED1 changes its state when there is a new ADC reading while the LED2 indicates
 *              the raw ADC data is transmitted through the UART.
 *
 *              The microcontroller is in low power the rest of the time.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        14/November/2017
 * @version     14/November/2017    The ORIGIN
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
    conf_LFCLK  ();
    conf_GPIO   ();
    conf_GPIOTE ();
    conf_UART   ();
    conf_RTC1   ();
    conf_ADC    ();
    conf_PPI    ();


    NRF_RTC1->TASKS_START  =   1;                   // Start RTC1

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
