/**
 * @brief       main.c
 * @details     [todo]This example shows how to work with the external device: ADS1015. Every 1 seconds, a new
 *              voltage measurement is performed and the result is transmitted through the UART ( Baud Rate: 230400 ).
 *
 *              The microcontroller is in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        01/August/2019
 * @version     01/August/2019    The ORIGIN
 * @pre         This firmware was tested on the nrf52-DK with Segger Embedded Studio v4.18 ( SDK 14.2.0 ).
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
#include "D:/Workspace/ARM/Drivers/DHT11/DHT11.h" 
#else
#include "D:/vsProjects/ARM/Drivers/DHT11/DHT11.h" 
#endif


/**@brief Constants.
 */
#define TX_BUFF_SIZE  64                              /*!<   UART buffer size                     */


/**@brief Variables.
 */
volatile uint32_t           myState;                  /*!<   State that indicates next action     */
volatile uint8_t            *myPtr;                   /*!<   Pointer to point out myMessage       */



/**@brief Function for application main entry.
 */
int main(void)
{
  uint8_t           myMessage[ TX_BUFF_SIZE ];
  I2C_parameters_t  myDHT11_I2C_parameters;
  DHT11_data_t    myDHT11_Data;
  DHT11_status_t  aux;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();
  
  /* I2C definition   */
  myDHT11_I2C_parameters.TWIinstance =    NRF_TWI0;
  myDHT11_I2C_parameters.SDA         =    TWI0_SDA;
  myDHT11_I2C_parameters.SCL         =    TWI0_SCL;
  myDHT11_I2C_parameters.ADDR        =    DHT11_ADDRESS_GND;
  myDHT11_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
  myDHT11_I2C_parameters.SDAport     =    NRF_P0;
  myDHT11_I2C_parameters.SCLport     =    NRF_P0;

  /* Configure I2C peripheral  */
  myDHT11_Data.device  =   DEVICE_ADS1015;
  aux  =   DHT11_Init  ( myDHT11_I2C_parameters, myDHT11_Data );

  /* Perform a softreset   */
  aux  =   DHT11_SoftReset  ( myDHT11_I2C_parameters );
  nrf_delay_ms ( 500U );

  /* Input multiplexor configuration ( channels ): AINp = AIN0 | AINn = GND  */
  myDHT11_Data.mux  =   CONFIG_MUX_AINP_AIN0_AND_AINN_GND;
  aux  =   DHT11_SetMux  ( myDHT11_I2C_parameters, myDHT11_Data );

  /* Gain: ±4.096V  */
  myDHT11_Data.pga  =   CONFIG_PGA_FSR_4_096_V;
  aux  =   DHT11_SetGain  ( myDHT11_I2C_parameters, myDHT11_Data );

  /* Mode: Single-shot  */
  myDHT11_Data.mode  =   CONFIG_MODE_SINGLE_SHOT;
  aux  =   DHT11_SetMode  ( myDHT11_I2C_parameters, myDHT11_Data );

  /* Data rate: 1600 SPS  */
  myDHT11_Data.dr  =   CONFIG_DR_1600_SPS;
  aux  =   DHT11_SetDataRate  ( myDHT11_I2C_parameters, myDHT11_Data );

  /* Comparator: Disabled  */
  myDHT11_Data.comp_que  =   CONFIG_COMP_QUE_DISABLED;
  aux  =   DHT11_SetComparator  ( myDHT11_I2C_parameters, myDHT11_Data );

   
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
      
      /* Trigger a new conversion  */
      aux  =   DHT11_StartSingleConversion ( myDHT11_I2C_parameters );
      
      /* Wait until the conversion is completed  */
      do{
        aux  =   DHT11_GetOS ( myDHT11_I2C_parameters, &myDHT11_Data );
      }while( ( myDHT11_Data.os & CONFIG_OS_MASK ) == CONFIG_OS_BUSY );       // [TODO] Too dangerous! the uC may get stuck here
                                                                                // [WORKAROUND] Insert a counter.
      /* Get the result  */
      aux  =   DHT11_GetConversion ( myDHT11_I2C_parameters, &myDHT11_Data );


      /* Transmit result through the UART  */
      sprintf ( (char*)myMessage, "V = %d mV\r\n", (int32_t)( 1000 * myDHT11_Data.conversion ) );

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
