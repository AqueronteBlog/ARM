/**
 * @brief       main.c
 * @details     [TODO].
 *
 *              The rest of the time, the microcontroller is in low power.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        19/February/2018
 * @version     19/February/2018    The ORIGIN
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
    uint8_t myPacket[16] = "TontoElQueLoLea!";


    conf_CLK    ();
    conf_GPIO   ();
    conf_RADIO  ( &myPacket[0] );
    conf_TIMER0 ();



    //NRF_TIMER0->TASKS_START  =   1;                 // Start Timer0

    while( 1 )
    {
        NRF_GPIO->OUTCLR     =   ( 1 << LED1 );


        NRF_RADIO->TASKS_TXEN       =    1;
        while ( ( NRF_RADIO->EVENTS_DISABLED ) == 0 );  // [TODO]       This is DANGEROUS, if something goes wrong, the uC will get stuck here!!!.
                                                        // [WORKAROUND] Insert a counter.
        NRF_RADIO->EVENTS_DISABLED  =    0;

        NRF_GPIO->OUTSET     =   ( 1 << LED1 );

        nrf_delay_ms ( 1000 );


//        //NRF_POWER->SYSTEMOFF = 1;
//        NRF_POWER->TASKS_LOWPWR = 1;                // Sub power mode: Low power.
//
//        // Enter System ON sleep mode
//        __WFE();
//        // Make sure any pending events are cleared
//        __SEV();
//        __WFE();


        //__NOP();
    }
}
