/**
 * @brief       PCF8523.h
 * @details     Real-Time Clock (RTC) and calendar.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( https://www.nimbus.cit.ie ).
 */

#include "PCF8523.h"


/**
 * @brief       PCF8523_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_Init ( I2C_parameters_t myI2Cparameters )
{
  i2c_status_t aux;

  aux  =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_SetInternalOscillatorCapacitor ( I2C_parameters_t , PCF8523_control_1_cap_sel_t )
 *
 * @details     It sets the internal oscillator capacitor selection for quartz crystals with a corresponding load capacitance.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myCAP_SEL:       Load capacitance.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_SetInternalOscillatorCapacitor.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_SetInternalOscillatorCapacitor ( I2C_parameters_t myI2Cparameters, PCF8523_control_1_cap_sel_t myCAP_SEL )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF8523_CONTROL_1;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~CONTROL_1_CAP_SEL_MASK ) | myCAP_SEL );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_SetRTCMode ( I2C_parameters_t , PCF8523_control_1_stop_t )
 *
 * @details     It sets the RTC clock mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    mySTOP:          External clock test mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_SetRTCMode.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_SetRTCMode ( I2C_parameters_t myI2Cparameters, PCF8523_control_1_stop_t mySTOP )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF8523_CONTROL_1;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~CONTROL_1_STOP_MASK ) | mySTOP );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_SoftwareReset ( I2C_parameters_t )
 *
 * @details     It performs a software reset.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_SoftwareReset.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         For a software reset, 01011000 (58h) must be sent to register Control_1. Datasheet p12, 
 *              8.3 Reset.
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_SoftwareReset ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]   =   PCF8523_CONTROL_1;
  cmd[1]   =   0x58;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_SetHourMode ( I2C_parameters_t , PCF8523_control_1_12_24_t )
 *
 * @details     It sets 24h/12h mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    my12_24:         12h/24h mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_SetHourMode.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_SetHourMode ( I2C_parameters_t myI2Cparameters, PCF8523_control_1_12_24_t my12_24 )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF8523_CONTROL_1;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~CONTROL_1_12_24_MASK ) | my12_24 );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_SetSecondInterrupt ( I2C_parameters_t , PCF8523_control_1_sie_t )
 *
 * @details     It enables/disables the second interrupt.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    mySIE:           Second interrupt enabled/disabled.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_SetSecondInterrupt.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_SetSecondInterrupt ( I2C_parameters_t myI2Cparameters, PCF8523_control_1_sie_t mySIE )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF8523_CONTROL_1;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~CONTROL_1_SIE_MASK ) | mySIE );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_SetAlarmInterrupt ( I2C_parameters_t , PCF8523_control_1_aie_t )
 *
 * @details     It enables/disables the alarm interrupt.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myAIE:           Alarm interrupt enabled/disabled.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_SetAlarmInterrupt.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_SetAlarmInterrupt ( I2C_parameters_t myI2Cparameters, PCF8523_control_1_aie_t myAIE )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF8523_CONTROL_1;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~CONTROL_1_AIE_MASK ) | myAIE );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_SetCorrectionInterruptMode ( I2C_parameters_t , PCF8523_control_1_cie_t )
 *
 * @details     It sets the correction interrupt mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myCIE:           Correction interrupt enable.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_SetCorrectionInterruptMode.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_SetCorrectionInterruptMode ( I2C_parameters_t myI2Cparameters, PCF8523_control_1_cie_t myCIE )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF8523_CONTROL_1;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~CONTROL_1_CIE_MASK ) | myCIE );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_GetStatusInterruptFlags ( I2C_parameters_t , PCF8523_interrupt_flags_status_t* )
 *
 * @details     It gets the status interrupt flags.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myFlags:         All interrupt flags.
 *
 *
 * @return       Status of PCF8523_GetStatusInterruptFlags.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_GetStatusInterruptFlags ( I2C_parameters_t myI2Cparameters, PCF8523_interrupt_flags_status_t* myFlags )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd   =   PCF8523_CONTROL_2;
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myFlags->wtaf  =  (PCF8523_control_2_wtaf_t)( cmd & CONTROL_2_WTAG_MASK );
  myFlags->ctaf  =  (PCF8523_control_2_ctaf_t)( cmd & CONTROL_2_CTAF_MASK );
  myFlags->ctbf  =  (PCF8523_control_2_ctbf_t)( cmd & CONTROL_2_CTBF_MASK );
  myFlags->sf    =  (PCF8523_control_2_sf_t)( cmd & CONTROL_2_SF_MASK );
  myFlags->af    =  (PCF8523_control_2_af_t)( cmd & CONTROL_2_AF_MASK );
  
  /* Read the register   */
  cmd   =   PCF8523_CONTROL_3;
  aux   =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux   =   i2c_read ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myFlags->bsf   =  (PCF8523_control_3_bsf_t)( cmd & CONTROL_3_BSF_MASK );
  myFlags->blf   =  (PCF8523_control_3_blf_t)( cmd & CONTROL_3_BLF_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_SetWatchdogTimerA_Interrupt ( I2C_parameters_t , PCF8523_control_2_wtaie_t )
 *
 * @details     It enables/disables the watchdog timer A interrupt.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myWTAIE:         WDT timer A interrupt enabled/disabled.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_SetWatchdogTimerA_Interrupt.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_SetWatchdogTimerA_Interrupt ( I2C_parameters_t myI2Cparameters, PCF8523_control_2_wtaie_t myWTAIE )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF8523_CONTROL_2;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~CONTROL_2_WTAIE_MASK ) | myWTAIE );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_SetCountdownTimerA_Interrupt ( I2C_parameters_t , PCF8523_control_2_ctaie_t )
 *
 * @details     It enables/disables the countdown timer A interrupt.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myCTAIE:         Countdown timer A interrupt enabled/disabled.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_SetCountdownTimerA_Interrupt.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_SetCountdownTimerA_Interrupt ( I2C_parameters_t myI2Cparameters, PCF8523_control_2_ctaie_t myCTAIE )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF8523_CONTROL_2;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~CONTROL_2_CTAIE_MASK ) | myCTAIE );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_SetCountdownTimerB_Interrupt ( I2C_parameters_t , PCF8523_control_2_ctbie_t )
 *
 * @details     It enables/disables the countdown timer B interrupt.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myCTBIE:         Countdown timer B interrupt enabled/disabled.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_SetCountdownTimerB_Interrupt.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_SetCountdownTimerB_Interrupt ( I2C_parameters_t myI2Cparameters, PCF8523_control_2_ctbie_t myCTBIE )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF8523_CONTROL_2;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~CONTROL_2_CTBIE_MASK ) | myCTBIE );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_SetBatterySwitchOverInterrupt ( I2C_parameters_t , PCF8523_control_3_bsie_t )
 *
 * @details     It enables/disables the battery switch-over interrupt.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myBSIE:          Battery swith-over interrupt enabled/disabled.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_SetBatterySwitchOverInterrupt.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_SetBatterySwitchOverInterrupt ( I2C_parameters_t myI2Cparameters, PCF8523_control_3_bsie_t myBSIE )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF8523_CONTROL_3;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~CONTROL_3_BSIE_MASK ) | myBSIE );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_SetBatteryLowInterrupt ( I2C_parameters_t , PCF8523_control_3_blie_t )
 *
 * @details     It enables/disables the battery low interrupt.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myBLIE:          Battery low interrupt enabled/disabled.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_SetBatteryLowInterrupt.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_SetBatteryLowInterrupt ( I2C_parameters_t myI2Cparameters, PCF8523_control_3_blie_t myBLIE )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF8523_CONTROL_3;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~CONTROL_3_BLIE_MASK ) | myBLIE );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_SetBatteryPowerModeControl ( I2C_parameters_t , PCF8523_control_3_pm_t )
 *
 * @details     It sets the power mode: battery switch-over and battery low detection control.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myPM:            Battery power mode control.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_SetBatteryPowerModeControl.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_SetBatteryPowerModeControl ( I2C_parameters_t myI2Cparameters, PCF8523_control_3_pm_t myPM )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF8523_CONTROL_3;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~CONTROL_3_PM_MASK ) | myPM );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_GetTime ( I2C_parameters_t , PCF8523_time_t* )
 *
 * @details     It gets the time ( BCD format ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myActualTime:    Current time ( BCD format: HHMMSS ).
 *
 *
 * @return       Status of PCF8523_GetTime.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         This function makes use of the auto-incrementing function of the registers.
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_GetTime ( I2C_parameters_t myI2Cparameters, PCF8523_time_t* myActualTime )
{
  uint8_t      cmd[3]  =  { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF8523_SECONDS;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  if ( myActualTime->hourMode == CONTROL_1_12_24_MODE_24_HOUR )
  {
    myActualTime->bcd   =   ( cmd[2] & ( HOURS_24_HOUR_MODE_TEN_PLACE_MASK | HOURS_HOURS_UNIT_PLACE_MASK ) );
  }
  else
  {
    myActualTime->bcd        =   ( cmd[2] & ( HOURS_12_HOUR_MODE_TEN_PLACE_MASK | HOURS_HOURS_UNIT_PLACE_MASK ) );
    myActualTime->timeMode   =   (PCF8523_hours_ampm_t)( cmd[2] & HOURS_AMPM_MASK );
  }

  myActualTime->bcd <<=   8U;
  myActualTime->bcd  |=   ( cmd[1] & ( MINUTES_MINUTES_TEN_PLACE_MASK | MINUTES_MINUTES_UNIT_PLACE_MASK ) );
  myActualTime->bcd <<=   8U;
  myActualTime->bcd  |=   ( cmd[0] & ( SECONDS_SECONDS_TEN_PLACE_MASK | SECONDS_SECONDS_UNIT_PLACE_MASK ) );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_SetTime ( I2C_parameters_t , PCF8523_time_t )
 *
 * @details     It sets the time ( BCD format ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myNewTime:       New current time ( BCD format: HHMMSS ).
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_SetTime.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         This function also updates the 12h/24h mode.
 * @pre         This function makes use of the auto-incrementing function of the registers.
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_SetTime ( I2C_parameters_t myI2Cparameters, PCF8523_time_t myNewTime )
{
  uint8_t      cmd[4]  =  { 0U };
  i2c_status_t aux  = I2C_SUCCESS;
  PCF8523_status_t auxHourMode  = PCF8523_SUCCESS;

  /* Updates the 12h/24h mode   */
  auxHourMode |=   PCF8523_SetHourMode ( myI2Cparameters, myNewTime.hourMode );


  /* Read the register   */
  cmd[0]   =   PCF8523_SECONDS;
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read ( myI2Cparameters, &cmd[1], 3U );
  
  /* Mask it and update the register  */
  cmd[1]  &=  ~( SECONDS_SECONDS_TEN_PLACE_MASK | SECONDS_SECONDS_UNIT_PLACE_MASK );
  cmd[1]  |=   (uint8_t)( myNewTime.bcd & 0x0000FF );
  cmd[2]  &=  ~( MINUTES_MINUTES_TEN_PLACE_MASK | MINUTES_MINUTES_UNIT_PLACE_MASK );
  cmd[2]  |=   (uint8_t)( ( myNewTime.bcd & 0x00FF00 ) >> 8U );

  if ( myNewTime.hourMode == CONTROL_1_12_24_MODE_24_HOUR )
  {
    cmd[3]  &=  ~( HOURS_24_HOUR_MODE_TEN_PLACE_MASK | HOURS_HOURS_UNIT_PLACE_MASK );
  }
  else
  {
    auxHourMode |=   PCF8523_SetAM_PM_Indicator ( myI2Cparameters, myNewTime );
    cmd[3]      &=  ~( HOURS_12_HOUR_MODE_TEN_PLACE_MASK | HOURS_HOURS_UNIT_PLACE_MASK );
  }
  cmd[3]  |=   (uint8_t)( ( myNewTime.bcd & 0xFF0000 ) >> 16U );
  aux     |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




  if ( ( aux == I2C_SUCCESS ) && ( auxHourMode == PCF8523_SUCCESS ) )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_SetAM_PM_Indicator ( I2C_parameters_t , PCF8523_time_t )
 *
 * @details     It sets the AM/PM indicator ( only for 12-hour mode ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myAM_PM_Indicator: AM/PM indicator.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_SetAM_PM_Indicator.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     This function only works when the device is set for 12-hour mode, otherwise it
 *              will return FAILURE.
 */
PCF8523_status_t  PCF8523_SetAM_PM_Indicator ( I2C_parameters_t myI2Cparameters, PCF8523_time_t myAM_PM_Indicator )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux     =  I2C_SUCCESS;
  
  /* This function only works when the device is set for 12-hour mode  */
  if ( myAM_PM_Indicator.hourMode == CONTROL_1_12_24_MODE_24_HOUR )
  {
    return   PCF8523_FAILURE;
  }
  else
  {
    /* Read the register   */
    cmd[0]   =   PCF8523_HOURS;
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux     |=   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
    /* Mask it and update it with the new value  */
    cmd[1]   =   ( cmd[1] & ~HOURS_AMPM_MASK ) | myAM_PM_Indicator.timeMode;
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  }



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_GetAM_PM_Indicator ( I2C_parameters_t , PCF8523_time_t* )
 *
 * @details     It gets the AM/PM indicator ( only for 12-hour mode ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myAM_PM_Indicator: AM/PM indicator.
 *
 *
 * @return       Status of PCF8523_GetAM_PM_Indicator.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     This function only works when the device is set for 12-hour mode, otherwise it
 *              will return FAILURE.
 */
PCF8523_status_t  PCF8523_GetAM_PM_Indicator ( I2C_parameters_t myI2Cparameters, PCF8523_time_t* myAM_PM_Indicator )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux  =  I2C_SUCCESS;
  
  /* This function only works when the device is set for 12-hour mode  */
  if ( myAM_PM_Indicator->timeMode == CONTROL_1_12_24_MODE_24_HOUR )
  {
    return   PCF8523_FAILURE;
  }
  else
  {
    /* Read the register   */
    cmd      =   PCF8523_HOURS;
    aux     |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux     |=   i2c_read ( myI2Cparameters, &cmd, 1U );
  
    /* Parse the data  */
    myAM_PM_Indicator->timeMode  =   cmd;
  }



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_GetDay ( I2C_parameters_t , uint8_t* )
 *
 * @details     It gets the day ( BCD format ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myActualDay:     Current day.
 *
 *
 * @return       Status of PCF8523_GetDay.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_GetDay ( I2C_parameters_t myI2Cparameters, uint8_t* myActualDay )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux  =  I2C_SUCCESS;

  /* Read the register   */
  cmd      =   PCF8523_DAYS;
  aux     |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  *myActualDay  =   ( cmd & ( DAYS_DAYS_TEN_PLACE_MASK | DAYS_DAYS_UNIT_PLACE_MASK ) );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_SetDay ( I2C_parameters_t , uint8_t )
 *
 * @details     It sets the day ( BCD format ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myNewDay:        New day ( BCD format ).
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_SetDay.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_SetDay ( I2C_parameters_t myI2Cparameters, uint8_t myNewDay )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]   =   PCF8523_DAYS;
  cmd[1]   =   ( myNewDay & ( DAYS_DAYS_TEN_PLACE_MASK | DAYS_DAYS_UNIT_PLACE_MASK ) );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_GetWeekday ( I2C_parameters_t , PCF8523_weekdays_weekdays_t* )
 *
 * @details     It gets the weekday.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myActualWeekday: Current weekday.
 *
 *
 * @return       Status of PCF8523_GetWeekday.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_GetWeekday ( I2C_parameters_t myI2Cparameters, PCF8523_weekdays_weekdays_t* myActualWeekday )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux  =  I2C_SUCCESS;

  /* Read the register   */
  cmd      =   PCF8523_WEEKDAYS;
  aux     |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  *myActualWeekday  =   ( cmd & WEEKDAYS_WEEKDAYS_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_SetWeekday ( I2C_parameters_t , PCF8523_weekdays_weekdays_t )
 *
 * @details     It sets the weekday.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myNewWeekday:    New weekday.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_SetWeekday.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_SetWeekday ( I2C_parameters_t myI2Cparameters, PCF8523_weekdays_weekdays_t myNewWeekday )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]   =   PCF8523_WEEKDAYS;
  cmd[1]   =   myNewWeekday;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_GetMonth ( I2C_parameters_t , PCF8523_months_months_t* )
 *
 * @details     It gets the month ( BCD format ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myActualMonth:   Current month.
 *
 *
 * @return       Status of PCF8523_GetMonth.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_GetMonth ( I2C_parameters_t myI2Cparameters, PCF8523_months_months_t* myActualMonth )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux  =  I2C_SUCCESS;

  /* Read the register   */
  cmd      =   PCF8523_MONTHS;
  aux     |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  *myActualMonth  =   ( cmd & MONTHS_MONTHS_MASK );




  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_SetMonth ( I2C_parameters_t , PCF8523_months_months_t )
 *
 * @details     It sets the month ( BCD format ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myNewMonth:      New month.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_SetMonth.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_SetMonth ( I2C_parameters_t myI2Cparameters, PCF8523_months_months_t myNewMonth )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]   =   PCF8523_MONTHS;
  cmd[1]   =   myNewMonth;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_GetYear ( I2C_parameters_t , uint8_t* )
 *
 * @details     It gets the year ( BCD format ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myActualYear:    Current year.
 *
 *
 * @return       Status of PCF8523_GetYear.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_GetYear ( I2C_parameters_t myI2Cparameters, uint8_t* myActualYear )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux  =  I2C_SUCCESS;

  /* Read the register   */
  cmd      =   PCF8523_YEARS;
  aux     |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux     |=   i2c_read ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  *myActualYear  =   cmd;



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_SetYear ( I2C_parameters_t , uint8_t )
 *
 * @details     It sets the year ( BCD format ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myNewYear:       New year.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_SetYear.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_SetYear ( I2C_parameters_t myI2Cparameters, uint8_t myNewYear )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]   =   PCF8523_YEARS;
  cmd[1]   =   myNewYear;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_SetOffset ( I2C_parameters_t , PCF8523_offset_t )
 *
 * @details     It sets the offset.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myOFFSET:        Offset mode and Offset value: from +63 to -64.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF8523_SetOffset.
 *
 *
 * @author      Manuel Caballero
 * @date        03/February/2021
 * @version     03/February/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_SetOffset ( I2C_parameters_t myI2Cparameters, PCF8523_offset_t myOFFSET )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux     =  I2C_SUCCESS;
  
  /*  Check offset values  */
  if ( ( myOFFSET.value < -64 ) || ( myOFFSET.value > 63 ) )
  {
    return   PCF8523_FAILURE;
  }
  else
  {
    /* Read the register   */
    cmd[0]   =   PCF8523_OFFSET;
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux     |=   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
    /* Mask it and update it with the new value  */
    cmd[1]   =   ( cmd[1] & ~( OFFSET_MODE_MASK | 0b01111111 ) ) | ( myOFFSET.mode | myOFFSET.value );
    aux     |=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  }



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_GetOffset ( I2C_parameters_t , PCF8523_offset_t* )
 *
 * @details     It gets the offset values.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myOFFSET:        Offset mode and Offset value: from +63 to -64.
 *
 *
 * @return       Status of PCF8523_GetOffset.
 *
 *
 * @author      Manuel Caballero
 * @date        21/June/2021
 * @version     21/June/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_GetOffset ( I2C_parameters_t myI2Cparameters, PCF8523_offset_t* myOFFSET )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux  =  I2C_SUCCESS;
  
  /* Read the register   */
  cmd   =   PCF8523_OFFSET;
  aux  |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  |=   i2c_read ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myOFFSET->mode   =  (PCF8523_offset_mode_t)( cmd & OFFSET_MODE_MASK );
  myOFFSET->value  =  ( cmd & 0x7F );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}



/**
 * @brief       PCF8523_GetClockIntegrityFlag ( I2C_parameters_t , PCF8523_seconds_os_t* )
 *
 * @details     It gets the clock integrity flag.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myOS:            Clock integrity flag.
 *
 *
 * @return       Status of PCF8523_GetClockIntegrityFlag.
 *
 *
 * @author      Manuel Caballero
 * @date        21/June/2021
 * @version     21/June/2021     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF8523_status_t  PCF8523_GetClockIntegrityFlag ( I2C_parameters_t myI2Cparameters, PCF8523_seconds_os_t* myOS )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux  =  I2C_SUCCESS;
  
  /* Read the register   */
  cmd   =   PCF8523_SECONDS;
  aux  |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  |=   i2c_read ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  *myOS  =  (PCF8523_seconds_os_t)( cmd & SECONDS_OS_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF8523_SUCCESS;
  }
  else
  {
    return   PCF8523_FAILURE;
  }
}

