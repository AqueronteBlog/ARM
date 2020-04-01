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
AS7263_status_t AS7263_GetConfigurationRegister	( I2C_parameters_t myI2Cparameters, AS7263_configuration_register_t* myConfReg )
{
	uint8_t		 cmd[2]  			= 	{ 0 };
	uint16_t	 auxConfiguration	=	 0U;
	i2c_status_t aux;

	/* Read the register	 */
	cmd[0]	 =   AS7263_ALS_CONF;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1UL, I2C_NO_STOP_BIT );
	aux	 	|=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Update the data	 */
	auxConfiguration	 =	 cmd[0];
	auxConfiguration   <<=	 8U;
	auxConfiguration	|=	 cmd[1];

	myConfReg->als_sens	 		 =	 (AS7263_als_conf_sens_t)( auxConfiguration & ALS_CONF_SENS_MASK );
	myConfReg->als_dg	 		 =	 (AS7263_als_conf_dg_t)( auxConfiguration & ALS_CONF_DG_MASK );
	myConfReg->als_gain	 		 =	 (AS7263_als_conf_gain_t)( auxConfiguration & ALS_CONF_GAIN_MASK );
	myConfReg->als_it	 		 =	 (AS7263_als_conf_als_it_t)( auxConfiguration & ALS_CONF_ALS_IT_MASK );
	myConfReg->als_pers	 		 =	 (AS7263_als_conf_als_pers_t)( auxConfiguration & ALS_CONF_ALS_PERS_MASK );
	myConfReg->als_int_channel	 =	 (AS7263_als_conf_als_int_channel_t)( auxConfiguration & ALS_CONF_ALS_INT_CHANNEL_MASK );
	myConfReg->als_channel_en	 =	 (AS7263_als_conf_als_channel_en_t)( auxConfiguration & ALS_CONF_ALS_CHANNEL_EN_MASK );
	myConfReg->als_int_en		 =	 (AS7263_als_conf_als_int_en_t)( auxConfiguration & ALS_CONF_ALS_INT_EN_MASK );
	myConfReg->als_sd			 =	 (AS7263_als_conf_als_sd_t)( auxConfiguration & ALS_CONF_ALS_SD_MASK );



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
 * @brief       AS7263_SetConfigurationRegister ( I2C_parameters_t , AS7263_configuration_register_t )
 *
 * @details     It writes the configuration register.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myConfReg:   		It writes the configuration values.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS7263_SetConfigurationRegister.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     It is advisable to use AS7263_GetConfigurationRegister first, in order to mask the values of
 * 				the register.
 */
AS7263_status_t AS7263_SetConfigurationRegister	( I2C_parameters_t myI2Cparameters, AS7263_configuration_register_t myConfReg )
{
	uint8_t		 cmd[3]				= 	{ 0 };
	uint16_t	 auxConfiguration	=	 0U;
	i2c_status_t aux;

	/* Update the register	 */
	auxConfiguration	 =	 ( myConfReg.als_sens | myConfReg.als_dg | myConfReg.als_gain | myConfReg.als_it | myConfReg.als_pers | myConfReg.als_int_channel | myConfReg.als_channel_en | myConfReg.als_int_en | myConfReg.als_sd );
	cmd[0]				 =	 AS7263_ALS_CONF;
	cmd[1]				 =	 (uint8_t)( auxConfiguration >> 8U );
	cmd[2]				 =	 (uint8_t)( auxConfiguration );
	aux					 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



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
 * @brief       AS7263_SetSensitivity ( I2C_parameters_t , AS7263_data_t )
 *
 * @details     It sets the sensitivity value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    mySENS:   			Sensitivity value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS7263_SetSensitivity.
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
	AS7263_configuration_register_t	auxConfiguration;
	AS7263_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   AS7263_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data and update the register	 */
	auxConfiguration.als_sens	 =	 mySENS.configuration.als_sens;
	aux	 	 =   AS7263_SetConfigurationRegister ( myI2Cparameters, auxConfiguration );


	return   aux;
}



