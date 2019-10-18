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
 * @date        10/October/2019
 * @version     10/October/2019   The ORIGIN
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
 * @brief       HDC2080_GetRawTemperature ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the raw temperature.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawTemperature:	Raw temperature.
 *
 *
 * @return       Status of HDC2080_GetRawTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        14/October/2019
 * @version     14/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetRawTemperature  ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myRawTemperature )
{
	uint8_t		 cmd[2] = { 0 };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   HDC2080_TEMPERATURE_LOW;
	aux   	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux   	 =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


	/* Parse data   */
	myRawTemperature->rawTemperature	 =	 cmd[1];
	myRawTemperature->rawTemperature   <<=	 8U;
	myRawTemperature->rawTemperature	|=	 cmd[0];



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
 * @brief       HDC2080_GetTemperature ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the current temperature.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTemperature:		Current temperature.
 *
 *
 * @return       Status of HDC2080_GetTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        14/October/2019
 * @version     14/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetTemperature  ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myTemperature )
{
	HDC2080_status_t aux;

	/* Read the register */
	aux   	 =   HDC2080_GetRawTemperature  ( myI2Cparameters, &(*myTemperature) );

	/* Parse data   */
	myTemperature->temperature	=	( ( myTemperature->rawTemperature ) / 65536 ) * 165 - 40;


	return   aux;
}



/**
 * @brief       HDC2080_GetRawHumidity ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the raw humidity.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawTemperature:	Raw humidity.
 *
 *
 * @return       Status of HDC2080_GetRawHumidity.
 *
 *
 * @author      Manuel Caballero
 * @date        14/October/2019
 * @version     14/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetRawHumidity  ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myRawHumidity )
{
	uint8_t		 cmd[2] = { 0 };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   HDC2080_HUMIDITY_LOW;
	aux   	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux   	 =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


	/* Parse data   */
	myRawHumidity->rawHumidity	 =	 cmd[1];
	myRawHumidity->rawHumidity   <<=	 8U;
	myRawHumidity->rawHumidity	|=	 cmd[0];



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
 * @brief       HDC2080_GetHumidity ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the current humidity.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTemperature:		Current humidity.
 *
 *
 * @return       Status of HDC2080_GetTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        14/October/2019
 * @version     14/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetHumidity  ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myHumidity )
{
	HDC2080_status_t aux;

	/* Read the register */
	aux   	 =   HDC2080_GetRawHumidity  ( myI2Cparameters, &(*myHumidity) );

	/* Parse data   */
	myHumidity->humidity	=	( ( myHumidity->rawHumidity ) / 65536 ) * 100;


	return   aux;
}



