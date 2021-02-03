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

  //I2C_parameters_t   myPCF8523_I2C_parameters;
  //PCF8523_status_t  aux;
  //PCF8523_data_t    myPCF8523_Data;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  

  ///* I2C definition   */
  //myPCF8523_I2C_parameters.TWIinstance =    NRF_TWI0;
  //myPCF8523_I2C_parameters.SDA         =    TWI0_SDA;
  //myPCF8523_I2C_parameters.SCL         =    TWI0_SCL;
  //myPCF8523_I2C_parameters.ADDR        =    PCF8523_ADDRESS;
  //myPCF8523_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
  //myPCF8523_I2C_parameters.SDAport     =    NRF_P0;
  //myPCF8523_I2C_parameters.SCLport     =    NRF_P0;

  ///* Configure I2C peripheral  */
  //aux  =   PCF8523_Init           ( myPCF8523_I2C_parameters );

  ///* Perform a software reset  */
  //aux  =   PCF8523_SoftwareReset ( myPCF8523_I2C_parameters );

  ///* Wait until the oscillator is stable   */
  //do{ 
  //  /* Clear Clock integrity flag.  */
  //  aux  =   PCF8523_ClearOscillatorClockIntegrityFlag ( myPCF8523_I2C_parameters );

  //  /* Clear Clock integrity flag.  */
  //  aux  =   PCF8523_CheckOscillatorClockIntegrityFlag ( myPCF8523_I2C_parameters, &myPCF8523_Data );
  //}while( myPCF8523_Data.os == SECONDS_OS_CLOCK_INTEGRITY_NOT_GUARANTEED );
  
  ///* External clock test mode: Normal mode ( no test at all )  */
  //aux  =   PCF8523_SetTestMode ( myPCF8523_I2C_parameters, CONTROL_1_EXT_TEST_NORMAL_MODE );

  ///* RTC clock is enabled  */
  //aux  =   PCF8523_SetRTCMode ( myPCF8523_I2C_parameters, CONTROL_1_STOP_RTC_CLOCK_RUNS );

  ///* No correction interrupt generated  */
  //aux  =   PCF8523_SetCorrectionInterruptMode ( myPCF8523_I2C_parameters, CONTROL_1_CIE_NO_CORRECTION_INTERRUPT_GENERATED );

  ///* 24 hour mode is selected  */
  //myPCF8523_Data.Time12H_24HMode  =   CONTROL_1_12_24_24_HOUR_MODE;
  //aux  =   PCF8523_Set12_24_HourMode ( myPCF8523_I2C_parameters, myPCF8523_Data );

  ///* Internal oscillator capacitor selection: 7 pF  */
  //aux  =   PCF8523_SetInternalOscillatorCapacitor ( myPCF8523_I2C_parameters, CONTROL_1_CAP_SEL_7_PF );

  ///* Minute interrupt and half minute interrupt are disabled  */
  //aux  =   PCF8523_SetMinuteInterrupts ( myPCF8523_I2C_parameters, CONTROL_2_MI_MINUTE_INTERRUPT_DISABLED, CONTROL_2_HMI_HALF_MINUTE_INTERRUPT_DISABLED );

  ///* Clear timer flag  */
  //aux  =   PCF8523_ClearTimerFlag ( myPCF8523_I2C_parameters );

  ///* CLKOUT: 1Hz  */
  //aux  =   PCF8523_SetClockOutputFrequency ( myPCF8523_I2C_parameters, CONTROL_2_COF_CLKOUT_1_HZ );

  ///* Normal mode offset at 0.  */
  //aux  =   PCF8523_SetOffset ( myPCF8523_I2C_parameters, OFFSET_MODE_NORMAL_MODE, 0 );

  ///* Write data ( 0x23 ) into device's RAM */
  //myPCF8523_Data.ramByte  =   0x23;
  //aux  =   PCF8523_WriteByteRAM ( myPCF8523_I2C_parameters, myPCF8523_Data );

  ///* Read data from device's RAM */
  //myPCF8523_Data.ramByte  =   0;                                                       // Reset the variable
  //aux  =   PCF8523_ReadByteRAM ( myPCF8523_I2C_parameters, &myPCF8523_Data );

  ///* Get day. After reset, we expect to get 0x01  */
  //aux  =   PCF8523_GetDay ( myPCF8523_I2C_parameters, &myPCF8523_Data );

  ///* Set day: 23  */
  //myPCF8523_Data.BCDday   =   0x23;
  //aux  =   PCF8523_SetDay ( myPCF8523_I2C_parameters, myPCF8523_Data );

  ///* Get month. After reset, we expect to get 0x01 ( January )  */
  //aux  =   PCF8523_GetMonth ( myPCF8523_I2C_parameters, &myPCF8523_Data );

  ///* Set month: September  */
  //myPCF8523_Data.BCDmonth   =   MONTHS_MONTHS_SEPTEMBER;
  //aux  =   PCF8523_SetMonth ( myPCF8523_I2C_parameters, myPCF8523_Data );

  ///* Get weekday. After reset, we expect to get Saturday  */
  //aux  =   PCF8523_GetWeekday ( myPCF8523_I2C_parameters, &myPCF8523_Data );

  ///* Set weekday: Friday  */
  //myPCF8523_Data.weekday   =   WEEKDAYS_WEEKDAYS_FRIDAY;
  //aux  =   PCF8523_SetWeekday ( myPCF8523_I2C_parameters, myPCF8523_Data );

  ///* Get year. After reset, we expect to get 00 ( it corresponds to 2000 )  */
  //aux  =   PCF8523_GetYear ( myPCF8523_I2C_parameters, &myPCF8523_Data );

  ///* Set year: 19 ( 2019 )  */
  //myPCF8523_Data.BCDyear   =   0x19;
  //aux  =   PCF8523_SetYear ( myPCF8523_I2C_parameters, myPCF8523_Data );

  ///* Set time: 235955 ( 23:59:55 )  */
  //myPCF8523_Data.BCDtime   =   0x235955;
  //aux  =   PCF8523_SetTime ( myPCF8523_I2C_parameters, myPCF8523_Data );
  
  
    
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

      ///* Get time  */
      //aux  =   PCF8523_GetTime ( myPCF8523_I2C_parameters, &myPCF8523_Data );

      ///* Get day  */
      //aux  =   PCF8523_GetDay ( myPCF8523_I2C_parameters, &myPCF8523_Data );

      ///* Get month  */
      //aux  =   PCF8523_GetMonth ( myPCF8523_I2C_parameters, &myPCF8523_Data );

      ///* Get weekday  */
      //aux  =   PCF8523_GetWeekday ( myPCF8523_I2C_parameters, &myPCF8523_Data );

      ///* Get year  */
      //aux  =   PCF8523_GetYear ( myPCF8523_I2C_parameters, &myPCF8523_Data );


      ///* Transmit result through the UART  */
      //sprintf ( (char*)myMessage, "Time: %0.2x:%0.2x:%0.2x, Month %x Day %x %s 20%x\r\n", ( ( myPCF8523_Data.BCDtime & 0xFF0000 ) >> 16U ), ( ( myPCF8523_Data.BCDtime & 0x00FF00 ) >> 8U ), 
      //                                                        ( myPCF8523_Data.BCDtime & 0x0000FF ), myPCF8523_Data.BCDmonth, myPCF8523_Data.BCDday, MY_WEEK_DAY_STRING[myPCF8523_Data.weekday], myPCF8523_Data.BCDyear );

      //NRF_UART0->TASKS_STOPRX  =   1UL;
      //NRF_UART0->TASKS_STOPTX  =   1UL;
      //myPtr                    =   &myMessage[0];

      //NRF_UART0->TASKS_STARTTX =   1UL;
      //NRF_UART0->TXD           =   *myPtr;

      
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
