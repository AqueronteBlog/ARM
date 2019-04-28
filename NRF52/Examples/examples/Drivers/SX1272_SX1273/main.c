/**
 * @brief       main.c
 * @details     This example shows how to work with the external device: MCP9808. Every 1 seconds, a new
 *              temperature value is read and the data is transmitted through the UART ( Baud Rate: 230400 ).
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
#include "D:/Workspace/ARM/Drivers/SX1272_1273/SX1272_SX1273.h" 
#else
#include "D:/vsProjects/ARM/Drivers/SX1272_1273/SX1272_SX1273.h" 
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

//  I2C_parameters_t      myMCP9808_I2C_parameters;
//  MCP9808_status_t      aux;
//  MCP9808_config_reg_t  myMCP9808_Config;
//  MCP9808_data_t        myMCP9808_Data;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  

  /* I2C definition   */
//  myMCP9808_I2C_parameters.TWIinstance =    NRF_TWI0;
//  myMCP9808_I2C_parameters.SDA         =    TWI0_SDA;
//  myMCP9808_I2C_parameters.SCL         =    TWI0_SCL;
//  myMCP9808_I2C_parameters.ADDR        =    MCP9808_ADDRESS_0;
//  myMCP9808_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
//  myMCP9808_I2C_parameters.SDAport     =    NRF_P0;
//  myMCP9808_I2C_parameters.SCLport     =    NRF_P0;
//
//  /* Configure I2C peripheral  */
//  aux  =   MCP9808_Init  ( myMCP9808_I2C_parameters );
//
//  /* Shutdown the device, low-power mode enabled  */
//  aux  =   MCP9808_GetCONFIG ( myMCP9808_I2C_parameters, &myMCP9808_Config );
//  
//  myMCP9808_Config.shdn  =   CONFIG_SHDN_SHUTDOWN;
//  aux  =   MCP9808_SetCONFIG ( myMCP9808_I2C_parameters, myMCP9808_Config );
//  
//  /* Get manufacturer ID  */
//  aux  =   MCP9808_GetManufacturerID ( myMCP9808_I2C_parameters, &myMCP9808_Data );
//
//  /* Get device ID and device revision  */
//  aux  =   MCP9808_GetDeviceID ( myMCP9808_I2C_parameters, &myMCP9808_Data );
//  
//  /* Configure the device
//   *  - T_UPPER and T_LOWER limit hysteresis at 0C
//   *  - Continuous conversion mode
//   *  - T_CRIT unlocked
//   *  - Window lock unlocked
//   *  - Alert output control disabled
//   *  - Alert output select: Alert for T_UPPER, T_LOWER and T_CRIT
//   *  - Alert output polaruty: Active-low
//   *  - Alert output mode: Comparator output
//   */
//  myMCP9808_Config.t_hyst      =   CONFIG_T_HYST_0_C;
//  myMCP9808_Config.shdn        =   CONFIG_SHDN_CONTINUOUS_CONVERSION;
//  myMCP9808_Config.t_crit      =   CONFIG_CRIT_LOCK_UNLOCKED;
//  myMCP9808_Config.t_win_lock  =   CONFIG_WIN_LOCK_UNLOCKED;
//  myMCP9808_Config.alert_cnt   =   CONFIG_ALERT_CNT_DISABLED;
//  myMCP9808_Config.alert_sel   =   CONFIG_ALERT_SEL_TUPPER_TLOWER_TCRIT;
//  myMCP9808_Config.alert_pol   =   CONFIG_ALERT_POL_ACTIVE_LOW;
//  myMCP9808_Config.alert_mod   =   CONFIG_ALERT_MOD_COMPARATOR_OUTPUT;
//  aux  =   MCP9808_SetCONFIG ( myMCP9808_I2C_parameters, myMCP9808_Config );
//
//  /* Set resolution: +0.0625C ( t_CON ~ 250ms )  */
//  myMCP9808_Data.resolution  =   RESOLUTION_0_0625_C;
//  aux  =   MCP9808_SetResolution ( myMCP9808_I2C_parameters, myMCP9808_Data );
  
  
    
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

//      /* Get ambient temperature  */
//      aux  =   MCP9808_GetTA ( myMCP9808_I2C_parameters, &myMCP9808_Data );
//
//      /* Transmit result through the UART  */
//      sprintf ( (char*)myMessage, "T: %d.%d C\r\n", (int32_t)myMCP9808_Data.t_a, (int32_t)( ( myMCP9808_Data.t_a - (uint32_t)myMCP9808_Data.t_a ) * 10000.0f ) );
//
//      NRF_UART0->TASKS_STOPRX  =   1UL;
//      NRF_UART0->TASKS_STOPTX  =   1UL;
//      myPtr                    =   &myMessage[0];
//
//      NRF_UART0->TASKS_STARTTX =   1UL;
//      NRF_UART0->TXD           =   *myPtr;

      
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
