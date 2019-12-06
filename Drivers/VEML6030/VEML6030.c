/**
 * @brief       VEML6030.c
 * @details     High Accuracy Ambient Light Sensor With I2C Interface.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        29/November/2019
 * @version     29/November/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "VEML6030.h"


/**
 * @brief       VEML6030_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of VEML6030_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        04/November/2019
 * @version     04/November/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6030_status_t VEML6030_Init ( I2C_parameters_t myI2Cparameters )
{
	i2c_status_t aux;

	aux  =   i2c_init ( myI2Cparameters );


	if ( aux == I2C_SUCCESS )
	{
		return   VEML6030_SUCCESS;
	}
	else
	{
		return   VEML6030_FAILURE;
	}
}



/**
 * @brief       VEML6030_SetConfiguration ( I2C_parameters_t , VEML6030_data_t )
 *
 * @details     It sets the configuration register.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myALS_Conf:   		ALS gain, integration time, interrupt, and shut down.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of VEML6030_SetConfiguration.
 *
 *
 * @author      Manuel Caballero
 * @date        06/December/2019
 * @version     06/December/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6030_status_t VEML6030_SetConfiguration ( I2C_parameters_t myI2Cparameters, VEML6030_data_t myALS_Conf )
{
	uint8_t		 cmd[3]  = { 0 };
	uint16_t	 aux_reg = 0U;
	i2c_status_t aux;

	/* Update the register	 */
	aux_reg	 =	 ( myALS_Conf.als_gain | myALS_Conf.als_it | myALS_Conf.als_pers | myALS_Conf.als_int_en | myALS_Conf.als_sd );

	cmd[0]	 =   VEML6030_ALS_CONF;
	cmd[1]	 =	 (uint8_t)( aux_reg >> 2U );
	cmd[2]	 =	 (uint8_t)( aux_reg & 0xFF );
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



	if ( aux == I2C_SUCCESS )
	{
		return   VEML6030_SUCCESS;
	}
	else
	{
		return   VEML6030_FAILURE;
	}
}



/**
 * @brief       VEML6030_GetConfiguration ( I2C_parameters_t , VEML6030_data_t* )
 *
 * @details     It gets the configuration register.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myALS_Conf:   		ALS gain, integration time, interrupt, and shut down.
 *
 *
 * @return       Status of VEML6030_GetConfiguration.
 *
 *
 * @author      Manuel Caballero
 * @date        06/December/2019
 * @version     06/December/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6030_status_t VEML6030_GetConfiguration ( I2C_parameters_t myI2Cparameters, VEML6030_data_t* myALS_Conf )
{
	uint8_t		 cmd[2]  = { 0 };
	uint16_t	 aux_reg = 0U;
	i2c_status_t aux;

	/* Read the register	 */
	cmd[0]	 =   VEML6030_ALS_CONF;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Parse the data	 */
	aux_reg	 =	 ( myALS_Conf->als_gain | myALS_Conf->als_it | myALS_Conf->als_pers | myALS_Conf->als_int_en | myALS_Conf->als_sd );

	myALS_Conf->als_gain	 =	 (VEML6030_als_conf_als_gain_t)( aux_reg & ALS_CONF_ALS_GAIN_MASK );
	myALS_Conf->als_it		 =	 (VEML6030_als_conf_als_it_t)( aux_reg & ALS_CONF_ALS_IT_MASK );
	myALS_Conf->als_pers	 =	 (VEML6030_als_conf_als_pers_t)( aux_reg & ALS_CONF_ALS_PERS_MASK );
	myALS_Conf->als_int_en	 =	 (VEML6030_als_conf_als_int_en_t)( aux_reg & ALS_CONF_ALS_INT_EN_MASK );
	myALS_Conf->als_sd		 =	 (VEML6030_als_conf_als_sd_t)( aux_reg & ALS_CONF_ALS_SD_MASK );



	if ( aux == I2C_SUCCESS )
	{
		return   VEML6030_SUCCESS;
	}
	else
	{
		return   VEML6030_FAILURE;
	}
}