/**
 * @brief       AS7263_GetSensitivity ( I2C_parameters_t , AS7263_data_t* )
 *
 * @details     It gets the sensitivity value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   mySENS:   			Sensitivity value.
 *
 *
 * @return       Status of AS7263_GetSensitivity.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetSensitivity ( I2C_parameters_t myI2Cparameters, AS7263_data_t* mySENS )
{
	AS7263_configuration_register_t	auxConfiguration;
	AS7263_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   AS7263_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data	 */
	mySENS->configuration.als_sens	 =	 auxConfiguration.als_sens;


	return   aux;
}



/**
 * @brief       AS7263_SetDG ( I2C_parameters_t , AS7263_data_t )
 *
 * @details     It sets the DG value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myDG:   			DG value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS7263_SetDG.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_SetDG ( I2C_parameters_t myI2Cparameters, AS7263_data_t myDG )
{
	AS7263_configuration_register_t	auxConfiguration;
	AS7263_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   AS7263_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data and update the register	 */
	auxConfiguration.als_dg	 =	 myDG.configuration.als_dg;
	aux	 	 =   AS7263_SetConfigurationRegister ( myI2Cparameters, auxConfiguration );


	return   aux;
}



/**
 * @brief       AS7263_GetDG ( I2C_parameters_t , AS7263_data_t* )
 *
 * @details     It gets the DG value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myDG:   			DG value..
 *
 *
 * @return       Status of AS7263_GetDG.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetDG ( I2C_parameters_t myI2Cparameters, AS7263_data_t* myDG )
{
	AS7263_configuration_register_t	auxConfiguration;
	AS7263_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   AS7263_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data	 */
	myDG->configuration.als_dg	 =	 auxConfiguration.als_dg;


	return   aux;
}



/**
 * @brief       AS7263_SetGain ( I2C_parameters_t , AS7263_data_t )
 *
 * @details     It sets the gain value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myGain:   			Gain value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS7263_SetGain.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_SetGain ( I2C_parameters_t myI2Cparameters, AS7263_data_t myGain )
{
	AS7263_configuration_register_t	auxConfiguration;
	AS7263_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   AS7263_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data and update the register	 */
	auxConfiguration.als_gain	 =	 myGain.configuration.als_gain;
	aux	 	 =   AS7263_SetConfigurationRegister ( myI2Cparameters, auxConfiguration );


	return   aux;
}



/**
 * @brief       AS7263_GetGain ( I2C_parameters_t , AS7263_data_t* )
 *
 * @details     It gets the gain value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myGain:   			Gain value.
 *
 *
 * @return       Status of AS7263_GetGain.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetGain ( I2C_parameters_t myI2Cparameters, AS7263_data_t* myGain )
{
	AS7263_configuration_register_t	auxConfiguration;
	AS7263_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   AS7263_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data	 */
	myGain->configuration.als_gain	 =	 auxConfiguration.als_gain;


	return   aux;
}



/**
 * @brief       AS7263_SetIntegrationTime ( I2C_parameters_t , AS7263_data_t )
 *
 * @details     It sets the integration time value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myALS_IT:   		Integration time value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS7263_SetIntegrationTime.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_SetIntegrationTime ( I2C_parameters_t myI2Cparameters, AS7263_data_t myALS_IT )
{
	AS7263_configuration_register_t	auxConfiguration;
	AS7263_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   AS7263_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data and update the register	 */
	auxConfiguration.als_it	 =	 myALS_IT.configuration.als_it;
	aux	 	 =   AS7263_SetConfigurationRegister ( myI2Cparameters, auxConfiguration );


	return   aux;
}



/**
 * @brief       AS7263_GetIntegrationTime ( I2C_parameters_t , AS7263_data_t* )
 *
 * @details     It gets the integration time value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myALS_IT:   		Integration Time value.
 *
 *
 * @return       Status of AS7263_GetIntegrationTime.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetIntegrationTime ( I2C_parameters_t myI2Cparameters, AS7263_data_t* myALS_IT )
{
	AS7263_configuration_register_t	auxConfiguration;
	AS7263_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   AS7263_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data	 */
	myALS_IT->configuration.als_it	 =	 auxConfiguration.als_it;


	return   aux;
}



