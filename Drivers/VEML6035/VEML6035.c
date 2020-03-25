/**
 * @brief       VEML6035.c
 * @details     Low Power, High Sensitivity, I2C Ambient Light Sensor.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/March/2020
 * @version     17/March/2020    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "VEML6035.h"


/**
 * @brief       VEML6035_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of VEML6035_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        17/March/2020
 * @version     17/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_Init ( I2C_parameters_t myI2Cparameters )
{
	i2c_status_t aux;

	aux  =   i2c_init ( myI2Cparameters );


	if ( aux == I2C_SUCCESS )
	{
		return   VEML6035_SUCCESS;
	}
	else
	{
		return   VEML6035_FAILURE;
	}
}



/**
 * @brief       VEML6035_GetConfigurationRegister ( I2C_parameters_t , VEML6035_configuration_register_t* )
 *
 * @details     It reads the configuration register.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myConfReg:   		Configuration values.
 *
 *
 * @return       Status of VEML6035_GetConfigurationRegister.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_GetConfigurationRegister	( I2C_parameters_t myI2Cparameters, VEML6035_configuration_register_t* myConfReg )
{
	uint8_t		 cmd[2]  			= 	{ 0 };
	uint16_t	 auxConfiguration	=	 0U;
	i2c_status_t aux;

	/* Read the register	 */
	cmd[0]	 =   VEML6035_ALS_CONF;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1UL, I2C_NO_STOP_BIT );
	aux	 	|=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Update the data	 */
	auxConfiguration	 =	 cmd[0];
	auxConfiguration   <<=	 8U;
	auxConfiguration	|=	 cmd[1];

	myConfReg->als_sens	 		 =	 (VEML6035_als_conf_sens_t)( auxConfiguration & ALS_CONF_SENS_MASK );
	myConfReg->als_dg	 		 =	 (VEML6035_als_conf_dg_t)( auxConfiguration & ALS_CONF_DG_MASK );
	myConfReg->als_gain	 		 =	 (VEML6035_als_conf_gain_t)( auxConfiguration & ALS_CONF_GAIN_MASK );
	myConfReg->als_it	 		 =	 (VEML6035_als_conf_als_it_t)( auxConfiguration & ALS_CONF_ALS_IT_MASK );
	myConfReg->als_pers	 		 =	 (VEML6035_als_conf_als_pers_t)( auxConfiguration & ALS_CONF_ALS_PERS_MASK );
	myConfReg->als_int_channel	 =	 (VEML6035_als_conf_als_int_channel_t)( auxConfiguration & ALS_CONF_ALS_INT_CHANNEL_MASK );
	myConfReg->als_channel_en	 =	 (VEML6035_als_conf_als_channel_en_t)( auxConfiguration & ALS_CONF_ALS_CHANNEL_EN_MASK );
	myConfReg->als_int_en		 =	 (VEML6035_als_conf_als_int_en_t)( auxConfiguration & ALS_CONF_ALS_INT_EN_MASK );
	myConfReg->als_sd			 =	 (VEML6035_als_conf_als_sd_t)( auxConfiguration & ALS_CONF_ALS_SD_MASK );



	if ( aux == I2C_SUCCESS )
	{
		return   VEML6035_SUCCESS;
	}
	else
	{
		return   VEML6035_FAILURE;
	}
}



/**
 * @brief       VEML6035_SetConfigurationRegister ( I2C_parameters_t , VEML6035_configuration_register_t )
 *
 * @details     It writes the configuration register.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myConfReg:   		It writes the configuration values.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of VEML6035_SetConfigurationRegister.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     It is advisable to use VEML6035_GetConfigurationRegister first, in order to mask the values of
 * 				the register.
 */
