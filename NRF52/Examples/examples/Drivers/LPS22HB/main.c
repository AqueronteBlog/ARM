/**
 * @brief       main.c
 * @details     [TODO]This example shows how to work with the external device: LPS22HB. Every 1 seconds, a new
 *              pressure/temperature value is read and the data is transmitted through the UART ( Baud Rate: 230400 ).
 *
 *              The microcontroller is in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        15/June/2019
 * @version     15/June/2019    The ORIGIN
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
#include "D:/Workspace/ARM/Drivers/LPS22HB/LPS22HB.h" 
#else
#include "D:/vsProjects/ARM/Drivers/LPS22HB/LPS22HB.h" 
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

//  I2C_parameters_t     myLPS22HB_I2C_parameters;
//  LPS22HB_status_t     aux;
//  LPS22HB_data_t       myLPS22HB_Data;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

//  
//  /* I2C definition   */
//  myLPS22HB_I2C_parameters.TWIinstance =    NRF_TWI0;
//  myLPS22HB_I2C_parameters.SDA         =    TWI0_SDA;
//  myLPS22HB_I2C_parameters.SCL         =    TWI0_SCL;
//  myLPS22HB_I2C_parameters.ADDR        =    LPS22HB_ADDRESS_1;
//  myLPS22HB_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
//  myLPS22HB_I2C_parameters.SDAport     =    NRF_P0;
//  myLPS22HB_I2C_parameters.SCLport     =    NRF_P0;
//
//  /* Configure I2C peripheral  */
//  aux  =   LPS22HB_Init  ( myLPS22HB_I2C_parameters );
//
//  /* Perform a software reset  */
//  aux  =   LPS22HB_SetSoftwareReset ( myLPS22HB_I2C_parameters );
//
//  do{
//    aux  =   LPS22HB_GetSoftwareReset ( myLPS22HB_I2C_parameters, &myLPS22HB_Data );      // Dangerous!!! The uC may get stuck here...
//                                                                                          // [WORKAROUND] Insert a counter
//  }while ( myLPS22HB_Data.swreset == CTRL_REG2_SWRESET_SW_RESET );
//
//  /* Reboot memory content  */
//  aux  =   LPS22HB_SetRebootMemoryContent ( myLPS22HB_I2C_parameters );
//
//  do{
//    aux  =   LPS22HB_GetRebootMemoryContent ( myLPS22HB_I2C_parameters, &myLPS22HB_Data );  // Dangerous!!! The uC may get stuck here...
//                                                                                            // [WORKAROUND] Insert a counter
//  }while ( myLPS22HB_Data.boot == CTRL_REG2_BOOT_REBOOT_MODE );
//  
//  /* Set device in lOW-POWER mode  */
//  aux  =   LPS22HB_SetPowerMode ( myLPS22HB_I2C_parameters, CTRL_REG1_PD_ACTIVE_MODE ); //CTRL_REG1_PD_POWER_DOWN_MODE );
//
//  /* Get device ID  */
//  aux  =   LPS22HB_GetDeviceID ( myLPS22HB_I2C_parameters, &myLPS22HB_Data );
//
//  /* Set temperature resolution: 64 internal average  */
//  myLPS22HB_Data.avgt  =   RES_CONF_AVGT_64;
//  aux  =   LPS22HB_SetTemperatureResolution ( myLPS22HB_I2C_parameters, myLPS22HB_Data );
//
//  /* Set pressure resolution: 512 internal average  */
//  myLPS22HB_Data.avgp  =   RES_CONF_AVGP_512;
//  aux  =   LPS22HB_SetPressureResolution ( myLPS22HB_I2C_parameters, myLPS22HB_Data );
//  
//  /* Set ODR: One-shot mode enabled  */
//  myLPS22HB_Data.odr   =   CTRL_REG1_ODR_ONE_SHOT_MODE;
//  aux  =   LPS22HB_SetOutputDataRate ( myLPS22HB_I2C_parameters, myLPS22HB_Data );
//
//  /* Interrupt generation disabled  */
//  aux  =   LPS22HB_SetInterruptGeneration ( myLPS22HB_I2C_parameters, CTRL_REG1_DIFF_EN_DISABLED );
//
//  /* Block data update: output registers not updated until MSB and LSB have been read  */
//  aux  =   LPS22HB_SetBlockDataUpdate ( myLPS22HB_I2C_parameters, CTRL_REG1_BDU_1 );
//
//  /* FIFO disabled  */
//  myLPS22HB_Data.fifo_en   =   CTRL_REG2_FIFO_EN_DISABLED;
//  aux  =   LPS22HB_SetFIFOEnable ( myLPS22HB_I2C_parameters, myLPS22HB_Data );
//
//  /* Autozero: Normal mode  */
//  myLPS22HB_Data.autozero  =   CTRL_REG2_AUTOZERO_NORMAL_MODE;
//  aux  =   LPS22HB_SetAutozero ( myLPS22HB_I2C_parameters, myLPS22HB_Data );
//
//  /* Set device in ACTIVE mode  */
//  //aux  =   LPS22HB_SetPowerMode ( myLPS22HB_I2C_parameters, CTRL_REG1_PD_ACTIVE_MODE );

  
  
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
//
//      /* Trigger to get a new data value  */
//      aux  =   LPS22HB_SetOneShot ( myLPS22HB_I2C_parameters );
//
//      /* Wait until the conversion is done  */
//      do{
//        aux  =   LPS22HB_GetOneShot ( myLPS22HB_I2C_parameters, &myLPS22HB_Data );
//      }while( myLPS22HB_Data.one_shot == CTRL_REG2_ONE_SHOT_NEW_DATASET );                        // Dangerous!!! The uC may get stuck here...
//                                                                                                  // [WORKAROUND] Insert a counter
//
//      /* Wait until there is a new data ( both pressure and temperature )  */
//      do{
//        aux  =   LPS22HB_GetStatusRegister ( myLPS22HB_I2C_parameters, &myLPS22HB_Data );
//      }while( ( myLPS22HB_Data.status_reg & ( STATUS_REG_P_DA_MASK | STATUS_REG_T_DA_MASK ) ) != STATUS_REG_P_DA_NEW_DATA ); // Dangerous!!! The uC may get stuck here...
//                                                                                                                                                            // [WORKAROUND] Insert a counter
//      
//      /* Get pressure  */
//      aux  =   LPS22HB_GetPressure ( myLPS22HB_I2C_parameters, &myLPS22HB_Data );
//
//      /* Get temperature  */
//      aux  =   LPS22HB_GetTemperature ( myLPS22HB_I2C_parameters, &myLPS22HB_Data );
//      
//      
//      /* Transmit result through the UART  */
//      sprintf ( (char*)myMessage, "T: %d.%d C, P: %d.%d mbar\r\n", (int32_t)myLPS22HB_Data.temperature, (int32_t)( ( myLPS22HB_Data.temperature - (uint32_t)myLPS22HB_Data.temperature ) * 10.0f ), 
//                                                                   (int32_t)myLPS22HB_Data.pressure, (int32_t)( ( myLPS22HB_Data.pressure - (uint32_t)myLPS22HB_Data.pressure ) * 10.0f ) );
//
//      NRF_UART0->TASKS_STOPRX  =   1UL;
//      NRF_UART0->TASKS_STOPTX  =   1UL;
//      myPtr                    =   &myMessage[0];
//
//      NRF_UART0->TASKS_STARTTX =   1UL;
//      NRF_UART0->TXD           =   *myPtr;

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
