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
