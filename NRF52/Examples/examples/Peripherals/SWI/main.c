/**
 * @brief       main.c
 * @details     This example shows how the software interrupts work. Every software interrupt
 *              will be linked to one LED.
 *
 *              Every 125ms, the state of the LEDs will change depending on the following:
 *
 *                  - SWI5: Turn on the LED1.
 *                  - SWI1: Turn on the LED2.
 *                  - SWI3: Turn on the LED3.
 *                  - SWI4: Turn on the LED4.
 *
 *              This firmware is just an example about how to use the SWI on the NRF52832.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/April/2018
 * @version     3/April/2018    The ORIGIN
 * @pre         This firmware was tested on the nrf52-DK with Segger Embedded Studio v3.34a
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


/**@brief CONSTANTS.
 */

/**@brief VARIABLES.
 */
uint32_t chooseLEDON   =   LED1_ON;    /*< Variable to choose which LED to turn on   >*/



/**@brief Function for application main entry.
 */
int main(void)
{
  conf_GPIO   ();
  conf_LFCLK  ();
  conf_RTC0   ();
  conf_SWI    ();

  NRF_RTC0->TASKS_START = 1;    // Start RTC0
  
  // NRF_POWER->SYSTEMOFF    = 1;
  NRF_POWER->TASKS_LOWPWR = 1;        // Sub power mode: Low power.

  while( 1 )
  {
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
