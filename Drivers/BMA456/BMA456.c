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


