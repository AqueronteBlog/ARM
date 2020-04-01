/**
 * @brief       AS7263.c
 * @details     6-Channel NIR Spectral_ID Device with Electronic Shutter and Smart Interface.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        01/April/2020
 * @version     01/April/2020    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "AS7263.h"


/**
 * @brief       AS7263_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS7263_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        01/April/2020
 * @version     01/April/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_Init ( I2C_parameters_t myI2Cparameters )
{
	i2c_status_t aux;

	aux  =   i2c_init ( myI2Cparameters );


	if ( aux == I2C_SUCCESS )
	{
		return   AS7263_SUCCESS;
	}
	else
	{
		return   AS7263_FAILURE;
	}
}



/**
 * @brief       AS7263_GetConfigurationRegister ( I2C_parameters_t , AS7263_configuration_register_t* )
 *
 * @details     It reads the configuration register.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myConfReg:   		Configuration values.
 *
 *
 * @return       Status of AS7263_GetConfigurationRegister.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_SetSensitivity ( I2C_parameters_t myI2Cparameters, AS7263_data_t mySENS )
{
	uint8_t		 cmd[2]  			= 	{ 0 };
	uint16_t	 auxConfiguration	=	 0U;
	i2c_status_t aux;

	/* Read the register	 */
	//cmd[0]	 =   AS7263_ALS_CONF;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1UL, I2C_NO_STOP_BIT );
	aux	 	|=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Update the data	 */
	auxConfiguration	 =	 cmd[0];
	auxConfiguration   <<=	 8U;
	auxConfiguration	|=	 cmd[1];




	if ( aux == I2C_SUCCESS )
	{
		return   AS7263_SUCCESS;
	}
	else
	{
		return   AS7263_FAILURE;
	}
}
