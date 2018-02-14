/**
 * @brief       main.c
 * @details     [TODO].
 *
 *              The microcontroller remains in low power the rest of the time.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/February/2018
 * @version     14/February/2018    The ORIGIN
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
  conf_TIMER0 ();
  

  NRF_TIMER0->TASKS_START  =   1;               // Start Timer0


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


/**
 * @}
 */
