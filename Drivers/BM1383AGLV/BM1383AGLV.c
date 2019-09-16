/**
 * @brief       BM1383AGLV.c
 * @details     Pressure Sensor IC.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        09/September/2019
 * @version     09/September/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */

#include "BM1383AGLV.h"


/**
 * @brief       BM1383AGLV_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BM1383AGLV_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        09/September/2019
 * @version     09/September/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BM1383AGLV_status_t BM1383AGLV_Init ( I2C_parameters_t myI2Cparameters )
{
  i2c_status_t aux;

  aux  =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   BM1383AGLV_SUCCESS;
  }
  else
  {
    return   BM1383AGLV_FAILURE;
  }
}



/**
 * @brief       BM1383AGLV_GetDeviceID ( I2C_parameters_t , BM1383AGLV_data_t* )
 *
 * @details     It gets the device identification.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myDeviceID:      Device ID ( ID1 and ID2 ).
 *
 *
 * @return       Status of BM1383AGLV_GetDeviceID.
 *
 *
 * @author      Manuel Caballero
 * @date        12/September/2019
 * @version     12/September/2019     The ORIGIN
 * @pre         This function uses auto-increment.
 * @warning     N/A.
 */
BM1383AGLV_status_t BM1383AGLV_GetDeviceID ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t* myDeviceID )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]	 =   BM1383AGLV_ID1;
  aux   	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux   	 =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data  */
  myDeviceID->id1   =   cmd[0];
  myDeviceID->id2   =   cmd[1];



  if ( aux == I2C_SUCCESS )
  {
    return   BM1383AGLV_SUCCESS;
  }
  else
  {
    return   BM1383AGLV_FAILURE;
  }
}



/**
 * @brief       BM1383AGLV_SetPowerDown ( I2C_parameters_t , BM1383AGLV_data_t )
 *
 * @details     It sets the power-down mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myPwrDown: 	  Power down mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BM1383AGLV_SetPowerDown.
 *
 *
 * @author      Manuel Caballero
 * @date        12/September/2019
 * @version     12/September/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BM1383AGLV_status_t BM1383AGLV_SetPowerDown ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t myPwrDown )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Write the register   */
  cmd[0]	 =   BM1383AGLV_POWER_DOWN;
  cmd[1]	 =	 myPwrDown.pwr_down;
  aux   	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   BM1383AGLV_SUCCESS;
  }
  else
  {
    return   BM1383AGLV_FAILURE;
  }
}



/**
 * @brief       BM1383AGLV_GetPowerDown ( I2C_parameters_t , BM1383AGLV_data_t* )
 *
 * @details     It gets the power-down mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myPwrDown: 	  Power down mode.
 *
 *
 * @return       Status of BM1383AGLV_GetPowerDown.
 *
 *
 * @author      Manuel Caballero
 * @date        12/September/2019
 * @version     12/September/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BM1383AGLV_status_t BM1383AGLV_GetPowerDown ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t* myPwrDown )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd	 =   BM1383AGLV_POWER_DOWN;
  aux  	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux    =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data	 */
  myPwrDown->pwr_down	 =	 (BM1383AGLV_power_down_pwr_down_t)cmd;



  if ( aux == I2C_SUCCESS )
  {
    return   BM1383AGLV_SUCCESS;
  }
  else
  {
    return   BM1383AGLV_FAILURE;
  }
}



/**
 * @brief       BM1383AGLV_SetSoftReset ( I2C_parameters_t , BM1383AGLV_data_t )
 *
 * @details     It produces a soft-reset.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myRSTB: 		  Reset mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BM1383AGLV_SetSoftReset.
 *
 *
 * @author      Manuel Caballero
 * @date        12/September/2019
 * @version     12/September/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BM1383AGLV_status_t BM1383AGLV_SetSoftReset ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t myRSTB )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Write the register   */
  cmd[0]	 =   BM1383AGLV_RESET;
  cmd[1]	 =	 myRSTB.rstb;
  aux   	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   BM1383AGLV_SUCCESS;
  }
  else
  {
    return   BM1383AGLV_FAILURE;
  }
}



