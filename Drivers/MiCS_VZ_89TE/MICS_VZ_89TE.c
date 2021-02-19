/**
 * @brief       MICS_VZ_89TE.c
 * @details     Integrated VOC Sensor Module with CO2 equivalent.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        26/January/2021
 * @version     26/January/2021    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( https://www.nimbus.cit.ie ).
 */

#include "MICS_VZ_89TE.h"


/**
 * @brief       MICS_VZ_89TE_Init ( I2C_parameters_t );
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MICS_VZ_89TE_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        26/January/2021
 * @version     26/January/2021   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MICS_VZ_89TE_status_t MICS_VZ_89TE_Init ( I2C_parameters_t myI2Cparameters )
{
  i2c_status_t aux;;

  aux   =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   MICS_VZ_89TE_SUCCESS;
  }
  else
  {
    return   MICS_VZ_89TE_FAILURE;
  }
}



/**
 * @brief       MICS_VZ_89TE_TriggersStatus ( I2C_parameters_t );
 *
 * @details     It triggers the STATUS command.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of MICS_VZ_89TE_TriggersStatus.
 *
 *
 * @author      Manuel Caballero
 * @date        26/January/2021
 * @version     27/January/2021   CRC was added.
 *              26/January/2021   The ORIGIN
 * @pre         N/A.
 * @warning     A delay (~100ms) between the command (Write) frame and the status-request (Read) frame should be implemented.
 */
MICS_VZ_89TE_status_t MICS_VZ_89TE_TriggersStatus ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[6]   =  { 0U };
  i2c_status_t aux;
   

  /* Write the register   */
  cmd[0]   =   MICS_VZ_89TE_GET_STATUS;
  cmd[5]   =   MICS_VZ_89TE_GetCRC ( &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );                 // Calculate the CRC
  aux      =   i2c_write  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), true );
  


  if ( aux == I2C_SUCCESS )
  {
    return   MICS_VZ_89TE_SUCCESS;
  }
  else
  {
    return   MICS_VZ_89TE_FAILURE;
  }
}



/**
 * @brief       MICS_VZ_89TE_GetStatus ( I2C_parameters_t , MICS_VZ_89TE_get_status_t* );
 *
 * @details     It gets all the raw values from the sensor.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   status:          All the raw values: D1-D7
 *
 *
 * @return       Status of MICS_VZ_89TE_GetStatus.
 *
 *
 * @author      Manuel Caballero
 * @date        26/January/2021
 * @version     27/January/2021   Parsing the data was added and, CRC calculation was added.
 *              26/January/2021   The ORIGIN
 * @pre         N/A.
 * @warning     MICS_VZ_89TE_TriggersStatus function must be called first and then after a delay of ~100ms, this function
 *              MICS_VZ_89TE_GetStatus can be called.
 */
MICS_VZ_89TE_status_t MICS_VZ_89TE_GetStatus ( I2C_parameters_t myI2Cparameters, MICS_VZ_89TE_get_status_t* status )
{
  uint8_t      cmd[7]   =  { 0U };
  uint8_t      crc      =  0U;
  i2c_status_t aux;
  
  /* Read the register   */
  aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  status->d1   =   cmd[0];
  status->d2   =   cmd[1];
  status->d3   =   cmd[2];
  status->d4   =   cmd[3];
  status->d5   =   cmd[4];
  status->d6   =   cmd[5];
  status->d7   =   cmd[6];

  /* Check the CRC   */
  crc  =   MICS_VZ_89TE_GetCRC ( (uint8_t*)&status, 6U );           



  if ( aux == I2C_SUCCESS )
  {
    if ( ( crc - status->d7 ) == 0U )
    {
      return   MICS_VZ_89TE_SUCCESS;
    }
    else
    {
      return   MICS_VZ_89TE_DATA_CORRUPTED;
    }
  }
  else
  {
    return   MICS_VZ_89TE_FAILURE;
  }
}



/**
 * @brief       MICS_VZ_89TE_GetUpdateValues ( I2C_parameters_t , MICS_VZ_89TE_get_status_t* , MICS_VZ_89TE_get_status_t* );
 *
 * @details     It gets all the values: tVOC, CO2_equ and Resistor.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   status:          All the raw values: D1-D7
 * @param[out]   values:          Output values: tVOC, CO2_equ and Resistor
 *
 *
 * @return       Status of MICS_VZ_89TE_GetUpdateValues.
 *
 *
 * @author      Manuel Caballero
 * @date        01/February/2021
 * @version     01/February/2021   The ORIGIN
 * @pre         This function also updates the STATUS values.
 * @warning     MICS_VZ_89TE_TriggersStatus function must be called first and then after a delay of ~100ms, this function
 *              MICS_VZ_89TE_GetUpdateValues can be called.
 */
