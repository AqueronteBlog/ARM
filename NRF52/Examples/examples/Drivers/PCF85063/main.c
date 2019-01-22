/**
 * @brief       main.c
 * @details     [TODO]This example shows how to work with the external device: PCF85063. Every 10 seconds, a new
 *              sample is performed and transmitted through the UART ( Baud Rate: 230400 ).
 *
 *              The microcontroller is in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/January/2019
 * @version     22/January/2019    The ORIGIN
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
#include "D:/Workspace/ARM/Drivers/PCF85063/PCF85063.h" 
#else
#include "D:/vsProjects/ARM/Drivers/PCF85063/PCF85063.h" 
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

//  I2C_parameters_t myPCF85063_I2C_parameters;
//  PCF85063_status_t  aux;
//  PCF85063_data_t    myPCF85063_Data;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  

//  /* I2C definition   */
//  myPCF85063_I2C_parameters.TWIinstance =    NRF_TWI0;
//  myPCF85063_I2C_parameters.SDA         =    TWI0_SDA;
//  myPCF85063_I2C_parameters.SCL         =    TWI0_SCL;
//  myPCF85063_I2C_parameters.ADDR        =    PCF85063_ADDRESS_AD_SELECT_VDD;
//  myPCF85063_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
//  myPCF85063_I2C_parameters.SDAport     =    NRF_P0;
//  myPCF85063_I2C_parameters.SCLport     =    NRF_P0;
//
//  /* Configure I2C peripheral  */
//  aux  =   PCF85063_Init           ( myPCF85063_I2C_parameters );
//
//  /* Put the device in Normal mode  */
//  myPCF85063_Data.operationMode   =   PCTL_NORMAL_MODE;
//  aux  =   PCF85063_SetOperationMode ( myPCF85063_I2C_parameters, myPCF85063_Data );
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



    if ( myState == 1UL )
    {
      NRF_P0->OUTCLR  |= ( ( 1U << LED1 ) | ( 1U << LED2 ) | ( 1U << LED3 ) | ( 1U << LED4 ) );          // Turn all the LEDs on

//      /* Get thermistor temperature value  */
//      aux  =   PCF85063_GetThermistorValue   ( myPCF85063_I2C_parameters, &myPCF85063_Data );
//
//      /* Get pixel temperature values  */
//      aux  =   PCF85063_GetPixelTemperatures ( myPCF85063_I2C_parameters, &myPCF85063_Data );
//
//
//      /* Transmit result through the UART  */
//      sprintf ( (char*)myMessage, "Temp: %d C\r\n", (int16_t)( myPCF85063_Data.termistorOutputValue ) );
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