VEML6035_status_t VEML6035_SetConfigurationRegister	( I2C_parameters_t myI2Cparameters, VEML6035_configuration_register_t myConfReg )
{
	uint8_t		 cmd[3]				= 	{ 0 };
	uint16_t	 auxConfiguration	=	 0U;
	i2c_status_t aux;

	/* Update the register	 */
	auxConfiguration	 =	 ( myConfReg.als_sens | myConfReg.als_dg | myConfReg.als_gain | myConfReg.als_it | myConfReg.als_pers | myConfReg.als_int_channel | myConfReg.als_channel_en | myConfReg.als_int_en | myConfReg.als_sd );
	cmd[0]				 =	 VEML6035_ALS_CONF;
	cmd[1]				 =	 (uint8_t)( auxConfiguration >> 8U );
	cmd[2]				 =	 (uint8_t)( auxConfiguration );
	aux					 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



	if ( aux == I2C_SUCCESS )
	{
		return   VEML6035_SUCCESS;
	}
	else
	{
		return   VEML6035_FAILURE;
	}
}



/**
 * @brief       VEML6035_SetSensitivity ( I2C_parameters_t , VEML6035_data_t )
 *
 * @details     It sets the sensitivity value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    mySENS:   			Sensitivity value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of VEML6035_SetSensitivity.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_SetSensitivity ( I2C_parameters_t myI2Cparameters, VEML6035_data_t mySENS )
{
	VEML6035_configuration_register_t	auxConfiguration;
	VEML6035_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   VEML6035_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data and update the register	 */
	auxConfiguration.als_sens	 =	 mySENS.configuration.als_sens;
	aux	 	 =   VEML6035_SetConfigurationRegister ( myI2Cparameters, auxConfiguration );


	return   aux;
}



/**
 * @brief       VEML6035_GetSensitivity ( I2C_parameters_t , VEML6035_data_t* )
 *
 * @details     It gets the sensitivity value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   mySENS:   			Sensitivity value.
 *
 *
 * @return       Status of VEML6035_GetSensitivity.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_GetSensitivity ( I2C_parameters_t myI2Cparameters, VEML6035_data_t* mySENS )
{
	VEML6035_configuration_register_t	auxConfiguration;
	VEML6035_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   VEML6035_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data	 */
	mySENS->configuration.als_sens	 =	 auxConfiguration.als_sens;


	return   aux;
}



/**
 * @brief       VEML6035_SetDG ( I2C_parameters_t , VEML6035_data_t )
 *
 * @details     It sets the DG value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myDG:   			DG value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of VEML6035_SetDG.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_SetDG ( I2C_parameters_t myI2Cparameters, VEML6035_data_t myDG )
{
	VEML6035_configuration_register_t	auxConfiguration;
	VEML6035_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   VEML6035_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data and update the register	 */
	auxConfiguration.als_dg	 =	 myDG.configuration.als_dg;
	aux	 	 =   VEML6035_SetConfigurationRegister ( myI2Cparameters, auxConfiguration );


	return   aux;
}



/**
 * @brief       VEML6035_GetDG ( I2C_parameters_t , VEML6035_data_t* )
 *
 * @details     It gets the DG value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myDG:   			DG value..
 *
 *
 * @return       Status of VEML6035_GetDG.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_GetDG ( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myDG )
{
	VEML6035_configuration_register_t	auxConfiguration;
	VEML6035_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   VEML6035_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data	 */
	myDG->configuration.als_dg	 =	 auxConfiguration.als_dg;


	return   aux;
}



/**
 * @brief       VEML6035_SetGain ( I2C_parameters_t , VEML6035_data_t )
 *
 * @details     It sets the gain value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myGain:   			Gain value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of VEML6035_SetGain.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_SetGain ( I2C_parameters_t myI2Cparameters, VEML6035_data_t myGain )
{
	VEML6035_configuration_register_t	auxConfiguration;
	VEML6035_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   VEML6035_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data and update the register	 */
	auxConfiguration.als_gain	 =	 myGain.configuration.als_gain;
	aux	 	 =   VEML6035_SetConfigurationRegister ( myI2Cparameters, auxConfiguration );


	return   aux;
}



/**
 * @brief       VEML6035_GetGain ( I2C_parameters_t , VEML6035_data_t* )
 *
 * @details     It gets the gain value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myGain:   			Gain value.
 *
 *
 * @return       Status of VEML6035_GetGain.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_GetGain ( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myGain )
{
	VEML6035_configuration_register_t	auxConfiguration;
	VEML6035_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   VEML6035_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data	 */
	myGain->configuration.als_gain	 =	 auxConfiguration.als_gain;


	return   aux;
}



