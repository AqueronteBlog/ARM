/**
 * @brief       AMBIMATE_MS4.c
 * @details     AmbiMate Sensor Module.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/May/2021
 * @version     17/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */

 #include "AMBIMATE_MS4.h"


 /**
 * @brief       AMBIMATE_MS4_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AMBIMATE_MS4_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        17/May/2021
 * @version     17/May/2021   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_Init ( I2C_parameters_t myI2Cparameters )
{
  i2c_status_t aux;

  aux  =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_ScanStartByte    ( I2C_parameters_t , AMBIMATE_MS4_writeable_reg_gas_t , AMBIMATE_MS4_writeable_reg_batt_t , AMBIMATE_MS4_writeable_reg_aud_t , AMBIMATE_MS4_writeable_reg_light_t , AMBIMATE_MS4_writeable_reg_hum_t , AMBIMATE_MS4_writeable_reg_temp_t , AMBIMATE_MS4_writeable_reg_status_t )
 * @details     It initiates a new measurements of the chosen sensors.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    gas:               Initiates a new measurement.
 * @param[in]    batt:              Initiates a new measurement.
 * @param[in]    aud:               Initiates a new measurement.
 * @param[in]    light:             Initiates a new measurement.
 * @param[in]    hum:               Initiates a new measurement.
 * @param[in]    temp:              Initiates a new measurement.
 * @param[in]    status:            Initiates a new measurement.
 *
 * @param[out]   N/A
 *
 *
 * @return      Status of AMBIMATE_MS4_ScanStartByte.
 *
 * @author      Manuel Caballero
 * @date        17/May/2021
 * @version     17/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_ScanStartByte ( I2C_parameters_t myI2Cparameters, AMBIMATE_MS4_writeable_reg_gas_t gas, AMBIMATE_MS4_writeable_reg_batt_t batt, AMBIMATE_MS4_writeable_reg_aud_t aud, AMBIMATE_MS4_writeable_reg_light_t light, AMBIMATE_MS4_writeable_reg_hum_t hum, AMBIMATE_MS4_writeable_reg_temp_t temp, AMBIMATE_MS4_writeable_reg_status_t status )
{
  uint8_t       cmd[2] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  AMBIMATE_MS4_SCAN_START_BYTE;
  cmd[1]   =  ( gas | batt | aud | light | hum | temp | status );
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_GetFirmwareVersion    ( I2C_parameters_t , uint8_t* )
 * @details     It gets the firmware version.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   fw_version:        Firmware version.
 *
 *
 * @return      Status of AMBIMATE_MS4_GetFirmwareVersion.
 *
 * @author      Manuel Caballero
 * @date        17/May/2021
 * @version     17/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetFirmwareVersion  ( I2C_parameters_t myI2Cparameters, uint8_t* fw_version )
{
  uint8_t       cmd = 0U;
  i2c_status_t  aux;

  /* Write the register  */
  cmd   =  AMBIMATE_MS4_FIRMWARE_VERSION;
  aux   =  i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  |=  i2c_read ( myI2Cparameters, &(*fw_version), 1U );


  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_GetFirmwareSubVersion    ( I2C_parameters_t , uint8_t* )
 * @details     It gets the firmware sub-version.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   fw_subversion:     Firmware version.
 *
 *
 * @return      Status of AMBIMATE_MS4_GetFirmwareSubVersion.
 *
 * @author      Manuel Caballero
 * @date        17/May/2021
 * @version     17/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetFirmwareSubVersion ( I2C_parameters_t myI2Cparameters, uint8_t* fw_subversion )
{
  uint8_t       cmd = 0U;
  i2c_status_t  aux;

  /* Write the register  */
  cmd   =  AMBIMATE_MS4_FIRMWARE_SUB_VERSION;
  aux   =  i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  |=  i2c_read ( myI2Cparameters, &(*fw_subversion), 1U );


  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_GetOptionalSensorsByte    ( I2C_parameters_t , AMBIMATE_MS4_op_sensors_byte_t* )
 * @details     It gets the optional sensors on board.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   op_sensors:        Optional sensors on board.
 *
 *
 * @return      Status of AMBIMATE_MS4_GetOptionalSensorsByte.
 *
 * @author      Manuel Caballero
 * @date        17/May/2021
 * @version     17/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetOptionalSensorsByte ( I2C_parameters_t myI2Cparameters, AMBIMATE_MS4_op_sensors_byte_t* op_sensors )
{
  uint8_t       cmd = 0U;
  i2c_status_t  aux;

  /* Write the register  */
  cmd   =  AMBIMATE_MS4_OPTIONAL_SENSORS;
  aux   =  i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  |=  i2c_read ( myI2Cparameters, &cmd, 1U );

  /* Parse the data  */
  *op_sensors  =  (AMBIMATE_MS4_op_sensors_byte_t)( cmd & ( OPTIONAL_SENSORS_BYTE_CO2_MASK | OPTIONAL_SENSORS_BYTE_MIC_MASK ) );



  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_ProcessorReset    ( I2C_parameters_t )
 * @details     It performs a processor reset.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of AMBIMATE_MS4_ProcessorReset.
 *
 * @author      Manuel Caballero
 * @date        17/May/2021
 * @version     17/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_ProcessorReset ( I2C_parameters_t myI2Cparameters )
{
  uint8_t       cmd[2] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  AMBIMATE_MS4_PROCESSOR_RESET;
  cmd[1]   =  RESET_REGISTER_PROCESSOR_RESET;
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_GetStatus    ( I2C_parameters_t , uint8_t* )
 * @details     It gets the Status value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   status:            Status register.
 *
 *
 * @return      Status of AMBIMATE_MS4_GetStatus.
 *
 * @author      Manuel Caballero
 * @date        21/May/2021
 * @version     21/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetStatus ( I2C_parameters_t myI2Cparameters, uint8_t* status )
{
  uint8_t       cmd = 0U;
  i2c_status_t  aux;

  /* Write the register  */
  cmd   =  AMBIMATE_MS4_STATUS_HIGH_BYTE;
  aux   =  i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  |=  i2c_read ( myI2Cparameters, &(*status), 1U );



  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_GetRawTemperature    ( I2C_parameters_t , uint16_t* )
 * @details     It gets the temperature raw value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   raw_temp:          Raw value for temperature.
 *
 *
 * @return      Status of AMBIMATE_MS4_GetRawTemperature.
 *
 * @author      Manuel Caballero
 * @date        23/May/2021
 * @version     23/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetRawTemperature ( I2C_parameters_t myI2Cparameters, uint16_t* raw_temp )
{
  uint8_t       cmd[2] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  AMBIMATE_MS4_TEMPERATURE_HIGH_BYTE;
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=  i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data  */
  *raw_temp   =   cmd[0];
  *raw_temp <<=   8U;
  *raw_temp  |=   cmd[1];



  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_GetRawHumidity    ( I2C_parameters_t , uint16_t* )
 * @details     It gets the humidity raw value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   raw_hum:           Raw value for humidity.
 *
 *
 * @return      Status of AMBIMATE_MS4_GetRawHumidity.
 *
 * @author      Manuel Caballero
 * @date        23/May/2021
 * @version     23/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetRawHumidity ( I2C_parameters_t myI2Cparameters, uint16_t* raw_hum )
{
  uint8_t       cmd[2] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  AMBIMATE_MS4_HUMIDITY_HIGH_BYTE;
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=  i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data  */
  *raw_hum   =   cmd[0];
  *raw_hum <<=   8U;
  *raw_hum  |=   cmd[1];



  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_GetRawLight    ( I2C_parameters_t , uint16_t* )
 * @details     It gets the light raw value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   raw_light          Raw value for light.
 *
 *
 * @return      Status of AMBIMATE_MS4_GetRawLight.
 *
 * @author      Manuel Caballero
 * @date        23/May/2021
 * @version     23/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetRawLight ( I2C_parameters_t myI2Cparameters, uint16_t* raw_light )
{
  uint8_t       cmd[2] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  AMBIMATE_MS4_LIGHT_HIGH_BYTE;
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=  i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data  */
  *raw_light   =   cmd[0];
  *raw_light <<=   8U;
  *raw_light  |=   cmd[1];



  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_GetRawAudio    ( I2C_parameters_t , uint16_t* )
 * @details     It gets the audio raw value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   raw_audio          Raw value for audio.
 *
 *
 * @return      Status of AMBIMATE_MS4_GetRawAudio.
 *
 * @author      Manuel Caballero
 * @date        23/May/2021
 * @version     23/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetRawAudio ( I2C_parameters_t myI2Cparameters, uint16_t* raw_audio )
{
  uint8_t       cmd[2] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  AMBIMATE_MS4_AUDIO_HIGH_BYTE;
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=  i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data  */
  *raw_audio   =   cmd[0];
  *raw_audio <<=   8U;
  *raw_audio  |=   cmd[1];



  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_GetRawBatteryVolts    ( I2C_parameters_t , uint16_t* )
 * @details     It gets the battery volts raw value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   raw_batt           Raw value for battery volts.
 *
 *
 * @return      Status of AMBIMATE_MS4_GetRawBatteryVolts.
 *
 * @author      Manuel Caballero
 * @date        23/May/2021
 * @version     23/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetRawBatteryVolts ( I2C_parameters_t myI2Cparameters, uint16_t* raw_batt )
{
  uint8_t       cmd[2] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  AMBIMATE_MS4_BATTERY_VOLTS_HIGH_BYTE;
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=  i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data  */
  *raw_batt   =   cmd[0];
  *raw_batt <<=   8U;
  *raw_batt  |=   cmd[1];



  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_GetRawECO2    ( I2C_parameters_t , uint16_t* )
 * @details     It gets the eCO2 raw value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   raw_eco2           Raw value for eCO2.
 *
 *
 * @return      Status of AMBIMATE_MS4_GetRawECO2.
 *
 * @author      Manuel Caballero
 * @date        23/May/2021
 * @version     23/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetRawECO2 ( I2C_parameters_t myI2Cparameters, uint16_t* raw_eco2 )
{
  uint8_t       cmd[2] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  AMBIMATE_MS4_ECO2_HIGH_BYTE;
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=  i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data  */
  *raw_eco2   =   cmd[0];
  *raw_eco2 <<=   8U;
  *raw_eco2  |=   cmd[1];



  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_GetRawVOC    ( I2C_parameters_t , uint16_t* )
 * @details     It gets the VOC raw value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   raw_voc            Raw value for VOC.
 *
 *
 * @return      Status of AMBIMATE_MS4_GetRawVOC.
 *
 * @author      Manuel Caballero
 * @date        23/May/2021
 * @version     23/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetRawVOC ( I2C_parameters_t myI2Cparameters, uint16_t* raw_voc )
{
  uint8_t       cmd[2] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  AMBIMATE_MS4_ECO2_HIGH_BYTE;
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=  i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data  */
  *raw_voc   =   cmd[0];
  *raw_voc <<=   8U;
  *raw_voc  |=   cmd[1];



  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_GetRawAllSensors    ( I2C_parameters_t , uint8_t* , AMBIMATE_MS4_raw_data_values_t* )
 * @details     It gets the all sensors raw values.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   status             Status byte.
 * @param[out]   raw_all            Raw value for all the sensors.
 *
 *
 * @return      Status of AMBIMATE_MS4_GetRawAllSensors.
 *
 * @author      Manuel Caballero
 * @date        23/May/2021
 * @version     23/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetRawAllSensors ( I2C_parameters_t myI2Cparameters, uint8_t* status, AMBIMATE_MS4_raw_data_values_t* raw_all )
{
  uint8_t       cmd[15] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  AMBIMATE_MS4_STATUS_HIGH_BYTE;
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=  i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data  */
  *status   =   cmd[0];
  
  raw_all->raw_temperature      =   cmd[1];
  raw_all->raw_temperature    <<=   8U;
  raw_all->raw_temperature     |=   cmd[2];

  raw_all->raw_humidity         =   cmd[3];
  raw_all->raw_humidity       <<=   8U;
  raw_all->raw_humidity        |=   cmd[4];

  raw_all->raw_light            =   cmd[5];
  raw_all->raw_light          <<=   8U;
  raw_all->raw_light           |=   cmd[6];

  raw_all->raw_audio            =   cmd[7];
  raw_all->raw_audio          <<=   8U;
  raw_all->raw_audio           |=   cmd[8];

  raw_all->raw_battery_volts    =   cmd[9];
  raw_all->raw_battery_volts  <<=   8U;
  raw_all->raw_battery_volts   |=   cmd[10];

  raw_all->raw_eco2             =   cmd[11];
  raw_all->raw_eco2           <<=   8U;
  raw_all->raw_eco2            |=   cmd[12];

  raw_all->raw_voc              =   cmd[13];
  raw_all->raw_voc            <<=   8U;
  raw_all->raw_voc             |=   cmd[14];



  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_Get8bitRawTemperature    ( I2C_parameters_t , uint8_t* )
 * @details     It gets the temperature raw value ( 8-bit ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   raw_8bit_temp:     Raw value for temperature ( 8-bit resolution ).
 *
 *
 * @return      Status of AMBIMATE_MS4_Get8bitRawTemperature.
 *
 * @author      Manuel Caballero
 * @date        23/May/2021
 * @version     23/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_Get8bitRawTemperature ( I2C_parameters_t myI2Cparameters, uint8_t* raw_8bit_temp )
{
  uint8_t       cmd = 0U;
  i2c_status_t  aux;

  /* Write the register  */
  cmd   =  AMBIMATE_MS4_8BIT_STATUS_HIGH_BYTE;
  aux   =  i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  |=  i2c_read ( myI2Cparameters, &(*raw_8bit_temp), 1U );



  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_Get8bitRawHumidity ( I2C_parameters_t , uint8_t* )
 * @details     It gets the humidity raw value ( 8-bit resolution ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   raw_8bit_hum:      Raw value for humidity ( 8-bit ).
 *
 *
 * @return      Status of AMBIMATE_MS4_Get8bitRawHumidity.
 *
 * @author      Manuel Caballero
 * @date        23/May/2021
 * @version     23/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_Get8bitRawHumidity ( I2C_parameters_t myI2Cparameters, uint8_t* raw_8bit_hum )
{
  uint8_t       cmd = 0U;
  i2c_status_t  aux;

  /* Write the register  */
  cmd   =  AMBIMATE_MS4_8BIT_HUMIDITY_HIGH_BYTE;
  aux   =  i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  |=  i2c_read ( myI2Cparameters, &(*raw_8bit_hum), 1U );



  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_Get8bitRawLight    ( I2C_parameters_t , uint8_t* )
 * @details     It gets the light raw value ( 8-bit resolution ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   raw_8bit_light     Raw value for light ( 8-bit ).
 *
 *
 * @return      Status of AMBIMATE_MS4_Get8bitRawLight.
 *
 * @author      Manuel Caballero
 * @date        23/May/2021
 * @version     23/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_Get8bitRawLight ( I2C_parameters_t myI2Cparameters, uint8_t* raw_8bit_light )
{
  uint8_t       cmd = 0U;
  i2c_status_t  aux;

  /* Write the register  */
  cmd   =  AMBIMATE_MS4_8BIT_LIGHT_HIGH_BYTE;
  aux   =  i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  |=  i2c_read ( myI2Cparameters, &(*raw_8bit_light), 1U );



  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_Get8bitRawAudio    ( I2C_parameters_t , uint8_t* )
 * @details     It gets the audio raw value ( 8-bit resolution ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   raw_8bit_audio     Raw value for audio ( 8-bit ).
 *
 *
 * @return      Status of AMBIMATE_MS4_Get8bitRawAudio.
 *
 * @author      Manuel Caballero
 * @date        23/May/2021
 * @version     23/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_Get8bitRawAudio ( I2C_parameters_t myI2Cparameters, uint8_t* raw_8bit_audio )
{
  uint8_t       cmd = 0U;
  i2c_status_t  aux;

  /* Write the register  */
  cmd   =  AMBIMATE_MS4_8BIT_AUDIO_HIGH_BYTE;
  aux   =  i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  |=  i2c_read ( myI2Cparameters, &(*raw_8bit_audio), 1U );



  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_Get8bitRawBatteryVolts    ( I2C_parameters_t , uint8_t* )
 * @details     It gets the battery volts raw value ( 8-bit resolution ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   raw_8bit_batt      Raw value for battery volts ( 8-bit ).
 *
 *
 * @return      Status of AMBIMATE_MS4_Get8bitRawBatteryVolts.
 *
 * @author      Manuel Caballero
 * @date        23/May/2021
 * @version     23/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_Get8bitRawBatteryVolts ( I2C_parameters_t myI2Cparameters, uint8_t* raw_8bit_batt )
{
  uint8_t       cmd = 0U;
  i2c_status_t  aux;

  /* Write the register  */
  cmd   =  AMBIMATE_MS4_8BIT_BATTERY_VOLTS_HIGH_BYTE;
  aux   =  i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  |=  i2c_read ( myI2Cparameters, &(*raw_8bit_batt), 1U );



  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       MBIMATE_MS4_Get8bitRawECO2    ( I2C_parameters_t , uint8_t* )
 * @details     It gets the eCO2 raw value ( 8-bit resolution ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   raw_eco2           Raw value for eCO2 ( 8-bit ).
 *
 *
 * @return      Status of MBIMATE_MS4_Get8bitRawECO2.
 *
 * @author      Manuel Caballero
 * @date        23/May/2021
 * @version     23/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  MBIMATE_MS4_Get8bitRawECO2 ( I2C_parameters_t myI2Cparameters, uint8_t* raw_8bit_eco2 )
{
  uint8_t       cmd = 0U;
  i2c_status_t  aux;

  /* Write the register  */
  cmd   =  AMBIMATE_MS4_8BIT_ECO2_HIGH_BYTE;
  aux   =  i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  |=  i2c_read ( myI2Cparameters, &(*raw_8bit_eco2), 1U );



  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_Get8bitRawVOC    ( I2C_parameters_t , uint8_t* )
 * @details     It gets the VOC raw value ( 8-bit resolution ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   raw_8bit_voc       Raw value for VOC ( 8-bit ).
 *
 *
 * @return      Status of AMBIMATE_MS4_Get8bitRawVOC.
 *
 * @author      Manuel Caballero
 * @date        23/May/2021
 * @version     23/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_Get8bitRawVOC ( I2C_parameters_t myI2Cparameters, uint8_t* raw_8bit_voc )
{
  uint8_t       cmd = 0U;
  i2c_status_t  aux;

  /* Write the register  */
  cmd   =  AMBIMATE_MS4_8BIT_VOC_HIGH_BYTE;
  aux   =  i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  |=  i2c_read ( myI2Cparameters, &(*raw_8bit_voc), 1U );



  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_GetRaw8bitAllSensors    ( I2C_parameters_t , uint8_t* , AMBIMATE_MS4_raw_8bit_data_values_t* )
 * @details     It gets the all sensors raw values ( 8-bit resolution ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   status             Status byte.
 * @param[out]   raw_8bit_all       Raw value for all the sensors ( 8-bit ).
 *
 *
 * @return      Status of AMBIMATE_MS4_GetRaw8bitAllSensors.
 *
 * @author      Manuel Caballero
 * @date        23/May/2021
 * @version     23/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_GetRaw8bitAllSensors ( I2C_parameters_t myI2Cparameters, uint8_t* status, AMBIMATE_MS4_raw_8bit_data_values_t* raw_8bit_all )
{
  uint8_t       cmd[8] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[0]   =  AMBIMATE_MS4_8BIT_STATUS_HIGH_BYTE;
  aux      =  i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     |=  i2c_read ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data  */
  *status   =   cmd[0];
  
  raw_8bit_all->raw_8bit_temperature      =   cmd[1];

  raw_8bit_all->raw_8bit_humidity         =   cmd[2];

  raw_8bit_all->raw_8bit_light            =   cmd[3];

  raw_8bit_all->raw_8bit_audio            =   cmd[4];

  raw_8bit_all->raw_8bit_battery_volts    =   cmd[5];

  raw_8bit_all->raw_8bit_eco2             =   cmd[6];

  raw_8bit_all->raw_8bit_voc              =   cmd[7];



  if ( aux == I2C_SUCCESS )
  {
      return   AMBIMATE_MS4_SUCCESS;
  }
  else
  {
      return   AMBIMATE_MS4_FAILURE;
  }
}



/**
 * @brief       AMBIMATE_MS4_ProcessAllData    ( AMBIMATE_MS4_raw_data_values_t )
 * @details     It process all the data to human readable values for all the sensors.
 *
 * @param[in]    raw_all:   All raw values.
 *
 * @param[out]   N/A.
 *
 *
 * @return      all_data   All data is processed.
 *
 * @author      Manuel Caballero
 * @date        23/May/2021
 * @version     23/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_data_values_t  AMBIMATE_MS4_ProcessAllData ( AMBIMATE_MS4_raw_data_values_t raw_all )
{
  AMBIMATE_MS4_data_values_t myData;

  /* Temperature  */
  myData.temperature = ((double)((uint8_t)(raw_all.raw_temperature >> 8U)*256 + (uint8_t)(raw_all.raw_temperature & 0x00FF)))/10.0;
  
  /* Humidity  */
  myData.humidity = ((double)((uint8_t)(raw_all.raw_humidity >> 8U)*256 + (uint8_t)(raw_all.raw_humidity & 0x00FF)))/10.0;
  
  /* Light  */
  myData.light = ((uint8_t)(raw_all.raw_humidity >> 8U)*256 + (uint8_t)(raw_all.raw_humidity & 0x00FF));
  
  /* Audio  */
  myData.audio = ((uint8_t)(raw_all.raw_audio >> 8U)*256 + (uint8_t)(raw_all.raw_audio & 0x00FF));
  
  /* Battery volts  */
  myData.battery_volts = ((double)((uint8_t)(raw_all.raw_battery_volts >> 8U)*256 + (uint8_t)(raw_all.raw_battery_volts & 0x00FF))/1024.0)*(3.3/0.330);
  
  /* Gas, eCO2  */
  myData.eco2 = ((uint8_t)(raw_all.raw_eco2 >> 8U)*256 + (uint8_t)(raw_all.raw_eco2 & 0x00FF));
  
  /* VOC  */
  myData.voc = ((uint8_t)(raw_all.raw_voc >> 8U)*256 + (uint8_t)(raw_all.raw_voc & 0x00FF));


  return   myData;
}

