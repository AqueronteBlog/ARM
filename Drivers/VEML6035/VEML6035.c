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
 * @brief       VEML6035_SetConfiguration ( I2C_parameters_t , VEML6035_data_t )
 *
 * @details     It sets the configuration register.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myALS_Conf:   		ALS gain, integration time, interrupt, and shut down.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of VEML6035_SetConfiguration.
 *
 *
 * @author      Manuel Caballero
 * @date        17/March/2020
 * @version     17/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_SetConfiguration ( I2C_parameters_t myI2Cparameters, VEML6035_data_t myALS_Conf )
{
	uint8_t		 cmd[3]  = { 0 };
	uint16_t	 aux_reg = 0U;
	i2c_status_t aux;

	/* Update the register	 */
	aux_reg	 =	 ( myALS_Conf.als_gain | myALS_Conf.als_it | myALS_Conf.als_pers | myALS_Conf.als_int_en | myALS_Conf.als_sd );

	cmd[0]	 =   VEML6035_ALS_CONF;
	cmd[1]	 =	 (uint8_t)( aux_reg >> 2U );
	cmd[2]	 =	 (uint8_t)( aux_reg & 0xFF );
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
 * @brief       VEML6035_SetHighThreshold ( I2C_parameters_t , VEML6035_data_t )
 *
 * @details     It sets the high threshold windows value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myALS_WH:   		High threshold windows value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of VEML6035_SetHighThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        17/March/2020
 * @version     17/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_SetHighThreshold ( I2C_parameters_t myI2Cparameters, VEML6035_data_t myALS_WH )
{
	uint8_t		 cmd[3]  = { 0 };
	i2c_status_t aux;

	/* Update the register	 */
	cmd[0]	 =   VEML6035_ALS_WH;
	cmd[1]	 =	 (uint8_t)( myALS_WH.high_threshold_windows_setting >> 2U );
	cmd[2]	 =	 (uint8_t)( myALS_WH.high_threshold_windows_setting & 0xFF );
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
 * @brief       VEML6035_SetLowThreshold ( I2C_parameters_t , VEML6035_data_t )
 *
 * @details     It sets the low threshold windows value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myALS_WL:   		Low threshold windows value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of VEML6035_SetHighThreshold.
 *
 *
 * @author      Manuel Caballero
 * @date        17/March/2020
 * @version     17/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_SetLowThreshold ( I2C_parameters_t myI2Cparameters, VEML6035_data_t myALS_WL )
{
	uint8_t		 cmd[3]  = { 0 };
	i2c_status_t aux;

	/* Update the register	 */
	cmd[0]	 =   VEML6035_ALS_WL;
	cmd[1]	 =	 (uint8_t)( myALS_WL.low_threshold_windows_setting >> 2U );
	cmd[2]	 =	 (uint8_t)( myALS_WL.low_threshold_windows_setting & 0xFF );
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
 * @brief       VEML6035_SetPowerSavingModes ( I2C_parameters_t , VEML6035_data_t )
 *
 * @details     It sets the power saving modes.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myPSM:		   		PSM and PSM_EN.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of VEML6035_SetPowerSavingModes.
 *
 *
 * @author      Manuel Caballero
 * @date        17/March/2020
 * @version     17/March/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_SetPowerSavingModes ( I2C_parameters_t myI2Cparameters, VEML6035_data_t myPSM )
{
	uint8_t		 cmd[3]  = { 0 };
	uint16_t	 aux_reg = 0U;
	i2c_status_t aux;

	/* Update the register	 */
	aux_reg	 =	 ( myPSM.psm | myPSM.psm_en );

	cmd[0]	 =   VEML6035_POWER_SAVING;
	cmd[1]	 =	 (uint8_t)( aux_reg >> 2U );
	cmd[2]	 =	 (uint8_t)( aux_reg & 0xFF );
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
 * @brief       VEML6035_GetALS_OuputData ( I2C_parameters_t , VEML6035_data_t* )
 *
 * @details     It gets the ALS high resolution output data.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myALS:		   		ALS high resolution output data.
 *
 *
 * @return       Status of VEML6035_GetALS_OuputData.
 *
 *
 * @author      Manuel Caballero
 * @date        17/March/2020
 * @version     17/March/2020   The ORIGIN
 * @pre         This function returns raw data.
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_GetALS_OuputData ( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myALS )
{
	uint8_t		 cmd[2]  = { 0 };
	i2c_status_t aux;

	/* Read the register	 */
	cmd[0]	 =   VEML6035_ALS;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Parse the data	 */
	myALS->als_high_resolution_output_data	 =	 cmd[0];
	myALS->als_high_resolution_output_data <<=	 8U;
	myALS->als_high_resolution_output_data	|=	 cmd[1];



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
 * @brief       VEML6035_GetWhiteChannelOuputData ( I2C_parameters_t , VEML6035_data_t* )
 *
 * @details     It gets the WHITE output data.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myWhite:	   		WHITE output data.
 *
 *
 * @return       Status of VEML6035_GetWhiteChannelOuputData.
 *
 *
 * @author      Manuel Caballero
 * @date        17/March/2020
 * @version     17/March/2020   The ORIGIN
 * @pre         This function returns raw data.
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_GetWhiteChannelOuputData	( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myWhite )
{
	uint8_t		 cmd[2]  = { 0 };
	i2c_status_t aux;

	/* Read the register	 */
	cmd[0]	 =   VEML6035_WHITE;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Parse the data	 */
	myWhite->white_output_data	 =	 cmd[0];
	myWhite->white_output_data <<=	 8U;
	myWhite->white_output_data	|=	 cmd[1];



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
 * @details     It gets the Interrupt status value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myIntStatus:	   	Status for: int_th_low and int_th_high.
 *
 *
 * @return       Status of VEML6035_GetInterruptStatus.
 *
 *
 * @author      Manuel Caballero
 * @date        17/March/2020
 * @version     17/March/2020   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_GetInterruptStatus ( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myIntStatus )
{
	uint8_t		 cmd[2]  = { 0 };
	uint16_t	 aux_reg = 0U;
	i2c_status_t aux;

	/* Read the register	 */
	cmd[0]	 =   VEML6035_ALS_INT;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Parse the data	 */
	aux_reg						 =	 cmd[0];
	aux_reg						<<=	 8U;
	aux_reg						|=	 cmd[1];

	myIntStatus->int_th_high	 =	(VEML6035_als_int_int_th_high_t)( aux_reg & ALS_INT_INT_TH_HIGH_MASK );
	myIntStatus->int_th_low		|=	(VEML6035_als_int_int_th_low_t)( aux_reg & ALS_INT_INT_TH_LOW_MASK );



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
 * @brief       VEML6035_CalculateLuxValue ( I2C_parameters_t , VEML6035_data_t* )
 *
 * @details     It calculates the total lux value.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myLuxValue:   		Raw ALS output data.
 *
 * @param[out]   myLuxValue:	   	Lux value, resolution.
 *
 *
 * @return       Status of VEML6035_CalculateLuxValue.
 *
 *
 * @author      Manuel Caballero
 * @date        17/March/2020
 * @version     17/March/2020   The ORIGIN
 * @pre         NOT Tested!.
 * @warning     N/A.
 */
VEML6035_status_t VEML6035_CalculateLuxValue ( I2C_parameters_t myI2Cparameters, VEML6035_data_t* myLuxValue )
{
	uint32_t	auxRes	 =	 0U;
	double		a1 = 0, a2 = 0, a3 = 0, a4 = 0;


	/* Initial resolution	 */
	auxRes	 =	 TYPICAL_RESOLUTION_GAIN_2_IT_800MS;


	/* Calculate the resolution regarding the integration time	 */
	switch ( myLuxValue->als_it )
	{
		case ALS_CONF_ALS_IT_25MS:
			auxRes <<=	 5U;	// auxRes *= 32
			break;

		case ALS_CONF_ALS_IT_50MS:
			auxRes <<=	 4U;	// auxRes *= 16
			break;

		case ALS_CONF_ALS_IT_100MS:
			auxRes <<=	 3U;	// auxRes *= 8
			break;

		case ALS_CONF_ALS_IT_200MS:
			auxRes <<=	 2U;	// auxRes *= 4
			break;

		case ALS_CONF_ALS_IT_400MS:
			auxRes <<=	 1U;	// auxRes *= 2
			break;

		default:
		case ALS_CONF_ALS_IT_800MS:
			break;
	}

	/* Calculate the resolution regarding the gain	 */
	switch ( myLuxValue->als_gain )
	{
		case ALS_CONF_ALS_GAIN_X1:
			auxRes <<=	 1U;	// auxRes *= 2
			break;

		default:
		case ALS_CONF_ALS_GAIN_X2:
			break;

		case ALS_CONF_ALS_GAIN_X1_4:
			auxRes <<=	 3U;	// auxRes *= 8
			break;

		case ALS_CONF_ALS_GAIN_X1_8:
			auxRes <<=	 4U;	// auxRes *= 16
			break;
	}


	/* Calculate the resolution	 */
	myLuxValue->resolution	 =	 (float)( auxRes / 10000.0 );

	/* Calculate the light level	 */
	myLuxValue->light_level	 =	 (float)( ( myLuxValue->als_high_resolution_output_data * auxRes ) / 10000.0 );

	/* Check if a correction formula needs to be applied	 */
	if ( myLuxValue->light_level > 1000 )
	{
		a1	 =	 0.00000000000060135*pow((uint32_t)myLuxValue->light_level, 4);
		a2	 =	 0.0000000093924*pow((uint32_t)myLuxValue->light_level, 3);
		a3	 =	 0.000081488*pow((uint32_t)myLuxValue->light_level, 2);
		a4	 =	 1.0023*myLuxValue->light_level;

		myLuxValue->light_level	 =	(float)( a1 - a2 + a3 + a4 );
	}

	return   VEML6035_SUCCESS;
}



