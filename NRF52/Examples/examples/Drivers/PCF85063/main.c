/**
 * @brief       main.c
 * @details     This example shows how to work with the external device: PCF85063. Every 1 seconds, a new
 *              time and date is read from the device and the data is transmitted through the UART ( Baud Rate: 230400 ).
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
  static const char* MY_WEEK_DAY_STRING[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

  uint8_t  myMessage[ TX_BUFF_SIZE ];

  I2C_parameters_t   myPCF85063_I2C_parameters;
  PCF85063_status_t  aux;
  PCF85063_data_t    myPCF85063_Data;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  

  /* I2C definition   */
  myPCF85063_I2C_parameters.TWIinstance =    NRF_TWI0;
  myPCF85063_I2C_parameters.SDA         =    TWI0_SDA;
  myPCF85063_I2C_parameters.SCL         =    TWI0_SCL;
  myPCF85063_I2C_parameters.ADDR        =    PCF85063_ADDRESS;
  myPCF85063_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
  myPCF85063_I2C_parameters.SDAport     =    NRF_P0;
  myPCF85063_I2C_parameters.SCLport     =    NRF_P0;

  /* Configure I2C peripheral  */
  aux  =   PCF85063_Init           ( myPCF85063_I2C_parameters );

  /* Perform a software reset  */
  aux  =   PCF85063_SoftwareReset ( myPCF85063_I2C_parameters );

  /* Wait until the oscillator is stable   */
  do{ 
    /* Clear Clock integrity flag.  */
    aux  =   PCF85063_ClearOscillatorClockIntegrityFlag ( myPCF85063_I2C_parameters );

    /* Clear Clock integrity flag.  */
    aux  =   PCF85063_CheckOscillatorClockIntegrityFlag ( myPCF85063_I2C_parameters, &myPCF85063_Data );
  }while( myPCF85063_Data.os == SECONDS_OS_CLOCK_INTEGRITY_NOT_GUARANTEED );
  
  /* External clock test mode: Normal mode ( no test at all )  */
  aux  =   PCF85063_SetTestMode ( myPCF85063_I2C_parameters, CONTROL_1_EXT_TEST_NORMAL_MODE );

  /* RTC clock is enabled  */
  aux  =   PCF85063_SetRTCMode ( myPCF85063_I2C_parameters, CONTROL_1_STOP_RTC_CLOCK_RUNS );

  /* No correction interrupt generated  */
  aux  =   PCF85063_SetCorrectionInterruptMode ( myPCF85063_I2C_parameters, CONTROL_1_CIE_NO_CORRECTION_INTERRUPT_GENERATED );

  /* 24 hour mode is selected  */
  myPCF85063_Data.Time12H_24HMode  =   CONTROL_1_12_24_24_HOUR_MODE;
  aux  =   PCF85063_Set12_24_HourMode ( myPCF85063_I2C_parameters, myPCF85063_Data );

  /* Internal oscillator capacitor selection: 7 pF  */
  aux  =   PCF85063_SetInternalOscillatorCapacitor ( myPCF85063_I2C_parameters, CONTROL_1_CAP_SEL_7_PF );

  /* Minute interrupt and half minute interrupt are disabled  */
  aux  =   PCF85063_SetMinuteInterrupts ( myPCF85063_I2C_parameters, CONTROL_2_MI_MINUTE_INTERRUPT_DISABLED, CONTROL_2_HMI_HALF_MINUTE_INTERRUPT_DISABLED );

  /* Clear timer flag  */
  aux  =   PCF85063_ClearTimerFlag ( myPCF85063_I2C_parameters );

  /* CLKOUT: 1Hz  */
  aux  =   PCF85063_SetClockOutputFrequency ( myPCF85063_I2C_parameters, CONTROL_2_COF_CLKOUT_1_HZ );

  /* Normal mode offset at 0.  */
  aux  =   PCF85063_SetOffset ( myPCF85063_I2C_parameters, OFFSET_MODE_NORMAL_MODE, 0 );

  /* Write data ( 0x23 ) into device's RAM */
  myPCF85063_Data.ramByte  =   0x23;
  aux  =   PCF85063_WriteByteRAM ( myPCF85063_I2C_parameters, myPCF85063_Data );

  /* Read data from device's RAM */
  myPCF85063_Data.ramByte  =   0;                                                       // Reset the variable
  aux  =   PCF85063_ReadByteRAM ( myPCF85063_I2C_parameters, &myPCF85063_Data );

  /* Get day. After reset, we expect to get 0x01  */
  aux  =   PCF85063_GetDay ( myPCF85063_I2C_parameters, &myPCF85063_Data );

  /* Set day: 23  */
  myPCF85063_Data.BCDday   =   0x23;
  aux  =   PCF85063_SetDay ( myPCF85063_I2C_parameters, myPCF85063_Data );

  /* Get month. After reset, we expect to get 0x01 ( January )  */
  aux  =   PCF85063_GetMonth ( myPCF85063_I2C_parameters, &myPCF85063_Data );

  /* Set month: September  */
  myPCF85063_Data.BCDmonth   =   MONTHS_MONTHS_SEPTEMBER;
  aux  =   PCF85063_SetMonth ( myPCF85063_I2C_parameters, myPCF85063_Data );

  /* Get weekday. After reset, we expect to get Saturday  */
  aux  =   PCF85063_GetWeekday ( myPCF85063_I2C_parameters, &myPCF85063_Data );

  /* Set weekday: Friday  */
  myPCF85063_Data.weekday   =   WEEKDAYS_WEEKDAYS_FRIDAY;
  aux  =   PCF85063_SetWeekday ( myPCF85063_I2C_parameters, myPCF85063_Data );

  /* Get year. After reset, we expect to get 00 ( it corresponds to 2000 )  */
  aux  =   PCF85063_GetYear ( myPCF85063_I2C_parameters, &myPCF85063_Data );

  /* Set year: 19 ( 2019 )  */
  myPCF85063_Data.BCDyear   =   0x19;
  aux  =   PCF85063_SetYear ( myPCF85063_I2C_parameters, myPCF85063_Data );

  /* Set time: 235955 ( 23:59:55 )  */
  myPCF85063_Data.BCDtime   =   0x235955;
  aux  =   PCF85063_SetTime ( myPCF85063_I2C_parameters, myPCF85063_Data );
  
  
    
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
      aux  =   PCF85063_GetTime ( myPCF85063_I2C_parameters, &myPCF85063_Data );

      /* Get day  */
      aux  =   PCF85063_GetDay ( myPCF85063_I2C_parameters, &myPCF85063_Data );

      /* Get month  */
      aux  =   PCF85063_GetMonth ( myPCF85063_I2C_parameters, &myPCF85063_Data );

      /* Get weekday  */
      aux  =   PCF85063_GetWeekday ( myPCF85063_I2C_parameters, &myPCF85063_Data );

      /* Get year  */
      aux  =   PCF85063_GetYear ( myPCF85063_I2C_parameters, &myPCF85063_Data );


      /* Transmit result through the UART  */
      sprintf ( (char*)myMessage, "Time: %0.2x:%0.2x:%0.2x, Month %x Day %x %s 20%x\r\n", ( ( myPCF85063_Data.BCDtime & 0xFF0000 ) >> 16U ), ( ( myPCF85063_Data.BCDtime & 0x00FF00 ) >> 8U ), 
                                                              ( myPCF85063_Data.BCDtime & 0x0000FF ), myPCF85063_Data.BCDmonth, myPCF85063_Data.BCDday, MY_WEEK_DAY_STRING[myPCF85063_Data.weekday], myPCF85063_Data.BCDyear );

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