MICS_VZ_89TE_status_t MICS_VZ_89TE_GetUpdateValues ( I2C_parameters_t myI2Cparameters, MICS_VZ_89TE_get_status_t* status, MICS_VZ_89TE_output_values_t* values )
{
  MICS_VZ_89TE_status_t aux;
  
  /* Read the register   */
  aux  =   MICS_VZ_89TE_GetStatus  ( myI2Cparameters, (MICS_VZ_89TE_get_status_t*)&status );
  
  /* Parse the data  */
  values->tvoc     =  (float)( ( status->d1 - 13.0 ) * ( 1000.0 / 229.0 ) );
  values->co2_equ  =  (float)( ( status->d2 - 13.0 ) * ( 1600.0 / 229.0 ) + 400.0 );
  values->resistor =  (float)( 10.0 * ( status->d5 + ( 256.0 * status->d4 ) + ( 65536.0 * status->d3 ) ) );


  return   aux;
}



/**
 * @brief       MICS_VZ_89TE_TriggersRevision ( I2C_parameters_t );
 *
 * @details     It triggers the Revsion command.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of MICS_VZ_89TE_TriggersRevision.
 *
 *
 * @author      Manuel Caballero
 * @date        28/January/2021
 * @version     28/January/2021   The ORIGIN
 * @pre         N/A.
 * @warning     A delay (~100ms) between the command (Write) frame and the status-request (Read) frame should be implemented.
 */
MICS_VZ_89TE_status_t MICS_VZ_89TE_TriggersRevision ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[6]   =  { 0U };
  i2c_status_t aux;
   

  /* Write the register   */
  cmd[0]   =   MICS_VZ_89TE_GET_REVISION;
  cmd[5]   =   MICS_VZ_89TE_GetCRC ( &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );                 // Calculate the CRC
  aux      =   i2c_write  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), true );
  


  if ( aux == I2C_SUCCESS )
  {
    return   MICS_VZ_89TE_SUCCESS;
  }
  else
  {
    return   MICS_VZ_89TE_FAILURE;
  }
}



/**
 * @brief       MICS_VZ_89TE_GetRevision ( I2C_parameters_t , MICS_VZ_89TE_revision_t* );
 *
 * @details     It gets Revision values.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   revision:        Revision values.
 *
 *
 * @return       Status of MICS_VZ_89TE_GetRevision.
 *
 *
 * @author      Manuel Caballero
 * @date        28/January/2021
 * @version     28/January/2021   The ORIGIN
 * @pre         N/A.
 * @warning     MICS_VZ_89TE_TriggersRevision function must be called first and then after a delay of ~100ms, this function
 *              MICS_VZ_89TE_GetRevision can be called.
 */
MICS_VZ_89TE_status_t MICS_VZ_89TE_GetRevision ( I2C_parameters_t myI2Cparameters, MICS_VZ_89TE_revision_t* revision )
{
  uint8_t      cmd[7]   =  { 0U };
  uint8_t      crc      =  0U;
  i2c_status_t aux;
  
  /* Read the register   */
  aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  revision->year        =   cmd[0];
  revision->month       =   cmd[1];
  revision->day         =   cmd[2];
  revision->ascii_code  =   cmd[3];
  revision->crc         =   cmd[6];

  /* Check the CRC   */
  crc  =   MICS_VZ_89TE_GetCRC ( (uint8_t*)&revision, 5U );           



  if ( aux == I2C_SUCCESS )
  {
    if ( ( crc - revision->crc ) == 0U )
    {
      return   MICS_VZ_89TE_SUCCESS;
    }
    else
    {
      return   MICS_VZ_89TE_DATA_CORRUPTED;
    }
  }
  else
  {
    return   MICS_VZ_89TE_FAILURE;
  }
}



/**
 * @brief       MICS_VZ_89TE_TriggersR0 ( I2C_parameters_t );
 *
 * @details     It triggers the R0 command.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of MICS_VZ_89TE_TriggersR0.
 *
 *
 * @author      Manuel Caballero
 * @date        28/January/2021
 * @version     28/January/2021   The ORIGIN
 * @pre         N/A.
 * @warning     A delay (~100ms) between the command (Write) frame and the status-request (Read) frame should be implemented.
 */
MICS_VZ_89TE_status_t MICS_VZ_89TE_TriggersR0 ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd[6]   =  { 0U };
  i2c_status_t aux;
   

  /* Write the register   */
  cmd[0]   =   MICS_VZ_89TE_GET_R0;
  cmd[5]   =   MICS_VZ_89TE_GetCRC ( &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );                 // Calculate the CRC
  aux      =   i2c_write  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), true );
  


  if ( aux == I2C_SUCCESS )
  {
    return   MICS_VZ_89TE_SUCCESS;
  }
  else
  {
    return   MICS_VZ_89TE_FAILURE;
  }
}



