/**
 * @brief       main.c
 * @details     [TODO]This example shows how to work with the external device: MCP9808. Every 1 seconds, a new
 *              time and date is read from the device and the data is transmitted through the UART ( Baud Rate: 230400 ).
 *
 *              The microcontroller is in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        15/April/2019
 * @version     15/April/2019    The ORIGIN
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
#include "D:/Workspace/ARM/Drivers/MCP9808/MCP9808.h" 
#else
#include "D:/vsProjects/ARM/Drivers/MCP9808/MCP9808.h" 
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

//  I2C_parameters_t   myMCP9808_I2C_parameters;
//  MCP9808_status_t  aux;
//  MCP9808_data_t    myMCP9808_Data;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  

//  /* I2C definition   */
//  myMCP9808_I2C_parameters.TWIinstance =    NRF_TWI0;
//  myMCP9808_I2C_parameters.SDA         =    TWI0_SDA;
//  myMCP9808_I2C_parameters.SCL         =    TWI0_SCL;
//  myMCP9808_I2C_parameters.ADDR        =    MCP9808_ADDRESS;
//  myMCP9808_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
//  myMCP9808_I2C_parameters.SDAport     =    NRF_P0;
//  myMCP9808_I2C_parameters.SCLport     =    NRF_P0;
//
//  /* Configure I2C peripheral  */
//  aux  =   MCP9808_Init           ( myMCP9808_I2C_parameters );
//
//  /* Perform a software reset  */
//  aux  =   MCP9808_SoftwareReset ( myMCP9808_I2C_parameters );
//
//  /* Wait until the oscillator is stable   */
//  do{ 
//    /* Clear Clock integrity flag.  */
//    aux  =   MCP9808_ClearOscillatorClockIntegrityFlag ( myMCP9808_I2C_parameters );
//
//    /* Clear Clock integrity flag.  */
//    aux  =   MCP9808_CheckOscillatorClockIntegrityFlag ( myMCP9808_I2C_parameters, &myMCP9808_Data );
//  }while( myMCP9808_Data.os == SECONDS_OS_CLOCK_INTEGRITY_NOT_GUARANTEED );
//  
//  /* External clock test mode: Normal mode ( no test at all )  */
//  aux  =   MCP9808_SetTestMode ( myMCP9808_I2C_parameters, CONTROL_1_EXT_TEST_NORMAL_MODE );
//
//  /* RTC clock is enabled  */
//  aux  =   MCP9808_SetRTCMode ( myMCP9808_I2C_parameters, CONTROL_1_STOP_RTC_CLOCK_RUNS );
//
//  /* No correction interrupt generated  */
//  aux  =   MCP9808_SetCorrectionInterruptMode ( myMCP9808_I2C_parameters, CONTROL_1_CIE_NO_CORRECTION_INTERRUPT_GENERATED );
//
//  /* 24 hour mode is selected  */
//  myMCP9808_Data.Time12H_24HMode  =   CONTROL_1_12_24_24_HOUR_MODE;
//  aux  =   MCP9808_Set12_24_HourMode ( myMCP9808_I2C_parameters, myMCP9808_Data );

  
    
  myState  =   0;                             /// Reset the variable
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

//      /* Get time  */
//      aux  =   MCP9808_GetTime ( myMCP9808_I2C_parameters, &myMCP9808_Data );
//
//      /* Get day  */
//      aux  =   MCP9808_GetDay ( myMCP9808_I2C_parameters, &myMCP9808_Data );
//
//      /* Get month  */
//      aux  =   MCP9808_GetMonth ( myMCP9808_I2C_parameters, &myMCP9808_Data );
//
//      /* Get weekday  */
//      aux  =   MCP9808_GetWeekday ( myMCP9808_I2C_parameters, &myMCP9808_Data );
//
//      /* Get year  */
//      aux  =   MCP9808_GetYear ( myMCP9808_I2C_parameters, &myMCP9808_Data );
//
//
//      /* Transmit result through the UART  */
//      sprintf ( (char*)myMessage, "Time: %0.2x:%0.2x:%0.2x, Month %x Day %x %s 20%x\r\n", ( ( myMCP9808_Data.BCDtime & 0xFF0000 ) >> 16U ), ( ( myMCP9808_Data.BCDtime & 0x00FF00 ) >> 8U ), 
//                                                              ( myMCP9808_Data.BCDtime & 0x0000FF ), myMCP9808_Data.BCDmonth, myMCP9808_Data.BCDday, MY_WEEK_DAY_STRING[myMCP9808_Data.weekday], myMCP9808_Data.BCDyear );
//
//      NRF_UART0->TASKS_STOPRX  =   1UL;
//      NRF_UART0->TASKS_STOPTX  =   1UL;
//      myPtr                    =   &myMessage[0];
//
//      NRF_UART0->TASKS_STARTTX =   1UL;
//      NRF_UART0->TXD           =   *myPtr;
//
//      
//      /* Reset the variables   */
//      myState          =   0UL;
      NRF_P0->OUTSET  |=   ( ( 1U << LED1 ) | ( 1U << LED2 ) | ( 1U << LED3 ) | ( 1U << LED4 ) );          // Turn all the LEDs off
    }
    //__NOP();
  }
}


/**
 * @}
 */
