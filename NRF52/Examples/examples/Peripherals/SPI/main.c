/**
 * @brief       main.c
 * @details     This firmware shows how to work with two peripherals: SPI ( Master )
 *              and SPIS ( Slave ). Every one second, the Master sends one byte to the
 *              Slave. It depends on the data transmitted by the Master, the Slave will
 *              answer with a different byte.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/March/2018
 * @version     10/March/2018    The ORIGIN
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



/**@brief Function for application main entry.
 */
int main(void)
{
  conf_GPIO   ();
  conf_SPI0   ();
  conf_SPIS1  ();
  conf_TIMER0 ();

  NRF_TIMER0->TASKS_START = 1;            // Start Timer0


  while( 1 )
  {
      //NRF_POWER->SYSTEMOFF = 1;
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
