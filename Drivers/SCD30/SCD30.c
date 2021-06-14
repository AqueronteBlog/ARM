/**
 * @brief       SCD30.c
 * @details     CO2, humidity and temperature sensor.
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

 #include "SCD30.h"


 /**
 * @brief       SCD30_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SCD30_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        22/January/2021
 * @version     22/January/2021   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SCD30_status_t  SCD30_Init ( I2C_parameters_t myI2Cparameters )
{
  i2c_status_t aux;

  aux  =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
      return   SCD30_SUCCESS;
  }
  else
  {
      return   SCD30_FAILURE;
  }
}



/**
 * @brief       SCD30_TriggerContinuousMeasurement    ( I2C_parameters_t , uint16_t  )
 * @details     It triggers continuous measurement with or without ambient pressure compensation.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 * @param[in]    pressure_compensation: 0 (desactivates pressure compensation) or [700 - 1400]. Pressure in mBar.
 *
 * @param[out]   N/A
 *
 *
 * @return      Status of SCD30_TriggerContinuousMeasurement.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SCD30_status_t  SCD30_TriggerContinuousMeasurement ( I2C_parameters_t myI2Cparameters, uint16_t pressure_compensation )
{
  uint8_t       cmd[5] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SCD30_TRIGGERS_CONTINUOUS_MEASUREMENT >> 8U );
  cmd[1]   =  (uint8_t)( SCD30_TRIGGERS_CONTINUOUS_MEASUREMENT & 0xFF );
  cmd[2]   =  (uint8_t)( pressure_compensation >> 8U );
  cmd[3]   =  (uint8_t)( pressure_compensation & 0xFF );
  cmd[4]   =  SCD30_CalculateI2C_CRC8 ( pressure_compensation );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


  if ( aux == I2C_SUCCESS )
  {
      return   SCD30_SUCCESS;
  }
  else
  {
      return   SCD30_FAILURE;
  }
}



/**
 * @brief       SCD30_StopContinuousMeasurement    ( I2C_parameters_t )
 * @details     It stops the continuous measurement.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A
 *
 *
 * @return      Status of SCD30_StopContinuousMeasurement.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SCD30_status_t  SCD30_StopContinuousMeasurement ( I2C_parameters_t myI2Cparameters )
{
  uint8_t       cmd[2] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SCD30_STOP_CONTINUOUS_MEASUREMENT >> 8U );
  cmd[1]   =  (uint8_t)( SCD30_STOP_CONTINUOUS_MEASUREMENT & 0xFF );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


  if ( aux == I2C_SUCCESS )
  {
      return   SCD30_SUCCESS;
  }
  else
  {
      return   SCD30_FAILURE;
  }
}



/**
 * @brief       SCD30_SetMeasurementInterval    ( I2C_parameters_t , uint16_t )
 * @details     It sets the measurement interval.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 * @param[in]    measurement_interval:  [2 - 1800]. Interval in seconds.
 *
 * @param[out]   N/A
 *
 *
 * @return      Status of SCD30_SetMeasurementInterval.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SCD30_status_t  SCD30_SetMeasurementInterval ( I2C_parameters_t myI2Cparameters, uint16_t measurement_interval )
{
  uint8_t       cmd[5] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SCD30_STOP_CONTINUOUS_MEASUREMENT >> 8U );
  cmd[1]   =  (uint8_t)( SCD30_STOP_CONTINUOUS_MEASUREMENT & 0xFF );
  cmd[2]   =  (uint8_t)( measurement_interval >> 8U );
  cmd[3]   =  (uint8_t)( measurement_interval & 0xFF );
  cmd[4]   =  SCD30_CalculateI2C_CRC8 ( measurement_interval );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


  if ( aux == I2C_SUCCESS )
  {
      return   SCD30_SUCCESS;
  }
  else
  {
      return   SCD30_FAILURE;
  }
}



/**
 * @brief       SCD30_GetMeasurementInterval    ( I2C_parameters_t , uint16_t* )
 * @details     It sets the measurement interval.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   measurement_interval:  Value. Interval in seconds.
 *
 *
 * @return      Status of SCD30_GetMeasurementInterval.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SCD30_status_t  SCD30_GetMeasurementInterval ( I2C_parameters_t myI2Cparameters, uint16_t* measurement_interval )
{
  uint8_t       cmd[4] = { 0U };
  uint8_t       aux_crc;
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SCD30_STOP_CONTINUOUS_MEASUREMENT >> 8U );
  cmd[1]   =  (uint8_t)( SCD30_STOP_CONTINUOUS_MEASUREMENT & 0xFF );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], 2U, I2C_STOP_BIT );

  /* Read the register   */
  aux     |=  i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  *measurement_interval   =   cmd[0];
  *measurement_interval <<=   8U;
  *measurement_interval  |=   cmd[1];

  /* Check the CRC   */
  aux_crc    =  SCD30_CalculateI2C_CRC8 ( *measurement_interval );

  if ( aux == I2C_SUCCESS )
  {
    if ( ( aux_crc - cmd[2] ) == 0U )
    {
      return   SCD30_SUCCESS;
    }
    else
    {
      return   SCD30_DATA_CORRUPTED;
    }
  }
  else
  {
      return   SCD30_FAILURE;
  }
}