/**
 * @brief       BM1383AGLV_GetSoftResetFlag ( I2C_parameters_t , BM1383AGLV_data_t* )
 *
 * @details     It gets the soft-reset flag.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myRSTB: 	  	  Soft-reset flag.
 *
 *
 * @return       Status of BM1383AGLV_GetSoftResetFlag.
 *
 *
 * @author      Manuel Caballero
 * @date        12/September/2019
 * @version     12/September/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BM1383AGLV_status_t BM1383AGLV_GetSoftResetFlag ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t* myRSTB )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd	 =   BM1383AGLV_RESET;
  aux  	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux    =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data	 */
  myRSTB->rstb	 =	 (BM1383AGLV_reset_rstb_t)cmd;



  if ( aux == I2C_SUCCESS )
  {
    return   BM1383AGLV_SUCCESS;
  }
  else
  {
    return   BM1383AGLV_FAILURE;
  }
}



/**
 * @brief       BM1383AGLV_SetModeControl ( I2C_parameters_t , BM1383AGLV_data_t )
 *
 * @details     It sets the mode control.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myModeCont: 	  AVE_NUM, DREN and MODE.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BM1383AGLV_SetModeControl.
 *
 *
 * @author      Manuel Caballero
 * @date        12/September/2019
 * @version     12/September/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BM1383AGLV_status_t BM1383AGLV_SetModeControl ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t myModeCont )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register to mask   */
  cmd[0]	 =   BM1383AGLV_MODE_CONTROL;
  aux   	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux    	 =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

  /* Mask the register and update it	 */
  cmd[1]	&=	~( MODE_CONTROL_AVE_NUM_MASK | MODE_CONTROL_DREN_MASK | MODE_CONTROL_MODE_MASK );
  cmd[1]	|=	 ( myModeCont.ave_num | myModeCont.dren | myModeCont.mode );
  aux   	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   BM1383AGLV_SUCCESS;
  }
  else
  {
    return   BM1383AGLV_FAILURE;
  }
}



/**
 * @brief       BM1383AGLV_GetModeControl ( I2C_parameters_t , BM1383AGLV_data_t* )
 *
 * @details     It gets the mode control.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myModeCont: 	  AVE_NUM, DREN and MODE.
 *
 *
 * @return       Status of BM1383AGLV_GetModeControl.
 *
 *
 * @author      Manuel Caballero
 * @date        12/September/2019
 * @version     12/September/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BM1383AGLV_status_t BM1383AGLV_GetModeControl ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t* myModeCont )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd	 =   BM1383AGLV_MODE_CONTROL;
  aux  	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux    =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data	 */
  myModeCont->ave_num	 =	 (BM1383AGLV_mode_control_ave_num_t)( cmd & MODE_CONTROL_AVE_NUM_MASK );
  myModeCont->dren		 =	 (BM1383AGLV_mode_control_dren_t)( cmd & MODE_CONTROL_DREN_MASK );
  myModeCont->mode		 =	 (BM1383AGLV_mode_control_mode_t)( cmd & MODE_CONTROL_MODE_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   BM1383AGLV_SUCCESS;
  }
  else
  {
    return   BM1383AGLV_FAILURE;
  }
}



/**
 * @brief       BM1383AGLV_GetStatus ( I2C_parameters_t , BM1383AGLV_data_t* )
 *
 * @details     It gets the status flag.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myRD_DRDY: 	  Pressure and temperature measurement data ready bit.
 *
 *
 * @return       Status of BM1383AGLV_GetStatus.
 *
 *
 * @author      Manuel Caballero
 * @date        12/September/2019
 * @version     12/September/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BM1383AGLV_status_t BM1383AGLV_GetStatus ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t* myRD_DRDY )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd	 =   BM1383AGLV_STATUS;
  aux  	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux    =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data	 */
  myRD_DRDY->rd_drdy	 =	 (BM1383AGLV_reset_rd_drdy_t)( cmd );



  if ( aux == I2C_SUCCESS )
  {
    return   BM1383AGLV_SUCCESS;
  }
  else
  {
    return   BM1383AGLV_FAILURE;
  }
}