/**
 * @brief       VEML6035_SetIntegrationTime ( I2C_parameters_t , VEML6035_data_t )
 *
 * @details     It sets the integration time value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myALS_IT:   		Integration time value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of VEML6035_SetIntegrationTime.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_SetIntegrationTime ( I2C_parameters_t myI2Cparameters, VEML6035_data_t myALS_IT )
{
	VEML6035_configuration_register_t	auxConfiguration;
	VEML6035_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   VEML6035_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data and update the register	 */
	auxConfiguration.als_it	 =	 myALS_IT.configuration.als_it;
	aux	 	 =   VEML6035_SetConfigurationRegister ( myI2Cparameters, auxConfiguration );


	return   aux;
}



/**
 * @brief       VEML6035_GetIntegrationTime ( I2C_parameters_t , VEML6035_data_t* )
 *
 * @details     It gets the integration time value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myALS_IT:   		Integration Time value.
 *
 *
 * @return       Status of VEML6035_GetIntegrationTime.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_GetIntegrationTime ( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myALS_IT )
{
	VEML6035_configuration_register_t	auxConfiguration;
	VEML6035_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   VEML6035_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data	 */
	myALS_IT->configuration.als_it	 =	 auxConfiguration.als_it;


	return   aux;
}



/**
 * @brief       VEML6035_SetInterruptPersistence ( I2C_parameters_t , VEML6035_data_t )
 *
 * @details     It sets the interrupt persistence value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myALS_PERS:   		Interrupt persistence value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of VEML6035_SetInterruptPersistence.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_SetInterruptPersistence ( I2C_parameters_t myI2Cparameters, VEML6035_data_t myALS_PERS )
{
	VEML6035_configuration_register_t	auxConfiguration;
	VEML6035_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   VEML6035_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data and update the register	 */
	auxConfiguration.als_pers	 =	 myALS_PERS.configuration.als_pers;
	aux	 	 =   VEML6035_SetConfigurationRegister ( myI2Cparameters, auxConfiguration );


	return   aux;
}



/**
 * @brief       VEML6035_GetInterruptPersistence ( I2C_parameters_t , VEML6035_data_t* )
 *
 * @details     It gets the interrupt persistence value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myALS_PERS:   		Interrupt persistence value.
 *
 *
 * @return       Status of VEML6035_GetInterruptPersistence.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_GetInterruptPersistence ( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myALS_PERS )
{
	VEML6035_configuration_register_t	auxConfiguration;
	VEML6035_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   VEML6035_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data	 */
	myALS_PERS->configuration.als_pers	 =	 auxConfiguration.als_pers;


	return   aux;
}



/**
 * @brief       VEML6035_SetChannelInterrupt ( I2C_parameters_t , VEML6035_data_t )
 *
 * @details     It sets the channel interrupt value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myINT_CHANNEL:   	Channel interrupt value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of VEML6035_SetChannelInterrupt.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_SetChannelInterrupt ( I2C_parameters_t myI2Cparameters, VEML6035_data_t myINT_CHANNEL )
{
	VEML6035_configuration_register_t	auxConfiguration;
	VEML6035_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   VEML6035_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data and update the register	 */
	auxConfiguration.als_int_channel	 =	 myINT_CHANNEL.configuration.als_int_channel;
	aux	 	 =   VEML6035_SetConfigurationRegister ( myI2Cparameters, auxConfiguration );


	return   aux;
}



/**
 * @brief       VEML6035_GetChannelInterrupt ( I2C_parameters_t , VEML6035_data_t* )
 *
 * @details     It gets the channel interrupt value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myINT_CHANNEL:   	Channel interrupt value.
 *
 *
 * @return       Status of VEML6035_GetChannelInterrupt.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_GetChannelInterrupt ( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myINT_CHANNEL )
{
	VEML6035_configuration_register_t	auxConfiguration;
	VEML6035_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   VEML6035_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data	 */
	myINT_CHANNEL->configuration.als_int_channel	 =	 auxConfiguration.als_int_channel;


	return   aux;
}



