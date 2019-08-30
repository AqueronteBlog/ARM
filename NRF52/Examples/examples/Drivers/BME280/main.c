/**
 * @brief       main.c
 * @details     [TODO]This example shows how to work with the external device: BME280. Every 1 seconds, a new
 *              pressure/temperature/wake-up event value is read and the data is transmitted through the UART ( Baud Rate: 230400 ).
 *
 *              The wake-up event is triggered by a double tap.
 *
 *              The microcontroller is in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        30/August/2019
 * @version     30/August/2019    The ORIGIN
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
#include "D:/Workspace/ARM/Drivers/BME280/bme280_port.h" 
#else
#include "D:/vsProjects/ARM/Drivers/BME280/bme280_port.h" 
#endif


/**@brief Constants.
 */
#define TX_BUFF_SIZE  64                              /*!<   UART buffer size                     */


/**@brief Variables.
 */
volatile uint32_t           myState;                  /*!<   State that indicates next action     */
volatile uint8_t            *myPtr;                   /*!<   Pointer to point out myMessage       */
volatile I2C_parameters_t   myBME280_I2C_parameters;  /*!<   I2C configuration                    */




/**@brief Function for application main entry.
 */
int main(void)
{
  uint8_t           myMessage[ TX_BUFF_SIZE ];
  uint8_t           myWakeUpInfo[]  = { "OFF" };
  BME280_status_t   aux;
  struct bme280_dev dev;
  int8_t rslt = BME280_OK;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();
  
  /* I2C definition   */
  myBME280_I2C_parameters.TWIinstance =    NRF_TWI0;
  myBME280_I2C_parameters.SDA         =    TWI0_SDA;
  myBME280_I2C_parameters.SCL         =    TWI0_SCL;
  myBME280_I2C_parameters.ADDR        =    BME280_I2C_ADDR_PRIM;
  myBME280_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
  myBME280_I2C_parameters.SDAport     =    NRF_P0;
  myBME280_I2C_parameters.SCLport     =    NRF_P0;

  /* Configure I2C peripheral  */
  dev.dev_id    =   BME280_I2C_ADDR_PRIM;
  dev.intf      =   BME280_I2C_INTF;
  dev.read      =   user_i2c_read;
  dev.write     =   user_i2c_write;
  dev.delay_ms  =   user_delay_ms;

  aux  =   BME280_Init_I2C  ( myBME280_I2C_parameters );

  
  
  
  myState  =   0UL;                           // Reset the variable
  NRF_TIMER0->TASKS_START  =   1UL;           // Start Timer0

  //NRF_POWER->SYSTEMOFF = 1;
  NRF_POWER->TASKS_LOWPWR  =   1UL;           // Sub power mode: Low power.
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
      
      
		
      /* Transmit result through the UART  */
      //sprintf ( (char*)myMessage, "X: %d mg | Y: %d mg | Z: %d mg | T: %d C | WakeUp: %s\r\n", ( 1000 * sens_data.x ) / myRange, ( 1000 * sens_data.y ) / myRange, ( 1000 * sens_data.z ) / myRange, temp / BMA4_SCALE_TEMP, myWakeUpInfo );

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
