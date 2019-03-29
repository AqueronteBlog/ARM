/**
 * @brief       main.c
 * @details     [todo]It changes the state of the LEDs using the UARTE.
 *
 *              It will depend on what character the user sends through the UART:
 *                  - '1':  LED1 ON. Message replay: "LED 1 ON".
 *                  - '2':  LED2 ON. Message replay: "LED 2 ON".
 *                  - '3':  LED3 ON. Message replay: "LED 3 ON".
 *                  - '4':  LED4 ON. Message replay: "LED 4 ON".
 *                  - Another character will turn all the LEDs OFF without any message back through the UART.
 *
 *
 *              This firmware is just an example about how to use the UART on the nrf52832. The system
 *              will handle everything on the Interrupts ( Low power mode selected ).
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        25/March/2019
 * @version     25/March/2019    The ORIGIN
 * @pre         This firmware was tested on the nrf52-DK with Segger Embedded Studio v4.12 ( SDK 14.2.0 ).
 * @warning     The softdevice (s132) is taken into account, Bluetooth was not used although.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
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

const uint32_t  NO   = 0UL;             /*!<   Constant to control the UART0                  */
const uint32_t  YES  = 1UL;             /*!<   Constant to control the UART0                  */

/**@brief Variables.
 */
static uint8_t txBuffer[ TX_BUFF_SIZE ];  /*!<   TX buffer to be transmitted through the UART   */
static uint8_t rxBuffer[ TX_BUFF_SIZE ];  /*!<   RX buffer to be received through the UART      */
uint8_t *myPtr;                           /*!<   Pointer to point out myMessage                 */
uint8_t TX_inProgress;                    /*!<   It indicates if a transmission is in progress  */



/**@brief Function for application main entry.
 */
int main(void)
{
  uint32_t TX_dataEnable   =   NO;

  /* Initialized the message  */
  txBuffer[ 0 ]   =  'L';
  txBuffer[ 1 ]   =  'E';
  txBuffer[ 2 ]   =  'D';
  txBuffer[ 3 ]   =  ' ';
  txBuffer[ 4 ]   =  ' ';
  txBuffer[ 5 ]   =  ' ';
  txBuffer[ 6 ]   =  'O';
  txBuffer[ 7 ]   =  'N';
  txBuffer[ 8 ]   =  '\n';

  conf_GPIO   ();
  conf_UARTE  ( &txBuffer[0], 9U, &rxBuffer[0], 1U );


  while( 1UL )
  {
      //NRF_POWER->SYSTEMOFF = 1UL;
      NRF_POWER->TASKS_LOWPWR = 1UL;        // Sub power mode: Low power.

      // Enter System ON sleep mode
      __WFE();
      // Make sure any pending events are cleared
      __SEV();
      __WFE();

      __NOP();


      /* Reset and re-start conditions before evaluating the collected data from UART.   */
      //NRF_UARTE0->TASKS_STOPRX     =   1UL;
      //NRF_UARTE0->TASKS_STOPTX     =   1UL;

      /* Evaluate the data   */
      switch ( rxBuffer[0] )
      {
      /* Character '1': Turn LED1 ON and send a message through the UART   */
      case '1':
          NRF_P0->OUTCLR   =   ( 1UL << LED1 );
          txBuffer [ 4 ]   =   '1';
          TX_dataEnable    =   YES;
          break;

      /* Character '2': Turn LED2 ON and send a message through the UART   */
      case '2':  
          NRF_P0->OUTCLR   =   ( 1UL << LED2 );
          txBuffer [ 4 ]   =   '2';
          TX_dataEnable    =   YES;
          break;

      /* Character '3': Turn LED3 ON and send a message through the UART  */
      case '3':
          NRF_P0->OUTCLR   =   ( 1UL << LED3 );
          txBuffer [ 4 ]   =   '3';
          TX_dataEnable    =   YES;
          break;

      /* Character '4': Turn LED4 ON and send a message through the UART  */
      case '4':
          NRF_P0->OUTCLR   =   ( 1UL << LED4 );
          txBuffer [ 4 ]   =   '4';
          TX_dataEnable    =   YES;
          break;

      /* Turn all LEDs OFF: DO NOT send anything through the UART */
      default:
          for ( uint32_t ii = LED1; ii < ( LED4 + 1 ); ii++ )
              NRF_P0->OUTSET        =   ( 1UL << ii );

          TX_dataEnable                =   NO;
          NRF_UARTE0->TASKS_STARTRX    =   1UL;             // Enable reception from UART
          break;
       }


      /* Send which LED was turned ON back through the UART */
      if ( TX_dataEnable == YES )
      {
          TX_inProgress                =   YES;
          NRF_UARTE0->TASKS_STARTTX    =   1UL;

          /* Wait until the message is transmitted  */
          while ( TX_inProgress == YES ){
             __WFE();
             /* Make sure any pending events are cleared  */
             __SEV();
             __WFE();
          }

          NRF_UARTE0->TASKS_STARTRX    =   1UL;             // Enable reception from UART
      }
  }
}
/**
 * @}
 */
