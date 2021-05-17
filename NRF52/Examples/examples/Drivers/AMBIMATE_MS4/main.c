/**
 * @brief       main.c
 * @details     [TODO]This example shows how to work with the external device: AMBIMATE_MS4. Every 4 seconds, a new
 *              CO2, pressure and temperature values are read and the data is transmitted through the UART ( Baud Rate: 230400 ).
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
#include "D:/Workspaces/Personal/ARM/Drivers/AMBIMATE_MS4/AMBIMATE_MS4.h" 
#else
#include "D:/vsProjects/ARM/Drivers/AMBIMATE_MS4/AMBIMATE_MS4.h" 
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


  I2C_parameters_t  myAMBIMATE_MS4_I2C_parameters;
  AMBIMATE_MS4_status_t    aux;
  AMBIMATE_MS4_data_t      myAMBIMATE_MS4_Data;



  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  

  /* I2C definition   */
  myAMBIMATE_MS4_I2C_parameters.TWIinstance =    NRF_TWI0;
  myAMBIMATE_MS4_I2C_parameters.SDA         =    TWI0_SDA;
  myAMBIMATE_MS4_I2C_parameters.SCL         =    TWI0_SCL;
  myAMBIMATE_MS4_I2C_parameters.ADDR        =    AMBIMATE_MS4_ADDRESS;
  myAMBIMATE_MS4_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K100;
  myAMBIMATE_MS4_I2C_parameters.SDAport     =    NRF_P0;
  myAMBIMATE_MS4_I2C_parameters.SCLport     =    NRF_P0;

  /* Configure I2C peripheral  */
  aux  =   AMBIMATE_MS4_Init  ( myAMBIMATE_MS4_I2C_parameters );



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

      //aux  =   AMBIMATE_MS4_TriggerContinuousMeasurement ( myAMBIMATE_MS4_I2C_parameters, myAMBIMATE_MS4_Data.pressure_compensation );

      ///* Wait for a new data value  */
      //do{
      //  aux  =   AMBIMATE_MS4_GetDataReadyStatus ( myAMBIMATE_MS4_I2C_parameters, &myAMBIMATE_MS4_Data.status );
      //  nrf_delay_ms (100);
      //}while( myAMBIMATE_MS4_Data.status == GET_READY_STATUS_BIT_DATA_NO_READY );

      ///* Get all the values  */
      //aux  =   AMBIMATE_MS4_ReadMeasurement ( myAMBIMATE_MS4_I2C_parameters, &myAMBIMATE_MS4_Data.data );


      ///* Transmit result through the UART  */
      //sprintf ( (char*)myMessage, "CO2: %d ppm, T: %d C, RH: %d %%\r\n", (uint32_t)myAMBIMATE_MS4_Data.data.processed.co2, (uint32_t)myAMBIMATE_MS4_Data.data.processed.temperature, (uint32_t)myAMBIMATE_MS4_Data.data.processed.humidity );

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
