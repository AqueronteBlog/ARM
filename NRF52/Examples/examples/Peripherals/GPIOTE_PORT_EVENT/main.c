/**
 * @brief       main.c
 * @details     This shows how to work with the internal peripheral GPIOTE PORT EVENT. 
 *
 *              GPIOTE will be associated with the BTNs to generate an interruption
 *              and change the state of the LEDs.
 *              
 *                BTN1 --> LED1
 *                BTN2 --> LED2
 *                BTN3 --> LED3
 *                BTN4 --> LED4
 *
 *
 *              The microcontroller will remain in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/July/2018
 * @version     3/July/2018    The ORIGIN
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



/**@brief Global Variables.
 */
uint32_t volatile changeLEDsSTATE;       /*!<   0x01 = LED1
                                                0x02 = LED2
                                                0x04 = LED3
                                                0x08 = LED4       */


/**@brief Function for application main entry.
 */
int main(void)
{
  conf_GPIO   ();
  conf_GPIOTE ();
  

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