/**
 * @brief       VEML6035_SetChannelEnable ( I2C_parameters_t , VEML6035_data_t )
 *
 * @details     It sets the channel enable value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myCHANNEL_EN:   	Channel enable value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of VEML6035_SetChannelEnable.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_SetChannelEnable ( I2C_parameters_t myI2Cparameters, VEML6035_data_t myCHANNEL_EN )
{
	VEML6035_configuration_register_t	auxConfiguration;
	VEML6035_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   VEML6035_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data and update the register	 */
	auxConfiguration.als_channel_en	 =	 myCHANNEL_EN.configuration.als_channel_en;
	aux	 	 =   VEML6035_SetConfigurationRegister ( myI2Cparameters, auxConfiguration );


	return   aux;
}



/**
 * @brief       VEML6035_GetChannelEnable ( I2C_parameters_t , VEML6035_data_t* )
 *
 * @details     It gets the channel enable value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myCHANNEL_EN:   	Channel enable value.
 *
 *
 * @return       Status of VEML6035_GetChannelEnable.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_GetChannelEnable ( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myCHANNEL_EN )
{
	VEML6035_configuration_register_t	auxConfiguration;
	VEML6035_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   VEML6035_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data	 */
	myCHANNEL_EN->configuration.als_channel_en	 =	 auxConfiguration.als_channel_en;


	return   aux;
}



/**
 * @brief       VEML6035_SetInterruptEnable ( I2C_parameters_t , VEML6035_data_t )
 *
 * @details     It sets the interrupt enable value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myINT_EN:   		Interrupt enable value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of VEML6035_SetInterruptEnable.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_SetInterruptEnable ( I2C_parameters_t myI2Cparameters, VEML6035_data_t myINT_EN )
{
	VEML6035_configuration_register_t	auxConfiguration;
	VEML6035_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   VEML6035_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data and update the register	 */
	auxConfiguration.als_int_en	 =	 myINT_EN.configuration.als_int_en;
	aux	 	 =   VEML6035_SetConfigurationRegister ( myI2Cparameters, auxConfiguration );


	return   aux;
}



/**
 * @brief       VEML6035_GetInterruptEnable ( I2C_parameters_t , VEML6035_data_t* )
 *
 * @details     It gets the interrupt enable value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myINT_EN:   		Interrupt enable value.
 *
 *
 * @return       Status of VEML6035_GetInterruptEnable.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_GetInterruptEnable ( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myINT_EN )
{
	VEML6035_configuration_register_t	auxConfiguration;
	VEML6035_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   VEML6035_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data	 */
	myINT_EN->configuration.als_int_en	 =	 auxConfiguration.als_int_en;


	return   aux;
}



/**
 * @brief       VEML6035_SetShutDownMode ( I2C_parameters_t , VEML6035_data_t )
 *
 * @details     It sets the interrupt enable value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    mySD:   			Shutdown mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of VEML6035_SetShutDownMode.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_SetShutDownMode ( I2C_parameters_t myI2Cparameters, VEML6035_data_t mySD )
{
	VEML6035_configuration_register_t	auxConfiguration;
	VEML6035_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   VEML6035_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data and update the register	 */
	auxConfiguration.als_sd	 =	 mySD.configuration.als_sd;
	aux	 	 =   VEML6035_SetConfigurationRegister ( myI2Cparameters, auxConfiguration );


	return   aux;
}



/**
 * @brief       VEML6035_GetShutDownMode ( I2C_parameters_t , VEML6035_data_t* )
 *
 * @details     It gets the shutdown mode.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   mySD:   			Shutdown mode.
 *
 *
 * @return       Status of VEML6035_GetShutDownMode.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_GetShutDownMode ( I2C_parameters_t myI2Cparameters, VEML6035_data_t* mySD )
{
	VEML6035_configuration_register_t	auxConfiguration;
	VEML6035_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   VEML6035_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data	 */
	mySD->configuration.als_sd	 =	 auxConfiguration.als_sd;


	return   aux;
}



