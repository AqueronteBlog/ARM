/**
 * @brief       BMA456.c
 * @details     MEMS nano pressure sensor: 260-1260 hPa absolute digital output barometer.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        15/June/2019
 * @version     15/June/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "BMA456.h"


/**
 * @brief       BMA456_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BMA456_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        08/June/2019
 * @version     08/June/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BMA456_status_t BMA456_Init ( I2C_parameters_t myI2Cparameters )
{
  i2c_status_t aux;

  aux  =   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetID ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the device ID.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myID:            Device ID.
 *
 *
 * @return       Status of BMA456_GetID.
 *
 *
 * @author      Manuel Caballero
 * @date        04/July/2019
 * @version     04/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetID ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myID )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_CHIP_ID;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data   */
  myID->chip_id   =   cmd;



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetSensorErrorConditions ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It reports sensor error conditions.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myErrors:        It reports sensor error conditions.
 *
 *
 * @return       Status of BMA456_GetSensorErrorConditions.
 *
 *
 * @author      Manuel Caballero
 * @date        04/July/2019
 * @version     04/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetSensorErrorConditions ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myErrors )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_ERR_REG;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data   */
  myErrors->aux_err      =   (BMA456_err_reg_aux_err_t)( cmd & ERR_REG_AUX_ERR_MASK );
  myErrors->fifo_err     =   (BMA456_err_reg_fifo_err_t)( cmd & ERR_REG_FIFO_ERR_MASK );
  myErrors->error_code   =   (BMA456_err_reg_error_code_t)( cmd & ERR_REG_ERROR_CODE_MASK );
  myErrors->cmd_err      =   (BMA456_err_reg_cmd_err_t)( cmd & ERR_REG_CMD_ERR_MASK );
  myErrors->fatal_err    =   (BMA456_err_reg_fatal_err_t)( cmd & ERR_REG_FATAL_ERR_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetSensorStatusFlags ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It reports sensor status flags.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myErrors:        It reports sensor status flags.
 *
 *
 * @return       Status of BMA456_GetSensorStatusFlags.
 *
 *
 * @author      Manuel Caballero
 * @date        04/July/2019
 * @version     04/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetSensorStatusFlags ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myStatusFlags )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_STATUS;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data   */
  myStatusFlags->drdy_acc    =   (BMA456_status_drdy_acc_t)( cmd & STATUS_DRDY_ACC_MASK );
  myStatusFlags->drdy_aux    =   (BMA456_status_drdy_aux_t)( cmd & STATUS_DRDY_AUX_MASK );
  myStatusFlags->cmd_rdy     =   (BMA456_status_cmd_rdy_t)( cmd & STATUS_CMD_RDY_MASK );
  myStatusFlags->aux_man_op  =   (BMA456_status_aux_man_op_t)( cmd & STATUS_AUX_MAN_OP_MASK );




  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetAuRawxData ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets aux raw data ( X, Y, Z and R ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myAuxRawData:    Auxiliary raw data.
 *
 *
 * @return       Status of BMA456_GetAuRawxData.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         This function uses auto-increment access.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetAuRawxData ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAuxRawData )
{
  uint8_t      cmd[8]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   BMA456_DATA_0;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data   */
  myAuxRawData->aux_raw_x   =   cmd[1];
  myAuxRawData->aux_raw_x <<=   8U;
  myAuxRawData->aux_raw_x  |=   cmd[0];

  myAuxRawData->aux_raw_y   =   cmd[3];
  myAuxRawData->aux_raw_y <<=   8U;
  myAuxRawData->aux_raw_y  |=   cmd[2];

  myAuxRawData->aux_raw_z   =   cmd[5];
  myAuxRawData->aux_raw_z <<=   8U;
  myAuxRawData->aux_raw_z  |=   cmd[4];

  myAuxRawData->aux_raw_r   =   cmd[7];
  myAuxRawData->aux_raw_r <<=   8U;
  myAuxRawData->aux_raw_r  |=   cmd[6];




  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetAccRawData ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets acceleration raw data ( X, Y and Z ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myAccRawData:    Acceleration raw data.
 *
 *
 * @return       Status of BMA456_GetAccRawData.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         This function uses auto-increment access.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetAccRawData ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAccRawData )
{
  uint8_t      cmd[6]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   BMA456_DATA_8;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data   */
  myAccRawData->acc_raw_x   =   cmd[1];
  myAccRawData->acc_raw_x <<=   8U;
  myAccRawData->acc_raw_x  |=   cmd[0];

  myAccRawData->acc_raw_y   =   cmd[3];
  myAccRawData->acc_raw_y <<=   8U;
  myAccRawData->acc_raw_y  |=   cmd[2];

  myAccRawData->acc_raw_z   =   cmd[5];
  myAccRawData->acc_raw_z <<=   8U;
  myAccRawData->acc_raw_z  |=   cmd[4];




  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetSensorTime ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets sensor time ( raw value ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   mySensorTime:    Sensor time raw value.
 *
 *
 * @return       Status of BMA456_GetSensorTime.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         This function uses auto-increment access.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetSensorTime ( I2C_parameters_t myI2Cparameters, BMA456_data_t* mySensorTime )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   BMA456_SENSOR_TIME_0;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data   */
  mySensorTime->sensor_time   =   cmd[2];
  mySensorTime->sensor_time <<=   8U;
  mySensorTime->sensor_time  |=   cmd[1];
  mySensorTime->sensor_time <<=   8U;
  mySensorTime->sensor_time  |=   cmd[0];



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetEvent ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets sensor status flag ( POR event ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myEvent:         Power-up/Softreset flag value.
 *
 *
 * @return       Status of BMA456_GetEvent.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         Clear-on-read.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetEvent ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myEvent )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_SENSOR_TIME_0;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );
  
  /* Parse the data   */
  myEvent->por_detected   =   (BMA456_event_por_detected_t)cmd;



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetIntStatus ( I2C_parameters_t , BMA456_int_status_t* )
 *
 * @details     It gets interrupt/feature status.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myIntStatus:     Interrupt/Feature status.
 *
 *
 * @return       Status of BMA456_GetIntStatus.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         This function uses auto-increment access.
 * @pre         All the flags will be cleared on read.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetIntStatus ( I2C_parameters_t myI2Cparameters, BMA456_int_status_t* myIntStatus )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   BMA456_INT_STATUS_0;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data   */
  myIntStatus->error_int_out      =   (BMA456_int_status_0_error_int_out_t)( cmd[0] & INT_STATUS_0_ERROR_INT_OUT_MASK );
  myIntStatus->any_no_motion_out  =   (BMA456_int_status_0_any_no_motion_out_t)( cmd[0] & INT_STATUS_0_ANY_NO_MOTION_OUT_MASK );
  myIntStatus->wakeup_out         =   (BMA456_int_status_0_wakeup_out_t)( cmd[0] & INT_STATUS_0_WAKEUP_OUT_MASK );
  myIntStatus->wrist_tilt_out     =   (BMA456_int_status_0_wrist_tilt_out_t)( cmd[0] & INT_STATUS_0_WRIST_TILT_OUT_MASK );
  myIntStatus->activity_type_out  =   (BMA456_int_status_0_activity_type_out_t)( cmd[0] & INT_STATUS_0_ACTIVITY_TYPE_OUT_MASK );
  myIntStatus->step_counter_out   =   (BMA456_int_status_0_step_counter_out_t)( cmd[0] & INT_STATUS_0_STEP_COUNTER_OUT_MASK );
  myIntStatus->acc_drdy_int       =   (BMA456_int_status_1_acc_drdy_int_t)( cmd[1] & INT_STATUS_1_ACC_DRDY_INT_MASK );
  myIntStatus->aux_drdy_int       =   (BMA456_int_status_1_aux_drdy_int_t)( cmd[1] & INT_STATUS_1_AUX_DRDY_INT_MASK );
  myIntStatus->fwm_int            =   (BMA456_int_status_1_fwm_int_t)( cmd[1] & INT_STATUS_1_FWM_INT_MASK );
  myIntStatus->ffull_int          =   (BMA456_int_status_1_ffull_int_t)( cmd[1] & INT_STATUS_1_FFULL_INT_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetStepCounter ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets step counter value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myStepCounter:   Step counter value.
 *
 *
 * @return       Status of BMA456_GetStepCounter.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         This function uses auto-increment access.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetStepCounter ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myStepCounter )
{
  uint8_t      cmd[4]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   BMA456_STEP_COUNTER_0;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data   */
  myStepCounter->step_counter   =  cmd[3];
  myStepCounter->step_counter <<=  8U;
  myStepCounter->step_counter  |=  cmd[2];
  myStepCounter->step_counter <<=  8U;
  myStepCounter->step_counter  |=  cmd[1];
  myStepCounter->step_counter <<=  8U;
  myStepCounter->step_counter  |=  cmd[0];



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetRawTemperature ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the temperature raw value of the sensor.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawTemperature:  Temperature raw value of the sensor.
 *
 *
 * @return       Status of BMA456_GetRawTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         Temperature value in two's complement representation in units of 1 Kelvin: 0x00 corresponds to 23 degree Celsius.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetRawTemperature ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myRawTemperature )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_TEMPERATURE;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myRawTemperature->rawTemperature   =   cmd;



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetFIFO_Length ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the FIFO length.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myFIFOlen:       FIFO byte counter register.
 *
 *
 * @return       Status of BMA456_GetFIFO_Length.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         This function uses auto-increment access.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetFIFO_Length ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myFIFOlen )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   BMA456_FIFO_LENGTH_0;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data   */
  myFIFOlen->fifo_byte_counter   =   cmd[1];
  myFIFOlen->fifo_byte_counter <<=   8U;
  myFIFOlen->fifo_byte_counter  |=   cmd[0];



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetFIFO_Data ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the FIFO data output.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myFIFOdata:      FIFO data output register.
 *
 *
 * @return       Status of BMA456_GetFIFO_Data.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetFIFO_Data ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myFIFOdata )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_FIFO_DATA;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myFIFOdata->fifo_data  =   cmd;



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetActivityType ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the activity type ( Running, walking or still ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myActivityType:  Step counter activity output ( Running, walking or still ).
 *
 *
 * @return       Status of BMA456_GetActivityType.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetActivityType ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myActivityType )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_ACTIVITY_TYPE;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myActivityType->activity_type_out  =   (BMA456_activity_type_activity_type_out_t)( cmd & ACTIVITY_TYPE_ACTIVITY_TYPE_OUT_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetInternalStatus ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the internal status.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myInternalStatus:  Error bits and message indicating internal status.
 *
 *
 * @return       Status of BMA456_GetInternalStatus.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetInternalStatus ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myInternalStatus )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_INTERNAL_STATUS;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myInternalStatus->odr_high_error     =   (BMA456_internal_status_odr_high_error_t)( cmd & INTERNAL_STATUS_ODR_HIGH_ERROR_MASK );
  myInternalStatus->odr_50hz_error     =   (BMA456_internal_status_odr_50hz_error_t)( cmd & INTERNAL_STATUS_ODR_50HZ_ERROR_MASK );
  myInternalStatus->axes_remap_error   =   (BMA456_internal_status_axes_remap_error_t)( cmd & INTERNAL_STATUS_AXES_REMAP_ERROR_MASK );
  myInternalStatus->message            =   (BMA456_internal_status_message_t)( cmd & INTERNAL_STATUS_MESSAGE_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetAccConf ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the accelerometer configuration of the acceleration sensor.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myAccConf:       ODR, bandwidth and the read mode of the acceleration sensor.
 *
 *
 * @return       Status of BMA456_GetAccConf.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetAccConf ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAccConf )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_ACC_CONF;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myAccConf->acc_perf_mode    =   (BMA456_acc_conf_acc_perf_mode_t)( cmd & ACC_CONF_ACC_PERF_MODE_MASK );
  myAccConf->acc_bwp          =   (BMA456_acc_conf_acc_bwp_t)( cmd & ACC_CONF_ACC_BWP_MASK );
  myAccConf->acc_odr          =   (BMA456_acc_conf_acc_odr_t)( cmd & ACC_CONF_ACC_ODR_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_SetAccConf ( I2C_parameters_t , BMA456_data_t )
 *
 * @details     It sets the accelerometer configuration of the acceleration sensor.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myAccConf:       ODR, bandwidth and the read mode of the acceleration sensor.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BMA456_SetAccConf.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_SetAccConf ( I2C_parameters_t myI2Cparameters, BMA456_data_t myAccConf )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Write the register   */
  cmd[0]  =   BMA456_ACC_CONF;
  cmd[1]  =   ( myAccConf.acc_perf_mode | myAccConf.acc_bwp | myAccConf.acc_odr );
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetAccRange ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the accelerometer range: ±2g/±4g/±8g/±16g.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myAccRange:      Accelerometer range: ±2g/±4g/±8g/±16g.
 *
 *
 * @return       Status of BMA456_GetAccRange.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetAccRange ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAccRange )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_ACC_RANGE;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myAccRange->acc_range  =   (BMA456_acc_range_acc_acc_range_t)( cmd & ACC_RANGE_ACC_RANGE_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_SetAccRange ( I2C_parameters_t , BMA456_data_t )
 *
 * @details     It sets the accelerometer range: ±2g/±4g/±8g/±16g.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myAccRange:      Accelerometer range: ±2g/±4g/±8g/±16g.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BMA456_SetAccRange.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_SetAccRange ( I2C_parameters_t myI2Cparameters, BMA456_data_t myAccRange )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Write the register   */
  cmd[0]  =   BMA456_ACC_RANGE;
  cmd[1]  =   myAccRange.acc_range;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetAuxConf ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the auxiliary configuration of the auxiliary interface.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myAuxConf:       Sets the output data rate of the auxiliary interface.
 *
 *
 * @return       Status of BMA456_GetAuxConf.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetAuxConf ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAuxConf )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_AUX_CONF;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myAuxConf->aux_offset  =    ( cmd & AUX_CONF_AUX_OFFSET_MASK );
  myAuxConf->aux_odr     =   (BMA456_aux_conf_aux_odr_t)( cmd & AUX_CONF_AUX_ODR_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_SetAuxConf ( I2C_parameters_t , BMA456_data_t )
 *
 * @details     It sets the auxiliary configuration of the auxiliary interface.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myAuxConf:       Sets the output data rate of the auxiliary interface.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BMA456_SetAuxConf.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_SetAuxConf ( I2C_parameters_t myI2Cparameters, BMA456_data_t myAuxConf )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;
  
  /* Check value of the offset, maximum value is 15   */
  if ( myAuxConf.aux_offset > 15U )
  {
    return   BMA456_FAILURE;
  }
  else
  {
    /* Write the register   */
    cmd[0]  =   BMA456_AUX_CONF;
    cmd[1]  =   ( ( myAuxConf.aux_offset << 4U ) | myAuxConf.aux_odr );
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_STOP_BIT );
  }



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetFIFO_Downs ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the sensor configuration downsampling rates for FIFO.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myFIFOdowns:     Configure accelerometer downsampling rates for FIFO.
 *
 *
 * @return       Status of BMA456_GetFIFO_Downs.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetFIFO_Downs ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myFIFOdowns )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_FIFO_DOWNS;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myFIFOdowns->acc_fifo_filt_data  =   ( cmd & FIFO_DOWNS_ACC_FIFO_DOWNS_MASK );
  myFIFOdowns->acc_fifo_downs      =   (BMA456_fifo_downs_acc_fifo_filt_data_t)( cmd & FIFO_DOWNS_ACC_FIFO_FILT_DATA_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_SetFIFO_Downs ( I2C_parameters_t , BMA456_data_t )
 *
 * @details     It sets the sensor configuration downsampling rates for FIFO.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myFIFOdowns:     Configuration for accelerometer downsampling rates for FIFO.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BMA456_SetFIFO_Downs.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_SetFIFO_Downs ( I2C_parameters_t myI2Cparameters, BMA456_data_t myFIFOdowns )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;
  
  /* Check acc_fifo_downs value, it cannot be greater than 7   */
  if ( myFIFOdowns.acc_fifo_downs > 7U )
  {
    return   BMA456_FAILURE;
  }
  else
  {
    /* Write the register   */
    cmd[0]  =   BMA456_FIFO_DOWNS;
    cmd[1]  =   ( ( myFIFOdowns.acc_fifo_downs << 4U ) | myFIFOdowns.acc_fifo_filt_data );
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  }



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetFIFO_Watermark ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the FIFO watermark level.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myFIFOwtm:       Configure accelerometer downsampling rates for FIFO.
 *
 *
 * @return       Status of BMA456_GetFIFO_Watermark.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         This function uses auto-increment access.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetFIFO_Watermark ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myFIFOwtm )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   BMA456_FIFO_WTM_0;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data   */
  myFIFOwtm->fifo_water_mark   =   ( cmd[1] & 0x1F );
  myFIFOwtm->fifo_water_mark <<=   8U;
  myFIFOwtm->fifo_water_mark  |=   cmd[0];



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_SetFIFO_Watermark ( I2C_parameters_t , BMA456_data_t )
 *
 * @details     It sets the FIFO watermark level.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myFIFOwtm:       Aaccelerometer downsampling rates configuration for FIFO.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of BMA456_GetFIFO_Watermark.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         This function uses auto-increment access.
 * @warning     N/A.
 */