/**
 * @brief       AS7263_SetInterruptPersistence ( I2C_parameters_t , AS7263_data_t )
 *
 * @details     It sets the interrupt persistence value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myALS_PERS:   		Interrupt persistence value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS7263_SetInterruptPersistence.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_SetInterruptPersistence ( I2C_parameters_t myI2Cparameters, AS7263_data_t myALS_PERS )
{
	AS7263_configuration_register_t	auxConfiguration;
	AS7263_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   AS7263_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data and update the register	 */
	auxConfiguration.als_pers	 =	 myALS_PERS.configuration.als_pers;
	aux	 	 =   AS7263_SetConfigurationRegister ( myI2Cparameters, auxConfiguration );


	return   aux;
}



/**
 * @brief       AS7263_GetInterruptPersistence ( I2C_parameters_t , AS7263_data_t* )
 *
 * @details     It gets the interrupt persistence value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myALS_PERS:   		Interrupt persistence value.
 *
 *
 * @return       Status of AS7263_GetInterruptPersistence.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetInterruptPersistence ( I2C_parameters_t myI2Cparameters, AS7263_data_t* myALS_PERS )
{
	AS7263_configuration_register_t	auxConfiguration;
	AS7263_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   AS7263_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data	 */
	myALS_PERS->configuration.als_pers	 =	 auxConfiguration.als_pers;


	return   aux;
}



/**
 * @brief       AS7263_SetChannelInterrupt ( I2C_parameters_t , AS7263_data_t )
 *
 * @details     It sets the channel interrupt value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myINT_CHANNEL:   	Channel interrupt value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS7263_SetChannelInterrupt.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_SetChannelInterrupt ( I2C_parameters_t myI2Cparameters, AS7263_data_t myINT_CHANNEL )
{
	AS7263_configuration_register_t	auxConfiguration;
	AS7263_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   AS7263_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data and update the register	 */
	auxConfiguration.als_int_channel	 =	 myINT_CHANNEL.configuration.als_int_channel;
	aux	 	 =   AS7263_SetConfigurationRegister ( myI2Cparameters, auxConfiguration );


	return   aux;
}



/**
 * @brief       AS7263_GetChannelInterrupt ( I2C_parameters_t , AS7263_data_t* )
 *
 * @details     It gets the channel interrupt value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myINT_CHANNEL:   	Channel interrupt value.
 *
 *
 * @return       Status of AS7263_GetChannelInterrupt.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetChannelInterrupt ( I2C_parameters_t myI2Cparameters, AS7263_data_t* myINT_CHANNEL )
{
	AS7263_configuration_register_t	auxConfiguration;
	AS7263_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   AS7263_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data	 */
	myINT_CHANNEL->configuration.als_int_channel	 =	 auxConfiguration.als_int_channel;


	return   aux;
}



/**
 * @brief       AS7263_SetChannelEnable ( I2C_parameters_t , AS7263_data_t )
 *
 * @details     It sets the channel enable value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myCHANNEL_EN:   	Channel enable value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS7263_SetChannelEnable.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_SetChannelEnable ( I2C_parameters_t myI2Cparameters, AS7263_data_t myCHANNEL_EN )
{
	AS7263_configuration_register_t	auxConfiguration;
	AS7263_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   AS7263_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data and update the register	 */
	auxConfiguration.als_channel_en	 =	 myCHANNEL_EN.configuration.als_channel_en;
	aux	 	 =   AS7263_SetConfigurationRegister ( myI2Cparameters, auxConfiguration );


	return   aux;
}



/**
 * @brief       AS7263_GetChannelEnable ( I2C_parameters_t , AS7263_data_t* )
 *
 * @details     It gets the channel enable value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myCHANNEL_EN:   	Channel enable value.
 *
 *
 * @return       Status of AS7263_GetChannelEnable.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetChannelEnable ( I2C_parameters_t myI2Cparameters, AS7263_data_t* myCHANNEL_EN )
{
	AS7263_configuration_register_t	auxConfiguration;
	AS7263_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   AS7263_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data	 */
	myCHANNEL_EN->configuration.als_channel_en	 =	 auxConfiguration.als_channel_en;


	return   aux;
}



