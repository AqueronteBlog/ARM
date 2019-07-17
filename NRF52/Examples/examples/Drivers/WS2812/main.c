/**
 * @brief       main.c
 * @details     [TODO]This example shows how to work with the external device: WS2812. Every 1 seconds, a new
 *              pressure/temperature value is read and the data is transmitted through the UART ( Baud Rate: 230400 ).
 *
 *              The microcontroller is in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/July/2019
 * @version     16/July/2019    The ORIGIN
 * @pre         This firmware was tested on the nrf52-DK with Segger Embedded Studio v4.16 ( SDK 14.2.0 ).
 * @warning     The softdevice (s132) is taken into account, Bluetooth was not used although.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */
#include <stdio.h>

#include "nordic_common.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "board.h"
#include "functions.h"
#include "interrupts.h"
#if defined (WORK_FROM_HOME)
#include "D:/Workspace/ARM/Drivers/WS2812/WS2812.h" 
#else
#include "D:/vsProjects/ARM/Drivers/WS2812/WS2812.h" 
#endif


/**@brief Constants.
 */


/**@brief Variables.
 */
volatile uint32_t myState;                        /*!<   State that indicates when to perform an ADC sample     */


/**@brief Function prototypes.
 */
void myDelay_ns ( uint32_t myDelay_ns );          /*!<   User function for Delay                                */




/**@brief Function for application main entry.
 */
int main(void)
{
  WS2812_status_t     aux;
  WS2812_data_t       myWS2812_Data;
  WS2812_com_t        myWS2812_Bus;
  WS2812_parameters_t myWS2812_parameters;


  conf_CLK    ();
  conf_GPIO   ();
  conf_TIMER0 ();


  myWS2812_Bus.delay_ns  = myDelay_ns;

  /* WS2812 platform definition   */
  myWS2812_parameters.DIN      =   27;
  myWS2812_parameters.DINport  =   NRF_P0;

  aux  =   WS2812_Init  ( myWS2812_parameters );
  
  /* WS2812 configuration: 8 RGB LEDs  */
  myWS2812_Data.numberOfLEDs   =   8UL;
  
  /* WS2812 configuration: Fill up the buffer, red colour for all the LEDs  */
  WS2812_num_leds_t   myLEDs[myWS2812_Data.numberOfLEDs];
  for ( uint32_t i = 0UL; i < myWS2812_Data.numberOfLEDs; i++ )
  {
    myLEDs[i].red    =   0xFF;
    myLEDs[i].green  =   0x00;
    myLEDs[i].blue   =   0x00;
  }
  
  
  myState  =   0;                             // Reset the variable
  NRF_TIMER0->TASKS_START  =   1;             // Start Timer0

  //NRF_POWER->SYSTEMOFF = 1;
  NRF_POWER->TASKS_LOWPWR  =   1;             // Sub power mode: Low power.
  while( 1 )
  {
    /* Enter System ON sleep mode   */
    __WFE();
    /* Make sure any pending events are cleared */
    __SEV();
    __WFE();


    /* Proccess new action   */
    if ( myState == 1UL )
    {
      NRF_P0->OUTCLR  |= ( ( 1U << LED1 ) | ( 1U << LED2 ) | ( 1U << LED3 ) | ( 1U << LED4 ) );   // Turn all the LEDs on

      

      /* Reset the variables   */
      myState          =   0UL;
      NRF_P0->OUTSET  |=   ( ( 1U << LED1 ) | ( 1U << LED2 ) | ( 1U << LED3 ) | ( 1U << LED4 ) );  // Turn all the LEDs off
    }
    //__NOP();
  }
}




void myDelay_ns ( uint32_t myDelay_ns )
{
  uint32_t i = 0;

  NRF_TIMER1->TASKS_START = 1;    // Start Timer1

  for ( i = 0; i < myDelay_ns; i++ )
  {
    while ( NRF_TIMER1->EVENTS_COMPARE[0] == 0 );
    NRF_TIMER1->EVENTS_COMPARE[0]    =   0;
  }

  NRF_TIMER1->TASKS_STOP = 1;    // Stop Timer1
}



/**
 * @}
 */
