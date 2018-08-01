/**
 * @brief       main.c
 * @details     This example shows how to work with the external device: DS1307. Every 1 seconds, a new
 *              sample is performed and transmitted through the UART ( Baud Rate: 230400 ).
 *
 *              The microcontroller is in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        31/July/2018
 * @version     31/July/2018    The ORIGIN
 * @pre         This firmware was tested on the nrf52-DK with Segger Embedded Studio v3.40
 *              ( SDK 14.2.0 ).
 * @warning     The softdevice (s132) is taken into account, Bluetooth was not used although.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */
#include <stdio.h>

#include "nordic_common.h"
#include "nrf.h"
#include "board.h"
#include "functions.h"
#include "interrupts.h"
#include "D:/Workspace/ARM/Drivers/DS1307/DS1307.h"


/**@brief Constants.
 */
#define TX_BUFF_SIZE  64                          /*!<   UART buffer size                                       */


/**@brief Variables.
 */
volatile uint32_t myState;                        /*!<   State that indicates when to perform an ADC sample     */
volatile uint32_t myADCDoneFlag;                  /*!<   It indicates when a new ADC conversion is ready        */
volatile uint8_t  myMessage[ TX_BUFF_SIZE ];      /*!<   Message to be transmitted through the UART             */
volatile uint8_t  *myPtr;                         /*!<   Pointer to point out myMessage                         */




/**@brief Function for application main entry.
 */
int main(void)
{
  uint8_t                  myDataRAM;
  I2C_parameters_t         myDS1307_I2C_parameters;
  DS1307_status_t          aux;
  DS1307_vector_data_t     myDS1307_Data;
    

  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  

  /* I2C definition   */
  myDS1307_I2C_parameters.TWIinstance =    NRF_TWI0;
  myDS1307_I2C_parameters.SDA         =    TWI0_SDA;
  myDS1307_I2C_parameters.SCL         =    TWI0_SCL;
  myDS1307_I2C_parameters.ADDR        =    DS1307_ADDRESS;
  myDS1307_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
  myDS1307_I2C_parameters.SDAport     =    NRF_P0;
  myDS1307_I2C_parameters.SCLport     =    NRF_P0;

  /* Configure I2C peripheral */
  aux  =   DS1307_Init            ( myDS1307_I2C_parameters );

  /* Enable the DS1307 oscillator */
  aux  =   DS1307_OscillatorMode  ( myDS1307_I2C_parameters, SECONDS_CH_OSCILLATOR_ENABLED );

  /* Write data into the RAM memory */
  myDataRAM  =   0x23;
  aux  =   DS1307_WriteByteRAM    ( myDS1307_I2C_parameters, myDataRAM, 0x11 );                 // Data: 0x23, Address: 0x11
  
  /* Read data into the RAM memory */
  myDataRAM  =   0;
  aux  =   DS1307_ReadByteRAM     ( myDS1307_I2C_parameters, &myDataRAM, 0x11 );                // Address: 0x11        
  
  /* Erase data into the RAM memory */
  aux  =   DS1307_EraseByteRAM     ( myDS1307_I2C_parameters, 0x11 );                           // Address: 0x11
  
  /* Read data into the RAM memory */
  myDataRAM  =   0;
  aux  =   DS1307_ReadByteRAM     ( myDS1307_I2C_parameters, &myDataRAM, 0x11 );                // Address: 0x11 

  /* Set the day of the week */
  myDS1307_Data.DayOfTheWeek     =   DAY_TUESDAY;
  aux  =   DS1307_SetDayOfTheWeek ( myDS1307_I2C_parameters, myDS1307_Data );

  /* Set the date */
  myDS1307_Data.BCDDate          =   0x31;                                                      // Date: 31
  aux  =   DS1307_SetDate         ( myDS1307_I2C_parameters, myDS1307_Data );

  /* Set the month */
  myDS1307_Data.BCDMonth         =   MONTH_JULY;
  aux  =   DS1307_SetMonth        ( myDS1307_I2C_parameters, myDS1307_Data );

  /* Set the year */
  myDS1307_Data.BCDYear          =   0x18;                                                      // Year: 2018
  aux  =   DS1307_SetYear         ( myDS1307_I2C_parameters, myDS1307_Data );

  /* Set the time */
  myDS1307_Data.BCDTime          =   0x150300;                                                  // Time: 13:52.00
  myDS1307_Data.Time12H_24HMode  =   HOURS_MODE_24H;
  myDS1307_Data.TimeAM_PM_Mode   =   HOURS_MODE_PM;
  aux  =   DS1307_SetTime         ( myDS1307_I2C_parameters, myDS1307_Data );

  /* Set square-wave output pin: 32.768kHz  */
  aux  =   DS1307_SquareWaveOutput( myDS1307_I2C_parameters, CONTROL_SQWE_ENABLED, CONTROL_RS_32_768_KHZ );



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



    if ( myState == 1 )
    {
      NRF_P0->OUTCLR  |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );          // Turn all the LEDs on

      /* Get the day of the week */
      aux  =   DS1307_GetDayOfTheWeek ( myDS1307_I2C_parameters, &myDS1307_Data );

      /* Get the day of the date */
      aux  =   DS1307_GetDate         ( myDS1307_I2C_parameters, &myDS1307_Data );

      /* Get the month */
      aux  =   DS1307_GetMonth        ( myDS1307_I2C_parameters, &myDS1307_Data );

      /* Get the year */
      aux  =   DS1307_GetYear         ( myDS1307_I2C_parameters, &myDS1307_Data );

      /* Get the time */
      aux  =   DS1307_GetTime         ( myDS1307_I2C_parameters, &myDS1307_Data );


      /* Transmit result through the UART  */
      sprintf ( (char*)myMessage, "%02x/%02x/%02x %d %02x:%02x.%02x\r\n", myDS1307_Data.BCDDate, myDS1307_Data.BCDMonth, myDS1307_Data.BCDYear, myDS1307_Data.DayOfTheWeek,
                                                                          (uint8_t)( ( myDS1307_Data.BCDTime & 0xFF0000 ) >> 16U ), (uint8_t)( ( myDS1307_Data.BCDTime & 0x00FF00 ) >> 8U ),
                                                                          (uint8_t)( myDS1307_Data.BCDTime & 0x0000FF ) );

      NRF_UART0->TASKS_STOPRX  =   1UL;
      NRF_UART0->TASKS_STOPTX  =   1UL;
      myPtr                    =   &myMessage[0];

      NRF_UART0->TASKS_STARTTX =   1UL;
      NRF_UART0->TXD           =   *myPtr;

      
      /* Reset the variables   */
      myState          =   0;
      NRF_P0->OUTSET  |=   ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );          // Turn all the LEDs off
    }
    //__NOP();
  }
}


/**
 * @}
 */
