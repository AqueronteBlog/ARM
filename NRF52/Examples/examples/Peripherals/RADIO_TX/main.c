/**
 * @brief       main.c
 * @details     [TODO] XXX.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        21/February/2018
 * @version     21/February/2018    The ORIGIN
 * @pre         This firmware was tested on the nrf52-DK with Segger Embedded Studio v3.34
 *              ( SDK 14.2.0 ).
 * @warning     The softdevice (s132) is taken into account, Bluetooth was not used although.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "functions.h"
#include "interrupts.h"
#include "nordic_common.h"
#include "nrf.h"
#include "variables.h"
#include "nrf_delay.h"


/**@brief Function for application main entry.
 */
int main(void) {
  uint8_t myPacket[20] = "TontoElQueLoLea!";
  uint8_t myChangePackage = 0;

  conf_CLK    ();
  conf_GPIO   ();
  conf_RADIO  ( &myPacket[0] );

  while (1) {
    NRF_P0->OUTCLR     =   ( 1 << LED1 );


    NRF_RADIO->TASKS_TXEN       =    1;
    while ( ( NRF_RADIO->EVENTS_DISABLED ) == 0 );    // [TODO]       This is DANGEROUS, if something goes wrong, the uC will get stuck here!!!.
                                                      // [WORKAROUND] Insert a counter.
    NRF_RADIO->EVENTS_DISABLED  =    0;

    NRF_P0->OUTSET     =   ( 1 << LED1 );

    nrf_delay_ms ( 1000 );
    
    if ( myChangePackage == 0 )
      {
        myPacket[15]   =   '?';
        myChangePackage    = 1;
      }
      else{
        myPacket[15]   =   '!';
        myChangePackage    = 0;
      }



    /*
      //NRF_POWER->SYSTEMOFF = 1;
      NRF_POWER->TASKS_LOWPWR = 1;        // Sub power mode: Low power.

      // Enter System ON sleep mode
      __WFE();
      // Make sure any pending events are cleared
      __SEV();
      __WFE();
      */
  }
}

/**
 * @}
 */