/**
 * @brief       VEML6035_SetHighThreshold ( I2C_parameters_t , VEML6035_data_t )
 *
 * @details     It sets the high threshold value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myHighThreshold:   High threshold value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of VEML6035_SetHighThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_SetHighThreshold ( I2C_parameters_t myI2Cparameters, VEML6035_data_t myHighThreshold )
{
	uint8_t			cmd[3]	=	{0};
	i2c_status_t 	aux;


	/* Update the register	 */
	cmd[0]	 =	 VEML6035_ALS_WH;
	cmd[1]	 =	 (uint8_t)( myHighThreshold.int_th_high >> 8U );
	cmd[2]	 =	 (uint8_t)( myHighThreshold.int_th_high );
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



	if ( aux == I2C_SUCCESS )
	{
		return   VEML6035_SUCCESS;
	}
	else
	{
		return   VEML6035_FAILURE;
	}
}



/**
 * @brief       VEML6035_GetHighThreshold ( I2C_parameters_t , VEML6035_data_t* )
 *
 * @details     It gets the high threshold value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myHighThreshold:   High threshold value.
 *
 *
 * @return       Status of VEML6035_GetHighThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_GetHighThreshold ( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myHighThreshold )
{
	uint8_t			cmd[2]	=	{0};
	i2c_status_t 	aux;


	/* Read the register	 */
	cmd[0]	 =	 VEML6035_ALS_WH;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Parse the data	 */
	myHighThreshold->int_th_high	 =	 cmd[0];
	myHighThreshold->int_th_high   <<=	 8U;
	myHighThreshold->int_th_high	|=	 cmd[1];



	if ( aux == I2C_SUCCESS )
	{
		return   VEML6035_SUCCESS;
	}
	else
	{
		return   VEML6035_FAILURE;
	}
}



/**
 * @brief       VEML6035_SetLowThreshold ( I2C_parameters_t , VEML6035_data_t )
 *
 * @details     It sets the low threshold value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myLowThreshold:    Low threshold value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of VEML6035_SetLowThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_SetLowThreshold ( I2C_parameters_t myI2Cparameters, VEML6035_data_t myLowThreshold )
{
	uint8_t			cmd[3]	=	{0};
	i2c_status_t 	aux;


	/* Update the register	 */
	cmd[0]	 =	 VEML6035_ALS_WL;
	cmd[1]	 =	 (uint8_t)( myLowThreshold.int_th_low >> 8U );
	cmd[2]	 =	 (uint8_t)( myLowThreshold.int_th_low );
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



	if ( aux == I2C_SUCCESS )
	{
		return   VEML6035_SUCCESS;
	}
	else
	{
		return   VEML6035_FAILURE;
	}
}



/**
 * @brief       VEML6035_GetLowThreshold ( I2C_parameters_t , VEML6035_data_t* )
 *
 * @details     It gets the low threshold value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myLowThreshold:    Low threshold value.
 *
 *
 * @return       Status of VEML6035_GetLowThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_GetLowThreshold ( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myLowThreshold )
{
	uint8_t			cmd[2]	=	{0};
	i2c_status_t 	aux;


	/* Read the register	 */
	cmd[0]	 =	 VEML6035_ALS_WL;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Parse the data	 */
	myLowThreshold->int_th_low	 =	 cmd[0];
	myLowThreshold->int_th_low <<=	 8U;
	myLowThreshold->int_th_low	|=	 cmd[1];



	if ( aux == I2C_SUCCESS )
	{
		return   VEML6035_SUCCESS;
	}
	else
	{
		return   VEML6035_FAILURE;
	}
}



/**
 * @brief       VEML6035_SetPowerSafeMode ( I2C_parameters_t , VEML6035_data_t )
 *
 * @details     It sets the power safe mode register.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myPowerSafeMode:   PSM_WAIT and PSM_EN values.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of VEML6035_SetPowerSafeMode.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_SetPowerSafeMode ( I2C_parameters_t myI2Cparameters, VEML6035_data_t myPowerSafeMode )
{
	uint8_t			cmd[3]			 =	{0};
	uint16_t		auxPowerSafeMode =  0U;
	i2c_status_t	aux;


	/* Read the register	 */
	cmd[0]	 =	 VEML6035_POWER_SAVING;
	aux		 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux		|=   i2c_read  ( myI2Cparameters, &cmd[1], 2U );


	/* Update the register	 */
	auxPowerSafeMode	 =	 cmd[1];
	auxPowerSafeMode   <<=	 8U;
	auxPowerSafeMode	|=	 cmd[2];

	auxPowerSafeMode	&=	~( POWER_SAVING_PSM_EN_MASK | POWER_SAVING_PSM_WAIT_MASK );
	auxPowerSafeMode	|=	 ( myPowerSafeMode.psm_en | myPowerSafeMode.psm_wait );

	cmd[1]	 =	 (uint8_t)( auxPowerSafeMode >> 8U );
	cmd[2]	 =	 (uint8_t)( auxPowerSafeMode );
	aux 	|=   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



	if ( aux == I2C_SUCCESS )
	{
		return   VEML6035_SUCCESS;
	}
	else
	{
		return   VEML6035_FAILURE;
	}
}



