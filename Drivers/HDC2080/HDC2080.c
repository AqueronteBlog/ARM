/**
 * @brief       HDC2080.c
 * @details     Low-Power Humidity and Temperature Digital Sensor.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/October/2019
 * @version     10/October/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( https://www.nimbus.cit.ie ).
 */

#include "HDC2080.h"


/**
 * @brief       HDC2080_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of HDC2080_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        09/September/2019
 * @version     09/September/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_Init ( I2C_parameters_t myI2Cparameters )
{
  i2c_status_t aux;

  aux  =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   HDC2080_SUCCESS;
  }
  else
  {
    return   HDC2080_FAILURE;
  }
}



/**
 * @brief       HDC2080_GetDeviceID ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the device identification.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myDeviceID:      Device ID ( ID1 and ID2 ).
 *
 *
 * @return       Status of HDC2080_GetDeviceID.
 *
 *
 * @author      Manuel Caballero
 * @date        12/September/2019
 * @version     12/September/2019     The ORIGIN
 * @pre         This function uses auto-increment.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetDeviceID ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myDeviceID )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]	 =   HDC2080_ID1;
  aux   	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux   	 =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data  */
  myDeviceID->id1   =   cmd[0];
  myDeviceID->id2   =   cmd[1];



  if ( aux == I2C_SUCCESS )
  {
    return   HDC2080_SUCCESS;
  }
  else
  {
    return   HDC2080_FAILURE;
  }
}



/**
 * @brief       HDC2080_SetPowerDown ( I2C_parameters_t , HDC2080_data_t )
 *
 * @details     It sets the power-down mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myPwrDown: 	  Power down mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of HDC2080_SetPowerDown.
 *
 *
 * @author      Manuel Caballero
 * @date        12/September/2019
 * @version     12/September/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_SetPowerDown ( I2C_parameters_t myI2Cparameters, HDC2080_data_t myPwrDown )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Write the register   */
  cmd[0]	 =   HDC2080_POWER_DOWN;
  cmd[1]	 =	 myPwrDown.pwr_down;
  aux   	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   HDC2080_SUCCESS;
  }
  else
  {
    return   HDC2080_FAILURE;
  }
}



/**
 * @brief       HDC2080_GetPowerDown ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the power-down mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myPwrDown: 	  Power down mode.
 *
 *
 * @return       Status of HDC2080_GetPowerDown.
 *
 *
 * @author      Manuel Caballero
 * @date        12/September/2019
 * @version     12/September/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetPowerDown ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myPwrDown )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd	 =   HDC2080_POWER_DOWN;
  aux  	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux    =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data	 */
  myPwrDown->pwr_down	 =	 (HDC2080_power_down_pwr_down_t)cmd;



  if ( aux == I2C_SUCCESS )
  {
    return   HDC2080_SUCCESS;
  }
  else
  {
    return   HDC2080_FAILURE;
  }
}



/**
 * @brief       HDC2080_SetSoftReset ( I2C_parameters_t , HDC2080_data_t )
 *
 * @details     It produces a soft-reset.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myRSTB: 		  Reset mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of HDC2080_SetSoftReset.
 *
 *
 * @author      Manuel Caballero
 * @date        12/September/2019
 * @version     12/September/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_SetSoftReset ( I2C_parameters_t myI2Cparameters, HDC2080_data_t myRSTB )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Write the register   */
  cmd[0]	 =   HDC2080_RESET;
  cmd[1]	 =	 myRSTB.rstb;
  aux   	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   HDC2080_SUCCESS;
  }
  else
  {
    return   HDC2080_FAILURE;
  }
}



/**
 * @brief       HDC2080_GetSoftResetFlag ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the soft-reset flag.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myRSTB: 	  	  Soft-reset flag.
 *
 *
 * @return       Status of HDC2080_GetSoftResetFlag.
 *
 *
 * @author      Manuel Caballero
 * @date        12/September/2019
 * @version     12/September/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetSoftResetFlag ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myRSTB )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd	 =   HDC2080_RESET;
  aux  	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux    =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data	 */
  myRSTB->rstb	 =	 (HDC2080_reset_rstb_t)cmd;



  if ( aux == I2C_SUCCESS )
  {
    return   HDC2080_SUCCESS;
  }
  else
  {
    return   HDC2080_FAILURE;
  }
}



/**
 * @brief       HDC2080_SetModeControl ( I2C_parameters_t , HDC2080_data_t )
 *
 * @details     It sets the mode control.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myModeCont: 	  AVE_NUM, DREN and MODE.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of HDC2080_SetModeControl.
 *
 *
 * @author      Manuel Caballero
 * @date        12/September/2019
 * @version     12/September/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_SetModeControl ( I2C_parameters_t myI2Cparameters, HDC2080_data_t myModeCont )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register to mask   */
  cmd[0]	 =   HDC2080_MODE_CONTROL;
  aux   	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux    	 =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Mask the register and update it	 */
  cmd[1]	&=	~( MODE_CONTROL_AVE_NUM_MASK | MODE_CONTROL_DREN_MASK | MODE_CONTROL_MODE_MASK );
  cmd[1]	|=	 ( myModeCont.ave_num | myModeCont.dren | myModeCont.mode );
  aux   	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   HDC2080_SUCCESS;
  }
  else
  {
    return   HDC2080_FAILURE;
  }
}



