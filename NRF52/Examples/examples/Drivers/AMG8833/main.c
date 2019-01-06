/**
 * @brief       main.c
 * @details     This example shows how to work with the external device: AMG8833. Every 10 seconds, a new
 *              sample is performed and transmitted through the UART ( Baud Rate: 230400 ).
 *
 *              The microcontroller is in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        19/December/2018
 * @version     19/December/2018    The ORIGIN
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
#include "D:/Workspace/ARM/Drivers/AMG8833/AMG8833.h" 
#else
#include "D:/vsProjects/ARM/Drivers/AMG8833/AMG8833.h" 
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

  I2C_parameters_t myAMG8833_I2C_parameters;
  AMG8833_status_t  aux;
  AMG8833_data_t    myAMG8833_Data;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  

  /* I2C definition   */
  myAMG8833_I2C_parameters.TWIinstance =    NRF_TWI0;
  myAMG8833_I2C_parameters.SDA         =    TWI0_SDA;
  myAMG8833_I2C_parameters.SCL         =    TWI0_SCL;
  myAMG8833_I2C_parameters.ADDR        =    AMG8833_ADDRESS_AD_SELECT_VDD;
  myAMG8833_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
  myAMG8833_I2C_parameters.SDAport     =    NRF_P0;
  myAMG8833_I2C_parameters.SCLport     =    NRF_P0;

  /* Configure I2C peripheral  */
  aux  =   AMG8833_Init           ( myAMG8833_I2C_parameters );

  /* Put the device in Normal mode  */
  myAMG8833_Data.operationMode   =   PCTL_NORMAL_MODE;
  aux  =   AMG8833_SetOperationMode ( myAMG8833_I2C_parameters, myAMG8833_Data );
  
  /* Reset the device by software  */
  aux  =   AMG8833_SoftwareReset  ( myAMG8833_I2C_parameters, RST_INITIAL_RESET );
  nrf_delay_ms ( 500 );

  /* Set frame rate: 10 FPSC   */
  aux  =   AMG8833_SetFrameMode     ( myAMG8833_I2C_parameters, FPSC_10FPS );

  /* Set moving average Output Mode: OFF   */
  aux  =   AMG8833_SetAverageOutputMode ( myAMG8833_I2C_parameters, MAMOD_WICE_MOVING_AVERAGE_OUTPUT_MODE_OFF );
  
  /* Clear all flags   */
  aux  =   AMG8833_ClearFlags       ( myAMG8833_I2C_parameters, ( OVT_CLR_THERMISTOR_TEMPERATURE_OVERFLOW_CLEAR_FLAG | OVS_CLR_TEMPERATURE_OVERFLOW_CLEAR_FLAG | INTCLR_INTERRUPT_OUTBREAK_CLEAR_FLAG ) );
  
  /* Resume from reset state  */
  aux  =   AMG8833_SoftwareReset  ( myAMG8833_I2C_parameters, RST_RESUME_FROM_RESET );
  nrf_delay_ms ( 500 );

  /* Put the device in Stand-by ( new data every 10 seconds ) mode  */
  myAMG8833_Data.operationMode   =   PCTL_STANDBY_10SEC_MODE;
  aux  =   AMG8833_SetOperationMode ( myAMG8833_I2C_parameters, myAMG8833_Data );
  
    
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

      /* Get thermistor temperature value  */
      aux  =   AMG8833_GetThermistorValue   ( myAMG8833_I2C_parameters, &myAMG8833_Data );

      /* Get pixel temperature values  */
      aux  =   AMG8833_GetPixelTemperatures ( myAMG8833_I2C_parameters, &myAMG8833_Data );


      /* Transmit result through the UART  */
      sprintf ( (char*)myMessage, "Temp: %d C\r\n", (int32_t)( myAMG8833_Data.termistorOutputValue ) );

      NRF_UART0->TASKS_STOPRX  =   1UL;
      NRF_UART0->TASKS_STOPTX  =   1UL;
      myPtr                    =   &myMessage[0];

      NRF_UART0->TASKS_STARTTX =   1UL;
      NRF_UART0->TXD           =   *myPtr;

      
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
