/**
 * @brief       PCF85063.c
 * @details     Tiny Real-Time Clock/calendar.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/January/2019
 * @version     22/January/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ). All rights reserved.
 */

#include "PCF85063.h"


/**
 * @brief       PCF85063_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF85063_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        22/January/2019
 * @version     22/January/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_Init ( I2C_parameters_t myI2Cparameters )
{
  i2c_status_t aux;

  aux  =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_SetTestMode ( I2C_parameters_t , PCF85063_control_1_ext_test_t )
 *
 * @details     It sets the external clock test mod.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myEXT_TEST:        External clock test mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF85063_SetTestMode.
 *
 *
 * @author      Manuel Caballero
 * @date        23/January/2019
 * @version     23/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_SetTestMode ( I2C_parameters_t myI2Cparameters, PCF85063_control_1_ext_test_t myEXT_TEST )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF85063_CONTROL_1;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~CONTROL_1_EXT_TEST_MASK ) | myEXT_TEST );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_SetRTCMode ( I2C_parameters_t , PCF85063_control_1_stop_t )
 *
 * @details     It sets the RTC clock mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    mySTOP:          External clock test mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF85063_SetRTCMode.
 *
 *
 * @author      Manuel Caballero
 * @date        23/January/2019
 * @version     23/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_SetRTCMode ( I2C_parameters_t myI2Cparameters, PCF85063_control_1_stop_t mySTOP )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF85063_CONTROL_1;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~CONTROL_1_STOP_MASK ) | mySTOP );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_SoftwareReset ( I2C_parameters_t )
 *
 * @details     It performs a software reset.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF85063_SoftwareReset.
 *
 *
 * @author      Manuel Caballero
 * @date        23/January/2019
 * @version     23/January/2019     The ORIGIN
 * @pre         For a software reset, 01011000 (58h) must be sent to register Control_1. Datasheet p6, 
 *              Table 6. Control_1 - control and status register 1 (address 00h) bit description.
 *
 *              The PCF85063TP resets to:
 *                -Time    — 00:00:00
 *                -Date    — 20000101
 *                -Weekday — Saturday
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_SoftwareReset ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]   =   PCF85063_CONTROL_1;
  cmd[1]   =   0x58;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_SetCorrectionInterruptMode ( I2C_parameters_t , PCF85063_control_1_cie_t )
 *
 * @details     It sets the correction interrupt mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myCIE:           Correction interrupt enable.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF85063_SetCorrectionInterruptMode.
 *
 *
 * @author      Manuel Caballero
 * @date        23/January/2019
 * @version     23/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_SetCorrectionInterruptMode ( I2C_parameters_t myI2Cparameters, PCF85063_control_1_cie_t myCIE )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF85063_CONTROL_1;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~CONTROL_1_CIE_MASK ) | myCIE );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_Set12_24_HourMode ( I2C_parameters_t , PCF85063_control_1_12_24_t )
 *
 * @details     It sets 12 or 24 hour mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    my12_24:         12 or 24 hour mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF85063_Set12_24_HourMode.
 *
 *
 * @author      Manuel Caballero
 * @date        23/January/2019
 * @version     23/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_Set12_24_HourMode ( I2C_parameters_t myI2Cparameters, PCF85063_control_1_12_24_t my12_24 )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF85063_CONTROL_1;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~CONTROL_1_12_24_MASK ) | my12_24 );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_SetInternalOscillatorCapacitor ( I2C_parameters_t , PCF85063_control_1_cap_sel_t )
 *
 * @details     It sets the internal oscillator capacitor.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myCAP_SEL:       Internal oscillator capacitor selection.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF85063_SetInternalOscillatorCapacitor.
 *
 *
 * @author      Manuel Caballero
 * @date        23/January/2019
 * @version     23/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_SetInternalOscillatorCapacitor ( I2C_parameters_t myI2Cparameters, PCF85063_control_1_cap_sel_t myCAP_SEL )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF85063_CONTROL_1;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~CONTROL_1_CAP_SEL_MASK ) | myCAP_SEL );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_SetMinuteInterrupts ( I2C_parameters_t , PCF85063_control_2_mi_t , PCF85063_control_2_hmi_t )
 *
 * @details     It enables/disables minute/half minute interrupt.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myMI:            Minute interrupt.
 * @param[in]    myHMI:           Half minute interrupt.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF85063_SetMinuteInterrupts.
 *
 *
 * @author      Manuel Caballero
 * @date        23/January/2019
 * @version     23/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_SetMinuteInterrupts ( I2C_parameters_t myI2Cparameters, PCF85063_control_2_mi_t myMI, PCF85063_control_2_hmi_t myHMI )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF85063_CONTROL_2;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update it with the new value  */
  cmd[1]   =   ( ( cmd[1] & ~( CONTROL_2_MI_MASK | CONTROL_2_HMI_MASK ) ) | myMI | myHMI );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_GetTimerFlag ( I2C_parameters_t , PCF85063_control_2_tf_t* )
 *
 * @details     It gets the status of the timer flag.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myTF:            Timer flag.
 *
 *
 * @return       Status of PCF85063_GetTimerFlag.
 *
 *
 * @author      Manuel Caballero
 * @date        23/January/2019
 * @version     23/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_GetTimerFlag ( I2C_parameters_t myI2Cparameters, PCF85063_control_2_tf_t* myTF )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd      =   PCF85063_CONTROL_2;
  aux      =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  *myTF  =   ( cmd & CONTROL_2_TF_MASK );




  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_ClearTimerFlag ( I2C_parameters_t )
 *
 * @details     It resets the status of the timer flag.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF85063_ClearTimerFlag.
 *
 *
 * @author      Manuel Caballero
 * @date        23/January/2019
 * @version     23/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_ClearTimerFlag ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF85063_CONTROL_2;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update it with the new value  */
  cmd[1]   =   ( cmd[1] & ~CONTROL_2_TF_MASK );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_SetClockOutputFrequency ( I2C_parameters_t , PCF85063_control_2_cof_t )
 *
 * @details     It sets the clock output frequency.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myCOF:           CLKOUT control.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF85063_SetClockOutputFrequency.
 *
 *
 * @author      Manuel Caballero
 * @date        23/January/2019
 * @version     23/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_SetClockOutputFrequency ( I2C_parameters_t myI2Cparameters, PCF85063_control_2_cof_t myCOF )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF85063_CONTROL_2;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update it with the new value  */
  cmd[1]   =   ( cmd[1] & ~CONTROL_2_COF_MASK ) | myCOF;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_SetOffset ( I2C_parameters_t , PCF85063_offset_mode_t , int8_t )
 *
 * @details     It sets the offset.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myMODE:          Offset mode.
 * @param[in]    myOFFSET:        from +63 to -64.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF85063_SetOffset.
 *
 *
 * @author      Manuel Caballero
 * @date        23/January/2019
 * @version     23/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_SetOffset ( I2C_parameters_t myI2Cparameters, PCF85063_offset_mode_t myMODE, int8_t myOFFSET )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;
  
  /*  Check offset values  */
  if ( ( myOFFSET < -64 ) || ( myOFFSET > 63 ) )
  {
    return   PCF85063_FAILURE;
  }
  else
  {
    /* Read the register   */
    cmd[0]   =   PCF85063_OFFSET;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
    /* Mask it and update it with the new value  */
    cmd[1]   =   ( cmd[1] & ~( OFFSET_MODE_MASK | 0b01111111 ) ) | ( myMODE | myOFFSET );
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  }



  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_WriteByteRAM ( I2C_parameters_t , int8_t )
 *
 * @details     It writes into the RAM byte register.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myData:          Data to be written in the RAM byte register.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF85063_WriteByteRAM.
 *
 *
 * @author      Manuel Caballero
 * @date        23/January/2019
 * @version     23/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_WriteByteRAM ( I2C_parameters_t myI2Cparameters, int8_t myData )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]   =   PCF85063_RAM_BYTE;
  cmd[1]   =   myData;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_ReadByteRAM ( I2C_parameters_t , int8_t* )
 *
 * @details     It writes into the RAM byte register.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myData:          Data to be read from the RAM byte register.
 *
 *
 * @return       Status of PCF85063_ReadByteRAM.
 *
 *
 * @author      Manuel Caballero
 * @date        23/January/2019
 * @version     23/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_ReadByteRAM ( I2C_parameters_t myI2Cparameters, int8_t* myData )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd      =   PCF85063_RAM_BYTE;
  aux      =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  *myData   =   cmd;




  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_CheckOscillatorClockIntegrityFlag ( I2C_parameters_t , PCF85063_seconds_os_t* )
 *
 * @details     It checks oscillator clock integrity flag.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myOS:            CLKOUT control.
 *
 *
 * @return       Status of PCF85063_CheckOscillatorClockIntegrityFlag.
 *
 *
 * @author      Manuel Caballero
 * @date        23/January/2019
 * @version     23/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_CheckOscillatorClockIntegrityFlag ( I2C_parameters_t myI2Cparameters, PCF85063_seconds_os_t* myOS )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd      =   PCF85063_SECONDS;
  aux      =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  *myOS   =   cmd;




  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_ClearOscillatorClockIntegrityFlag ( I2C_parameters_t )
 *
 * @details     It clears oscillator clock integrity flag.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF85063_ClearOscillatorClockIntegrityFlag.
 *
 *
 * @author      Manuel Caballero
 * @date        23/January/2019
 * @version     23/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_ClearOscillatorClockIntegrityFlag ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]   =   PCF85063_SECONDS;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
  /* Mask it and update it with the new value  */
  cmd[1]   =   ( cmd[1] & ~SECONDS_OS_MASK );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_SetAM_PM_Indicator ( I2C_parameters_t , PCF85063_data_t )
 *
 * @details     It sets the AM/PM indicator ( only for 12-hour mode ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myAM_PM_Indicator: AM/PM indicator.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF85063_SetAM_PM_Indicator.
 *
 *
 * @author      Manuel Caballero
 * @date        23/January/2019
 * @version     23/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     This function only works when the device is set for 12-hour mode, otherwise it
 *              will return FAILURE.
 */
PCF85063_status_t  PCF85063_SetAM_PM_Indicator ( I2C_parameters_t myI2Cparameters, PCF85063_data_t myAM_PM_Indicator )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;
  
  /* This function only works when the device is set for 12-hour mode  */
  if ( myAM_PM_Indicator.Time12H_24HMode == CONTROL_1_12_24_24_HOUR_MODE )
  {
    return   PCF85063_FAILURE;
  }
  else
  {
    /* Read the register   */
    cmd[0]   =   PCF85063_HOURS;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read ( myI2Cparameters, &cmd[1], 1U );
  
    /* Mask it and update it with the new value  */
    cmd[1]   =   ( cmd[1] & ~HOURS_AMPM_MASK ) | myAM_PM_Indicator.TimeAM_PM_Mode;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  }



  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_GetAM_PM_Indicator ( I2C_parameters_t , PCF85063_data_t* )
 *
 * @details     It gets the AM/PM indicator ( only for 12-hour mode ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myAM_PM_Indicator: AM/PM indicator.
 *
 *
 * @return       Status of PCF85063_GetAM_PM_Indicator.
 *
 *
 * @author      Manuel Caballero
 * @date        23/January/2019
 * @version     23/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     This function only works when the device is set for 12-hour mode, otherwise it
 *              will return FAILURE.
 */
PCF85063_status_t  PCF85063_GetAM_PM_Indicator ( I2C_parameters_t myI2Cparameters, PCF85063_data_t* myAM_PM_Indicator )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux;
  
  /* This function only works when the device is set for 12-hour mode  */
  if ( myAM_PM_Indicator->Time12H_24HMode == CONTROL_1_12_24_24_HOUR_MODE )
  {
    return   PCF85063_FAILURE;
  }
  else
  {
    /* Read the register   */
    cmd      =   PCF85063_HOURS;
    aux      =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
    aux      =   i2c_read ( myI2Cparameters, &cmd, 1U );
  
    /* Parse the data  */
    myAM_PM_Indicator->TimeAM_PM_Mode  =   cmd;
  }



  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_GetDay ( I2C_parameters_t , PCF85063_data_t* )
 *
 * @details     It gets the day ( BCD format ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myActualDay:     Current day.
 *
 *
 * @return       Status of PCF85063_GetDay.
 *
 *
 * @author      Manuel Caballero
 * @date        24/January/2019
 * @version     24/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_GetDay ( I2C_parameters_t myI2Cparameters, PCF85063_data_t* myActualDay )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd      =   PCF85063_DAYS;
  aux      =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myActualDay->BCDday  =   ( cmd & ( DAYS_DAYS_TEN_PLACE_MASK | DAYS_DAYS_UNIT_PLACE_MASK ) );




  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_SetDay ( I2C_parameters_t , PCF85063_data_t )
 *
 * @details     It sets the day ( BCD format ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myNewDay:        New day ( BCD format ).
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF85063_SetDay.
 *
 *
 * @author      Manuel Caballero
 * @date        24/January/2019
 * @version     24/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_SetDay ( I2C_parameters_t myI2Cparameters, PCF85063_data_t myNewDay )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]   =   PCF85063_DAYS;
  cmd[1]   =   ( myNewDay.BCDday & ( DAYS_DAYS_TEN_PLACE_MASK | DAYS_DAYS_UNIT_PLACE_MASK ) );
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_GetWeekday ( I2C_parameters_t , PCF85063_data_t* )
 *
 * @details     It gets the weekday.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myActualWeekday: Current weekday.
 *
 *
 * @return       Status of PCF85063_GetWeekday.
 *
 *
 * @author      Manuel Caballero
 * @date        24/January/2019
 * @version     24/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_GetWeekday ( I2C_parameters_t myI2Cparameters, PCF85063_data_t* myActualWeekday )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd      =   PCF85063_WEEKDAYS;
  aux      =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myActualWeekday->weekday  =   ( cmd & WEEKDAYS_WEEKDAYS_MASK );




  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_SetWeekday ( I2C_parameters_t , PCF85063_data_t )
 *
 * @details     It sets the weekday.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myNewWeekday:    New weekday.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF85063_SetWeekday.
 *
 *
 * @author      Manuel Caballero
 * @date        24/January/2019
 * @version     24/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_SetWeekday ( I2C_parameters_t myI2Cparameters, PCF85063_data_t myNewWeekday )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]   =   PCF85063_WEEKDAYS;
  cmd[1]   =   myNewWeekday.weekday;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_GetMonth ( I2C_parameters_t , PCF85063_data_t* )
 *
 * @details     It gets the month ( BCD format ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myActualMonth:   Current month.
 *
 *
 * @return       Status of PCF85063_GetMonth.
 *
 *
 * @author      Manuel Caballero
 * @date        24/January/2019
 * @version     24/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_GetMonth ( I2C_parameters_t myI2Cparameters, PCF85063_data_t* myActualMonth )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd      =   PCF85063_MONTHS;
  aux      =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myActualMonth->BCDmonth  =   ( cmd & MONTHS_MONTHS_MASK );




  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_SetMonth ( I2C_parameters_t , PCF85063_data_t )
 *
 * @details     It sets the month ( BCD format ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myNewMonth:      New month.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF85063_SetMonth.
 *
 *
 * @author      Manuel Caballero
 * @date        24/January/2019
 * @version     24/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_SetMonth ( I2C_parameters_t myI2Cparameters, PCF85063_data_t myNewMonth )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]   =   PCF85063_MONTHS;
  cmd[1]   =   myNewMonth.BCDmonth;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_GetYear ( I2C_parameters_t , PCF85063_data_t* )
 *
 * @details     It gets the year ( BCD format ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myActualYear:    Current year.
 *
 *
 * @return       Status of PCF85063_GetYear.
 *
 *
 * @author      Manuel Caballero
 * @date        24/January/2019
 * @version     24/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_GetYear ( I2C_parameters_t myI2Cparameters, PCF85063_data_t* myActualYear )
{
  uint8_t      cmd  =  0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd      =   PCF85063_YEARS;
  aux      =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux      =   i2c_read ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data  */
  myActualYear->BCDyear  =   cmd;




  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}



/**
 * @brief       PCF85063_SetYear ( I2C_parameters_t , PCF85063_data_t )
 *
 * @details     It sets the year ( BCD format ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myNewYear:       New year.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF85063_SetYear.
 *
 *
 * @author      Manuel Caballero
 * @date        24/January/2019
 * @version     24/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_SetYear ( I2C_parameters_t myI2Cparameters, PCF85063_data_t myNewYear )
{
  uint8_t      cmd[2]  =  { 0U };
  i2c_status_t aux;

  /* Update the register   */
  cmd[0]   =   PCF85063_YEARS;
  cmd[1]   =   myNewYear.BCDyear;
  aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




  if ( aux == I2C_SUCCESS )
  {
    return   PCF85063_SUCCESS;
  }
  else
  {
    return   PCF85063_FAILURE;
  }
}