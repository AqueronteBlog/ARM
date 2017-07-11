/**
 * @brief       main.c
 * @details     [todo] It reads the internal temperature sensor every one second and send the data ( LSB first )
 *              through the UART.
 *
 *              The LED1 will be turned on when the process begins ( reading internal temperature ) and be
 *              turned off when the process finishes ( all the data is sent through the UART ).
 *
 *              This firmware is just an example about how to read the internal temperature sensor on the nrf51422. The system
 *              will handle everything on the Interruptions ( Low power mode selected ).
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        11/July/2017    The ORIGIN
 * @version     11/July/2017    The ORIGIN
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
    conf_UART   ();
    conf_ADC    ();
    conf_TIMER0 ();


    NRF_TIMER0->TASKS_START = 1;    // Start Timer0

    while( 1 )
    {
        //NRF_POWER->SYSTEMOFF = 1;
        NRF_POWER->TASKS_LOWPWR = 1;        // Sub power mode: Low power.

        // Enter System ON sleep mode
		__WFE();
		// Make sure any pending events are cleared
		__SEV();
		__WFE();

        __NOP();
    }
}
