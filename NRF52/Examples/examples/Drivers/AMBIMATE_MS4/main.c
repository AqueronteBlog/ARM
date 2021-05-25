/**
 * @brief       main.c
 * @details     [TODO]This example shows how to work with the external device: AMBIMATE_MS4. Every 4 seconds, a new
 *              set of values are read and the data is transmitted through the UART ( Baud Rate: 230400 ).
 *
 *              The microcontroller is in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        23/May/2021
 * @version     23/May/2021    The ORIGIN
 * @pre         This firmware was tested on the nrf52-DK with Segger Embedded Studio v5.44 ( SDK 14.2.0 ).
 * @warning     The softdevice (s132) is taken into account, Bluetooth was not used although.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */
#include <stdio.h>

#include "nordic_common.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "board.h"
#include "functions.h"
#include "interrupts.h"
#if defined (WORK_FROM_HOME)
#include "D:/Workspaces/Personal/ARM/Drivers/AMBIMATE_MS4/AMBIMATE_MS4.h" 
#else
#include "D:/vsProjects/ARM/Drivers/AMBIMATE_MS4/AMBIMATE_MS4.h" 
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

  I2C_parameters_t  myAMBIMATE_MS4_I2C_parameters;
  AMBIMATE_MS4_status_t    aux;
  AMBIMATE_MS4_data_t      myAMBIMATE_MS4_Data;



  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  

  /* I2C definition   */
  myAMBIMATE_MS4_I2C_parameters.TWIinstance =    NRF_TWI0;
  myAMBIMATE_MS4_I2C_parameters.SDA         =    TWI0_SDA;
  myAMBIMATE_MS4_I2C_parameters.SCL         =    TWI0_SCL;
  myAMBIMATE_MS4_I2C_parameters.ADDR        =    AMBIMATE_MS4_ADDRESS;
  myAMBIMATE_MS4_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K100;
  myAMBIMATE_MS4_I2C_parameters.SDAport     =    NRF_P0;
  myAMBIMATE_MS4_I2C_parameters.SCLport     =    NRF_P0;

  /* Configure I2C peripheral  */
  aux  =   AMBIMATE_MS4_Init ( myAMBIMATE_MS4_I2C_parameters );

  /* Reset the Ambimate MS4 sensor  */
  aux  =   AMBIMATE_MS4_ProcessorReset ( myAMBIMATE_MS4_I2C_parameters );
  nrf_delay_ms (1000);

  /* Get the firmware version  */
  aux  =   AMBIMATE_MS4_GetFirmwareVersion ( myAMBIMATE_MS4_I2C_parameters, &myAMBIMATE_MS4_Data.info.firmware_version );

  /* Get the firmware sub-version  */
  aux  =   AMBIMATE_MS4_GetFirmwareSubVersion ( myAMBIMATE_MS4_I2C_parameters, &myAMBIMATE_MS4_Data.info.firmware_sub_version );

  /* Get the optional sensors on the board  */
  aux  =   AMBIMATE_MS4_GetOptionalSensorsByte ( myAMBIMATE_MS4_I2C_parameters, &myAMBIMATE_MS4_Data.info.optional_sensors );



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


    /* Proccess new action   */
    if ( myState == 1UL )
    {
      NRF_P0->OUTCLR  |= ( ( 1U << LED1 ) | ( 1U << LED2 ) | ( 1U << LED3 ) | ( 1U << LED4 ) );   // Turn all the LEDs on

      aux  =   AMBIMATE_MS4_ScanStartByte ( myAMBIMATE_MS4_I2C_parameters, WRITEABLE_REGISTERS_GAS_INITIATE_NEW_MEASUREMENT, WRITEABLE_REGISTERS_BATT_INITIATE_NEW_MEASUREMENT, WRITEABLE_REGISTERS_AUD_INITIATE_NEW_MEASUREMENT, WRITEABLE_REGISTERS_LIGHT_INITIATE_NEW_MEASUREMENT, WRITEABLE_REGISTERS_HUM_INITIATE_NEW_MEASUREMENT, WRITEABLE_REGISTERS_TEMP_INITIATE_NEW_MEASUREMENT, WRITEABLE_REGISTERS_STATUS_INITIATE_NEW_MEASUREMENT );

      /* Wait for a new data set value  */
      do{
        /* Reset the variable  */
        myAMBIMATE_MS4_Data.start_scan_byte  =  (uint8_t)( WRITEABLE_REGISTERS_GAS_INITIATE_NEW_MEASUREMENT | WRITEABLE_REGISTERS_BATT_INITIATE_NEW_MEASUREMENT | WRITEABLE_REGISTERS_AUD_INITIATE_NEW_MEASUREMENT | WRITEABLE_REGISTERS_LIGHT_INITIATE_NEW_MEASUREMENT | WRITEABLE_REGISTERS_HUM_INITIATE_NEW_MEASUREMENT | WRITEABLE_REGISTERS_TEMP_INITIATE_NEW_MEASUREMENT | WRITEABLE_REGISTERS_STATUS_INITIATE_NEW_MEASUREMENT ); 
        
        aux  =   AMBIMATE_MS4_GetScanStartByte ( myAMBIMATE_MS4_I2C_parameters, &myAMBIMATE_MS4_Data.start_scan_byte );
        nrf_delay_ms (100);
      }while( ( myAMBIMATE_MS4_Data.start_scan_byte & ( WRITEABLE_REGISTERS_GAS_MASK | WRITEABLE_REGISTERS_BATT_MASK | WRITEABLE_REGISTERS_AUD_MASK | WRITEABLE_REGISTERS_LIGHT_MASK | WRITEABLE_REGISTERS_HUM_MASK | WRITEABLE_REGISTERS_TEMP_MASK | WRITEABLE_REGISTERS_STATUS_MASK ) ) != 0x00 );

      /* Get all the raw values  */
      aux  =   AMBIMATE_MS4_GetRawAllSensors ( myAMBIMATE_MS4_I2C_parameters, &myAMBIMATE_MS4_Data.status, &myAMBIMATE_MS4_Data.raw_data );


      /* Transmit result through the UART  */
      sprintf ( (char*)myMessage, "CO2: %d ppm, VOC: %d, T: %d C, RH: %d %%, Lux: %d, Batt: %d V, Aud: %d db\r\n", (uint32_t)myAMBIMATE_MS4_Data.data.eco2, (uint32_t)myAMBIMATE_MS4_Data.data.voc, (uint32_t)myAMBIMATE_MS4_Data.data.temperature, (uint32_t)myAMBIMATE_MS4_Data.data.humidity, myAMBIMATE_MS4_Data.data.light, myAMBIMATE_MS4_Data.data.battery_volts, myAMBIMATE_MS4_Data.data.audio );

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