BMA456_status_t BMA456_SetFIFO_Watermark ( I2C_parameters_t myI2Cparameters, BMA456_data_t myFIFOwtm )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;
  
  /* Check acc_fifo_downs value, it cannot be greater than 0x1FFF   */
  if ( myFIFOwtm.fifo_water_mark > 0x1FFF )
  {
    return   BMA456_FAILURE;
  }
  else
  {
    /* Write the register   */
    cmd[0]  =   BMA456_FIFO_WTM_0;
    cmd[1]  =   (uint8_t)( myFIFOwtm.fifo_water_mark );
    cmd[2]  =   (uint8_t)( myFIFOwtm.fifo_water_mark >> 8U );
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  }



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetFIFO_Config ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the FIFO frame content configuration.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myFIFOconfig:    FIFO frame content configuration.
 *
 *
 * @return       Status of BMA456_GetFIFO_Config.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         This function uses auto-increment access.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetFIFO_Config ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myFIFOconfig )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;

  /* Read the register   */
  cmd[0]  =   BMA456_FIFO_CONFIG_0;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
  aux     =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data   */
  myFIFOconfig->fifo_time_en      =   (BMA456_fifo_config_0_fifo_time_en_t)( cmd[0] & FIFO_CONFIG_0_FIFO_TIME_EN_MASK );
  myFIFOconfig->fifo_stop_on_full =   (BMA456_fifo_config_0_fifo_stop_on_full_t)( cmd[0] & FIFO_CONFIG_0_FIFO_STOP_ON_FULL_MASK );
  myFIFOconfig->fifo_acc_en       =   (BMA456_fifo_config_1_fifo_acc_en_t)( cmd[1] & FIFO_CONFIG_1_FIFO_ACC_EN_MASK );
  myFIFOconfig->fifo_aux_en       =   (BMA456_fifo_config_1_fifo_aux_en_t)( cmd[1] & FIFO_CONFIG_1_FIFO_AUX_EN_MASK );
  myFIFOconfig->fifo_header_en    =   (BMA456_fifo_config_1_fifo_header_en_t)( cmd[1] & FIFO_CONFIG_1_FIFO_HEADER_EN_MASK );
  myFIFOconfig->fifo_tag_int1_en  =   (BMA456_fifo_config_1_fifo_tag_int1_en_t)( cmd[1] & FIFO_CONFIG_1_FIFO_TAG_INT1_EN_MASK );
  myFIFOconfig->fifo_tag_int2_en  =   (BMA456_fifo_config_1_fifo_tag_int2_en_t)( cmd[1] & FIFO_CONFIG_1_FIFO_TAG_INT2_EN_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_SetFIFO_Config ( I2C_parameters_t , BMA456_data_t )
 *
 * @details     It sets the FIFO frame content configuration.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myFIFOconfig:    FIFO frame content configuration.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of BMA456_SetFIFO_Config.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         This function uses auto-increment access.
 * @warning     N/A.
 */
BMA456_status_t BMA456_SetFIFO_Config ( I2C_parameters_t myI2Cparameters, BMA456_data_t myFIFOconfig )
{
  uint8_t      cmd[3]  = { 0U };
  i2c_status_t aux;
  
  /* Write the register   */
  cmd[0]  =   BMA456_FIFO_CONFIG_0;
  cmd[1]  =   (uint8_t)( myFIFOconfig.fifo_time_en | myFIFOconfig.fifo_stop_on_full );
  cmd[2]  =   (uint8_t)( myFIFOconfig.fifo_acc_en | myFIFOconfig.fifo_aux_en | myFIFOconfig.fifo_header_en | myFIFOconfig.fifo_tag_int1_en | myFIFOconfig.fifo_tag_int2_en );
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetAuxDevID ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the auxiliary interface slave ID.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myAuxDevID:      Auxiliary interface slave device ID.
 *
 *
 * @return       Status of BMA456_GetAuxDevID.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetAuxDevID ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAuxDevID )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_AUX_DEV_ID;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myAuxDevID->i2c_device_addr  =   ( cmd >> 1U );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_SetAuxDevID ( I2C_parameters_t , BMA456_data_t )
 *
 * @details     It sets the auxiliary interface slave ID.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myAuxDevID:      Auxiliary interface slave device ID..
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BMA456_GetAuxDevID.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_SetAuxDevID ( I2C_parameters_t myI2Cparameters, BMA456_data_t myAuxDevID )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;
  
  /* Check that the slave device ID is correct   */
  if ( myAuxDevID.i2c_device_addr > 254U )
  {
    return   BMA456_FAILURE;
  }
  else
  {
    /* Write the register   */
    cmd[0]  =   BMA456_AUX_DEV_ID;
    cmd[1]  =   (uint8_t)( ( myAuxDevID.i2c_device_addr << 1U ) & AUX_DEV_ID_I2C_DEVICE_ADDR_MASK );
    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
  }



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetAuxIfConf ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the auxiliary interface configuration.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myAuxIfConf:     Auxiliary interface configuration.
 *
 *
 * @return       Status of BMA456_GetAuxIfConf.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetAuxIfConf ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAuxIfConf )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_AUX_IF_CONF;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myAuxIfConf->aux_manual_en  =   (BMA456_aux_if_conf_aux_manual_en_t)( cmd & AUX_IF_CONF_AUX_MANUAL_EN_MASK );
  myAuxIfConf->aux_rd_burst   =   (BMA456_aux_if_conf_aux_rd_burst_t)( cmd & AUX_IF_CONF_AUX_RD_BURST_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_SetAuxIfConf ( I2C_parameters_t , BMA456_data_t )
 *
 * @details     It gets the auxiliary interface configuration.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myAuxIfConf:     Auxiliary interface configuration.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of BMA456_GetAuxIfConf.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_SetAuxIfConf ( I2C_parameters_t myI2Cparameters, BMA456_data_t myAuxIfConf )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;
  
  /* Write the register   */
  cmd[0]  =   BMA456_AUX_IF_CONF;
  cmd[1]  =   (uint8_t)( myAuxIfConf.aux_manual_en | myAuxIfConf.aux_rd_burst );
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetAuxRdAddr ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the auxiliary interface read register address.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myAuxRdAddr:     Auxiliary interface, address to read.
 *
 *
 * @return       Status of BMA456_GetAuxRdAddr.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetAuxRdAddr ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAuxRdAddr )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_AUX_RD_ADDR;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myAuxRdAddr->read_addr  =   cmd;



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_SetAuxRdAddr ( I2C_parameters_t , BMA456_data_t )
 *
 * @details     It gsets the auxiliary interface read register address.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myAuxRdAddr:     Auxiliary interface, address to read.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BMA456_GetAuxRdAddr.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_SetAuxRdAddr ( I2C_parameters_t myI2Cparameters, BMA456_data_t myAuxRdAddr )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;
  
  /* Write the register   */
  cmd[0]  =   BMA456_AUX_RD_ADDR;
  cmd[1]  =   myAuxRdAddr.read_addr;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetAuxWdAddr ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the auxiliary interface write register address.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myAuxWdAddr:     Auxiliary interface, address to write.
 *
 *
 * @return       Status of BMA456_GetAuxWdAddr.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetAuxWdAddr ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAuxWdAddr )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_AUX_WR_ADDR;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myAuxWdAddr->write_addr  =   cmd;



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_SetAuxWdAddr ( I2C_parameters_t , BMA456_data_t )
 *
 * @details     It sets the auxiliary interface write register address.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myAuxWdAddr:     Auxiliary interface, address to write.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BMA456_SetAuxWdAddr.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_SetAuxWdAddr ( I2C_parameters_t myI2Cparameters, BMA456_data_t myAuxWdAddr )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;
  
  /* Write the register   */
  cmd[0]  =   BMA456_AUX_WR_ADDR;
  cmd[1]  =   myAuxWdAddr.write_addr;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetAuxWrData ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the auxiliary interface write data.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myAuxWrData:     Auxiliary interface, write data.
 *
 *
 * @return       Status of BMA456_GetAuxWrData.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetAuxWrData ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myAuxWrData )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_AUX_WR_DATA;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myAuxWrData->write_data  =   cmd;



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_SetAuxWrData ( I2C_parameters_t , BMA456_data_t )
 *
 * @details     It sets the auxiliary interface write data.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myAuxWrData:     Auxiliary interface, write data.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BMA456_GetAuxWrData.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_SetAuxWrData ( I2C_parameters_t myI2Cparameters, BMA456_data_t myAuxWrData )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;
  
  /* Write the register   */
  cmd[0]  =   BMA456_AUX_WR_DATA;
  cmd[1]  =   myAuxWrData.write_data;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetInt1_IO_Ctrl ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the configuration for the electrical behaviour of the interrupt pins ( INT1 ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myInt1_IO_Ctrl:  Configure the electrical behaviour of the interrupt pins.
 *
 *
 * @return       Status of BMA456_GetInt1_IO_Ctrl.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetInt1_IO_Ctrl ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myInt1_IO_Ctrl )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_INT1_IO_CTRL;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myInt1_IO_Ctrl->int1_input_en  =   (BMA456_int1_io_ctrl_input_en_t)( cmd & INT1_IO_CTRL_INPUT_EN_MASK );
  myInt1_IO_Ctrl->int1_output_en =   (BMA456_int1_io_ctrl_output_en_t)( cmd & INT1_IO_CTRL_OUTPUT_EN_MASK );
  myInt1_IO_Ctrl->int1_od        =   (BMA456_int1_io_ctrl_od_t)( cmd & INT1_IO_CTRL_OD_MASK );
  myInt1_IO_Ctrl->int1_lvl       =   (BMA456_int1_io_ctrl_lvl_t)( cmd & INT1_IO_CTRL_LVL_MASK );
  myInt1_IO_Ctrl->int1_edge_ctrl =   (BMA456_int1_io_ctrl_edge_ctrl_t)( cmd & INT1_IO_CTRL_EDGE_CTRL_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_SetInt1_IO_Ctrl ( I2C_parameters_t , BMA456_data_t )
 *
 * @details     It sets the configuration for the electrical behaviour of the interrupt pins ( INT1 ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myInt1_IO_Ctrl:  Configure the electrical behaviour of the interrupt pins.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BMA456_GetInt1_IO_Ctrl.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_SetInt1_IO_Ctrl ( I2C_parameters_t myI2Cparameters, BMA456_data_t myInt1_IO_Ctrl )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;
  
  /* Write the register   */
  cmd[0]  =   BMA456_INT1_IO_CTRL;
  cmd[1]  =   ( myInt1_IO_Ctrl.int1_input_en | myInt1_IO_Ctrl.int1_output_en | myInt1_IO_Ctrl.int1_od | myInt1_IO_Ctrl.int1_lvl | myInt1_IO_Ctrl.int1_edge_ctrl );
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetInt2_IO_Ctrl ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the configuration for the electrical behaviour of the interrupt pins ( INT2 ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myInt2_IO_Ctrl:  Configure the electrical behaviour of the interrupt pins.
 *
 *
 * @return       Status of BMA456_GetInt2_IO_Ctrl.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetInt2_IO_Ctrl ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myInt2_IO_Ctrl )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_INT2_IO_CTRL;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myInt2_IO_Ctrl->int1_input_en  =   (BMA456_int2_io_ctrl_input_en_t)( cmd & INT2_IO_CTRL_INPUT_EN_MASK );
  myInt2_IO_Ctrl->int1_output_en =   (BMA456_int2_io_ctrl_output_en_t)( cmd & INT2_IO_CTRL_OUTPUT_EN_MASK );
  myInt2_IO_Ctrl->int1_od        =   (BMA456_int2_io_ctrl_od_t)( cmd & INT2_IO_CTRL_OD_MASK );
  myInt2_IO_Ctrl->int1_lvl       =   (BMA456_int2_io_ctrl_lvl_t)( cmd & INT2_IO_CTRL_LVL_MASK );
  myInt2_IO_Ctrl->int1_edge_ctrl =   (BMA456_int2_io_ctrl_edge_ctrl_t)( cmd & INT2_IO_CTRL_EDGE_CTRL_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_SetInt2_IO_Ctrl ( I2C_parameters_t , BMA456_data_t )
 *
 * @details     It sets the configuration for the electrical behaviour of the interrupt pins ( INT2 ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myInt2_IO_Ctrl:  Configure the electrical behaviour of the interrupt pins.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BMA456_GetInt2_IO_Ctrl.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_SetInt2_IO_Ctrl ( I2C_parameters_t myI2Cparameters, BMA456_data_t myInt2_IO_Ctrl )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;
  
  /* Write the register   */
  cmd[0]  =   BMA456_INT2_IO_CTRL;
  cmd[1]  =   ( myInt2_IO_Ctrl.int2_input_en | myInt2_IO_Ctrl.int2_output_en | myInt2_IO_Ctrl.int2_od | myInt2_IO_Ctrl.int2_lvl | myInt2_IO_Ctrl.int2_edge_ctrl );
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetIntLatch ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the configuration for interrupt modes.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myIntLatch:      Latched/non-latched/temporary interrupt modes.
 *
 *
 * @return       Status of BMA456_GetIntLatch.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetIntLatch ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myIntLatch )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_INT_LATCH;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myIntLatch->int_latch =   (BMA456_int_latch_int_latch_t)( cmd & INT_LATCH_INT_LATCH_MASK );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_SetIntLatch ( I2C_parameters_t , BMA456_data_t )
 *
 * @details     It sets the configuration for interrupt modes.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myIntLatch:      Latched/non-latched/temporary interrupt modes.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BMA456_SetIntLatch.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_SetIntLatch ( I2C_parameters_t myI2Cparameters, BMA456_data_t myIntLatch )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;
  
  /* Write the register   */
  cmd[0]  =   BMA456_INT_LATCH;
  cmd[1]  =   myIntLatch.int_latch;
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetInt1Map ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the interrupt/feature mapping on INT1.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myInt1Map:       Interrupt/feature mapping on INT1.
 *
 *
 * @return       Status of BMA456_GetInt1Map.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetInt1Map ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myInt1Map )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_INT1_MAP;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myInt1Map->int1_error_int_out     =   (BMA456_int1_map_error_int_out_t)( cmd & INT1_MAP_ERROR_INT_OUT_MASK );
  myInt1Map->int1_any_no_motion_out =   (BMA456_int1_map_error_any_no_motion_out_t)( cmd & INT1_MAP_ERROR_ANY_NO_MOTION_OUT_MASK );
  myInt1Map->int1_wakeup_out        =   (BMA456_int1_map_error_wakeup_out_t)( cmd & INT1_MAP_ERROR_WAKEUP_OUT_MASK );
  myInt1Map->int1_wrist_tilt_out    =   (BMA456_int1_map_error_wrist_tilt_out_t)( cmd & INT1_MAP_ERROR_WRIST_TILT_OUT_MASK );
  myInt1Map->int1_activity_type_out =   (BMA456_int1_map_error_activity_type_out_t)( cmd & INT1_MAP_ERROR_ACTIVITY_TYPE_OUT_MASK );
  myInt1Map->int1_step_counter_out  =   (BMA456_int1_map_error_step_counter_out_t)( cmd & INT1_MAP_ERROR_STEP_COUNTER_OUT_MASK );


  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_SetInt1Map ( I2C_parameters_t , BMA456_data_t )
 *
 * @details     It sets the interrupt/feature mapping on INT1.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myInt1Map:       Interrupt/feature mapping on INT1.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BMA456_SetInt1Map.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_SetInt1Map ( I2C_parameters_t myI2Cparameters, BMA456_data_t myInt1Map )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;
  
  /* Write the register   */
  cmd[0]  =   BMA456_INT1_MAP;
  cmd[1]  =   ( myInt1Map.int1_error_int_out | myInt1Map.int1_any_no_motion_out | myInt1Map.int1_wakeup_out | myInt1Map.int1_wrist_tilt_out | myInt1Map.int1_activity_type_out | myInt1Map.int1_step_counter_out );
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_GetInt2Map ( I2C_parameters_t , BMA456_data_t* )
 *
 * @details     It gets the interrupt/feature mapping on INT2.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myInt2Map:       Interrupt/feature mapping on INT2.
 *
 *
 * @return       Status of BMA456_GetInt2Map.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_GetInt2Map ( I2C_parameters_t myI2Cparameters, BMA456_data_t* myInt2Map )
{
  uint8_t      cmd  = 0U;
  i2c_status_t aux;

  /* Read the register   */
  cmd  =   BMA456_INT2_MAP;
  aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
  aux  =   i2c_read  ( myI2Cparameters, &cmd, 1U );

  /* Parse the data   */
  myInt2Map->int2_error_int_out     =   (BMA456_int2_map_error_int_out_t)( cmd & INT2_MAP_ERROR_INT_OUT_MASK );
  myInt2Map->int2_any_no_motion_out =   (BMA456_int2_map_error_any_no_motion_out_t)( cmd & INT2_MAP_ERROR_ANY_NO_MOTION_OUT_MASK );
  myInt2Map->int2_wakeup_out        =   (BMA456_int2_map_error_wakeup_out_t)( cmd & INT2_MAP_ERROR_WAKEUP_OUT_MASK );
  myInt2Map->int2_wrist_tilt_out    =   (BMA456_int2_map_error_wrist_tilt_out_t)( cmd & INT2_MAP_ERROR_WRIST_TILT_OUT_MASK );
  myInt2Map->int2_activity_type_out =   (BMA456_int2_map_error_activity_type_out_t)( cmd & INT2_MAP_ERROR_ACTIVITY_TYPE_OUT_MASK );
  myInt2Map->int2_step_counter_out  =   (BMA456_int2_map_error_step_counter_out_t)( cmd & INT2_MAP_ERROR_STEP_COUNTER_OUT_MASK );


  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}



/**
 * @brief       BMA456_SetInt2Map ( I2C_parameters_t , BMA456_data_t )
 *
 * @details     It sets the interrupt/feature mapping on INT2.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myInt2Map:       Interrupt/feature mapping on INT2.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BMA456_SetInt2Map.
 *
 *
 * @author      Manuel Caballero
 * @date        08/July/2019
 * @version     08/July/2019     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BMA456_status_t BMA456_SetInt2Map ( I2C_parameters_t myI2Cparameters, BMA456_data_t myInt2Map )
{
  uint8_t      cmd[2]  = { 0U };
  i2c_status_t aux;
  
  /* Write the register   */
  cmd[0]  =   BMA456_INT2_MAP;
  cmd[1]  =   ( myInt2Map.int2_error_int_out | myInt2Map.int2_any_no_motion_out | myInt2Map.int2_wakeup_out | myInt2Map.int2_wrist_tilt_out | myInt2Map.int2_activity_type_out | myInt2Map.int2_step_counter_out );
  aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   BMA456_SUCCESS;
  }
  else
  {
    return   BMA456_FAILURE;
  }
}