/**
 * @brief       AS7263_SetInterruptEnable ( I2C_parameters_t , AS7263_data_t )
 *
 * @details     It sets the interrupt enable value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myINT_EN:   		Interrupt enable value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS7263_SetInterruptEnable.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_SetInterruptEnable ( I2C_parameters_t myI2Cparameters, AS7263_data_t myINT_EN )
{
	AS7263_configuration_register_t	auxConfiguration;
	AS7263_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   AS7263_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data and update the register	 */
	auxConfiguration.als_int_en	 =	 myINT_EN.configuration.als_int_en;
	aux	 	 =   AS7263_SetConfigurationRegister ( myI2Cparameters, auxConfiguration );


	return   aux;
}



/**
 * @brief       AS7263_GetInterruptEnable ( I2C_parameters_t , AS7263_data_t* )
 *
 * @details     It gets the interrupt enable value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myINT_EN:   		Interrupt enable value.
 *
 *
 * @return       Status of AS7263_GetInterruptEnable.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetInterruptEnable ( I2C_parameters_t myI2Cparameters, AS7263_data_t* myINT_EN )
{
	AS7263_configuration_register_t	auxConfiguration;
	AS7263_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   AS7263_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data	 */
	myINT_EN->configuration.als_int_en	 =	 auxConfiguration.als_int_en;


	return   aux;
}



/**
 * @brief       AS7263_SetShutDownMode ( I2C_parameters_t , AS7263_data_t )
 *
 * @details     It sets the interrupt enable value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    mySD:   			Shutdown mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS7263_SetShutDownMode.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_SetShutDownMode ( I2C_parameters_t myI2Cparameters, AS7263_data_t mySD )
{
	AS7263_configuration_register_t	auxConfiguration;
	AS7263_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   AS7263_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data and update the register	 */
	auxConfiguration.als_sd	 =	 mySD.configuration.als_sd;
	aux	 	 =   AS7263_SetConfigurationRegister ( myI2Cparameters, auxConfiguration );


	return   aux;
}



/**
 * @brief       AS7263_GetShutDownMode ( I2C_parameters_t , AS7263_data_t* )
 *
 * @details     It gets the shutdown mode.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   mySD:   			Shutdown mode.
 *
 *
 * @return       Status of AS7263_GetShutDownMode.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetShutDownMode ( I2C_parameters_t myI2Cparameters, AS7263_data_t* mySD )
{
	AS7263_configuration_register_t	auxConfiguration;
	AS7263_status_t 					aux;


	/* Read the register	 */
	aux	 	 =   AS7263_GetConfigurationRegister ( myI2Cparameters, &auxConfiguration );

	/* Parse the data	 */
	mySD->configuration.als_sd	 =	 auxConfiguration.als_sd;


	return   aux;
}



