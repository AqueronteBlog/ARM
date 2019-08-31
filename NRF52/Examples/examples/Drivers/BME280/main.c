/**
 * @brief       main.c
 * @details     [TODO]This example shows how to work with the external device: BME280. Every 1 seconds, a new
 *              pressure/temperature/humidity sample is read and the data is transmitted through the UART ( Baud Rate: 230400 ).
 *
 *              The microcontroller is in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        30/August/2019
 * @version     30/August/2019    The ORIGIN
 * @pre         This firmware was tested on the nrf52-DK with Segger Embedded Studio v4.18 ( SDK 14.2.0 ).
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
  uint8_t             myMessage[ TX_BUFF_SIZE ];
  BME280_status_t     aux;
  uint8_t             settings_sel;
  struct bme280_dev   dev;
  struct bme280_data  comp_data;
  int8_t              rslt = BME280_OK;


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

  /* Configure the device in Force mode */
  dev.settings.osr_h  = BME280_OVERSAMPLING_1X;
  dev.settings.osr_p  = BME280_OVERSAMPLING_16X;
  dev.settings.osr_t  = BME280_OVERSAMPLING_2X;
  dev.settings.filter = BME280_FILTER_COEFF_16;

  settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;

  aux  =  bme280_set_sensor_settings(settings_sel, &dev);
  

  
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
      
      /* Trigger a new sample   */
      aux = bme280_set_sensor_mode(BME280_FORCED_MODE, &dev);
      
      /* Wait for the measurement to complete and print data @25Hz */
      dev.delay_ms(40);
      
      /* Get the data  */
      aux = bme280_get_sensor_data(BME280_ALL, &comp_data, &dev);
	
                
      /* Transmit result through the UART  */
      sprintf ( (char*)myMessage, "T: %d C | P: %d Pa | RH: %d %%\r\n", comp_data.temperature, comp_data.pressure, comp_data.humidity );

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