/**
 * @brief       HDC2080_GetModeControl ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the mode control.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myModeCont: 	  AVE_NUM, DREN and MODE.
 *
 *
 * @return       Status of HDC2080_GetModeControl.
 *
 *
 * @author      Manuel Caballero
 * @date        12/September/2019
 * @version     12/September/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetModeControl ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myModeCont )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd	 =   HDC2080_MODE_CONTROL;
  aux  	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux    =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data	 */
  myModeCont->ave_num	 =	 (HDC2080_mode_control_ave_num_t)( cmd & MODE_CONTROL_AVE_NUM_MASK );
  myModeCont->dren		 =	 (HDC2080_mode_control_dren_t)( cmd & MODE_CONTROL_DREN_MASK );
  myModeCont->mode		 =	 (HDC2080_mode_control_mode_t)( cmd & MODE_CONTROL_MODE_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   HDC2080_SUCCESS;
  }
  else
  {
    return   HDC2080_FAILURE;
  }
}



/**
 * @brief       HDC2080_GetStatus ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the status flag.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myRD_DRDY: 	  Pressure and temperature measurement data ready bit.
 *
 *
 * @return       Status of HDC2080_GetStatus.
 *
 *
 * @author      Manuel Caballero
 * @date        12/September/2019
 * @version     12/September/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetStatus ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myRD_DRDY )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd	 =   HDC2080_STATUS;
  aux  	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux    =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data	 */
  myRD_DRDY->rd_drdy	 =	 (HDC2080_reset_rd_drdy_t)( cmd );



  if ( aux == I2C_SUCCESS )
  {
    return   HDC2080_SUCCESS;
  }
  else
  {
    return   HDC2080_FAILURE;
  }
}



/**
 * @brief       HDC2080_GetRawPressure ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the raw pressure.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myRawP: 	  	  Raw Pressure value.
 *
 *
 * @return       Status of HDC2080_GetRawPressure.
 *
 *
 * @author      Manuel Caballero
 * @date        13/September/2019
 * @version     17/September/2019     No need to manipulate the bits.
 * 				13/September/2019     The ORIGIN
 * @pre         This function uses auto-increment.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetRawPressure ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myRawP )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]	 =   HDC2080_PRESSURE_MSB;
  aux  	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux    	 =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data	 */
  myRawP->rawPressure	 =	 cmd[0];
  myRawP->rawPressure  <<=	 8U;
  myRawP->rawPressure	|=	 cmd[1];
  myRawP->rawPressure  <<=	 8U;
  myRawP->rawPressure	|=	 cmd[2];

  //myRawP->rawPressure  >>=	 2U;



  if ( aux == I2C_SUCCESS )
  {
    return   HDC2080_SUCCESS;
  }
  else
  {
    return   HDC2080_FAILURE;
  }
}



/**
 * @brief       HDC2080_GetRawTemperature ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the raw temperature.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myRawT: 	  	  Raw Temperature value.
 *
 *
 * @return       Status of HDC2080_GetRawTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        13/September/2019
 * @version     13/September/2019     The ORIGIN
 * @pre         This function uses auto-increment.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetRawTemperature ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myRawT )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]	 =   HDC2080_TEMPERATURE_MSB;
  aux  	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux    	 =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data	 */
  myRawT->rawTemperature	=	 cmd[0];
  myRawT->rawTemperature  <<=	 8U;
  myRawT->rawTemperature   |=	 cmd[1];




  if ( aux == I2C_SUCCESS )
  {
    return   HDC2080_SUCCESS;
  }
  else
  {
    return   HDC2080_FAILURE;
  }
}



/**
 * @brief       HDC2080_GetPressure ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the pressure.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myP: 	  	  	  Pressure value.
 *
 *
 * @return       Status of HDC2080_GetPressure.
 *
 *
 * @author      Manuel Caballero
 * @date        16/September/2019
 * @version     17/September/2019     The pressure is calculated correctly now.
 * 				16/September/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetPressure ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myP )
{
  HDC2080_status_t aux;

  /* Read the register   */
  aux	 =   HDC2080_GetRawPressure ( myI2Cparameters, &(*myP) );

  /* Parse the data	 */
  myP->pressure	 =	 ( ( ( ( myP->rawPressure >> 16U ) & 0xFF ) * 16384.0 ) + ( ( myP->rawPressure >> 8U ) & 0xFF ) * 64.0 ) + ( myP->rawPressure & 0xFF );
  myP->pressure	/=	2048.0;



  return   aux;
}



/**
 * @brief       HDC2080_GetTemperature ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the temperature.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myT: 	  	  	  Temperature value.
 *
 *
 * @return       Status of HDC2080_GetTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        16/September/2019
 * @version     16/September/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetTemperature ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myT )
{
  HDC2080_status_t aux;

  /* Read the register   */
  aux	 =   HDC2080_GetRawTemperature ( myI2Cparameters, &(*myT) );

  /* Parse the data	 */
  myT->temperature	 =	 ( ( ( ( myT->rawTemperature >> 8U ) & 0xFF ) * 256.0 ) + ( myT->rawTemperature & 0xFF ) );
  myT->temperature	/=	32.0;



  return   aux;
}