/**
 * @brief       SCD30_GetDataReadyStatus    ( I2C_parameters_t , SCD30_get_ready_status_bit_t* )
 * @details     It gets the status when the data is ready to be read.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   status:          Data ready status.
 *
 *
 * @return      Status of SCD30_GetDataReadyStatus.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SCD30_status_t  SCD30_GetDataReadyStatus ( I2C_parameters_t myI2Cparameters, SCD30_get_ready_status_bit_t* status )
{
  uint8_t       cmd[3] = { 0U };
  uint8_t       aux_crc;
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SCD30_GET_DATA_READY_STATUS >> 8U );
  cmd[1]   =  (uint8_t)( SCD30_GET_DATA_READY_STATUS & 0xFF );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], 2U, I2C_STOP_BIT );

  /* Read the register   */
  aux     |=  i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  *status   =   cmd[0];
  *status <<=   8U;
  *status  |=   cmd[1];

  /* Check the CRC   */
  aux_crc    =  SCD30_CalculateI2C_CRC8 ( *status );

  if ( aux == I2C_SUCCESS )
  {
    if ( ( aux_crc - cmd[2] ) == 0U )
    {
      return   SCD30_SUCCESS;
    }
    else
    {
      return   SCD30_DATA_CORRUPTED;
    }
  }
  else
  {
      return   SCD30_FAILURE;
  }
}



