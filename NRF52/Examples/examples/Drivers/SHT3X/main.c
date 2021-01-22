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
 * @date        22/May/2019
 * @version     22/May/2019    The ORIGIN
 * @pre         This firmware was tested on the nrf52-DK with Segger Embedded Studio v4.12 ( SDK 14.2.0 ).
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

  I2C_parameters_t     mySHT3X_I2C_parameters;
  SHT3X_status_t      aux;
  //SHT3X_data_t        mySHT3X_Data;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  
  /* I2C definition   */
  mySHT3X_I2C_parameters.TWIinstance =    NRF_TWI0;
  mySHT3X_I2C_parameters.SDA         =    TWI0_SDA;
  mySHT3X_I2C_parameters.SCL         =    TWI0_SCL;
  mySHT3X_I2C_parameters.ADDR        =    SHT3X_ADDRESS;
  mySHT3X_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
  mySHT3X_I2C_parameters.SDAport     =    NRF_P0;
  mySHT3X_I2C_parameters.SCLport     =    NRF_P0;

  /* Configure I2C peripheral  */
  aux  =   SHT3X_Init  ( mySHT3X_I2C_parameters );
  
  ///* Set device in lOW-POWER mode  */
  //aux  =   SHT3X_SetPowerDown ( mySHT3X_I2C_parameters, CTRL_REG1_PD_POWER_DOWN_MODE );

  ///* Get device ID  */
  //aux  =   SHT3X_GetDeviceID ( mySHT3X_I2C_parameters, &mySHT3X_Data );

  
  
  
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
      //aux  =   SHT3X_SetOneShot ( mySHT3X_I2C_parameters );

      ///* Wait until there is a new data  */
      //do{
      //  aux  =   SHT3X_GetOneShot ( mySHT3X_I2C_parameters, &mySHT3X_Data );
      //}while( mySHT3X_Data.one_shot == CTRL_REG2_ONE_SHOT_WAITING );                             // Dangerous!!! The uC may get stuck here...
      //                                                                                            // [WORKAROUND] Insert a counter

      ///* Get temperature  */
      //do{
      //  aux  =   SHT3X_GetTemperatureDataAvailable ( mySHT3X_I2C_parameters, &mySHT3X_Data );
      //}while( mySHT3X_Data.t_da == STATUS_REGISTER_T_DA_DATA_NOT_AVAILABLE );                    // Dangerous!!! The uC may get stuck here...
      //                                                                                            // [WORKAROUND] Insert a counter

      //aux  =   SHT3X_GetTemperature ( mySHT3X_I2C_parameters, &mySHT3X_Data );

      ///* Get humidity  */
      //do{
      //  aux  =   SHT3X_GetHumidityDataAvailable ( mySHT3X_I2C_parameters, &mySHT3X_Data );
      //}while( mySHT3X_Data.h_da == STATUS_REGISTER_H_DA_DATA_NOT_AVAILABLE );                    // Dangerous!!! The uC may get stuck here...
      //                                                                                            // [WORKAROUND] Insert a counter

      //aux  =   SHT3X_GetHumidity ( mySHT3X_I2C_parameters, &mySHT3X_Data );

      ///* Transmit result through the UART  */
      //sprintf ( (char*)myMessage, "T: %d.%d C, RH: %d.%d%%\r\n", (int32_t)mySHT3X_Data.temperature, (int32_t)( ( mySHT3X_Data.temperature - (uint32_t)mySHT3X_Data.temperature ) * 10.0f ), 
      //                                                           (int32_t)mySHT3X_Data.humidity, (int32_t)( ( mySHT3X_Data.humidity - (uint32_t)mySHT3X_Data.humidity ) * 10.0f ) );

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
