/**
 * @brief       main.c
 * @details     This example shows how to work with the internal peripheral PWM. It works on
 *              Up mode with four channels at 4Hz.
 *
 *              Duty Cycle for each channel:
 *                * Channel0: LED1 50% Duty Cycle, LOW Polarity
 *                * Channel1: LED2 50% Duty Cycle, HIGH Polarity
 *                * Channel2: LED3 50% Duty Cycle, LOW Polarity
 *                * Channel3: LED4 50% Duty Cycle, HIGH Polarity
 *
 *              This firmware is just an example about how to use the timers on the NRF52832. The CPU
 *              remains in low power all the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        27/March/2018
 * @version     27/March/2018    The ORIGIN
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
#include "board.h"
#include "functions.h"
#include "interrupts.h"



/**@brief Function for application main entry.
 */
int main(void)
{
  conf_GPIO ();
  conf_PWM0 ();


  //NRF_POWER->SYSTEMOFF = 1;
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
