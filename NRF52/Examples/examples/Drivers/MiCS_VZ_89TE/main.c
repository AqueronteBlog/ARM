/**
 * @brief       main.c
 * @details     This example shows how to work with the external device: MICS_VZ_89TE. Every 1 seconds, a new
 *              set of values ( tVOC, CO2_equ and Resistor ) is measured and the data is transmitted through the UART ( Baud Rate: 230400 ).
 *
 *              The microcontroller is in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        26/January/2021
 * @version     26/January/2021    The ORIGIN
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
#include "D:/Workspaces/Personal/ARM/Drivers/MiCS_VZ_89TE/MICS_VZ_89TE.h" 
#else
#include "D:/vsProjects/ARM/Drivers/MICS_VZ_89TE/MICS_VZ_89TE.h" 
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

  I2C_parameters_t      myMICS_VZ_89TE_I2C_parameters;
  MICS_VZ_89TE_status_t aux;
  MICS_VZ_89TE_data_t   myMICS_VZ_89TE_Data;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  
  /* I2C definition   */
  myMICS_VZ_89TE_I2C_parameters.TWIinstance =    NRF_TWI0;
  myMICS_VZ_89TE_I2C_parameters.SDA         =    TWI0_SDA;
  myMICS_VZ_89TE_I2C_parameters.SCL         =    TWI0_SCL;
  myMICS_VZ_89TE_I2C_parameters.ADDR        =    MICS_VZ_89TE_ADDRESS;
  myMICS_VZ_89TE_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K100;
  myMICS_VZ_89TE_I2C_parameters.SDAport     =    NRF_P0;
  myMICS_VZ_89TE_I2C_parameters.SCLport     =    NRF_P0;

  /* Configure I2C peripheral  */
  aux  =   MICS_VZ_89TE_Init  ( myMICS_VZ_89TE_I2C_parameters );

  /* It triggers the Revision command and gets the result  */
  aux  =   MICS_VZ_89TE_TriggersRevision ( myMICS_VZ_89TE_I2C_parameters );
  nrf_delay_ms (100);
  aux  =   MICS_VZ_89TE_GetRevision ( myMICS_VZ_89TE_I2C_parameters, &myMICS_VZ_89TE_Data.device );

  /* It triggers the R0 ( calibration ) command and gets the result  */
  aux  =   MICS_VZ_89TE_TriggersR0 ( myMICS_VZ_89TE_I2C_parameters );
  nrf_delay_ms (100);
  aux  =   MICS_VZ_89TE_GetR0 ( myMICS_VZ_89TE_I2C_parameters, &myMICS_VZ_89TE_Data.r0_raw, &myMICS_VZ_89TE_Data.r0 );
  



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

      /* Trigger to get a new data value  */
      aux  =   MICS_VZ_89TE_TriggersStatus ( myMICS_VZ_89TE_I2C_parameters );
      nrf_delay_ms (100);

      /* Get the values: tVOC, CO2_equ and Resistor  */
      aux  =   MICS_VZ_89TE_GetUpdateValues ( myMICS_VZ_89TE_I2C_parameters, &myMICS_VZ_89TE_Data.status, &myMICS_VZ_89TE_Data.values );


      /* Transmit result through the UART  */
      sprintf ( (char*)myMessage, "tVOC: %d [ppb], CO2_equ: %d [ppm], R: %d [kOhms]\r\n", (uint32_t)myMICS_VZ_89TE_Data.values.tvoc, (uint32_t)myMICS_VZ_89TE_Data.values.co2_equ, (uint32_t)myMICS_VZ_89TE_Data.values.resistor );

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
