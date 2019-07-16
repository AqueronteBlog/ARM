/**
 * @brief       main.c
 * @details     This example shows how to work with the external device: BMA456. Every 1 seconds, a new
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
 * @date        29/June/2019
 * @version     29/June/2019    The ORIGIN
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
#include "D:/Workspace/ARM/Drivers/BMA456/bma456_port.h" 
#else
#include "D:/vsProjects/ARM/Drivers/BMA456/bma456_port.h" 
#endif


/**@brief Constants.
 */
#define TX_BUFF_SIZE  64                              /*!<   UART buffer size                     */


/**@brief Variables.
 */
volatile uint32_t           myState;                  /*!<   State that indicates next action     */
volatile uint8_t            *myPtr;                   /*!<   Pointer to point out myMessage       */
volatile I2C_parameters_t   myBMA456_I2C_parameters;  /*!<   I2C configuration                    */




/**@brief Function for application main entry.
 */
int main(void)
{
  uint8_t           myMessage[ TX_BUFF_SIZE ];
  uint8_t           myWakeUpInfo[]  = { "OFF" };
  uint16_t          int_status      = 0U;
  struct bma4_accel sens_data;
  struct bma4_dev   dev;
  uint16_t          rslt            = BMA4_OK;
  uint8_t           init_seq_status = 0U;
  BMA456_status_t   aux;
  int16_t           myRange         = 0;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();
  
  /* I2C definition   */
  myBMA456_I2C_parameters.TWIinstance =    NRF_TWI0;
  myBMA456_I2C_parameters.SDA         =    TWI0_SDA;
  myBMA456_I2C_parameters.SCL         =    TWI0_SCL;
  myBMA456_I2C_parameters.ADDR        =    BMA4_I2C_ADDR_PRIMARY;
  myBMA456_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
  myBMA456_I2C_parameters.SDAport     =    NRF_P0;
  myBMA456_I2C_parameters.SCLport     =    NRF_P0;

  /* Configure I2C peripheral  */
  aux  =   BMA456_Init_I2C  ( myBMA456_I2C_parameters );

  /* Modify the parameters */
  dev.dev_addr        = BMA4_I2C_ADDR_PRIMARY;
  dev.interface       = BMA4_I2C_INTERFACE;
  dev.bus_read        = user_i2c_read;
  dev.bus_write       = user_i2c_write;
  dev.delay           = user_delay_ms;
  dev.read_write_len  = 8;
  dev.resolution      = 16;
  dev.feature_len     = BMA456_FEATURE_SIZE;
  
  /* Softreset   */
  bma4_set_command_register(0xB6, &dev); 
  dev.delay(1);

  /* a. Reading the chip id. */
  rslt = bma456_init(&dev);
  dev.delay(1);

  /* b. Performing initialization sequence. 
   * c. Checking the correct status of the initialization sequence.
   */
  rslt = bma456_write_config_file(&dev);
  dev.delay(1);

  /* Enable the accelerometer */
  bma4_set_accel_enable(BMA4_ENABLE, &dev);
  dev.delay(10);

  /* Declare an accelerometer configuration structure */
  struct bma4_accel_config accel_conf;
	
  /* Assign the desired settings */
  accel_conf.odr        = BMA4_OUTPUT_DATA_RATE_200HZ;
  accel_conf.range      = BMA4_ACCEL_RANGE_4G;
  accel_conf.bandwidth  = BMA4_ACCEL_OSR2_AVG2;
  accel_conf.perf_mode  = BMA4_CIC_AVG_MODE;

  /* Set the configuration */
  rslt = bma4_set_accel_config(&accel_conf, &dev);
  dev.delay(1);

  /* Feature: Doble tap ( wakeup feature ) mapped to INT1 pin */
  rslt = bma4_set_advance_power_save(BMA4_DISABLE, &dev);
  dev.delay(1);

  rslt = bma456_map_interrupt(BMA4_INTR1_MAP, BMA456_WAKEUP_INT, BMA4_ENABLE, &dev);
  dev.delay(1);
  rslt = bma456_wakeup_set_sensitivity(5, &dev);
  dev.delay(1);
  rslt = bma456_tap_selection(0, &dev);
  dev.delay(1);
  rslt = bma456_feature_enable(BMA456_WAKEUP, BMA4_ENABLE, &dev);
  dev.delay(1);
  
  
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
      
      /* Read the sensor data into the sensor data instance */
      rslt = bma4_read_accel_xyz(&sens_data, &dev);

      /* Get temperature   */
      int32_t temp = 0;
      rslt = bma4_get_temperature(&temp, BMA4_DEG, &dev);

      /* Read the Interrupt status reg. */
      rslt = bma456_read_int_status(&int_status, &dev);
      
      /* Check if double tap happened  */
      if ( int_status == BMA456_WAKEUP_INT )
      {
        myWakeUpInfo[0]  =   'O';
        myWakeUpInfo[1]  =   'N';
        myWakeUpInfo[2]  =   ' ';
      }
      else
      {
        myWakeUpInfo[0]  =   'O';
        myWakeUpInfo[1]  =   'F';
        myWakeUpInfo[2]  =   'F';
      }

      /* Get the configuration */
      rslt = bma4_get_accel_config(&accel_conf, &dev);

      /* Get the range   */
      switch ( accel_conf.range )
      {
        case BMA4_ACCEL_RANGE_2G:
          myRange  =   16348;
          break;
        
        default:
        case BMA4_ACCEL_RANGE_4G:
          myRange  =   8192;
          break;

        case BMA4_ACCEL_RANGE_8G:
          myRange  =   4096;
          break;

        case BMA4_ACCEL_RANGE_16G:
          myRange  =   2048;
          break;
      }
		
      /* Transmit result through the UART  */
      sprintf ( (char*)myMessage, "X: %d mg | Y: %d mg | Z: %d mg | T: %d C | WakeUp: %s\r\n", ( 1000 * sens_data.x ) / myRange, ( 1000 * sens_data.y ) / myRange, ( 1000 * sens_data.z ) / myRange, temp / BMA4_SCALE_TEMP, myWakeUpInfo );

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
