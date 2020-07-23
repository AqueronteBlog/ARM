/**
 * @brief       SFM4100.c
 * @details     Low-cost Digital Mass Flow Meter for Gases.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/July/2020
 * @version     22/July/2020    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( https://www.nimbus.cit.ie ).
 */

#include "SFM4100.h"


/**
 * @brief       SFM4100_Init ( I2C_parameters_t );
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SFM4100_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        22/July/2020
 * @version     22/July/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SFM4100_status_t SFM4100_Init ( I2C_parameters_t myI2Cparameters  )
{
  i2c_status_t aux =  I2C_SUCCESS;;

  aux  |=   i2c_init ( myI2Cparameters );



  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_SoftReset ( I2C_parameters_t );
 *
 * @details     It triggers a softreset.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SFM4100_SoftReset.
 *
 *
 * @author      Manuel Caballero
 * @date        22/June/2020
 * @version     22/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SFM4100_status_t SFM4100_SoftReset ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd   =  0U;
  i2c_status_t aux   =  I2C_SUCCESS;

  /* Write the register  */
  cmd   =   SFM4100_SOFT_RESET;
  aux  |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_TriggerNewFlow ( I2C_parameters_t );
 *
 * @details     It triggers a new flow measurement.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SFM4100_TriggerNewFlow.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2020
 * @version     23/June/2020   The ORIGIN
 * @pre         N/A
 * @warning     This function must be called before any measurement is read.
 * @warning     This function doesn't generate any STOP command on the I2C so, a read
 * 				function either SFM4100_GetRawFlow or SFM4100_GetFlow must be called.
 */
SFM4100_status_t SFM4100_TriggerNewFlow ( I2C_parameters_t myI2Cparameters )
{
  uint8_t      cmd   =  0U;
  i2c_status_t aux   =  I2C_SUCCESS;

  /* Write the register  */
  cmd   =   SFM4100_TRIGGER_FLOW_MEASUREMENT;
  aux  |=   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );



  if ( aux == I2C_SUCCESS )
  {
    return   SFM4100_SUCCESS;
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_GetRawFlow ( I2C_parameters_t , SFM4100_data_t* );
 *
 * @details     It gets the raw flow value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myRawFlow.
 *
 *
 * @return       Status of SFM4100_GetRawFlow.
 *
 *
 * @author      Manuel Caballero
 * @date        22/June/2020
 * @version     23/June/2020   To trigger a new flow value was removed from this function,
 * 							   a separate function was created to do such a task.
 * 				22/June/2020   The ORIGIN
 * @pre         This function also checks that the data is valid ( CRC )
 * @warning     SFM4100_TriggerNewFlow function must be called before.
 */
SFM4100_status_t SFM4100_GetRawFlow	( I2C_parameters_t myI2Cparameters, SFM4100_data_t* myRawFlow )
{
  uint8_t      		cmd[3]   	=  { 0U };
  i2c_status_t 		aux   		=  I2C_SUCCESS;
  SFM4100_status_t 	checksum 	=  SFM4100_SUCCESS;


  /* Read the register  */
  aux  		|=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

  /* Parse the data	 */
  myRawFlow->conversion.raw_flow	=	 cmd[0];
  myRawFlow->conversion.raw_flow <<=	 8U;
  myRawFlow->conversion.raw_flow  |=	 cmd[1];

  /* Check the integrity of the value ( CRC )	 */
  checksum	 =	 SFM4100_CalculateCRC ( &(*myRawFlow) );



  if ( aux == I2C_SUCCESS )
  {
	if ( checksum != SFM4100_DATA_CORRUPTED )
	{
		return  SFM4100_SUCCESS;
	}
	else
	{
		return	SFM4100_DATA_CORRUPTED;
	}
  }
  else
  {
    return   SFM4100_FAILURE;
  }
}



/**
 * @brief       SFM4100_GetFlow ( I2C_parameters_t , SFM4100_data_t* );
 *
 * @details     It gets the flow value.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myFlow:		Current flow ( in slm ) and CRC value.
 *
 *
 * @return       Status of SFM4100_GetFlow.
 *
 *
 * @author      Manuel Caballero
 * @date        23/June/2020
 * @version     23/June/2020   The ORIGIN
 * @pre         This function also checks that the data is valid ( CRC ) and updates the flow raw value.
 * @warning     SFM4100_TriggerNewFlow function must be called before.
 */
SFM4100_status_t SFM4100_GetFlow ( I2C_parameters_t myI2Cparameters, SFM4100_data_t* myFlow )
{
  SFM4100_status_t 	aux 	=  SFM4100_SUCCESS;

  /* Read the register  */
  aux	 =	 SFM4100_GetRawFlow	( myI2Cparameters, &(*myFlow) );

  /* Parse the data	 */
  myFlow->conversion.flow_slm	/=	 1000.0;


  return aux;
}



/**
 * @brief       SFM4100_CalculateCRC ( SFM4100_data_t* );
 *
 * @details     It calculates the CRC after a the flow value is read.
 *
 * @param[in]    myCRC: 		  Current data to be checked.
 *
 * @param[out]   myCRC:			  Raw and current CRC values.
 *
 *
 * @return       Status of SFM4100_GetRawFlow.
 *
 *
 * @author      Manuel Caballero
 * @date        22/June/2020
 * @version     22/June/2020   The ORIGIN
 * @pre         Based on: Application Note for I2C Flow and Differential Pressure Sensors. CRC Checksum
 * @warning     N/A.
 */
SFM4100_status_t SFM4100_CalculateCRC ( SFM4100_data_t* myCRC )
{
  uint8_t 	byteCtr	=  0U;
  uint8_t 	bit		=  0U;
  uint8_t	data[2] =  { 0U };

  /* Update the data	 */
  data[0]	 =	 (uint8_t)( myCRC->conversion.raw_flow >> 8U );
  data[1]	 =	 (uint8_t)( myCRC->conversion.raw_flow );


  /* Read the register  */
  for ( byteCtr = 0; byteCtr < 2U; ++byteCtr )
  {
	  myCRC->crc.calculated_crc ^= (data[byteCtr]);
	  for ( bit = 8U; bit > 0U; --bit )
	  {
		if ( myCRC->crc.calculated_crc & 0x80 )
		{
			myCRC->crc.calculated_crc = ( myCRC->crc.calculated_crc << 1U ) ^ SFM4100_POLYNOMIAL;
		}
		else
		{
			myCRC->crc.calculated_crc = ( myCRC->crc.calculated_crc << 1U );
		}
	  }
  }



  if ( myCRC->crc.calculated_crc != myCRC->crc.current_crc )
  {
    return   SFM4100_DATA_CORRUPTED;
  }
  else
  {
    return   SFM4100_SUCCESS;
  }
}
