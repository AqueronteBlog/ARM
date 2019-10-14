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
	myStatus->interrupt_drdy_status	 =	 cmd;



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
 *
 * @param[out]   myTemperatureMax:	Temperature max raw value.
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
 *
 * @param[out]   myTemperatureMax:	Humidity max raw value.
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
