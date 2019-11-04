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
 * @pre         This code belongs to Nimbus Centre ( https://www.nimbus.cit.ie ).
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
 * @date        10/October/2019
 * @version     10/October/2019   The ORIGIN
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
 * @brief       BH1790GLC_GetRawTemperature ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the raw temperature.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawTemperature:	Raw temperature.
 *
 *
 * @return       Status of BH1790GLC_GetRawTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        14/October/2019
 * @version     14/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetRawTemperature  ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myRawTemperature )
{
	uint8_t		 cmd[2] = { 0 };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   BH1790GLC_TEMPERATURE_LOW;
	aux   	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux   	 =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


	/* Parse data   */
	myRawTemperature->rawTemperature	 =	 cmd[1];
	myRawTemperature->rawTemperature   <<=	 8U;
	myRawTemperature->rawTemperature	|=	 cmd[0];



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
 * @brief       BH1790GLC_GetTemperature ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the current temperature.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTemperature:		Current temperature.
 *
 *
 * @return       Status of BH1790GLC_GetTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        14/October/2019
 * @version     14/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetTemperature  ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myTemperature )
{
	BH1790GLC_status_t aux;

	/* Read the register */
	aux   	 =   BH1790GLC_GetRawTemperature  ( myI2Cparameters, &(*myTemperature) );

	/* Parse data   */
	myTemperature->temperature	=	( (float)( myTemperature->rawTemperature ) / 65536.0 ) * 165.0 - 40.0;


	return   aux;
}



/**
 * @brief       BH1790GLC_GetRawHumidity ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the raw humidity.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawTemperature:	Raw humidity.
 *
 *
 * @return       Status of BH1790GLC_GetRawHumidity.
 *
 *
 * @author      Manuel Caballero
 * @date        14/October/2019
 * @version     14/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetRawHumidity  ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myRawHumidity )
{
	uint8_t		 cmd[2] = { 0 };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   BH1790GLC_HUMIDITY_LOW;
	aux   	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux   	 =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


	/* Parse data   */
	myRawHumidity->rawHumidity	 =	 cmd[1];
	myRawHumidity->rawHumidity <<=	 8U;
	myRawHumidity->rawHumidity	|=	 cmd[0];



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
 * @brief       BH1790GLC_GetHumidity ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the current humidity.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTemperature:		Current humidity.
 *
 *
 * @return       Status of BH1790GLC_GetTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        14/October/2019
 * @version     14/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetHumidity  ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myHumidity )
{
	BH1790GLC_status_t aux;

	/* Read the register */
	aux   	 =   BH1790GLC_GetRawHumidity  ( myI2Cparameters, &(*myHumidity) );

	/* Parse data   */
	myHumidity->humidity	=	( (float)( myHumidity->rawHumidity ) / 65536.0 ) * 100.0;


	return   aux;
}



