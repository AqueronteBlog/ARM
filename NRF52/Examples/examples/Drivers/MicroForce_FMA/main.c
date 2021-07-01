/**
 * @brief       main.c
 * @details     This example shows how to work with the external device: MicroForce_FMA. Every 1 seconds, a new
 *              force and temperature data are read and the data is transmitted through the UART ( Baud Rate: 230400 ).
 *
 *              The microcontroller is in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        29/June/2021
 * @version     29/June/2021    The ORIGIN
 * @pre         This firmware was tested on the nrf52-DK with Segger Embedded Studio v5.50a ( SDK 14.2.0 ).
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
#include "D:/Workspace/ARM/Drivers/MicroForce_FMA/MicroForce_FMA.h" 
#else
#include "D:/vsProjects/ARM/Drivers/MicroForce_FMA/MicroForce_FMA.h" 
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

  SPI_parameters_t             myMicroForce_FMA_SPI_parameters;
  MicroForce_FMA_status_t      aux;
  MicroForce_FMA_data_t        myMicroForce_FMA_Data;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  

  /* SPI definition   */
  myMicroForce_FMA_SPI_parameters.SPIinstance         =    NRF_SPI0;
  myMicroForce_FMA_SPI_parameters.SPImode             =    SPI_MODE_0;
  myMicroForce_FMA_SPI_parameters.SPIenable_line_mode =    SPI_ENABLE_LINE_LOW;
  myMicroForce_FMA_SPI_parameters.SPIbyte_order       =    SPI_ORDER_MSB_FIRST;
  myMicroForce_FMA_SPI_parameters.MOSI                =    SPI0_MOSI;
  myMicroForce_FMA_SPI_parameters.MISO                =    SPI0_MISO;
  myMicroForce_FMA_SPI_parameters.SCLK                =    SPI0_SCK;
  myMicroForce_FMA_SPI_parameters.CS                  =    SPI0_CS;
  myMicroForce_FMA_SPI_parameters.Freq                =    SPI_FREQUENCY_FREQUENCY_K500;
  myMicroForce_FMA_SPI_parameters.MISOport            =    NRF_GPIO;
  myMicroForce_FMA_SPI_parameters.MOSIport            =    NRF_GPIO;
  myMicroForce_FMA_SPI_parameters.SCLKport            =    NRF_GPIO;
  myMicroForce_FMA_SPI_parameters.CSport              =    NRF_GPIO;

  /* Configure SPI peripheral  */
  aux  =   MicroForce_FMA_Init  ( myMicroForce_FMA_SPI_parameters );


    
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
      
      do{
        /* Get all the data  */
        aux  =   MicroForce_FMA_GetAllRawData ( myMicroForce_FMA_SPI_parameters, &myMicroForce_FMA_Data.status, &myMicroForce_FMA_Data.force.raw_bridge_data, &myMicroForce_FMA_Data.temperature.raw_11bit_temperature );
        nrf_delay_ms(1U);
      }while( myMicroForce_FMA_Data.status.status_bits != MicroForce_FMA_STATUS_BITS_NORMAL_OPERATION );

      /* It processes all the data   */
      myMicroForce_FMA_Data.transfer_function             =  MicroForce_FMA_TRANSFER_FUNCTION_20_TO_80;
      myMicroForce_FMA_Data.force_range                   =  FMA_FORCE_RANGE_15_N;
      myMicroForce_FMA_Data.force.bridge_data             =  MicroForce_FMA_CalculateForce ( myMicroForce_FMA_Data.transfer_function, myMicroForce_FMA_Data.force_range, myMicroForce_FMA_Data.force.raw_bridge_data );
      myMicroForce_FMA_Data.temperature.temperature_data  =  MicroForce_FMA_Calculate11bitTemperature ( myMicroForce_FMA_Data.temperature.raw_11bit_temperature );


      /* Transmit result through the UART  */
      sprintf ( (char*)myMessage, "Force: %d N | Temp: %d C\r\n", (uint32_t)myMicroForce_FMA_Data.force.bridge_data, (uint32_t)myMicroForce_FMA_Data.temperature.temperature_data );

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
