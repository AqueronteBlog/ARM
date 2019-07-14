/**
 * @brief       main.c
 * @details     [todo]This example shows how to work with the external device: BMA456. Every 1 seconds, a new
 *              pressure/temperature value is read and the data is transmitted through the UART ( Baud Rate: 230400 ).
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
#include "D:/Workspace/ARM/Drivers/BMA456/BMA456.h" 
#else
#include "D:/vsProjects/ARM/Drivers/BMA456/BMA456.h" 
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

  I2C_parameters_t    myBMA456_I2C_parameters;
  BMA456_status_t     aux;
  BMA456_data_t       myBMA456_Data;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  
  /* I2C definition   */
  myBMA456_I2C_parameters.TWIinstance =    NRF_TWI0;
  myBMA456_I2C_parameters.SDA         =    TWI0_SDA;
  myBMA456_I2C_parameters.SCL         =    TWI0_SCL;
  myBMA456_I2C_parameters.ADDR        =    BMA456_ADDRESS_SDO_GND;
  myBMA456_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
  myBMA456_I2C_parameters.SDAport     =    NRF_P0;
  myBMA456_I2C_parameters.SCLport     =    NRF_P0;

  /* Configure I2C peripheral  */
  aux  =   BMA456_Init  ( myBMA456_I2C_parameters );

  /* Check that the device is not in Fatal error state ( Boot, powersystem )   */
  do{
    aux  =   BMA456_GetSensorErrorConditions ( myBMA456_I2C_parameters, &myBMA456_Data );   
  }while( myBMA456_Data.fatal_err == ERR_REG_FATAL_ERR_ERROR );                               // Dangerous!!! The uC may get stuck here...
                                                                                              // [WORKAROUND] Insert a counter
  /* Trigger a softreset  */
  myBMA456_Data.cmd  =   CMD_CMD_SOFTRESET;
  aux  =   BMA456_SetCMD  ( myBMA456_I2C_parameters, myBMA456_Data );

  /* Check that the device is not in Fatal error state ( Boot, powersystem )   */
  do{
    aux  =   BMA456_GetSensorErrorConditions ( myBMA456_I2C_parameters, &myBMA456_Data );   
  }while( myBMA456_Data.fatal_err == ERR_REG_FATAL_ERR_ERROR );                               // Dangerous!!! The uC may get stuck here...
                                                                                              // [WORKAROUND] Insert a counter                                                                                    
  
  /* Read event to make sure there was a POR detected  */
  do{
    aux  =   BMA456_GetEvent ( myBMA456_I2C_parameters, &myBMA456_Data );   
  }while( myBMA456_Data.por_detected == EVENT_POR_DETECTED_HIGH );                            // Dangerous!!! The uC may get stuck here...
                                                                                              // [WORKAROUND] Insert a counter  
  /* Accelerometer disabled, Auxiliary sensor disabled  */
  myBMA456_Data.acc_en   =   PWR_CTRL_ACC_EN_ACC_OFF;
  myBMA456_Data.aux_en   =   PWR_CTRL_AUX_EN_MAG_OFF;
  aux  =   BMA456_SetPWR_Ctrl ( myBMA456_I2C_parameters, myBMA456_Data );
  nrf_delay_ms ( 1UL );

  /* Get the ID  */
  aux  =   BMA456_GetID ( myBMA456_I2C_parameters, &myBMA456_Data );
  
  /* Accelerometer. Range: +/- 16g  */
  myBMA456_Data.acc_range   =   ACC_RANGE_ACC_RANGE_RANGE_16G;
  aux  =   BMA456_SetAccRange ( myBMA456_I2C_parameters, myBMA456_Data );
  nrf_delay_ms ( 1UL );

  /* Accelerometer. Bandwidth: Average 2 samples | ODR: 50Hz | Filter performance: Average mode  */
  myBMA456_Data.acc_bwp        =   ACC_CONF_ACC_BWP_OSR2_AVG2;
  myBMA456_Data.acc_odr        =   ACC_CONF_ACC_ODR_ODR_50;
  myBMA456_Data.acc_perf_mode  =   ACC_CONF_ACC_PERF_MODE_CIC_AVG;
  aux  =   BMA456_SetAccConf ( myBMA456_I2C_parameters, myBMA456_Data );
  nrf_delay_ms ( 1UL );

  /* Accelerometer. Advanced power mode enabled  */
  myBMA456_Data.adv_power_save   =   PWR_CONF_ADV_POWER_SAVE_APS_ON;
  aux  =   BMA456_SetPWR_Conf ( myBMA456_I2C_parameters, myBMA456_Data );
  nrf_delay_ms ( 1UL );

  /* Check that there is not any error after configuring ACC_CONF   */
  do{
    aux  =   BMA456_GetSensorErrorConditions ( myBMA456_I2C_parameters, &myBMA456_Data );   
  }while( myBMA456_Data.error_code == ERR_REG_ERROR_CODE_ACC_ERR );                           // Dangerous!!! The uC may get stuck here...
                                                                                              // [WORKAROUND] Insert a counter 
  /* Accelerometer enabled, Auxiliary sensor disabled  */
  myBMA456_Data.acc_en   =   PWR_CTRL_ACC_EN_ACC_ON;
  myBMA456_Data.aux_en   =   PWR_CTRL_AUX_EN_MAG_OFF;
  aux  =   BMA456_SetPWR_Ctrl ( myBMA456_I2C_parameters, myBMA456_Data );
  nrf_delay_ms ( 1UL );

  

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
      
      aux  =   BMA456_GetTemperature ( myBMA456_I2C_parameters, &myBMA456_Data );

      /* Wait until there is a new data ready for accelerometer  */
      do{
        aux  =   BMA456_GetSensorStatusFlags ( myBMA456_I2C_parameters, &myBMA456_Data );
      }while( myBMA456_Data.drdy_acc == STATUS_DRDY_ACC_DATA_NO_READY );                    // Dangerous!!! The uC may get stuck here...
                                                                                            // [WORKAROUND] Insert a counter 
      /* Get the acceleration data from the device   */
      aux  =   BMA456_GetAccData ( myBMA456_I2C_parameters, &myBMA456_Data );


      /* Transmit result through the UART  */
      sprintf ( (char*)myMessage, "X: %d mg | Y: %d mg | Z: %d mg | T: %d C\r\n", (int16_t)( myBMA456_Data.acc_x * 1000.0 ), (int16_t)( myBMA456_Data.acc_y * 1000.0 ), (int16_t)( myBMA456_Data.acc_z * 1000.0 ), myBMA456_Data.temperature );

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