/**
 * @brief       SCD30_ReadRawMeasurement    ( I2C_parameters_t , SCD30_raw_output_data_t* )
 * @details     It gets all the raw data.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   raw_data:        All the data in raw values.
 *
 *
 * @return      Status of SCD30_ReadRawMeasurement.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SCD30_status_t  SCD30_ReadRawMeasurement ( I2C_parameters_t myI2Cparameters, SCD30_raw_output_data_t* raw_data )
{
  uint8_t       cmd[18] = { 0U };
  uint16_t      aux_seed;
  uint8_t       aux_crc;
  uint8_t       aux_return = 0U;
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SCD30_READ_MEASUREMENT >> 8U );
  cmd[1]   =  (uint8_t)( SCD30_READ_MEASUREMENT & 0xFF );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], 2U, I2C_STOP_BIT );

  /* Read the register   */
  aux     |=  i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  raw_data->co2_mmsb                  =   cmd[0];
  raw_data->co2_mlsb                  =   cmd[1];
  raw_data->co2_mmsb_mlsb_crc         =   cmd[2];

  /* Check the CRC   */
  aux_seed   =  raw_data->co2_mmsb;
  aux_seed <<=  8U;
  aux_seed  |=  raw_data->co2_mlsb;
  aux_crc    =  SCD30_CalculateI2C_CRC8 ( aux_seed );

  if ( ( aux_crc - raw_data->co2_mmsb_mlsb_crc ) != 0U )
  {
    aux_return++;
  }

  raw_data->co2_lmsb                  =   cmd[3];
  raw_data->co2_llsb                  =   cmd[4];
  raw_data->co2_lmsb_llsb_crc         =   cmd[5];

  /* Check the CRC   */
  aux_seed   =  raw_data->co2_lmsb;
  aux_seed <<=  8U;
  aux_seed  |=  raw_data->co2_llsb;
  aux_crc    =  SCD30_CalculateI2C_CRC8 ( aux_seed );

  if ( ( aux_crc - raw_data->co2_lmsb_llsb_crc ) != 0U )
  {
    aux_return++;
  }

  raw_data->temperature_mmsb          =   cmd[6];
  raw_data->temperature_mlsb          =   cmd[7];
  raw_data->temperature_mmsb_mlsb_crc =   cmd[8];

  /* Check the CRC   */
  aux_seed   =  raw_data->temperature_mmsb;
  aux_seed <<=  8U;
  aux_seed  |=  raw_data->temperature_mlsb;
  aux_crc    =  SCD30_CalculateI2C_CRC8 ( aux_seed );

  if ( ( aux_crc - raw_data->temperature_mmsb_mlsb_crc ) != 0U )
  {
    aux_return++;
  }

  raw_data->temperature_lmsb          =   cmd[9];
  raw_data->temperature_llsb          =   cmd[10];
  raw_data->temperature_lmsb_llsb_crc =   cmd[11];

  /* Check the CRC   */
  aux_seed   =  raw_data->temperature_lmsb;
  aux_seed <<=  8U;
  aux_seed  |=  raw_data->temperature_llsb;
  aux_crc    =  SCD30_CalculateI2C_CRC8 ( aux_seed );

  if ( ( aux_crc - raw_data->temperature_lmsb_llsb_crc ) != 0U )
  {
    aux_return++;
  }

  raw_data->humidity_mmsb             =   cmd[12];
  raw_data->humidity_mlsb             =   cmd[13];
  raw_data->humidity_mmsb_mlsb_crc    =   cmd[14];

  /* Check the CRC   */
  aux_seed   =  raw_data->humidity_mmsb;
  aux_seed <<=  8U;
  aux_seed  |=  raw_data->humidity_mlsb;
  aux_crc    =  SCD30_CalculateI2C_CRC8 ( aux_seed );

  if ( ( aux_crc - raw_data->humidity_mmsb_mlsb_crc ) != 0U )
  {
    aux_return++;
  }

  raw_data->humidity_lmsb             =   cmd[15];
  raw_data->humidity_llsb             =   cmd[16];
  raw_data->humidity_lmsb_llsb_crc    =   cmd[17];

  /* Check the CRC   */
  aux_seed   =  raw_data->humidity_lmsb;
  aux_seed <<=  8U;
  aux_seed  |=  raw_data->humidity_llsb;
  aux_crc    =  SCD30_CalculateI2C_CRC8 ( aux_seed );

  if ( ( aux_crc - raw_data->humidity_lmsb_llsb_crc ) != 0U )
  {
    aux_return++;
  }

  
  if ( aux == I2C_SUCCESS )
  {
    if ( aux_return == 0U )
    {
      return   SCD30_SUCCESS;
    }
    else
    {
      return   SCD30_DATA_CORRUPTED;
    }
  }
  else
  {
      return   SCD30_FAILURE;
  }
}



/**
 * @brief       SCD30_ReadMeasurement    ( I2C_parameters_t , SCD30_output_data_t* )
 * @details     It gets all the data.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   data:            All the data.
 *
 *
 * @return      Status of SCD30_ReadMeasurement.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         This function updates the raw data too.
 * @warning     N/A.
 */
SCD30_status_t  SCD30_ReadMeasurement ( I2C_parameters_t myI2Cparameters, SCD30_output_data_t* data )
{
  SCD30_status_t  aux;
  uint32_t        data_aux;

  /* Read all the raw data  */
  aux      =  SCD30_ReadRawMeasurement ( myI2Cparameters, (SCD30_raw_output_data_t*)&data->raw );

    
  /* Parse the data  */
  data_aux    =   data->raw.co2_mmsb;
  data_aux  <<=   8U;
  data_aux   |=   data->raw.co2_mlsb;
  data_aux  <<=   8U;
  data_aux   |=   data->raw.co2_lmsb;
  data_aux  <<=   8U;
  data_aux   |=   data->raw.co2_llsb;
  
  data->processed.co2  =  *(float*)&data_aux;

  data_aux    =   data->raw.temperature_mmsb;
  data_aux  <<=   8U;
  data_aux   |=   data->raw.temperature_mlsb;
  data_aux  <<=   8U;
  data_aux   |=   data->raw.temperature_lmsb;
  data_aux  <<=   8U;
  data_aux   |=   data->raw.temperature_llsb;
  
  data->processed.temperature  =  *(float*)&data_aux;

  data_aux    =   data->raw.humidity_mmsb;
  data_aux  <<=   8U;
  data_aux   |=   data->raw.humidity_mlsb;
  data_aux  <<=   8U;
  data_aux   |=   data->raw.humidity_lmsb;
  data_aux  <<=   8U;
  data_aux   |=   data->raw.humidity_llsb;
  
  data->processed.humidity  =  *(float*)&data_aux;


  return   aux;
}



