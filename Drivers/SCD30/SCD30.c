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
  uint8_t       cmd[4] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SCD30_TRIGGERS_CONTINUOUS_MEASUREMENT >> 8U );
  cmd[1]   =  (uint8_t)( SCD30_TRIGGERS_CONTINUOUS_MEASUREMENT & 0xFF );
  cmd[2]   =  (uint8_t)( pressure_compensation >> 8U );
  cmd[3]   =  (uint8_t)( pressure_compensation & 0xFF );
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
  uint8_t       cmd[4] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SCD30_STOP_CONTINUOUS_MEASUREMENT >> 8U );
  cmd[1]   =  (uint8_t)( SCD30_STOP_CONTINUOUS_MEASUREMENT & 0xFF );
  cmd[2]   =  (uint8_t)( measurement_interval >> 8U );
  cmd[3]   =  (uint8_t)( measurement_interval & 0xFF );
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
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  (uint8_t)( SCD30_STOP_CONTINUOUS_MEASUREMENT >> 8U );
  cmd[1]   =  (uint8_t)( SCD30_STOP_CONTINUOUS_MEASUREMENT & 0xFF );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );

  /* Read the register   */
  aux     |=  i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  *measurement_interval   =   cmd[0];
  *measurement_interval <<=   8U;
  *measurement_interval  |=   cmd[1];

  //CRC has to be implemented 


  if ( aux == I2C_SUCCESS )
  {
      return   SCD30_SUCCESS;
  }
  else
  {
      return   SCD30_FAILURE;
  }
}



