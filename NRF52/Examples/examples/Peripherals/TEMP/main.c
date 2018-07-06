/**
 * @brief       main.c
 * @details     [todo]
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        6/July/2018
 * @version     6/July/2018    The ORIGIN
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


/**@brief Constants.
 */
#define TX_BUFF_SIZE  32                /*!<   UART buffer size                               */


/**@brief Variables.
 */
uint8_t myMessage[ TX_BUFF_SIZE ];      /*!<   Message to be transmitted through the UART     */
uint8_t *myPtr;                         /*!<   Pointer to point out myMessage                 */



/**@brief Function for application main entry.
 */
int main(void)
{
  conf_GPIO   ();
  conf_UART0  ();

//  NRF_POWER->SYSTEMOFF = 1;
  NRF_POWER->TASKS_LOWPWR = 1;        // Sub power mode: Low power.
  while( 1 )
  {
    // Enter System ON sleep mode
    __WFE();
    // Make sure any pending events are cleared
    __SEV();
    __WFE();


    // Reset and re-start conditions before evaluating the collected data from UART.
    NRF_UART0->TASKS_STOPRX      =   1;
    NRF_UART0->TASKS_STOPTX      =   1;
    myPtr                        =   &myMessage[0];

    NRF_UART0->TASKS_STARTTX     =   1;
    NRF_UART0->TXD               =   *myPtr;

  }
}


/**
 * @}
 */