/**
 * @brief       SCD30_SetContinuousASC    ( I2C_parameters_t , SCD30_continuous_auto_selfcal_t )
 * @details     It enables/disables the continuous automatic self-calibration.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    asc:             Continuous automatic self-calibration value.
 *
 * @param[out]   N/A
 *
 *
 * @return      Status of SCD30_SetContinuousASC.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SCD30_status_t  SCD30_SetContinuousASC ( I2C_parameters_t myI2Cparameters, SCD30_continuous_auto_selfcal_t asc )
{
  uint8_t       cmd[5] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SCD30_CONTINUOUS_AUTOMATIC_SELF_CALIBRATION >> 8U );
  cmd[1]   =  (uint8_t)( SCD30_CONTINUOUS_AUTOMATIC_SELF_CALIBRATION & 0xFF );
  cmd[2]   =  (uint8_t)( asc >> 8U );
  cmd[3]   =  (uint8_t)( asc & 0xFF );
  cmd[4]   =  SCD30_CalculateI2C_CRC8 ( asc );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


  if ( aux == I2C_SUCCESS )
  {
      return   SCD30_SUCCESS;
  }
  else
  {
      return   SCD30_FAILURE;
  }
}



/**
 * @brief       SCD30_GetContinuousASC    ( I2C_parameters_t , SCD30_continuous_auto_selfcal_t* )
 * @details     It gets the continuous automatic self-calibration bit.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   asc:             Continuous automatic self-calibration value.
 *
 *
 * @return      Status of SCD30_GetContinuousASC.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SCD30_status_t  SCD30_GetContinuousASC ( I2C_parameters_t myI2Cparameters, SCD30_continuous_auto_selfcal_t* asc )
{
  uint8_t       cmd[4] = { 0U };
  uint8_t       aux_crc;
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SCD30_CONTINUOUS_AUTOMATIC_SELF_CALIBRATION >> 8U );
  cmd[1]   =  (uint8_t)( SCD30_CONTINUOUS_AUTOMATIC_SELF_CALIBRATION & 0xFF );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], 2U, I2C_STOP_BIT );

  /* Read the register   */
  aux     |=  i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  *asc   =   cmd[0];
  *asc <<=   8U;
  *asc  |=   cmd[1];

  /* Check the CRC   */
  aux_crc    =  SCD30_CalculateI2C_CRC8 ( *asc );

  if ( aux == I2C_SUCCESS )
  {
    if ( ( aux_crc - cmd[2] ) == 0U )
    {
      return   SCD30_SUCCESS;
    }
    else
    {
      return   SCD30_DATA_CORRUPTED;
    }
  }
  else
  {
      return   SCD30_FAILURE;
  }
}



/**
 * @brief       SCD30_SetForcedRecalibrationValue    ( I2C_parameters_t , uint16_t )
 * @details     It sets the forced recalibration value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    frc:             Forced recalibration value.
 *
 * @param[out]   N/A
 *
 *
 * @return      Status of SCD30_SetForcedRecalibrationValue.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SCD30_status_t  SCD30_SetForcedRecalibrationValue ( I2C_parameters_t myI2Cparameters, uint16_t frc )
{
  uint8_t       cmd[5] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SCD30_SET_FORCED_RECALIBRATION >> 8U );
  cmd[1]   =  (uint8_t)( SCD30_SET_FORCED_RECALIBRATION & 0xFF );
  cmd[2]   =  (uint8_t)( frc >> 8U );
  cmd[3]   =  (uint8_t)( frc & 0xFF );
  cmd[4]   =  SCD30_CalculateI2C_CRC8 ( frc );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


  if ( aux == I2C_SUCCESS )
  {
      return   SCD30_SUCCESS;
  }
  else
  {
      return   SCD30_FAILURE;
  }
}



/**
 * @brief       SCD30_GetForcedRecalibrationValue    ( I2C_parameters_t , uint16_t* )
 * @details     It gets the forced recalibration value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   frc:             Forced recalibration value.
 *
 *
 * @return      Status of SCD30_GetForcedRecalibrationValue.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SCD30_status_t  SCD30_GetForcedRecalibrationValue ( I2C_parameters_t myI2Cparameters, uint16_t* frc )
{
  uint8_t       cmd[3] = { 0U };
  uint8_t       aux_crc;
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SCD30_SET_FORCED_RECALIBRATION >> 8U );
  cmd[1]   =  (uint8_t)( SCD30_SET_FORCED_RECALIBRATION & 0xFF );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], 2U, I2C_STOP_BIT );

  /* Read the register   */
  aux     |=  i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  *frc   =   cmd[0];
  *frc <<=   8U;
  *frc  |=   cmd[1];

  /* Check the CRC   */
  aux_crc    =  SCD30_CalculateI2C_CRC8 ( *frc );

  if ( aux == I2C_SUCCESS )
  {
    if ( ( aux_crc - cmd[2] ) == 0U )
    {
      return   SCD30_SUCCESS;
    }
    else
    {
      return   SCD30_DATA_CORRUPTED;
    }
  }
  else
  {
      return   SCD30_FAILURE;
  }
}



