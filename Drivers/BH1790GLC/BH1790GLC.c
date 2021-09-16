/**
 * @brief       BH1790GLC.c
 * @details     Optical Sensor for Heart Rate Monitor IC.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        04/November/2019
 * @version     04/November/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "BH1790GLC.h"


/**
 * @brief       BH1790GLC_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BH1790GLC_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        04/November/2019
 * @version     04/November/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_Init ( I2C_parameters_t myI2Cparameters )
{
	i2c_status_t aux;

	aux  =   i2c_init ( myI2Cparameters );


	if ( aux == I2C_SUCCESS )
	{
		return   BH1790GLC_SUCCESS;
	}
	else
	{
		return   BH1790GLC_FAILURE;
	}
}



/**
 * @brief       BH1790GLC_GetManufacturerID ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the manufacturer ID.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myManufacturerID:	Manufacturer ID.
 *
 *
 * @return       Status of BH1790GLC_GetManufacturerID.
 *
 *
 * @author      Manuel Caballero
 * @date        19/November/2019
 * @version     19/November/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetManufacturerID ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myManufacturerID )
{
	uint8_t		 cmd = 0;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   BH1790GLC_MANUFACTURER_ID;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );


	/* Parse data   */
	myManufacturerID->manufacturer_id	=	 cmd;



	if ( aux == I2C_SUCCESS )
	{
		return   BH1790GLC_SUCCESS;
	}
	else
	{
		return   BH1790GLC_FAILURE;
	}
}



/**
 * @brief       BH1790GLC_GetPartID ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the part ID.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myPartID:			Part ID.
 *
 *
 * @return       Status of BH1790GLC_GetPartID.
 *
 *
 * @author      Manuel Caballero
 * @date        19/November/2019
 * @version     19/November/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetPartID ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myPartID )
{
	uint8_t		 cmd = 0;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   BH1790GLC_PART_ID;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );


	/* Parse data   */
	myPartID->part_id	=	 cmd;



	if ( aux == I2C_SUCCESS )
	{
		return   BH1790GLC_SUCCESS;
	}
	else
	{
		return   BH1790GLC_FAILURE;
	}
}



/**
 * @brief       BH1790GLC_SoftReset ( I2C_parameters_t )
 *
 * @details     It performs a software reset.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BH1790GLC_SoftReset.
 *
 *
 * @author      Manuel Caballero
 * @date        19/November/2019
 * @version     19/November/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_SoftReset ( I2C_parameters_t myI2Cparameters )
{
	uint8_t		 cmd[2] = { 0 };
	i2c_status_t aux;

	/* Update the register */
	cmd[0]	 =   BH1790GLC_RESET;
	cmd[1]	 =   RESET_SWRESET_ENABLED;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



	if ( aux == I2C_SUCCESS )
	{
		return   BH1790GLC_SUCCESS;
	}
	else
	{
		return   BH1790GLC_FAILURE;
	}
}


/**
 * @brief       BH1790GLC_StartMeasurement ( I2C_parameters_t , BH1790GLC_data_t )
 *
 * @details     It triggers a new measurement sample.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myConfData:   		System control setting and Measurement control setting.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BH1790GLC_StartMeasurement.
 *
 *
 * @author      Manuel Caballero
 * @date        20/November/2019
 * @version     22/November/2019   System and Measurement Control settings are added. It seems that the device
 * 								   must be configured writing to all the registers without a STOP bit (I2C).
 * 				20/November/2019   The ORIGIN
 * @pre         Start measurement by writing �MEAS_ST=1� after writing �RDY=1�. Measurement doesn�t
 * 				restart if writing �MEAS_ST=1� after start measurement. When stop measurement, write �SWRESET=1�
 * 				without writing �MEAS_ST=0� (for changing some parameters as well).
 * @pre         The user MUST RESPECT the measurement time, T_INT = 28ms ( maximum ).
 * @pre         The function uses auto-increment.
 * @warning     System control setting and measurement control setting must be initialized in order to guarantee
 * 				the correct behavior of the device.
 */
BH1790GLC_status_t BH1790GLC_StartMeasurement ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myConfData )
{
	uint8_t		 cmd[4] = { 0 };
	i2c_status_t aux;

	/* Write the register */
	cmd[0]	 =   BH1790GLC_MEAS_CONTROL1;
	cmd[1]	 =   ( myConfData.rdy | myConfData.led_lighting_freq | myConfData.rcycle );
	cmd[2]	 =	 ( myConfData.led_en | myConfData.led_on_time | myConfData.led_current );
	cmd[3]	 =	 MEAS_START_MEAS_ST_MEASUREMENT_START;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



	if ( aux == I2C_SUCCESS )
	{
		return   BH1790GLC_SUCCESS;
	}
	else
	{
		return   BH1790GLC_FAILURE;
	}
}



/**
 * @brief       BH1790GLC_GetRawDataOut ( I2C_parameters_t )
 *
 * @details     It gets the DATAOUT ( DATAOUT_LEDOFF and DATAOUT_LEDON data ). Raw data value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawDataOut:		Raw data for DATAOUT_LEDOFF and DATAOUT_LEDON.
 *
 *
 * @return       Status of BH1790GLC_GetRawDataOut.
 *
 *
 * @author      Manuel Caballero
 * @date        20/November/2019
 * @version     16/September/2021  Bug was fixed, the data must be switched.
 * 				20/November/2019   The ORIGIN
 * @pre         This function uses auto-increment.
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetRawDataOut ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myRawDataOut )
{
	uint8_t		 cmd[4] = { 0 };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   BH1790GLC_DATAOUT_LEDOFF_LSB;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Parse the data	 */
	myRawDataOut->dataOut_LED_OFF   =	 cmd[1];
	myRawDataOut->dataOut_LED_OFF <<=	 8U;
	myRawDataOut->dataOut_LED_OFF  |=	 cmd[0];

	myRawDataOut->dataOut_LED_ON	=	 cmd[3];
	myRawDataOut->dataOut_LED_ON  <<=	 8U;
	myRawDataOut->dataOut_LED_ON   |=	 cmd[2];



	if ( aux == I2C_SUCCESS )
	{
		return   BH1790GLC_SUCCESS;
	}
	else
	{
		return   BH1790GLC_FAILURE;
	}
}
