/**
 * @brief       main.c
 * @details     It changes the state of the LED1 and LED4 using the RTCs.
 *
 *                  - LED1. RTC0: Tick, Interrupt ON.           Blinks every 125ms.
 *                  - LED4. RTC1: Channel 0, Interrupt ON.      Blinks every 2s.
 *
 *              This firmware is just an example about how to use the RTCs on the NRF51832.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        15/February/2018
 * @version     15/February/2018    The ORIGIN
 * @pre         This firmware was tested on the nrf52-DK with Segger Embedded Studio v3.34
 *              ( SDK 14.2.0 ).
 * @warning     The softdevice (s132) is taken into account, Bluetooth was not used although.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "nordic_common.h"
#include "nrf.h"
#include "variables.h"
#include "functions.h"
#include "interrupts.h"



/**@brief Function for application main entry.
 */
int main(void)
{
  conf_GPIO   ();
  conf_LFCLK  ();
  conf_RTC0   ();
  conf_RTC2   ();

  NRF_RTC0->TASKS_START = 1;    // Start RTC0
  NRF_RTC2->TASKS_START = 1;    // Start RTC1

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


/**
 * @}
 */