/**
 * @brief       SCD30_SetTemperatureOffsetValue    ( I2C_parameters_t , uint16_t )
 * @details     It sets the temperature offset value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    temp_offset:     Temperature offset value.
 *
 * @param[out]   N/A
 *
 *
 * @return      Status of SCD30_SetTemperatureOffsetValue.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SCD30_status_t  SCD30_SetTemperatureOffsetValue ( I2C_parameters_t myI2Cparameters, uint16_t temp_offset )
{
  uint8_t       cmd[5] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SCD30_SET_TEMPERATURE_OFFSET >> 8U );
  cmd[1]   =  (uint8_t)( SCD30_SET_TEMPERATURE_OFFSET & 0xFF );
  cmd[2]   =  (uint8_t)( temp_offset >> 8U );
  cmd[3]   =  (uint8_t)( temp_offset & 0xFF );
  cmd[4]   =  SCD30_CalculateI2C_CRC8 ( temp_offset );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


  if ( aux == I2C_SUCCESS )
  {
      return   SCD30_SUCCESS;
  }
  else
  {
      return   SCD30_FAILURE;
  }
}



/**
 * @brief       SCD30_GetTemperatureOffsetValue    ( I2C_parameters_t , uint16_t* )
 * @details     It gets the temperature offset value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   temp_offset:     Temperature offset value.
 *
 *
 * @return      Status of SCD30_GetTemperatureOffsetValue.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SCD30_status_t  SCD30_GetTemperatureOffsetValue ( I2C_parameters_t myI2Cparameters, uint16_t* temp_offset )
{
  uint8_t       cmd[3] = { 0U };
  uint8_t       aux_crc;
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SCD30_SET_FORCED_RECALIBRATION >> 8U );
  cmd[1]   =  (uint8_t)( SCD30_SET_FORCED_RECALIBRATION & 0xFF );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], 2U, I2C_STOP_BIT );

  /* Read the register   */
  aux     |=  i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  *temp_offset   =   cmd[0];
  *temp_offset <<=   8U;
  *temp_offset  |=   cmd[1];

  /* Check the CRC   */
  aux_crc    =  SCD30_CalculateI2C_CRC8 ( *temp_offset );

  if ( aux == I2C_SUCCESS )
  {
    if ( ( aux_crc - cmd[2] ) == 0U )
    {
      return   SCD30_SUCCESS;
    }
    else
    {
      return   SCD30_DATA_CORRUPTED;
    }
  }
  else
  {
      return   SCD30_FAILURE;
  }
}



/**
 * @brief       SCD30_SetAltitudeCompensationValue    ( I2C_parameters_t , uint16_t )
 * @details     It sets the altitude compensation value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    alt_comp:        Altitude compensation value.
 *
 * @param[out]   N/A
 *
 *
 * @return      Status of SCD30_SetAltitudeCompensationValue.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SCD30_status_t  SCD30_SetAltitudeCompensationValue ( I2C_parameters_t myI2Cparameters, uint16_t alt_comp )
{
  uint8_t       cmd[5] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SCD30_SET_ALTITUDE_COMPENSATION >> 8U );
  cmd[1]   =  (uint8_t)( SCD30_SET_ALTITUDE_COMPENSATION & 0xFF );
  cmd[2]   =  (uint8_t)( alt_comp >> 8U );
  cmd[3]   =  (uint8_t)( alt_comp & 0xFF );
  cmd[4]   =  SCD30_CalculateI2C_CRC8 ( alt_comp );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


  if ( aux == I2C_SUCCESS )
  {
      return   SCD30_SUCCESS;
  }
  else
  {
      return   SCD30_FAILURE;
  }
}



/**
 * @brief       SCD30_GetAltitudeCompensationValue    ( I2C_parameters_t , uint16_t* )
 * @details     It gets the altitude compensation value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   alt_comp:        Altitude compensation value.
 *
 *
 * @return      Status of SCD30_GetAltitudeCompensationValue.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SCD30_status_t  SCD30_GetAltitudeCompensationValue ( I2C_parameters_t myI2Cparameters, uint16_t* alt_comp )
{
  uint8_t       cmd[3] = { 0U };
  uint8_t       aux_crc;
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SCD30_SET_ALTITUDE_COMPENSATION >> 8U );
  cmd[1]   =  (uint8_t)( SCD30_SET_ALTITUDE_COMPENSATION & 0xFF );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], 2U, I2C_STOP_BIT );

  /* Read the register   */
  aux     |=  i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  *alt_comp   =   cmd[0];
  *alt_comp <<=   8U;
  *alt_comp  |=   cmd[1];

  /* Check the CRC   */
  aux_crc    =  SCD30_CalculateI2C_CRC8 ( *alt_comp );

  if ( aux == I2C_SUCCESS )
  {
    if ( ( aux_crc - cmd[2] ) == 0U )
    {
      return   SCD30_SUCCESS;
    }
    else
    {
      return   SCD30_DATA_CORRUPTED;
    }
  }
  else
  {
      return   SCD30_FAILURE;
  }
}



