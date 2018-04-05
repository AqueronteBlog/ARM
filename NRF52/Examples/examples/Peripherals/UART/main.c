/**
 * @brief       main.c
 * @details     [todo]
 *
 *              The CPU remains in low power all the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        5/April/2018
 * @version     5/April/2018    The ORIGIN
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
