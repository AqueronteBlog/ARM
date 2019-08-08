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


/**@brief Function prototypes.
 */
DHT11_status_t myDHT11_SetPinHigh ( uint8_t myDHT11pin                                              );
DHT11_status_t myDHT11_SetPinLow  ( uint8_t myDHT11pin                                              );
DHT11_status_t myDHT11_ReadPin    ( uint8_t myDHT11pin, DHT11_device_bus_status_t* myDHT11pinStatus );
DHT11_status_t myDHT11_Delay_us   ( uint32_t myDHT11delay                                           );




/**@brief Function for application main entry.
 */
int main(void)
{
  uint8_t         myMessage[ TX_BUFF_SIZE ];
  DHT11_comm_t    myDHT11_Dev;
  DHT11_data_t    myDHT11_Data;
  DHT11_status_t  aux;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();
  
  /* DHT11 definition   */
  myDHT11_Dev.pin              =   27UL;
  myDHT11_Dev.dht11_delay_us   =   &myDHT11_Delay_us;
  myDHT11_Dev.dht11_set_high   =   &myDHT11_SetPinHigh;
  myDHT11_Dev.dht11_set_low    =   &myDHT11_SetPinLow;
  myDHT11_Dev.dht11_read_pin   =   &myDHT11_ReadPin;

  aux |=   DHT11_Init ( myDHT11_Dev );



   
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
      
      /* Get a new data  */
      aux |=   DHT11_GetData ( myDHT11_Dev, &myDHT11_Data );
      


      /* Transmit result through the UART  */
      sprintf ( (char*)myMessage, "T = %d C | RH = %d %%\r\n", myDHT11_Data.temperature, myDHT11_Data.humidity );

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





DHT11_status_t myDHT11_Delay_us ( uint32_t myDHT11delay )
{
  /* Delay in us   */
  nrf_delay_us( myDHT11delay );


  return DHT11_SUCCESS;
}



DHT11_status_t myDHT11_SetPinHigh ( uint8_t myDHT11pin )
{
  /* Configure the pin as an output with 'high' output value   */
  NRF_P0->OUTSET              = ( 1UL << myDHT11pin );

  NRF_P0->PIN_CNF[myDHT11pin] = ( GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos   ) |
                                ( GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos ) |
                                ( GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos  ) |
                                ( GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos ) |
                                ( GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos );


  return DHT11_SUCCESS;
}



DHT11_status_t myDHT11_SetPinLow  ( uint8_t myDHT11pin )
{
  /* Configure the pin as an output with 'low' output value   */
  NRF_P0->OUTCLR              = ( 1UL << myDHT11pin );

  NRF_P0->PIN_CNF[myDHT11pin] = ( GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos   ) |
                                ( GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos ) |
                                ( GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos  ) |
                                ( GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos ) |
                                ( GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos );


  return DHT11_SUCCESS;
}



DHT11_status_t myDHT11_ReadPin ( uint8_t myDHT11pin, DHT11_device_bus_status_t* myDHT11pinStatus )
{
  /* Configure the pin as an input   */
  NRF_P0->PIN_CNF[myDHT11pin] = ( GPIO_PIN_CNF_DIR_Input          <<  GPIO_PIN_CNF_DIR_Pos    ) |
                                ( GPIO_PIN_CNF_INPUT_Connect      <<  GPIO_PIN_CNF_INPUT_Pos  ) |
                                ( GPIO_PIN_CNF_PULL_Pullup        <<  GPIO_PIN_CNF_PULL_Pos   ) |
                                ( GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos  ) |
                                ( GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos  );

  /* Get current value of the pin  */
  if ( ( NRF_P0->IN & ( 1UL << myDHT11pin ) ) == ( DHT11_PIN_LOW << myDHT11pin ) )
  {
    *myDHT11pinStatus  =   DHT11_PIN_LOW;
  }
  else
  {
    *myDHT11pinStatus  =   DHT11_PIN_HIGH;
  }



  return DHT11_SUCCESS;
}
/**
 * @}
 */
