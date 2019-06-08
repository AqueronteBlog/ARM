/**
 * @brief       main.c
 * @details     [todo]This example shows how to work with the external device: LPS25HB. Every 1 seconds, a new
 *              temperature/humidity value is read and the data is transmitted through the UART ( Baud Rate: 230400 ).
 *
 *              The microcontroller is in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        08/June/2019
 * @version     08/June/2019    The ORIGIN
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
#include "D:/Workspace/ARM/Drivers/LPS25HB/LPS25HB.h" 
#else
#include "D:/vsProjects/ARM/Drivers/LPS25HB/LPS25HB.h" 
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

//  I2C_parameters_t     myLPS25HB_I2C_parameters;
//  LPS25HB_status_t     aux;
//  LPS25HB_data_t       myLPS25HB_Data;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

//  
//  /* I2C definition   */
//  myLPS25HB_I2C_parameters.TWIinstance =    NRF_TWI0;
//  myLPS25HB_I2C_parameters.SDA         =    TWI0_SDA;
//  myLPS25HB_I2C_parameters.SCL         =    TWI0_SCL;
//  myLPS25HB_I2C_parameters.ADDR        =    LPS25HB_ADDRESS;
//  myLPS25HB_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
//  myLPS25HB_I2C_parameters.SDAport     =    NRF_P0;
//  myLPS25HB_I2C_parameters.SCLport     =    NRF_P0;
//
//  /* Configure I2C peripheral  */
//  aux  =   LPS25HB_Init  ( myLPS25HB_I2C_parameters );
//  
//  /* Set device in lOW-POWER mode  */
//  aux  =   LPS25HB_SetPowerDown ( myLPS25HB_I2C_parameters, CTRL_REG1_PD_POWER_DOWN_MODE );
//
//  /* Get device ID  */
//  aux  =   LPS25HB_GetDeviceID ( myLPS25HB_I2C_parameters, &myLPS25HB_Data );
//



  
  
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
//
//      /* Trigger to get a new data value  */
//      aux  =   LPS25HB_SetOneShot ( myLPS25HB_I2C_parameters );
//
//      /* Wait until there is a new data  */
//      do{
//        aux  =   LPS25HB_GetOneShot ( myLPS25HB_I2C_parameters, &myLPS25HB_Data );
//      }while( myLPS25HB_Data.one_shot == CTRL_REG2_ONE_SHOT_WAITING );                             // Dangerous!!! The uC may get stuck here...
//                                                                                                  // [WORKAROUND] Insert a counter
//
//      /* Transmit result through the UART  */
//      sprintf ( (char*)myMessage, "T: %d.%d C, RH: %d.%d%%\r\n", (int32_t)myLPS25HB_Data.temperature, (int32_t)( ( myLPS25HB_Data.temperature - (uint32_t)myLPS25HB_Data.temperature ) * 10.0f ), 
//                                                                 (int32_t)myLPS25HB_Data.humidity, (int32_t)( ( myLPS25HB_Data.humidity - (uint32_t)myLPS25HB_Data.humidity ) * 10.0f ) );
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
