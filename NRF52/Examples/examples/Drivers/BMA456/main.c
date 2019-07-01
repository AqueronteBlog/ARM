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

//  I2C_parameters_t    myBMA456_I2C_parameters;
//  BMA456_status_t     aux;
//  BMA456_data_t       myBMA456_Data;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  
//  /* I2C definition   */
//  myBMA456_I2C_parameters.TWIinstance =    NRF_TWI0;
//  myBMA456_I2C_parameters.SDA         =    TWI0_SDA;
//  myBMA456_I2C_parameters.SCL         =    TWI0_SCL;
//  myBMA456_I2C_parameters.ADDR        =    BMA456_ADDRESS_1;
//  myBMA456_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
//  myBMA456_I2C_parameters.SDAport     =    NRF_P0;
//  myBMA456_I2C_parameters.SCLport     =    NRF_P0;
//
//  /* Configure I2C peripheral  */
//  aux  =   BMA456_Init  ( myBMA456_I2C_parameters );
//
//  /* Perform a software reset  */
//  aux  =   BMA456_SetSoftwareReset ( myBMA456_I2C_parameters );
//
//  do{
//    aux  =   BMA456_GetSoftwareReset ( myBMA456_I2C_parameters, &myBMA456_Data );      // Dangerous!!! The uC may get stuck here...
//                                                                                          // [WORKAROUND] Insert a counter
//  }while ( myBMA456_Data.swreset == CTRL_REG2_SWRESET_SW_RESET );


  
  
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

//      /* Trigger to get a new data value  */
//      aux  =   BMA456_TriggerOneShot ( myBMA456_I2C_parameters );
//
//      /* Wait until the conversion is done  */
//      do{
//        aux  =   BMA456_GetOneShot ( myBMA456_I2C_parameters, &myBMA456_Data );
//      }while( myBMA456_Data.one_shot == CTRL_REG2_ONE_SHOT_NEW_DATASET );                        // Dangerous!!! The uC may get stuck here...
//                                                                                                  // [WORKAROUND] Insert a counter
//
//      /* Wait until there is a new data ( both pressure and temperature )  */
//      do{
//        aux  =   BMA456_GetStatusRegister ( myBMA456_I2C_parameters, &myBMA456_Data );
//      }while( ( myBMA456_Data.status & ( STATUS_REG_P_DA_MASK | STATUS_REG_T_DA_MASK ) ) != ( STATUS_REG_P_DA_NEW_DATA | STATUS_REG_T_DA_NEW_DATA ) ); // Dangerous!!! The uC may get stuck here...
//                                                                                                                                                        // [WORKAROUND] Insert a counter
//      
//      /* Get pressure  */
//      aux  =   BMA456_GetPressure ( myBMA456_I2C_parameters, &myBMA456_Data );
//
//      /* Get temperature  */
//      aux  =   BMA456_GetTemperature ( myBMA456_I2C_parameters, &myBMA456_Data );
//      
//      
//      /* Transmit result through the UART  */
//      sprintf ( (char*)myMessage, "T: %d.%d C, P: %d.%d mbar\r\n", (int32_t)myBMA456_Data.temperature, (int32_t)( ( myBMA456_Data.temperature - (uint32_t)myBMA456_Data.temperature ) * 10.0f ), 
//                                                                   (int32_t)myBMA456_Data.pressure, (int32_t)( ( myBMA456_Data.pressure - (uint32_t)myBMA456_Data.pressure ) * 10.0f ) );
//
//      NRF_UART0->TASKS_STOPRX  =   1UL;
//      NRF_UART0->TASKS_STOPTX  =   1UL;
//      myPtr                    =   &myMessage[0];
//
//      NRF_UART0->TASKS_STARTTX =   1UL;
//      NRF_UART0->TXD           =   *myPtr;

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
