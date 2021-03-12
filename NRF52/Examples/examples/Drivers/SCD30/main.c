/**
 * @brief       main.c
 * @details     [TODO]This example shows how to work with the external device: SCD30. Every 1 seconds, a new
 *              pressure/temperature value is read and the data is transmitted through the UART ( Baud Rate: 230400 ).
 *
 * @details     This example shows how to work with the external device: SCD30. Every 1 seconds, a new
 *              set of values ( CO2 and Resistor ) is measured and the data is transmitted through the UART ( Baud Rate: 230400 ).
 *
 *              The microcontroller is in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        23/January/2021
 * @version     23/January/2021    The ORIGIN
 * @pre         This firmware was tested on the nrf52-DK with Segger Embedded Studio v5.40c ( SDK 14.2.0 ).
 * @warning     The softdevice (s132) is taken into account, Bluetooth was not used although.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */
#include <stdio.h>

#include "nordic_common.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "board.h"
#include "functions.h"
#include "interrupts.h"
#if defined (WORK_FROM_HOME)
#include "D:/Workspaces/Personal/ARM/Drivers/SCD30/SCD30.h" 
#else
#include "D:/vsProjects/ARM/Drivers/SCD30/SCD30.h" 
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


  //I2C_parameters_t      mySCD30_I2C_parameters;
  //SCD30_status_t aux;
  //SCD30_data_t   mySCD30_Data;



  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  

  ///* I2C definition   */
  //mySCD30_I2C_parameters.TWIinstance =    NRF_TWI0;
  //mySCD30_I2C_parameters.SDA         =    TWI0_SDA;
  //mySCD30_I2C_parameters.SCL         =    TWI0_SCL;
  //mySCD30_I2C_parameters.ADDR        =    SCD30_ADDRESS;
  //mySCD30_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K100;
  //mySCD30_I2C_parameters.SDAport     =    NRF_P0;
  //mySCD30_I2C_parameters.SCLport     =    NRF_P0;

  ///* Configure I2C peripheral  */
  //aux  =   SCD30_Init  ( mySCD30_I2C_parameters );

  ///* It triggers the Revision command and gets the result  */
  //aux  =   SCD30_TriggersRevision ( mySCD30_I2C_parameters );
  //nrf_delay_ms (100);
  //aux  =   SCD30_GetRevision ( mySCD30_I2C_parameters, &mySCD30_Data.device );

  ///* It triggers the R0 ( calibration ) command and gets the result  */
  //aux  =   SCD30_TriggersR0 ( mySCD30_I2C_parameters );
  //nrf_delay_ms (100);
  //aux  =   SCD30_GetR0 ( mySCD30_I2C_parameters, &mySCD30_Data.r0_raw, &mySCD30_Data.r0 );
  


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


      ///* Trigger to get a new data value  */
      //aux  =   SCD30_TriggersStatus ( mySCD30_I2C_parameters );
      //nrf_delay_ms (100);

      ///* Get the values: tVOC, CO2_equ and Resistor  */
      //aux  =   SCD30_GetUpdateValues ( mySCD30_I2C_parameters, &mySCD30_Data.status, &mySCD30_Data.values );


      ///* Transmit result through the UART  */
      //sprintf ( (char*)myMessage, "tVOC: %d [ppb], CO2_equ: %d [ppm], R: %d [kOhms]\r\n", (uint32_t)mySCD30_Data.values.tvoc, (uint32_t)mySCD30_Data.values.co2_equ, (uint32_t)mySCD30_Data.values.resistor );

      //NRF_UART0->TASKS_STOPRX  =   1UL;
      //NRF_UART0->TASKS_STOPTX  =   1UL;
      //myPtr                    =   &myMessage[0];

      //NRF_UART0->TASKS_STARTTX =   1UL;
      //NRF_UART0->TXD           =   *myPtr;


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