/**
 * @brief       SCD30_GetFirmwareVersion    ( I2C_parameters_t , SCD30_fw_version_t* )
 * @details     It gets the firmware version value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   fw:              Firmware version value.
 *
 *
 * @return      Status of SCD30_GetFirmwareVersion.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SCD30_status_t  SCD30_GetFirmwareVersion ( I2C_parameters_t myI2Cparameters, SCD30_fw_version_t* fw )
{
  uint8_t       cmd[3] = { 0U };
  uint16_t      aux_seed;
  uint8_t       aux_crc;
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SCD30_FIRMWARE_VERSION >> 8U );
  cmd[1]   =  (uint8_t)( SCD30_FIRMWARE_VERSION & 0xFF );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], 2U, I2C_STOP_BIT );

  /* Read the register   */
  aux     |=  i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  fw->version_major  =   cmd[0];
  fw->version_minor  =   cmd[1];
  
  /* Check the CRC   */
  aux_seed   =  fw->version_major;
  aux_seed <<=  8U;
  aux_seed  |=  fw->version_minor;
  aux_crc    =  SCD30_CalculateI2C_CRC8 ( aux_seed );

  if ( aux == I2C_SUCCESS )
  {
    if ( ( aux_crc - cmd[2] ) == 0U )
    {
      return   SCD30_SUCCESS;
    }
    else
    {
      return   SCD30_DATA_CORRUPTED;
    }
  }
  else
  {
      return   SCD30_FAILURE;
  }
}



/**
 * @brief       SCD30_SoftReset    ( I2C_parameters_t )
 * @details     It performs a software reset.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of SCD30_SoftReset.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SCD30_status_t  SCD30_SoftReset ( I2C_parameters_t myI2Cparameters )
{
  uint8_t       cmd[2] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SCD30_SOFTRESET >> 8U );
  cmd[1]   =  (uint8_t)( SCD30_SOFTRESET & 0xFF );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
 


  if ( aux == I2C_SUCCESS )
  {
      return   SCD30_SUCCESS;
  }
  else
  {
      return   SCD30_FAILURE;
  }
}



/**
 * @brief       SCD30_CalculateI2C_CRC8    ( uint16_t )
 * @details     It calculates the I2C checksum calculation (CRC-8).
 *
 * @param[in]    seed: Data to calculate the CRC-8.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of SCD30_CalculateI2C_CRC8.
 *
 * @author      Manuel Caballero
 * @date        27/January/2021
 * @version     27/January/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
uint8_t  SCD30_CalculateI2C_CRC8 ( uint16_t seed )
{
  uint8_t bit;                  
  uint8_t crc = SCD30_CRC8_INITIALIZATION; 

  // calculates 8-Bit checksum with given polynomial
 
  crc ^= ( seed >> 8U ) & 255U;
  for(bit = 8U; bit > 0U; --bit)
  {
    if( crc & 0x80U )
    {
      crc = ( crc << 1U ) ^ SCD30_CRC8_POLYNOMIAL;
    }
    else
    {
      crc = ( crc << 1U );
    }
  }
 
  crc ^= seed & 255U;
  for( bit = 8U; bit > 0U; --bit )
  {
    if( crc & 0x80 )
    {
      crc = ( crc << 1U ) ^ SCD30_CRC8_POLYNOMIAL;
    }
    else
    {
      crc = ( crc << 1U );
    }
  }
    
  return crc;
}



