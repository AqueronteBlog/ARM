/**
 * @brief       main.c
 * @details     This example shows how to work with the external device: SCD30. Every 4 seconds, a new
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


  I2C_parameters_t  mySCD30_I2C_parameters;
  SCD30_status_t    aux;
  SCD30_data_t      mySCD30_Data;



  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  

  /* I2C definition   */
  mySCD30_I2C_parameters.TWIinstance =    NRF_TWI0;
  mySCD30_I2C_parameters.SDA         =    TWI0_SDA;
  mySCD30_I2C_parameters.SCL         =    TWI0_SCL;
  mySCD30_I2C_parameters.ADDR        =    SCD30_ADDRESS;
  mySCD30_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K100;
  mySCD30_I2C_parameters.SDAport     =    NRF_P0;
  mySCD30_I2C_parameters.SCLport     =    NRF_P0;

  /* Configure I2C peripheral  */
  aux  =   SCD30_Init  ( mySCD30_I2C_parameters );

  /* It performs a software reset  */
  aux  =   SCD30_SoftReset ( mySCD30_I2C_parameters );
  nrf_delay_ms (2000);

  /* It gets the firmware version   */
  aux  =   SCD30_GetFirmwareVersion ( mySCD30_I2C_parameters, &mySCD30_Data.firmware );

  /* It sets two mesurement interval   */
  mySCD30_Data.measurement_interval  =   2U;
  aux  =   SCD30_SetMeasurementInterval ( mySCD30_I2C_parameters, mySCD30_Data.measurement_interval );

  /* It configures the continuous automatic self-calibration   */ 
  mySCD30_Data.asc  =   CONTINUOUS_AUTOMATIC_SELF_CALIBRATION_ASC_ACTIVATE;
  aux  =   SCD30_SetContinuousASC ( mySCD30_I2C_parameters, mySCD30_Data.asc );
  nrf_delay_ms (2000);

  /* It sets the trigger without pressure compensation   */
  mySCD30_Data.pressure_compensation  =   0U;
  aux  =   SCD30_TriggerContinuousMeasurement ( mySCD30_I2C_parameters, mySCD30_Data.pressure_compensation );


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

      aux  =   SCD30_TriggerContinuousMeasurement ( mySCD30_I2C_parameters, mySCD30_Data.pressure_compensation );

      /* Wait for a new data value  */
      do{
        aux  =   SCD30_GetDataReadyStatus ( mySCD30_I2C_parameters, &mySCD30_Data.status );
        nrf_delay_ms (100);
      }while( mySCD30_Data.status == GET_READY_STATUS_BIT_DATA_NO_READY );

      /* Get all the values  */
      aux  =   SCD30_ReadMeasurement ( mySCD30_I2C_parameters, &mySCD30_Data.data );


      /* Transmit result through the UART  */
      sprintf ( (char*)myMessage, "CO2: %d ppm, T: %d C, RH: %d %%\r\n", (uint32_t)mySCD30_Data.data.processed.co2, (uint32_t)mySCD30_Data.data.processed.temperature, (uint32_t)mySCD30_Data.data.processed.humidity );

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
