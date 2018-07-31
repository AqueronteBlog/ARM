/**
 * @brief       main.c
 * @details     [todo]This example shows how to work with the SAADC peripheral by interrupts. Every 2 seconds, a new
 *              VDD sample is performed and transmitted through the UART.
 *
 *              The microcontroller is in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        31/July/2018
 * @version     31/July/2018    The ORIGIN
 * @pre         This firmware was tested on the nrf52-DK with Segger Embedded Studio v3.40
 *              ( SDK 14.2.0 ).
 * @warning     The softdevice (s132) is taken into account, Bluetooth was not used although.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */
#include <stdio.h>

#include "nordic_common.h"
#include "nrf.h"
#include "board.h"
#include "functions.h"
#include "interrupts.h"
#include "D:/Workspace/ARM/Drivers/DS1307/DS1307.h"


/**@brief Constants.
 */
#define TX_BUFF_SIZE  64                          /*!<   UART buffer size                                       */


/**@brief Variables.
 */
volatile uint32_t myState;                        /*!<   State that indicates when to perform an ADC sample     */
volatile uint32_t myADCDoneFlag;                  /*!<   It indicates when a new ADC conversion is ready        */
volatile uint8_t  myMessage[ TX_BUFF_SIZE ];      /*!<   Message to be transmitted through the UART             */
volatile uint8_t  *myPtr;                         /*!<   Pointer to point out myMessage                         */




/**@brief Function for application main entry.
 */
int main(void)
{
  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  

  NRF_TIMER0->TASKS_START  =   1UL;   // Start TIMER0

//  NRF_POWER->SYSTEMOFF = 1UL;
  NRF_POWER->TASKS_LOWPWR = 1UL;      // Sub power mode: Low power.
  while( 1 )
  {
    /* Enter System ON sleep mode  */
    __WFE();
    /* Make sure any pending events are cleared  */
    __SEV();
    __WFE();

    

    if ( myState == 1UL ) 
    {
      NRF_GPIO->OUTCLR   =   ( 1UL << LED1 );

          
      /* Transmit result through the UART  */
      sprintf ( (char*)myMessage, "VDD: %d mV\r\n", (int)( myVDD * 1000.0f ) );

      NRF_UART0->TASKS_STOPRX  =   1UL;
      NRF_UART0->TASKS_STOPTX  =   1UL;
      myPtr                    =   &myMessage[0];

      NRF_UART0->TASKS_STARTTX =   1UL;
      NRF_UART0->TXD           =   *myPtr;


      /* Reset the variables   */
      myState          =   0UL;
      NRF_GPIO->OUTSET =   ( 1UL << LED1 );
    }
  }
}


/**
 * @}
 */
