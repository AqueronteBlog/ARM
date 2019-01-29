/**
 * @brief       SX128X.c
 * @details     SX1280/SX1281. Long Range, Low Power, 2.4 GHz Transceiver with Ranging Capability.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        29/January/2019
 * @version     29/January/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ). All rights reserved.
 */

#include "SX128X.h"


/**
 * @brief       SX128X_Init ( SPI_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    mySPI_parameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SX128X_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        22/January/2019
 * @version     22/January/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SX128X_status_t  SX128X_Init ( SPI_parameters_t mySPI_parameters )
{
  spi_status_t aux;

  aux  =   i2c_init ( mySPI_parameters );



  if ( aux == SPI_SUCCESS )
  {
    return   SX128X_SUCCESS;
  }
  else
  {
    return   SX128X_FAILURE;
  }
}



///**
// * @brief       SX128X_SetTestMode ( SPI_parameters_t , SX128X_control_1_ext_test_t )
// *
// * @details     It sets the external clock test mod.
// *
// * @param[in]    mySPI_parameters:   I2C parameters.
// * @param[in]    myEXT_TEST:        External clock test mode.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SX128X_SetTestMode.
// *
// *
// * @author      Manuel Caballero
// * @date        23/January/2019
// * @version     23/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_SetTestMode ( SPI_parameters_t mySPI_parameters, SX128X_control_1_ext_test_t myEXT_TEST )
//{
//  uint8_t      cmd[2]  = { 0U };
//  spi_status_t aux;
//
//  /* Read the register   */
//  cmd[0]   =   SX128X_CONTROL_1;
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
//  aux      =   i2c_read ( mySPI_parameters, &cmd[1], 1U );
//
//  /* Mask it and update it with the new value  */
//  cmd[1]   =   ( ( cmd[1] & ~CONTROL_1_EXT_TEST_MASK ) | myEXT_TEST );
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_SetRTCMode ( SPI_parameters_t , SX128X_control_1_stop_t )
// *
// * @details     It sets the RTC clock mode.
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// * @param[in]    mySTOP:          External clock test mode.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SX128X_SetRTCMode.
// *
// *
// * @author      Manuel Caballero
// * @date        23/January/2019
// * @version     23/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_SetRTCMode ( SPI_parameters_t mySPI_parameters, SX128X_control_1_stop_t mySTOP )
//{
//  uint8_t      cmd[2]  = { 0U };
//  spi_status_t aux;
//
//  /* Read the register   */
//  cmd[0]   =   SX128X_CONTROL_1;
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
//  aux      =   i2c_read ( mySPI_parameters, &cmd[1], 1U );
//
//  /* Mask it and update it with the new value  */
//  cmd[1]   =   ( ( cmd[1] & ~CONTROL_1_STOP_MASK ) | mySTOP );
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_SoftwareReset ( SPI_parameters_t )
// *
// * @details     It performs a software reset.
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SX128X_SoftwareReset.
// *
// *
// * @author      Manuel Caballero
// * @date        23/January/2019
// * @version     23/January/2019     The ORIGIN
// * @pre         For a software reset, 01011000 (58h) must be sent to register Control_1. Datasheet p6,
// *              Table 6. Control_1 - control and status register 1 (address 00h) bit description.
// *
// *              The SX128XTP resets to:
// *                -Time    — 00:00:00
// *                -Date    — 20000101
// *                -Weekday — Saturday
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_SoftwareReset ( SPI_parameters_t mySPI_parameters )
//{
//  uint8_t      cmd[2]  = { 0U };
//  spi_status_t aux;
//
//  /* Update the register   */
//  cmd[0]   =   SX128X_CONTROL_1;
//  cmd[1]   =   0x58;
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_SetCorrectionInterruptMode ( SPI_parameters_t , SX128X_control_1_cie_t )
// *
// * @details     It sets the correction interrupt mode.
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// * @param[in]    myCIE:           Correction interrupt enable.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SX128X_SetCorrectionInterruptMode.
// *
// *
// * @author      Manuel Caballero
// * @date        23/January/2019
// * @version     23/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_SetCorrectionInterruptMode ( SPI_parameters_t mySPI_parameters, SX128X_control_1_cie_t myCIE )
//{
//  uint8_t      cmd[2]  = { 0U };
//  spi_status_t aux;
//
//  /* Read the register   */
//  cmd[0]   =   SX128X_CONTROL_1;
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
//  aux      =   i2c_read ( mySPI_parameters, &cmd[1], 1U );
//
//  /* Mask it and update it with the new value  */
//  cmd[1]   =   ( ( cmd[1] & ~CONTROL_1_CIE_MASK ) | myCIE );
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_Set12_24_HourMode ( SPI_parameters_t , SX128X_data_t )
// *
// * @details     It sets 12 or 24 hour mode.
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// * @param[in]    my12_24:         12 or 24 hour mode.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SX128X_Set12_24_HourMode.
// *
// *
// * @author      Manuel Caballero
// * @date        23/January/2019
// * @version     23/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_Set12_24_HourMode ( SPI_parameters_t mySPI_parameters, SX128X_data_t my12_24 )
//{
//  uint8_t      cmd[2]  = { 0U };
//  spi_status_t aux;
//
//  /* Read the register   */
//  cmd[0]   =   SX128X_CONTROL_1;
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
//  aux      =   i2c_read ( mySPI_parameters, &cmd[1], 1U );
//
//  /* Mask it and update it with the new value  */
//  cmd[1]   =   ( ( cmd[1] & ~CONTROL_1_12_24_MASK ) | my12_24.Time12H_24HMode );
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_SetInternalOscillatorCapacitor ( SPI_parameters_t , SX128X_control_1_cap_sel_t )
// *
// * @details     It sets the internal oscillator capacitor.
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// * @param[in]    myCAP_SEL:       Internal oscillator capacitor selection.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SX128X_SetInternalOscillatorCapacitor.
// *
// *
// * @author      Manuel Caballero
// * @date        23/January/2019
// * @version     23/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_SetInternalOscillatorCapacitor ( SPI_parameters_t mySPI_parameters, SX128X_control_1_cap_sel_t myCAP_SEL )
//{
//  uint8_t      cmd[2]  = { 0U };
//  spi_status_t aux;
//
//  /* Read the register   */
//  cmd[0]   =   SX128X_CONTROL_1;
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
//  aux      =   i2c_read ( mySPI_parameters, &cmd[1], 1U );
//
//  /* Mask it and update it with the new value  */
//  cmd[1]   =   ( ( cmd[1] & ~CONTROL_1_CAP_SEL_MASK ) | myCAP_SEL );
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_SetMinuteInterrupts ( SPI_parameters_t , SX128X_control_2_mi_t , SX128X_control_2_hmi_t )
// *
// * @details     It enables/disables minute/half minute interrupt.
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// * @param[in]    myMI:            Minute interrupt.
// * @param[in]    myHMI:           Half minute interrupt.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SX128X_SetMinuteInterrupts.
// *
// *
// * @author      Manuel Caballero
// * @date        23/January/2019
// * @version     23/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_SetMinuteInterrupts ( SPI_parameters_t mySPI_parameters, SX128X_control_2_mi_t myMI, SX128X_control_2_hmi_t myHMI )
//{
//  uint8_t      cmd[2]  = { 0U };
//  spi_status_t aux;
//
//  /* Read the register   */
//  cmd[0]   =   SX128X_CONTROL_2;
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
//  aux      =   i2c_read ( mySPI_parameters, &cmd[1], 1U );
//
//  /* Mask it and update it with the new value  */
//  cmd[1]   =   ( ( cmd[1] & ~( CONTROL_2_MI_MASK | CONTROL_2_HMI_MASK ) ) | myMI | myHMI );
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_GetTimerFlag ( SPI_parameters_t , SX128X_control_2_tf_t* )
// *
// * @details     It gets the status of the timer flag.
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// *
// * @param[out]   myTF:            Timer flag.
// *
// *
// * @return       Status of SX128X_GetTimerFlag.
// *
// *
// * @author      Manuel Caballero
// * @date        23/January/2019
// * @version     23/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_GetTimerFlag ( SPI_parameters_t mySPI_parameters, SX128X_control_2_tf_t* myTF )
//{
//  uint8_t      cmd  = 0U;
//  spi_status_t aux;
//
//  /* Read the register   */
//  cmd      =   SX128X_CONTROL_2;
//  aux      =   i2c_write ( mySPI_parameters, &cmd, 1U, I2C_NO_STOP_BIT );
//  aux      =   i2c_read ( mySPI_parameters, &cmd, 1U );
//
//  /* Parse the data  */
//  *myTF  =   ( cmd & CONTROL_2_TF_MASK );
//
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_ClearTimerFlag ( SPI_parameters_t )
// *
// * @details     It resets the status of the timer flag.
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SX128X_ClearTimerFlag.
// *
// *
// * @author      Manuel Caballero
// * @date        23/January/2019
// * @version     23/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_ClearTimerFlag ( SPI_parameters_t mySPI_parameters )
//{
//  uint8_t      cmd[2]  =  { 0U };
//  spi_status_t aux;
//
//  /* Read the register   */
//  cmd[0]   =   SX128X_CONTROL_2;
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
//  aux      =   i2c_read ( mySPI_parameters, &cmd[1], 1U );
//
//  /* Mask it and update it with the new value  */
//  cmd[1]   =   ( cmd[1] & ~CONTROL_2_TF_MASK );
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_SetClockOutputFrequency ( SPI_parameters_t , SX128X_control_2_cof_t )
// *
// * @details     It sets the clock output frequency.
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// * @param[in]    myCOF:           CLKOUT control.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SX128X_SetClockOutputFrequency.
// *
// *
// * @author      Manuel Caballero
// * @date        23/January/2019
// * @version     23/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_SetClockOutputFrequency ( SPI_parameters_t mySPI_parameters, SX128X_control_2_cof_t myCOF )
//{
//  uint8_t      cmd[2]  =  { 0U };
//  spi_status_t aux;
//
//  /* Read the register   */
//  cmd[0]   =   SX128X_CONTROL_2;
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
//  aux      =   i2c_read ( mySPI_parameters, &cmd[1], 1U );
//
//  /* Mask it and update it with the new value  */
//  cmd[1]   =   ( cmd[1] & ~CONTROL_2_COF_MASK ) | myCOF;
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_SetOffset ( SPI_parameters_t , SX128X_offset_mode_t , int8_t )
// *
// * @details     It sets the offset.
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// * @param[in]    myMODE:          Offset mode.
// * @param[in]    myOFFSET:        from +63 to -64.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SX128X_SetOffset.
// *
// *
// * @author      Manuel Caballero
// * @date        23/January/2019
// * @version     23/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_SetOffset ( SPI_parameters_t mySPI_parameters, SX128X_offset_mode_t myMODE, int8_t myOFFSET )
//{
//  uint8_t      cmd[2]  =  { 0U };
//  spi_status_t aux;
//
//  /*  Check offset values  */
//  if ( ( myOFFSET < -64 ) || ( myOFFSET > 63 ) )
//  {
//    return   SX128X_FAILURE;
//  }
//  else
//  {
//    /* Read the register   */
//    cmd[0]   =   SX128X_OFFSET;
//    aux      =   i2c_write ( mySPI_parameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
//    aux      =   i2c_read ( mySPI_parameters, &cmd[1], 1U );
//
//    /* Mask it and update it with the new value  */
//    cmd[1]   =   ( cmd[1] & ~( OFFSET_MODE_MASK | 0b01111111 ) ) | ( myMODE | myOFFSET );
//    aux      =   i2c_write ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//  }
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_WriteByteRAM ( SPI_parameters_t , SX128X_data_t )
// *
// * @details     It writes into the RAM byte register.
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// * @param[in]    myData:          Data to be written in the RAM byte register.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SX128X_WriteByteRAM.
// *
// *
// * @author      Manuel Caballero
// * @date        23/January/2019
// * @version     23/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_WriteByteRAM ( SPI_parameters_t mySPI_parameters, SX128X_data_t myData )
//{
//  uint8_t      cmd[2]  =  { 0U };
//  spi_status_t aux;
//
//  /* Update the register   */
//  cmd[0]   =   SX128X_RAM_BYTE;
//  cmd[1]   =   myData.ramByte;
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_ReadByteRAM ( SPI_parameters_t , SX128X_data_t* )
// *
// * @details     It writes into the RAM byte register.
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// *
// * @param[out]   myData:          Data to be read from the RAM byte register.
// *
// *
// * @return       Status of SX128X_ReadByteRAM.
// *
// *
// * @author      Manuel Caballero
// * @date        23/January/2019
// * @version     23/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_ReadByteRAM ( SPI_parameters_t mySPI_parameters, SX128X_data_t* myData )
//{
//  uint8_t      cmd  =  0U;
//  spi_status_t aux;
//
//  /* Read the register   */
//  cmd      =   SX128X_RAM_BYTE;
//  aux      =   i2c_write ( mySPI_parameters, &cmd, 1U, I2C_NO_STOP_BIT );
//  aux      =   i2c_read ( mySPI_parameters, &cmd, 1U );
//
//  /* Parse the data  */
//  myData->ramByte   =   cmd;
//
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_CheckOscillatorClockIntegrityFlag ( SPI_parameters_t , SX128X_data_t* )
// *
// * @details     It checks oscillator clock integrity flag.
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// *
// * @param[out]   myOS:            CLKOUT control.
// *
// *
// * @return       Status of SX128X_CheckOscillatorClockIntegrityFlag.
// *
// *
// * @author      Manuel Caballero
// * @date        23/January/2019
// * @version     23/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_CheckOscillatorClockIntegrityFlag ( SPI_parameters_t mySPI_parameters, SX128X_data_t* myOS )
//{
//  uint8_t      cmd  =  0U;
//  spi_status_t aux;
//
//  /* Read the register   */
//  cmd      =   SX128X_SECONDS;
//  aux      =   i2c_write ( mySPI_parameters, &cmd, 1U, I2C_NO_STOP_BIT );
//  aux      =   i2c_read ( mySPI_parameters, &cmd, 1U );
//
//  /* Parse the data  */
//  myOS->os   =   cmd;
//
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_ClearOscillatorClockIntegrityFlag ( SPI_parameters_t )
// *
// * @details     It clears oscillator clock integrity flag.
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SX128X_ClearOscillatorClockIntegrityFlag.
// *
// *
// * @author      Manuel Caballero
// * @date        23/January/2019
// * @version     23/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_ClearOscillatorClockIntegrityFlag ( SPI_parameters_t mySPI_parameters )
//{
//  uint8_t      cmd[2]  =  { 0U };
//  spi_status_t aux;
//
//  /* Read the register   */
//  cmd[0]   =   SX128X_SECONDS;
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
//  aux      =   i2c_read ( mySPI_parameters, &cmd[1], 1U );
//
//  /* Mask it and update it with the new value  */
//  cmd[1]   =   ( cmd[1] & ~SECONDS_OS_MASK );
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_SetAM_PM_Indicator ( SPI_parameters_t , SX128X_data_t )
// *
// * @details     It sets the AM/PM indicator ( only for 12-hour mode ).
// *
// * @param[in]    mySPI_parameters:   I2C parameters.
// * @param[in]    myAM_PM_Indicator: AM/PM indicator.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SX128X_SetAM_PM_Indicator.
// *
// *
// * @author      Manuel Caballero
// * @date        23/January/2019
// * @version     23/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     This function only works when the device is set for 12-hour mode, otherwise it
// *              will return FAILURE.
// */
//SX128X_status_t  SX128X_SetAM_PM_Indicator ( SPI_parameters_t mySPI_parameters, SX128X_data_t myAM_PM_Indicator )
//{
//  uint8_t      cmd[2]  =  { 0U };
//  spi_status_t aux;
//
//  /* This function only works when the device is set for 12-hour mode  */
//  if ( myAM_PM_Indicator.Time12H_24HMode == CONTROL_1_12_24_24_HOUR_MODE )
//  {
//    return   SX128X_FAILURE;
//  }
//  else
//  {
//    /* Read the register   */
//    cmd[0]   =   SX128X_HOURS;
//    aux      =   i2c_write ( mySPI_parameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
//    aux      =   i2c_read ( mySPI_parameters, &cmd[1], 1U );
//
//    /* Mask it and update it with the new value  */
//    cmd[1]   =   ( cmd[1] & ~HOURS_AMPM_MASK ) | myAM_PM_Indicator.TimeAM_PM_Mode;
//    aux      =   i2c_write ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//  }
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_GetAM_PM_Indicator ( SPI_parameters_t , SX128X_data_t* )
// *
// * @details     It gets the AM/PM indicator ( only for 12-hour mode ).
// *
// * @param[in]    mySPI_parameters:   I2C parameters.
// *
// * @param[out]   myAM_PM_Indicator: AM/PM indicator.
// *
// *
// * @return       Status of SX128X_GetAM_PM_Indicator.
// *
// *
// * @author      Manuel Caballero
// * @date        23/January/2019
// * @version     23/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     This function only works when the device is set for 12-hour mode, otherwise it
// *              will return FAILURE.
// */
//SX128X_status_t  SX128X_GetAM_PM_Indicator ( SPI_parameters_t mySPI_parameters, SX128X_data_t* myAM_PM_Indicator )
//{
//  uint8_t      cmd  =  0U;
//  spi_status_t aux;
//
//  /* This function only works when the device is set for 12-hour mode  */
//  if ( myAM_PM_Indicator->Time12H_24HMode == CONTROL_1_12_24_24_HOUR_MODE )
//  {
//    return   SX128X_FAILURE;
//  }
//  else
//  {
//    /* Read the register   */
//    cmd      =   SX128X_HOURS;
//    aux      =   i2c_write ( mySPI_parameters, &cmd, 1U, I2C_NO_STOP_BIT );
//    aux      =   i2c_read ( mySPI_parameters, &cmd, 1U );
//
//    /* Parse the data  */
//    myAM_PM_Indicator->TimeAM_PM_Mode  =   cmd;
//  }
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_GetDay ( SPI_parameters_t , SX128X_data_t* )
// *
// * @details     It gets the day ( BCD format ).
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// *
// * @param[out]   myActualDay:     Current day.
// *
// *
// * @return       Status of SX128X_GetDay.
// *
// *
// * @author      Manuel Caballero
// * @date        24/January/2019
// * @version     24/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_GetDay ( SPI_parameters_t mySPI_parameters, SX128X_data_t* myActualDay )
//{
//  uint8_t      cmd  =  0U;
//  spi_status_t aux;
//
//  /* Read the register   */
//  cmd      =   SX128X_DAYS;
//  aux      =   i2c_write ( mySPI_parameters, &cmd, 1U, I2C_NO_STOP_BIT );
//  aux      =   i2c_read ( mySPI_parameters, &cmd, 1U );
//
//  /* Parse the data  */
//  myActualDay->BCDday  =   ( cmd & ( DAYS_DAYS_TEN_PLACE_MASK | DAYS_DAYS_UNIT_PLACE_MASK ) );
//
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_SetDay ( SPI_parameters_t , SX128X_data_t )
// *
// * @details     It sets the day ( BCD format ).
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// * @param[in]    myNewDay:        New day ( BCD format ).
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SX128X_SetDay.
// *
// *
// * @author      Manuel Caballero
// * @date        24/January/2019
// * @version     24/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_SetDay ( SPI_parameters_t mySPI_parameters, SX128X_data_t myNewDay )
//{
//  uint8_t      cmd[2]  =  { 0U };
//  spi_status_t aux;
//
//  /* Update the register   */
//  cmd[0]   =   SX128X_DAYS;
//  cmd[1]   =   ( myNewDay.BCDday & ( DAYS_DAYS_TEN_PLACE_MASK | DAYS_DAYS_UNIT_PLACE_MASK ) );
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_GetWeekday ( SPI_parameters_t , SX128X_data_t* )
// *
// * @details     It gets the weekday.
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// *
// * @param[out]   myActualWeekday: Current weekday.
// *
// *
// * @return       Status of SX128X_GetWeekday.
// *
// *
// * @author      Manuel Caballero
// * @date        24/January/2019
// * @version     24/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_GetWeekday ( SPI_parameters_t mySPI_parameters, SX128X_data_t* myActualWeekday )
//{
//  uint8_t      cmd  =  0U;
//  spi_status_t aux;
//
//  /* Read the register   */
//  cmd      =   SX128X_WEEKDAYS;
//  aux      =   i2c_write ( mySPI_parameters, &cmd, 1U, I2C_NO_STOP_BIT );
//  aux      =   i2c_read ( mySPI_parameters, &cmd, 1U );
//
//  /* Parse the data  */
//  myActualWeekday->weekday  =   ( cmd & WEEKDAYS_WEEKDAYS_MASK );
//
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_SetWeekday ( SPI_parameters_t , SX128X_data_t )
// *
// * @details     It sets the weekday.
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// * @param[in]    myNewWeekday:    New weekday.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SX128X_SetWeekday.
// *
// *
// * @author      Manuel Caballero
// * @date        24/January/2019
// * @version     24/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_SetWeekday ( SPI_parameters_t mySPI_parameters, SX128X_data_t myNewWeekday )
//{
//  uint8_t      cmd[2]  =  { 0U };
//  spi_status_t aux;
//
//  /* Update the register   */
//  cmd[0]   =   SX128X_WEEKDAYS;
//  cmd[1]   =   myNewWeekday.weekday;
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_GetMonth ( SPI_parameters_t , SX128X_data_t* )
// *
// * @details     It gets the month ( BCD format ).
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// *
// * @param[out]   myActualMonth:   Current month.
// *
// *
// * @return       Status of SX128X_GetMonth.
// *
// *
// * @author      Manuel Caballero
// * @date        24/January/2019
// * @version     24/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_GetMonth ( SPI_parameters_t mySPI_parameters, SX128X_data_t* myActualMonth )
//{
//  uint8_t      cmd  =  0U;
//  spi_status_t aux;
//
//  /* Read the register   */
//  cmd      =   SX128X_MONTHS;
//  aux      =   i2c_write ( mySPI_parameters, &cmd, 1U, I2C_NO_STOP_BIT );
//  aux      =   i2c_read ( mySPI_parameters, &cmd, 1U );
//
//  /* Parse the data  */
//  myActualMonth->BCDmonth  =   ( cmd & MONTHS_MONTHS_MASK );
//
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_SetMonth ( SPI_parameters_t , SX128X_data_t )
// *
// * @details     It sets the month ( BCD format ).
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// * @param[in]    myNewMonth:      New month.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SX128X_SetMonth.
// *
// *
// * @author      Manuel Caballero
// * @date        24/January/2019
// * @version     24/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_SetMonth ( SPI_parameters_t mySPI_parameters, SX128X_data_t myNewMonth )
//{
//  uint8_t      cmd[2]  =  { 0U };
//  spi_status_t aux;
//
//  /* Update the register   */
//  cmd[0]   =   SX128X_MONTHS;
//  cmd[1]   =   myNewMonth.BCDmonth;
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_GetYear ( SPI_parameters_t , SX128X_data_t* )
// *
// * @details     It gets the year ( BCD format ).
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// *
// * @param[out]   myActualYear:    Current year.
// *
// *
// * @return       Status of SX128X_GetYear.
// *
// *
// * @author      Manuel Caballero
// * @date        24/January/2019
// * @version     24/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_GetYear ( SPI_parameters_t mySPI_parameters, SX128X_data_t* myActualYear )
//{
//  uint8_t      cmd  =  0U;
//  spi_status_t aux;
//
//  /* Read the register   */
//  cmd      =   SX128X_YEARS;
//  aux      =   i2c_write ( mySPI_parameters, &cmd, 1U, I2C_NO_STOP_BIT );
//  aux      =   i2c_read ( mySPI_parameters, &cmd, 1U );
//
//  /* Parse the data  */
//  myActualYear->BCDyear  =   cmd;
//
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_SetYear ( SPI_parameters_t , SX128X_data_t )
// *
// * @details     It sets the year ( BCD format ).
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// * @param[in]    myNewYear:       New year.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SX128X_SetYear.
// *
// *
// * @author      Manuel Caballero
// * @date        24/January/2019
// * @version     24/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_SetYear ( SPI_parameters_t mySPI_parameters, SX128X_data_t myNewYear )
//{
//  uint8_t      cmd[2]  =  { 0U };
//  spi_status_t aux;
//
//  /* Update the register   */
//  cmd[0]   =   SX128X_YEARS;
//  cmd[1]   =   myNewYear.BCDyear;
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_GetTime ( SPI_parameters_t , SX128X_data_t* )
// *
// * @details     It gets the time ( BCD format ).
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// *
// * @param[out]   myActualTime:    Current time ( BCD format: HHMMSS ).
// *
// *
// * @return       Status of SX128X_GetTime.
// *
// *
// * @author      Manuel Caballero
// * @date        24/January/2019
// * @version     24/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_GetTime ( SPI_parameters_t mySPI_parameters, SX128X_data_t* myActualTime )
//{
//  uint8_t      cmd[3]  =  { 0U };
//  spi_status_t aux;
//
//  /* Read the register   */
//  cmd[0]   =   SX128X_SECONDS;
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
//  aux      =   i2c_read ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
//
//  /* Parse the data  */
//  if ( myActualTime->Time12H_24HMode == CONTROL_1_12_24_24_HOUR_MODE )
//  {
//    myActualTime->BCDtime   =   ( cmd[2] & ( HOURS_24_HOUR_MODE_TEN_PLACE_MASK | HOURS_HOURS_UNIT_PLACE_MASK ) );
//  }
//  else
//  {
//    myActualTime->BCDtime   =   ( cmd[2] & ( HOURS_12_HOUR_MODE_TEN_PLACE_MASK | HOURS_HOURS_UNIT_PLACE_MASK ) );
//  }
//
//  myActualTime->BCDtime <<=   8U;
//  myActualTime->BCDtime  |=   ( cmd[1] & ( MINUTES_MINUTES_TEN_PLACE_MASK | MINUTES_MINUTES_UNIT_PLACE_MASK ) );
//  myActualTime->BCDtime <<=   8U;
//  myActualTime->BCDtime  |=   ( cmd[0] & ( SECONDS_SECONDS_TEN_PLACE_MASK | SECONDS_SECONDS_UNIT_PLACE_MASK ) );
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
//
//
//
///**
// * @brief       SX128X_SetTime ( SPI_parameters_t , SX128X_data_t )
// *
// * @details     It sets the time ( BCD format ).
// *
// * @param[in]    mySPI_parameters: I2C parameters.
// * @param[in]    myNewTime:       New current time ( BCD format: HHMMSS ).
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SX128X_SetTime.
// *
// *
// * @author      Manuel Caballero
// * @date        24/January/2019
// * @version     24/January/2019     The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SX128X_status_t  SX128X_SetTime ( SPI_parameters_t mySPI_parameters, SX128X_data_t myNewTime )
//{
//  uint8_t      cmd[4]  =  { 0U };
//  spi_status_t aux;
//
//  /* Read the register   */
//  cmd[0]   =   SX128X_SECONDS;
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
//  aux      =   i2c_read ( mySPI_parameters, &cmd[1], 3U );
//
//  /* Mask it and update the register  */
//  cmd[1]  &=  ~( SECONDS_SECONDS_TEN_PLACE_MASK | SECONDS_SECONDS_UNIT_PLACE_MASK );
//  cmd[1]  |=   (uint8_t)( myNewTime.BCDtime & 0x0000FF );
//  cmd[2]  &=  ~( MINUTES_MINUTES_TEN_PLACE_MASK | MINUTES_MINUTES_UNIT_PLACE_MASK );
//  cmd[2]  |=   (uint8_t)( ( myNewTime.BCDtime & 0x00FF00 ) >> 8U );
//
//  if ( myNewTime.Time12H_24HMode == CONTROL_1_12_24_24_HOUR_MODE )
//  {
//    cmd[3]  &=  ~( HOURS_24_HOUR_MODE_TEN_PLACE_MASK | HOURS_HOURS_UNIT_PLACE_MASK );
//  }
//  else
//  {
//    cmd[3]  &=  ~( HOURS_12_HOUR_MODE_TEN_PLACE_MASK | HOURS_HOURS_UNIT_PLACE_MASK );
//  }
//  cmd[3]  |=   (uint8_t)( ( myNewTime.BCDtime & 0xFF0000 ) >> 16U );
//  aux      =   i2c_write ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//
//  if ( aux == SPI_SUCCESS )
//  {
//    return   SX128X_SUCCESS;
//  }
//  else
//  {
//    return   SX128X_FAILURE;
//  }
//}