/**
 * @brief       AS7263_SetHighThreshold ( I2C_parameters_t , AS7263_data_t )
 *
 * @details     It sets the high threshold value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myHighThreshold:   High threshold value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS7263_SetHighThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_SetHighThreshold ( I2C_parameters_t myI2Cparameters, AS7263_data_t myHighThreshold )
{
	uint8_t			cmd[3]	=	{0};
	i2c_status_t 	aux;


	/* Update the register	 */
	cmd[0]	 =	 AS7263_ALS_WH;
	cmd[1]	 =	 (uint8_t)( myHighThreshold.int_th_high >> 8U );
	cmd[2]	 =	 (uint8_t)( myHighThreshold.int_th_high );
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



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
 * @brief       AS7263_GetHighThreshold ( I2C_parameters_t , AS7263_data_t* )
 *
 * @details     It gets the high threshold value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myHighThreshold:   High threshold value.
 *
 *
 * @return       Status of AS7263_GetHighThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetHighThreshold ( I2C_parameters_t myI2Cparameters, AS7263_data_t* myHighThreshold )
{
	uint8_t			cmd[2]	=	{0};
	i2c_status_t 	aux;


	/* Read the register	 */
	cmd[0]	 =	 AS7263_ALS_WH;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Parse the data	 */
	myHighThreshold->int_th_high	 =	 cmd[0];
	myHighThreshold->int_th_high   <<=	 8U;
	myHighThreshold->int_th_high	|=	 cmd[1];



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
 * @brief       AS7263_SetLowThreshold ( I2C_parameters_t , AS7263_data_t )
 *
 * @details     It sets the low threshold value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myLowThreshold:    Low threshold value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS7263_SetLowThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_SetLowThreshold ( I2C_parameters_t myI2Cparameters, AS7263_data_t myLowThreshold )
{
	uint8_t			cmd[3]	=	{0};
	i2c_status_t 	aux;


	/* Update the register	 */
	cmd[0]	 =	 AS7263_ALS_WL;
	cmd[1]	 =	 (uint8_t)( myLowThreshold.int_th_low >> 8U );
	cmd[2]	 =	 (uint8_t)( myLowThreshold.int_th_low );
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



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
 * @brief       AS7263_GetLowThreshold ( I2C_parameters_t , AS7263_data_t* )
 *
 * @details     It gets the low threshold value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myLowThreshold:    Low threshold value.
 *
 *
 * @return       Status of AS7263_GetLowThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetLowThreshold ( I2C_parameters_t myI2Cparameters, AS7263_data_t* myLowThreshold )
{
	uint8_t			cmd[2]	=	{0};
	i2c_status_t 	aux;


	/* Read the register	 */
	cmd[0]	 =	 AS7263_ALS_WL;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Parse the data	 */
	myLowThreshold->int_th_low	 =	 cmd[0];
	myLowThreshold->int_th_low <<=	 8U;
	myLowThreshold->int_th_low	|=	 cmd[1];



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
 * @brief       AS7263_SetPowerSafeMode ( I2C_parameters_t , AS7263_data_t )
 *
 * @details     It sets the power safe mode register.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myPowerSafeMode:   PSM_WAIT and PSM_EN values.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS7263_SetPowerSafeMode.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_SetPowerSafeMode ( I2C_parameters_t myI2Cparameters, AS7263_data_t myPowerSafeMode )
{
	uint8_t			cmd[3]			 =	{0};
	uint16_t		auxPowerSafeMode =  0U;
	i2c_status_t	aux;


	/* Read the register	 */
	cmd[0]	 =	 AS7263_POWER_SAVING;
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
		return   AS7263_SUCCESS;
	}
	else
	{
		return   AS7263_FAILURE;
	}
}



/**
 * @brief       AS7263_GetPowerSafeMode ( I2C_parameters_t , AS7263_data_t* )
 *
 * @details     It gets the power safe mode register value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myPowerSafeMode:   PSM_WAIT and PSM_EN values.
 *
 *
 * @return       Status of AS7263_GetPowerSafeMode.
 *
 *
 * @author      Manuel Caballero
 * @date        19/March/2020
 * @version     19/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetPowerSafeMode ( I2C_parameters_t myI2Cparameters, AS7263_data_t* myPowerSafeMode )
{
	uint8_t			cmd[2]			 =	{0U};
	uint16_t		auxPowerSafeMode =  0U;
	i2c_status_t 	aux;


	/* Read the register	 */
	cmd[0]	 =	 AS7263_POWER_SAVING;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux		|=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Parse the data	 */
	auxPowerSafeMode	 =	 cmd[0];
	auxPowerSafeMode   <<=	 8U;
	auxPowerSafeMode	|=	 cmd[1];

	myPowerSafeMode->psm_wait	=	(AS7263_power_saving_psm_wait_t)( auxPowerSafeMode & POWER_SAVING_PSM_WAIT_MASK );
	myPowerSafeMode->psm_en		=	(AS7263_power_saving_psm_en_t)( auxPowerSafeMode & POWER_SAVING_PSM_EN_MASK );



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
 * @brief       AS7263_GetALS_HighResOutputData ( I2C_parameters_t , AS7263_data_t* )
 *
 * @details     It gets the ALS high resolution output data ( raw data ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myALS:   			ALS high resolution output data ( raw data ).
 *
 *
 * @return       Status of AS7263_GetALS_HighResOutputData.
 *
 *
 * @author      Manuel Caballero
 * @date        20/March/2020
 * @version     20/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetALS_HighResOutputData	( I2C_parameters_t myI2Cparameters, AS7263_data_t* myALS )
{
	uint8_t			cmd[2]	=	{0U};
	i2c_status_t 	aux;


	/* Read the register	 */
	cmd[0]	 =	 AS7263_ALS;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux		|=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Parse the data	 */
	myALS->als_high_resolution_output_data	  =	 cmd[0];
	myALS->als_high_resolution_output_data	<<=	 8U;
	myALS->als_high_resolution_output_data	 |=	 cmd[1];



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
 * @brief       AS7263_GetWhiteChannelOutputData ( I2C_parameters_t , AS7263_data_t* )
 *
 * @details     It gets the white channel output data ( raw data ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myWhite:  			White channel output data ( raw data ).
 *
 *
 * @return       Status of AS7263_GetWhiteChannelOutputData.
 *
 *
 * @author      Manuel Caballero
 * @date        20/March/2020
 * @version     20/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetWhiteChannelOutputData ( I2C_parameters_t myI2Cparameters, AS7263_data_t* myWhite )
{
	uint8_t			cmd[2]	=	{0U};
	i2c_status_t 	aux;


	/* Read the register	 */
	cmd[0]	 =	 AS7263_WHITE;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux		|=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Parse the data	 */
	myWhite->white_channel_output_data	  =	 cmd[0];
	myWhite->white_channel_output_data	<<=	 8U;
	myWhite->white_channel_output_data	 |=	 cmd[1];



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
 * @brief       AS7263_GetInterruptStatus ( I2C_parameters_t , AS7263_data_t* )
 *
 * @details     It gets the interrupt status.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myIF:  			IF_L and IF_H.
 *
 *
 * @return       Status of AS7263_GetInterruptStatus.
 *
 *
 * @author      Manuel Caballero
 * @date        20/March/2020
 * @version     20/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetInterruptStatus ( I2C_parameters_t myI2Cparameters, AS7263_data_t* myIF )
{
	uint8_t			cmd[2]				=	{0U};
	uint16_t		auxIntTriggerEvent	=	0U;
	i2c_status_t 	aux;


	/* Read the register	 */
	cmd[0]	 =	 AS7263_ALS_INT;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux		|=   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Parse the data	 */
	auxIntTriggerEvent	 =	 cmd[0];
	auxIntTriggerEvent <<=	 8U;
	auxIntTriggerEvent	|=	 cmd[1];

	myIF->int_th_high	 =	(AS7263_als_int_int_th_high_t)( auxIntTriggerEvent & ALS_INT_INT_TH_HIGH_MASK );
	myIF->int_th_low	 =	(AS7263_als_int_int_th_low_t)( auxIntTriggerEvent & ALS_INT_INT_TH_LOW_MASK );



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
 * @brief       AS7263_CalculateLuxLevel ( AS7263_data_t* )
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
 * @warning     The device AS7263 must be configured properly before calling this function.
 * @warning     AS7263_GetALS_HighResOutputData function must be called before calling this function.
 */
void AS7263_CalculateLuxLevel ( AS7263_data_t* myLux )
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
	myLux->resolution	 =	 (float)( AS7263_MAXIMUM_RESOLUTION * ( 800U / auxIT ) * ( 2U / auxDG ) * ( 2U / auxGain ) * auxSens );

	/* 3. Calculate the lux value	 */
	myLux->light_level	 =	 (float)( myLux->resolution * myLux->als_high_resolution_output_data );
}
