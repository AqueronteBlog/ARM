/**
 * @brief       main.c
 * @details     [TODO]This example shows how to work with the external device: HTS221. Every 1 seconds, a new
 *              temperature value is read and the data is transmitted through the UART ( Baud Rate: 230400 ).
 *
 *              The microcontroller is in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/May/2019
 * @version     22/May/2019    The ORIGIN
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
#include "D:/Workspace/ARM/Drivers/HTS221/HTS221.h" 
#else
#include "D:/vsProjects/ARM/Drivers/HTS221/HTS221.h" 
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

  I2C_parameters_t     myHTS221_I2C_parameters;
//  HTS221_status_t      aux;
//  HTS221_config_reg_t  myHTS221_Config;
//  HTS221_data_t        myHTS221_Data;


  conf_CLK    ();
  conf_GPIO   ();
  conf_UART   ();
  conf_TIMER0 ();

  

  /* I2C definition   */
//  myHTS221_I2C_parameters.TWIinstance =    NRF_TWI0;
//  myHTS221_I2C_parameters.SDA         =    TWI0_SDA;
//  myHTS221_I2C_parameters.SCL         =    TWI0_SCL;
//  myHTS221_I2C_parameters.ADDR        =    HTS221_ADDRESS_0;
//  myHTS221_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
//  myHTS221_I2C_parameters.SDAport     =    NRF_P0;
//  myHTS221_I2C_parameters.SCLport     =    NRF_P0;
//
//  /* Configure I2C peripheral  */
//  aux  =   HTS221_Init  ( myHTS221_I2C_parameters );
//
//  /* Shutdown the device, low-power mode enabled  */
//  aux  =   HTS221_GetCONFIG ( myHTS221_I2C_parameters, &myHTS221_Config );
//  
//  myHTS221_Config.shdn  =   CONFIG_SHDN_SHUTDOWN;
//  aux  =   HTS221_SetCONFIG ( myHTS221_I2C_parameters, myHTS221_Config );
//  
//  /* Get manufacturer ID  */
//  aux  =   HTS221_GetManufacturerID ( myHTS221_I2C_parameters, &myHTS221_Data );
//
//  /* Get device ID and device revision  */
//  aux  =   HTS221_GetDeviceID ( myHTS221_I2C_parameters, &myHTS221_Data );
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
//  myHTS221_Config.t_hyst      =   CONFIG_T_HYST_0_C;
//  myHTS221_Config.shdn        =   CONFIG_SHDN_CONTINUOUS_CONVERSION;
//  myHTS221_Config.t_crit      =   CONFIG_CRIT_LOCK_UNLOCKED;
//  myHTS221_Config.t_win_lock  =   CONFIG_WIN_LOCK_UNLOCKED;
//  myHTS221_Config.alert_cnt   =   CONFIG_ALERT_CNT_DISABLED;
//  myHTS221_Config.alert_sel   =   CONFIG_ALERT_SEL_TUPPER_TLOWER_TCRIT;
//  myHTS221_Config.alert_pol   =   CONFIG_ALERT_POL_ACTIVE_LOW;
//  myHTS221_Config.alert_mod   =   CONFIG_ALERT_MOD_COMPARATOR_OUTPUT;
//  aux  =   HTS221_SetCONFIG ( myHTS221_I2C_parameters, myHTS221_Config );
//
//  /* Set resolution: +0.0625C ( t_CON ~ 250ms )  */
//  myHTS221_Data.resolution  =   RESOLUTION_0_0625_C;
//  aux  =   HTS221_SetResolution ( myHTS221_I2C_parameters, myHTS221_Data );
  
  
    
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
//      aux  =   HTS221_GetTA ( myHTS221_I2C_parameters, &myHTS221_Data );
//
//      /* Transmit result through the UART  */
//      sprintf ( (char*)myMessage, "T: %d.%d C\r\n", (int32_t)myHTS221_Data.t_a, (int32_t)( ( myHTS221_Data.t_a - (uint32_t)myHTS221_Data.t_a ) * 10000.0f ) );
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
