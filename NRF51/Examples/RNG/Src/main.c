/**
 * @brief       main.c
 * @details     It sends a random value ( 0 to 255 ) through the UART every time it receives the
 *              character 'm' through the UART.
 *
 *              A different character will be ignored.
 *
 *
 *              This firmware is just an example about how to use the RNG on the nrf51422. The system
 *              will handle everything on the Interrupts ( Low power mode selected ).
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        22/June/2017
 * @version     22/June/2017    The ORIGIN
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
    conf_RNG    ();
    conf_UART   ();


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
