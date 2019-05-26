/**
 * @brief       main.c
 * @details     [TODO]This example shows how to work with the external device: HTS221. Every 1 seconds, a new
 *              temperature value is read and the data is transmitted through the UART ( Baud Rate: 230400 ).
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
#include "D:/Workspace/ARM/Drivers/HTS221/HTS221.h" 
#else
#include "D:/vsProjects/ARM/Drivers/HTS221/HTS221.h" 
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

  I2C_parameters_t     myHTS221_I2C_parameters;
  HTS221_status_t      aux;
  HTS221_data_t        myHTS221_Data;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  

  /* I2C definition   */
  myHTS221_I2C_parameters.TWIinstance =    NRF_TWI0;
  myHTS221_I2C_parameters.SDA         =    TWI0_SDA;
  myHTS221_I2C_parameters.SCL         =    TWI0_SCL;
  myHTS221_I2C_parameters.ADDR        =    HTS221_ADDRESS;
  myHTS221_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
  myHTS221_I2C_parameters.SDAport     =    NRF_P0;
  myHTS221_I2C_parameters.SCLport     =    NRF_P0;

  /* Configure I2C peripheral  */
  aux  =   HTS221_Init  ( myHTS221_I2C_parameters );

  /* Get device ID  */
  aux  =   HTS221_GetDeviceID ( myHTS221_I2C_parameters, &myHTS221_Data );

  /* Set device in ACTIVE mode  */
  aux  =   HTS221_SetPowerDown ( myHTS221_I2C_parameters, CTRL_REG1_PD_ACTIVE_MODE );

  /* Get calibration coefficients  */
  aux  =   HTS221_GetCalibrationCoefficients ( myHTS221_I2C_parameters, &myHTS221_Data );
  
  /* Set resolution: 16 AVGT, 32 AVGH  */
  myHTS221_Data.temperatureResolution  =   AV_CONF_AVGT_16;
  myHTS221_Data.humidityResolution     =   AV_CONF_AVGH_32;
  aux  =   HTS221_SetResolution ( myHTS221_I2C_parameters, myHTS221_Data );
  
  /* ODR  */
  myHTS221_Data.odr  =   CTRL_REG1_ODR_ONE_SHOT;
  aux  =   HTS221_SetOutputDataRate ( myHTS221_I2C_parameters, myHTS221_Data );

  
  
  
    
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



    if ( myState == 1UL )
    {
      NRF_P0->OUTCLR  |= ( ( 1U << LED1 ) | ( 1U << LED2 ) | ( 1U << LED3 ) | ( 1U << LED4 ) );          // Turn all the LEDs on

      /* Trigger to get a new data value  */
      aux  =   HTS221_SetOneShot ( myHTS221_I2C_parameters );

      /* Wait until there is a new data  */
      do{
        aux  =   HTS221_GetOneShot ( myHTS221_I2C_parameters, &myHTS221_Data );
      }while( myHTS221_Data.one_shot == CTRL_REG2_ONE_SHOT_WAITING );

      
      aux  =   HTS221_GetCalibrationCoefficients ( myHTS221_I2C_parameters, &myHTS221_Data );

      /* Get temperature  */
      aux  =   HTS221_GetTemperature ( myHTS221_I2C_parameters, &myHTS221_Data );

      /* Get humidity  */
      aux  =   HTS221_GetHumidity ( myHTS221_I2C_parameters, &myHTS221_Data );

//      /* Transmit result through the UART  */
//      sprintf ( (char*)myMessage, "T: %d.%d C\r\n", (int32_t)myHTS221_Data.t_a, (int32_t)( ( myHTS221_Data.t_a - (uint32_t)myHTS221_Data.t_a ) * 10000.0f ) );
//
//      NRF_UART0->TASKS_STOPRX  =   1UL;
//      NRF_UART0->TASKS_STOPTX  =   1UL;
//      myPtr                    =   &myMessage[0];
//
//      NRF_UART0->TASKS_STARTTX =   1UL;
//      NRF_UART0->TXD           =   *myPtr;

      
      /* Reset the variables   */
      myState          =   0UL;
      NRF_P0->OUTSET  |=   ( ( 1U << LED1 ) | ( 1U << LED2 ) | ( 1U << LED3 ) | ( 1U << LED4 ) );          // Turn all the LEDs off
    }
    //__NOP();
  }
}
/**
 * @}
 */
