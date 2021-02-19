/**
 * @brief       SHT3X.c
 * @details     Humidity and Temperature Sensor.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/January/2021
 * @version     22/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */

 #include "SHT3X.h"


 /**
 * @brief       SHT3X_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SHT3X_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        22/January/2021
 * @version     22/January/2021   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SHT3X_status_t  SHT3X_Init ( I2C_parameters_t myI2Cparameters )
{
  i2c_status_t aux;

  aux  =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
      return   SHT3X_SUCCESS;
  }
  else
  {
      return   SHT3X_FAILURE;
  }
}



/**
 * @brief       SHT3X_OneShotTriggerAllData    ( I2C_parameters_t , SHT3X_command_registers_single_shot_mode_t  )
 * @details     It triggers all the raw data in single shot mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    mode:            Clock Stretching/No Stretching and the repeatability.
 *
 * @param[out]   N/A
 *
 *
 * @return      Status of SHT3X_OneShotTriggerAllData.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SHT3X_status_t  SHT3X_OneShotTriggerAllData ( I2C_parameters_t myI2Cparameters, SHT3X_command_registers_single_shot_mode_t mode )
{
  uint8_t       cmd[2] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( mode >> 8U );
  cmd[1]   =  (uint8_t)( mode & 0xFF );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


  if ( aux == I2C_SUCCESS )
  {
      return   SHT3X_SUCCESS;
  }
  else
  {
      return   SHT3X_FAILURE;
  }
}



/**
 * @brief       SHT3X_OneShotGetAllRawData ( I2C_parameters_t , SHT3X_raw_data_t* )
 * @details     It gets all the raw data in single shot mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   rawData:         All the raw data and their CRC values.
 *
 *
 * @return      Status of SHT3X_OneShotGetAllRawData.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     SHT3X_OneShotTriggerAllData function must be called first. The user MUST respect the
 *              measurement duration as indicated in the datasheet (Table4.System timing specification, p7):
 *              
 *                                     Typ.     Max
 *              Low repeatability      2.5ms    4ms
 *              Medium repeatability   4.5ms    6ms
 *              High repeatability    12.5ms   15ms.
 */
SHT3X_status_t  SHT3X_OneShotGetAllRawData ( I2C_parameters_t myI2Cparameters, SHT3X_raw_data_t* rawData )
{
  uint8_t       cmd[6] = { 0U };
  i2c_status_t  aux;

  /* Read the register  */
  aux = i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  rawData->rawTemperature        =   cmd[0];
  rawData->rawTemperature      <<=   8U;
  rawData->rawTemperature       |=   cmd[1];

  rawData->temperatureCRC        =   cmd[2];

  rawData->rawRelativeHumidity   =   cmd[3];
  rawData->rawRelativeHumidity <<=   8U;
  rawData->rawRelativeHumidity  |=   cmd[4];

  rawData->relativeHumidityCRC   =   cmd[5];


  if ( aux == I2C_SUCCESS )
  {
      return   SHT3X_SUCCESS;
  }
  else
  {
      return   SHT3X_FAILURE;
  }
}



