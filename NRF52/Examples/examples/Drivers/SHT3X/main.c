/**
 * @brief       main.c
 * @details     This example shows how to work with the external device: SHT3X. Every 1 seconds, a new
 *              temperature/humidity value is read and the data is transmitted through the UART ( Baud Rate: 230400 ).
 *
 *              The microcontroller is in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        23/January/2021
 * @version     23/January/2021    The ORIGIN
 * @pre         This firmware was tested on the nrf52-DK with Segger Embedded Studio v5.34 ( SDK 14.2.0 ).
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
#include "C:/Users/mcm/Documents/ARM/Drivers/SHT3X/SHT3X.h" 
#else
#include "D:/vsProjects/ARM/Drivers/SHT3X/SHT3X.h" 
#endif


/**@brief Constants.
 */
#define TX_BUFF_SIZE  64                          /*!<   UART buffer size                                       */


/**@brief Variables.
 */
volatile uint32_t myState;                        /*!<   State that indicates when to perform an ADC sample     */
volatile uint8_t  *myPtr;                         /*!<   Pointer to point out myMessage                         */




/**@brief Function for application main entry.
 */
int main(void)
{
  uint8_t  myMessage[ TX_BUFF_SIZE ];

  I2C_parameters_t  mySHT3X_I2C_parameters;
  SHT3X_status_t    aux;
  SHT3X_data_t      mySHT3X_Data;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  
  /* I2C definition   */
  mySHT3X_I2C_parameters.TWIinstance =    NRF_TWI0;
  mySHT3X_I2C_parameters.SDA         =    TWI0_SDA;
  mySHT3X_I2C_parameters.SCL         =    TWI0_SCL;
  mySHT3X_I2C_parameters.ADDR        =    SHT3X_ADDRESS_A;
  mySHT3X_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
  mySHT3X_I2C_parameters.SDAport     =    NRF_P0;
  mySHT3X_I2C_parameters.SCLport     =    NRF_P0;

  /* Configure I2C peripheral  */
  aux  =   SHT3X_Init  ( mySHT3X_I2C_parameters );
  
  /* Set a software reset  */
  aux  =   SHT3X_SetSoftReset ( mySHT3X_I2C_parameters );
  nrf_delay_ms(2U);

  /* Clear the STATUS register  */
  aux  =   SHT3X_ClearStatus ( mySHT3X_I2C_parameters );

  /* Disable the Heater  */
  aux  =   SHT3X_SetHeater ( mySHT3X_I2C_parameters, SHT3X_HEATER_DISABLE );

  /* Do not perform periodic measurement  */
  aux  =   SHT3X_SetBreakCommand ( mySHT3X_I2C_parameters );
  
  
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

      /* Trigger to get a new data set, no clock stretching and repeatibility high  */
      aux  =   SHT3X_OneShotTriggerAllData ( mySHT3X_I2C_parameters, SHT3X_CLOCK_STRETCHING_DISABLED_REPEATABILITY_HIGH );
      nrf_delay_ms(15U);

      /* Process all the data  */
      SHT3X_ProccessData ( mySHT3X_Data.rawData, &mySHT3X_Data.data );


      /* Transmit result through the UART  */
      sprintf ( (char*)myMessage, "T: %d C, RH: %d %%\r\n", (int32_t)( mySHT3X_Data.data.temperature + 0.5 ), (int32_t)( mySHT3X_Data.data.relativeHumidity + 0.5 ) );

      NRF_UART0->TASKS_STOPRX  =   1UL;
      NRF_UART0->TASKS_STOPTX  =   1UL;
      myPtr                    =   &myMessage[0];

      NRF_UART0->TASKS_STARTTX =   1UL;
      NRF_UART0->TXD           =   *myPtr;

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