/**
 * @brief       VEML6035_GetPowerSafeMode ( I2C_parameters_t , VEML6035_data_t* )
 *
 * @details     It gets the power safe mode register value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myPowerSafeMode:   PSM_WAIT and PSM_EN values.
 *
 *
 * @return       Status of VEML6035_GetPowerSafeMode.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_GetPowerSafeMode ( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myPowerSafeMode )
{
	uint8_t			cmd[2]			 =	{0U};
	uint16_t		auxPowerSafeMode =  0U;
	i2c_status_t 	aux;


	/* Read the register	 */
	cmd[0]	 =	 VEML6035_POWER_SAVING;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux		|=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Parse the data	 */
	auxPowerSafeMode	 =	 cmd[0];
	auxPowerSafeMode   <<=	 8U;
	auxPowerSafeMode	|=	 cmd[1];

	myPowerSafeMode->psm_wait	=	(VEML6035_power_saving_psm_wait_t)( auxPowerSafeMode & POWER_SAVING_PSM_WAIT_MASK );
	myPowerSafeMode->psm_en		=	(VEML6035_power_saving_psm_en_t)( auxPowerSafeMode & POWER_SAVING_PSM_EN_MASK );



	if ( aux == I2C_SUCCESS )
	{
		return   VEML6035_SUCCESS;
	}
	else
	{
		return   VEML6035_FAILURE;
	}
}



/**
 * @brief       VEML6035_GetALS_HighResOutputData ( I2C_parameters_t , VEML6035_data_t* )
 *
 * @details     It gets the ALS high resolution output data ( raw data ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myALS:   			ALS high resolution output data ( raw data ).
 *
 *
 * @return       Status of VEML6035_GetALS_HighResOutputData.
 *
 *
 * @author      Manuel Caballero
 * @date        20/March/2020
 * @version     20/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_GetALS_HighResOutputData	( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myALS )
{
	uint8_t			cmd[2]	=	{0U};
	i2c_status_t 	aux;


	/* Read the register	 */
	cmd[0]	 =	 VEML6035_ALS;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux		|=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Parse the data	 */
	myALS->als_high_resolution_output_data	  =	 cmd[0];
	myALS->als_high_resolution_output_data	<<=	 8U;
	myALS->als_high_resolution_output_data	 |=	 cmd[1];



	if ( aux == I2C_SUCCESS )
	{
		return   VEML6035_SUCCESS;
	}
	else
	{
		return   VEML6035_FAILURE;
	}
}



/**
 * @brief       VEML6035_GetWhiteChannelOutputData ( I2C_parameters_t , VEML6035_data_t* )
 *
 * @details     It gets the white channel output data ( raw data ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myWhite:  			White channel output data ( raw data ).
 *
 *
 * @return       Status of VEML6035_GetWhiteChannelOutputData.
 *
 *
 * @author      Manuel Caballero
 * @date        20/March/2020
 * @version     20/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_GetWhiteChannelOutputData ( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myWhite )
{
	uint8_t			cmd[2]	=	{0U};
	i2c_status_t 	aux;


	/* Read the register	 */
	cmd[0]	 =	 VEML6035_WHITE;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux		|=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Parse the data	 */
	myWhite->white_channel_output_data	  =	 cmd[0];
	myWhite->white_channel_output_data	<<=	 8U;
	myWhite->white_channel_output_data	 |=	 cmd[1];



	if ( aux == I2C_SUCCESS )
	{
		return   VEML6035_SUCCESS;
	}
	else
	{
		return   VEML6035_FAILURE;
	}
}