/**
 * @brief       HDC2080_GetInterrupt_DRDY_Status ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the interrupt DRDY status.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myStatus:			Interrupt DRDY status.
 *
 *
 * @return       Status of HDC2080_GetInterrupt_DRDY_Status.
 *
 *
 * @author      Manuel Caballero
 * @date        14/October/2019
 * @version     14/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetInterrupt_DRDY_Status ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myStatus )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   HDC2080_INTERRUPT_DRDY;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );


	/* Parse data   */
	myStatus->interrupt_drdy_status	 =	 (HDC2080_interrupt_drdy_drdy_status_t)( INTERRUPT_DRDY_DRDY_STATUS_MASK & cmd );



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
 * @brief       HDC2080_ConfTemperatureMax ( I2C_parameters_t , HDC2080_data_t )
 *
 * @details     It configures the temperature MAX register.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myTemperatureMax:	Temperature max raw value.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of HDC2080_ConfTemperatureMax.
 *
 *
 * @author      Manuel Caballero
 * @date        14/October/2019
 * @version     14/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_ConfTemperatureMax ( I2C_parameters_t myI2Cparameters, HDC2080_data_t myTemperatureMax )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   HDC2080_TEMPERATURE_MAX;
	cmd[1]	 =	 myTemperatureMax.rawTemperature_max;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


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
 * @brief       HDC2080_ConfHumidityMax ( I2C_parameters_t , HDC2080_data_t )
 *
 * @details     It configures the humidity MAX register.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myTemperatureMax:	Humidity max raw value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of HDC2080_ConfHumidityMax.
 *
 *
 * @author      Manuel Caballero
 * @date        14/October/2019
 * @version     14/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_ConfHumidityMax ( I2C_parameters_t myI2Cparameters, HDC2080_data_t myHumidityMax )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   HDC2080_HUMIDITY_MAX;
	cmd[1]	 =	 myHumidityMax.rawHumidity_max;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


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
 * @brief       HDC2080_GetInterruptConfiguration ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the interrupt configuration bits.
 *
 * @param[in]    myI2Cparameters:   	I2C parameters.
 *
 * @param[out]   myIntConfiguration:   	DRDY_ENABLE, TH_ENABLE, TL_ENABLE, HH_ENABLE and HL_ENABLE status.
 *
 *
 * @return       Status of HDC2080_GetInterruptConfiguration.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetInterruptConfiguration	( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myIntConfiguration )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   HDC2080_INTERRUPT_ENABLE;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myIntConfiguration->drdy_enable	 =	 (HDC2080_interrupt_enable_drdy_enable_t)( cmd & INTERRUPT_DRDY_DRDY_ENABLE_MASK );
	myIntConfiguration->th_enable	 =	 (HDC2080_interrupt_enable_th_enable_t)( cmd & INTERRUPT_DRDY_TH_ENABLE_MASK );
	myIntConfiguration->tl_enable	 =	 (HDC2080_interrupt_enable_tl_enable_t)( cmd & INTERRUPT_DRDY_TL_ENABLE_MASK );
	myIntConfiguration->hh_enable	 =	 (HDC2080_interrupt_enable_hh_enable_t)( cmd & INTERRUPT_DRDY_HH_ENABLE_MASK );
	myIntConfiguration->hl_enable	 =	 (HDC2080_interrupt_enable_hl_enable_t)( cmd & INTERRUPT_DRDY_HL_ENABLE_MASK );


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
 * @brief       HDC2080_SetInterruptConfiguration ( I2C_parameters_t , HDC2080_data_t )
 *
 * @details     It configures the humidity MAX register.
 *
 * @param[in]    myI2Cparameters:   	I2C parameters.
 * @param[in]    myIntConfiguration:   	DRDY_ENABLE, TH_ENABLE, TL_ENABLE, HH_ENABLE and HL_ENABLE.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of HDC2080_SetInterruptConfiguration.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_SetInterruptConfiguration	( I2C_parameters_t myI2Cparameters, HDC2080_data_t myIntConfiguration )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   HDC2080_INTERRUPT_ENABLE;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read ( myI2Cparameters, &cmd[1], 1U );

	/* Update the register	 */
	cmd[1]	&=	~( INTERRUPT_DRDY_DRDY_ENABLE_MASK | INTERRUPT_DRDY_TH_ENABLE_MASK | INTERRUPT_DRDY_TL_ENABLE_MASK | INTERRUPT_DRDY_HH_ENABLE_MASK | INTERRUPT_DRDY_HL_ENABLE_MASK );
	cmd[1]	|=	 ( myIntConfiguration.drdy_enable | myIntConfiguration.th_enable | myIntConfiguration.tl_enable | myIntConfiguration.hh_enable | myIntConfiguration.hl_enable );
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



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
 * @brief       HDC2080_SetTemperatureOffset ( I2C_parameters_t , HDC2080_data_t )
 *
 * @details     It sets the temperature offset.
 *
 * @param[in]    myI2Cparameters:   	I2C parameters.
 * @param[in]    myTemperatureOffset:   Temperature offset value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of HDC2080_SetTemperatureOffset.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_SetTemperatureOffset ( I2C_parameters_t myI2Cparameters, HDC2080_data_t myTemperatureOffset )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Write the register */
	cmd[0]	 =   HDC2080_TEMP_OFFSET_ADJUST;
	cmd[1]	 =	 myTemperatureOffset.temp_offset_adjust;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



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
 * @brief       HDC2080_GetTemperatureOffset ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the temperature offset ( raw value ).
 *
 * @param[in]    myI2Cparameters:   	I2C parameters.
 *
 * @param[out]   myTemperatureOffset:   Temperature offset value ( raw value ).
 *
 *
 * @return       Status of HDC2080_GetTemperatureOffset.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetTemperatureOffset ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myTemperatureOffset )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   HDC2080_TEMP_OFFSET_ADJUST;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myTemperatureOffset->temp_offset_adjust	 =	 cmd;



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
 * @brief       HDC2080_SetHumidityOffset ( I2C_parameters_t , HDC2080_data_t )
 *
 * @details     It sets the humidity offset.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myHumidityOffset:  Humidity offset value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of HDC2080_SetHumidityOffset.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_SetHumidityOffset ( I2C_parameters_t myI2Cparameters, HDC2080_data_t myHumidityOffset )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Write the register */
	cmd[0]	 =   HDC2080_HUM_OFFSET_ADJUST;
	cmd[1]	 =	 myHumidityOffset.hum_offset_adjust;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



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
 * @brief       HDC2080_GetHumidityOffset ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the humidity offset ( raw value ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myHumidityOffset:  Humidity offset value ( raw value ).
 *
 *
 * @return       Status of HDC2080_GetHumidityOffset.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetHumidityOffset ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myHumidityOffset )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   HDC2080_HUM_OFFSET_ADJUST;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myHumidityOffset->hum_offset_adjust	 =	 cmd;



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
 * @brief       HDC2080_SetTemperatureThresLow ( I2C_parameters_t , HDC2080_data_t )
 *
 * @details     It sets the temperature threshold low value ( raw value ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myTempThresLow:  Temperature threshold low value ( raw value ).
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of HDC2080_SetTemperatureThresLow.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_SetTemperatureThresLow	( I2C_parameters_t myI2Cparameters, HDC2080_data_t myTempThresLow )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Write the register */
	cmd[0]	 =   HDC2080_TEMP_THR_L;
	cmd[1]	 =	 myTempThresLow.temp_thres_low;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



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
 * @brief       HDC2080_GetTemperatureThresLow ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the temperature threshold low value ( raw value ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myTempThresLow:  Temperature threshold low value ( raw value ).
 *
 *
 * @return       Status of HDC2080_GetTemperatureThresLow.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetTemperatureThresLow	( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myTempThresLow )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   HDC2080_TEMP_THR_L;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myTempThresLow->temp_thres_low	 =	 cmd;



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
 * @brief       HDC2080_SetTemperatureThresHigh ( I2C_parameters_t , HDC2080_data_t )
 *
 * @details     It sets the temperature threshold high value ( raw value ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myTempThresHigh: Temperature threshold high value ( raw value ).
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of HDC2080_SetTemperatureThresHigh.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_SetTemperatureThresHigh	( I2C_parameters_t myI2Cparameters, HDC2080_data_t myTempThresHigh )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Write the register */
	cmd[0]	 =   HDC2080_TEMP_THR_H;
	cmd[1]	 =	 myTempThresHigh.temp_thres_high;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



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
 * @brief       HDC2080_GetTemperatureThresHigh ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the temperature threshold high value ( raw value ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myTempThresHigh: Temperature threshold high value ( raw value ).
 *
 *
 * @return       Status of HDC2080_GetTemperatureThresHigh.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetTemperatureThresHigh	( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myTempThresHigh )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   HDC2080_TEMP_THR_H;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myTempThresHigh->temp_thres_high	 =	 cmd;



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
 * @brief       HDC2080_SetHumidityThresLow ( I2C_parameters_t , HDC2080_data_t )
 *
 * @details     It sets the humidity threshold low value ( raw value ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myTempThresLow:  Humidity threshold low value ( raw value ).
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of HDC2080_SetHumidityThresLow.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_SetHumidityThresLow	( I2C_parameters_t myI2Cparameters, HDC2080_data_t myHumThresLow )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Write the register */
	cmd[0]	 =   HDC2080_RH_THR_L;
	cmd[1]	 =	 myHumThresLow.hum_thres_low;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



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
 * @brief       HDC2080_GetHumidityThresLow ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the humidity threshold low value ( raw value ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myHumThresLow:   Humidity threshold low value ( raw value ).
 *
 *
 * @return       Status of HDC2080_GetHumidityThresLow.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetHumidityThresLow	( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myHumThresLow )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   HDC2080_RH_THR_L;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myHumThresLow->hum_thres_low	 =	 cmd;



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
 * @brief       HDC2080_SetHumidityThresHigh ( I2C_parameters_t , HDC2080_data_t )
 *
 * @details     It sets the humidity threshold high value ( raw value ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myHumThresHigh:  Humidity threshold high value ( raw value ).
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of HDC2080_SetHumidityThresHigh.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_SetHumidityThresHigh ( I2C_parameters_t myI2Cparameters, HDC2080_data_t myHumThresHigh )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Write the register */
	cmd[0]	 =   HDC2080_RH_THR_H;
	cmd[1]	 =	 myHumThresHigh.hum_thres_high;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



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
 * @brief       HDC2080_GetHumidityThresHigh ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the humidity threshold high value ( raw value ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myHumThresHigh:  Humidity threshold high value ( raw value ).
 *
 *
 * @return       Status of HDC2080_GetHumidityThresHigh.
 *
 *
 * @author      Manuel Caballero
 * @date        15/October/2019
 * @version     15/October/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetHumidityThresHigh	( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myHumThresHigh )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   HDC2080_RH_THR_H;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myHumThresHigh->hum_thres_high	 =	 cmd;



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
 * @brief       HDC2080_SetSoftReset ( I2C_parameters_t )
 *
 * @details     It makes a soft reset.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of HDC2080_SetSoftReset.
 *
 *
 * @author      Manuel Caballero
 * @date        16/October/2019
 * @version     16/October/2019   The ORIGIN
 * @pre         This bit is self-clear.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_SetSoftReset ( I2C_parameters_t myI2Cparameters )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   HDC2080_RESET_DRDY_INT_CONF;
	aux		 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

	/* Update the register	 */
	cmd[1]	|=	 RESET_DRDY_INT_CONF_SOFT_RES_RESET;
	aux		 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



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
 * @brief       HDC2080_GetSoftReset ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It checks the soft reset flag.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   mySoftResetFlag: Soft reset flag.
 *
 *
 * @return       Status of HDC2080_SetSoftReset.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetSoftReset ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* mySoftResetFlag )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   HDC2080_RESET_DRDY_INT_CONF;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	mySoftResetFlag->soft_res	 =	 (HDC2080_reset_drdy_int_conf_soft_res_t)( RESET_DRDY_INT_CONF_SOFT_RES_MASK & cmd );



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
 * @brief       HDC2080_SetAutoMeasurementMode ( I2C_parameters_t , HDC2080_data_t )
 *
 * @details     It sets auto measurement mode ( AMM ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myAMM: 		  Auto measurement mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of HDC2080_SetAutoMeasurementMode.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_SetAutoMeasurementMode	( I2C_parameters_t myI2Cparameters, HDC2080_data_t myAMM )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   HDC2080_RESET_DRDY_INT_CONF;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

	/* Update the register	 */
	cmd[1]	&=	~( RESET_DRDY_INT_CONF_AMM_MASK );
	cmd[1]	|=	 ( myAMM.amm );
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



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
 * @brief       HDC2080_GetAutoMeasurementMode ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets auto measurement mode ( AMM ).
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myAMM: 		  Auto measurement mode.
 *
 *
 * @return       Status of HDC2080_GetAutoMeasurementMode.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetAutoMeasurementMode	( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myAMM )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   HDC2080_RESET_DRDY_INT_CONF;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myAMM->amm	 =	(HDC2080_reset_drdy_int_conf_amm_t)( RESET_DRDY_INT_CONF_AMM_MASK & cmd );



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
 * @brief       HDC2080_SetHeaterMode ( I2C_parameters_t , HDC2080_data_t )
 *
 * @details     It sets the heater mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myHeatEn: 		  Heater mode: On/Off.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of HDC2080_SetHeaterMode.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_SetHeaterMode ( I2C_parameters_t myI2Cparameters, HDC2080_data_t myHeatEn )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   HDC2080_RESET_DRDY_INT_CONF;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

	/* Update the register	 */
	cmd[1]	&=	~( RESET_DRDY_INT_CONF_HEAT_EN_MASK );
	cmd[1]	|=	 ( myHeatEn.heater_en );
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



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
 * @brief       HDC2080_GetHeaterMode ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the heater mode.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 *
 * @param[out]   myHeatEn: 		  Heater mode: On/Off..
 *
 *
 * @return       Status of HDC2080_GetHeaterMode.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetHeaterMode ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myHeatEn )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   HDC2080_RESET_DRDY_INT_CONF;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myHeatEn->heater_en	 =	(HDC2080_reset_drdy_int_conf_heat_en_t)( RESET_DRDY_INT_CONF_HEAT_EN_MASK & cmd );



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
 * @brief       HDC2080_SetPinConfifuration ( I2C_parameters_t , HDC2080_data_t )
 *
 * @details     It sets the DRDY/INT_EN pin configuration.
 *
 * @param[in]    myI2Cparameters: 	 I2C parameters.
 * @param[in]    myPinConfiguration: DRDY/INT_EN pin configuration.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of HDC2080_SetPinConfifuration.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_SetPinConfifuration ( I2C_parameters_t myI2Cparameters, HDC2080_data_t myPinConfiguration )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   HDC2080_RESET_DRDY_INT_CONF;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

	/* Update the register	 */
	cmd[1]	&=	~( RESET_DRDY_INT_CONF_DRDY_INT_EN_MASK );
	cmd[1]	|=	 ( myPinConfiguration.drdy_intEn );
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



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
 * @brief       HDC2080_GetPinConfifuration ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the DRDY/INT_EN pin configuration.
 *
 * @param[in]    myI2Cparameters: 	 I2C parameters.
 *
 * @param[out]   myPinConfiguration: DRDY/INT_EN pin configuration..
 *
 *
 * @return       Status of HDC2080_GetPinConfifuration.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetPinConfifuration ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myPinConfiguration )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   HDC2080_RESET_DRDY_INT_CONF;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Update the register	 */
	myPinConfiguration->drdy_intEn	 =	(HDC2080_reset_drdy_int_conf_drdr_int_en_t)( RESET_DRDY_INT_CONF_DRDY_INT_EN_MASK & cmd );



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
 * @brief       HDC2080_SetInterruptPolarity ( I2C_parameters_t , HDC2080_data_t )
 *
 * @details     It sets the interrupt polarity
 *
 * @param[in]    myI2Cparameters: 	I2C parameters.
 * @param[in]    myIntPol: 			Interrupt polarity: Active Low/High.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of HDC2080_SetInterruptPolarity.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_SetInterruptPolarity ( I2C_parameters_t myI2Cparameters, HDC2080_data_t myIntPol )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   HDC2080_RESET_DRDY_INT_CONF;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

	/* Update the register	 */
	cmd[1]	&=	~( RESET_DRDY_INT_CONF_INT_POL_MASK );
	cmd[1]	|=	 ( myIntPol.int_pol );
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



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
 * @brief       HDC2080_GetInterruptPolarity ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the interrupt polarity
 *
 * @param[in]    myI2Cparameters: 	I2C parameters.
 *
 * @param[out]   myIntPol: 			Interrupt polarity: Active Low/High.
 *
 *
 * @return       Status of HDC2080_GetInterruptPolarity.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetInterruptPolarity ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myIntPol )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   HDC2080_RESET_DRDY_INT_CONF;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Update the register	 */
	myIntPol->int_pol	 =	(HDC2080_reset_drdy_int_conf_int_pol_t)( RESET_DRDY_INT_CONF_INT_POL_MASK & cmd );



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
 * @brief       HDC2080_SetInterruptMode ( I2C_parameters_t , HDC2080_data_t )
 *
 * @details     It sets the interrupt mode
 *
 * @param[in]    myI2Cparameters: 	I2C parameters.
 * @param[in]    myIntMode: 		Interrupt mode: Level sensitive/Comparator mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of HDC2080_SetInterruptMode.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_SetInterruptMode ( I2C_parameters_t myI2Cparameters, HDC2080_data_t myIntMode )
{
	uint8_t		 cmd[2]  = { 0U };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   HDC2080_RESET_DRDY_INT_CONF;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[1], 1U );

	/* Update the register	 */
	cmd[1]	&=	~( RESET_DRDY_INT_CONF_INT_MODE_MASK );
	cmd[1]	|=	 ( myIntMode.int_mode );
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



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
 * @brief       HDC2080_GetInterruptMode ( I2C_parameters_t , HDC2080_data_t* )
 *
 * @details     It gets the interrupt mode
 *
 * @param[in]    myI2Cparameters: 	I2C parameters.
 *
 * @param[out]   myIntMode: 		Interrupt mode: Level sensitive/Comparator mode.
 *
 *
 * @return       Status of HDC2080_GetInterruptMode.
 *
 *
 * @author      Manuel Caballero
 * @date        17/October/2019
 * @version     17/October/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
HDC2080_status_t HDC2080_GetInterruptMode ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myIntMode )
{
	uint8_t		 cmd  = 0U;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   HDC2080_RESET_DRDY_INT_CONF;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Update the register	 */
	myIntMode->int_mode	 =	(HDC2080_reset_drdy_int_conf_int_mode_t)( RESET_DRDY_INT_CONF_INT_MODE_MASK & cmd );




	if ( aux == I2C_SUCCESS )
	{
		return   HDC2080_SUCCESS;
	}
	else
	{
		return   HDC2080_FAILURE;
	}
}