/**
 * @brief       BH1790GLC_GetInterrupt_DRDY_Status ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the interrupt DRDY status.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myStatus:			Interrupt DRDY status.
 *
 *
 * @return       Status of BH1790GLC_GetInterrupt_DRDY_Status.
 *
 *
 * @author      Manuel Caballero
 * @date        14/October/2019
 * @version     14/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetInterrupt_DRDY_Status ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myStatus )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   BH1790GLC_INTERRUPT_DRDY;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );


	/* Parse data   */
	myStatus->interrupt_drdy_status	 =	 (BH1790GLC_interrupt_drdy_drdy_status_t)( INTERRUPT_DRDY_DRDY_STATUS_MASK & cmd );



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
 * @brief       BH1790GLC_ConfTemperatureMax ( I2C_parameters_t , BH1790GLC_data_t )
 *
 * @details     It configures the temperature MAX register.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myTemperatureMax:	Temperature max raw value.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of BH1790GLC_ConfTemperatureMax.
 *
 *
 * @author      Manuel Caballero
 * @date        14/October/2019
 * @version     14/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_ConfTemperatureMax ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myTemperatureMax )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   BH1790GLC_TEMPERATURE_MAX;
	cmd[1]	 =	 myTemperatureMax.rawTemperature_max;
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
 * @brief       BH1790GLC_ConfHumidityMax ( I2C_parameters_t , BH1790GLC_data_t )
 *
 * @details     It configures the humidity MAX register.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myTemperatureMax:	Humidity max raw value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BH1790GLC_ConfHumidityMax.
 *
 *
 * @author      Manuel Caballero
 * @date        14/October/2019
 * @version     14/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_ConfHumidityMax ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myHumidityMax )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   BH1790GLC_HUMIDITY_MAX;
	cmd[1]	 =	 myHumidityMax.rawHumidity_max;
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
 * @brief       BH1790GLC_GetInterruptConfiguration ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the interrupt configuration bits.
 *
 * @param[in]    myI2Cparameters:   	I2C parameters.
 *
 * @param[out]   myIntConfiguration:   	DRDY_ENABLE, TH_ENABLE, TL_ENABLE, HH_ENABLE and HL_ENABLE status.
 *
 *
 * @return       Status of BH1790GLC_GetInterruptConfiguration.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetInterruptConfiguration	( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myIntConfiguration )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   BH1790GLC_INTERRUPT_ENABLE;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myIntConfiguration->drdy_enable	 =	 (BH1790GLC_interrupt_enable_drdy_enable_t)( cmd & INTERRUPT_DRDY_DRDY_ENABLE_MASK );
	myIntConfiguration->th_enable	 =	 (BH1790GLC_interrupt_enable_th_enable_t)( cmd & INTERRUPT_DRDY_TH_ENABLE_MASK );
	myIntConfiguration->tl_enable	 =	 (BH1790GLC_interrupt_enable_tl_enable_t)( cmd & INTERRUPT_DRDY_TL_ENABLE_MASK );
	myIntConfiguration->hh_enable	 =	 (BH1790GLC_interrupt_enable_hh_enable_t)( cmd & INTERRUPT_DRDY_HH_ENABLE_MASK );
	myIntConfiguration->hl_enable	 =	 (BH1790GLC_interrupt_enable_hl_enable_t)( cmd & INTERRUPT_DRDY_HL_ENABLE_MASK );


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
 * @brief       BH1790GLC_SetInterruptConfiguration ( I2C_parameters_t , BH1790GLC_data_t )
 *
 * @details     It configures the humidity MAX register.
 *
 * @param[in]    myI2Cparameters:   	I2C parameters.
 * @param[in]    myIntConfiguration:   	DRDY_ENABLE, TH_ENABLE, TL_ENABLE, HH_ENABLE and HL_ENABLE.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BH1790GLC_SetInterruptConfiguration.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_SetInterruptConfiguration	( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myIntConfiguration )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   BH1790GLC_INTERRUPT_ENABLE;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read ( myI2Cparameters, &cmd[1], 1U );

	/* Update the register	 */
	cmd[1]	&=	~( INTERRUPT_DRDY_DRDY_ENABLE_MASK | INTERRUPT_DRDY_TH_ENABLE_MASK | INTERRUPT_DRDY_TL_ENABLE_MASK | INTERRUPT_DRDY_HH_ENABLE_MASK | INTERRUPT_DRDY_HL_ENABLE_MASK );
	cmd[1]	|=	 ( myIntConfiguration.drdy_enable | myIntConfiguration.th_enable | myIntConfiguration.tl_enable | myIntConfiguration.hh_enable | myIntConfiguration.hl_enable );
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
 * @brief       BH1790GLC_SetTemperatureOffset ( I2C_parameters_t , BH1790GLC_data_t )
 *
 * @details     It sets the temperature offset.
 *
 * @param[in]    myI2Cparameters:   	I2C parameters.
 * @param[in]    myTemperatureOffset:   Temperature offset value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BH1790GLC_SetTemperatureOffset.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_SetTemperatureOffset ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myTemperatureOffset )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Write the register */
	cmd[0]	 =   BH1790GLC_TEMP_OFFSET_ADJUST;
	cmd[1]	 =	 myTemperatureOffset.temp_offset_adjust;
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
 * @brief       BH1790GLC_GetTemperatureOffset ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the temperature offset ( raw value ).
 *
 * @param[in]    myI2Cparameters:   	I2C parameters.
 *
 * @param[out]   myTemperatureOffset:   Temperature offset value ( raw value ).
 *
 *
 * @return       Status of BH1790GLC_GetTemperatureOffset.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetTemperatureOffset ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myTemperatureOffset )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   BH1790GLC_TEMP_OFFSET_ADJUST;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myTemperatureOffset->temp_offset_adjust	 =	 cmd;



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
 * @brief       BH1790GLC_SetHumidityOffset ( I2C_parameters_t , BH1790GLC_data_t )
 *
 * @details     It sets the humidity offset.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myHumidityOffset:  Humidity offset value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BH1790GLC_SetHumidityOffset.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_SetHumidityOffset ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myHumidityOffset )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Write the register */
	cmd[0]	 =   BH1790GLC_HUM_OFFSET_ADJUST;
	cmd[1]	 =	 myHumidityOffset.hum_offset_adjust;
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
 * @brief       BH1790GLC_GetHumidityOffset ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the humidity offset ( raw value ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myHumidityOffset:  Humidity offset value ( raw value ).
 *
 *
 * @return       Status of BH1790GLC_GetHumidityOffset.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetHumidityOffset ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myHumidityOffset )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   BH1790GLC_HUM_OFFSET_ADJUST;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myHumidityOffset->hum_offset_adjust	 =	 cmd;



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
 * @brief       BH1790GLC_SetTemperatureThresLow ( I2C_parameters_t , BH1790GLC_data_t )
 *
 * @details     It sets the temperature threshold low value ( raw value ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myTempThresLow:  Temperature threshold low value ( raw value ).
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BH1790GLC_SetTemperatureThresLow.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_SetTemperatureThresLow	( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myTempThresLow )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Write the register */
	cmd[0]	 =   BH1790GLC_TEMP_THR_L;
	cmd[1]	 =	 myTempThresLow.temp_thres_low;
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
 * @brief       BH1790GLC_GetTemperatureThresLow ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the temperature threshold low value ( raw value ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myTempThresLow:  Temperature threshold low value ( raw value ).
 *
 *
 * @return       Status of BH1790GLC_GetTemperatureThresLow.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetTemperatureThresLow	( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myTempThresLow )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   BH1790GLC_TEMP_THR_L;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myTempThresLow->temp_thres_low	 =	 cmd;



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
 * @brief       BH1790GLC_SetTemperatureThresHigh ( I2C_parameters_t , BH1790GLC_data_t )
 *
 * @details     It sets the temperature threshold high value ( raw value ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myTempThresHigh: Temperature threshold high value ( raw value ).
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BH1790GLC_SetTemperatureThresHigh.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_SetTemperatureThresHigh	( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myTempThresHigh )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Write the register */
	cmd[0]	 =   BH1790GLC_TEMP_THR_H;
	cmd[1]	 =	 myTempThresHigh.temp_thres_high;
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
 * @brief       BH1790GLC_GetTemperatureThresHigh ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the temperature threshold high value ( raw value ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myTempThresHigh: Temperature threshold high value ( raw value ).
 *
 *
 * @return       Status of BH1790GLC_GetTemperatureThresHigh.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetTemperatureThresHigh	( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myTempThresHigh )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   BH1790GLC_TEMP_THR_H;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myTempThresHigh->temp_thres_high	 =	 cmd;



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
 * @brief       BH1790GLC_SetHumidityThresLow ( I2C_parameters_t , BH1790GLC_data_t )
 *
 * @details     It sets the humidity threshold low value ( raw value ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myTempThresLow:  Humidity threshold low value ( raw value ).
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BH1790GLC_SetHumidityThresLow.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_SetHumidityThresLow	( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myHumThresLow )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Write the register */
	cmd[0]	 =   BH1790GLC_RH_THR_L;
	cmd[1]	 =	 myHumThresLow.hum_thres_low;
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
 * @brief       BH1790GLC_GetHumidityThresLow ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the humidity threshold low value ( raw value ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myHumThresLow:   Humidity threshold low value ( raw value ).
 *
 *
 * @return       Status of BH1790GLC_GetHumidityThresLow.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetHumidityThresLow	( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myHumThresLow )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   BH1790GLC_RH_THR_L;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myHumThresLow->hum_thres_low	 =	 cmd;



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
 * @brief       BH1790GLC_SetHumidityThresHigh ( I2C_parameters_t , BH1790GLC_data_t )
 *
 * @details     It sets the humidity threshold high value ( raw value ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myHumThresHigh:  Humidity threshold high value ( raw value ).
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BH1790GLC_SetHumidityThresHigh.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_SetHumidityThresHigh ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myHumThresHigh )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Write the register */
	cmd[0]	 =   BH1790GLC_RH_THR_H;
	cmd[1]	 =	 myHumThresHigh.hum_thres_high;
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
 * @brief       BH1790GLC_GetHumidityThresHigh ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the humidity threshold high value ( raw value ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myHumThresHigh:  Humidity threshold high value ( raw value ).
 *
 *
 * @return       Status of BH1790GLC_GetHumidityThresHigh.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetHumidityThresHigh	( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myHumThresHigh )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   BH1790GLC_RH_THR_H;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myHumThresHigh->hum_thres_high	 =	 cmd;



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
 * @brief       BH1790GLC_SetSoftReset ( I2C_parameters_t )
 *
 * @details     It makes a soft reset.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BH1790GLC_SetSoftReset.
 *
 *
 * @author      Manuel Caballero
 * @date        16/October/2019
 * @version     16/October/2019   The ORIGIN
 * @pre         This bit is self-clear.
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_SetSoftReset ( I2C_parameters_t myI2Cparameters )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   BH1790GLC_RESET_DRDY_INT_CONF;
	aux		 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

	/* Update the register	 */
	cmd[1]	|=	 RESET_DRDY_INT_CONF_SOFT_RES_RESET;
	aux		 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



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
 * @brief       BH1790GLC_GetSoftReset ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It checks the soft reset flag.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   mySoftResetFlag: Soft reset flag.
 *
 *
 * @return       Status of BH1790GLC_SetSoftReset.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetSoftReset ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* mySoftResetFlag )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   BH1790GLC_RESET_DRDY_INT_CONF;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	mySoftResetFlag->soft_res	 =	 (BH1790GLC_reset_drdy_int_conf_soft_res_t)( RESET_DRDY_INT_CONF_SOFT_RES_MASK & cmd );



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
 * @brief       BH1790GLC_SetAutoMeasurementMode ( I2C_parameters_t , BH1790GLC_data_t )
 *
 * @details     It sets auto measurement mode ( AMM ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myAMM: 		  Auto measurement mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BH1790GLC_SetAutoMeasurementMode.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_SetAutoMeasurementMode	( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myAMM )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   BH1790GLC_RESET_DRDY_INT_CONF;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

	/* Update the register	 */
	cmd[1]	&=	~( RESET_DRDY_INT_CONF_AMM_MASK );
	cmd[1]	|=	 ( myAMM.amm );
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
 * @brief       BH1790GLC_GetAutoMeasurementMode ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets auto measurement mode ( AMM ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myAMM: 		  Auto measurement mode.
 *
 *
 * @return       Status of BH1790GLC_GetAutoMeasurementMode.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetAutoMeasurementMode	( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myAMM )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   BH1790GLC_RESET_DRDY_INT_CONF;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myAMM->amm	 =	(BH1790GLC_reset_drdy_int_conf_amm_t)( RESET_DRDY_INT_CONF_AMM_MASK & cmd );



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
 * @brief       BH1790GLC_SetHeaterMode ( I2C_parameters_t , BH1790GLC_data_t )
 *
 * @details     It sets the heater mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myHeatEn: 		  Heater mode: On/Off.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BH1790GLC_SetHeaterMode.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_SetHeaterMode ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myHeatEn )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   BH1790GLC_RESET_DRDY_INT_CONF;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

	/* Update the register	 */
	cmd[1]	&=	~( RESET_DRDY_INT_CONF_HEAT_EN_MASK );
	cmd[1]	|=	 ( myHeatEn.heater_en );
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
 * @brief       BH1790GLC_GetHeaterMode ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the heater mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myHeatEn: 		  Heater mode: On/Off..
 *
 *
 * @return       Status of BH1790GLC_GetHeaterMode.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetHeaterMode ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myHeatEn )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   BH1790GLC_RESET_DRDY_INT_CONF;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myHeatEn->heater_en	 =	(BH1790GLC_reset_drdy_int_conf_heat_en_t)( RESET_DRDY_INT_CONF_HEAT_EN_MASK & cmd );



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
 * @brief       BH1790GLC_SetPinConfifuration ( I2C_parameters_t , BH1790GLC_data_t )
 *
 * @details     It sets the DRDY/INT_EN pin configuration.
 *
 * @param[in]    myI2Cparameters: 	 I2C parameters.
 * @param[in]    myPinConfiguration: DRDY/INT_EN pin configuration.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BH1790GLC_SetPinConfifuration.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_SetPinConfifuration ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myPinConfiguration )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   BH1790GLC_RESET_DRDY_INT_CONF;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

	/* Update the register	 */
	cmd[1]	&=	~( RESET_DRDY_INT_CONF_DRDY_INT_EN_MASK );
	cmd[1]	|=	 ( myPinConfiguration.drdy_intEn );
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
 * @brief       BH1790GLC_GetPinConfiguration ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the DRDY/INT_EN pin configuration.
 *
 * @param[in]    myI2Cparameters: 	 I2C parameters.
 *
 * @param[out]   myPinConfiguration: DRDY/INT_EN pin configuration..
 *
 *
 * @return       Status of BH1790GLC_GetPinConfiguration.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetPinConfiguration ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myPinConfiguration )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   BH1790GLC_RESET_DRDY_INT_CONF;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Update the register	 */
	myPinConfiguration->drdy_intEn	 =	(BH1790GLC_reset_drdy_int_conf_drdr_int_en_t)( RESET_DRDY_INT_CONF_DRDY_INT_EN_MASK & cmd );



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
 * @brief       BH1790GLC_SetInterruptPolarity ( I2C_parameters_t , BH1790GLC_data_t )
 *
 * @details     It sets the interrupt polarity
 *
 * @param[in]    myI2Cparameters: 	I2C parameters.
 * @param[in]    myIntPol: 			Interrupt polarity: Active Low/High.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BH1790GLC_SetInterruptPolarity.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_SetInterruptPolarity ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myIntPol )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   BH1790GLC_RESET_DRDY_INT_CONF;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

	/* Update the register	 */
	cmd[1]	&=	~( RESET_DRDY_INT_CONF_INT_POL_MASK );
	cmd[1]	|=	 ( myIntPol.int_pol );
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
 * @brief       BH1790GLC_GetInterruptPolarity ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the interrupt polarity
 *
 * @param[in]    myI2Cparameters: 	I2C parameters.
 *
 * @param[out]   myIntPol: 			Interrupt polarity: Active Low/High.
 *
 *
 * @return       Status of BH1790GLC_GetInterruptPolarity.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetInterruptPolarity ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myIntPol )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   BH1790GLC_RESET_DRDY_INT_CONF;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myIntPol->int_pol	 =	(BH1790GLC_reset_drdy_int_conf_int_pol_t)( RESET_DRDY_INT_CONF_INT_POL_MASK & cmd );



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
 * @brief       BH1790GLC_SetInterruptMode ( I2C_parameters_t , BH1790GLC_data_t )
 *
 * @details     It sets the interrupt mode
 *
 * @param[in]    myI2Cparameters: 	I2C parameters.
 * @param[in]    myIntMode: 		Interrupt mode: Level sensitive/Comparator mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BH1790GLC_SetInterruptMode.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_SetInterruptMode ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myIntMode )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   BH1790GLC_RESET_DRDY_INT_CONF;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

	/* Update the register	 */
	cmd[1]	&=	~( RESET_DRDY_INT_CONF_INT_MODE_MASK );
	cmd[1]	|=	 ( myIntMode.int_mode );
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
 * @brief       BH1790GLC_GetInterruptMode ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the interrupt mode
 *
 * @param[in]    myI2Cparameters: 	I2C parameters.
 *
 * @param[out]   myIntMode: 		Interrupt mode: Level sensitive/Comparator mode.
 *
 *
 * @return       Status of BH1790GLC_GetInterruptMode.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetInterruptMode ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myIntMode )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   BH1790GLC_RESET_DRDY_INT_CONF;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myIntMode->int_mode	 =	(BH1790GLC_reset_drdy_int_conf_int_mode_t)( RESET_DRDY_INT_CONF_INT_MODE_MASK & cmd );



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
 * @brief       BH1790GLC_SetMeasurementConf ( I2C_parameters_t , BH1790GLC_data_t )
 *
 * @details     It sets the measurement configuration.
 *
 * @param[in]    myI2Cparameters: 	I2C parameters.
 * @param[in]    myMeasConf: 		Temperature resolution, Humidity resolution and Measurement configuration.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BH1790GLC_SetMeasurementConf.
 *
 *
 * @author      Manuel Caballero
 * @date        31/October/2019
 * @version     31/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_SetMeasurementConf	( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myMeasConf )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   BH1790GLC_MEASUREMENT_CONFIGURATION;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

	/* Update the register	 */
	cmd[1]	&=	~( MEASUREMENT_CONF_TRES_MASK | MEASUREMENT_CONF_HRES_MASK | MEASUREMENT_CONF_MEAS_CONF_MASK );
	cmd[1]	|=	 ( myMeasConf.tres | myMeasConf.hres | myMeasConf.meas_conf );
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
 * @brief       BH1790GLC_GetMeasurementConf ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the measurement configuration.
 *
 * @param[in]    myI2Cparameters: 	I2C parameters.
 *
 * @param[out]   myMeasConf: 		Temperature resolution, Humidity resolution and Measurement configuration.
 *
 *
 * @return       Status of BH1790GLC_GetMeasurementConf.
 *
 *
 * @author      Manuel Caballero
 * @date        31/October/2019
 * @version     31/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetMeasurementConf	( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myMeasConf )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   BH1790GLC_MEASUREMENT_CONFIGURATION;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myMeasConf->tres	 	 =	(BH1790GLC_measurement_configuration_tres_t)( MEASUREMENT_CONF_TRES_MASK & cmd );
	myMeasConf->hres	 	 =	(BH1790GLC_measurement_configuration_hres_t)( MEASUREMENT_CONF_HRES_MASK & cmd );
	myMeasConf->meas_conf	 =	(BH1790GLC_measurement_configuration_meas_conf_t)( MEASUREMENT_CONF_MEAS_CONF_MASK & cmd );



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
 * @brief       BH1790GLC_StartMeasurementTrigger ( I2C_parameters_t )
 *
 * @details     It triggers a new measurement.
 *
 * @param[in]    myI2Cparameters: 	I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BH1790GLC_StartMeasurementTrigger.
 *
 *
 * @author      Manuel Caballero
 * @date        31/October/2019
 * @version     31/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_StartMeasurementTrigger ( I2C_parameters_t myI2Cparameters )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   BH1790GLC_MEASUREMENT_CONFIGURATION;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

	/* Update the register	 */
	cmd[1]	|=	 MEASUREMENT_CONF_MEAS_TRIG_START_MEASUREMENT;
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
 * @brief       BH1790GLC_GetMeasurementTrigger ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the measurement trigger flag.
 *
 * @param[in]    myI2Cparameters: 	I2C parameters.
 *
 * @param[out]   myMeasTrig:		Measurement trigger flag.
 *
 *
 * @return       Status of BH1790GLC_GetMeasurementTrigger.
 *
 *
 * @author      Manuel Caballero
 * @date        31/October/2019
 * @version     31/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetMeasurementTrigger ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myMeasTrig )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   BH1790GLC_MEASUREMENT_CONFIGURATION;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myMeasTrig->meas_trig	 =	(BH1790GLC_measurement_configuration_meas_trig_t)( MEASUREMENT_CONF_MEAS_TRIG_MASK & cmd );



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
 * @param[in]    myI2Cparameters: 	I2C parameters.
 *
 * @param[out]   myManufacturerID:	Manufacturer ID.
 *
 *
 * @return       Status of BH1790GLC_GetManufacturerID.
 *
 *
 * @author      Manuel Caballero
 * @date        31/October/2019
 * @version     31/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetManufacturerID ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myManufacturerID )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   BH1790GLC_MANUFACTURER_ID_LOW;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Parse the data	 */
	myManufacturerID->manufacturer_id	 =	 cmd[1];
	myManufacturerID->manufacturer_id  <<=	 8U;
	myManufacturerID->manufacturer_id	|=	 cmd[0];



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
 * @brief       BH1790GLC_GetDeviceID ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the device ID.
 *
 * @param[in]    myI2Cparameters: 	I2C parameters.
 *
 * @param[out]   myDeviceID:		Device ID.
 *
 *
 * @return       Status of BH1790GLC_GetDeviceID.
 *
 *
 * @author      Manuel Caballero
 * @date        31/October/2019
 * @version     31/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetDeviceID ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myDeviceID )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   BH1790GLC_DEVICE_ID_LOW;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Parse the data	 */
	myDeviceID->device_id	 =	 cmd[1];
	myDeviceID->device_id  <<=	 8U;
	myDeviceID->device_id	|=	 cmd[0];



	if ( aux == I2C_SUCCESS )
	{
		return   BH1790GLC_SUCCESS;
	}
	else
	{
		return   BH1790GLC_FAILURE;
	}
}
