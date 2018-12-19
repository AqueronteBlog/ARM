/**
 * @brief       main.c
 * @details     This example shows how to work with the external device: AMG8833. Every 1 seconds, a new
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

//  I2C_parameters_t myAMG8833_I2C_parameters;
//  AMG8833_status_t  aux;
//  AMG8833_data_t    myAMG8833_Data;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  

//  /* I2C definition   */
//  myAMG8833_I2C_parameters.TWIinstance =    NRF_TWI0;
//  myAMG8833_I2C_parameters.SDA         =    TWI0_SDA;
//  myAMG8833_I2C_parameters.SCL         =    TWI0_SCL;
//  myAMG8833_I2C_parameters.ADDR        =    AMG8833_ADDRESS_ADR1_0_ADR0_0;
//  myAMG8833_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
//  myAMG8833_I2C_parameters.SDAport     =    NRF_P0;
//  myAMG8833_I2C_parameters.SCLport     =    NRF_P0;
//
//  /* Configure I2C peripheral  */
//  aux  =   AMG8833_Init              ( myAMG8833_I2C_parameters );
//
//  /* Reset the device by software  */
//  aux  =   AMG8833_SoftwareReset     ( myAMG8833_I2C_parameters );
//  
//  /* Wait until the device is ready  */
//  do
//  {
//    /* Read configuration register  */
//    aux  =   AMG8833_ReadConfigurationRegister ( myAMG8833_I2C_parameters, &myAMG8833_Data );
//  }while ( ( myAMG8833_Data.ConfigurationRegister & RST_BIT_MASK ) != RST_NORMAL_OPERATION );  // [TODO]       This is DANGEROUS, if something goes wrong, the uC will get stuck here!!!.
//                                                                                              // [WORKAROUND] Insert a timeout.
//  /* Turn off the device  */
//  aux  =   AMG8833_SetModeOperation ( myAMG8833_I2C_parameters, MOD_POWER_DOWN );
//
//  /* Get manufacturer ID */
//  aux  =   AMG8833_GetManufacturerID ( myAMG8833_I2C_parameters, &myAMG8833_Data );
//  sprintf ( (char*)myMessage, "Manufacturer ID: %02x\r\n", myAMG8833_Data.ManufacturerID );
//  NRF_UART0->TASKS_STOPRX  =   1UL;
//  NRF_UART0->TASKS_STOPTX  =   1UL;
//  myPtr                    =   &myMessage[0];
//
//  NRF_UART0->TASKS_STARTTX =   1UL;
//  NRF_UART0->TXD           =   *myPtr;
//  nrf_delay_ms ( 500 );
//
//  /* Get device ID */
//  aux  =   AMG8833_GetDeviceID       ( myAMG8833_I2C_parameters, &myAMG8833_Data );
//  sprintf ( (char*)myMessage, "Device ID: %02x\r\n", myAMG8833_Data.DeviceID );
//  NRF_UART0->TASKS_STOPRX  =   1UL;
//  NRF_UART0->TASKS_STOPTX  =   1UL;
//  myPtr                    =   &myMessage[0];
//
//  NRF_UART0->TASKS_STARTTX =   1UL;
//  NRF_UART0->TXD           =   *myPtr;
//  nrf_delay_ms ( 500 );
//  
//  /* Conversion Rate: 1 conversions/sec ( 4 averaged samples ) */
//  aux  =   AMG8833_SetConversionRate ( myAMG8833_I2C_parameters, CR_4_AVERAGED_SAMPLES );
//
//  /* Disbale #DRDY pin */
//  aux  =   AMG8833_SetnDRDY_EnableBit ( myAMG8833_I2C_parameters, EN_nDRDY_PIN_DISABLED );
//
//  /* Turn on the device  */
//  aux  =   AMG8833_SetModeOperation ( myAMG8833_I2C_parameters, MOD_SENSOR_AND_DIE_CONT_CONVERSION );


  
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

//      /* Wait until a new data is ready to be read  */
//      do
//      {
//        /* Read configuration register  */
//        aux  =   AMG8833_ReadConfigurationRegister ( myAMG8833_I2C_parameters, &myAMG8833_Data );
//      }while ( ( myAMG8833_Data.ConfigurationRegister & nDRDY_MASK ) == nDRDY_CONVERSION_IN_PROGRESS );  // [TODO]       This is DANGEROUS, if something goes wrong, the uC will get stuck here!!!.
//                                                                                                        // [WORKAROUND] Insert a timeout.
//      /* Get raw temperature ( T_DIE ) */
//      aux  =   AMG8833_GetRawTemperature           ( myAMG8833_I2C_parameters, &myAMG8833_Data );
//
//      /* Get raw sensor voltage result ( V_SENSOR ) */
//      aux  =   AMG8833_GetRawSensorVoltage         ( myAMG8833_I2C_parameters, &myAMG8833_Data );
//
//      /* Calculate temperature ( T_DIE ) */
//      aux  =   AMG8833_CalculateTemperature        ( &myAMG8833_Data );
//
//      /* Calculates the real sensor voltage ( V_SENSOR ) value */
//      aux  =   AMG8833_CalculateSensorVoltage      ( &myAMG8833_Data );
//
//      /* Calculate object temperature ( T_OBJ ) */
//      myAMG8833_Data.s0   =   S0;                                                                        // Typical values for S0 are between 5×10^–14 and 7×10^–14
//      aux  =   AMG8833_CalculateObjectTemperature  ( &myAMG8833_Data );
//
//
//      /* Transmit result through the UART  */
//      sprintf ( (char*)myMessage, "T_DIE: %d mC | T_OBJ: %d mC\r\n", (int32_t)( myAMG8833_Data.TemperatureC * 1000.0 ), (int32_t)( myAMG8833_Data.ObjectTemperatureC * 1000.0 ) );
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
