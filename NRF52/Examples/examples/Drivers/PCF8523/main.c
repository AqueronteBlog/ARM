/**
 * @brief       main.c
 * @details     [TODO]This example shows how to work with the external device: PCF8523. Every 1 seconds, a new
 *              time and date is read from the device and the data is transmitted through the UART ( Baud Rate: 230400 ).
 *
 *              The microcontroller is in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021    The ORIGIN
 * @pre         This firmware was tested on the nrf52-DK with Segger Embedded Studio v5.34 ( SDK 14.2.0 ).
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
#include "C:/Users/mcm/Documents/ARM/Drivers/PCF8523/PCF8523.h" 
#else
#include "D:/vsProjects/ARM/Drivers/PCF8523/PCF8523.h" 
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
  static const char* MY_WEEK_DAY_STRING[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

  uint8_t  myMessage[ TX_BUFF_SIZE ];

  I2C_parameters_t   myPCF8523_I2C_parameters;
  PCF8523_status_t  aux;
  PCF8523_data_t    myPCF8523_Data;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  

  /* I2C definition   */
  myPCF8523_I2C_parameters.TWIinstance =    NRF_TWI0;
  myPCF8523_I2C_parameters.SDA         =    TWI0_SDA;
  myPCF8523_I2C_parameters.SCL         =    TWI0_SCL;
  myPCF8523_I2C_parameters.ADDR        =    PCF8523_ADDRESS;
  myPCF8523_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
  myPCF8523_I2C_parameters.SDAport     =    NRF_P0;
  myPCF8523_I2C_parameters.SCLport     =    NRF_P0;

  /* Configure I2C peripheral  */
  aux  =   PCF8523_Init           ( myPCF8523_I2C_parameters );

  /* Perform a software reset  */
  aux  =   PCF8523_SoftwareReset ( myPCF8523_I2C_parameters );

  /* Wait until the oscillator is stable   */
  do{ 
    aux  =   PCF8523_GetClockIntegrityFlag ( myPCF8523_I2C_parameters, &myPCF8523_Data.os );
  }while( myPCF8523_Data.os == SECONDS_OS_CLOCK_INTEGRITY_NOT_GUARANTEED );
  
  /* RTC clock is enabled  */
  aux  =   PCF8523_SetRTCMode ( myPCF8523_I2C_parameters, CONTROL_1_STOP_RTC_CLOCK_RUNS );

  /* No correction interrupt generated  */
  aux  =   PCF8523_SetCorrectionInterruptMode ( myPCF8523_I2C_parameters, CONTROL_1_CIE_NO_CORRECTION_INTERRUPT_GENERATED );

  /* 24 hour mode is selected  */
  myPCF8523_Data.time.hourMode  =   CONTROL_1_12_24_MODE_24_HOUR;
  aux  =   PCF8523_SetHourMode ( myPCF8523_I2C_parameters, myPCF8523_Data.time.hourMode );

  /* Internal oscillator capacitor selection: 7 pF  */
  aux  =   PCF8523_SetInternalOscillatorCapacitor ( myPCF8523_I2C_parameters, CONTROL_1_CAP_SEL_7_PF );

  /* Normal mode offset at 0.  */
  myPCF8523_Data.offset.mode  = OFFSET_MODE_ONCE_EVERY_TWO_HOURS;
  myPCF8523_Data.offset.value = 0U;
  aux  =   PCF8523_SetOffset ( myPCF8523_I2C_parameters, myPCF8523_Data.offset );

  /* Get day. After reset, we expect to get 0x01  */
  aux  =   PCF8523_GetDay ( myPCF8523_I2C_parameters, &myPCF8523_Data.date.day );

  /* Set day: 23  */
  myPCF8523_Data.date.day   =   0x23;
  aux  =   PCF8523_SetDay ( myPCF8523_I2C_parameters, myPCF8523_Data.date.day );

  /* Get month. After reset, we expect to get 0x01 ( January )  */
  aux  =   PCF8523_GetMonth ( myPCF8523_I2C_parameters, &myPCF8523_Data.date.month );

  /* Set month: September  */
  myPCF8523_Data.date.month   =   MONTHS_MONTHS_SEPTEMBER;
  aux  =   PCF8523_SetMonth ( myPCF8523_I2C_parameters, myPCF8523_Data.date.month );

  /* Get weekday. After reset, we expect to get Saturday  */
  aux  =   PCF8523_GetWeekday ( myPCF8523_I2C_parameters, &myPCF8523_Data.date.weekday );

  /* Set weekday: Friday  */
  myPCF8523_Data.date.weekday   =   WEEKDAYS_WEEKDAYS_FRIDAY;
  aux  =   PCF8523_SetWeekday ( myPCF8523_I2C_parameters, myPCF8523_Data.date.weekday );

  /* Get year. After reset, we expect to get 00 ( it corresponds to 2000 )  */
  aux  =   PCF8523_GetYear ( myPCF8523_I2C_parameters, &myPCF8523_Data.date.year );

  /* Set year: 21 ( 2021 )  */
  myPCF8523_Data.date.year   =   0x21;
  aux  =   PCF8523_SetYear ( myPCF8523_I2C_parameters, myPCF8523_Data.date.year );

  /* Set time: 235955 ( 23:59:55 )  */
  myPCF8523_Data.time.bcd       =   0x235955;
  myPCF8523_Data.time.hourMode  =   CONTROL_1_12_24_MODE_24_HOUR;
  aux  =   PCF8523_SetTime ( myPCF8523_I2C_parameters, myPCF8523_Data.time );
  
  
    
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

      /* Get time  */
      aux  =   PCF8523_GetTime ( myPCF8523_I2C_parameters, &myPCF8523_Data.time );

      /* Get day  */
      aux  =   PCF8523_GetDay ( myPCF8523_I2C_parameters, &myPCF8523_Data.date.day );

      /* Get month  */
      aux  =   PCF8523_GetMonth ( myPCF8523_I2C_parameters, &myPCF8523_Data.date.month );

      /* Get weekday  */
      aux  =   PCF8523_GetWeekday ( myPCF8523_I2C_parameters, &myPCF8523_Data.date.weekday );

      /* Get year  */
      aux  =   PCF8523_GetYear ( myPCF8523_I2C_parameters, &myPCF8523_Data.date.year );


      /* Transmit result through the UART  */
      sprintf ( (char*)myMessage, "Time: %0.2x:%0.2x:%0.2x, Month %x Day %x %s 20%x\r\n", ( ( myPCF8523_Data.time.bcd & 0xFF0000 ) >> 16U ), ( ( myPCF8523_Data.time.bcd & 0x00FF00 ) >> 8U ), 
                                                              ( myPCF8523_Data.time.bcd & 0x0000FF ), myPCF8523_Data.date.month, myPCF8523_Data.date.day, MY_WEEK_DAY_STRING[myPCF8523_Data.date.weekday], myPCF8523_Data.date.year );

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