/**
 * @brief       SHT3X_SetPeriodicMeasurementART ( I2C_parameters_t )
 * @details     It sets periodic measurement with ART (accelerated response time).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A
 *
 *
 * @return      Status of SHT3X_SetPeriodicMeasurementART.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SHT3X_status_t  SHT3X_SetPeriodicMeasurementART ( I2C_parameters_t myI2Cparameters )
{
  uint8_t       cmd[2] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SHT3X_PERIODIC_MESUREMENT_WITH_ART >> 8U );
  cmd[1]   =  (uint8_t)( SHT3X_PERIODIC_MESUREMENT_WITH_ART & 0xFF );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


  if ( aux == I2C_SUCCESS )
  {
      return   SHT3X_SUCCESS;
  }
  else
  {
      return   SHT3X_FAILURE;
  }
}



/**
 * @brief       SHT3X_SetBreakCommand ( I2C_parameters_t )
 * @details     It sets the break command (stop periodic data acquisition mode).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A
 *
 *
 * @return      Status of SHT3X_SetBreakCommand.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SHT3X_status_t  SHT3X_SetBreakCommand ( I2C_parameters_t myI2Cparameters )
{
  uint8_t       cmd[2] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SHT3X_BREAK >> 8U );
  cmd[1]   =  (uint8_t)( SHT3X_BREAK & 0xFF );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


  if ( aux == I2C_SUCCESS )
  {
      return   SHT3X_SUCCESS;
  }
  else
  {
      return   SHT3X_FAILURE;
  }
}



/**
 * @brief       SHT3X_SetSoftReset ( I2C_parameters_t )
 * @details     It performs a software reset.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A
 *
 *
 * @return      Status of SHT3X_SetSoftReset.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SHT3X_status_t  SHT3X_SetSoftReset ( I2C_parameters_t myI2Cparameters )
{
  uint8_t       cmd[2] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SHT3X_SOFT_RESET >> 8U );
  cmd[1]   =  (uint8_t)( SHT3X_SOFT_RESET & 0xFF );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


  if ( aux == I2C_SUCCESS )
  {
      return   SHT3X_SUCCESS;
  }
  else
  {
      return   SHT3X_FAILURE;
  }
}



/**
 * @brief       SHT3X_SetGeneralCallReset ( I2C_parameters_t )
 * @details     It perfoms a reset through a general call address.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A
 *
 *
 * @return      Status of SHT3X_SetGeneralCallReset.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SHT3X_status_t  SHT3X_SetGeneralCallReset ( I2C_parameters_t myI2Cparameters )
{
  uint8_t       cmd;
  uint8_t       aux_addr;
  i2c_status_t  aux;
  
  /* Save previous address   */
  aux_addr =   myI2Cparameters.ADDR;

  /* Write the register  */
  myI2Cparameters.ADDR   =  SHT3X_GENERAL_CALL_RESET_ADDRESS_BYTE;
  cmd                    =  SHT3X_GENERAL_CALL_RESET_SECOND_BYTE;
  aux                    =  i2c_write ( myI2Cparameters, &cmd, 1U, I2C_STOP_BIT );
  
  /* Restore previous address  */
  myI2Cparameters.ADDR   =   aux_addr;


  if ( aux == I2C_SUCCESS )
  {
      return   SHT3X_SUCCESS;
  }
  else
  {
      return   SHT3X_FAILURE;
  }
}



/**
 * @brief       SHT3X_SetHeater ( I2C_parameters_t )
 * @details     It sets the heater.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    heater:          Enable/Disable.
 *
 * @param[out]   N/A
 *
 *
 * @return      Status of SHT3X_SetHeater.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SHT3X_status_t  SHT3X_SetHeater ( I2C_parameters_t myI2Cparameters, SHT3X_command_registers_heater_t heater )
{
  uint8_t       cmd[2] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( heater >> 8U );
  cmd[1]   =  (uint8_t)( heater & 0xFF );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


  if ( aux == I2C_SUCCESS )
  {
      return   SHT3X_SUCCESS;
  }
  else
  {
      return   SHT3X_FAILURE;
  }
}



/**
 * @brief       SHT3X_GetStatus ( I2C_parameters_t , SHT3X_status_data_t* )
 * @details     It gets the status register.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   status:          The wole status register and its CRC.
 *
 *
 * @return      Status of SHT3X_GetStatus.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SHT3X_status_t  SHT3X_GetStatus ( I2C_parameters_t myI2Cparameters, SHT3X_status_data_t* status )
{
  uint8_t       cmd[3] = { 0U };
  i2c_status_t  aux    = SHT3X_SUCCESS;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SHT3X_STATUS_REGISTER >> 8U );
  cmd[1]   =  (uint8_t)( SHT3X_STATUS_REGISTER & 0xFF );
  aux     |=  i2c_write ( myI2Cparameters, &cmd[0], 2U, I2C_NO_STOP_BIT );
  
  /* Read the register   */
  aux     |=  i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  status->status     =   cmd[0];
  status->status   <<=   8U;
  status->status    |=   cmd[1];

  status->statusCRC  =   cmd[2];



  if ( aux == I2C_SUCCESS )
  {
      return   SHT3X_SUCCESS;
  }
  else
  {
      return   SHT3X_FAILURE;
  }
}