/**
 * @brief       BM1383AGLV_GetRawPressure ( I2C_parameters_t , BM1383AGLV_data_t* )
 *
 * @details     It gets the raw pressure.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myRawP: 	  	  Raw Pressure value.
 *
 *
 * @return       Status of BM1383AGLV_GetRawPressure.
 *
 *
 * @author      Manuel Caballero
 * @date        13/September/2019
 * @version     13/September/2019     The ORIGIN
 * @pre         This function uses auto-increment.
 * @warning     N/A.
 */
BM1383AGLV_status_t BM1383AGLV_GetRawPressure ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t* myRawP )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]	 =   BM1383AGLV_PRESSURE_MSB;
  aux  	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux    	 =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data	 */
  myRawP->rawPressure	 =	 cmd[0];
  myRawP->rawPressure  <<=	 8U;
  myRawP->rawPressure	|=	 cmd[1];
  myRawP->rawPressure  <<=	 8U;
  myRawP->rawPressure	|=	 cmd[2];

  myRawP->rawPressure  >>=	 2U;



  if ( aux == I2C_SUCCESS )
  {
    return   BM1383AGLV_SUCCESS;
  }
  else
  {
    return   BM1383AGLV_FAILURE;
  }
}



/**
 * @brief       BM1383AGLV_GetRawTemperature ( I2C_parameters_t , BM1383AGLV_data_t* )
 *
 * @details     It gets the raw temperature.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myRawT: 	  	  Raw Temperature value.
 *
 *
 * @return       Status of BM1383AGLV_GetRawTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        13/September/2019
 * @version     13/September/2019     The ORIGIN
 * @pre         This function uses auto-increment.
 * @warning     N/A.
 */
BM1383AGLV_status_t BM1383AGLV_GetRawTemperature ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t* myRawT )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]	 =   BM1383AGLV_TEMPERATURE_MSB;
  aux  	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux    	 =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data	 */
  myRawT->rawTemperature	=	 cmd[0];
  myRawT->rawTemperature  <<=	 8U;
  myRawT->rawTemperature   |=	 cmd[1];




  if ( aux == I2C_SUCCESS )
  {
    return   BM1383AGLV_SUCCESS;
  }
  else
  {
    return   BM1383AGLV_FAILURE;
  }
}



/**
 * @brief       BM1383AGLV_GetPressure ( I2C_parameters_t , BM1383AGLV_data_t* )
 *
 * @details     It gets the pressure.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myP: 	  	  	  Pressure value.
 *
 *
 * @return       Status of BM1383AGLV_GetPressure.
 *
 *
 * @author      Manuel Caballero
 * @date        16/September/2019
 * @version     16/September/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BM1383AGLV_status_t BM1383AGLV_GetPressure ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t* myP )
{
  BM1383AGLV_status_t aux;

  /* Read the register   */
  aux	 =   BM1383AGLV_GetRawPressure ( myI2Cparameters, &(*myP) );

  /* Parse the data	 */
  myP->pressure	 =	 ( ( ( ( myP->rawPressure >> 14U ) & 0xFF ) * 16384.0 ) + ( ( myP->rawPressure >> 6U ) & 0xFF ) * 64.0 );
  myP->pressure	/=	2048.0;



  return   aux;
}



/**
 * @brief       BM1383AGLV_GetTemperature ( I2C_parameters_t , BM1383AGLV_data_t* )
 *
 * @details     It gets the temperature.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myT: 	  	  	  Temperature value.
 *
 *
 * @return       Status of BM1383AGLV_GetTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        16/September/2019
 * @version     16/September/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BM1383AGLV_status_t BM1383AGLV_GetTemperature ( I2C_parameters_t myI2Cparameters, BM1383AGLV_data_t* myT )
{
  BM1383AGLV_status_t aux;

  /* Read the register   */
  aux	 =   BM1383AGLV_GetRawTemperature ( myI2Cparameters, &(*myT) );

  /* Parse the data	 */
  myT->temperature	 =	 ( ( ( ( myT->rawTemperature >> 8U ) & 0xFF ) * 256.0 ) + ( myT->rawTemperature & 0xFF ) );
  myT->temperature	/=	32.0;



  return   aux;
}
