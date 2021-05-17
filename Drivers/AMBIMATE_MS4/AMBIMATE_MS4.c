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

