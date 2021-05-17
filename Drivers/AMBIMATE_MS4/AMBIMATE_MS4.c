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
 * @brief       AMBIMATE_MS4_TriggerContinuousMeasurement    ( I2C_parameters_t , uint16_t  )
 * @details     It triggers continuous measurement with or without ambient pressure compensation.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 * @param[in]    pressure_compensation: 0 (desactivates pressure compensation) or [700 - 1400]. Pressure in mBar.
 *
 * @param[out]   N/A
 *
 *
 * @return      Status of AMBIMATE_MS4_TriggerContinuousMeasurement.
 *
 * @author      Manuel Caballero
 * @date        17/May/2021
 * @version     17/May/2021    The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AMBIMATE_MS4_status_t  AMBIMATE_MS4_TriggerContinuousMeasurement ( I2C_parameters_t myI2Cparameters, uint16_t pressure_compensation )
{
  uint8_t       cmd[5] = { 0U };
  i2c_status_t  aux;

  /* Write the register  */
  cmd[2]   =  (uint8_t)( pressure_compensation >> 8U );
  cmd[3]   =  (uint8_t)( pressure_compensation & 0xFF );
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

