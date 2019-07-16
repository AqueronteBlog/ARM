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




/**@brief Function for application main entry.
 */
int main(void)
{
  WS2812_status_t     aux;
  WS2812_data_t       myWS2812_Data;


  conf_CLK    ();
  conf_GPIO   ();
  conf_TIMER0 ();

  
//  /* I2C definition   */
//  myWS2812_I2C_parameters.TWIinstance =    NRF_TWI0;
//  myWS2812_I2C_parameters.SDA         =    TWI0_SDA;
//  myWS2812_I2C_parameters.SCL         =    TWI0_SCL;
//  myWS2812_I2C_parameters.ADDR        =    WS2812_ADDRESS_1;
//  myWS2812_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
//  myWS2812_I2C_parameters.SDAport     =    NRF_P0;
//  myWS2812_I2C_parameters.SCLport     =    NRF_P0;
//
//  /* Configure I2C peripheral  */
//  aux  =   WS2812_Init  ( myWS2812_I2C_parameters );

  

  
  
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
/**
 * @}
 */
