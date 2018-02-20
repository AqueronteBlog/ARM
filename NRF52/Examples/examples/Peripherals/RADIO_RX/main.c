/**
 * @brief       main.c
 * @details     [TODO] XXX.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        20/February/2018
 * @version     20/February/2018    The ORIGIN
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

/**@brief Function for application main entry.
 */
int main(void) {
  uint8_t myPacket[16] = {0};
  uint8_t myLEDS_state = 0;

  conf_CLK();
  conf_GPIO();
  conf_RADIO(&myPacket[0]);

  while (1) {
    NRF_RADIO->TASKS_RXEN = 1;
    while (NRF_RADIO->EVENTS_DISABLED == 0)
      ;
    NRF_RADIO->EVENTS_DISABLED = 0;



    if (NRF_RADIO->EVENTS_CRCOK == 1) {
      if ( myLEDS_state == 0 )
      {
        NRF_P0->OUTCLR  = ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );
        myLEDS_state    = 1;
      }
      else{
        NRF_P0->OUTSET  = ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );
        myLEDS_state    = 0;
      }

      NRF_RADIO->EVENTS_CRCOK = 0;
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