/**
 * @brief       VEML6035_GetInterruptStatus ( I2C_parameters_t , VEML6035_data_t* )
 *
 * @details     It gets the interrupt status.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myIF:  			IF_L and IF_H.
 *
 *
 * @return       Status of VEML6035_GetInterruptStatus.
 *
 *
 * @author      Manuel Caballero
 * @date        20/March/2020
 * @version     20/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_GetInterruptStatus ( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myIF )
{
	uint8_t			cmd[2]				=	{0U};
	uint16_t		auxIntTriggerEvent	=	0U;
	i2c_status_t 	aux;


	/* Read the register	 */
	cmd[0]	 =	 VEML6035_ALS_INT;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux		|=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Parse the data	 */
	auxIntTriggerEvent	 =	 cmd[0];
	auxIntTriggerEvent <<=	 8U;
	auxIntTriggerEvent	|=	 cmd[1];

	myIF->int_th_high	 =	(VEML6035_als_int_int_th_high_t)( auxIntTriggerEvent & ALS_INT_INT_TH_HIGH_MASK );
	myIF->int_th_low	 =	(VEML6035_als_int_int_th_low_t)( auxIntTriggerEvent & ALS_INT_INT_TH_LOW_MASK );



	if ( aux == I2C_SUCCESS )
	{
		return   VEML6035_SUCCESS;
	}
	else
	{
		return   VEML6035_FAILURE;
	}
}



/**
 * @brief       VEML6035_CalculateLuxLevel ( I2C_parameters_t , VEML6035_data_t* )
 *
 * @details     It calculates the lux level and the current resolution.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myLux:  			Lux value and current resolution.
 *
 *
 * @return       N/A.
 *
 *
 * @author      Manuel Caballero
 * @date        20/March/2020
 * @version     20/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     The device VEML6035 must be configured properly before calling this function.
 * @warning     VEML6035_GetALS_HighResOutputData function must be called before calling this function.
 */
void VEML6035_CalculateLuxLevel ( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myLux )
{
	uint8_t  auxGain = 0U, auxSens = 0U, auxDG = 0U;
	uint16_t auxIT = 0U;

	/* 1. Identify the parameters	 */
	/* Integration time	 */
	switch ( myLux->configuration.als_it )
	{
	case ALS_CONF_ALS_IT_25MS:
		auxIT	 =	 25U;
		break;

	case ALS_CONF_ALS_IT_50MS:
		auxIT	 =	 50U;
		break;

	default:
	case ALS_CONF_ALS_IT_100MS:
		auxIT	 =	 100U;
		break;

	case ALS_CONF_ALS_IT_200MS:
		auxIT	 =	 200;
		break;

	case ALS_CONF_ALS_IT_400MS:
		auxIT	 =	 400;
		break;

	case ALS_CONF_ALS_IT_800MS:
		auxIT	 =	 800;
		break;
	}

	/* Digital gain ( DG )	 */
	if ( myLux->configuration.als_dg == ALS_CONF_DG_NORMAL )
	{
		auxDG	 =	 1U;
	}
	else
	{
		auxDG	 =	 2U;
	}

	/* Gain	 */
	if ( myLux->configuration.als_gain == ALS_CONF_GAIN_NORMAL_SENSITIVITY )
	{
		auxGain	 =	 1U;
	}
	else
	{
		auxGain	 =	 2U;
	}

	/* Sensitivity	 */
	if ( myLux->configuration.als_sens == ALS_CONF_SENS_HIGH_SENSITIVITY )
	{
		auxSens	 =	 1U;
	}
	else
	{
		auxSens	 =	 8U;
	}

	/* 2. Calculate the current resolution	 */
	myLux->resolution	 =	 (float)( VEML6035_MAXIMUM_RESOLUTION * ( 800U / auxIT ) * ( 2U / auxDG ) * ( 2U / auxGain ) * auxSens );

	/* 3. Calculate the lux value	 */
	myLux->light_level	 =	 (float)( myLux->resolution * myLux->als_high_resolution_output_data );
}