/**
 * @brief       MICS_VZ_89TE_GetR0 ( I2C_parameters_t , MICS_VZ_89TE_r0_t* );
 *
 * @details     It gets R0 value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   rawR0:           R0 (calibration) raw value.
 *
 *
 * @return       Status of MICS_VZ_89TE_GetR0.
 *
 *
 * @author      Manuel Caballero
 * @date        28/January/2021
 * @version     28/January/2021   The ORIGIN
 * @pre         N/A.
 * @warning     MICS_VZ_89TE_TriggersR0 function must be called first and then after a delay of ~100ms, this function
 *              MICS_VZ_89TE_GetRawR0 can be called.
 */
MICS_VZ_89TE_status_t MICS_VZ_89TE_GetRawR0 ( I2C_parameters_t myI2Cparameters, MICS_VZ_89TE_r0_t* rawR0 )
{
  uint8_t      cmd[7]   =  { 0U };
  uint8_t      crc      =  0U;
  i2c_status_t aux;
  
  /* Read the register   */
  aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  rawR0->r0_lsb =   cmd[0];
  rawR0->r0_msb =   cmd[1];
  rawR0->crc    =   cmd[6];

  /* Check the CRC   */
  crc  =   MICS_VZ_89TE_GetCRC ( (uint8_t*)&rawR0, 3U );           



  if ( aux == I2C_SUCCESS )
  {
    if ( ( crc - rawR0->crc ) == 0U )
    {
      return   MICS_VZ_89TE_SUCCESS;
    }
    else
    {
      return   MICS_VZ_89TE_DATA_CORRUPTED;
    }
  }
  else
  {
    return   MICS_VZ_89TE_FAILURE;
  }
}



/**
 * @brief       MICS_VZ_89TE_GetR0 ( I2C_parameters_t , MICS_VZ_89TE_r0_t* , uint16_t* );
 *
 * @details     It gets R0 value (in kOhms).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   rawR0:           R0 (calibration) raw value.
 * @param[out]   r0:              R0 (calibration) value in kOhms.
 *
 *
 * @return       Status of MICS_VZ_89TE_GetR0.
 *
 *
 * @author      Manuel Caballero
 * @date        01/February/2021
 * @version     01/February/2021   The ORIGIN
 * @pre         This function also updates the raw R0 values.
 * @warning     MICS_VZ_89TE_TriggersR0 function must be called first and then after a delay of ~100ms, this function
 *              MICS_VZ_89TE_GetR0 can be called.
 */
MICS_VZ_89TE_status_t MICS_VZ_89TE_GetR0 ( I2C_parameters_t myI2Cparameters, MICS_VZ_89TE_r0_t* rawR0, uint16_t* r0 )
{
 MICS_VZ_89TE_status_t aux;
  
  /* Read the register   */
  aux  =   MICS_VZ_89TE_GetRawR0 ( myI2Cparameters, (MICS_VZ_89TE_r0_t*)&rawR0 );
  
  /* Parse the data  */
  *r0   =  rawR0->r0_msb;
  *r0 <<=  8U;
  *r0  |=  rawR0->r0_lsb;    


  return   aux;
}



/**
 * @brief       MICS_VZ_89TE_GetCRC ( uint8_t* , uint8_t );
 *
 * @details     It gets CRC byte.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    buffer:          Bytes to calculate the CRC.
 * @param[in]    size:            Number of bytes to consider to calculate the CRC.
 *
 * @param[out]   N/A
 *
 *
 * @return       Calculated CRC byte.
 *
 *
 * @author      sgxsensortech
 * @author      Manuel Caballero
 * @date        26/January/2021
 * @version     26/January/2021   The ORIGIN
 * @pre         The CRC byte sent by the MASTER is calculated with all data byte including command byte.
 * @pre         The CRC byte sent by the SLAVE (VZ89TE) is calculated with al data byte.
 * @warning     N/A.
 */
uint8_t MICS_VZ_89TE_GetCRC ( uint8_t* buffer, uint8_t size )
{
  uint8_t  crc = 0U;
  uint32_t i   = 0U;
  uint32_t sum = 0UL;
  
  /* Summation with carry   */
  for ( i = 0U; i < size; i++ )
  {
    sum +=   buffer[i]; 
  }
  

  crc  = (uint8_t)sum;
  crc += (sum/0x0100);    // Add with carry
  crc  = 0xFF - crc;      // complement


  return  crc;
}