/**
 * @brief       SHT3X_ClearStatus ( I2C_parameters_t )
 * @details     It clears the status register.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of SHT3X_ClearStatus.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SHT3X_status_t  SHT3X_ClearStatus ( I2C_parameters_t myI2Cparameters )
{
  uint8_t       cmd[2] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SHT3X_CLEAR_STATUS_REGISTER >> 8U );
  cmd[1]   =  (uint8_t)( SHT3X_CLEAR_STATUS_REGISTER & 0xFF );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
      return   SHT3X_SUCCESS;
  }
  else
  {
      return   SHT3X_FAILURE;
  }
}



/**
 * @brief       SHT3X_SetPeriodicAquisitionMode ( I2C_parameters_t , SHT3X_command_registers_periodic_data_mode_t )
 * @details     It sets the periodic data aquisition mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    mo:              Periodic aquisition mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of SHT3X_SetPeriodicAquisitionMode.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SHT3X_status_t  SHT3X_SetPeriodicAquisitionMode ( I2C_parameters_t myI2Cparameters, SHT3X_command_registers_periodic_data_mode_t mo )
{
  uint8_t       cmd[2] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( mo >> 8U );
  cmd[1]   =  (uint8_t)( mo & 0xFF );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
      return   SHT3X_SUCCESS;
  }
  else
  {
      return   SHT3X_FAILURE;
  }
}



/**
 * @brief       SHT3X_GetAllRawDataFetchData ( I2C_parameters_t , SHT3X_raw_data_t* )
 * @details     It gets the all raw data (in periodic aquisition mode).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   rawData:         Raw data and their CRC values.
 *
 *
 * @return      Status of SHT3X_GetAllRawDataFetchData.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SHT3X_status_t  SHT3X_GetAllRawDataFetchData ( I2C_parameters_t myI2Cparameters, SHT3X_raw_data_t* rawData )
{
  uint8_t       cmd[6] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SHT3X_FETCH_DATA >> 8U );
  cmd[1]   =  (uint8_t)( SHT3X_FETCH_DATA & 0xFF );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_NO_STOP_BIT );
  
  /* Read the register   */
  aux      =  i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  rawData->rawTemperature        =   cmd[0];
  rawData->rawTemperature      <<=   8U;
  rawData->rawTemperature       |=   cmd[1];

  rawData->temperatureCRC        =   cmd[2];

  rawData->rawRelativeHumidity   =   cmd[3];
  rawData->rawRelativeHumidity <<=   8U;
  rawData->rawRelativeHumidity  |=   cmd[4];

  rawData->relativeHumidityCRC   =   cmd[5];



  if ( aux == I2C_SUCCESS )
  {
      return   SHT3X_SUCCESS;
  }
  else
  {
      return   SHT3X_FAILURE;
  }
}



/**
 * @brief       SHT3X_ProccessData ( SHT3X_raw_data_t , SHT3X_final_data_t* )
 * @details     It clears the status register.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    rawData:         Data to be processed.
 *
 * @param[out]   data:            Data result.
 *
 *
 * @return      N/A.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void  SHT3X_ProccessData ( SHT3X_raw_data_t rawData, SHT3X_final_data_t* data )
{
  /* Process the temperature value  */
  data->temperature  =   ( -45.0 + ( 175.0 * ( rawData.rawTemperature / ( 65536.0 - 1.0 ) ) ) );
  
  /* Process the relative humidity value  */
  data->relativeHumidity  =   100.0 * ( rawData.rawRelativeHumidity / ( 65536.0 - 1.0 ) );
}
