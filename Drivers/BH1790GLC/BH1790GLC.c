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
 * @brief       BH1790GLC_SetSystemControl ( I2C_parameters_t , BH1790GLC_data_t )
 *
 * @details     It sets the system control setting.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myMeasControl1:    System control parameters: LED_LIGHTING_FREQ and RCYCLE.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of BH1790GLC_SetSystemControl.
 *
 *
 * @author      Manuel Caballero
 * @date        19/November/2019
 * @version     19/November/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_SetSystemControl ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t myMeasControl1 )
{
	uint8_t		 cmd[2] = { 0 };
	i2c_status_t aux;

	/* Read the register */
	cmd[0]	 =   BH1790GLC_MEAS_CONTROL1;
	aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
	aux	 	 =   i2c_read  ( myI2Cparameters, &cmd[0], 1U );

	/* Mask and Update the register	 */
	cmd[1]	&=  ~( MEAS_CONTROL1_LED_LIGHTING_FREQ_MASK | MEAS_CONTROL1_RCYCLE_MASK );
	cmd[1]	|=   ( myMeasControl1.led_lighting_freq | myMeasControl1.rcycle );
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
 * @brief       BH1790GLC_GetSystemControl ( I2C_parameters_t , BH1790GLC_data_t* )
 *
 * @details     It gets the system control setting.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myMeasControl1:    System control parameters: RDY, LED_LIGHTING_FREQ and RCYCLE.
 *
 *
 * @return       Status of BH1790GLC_GetSystemControl.
 *
 *
 * @author      Manuel Caballero
 * @date        19/November/2019
 * @version     19/November/2019   The ORIGIN
 * @pre         This function updates the RDY too.
 * @warning     N/A.
 */
BH1790GLC_status_t BH1790GLC_GetSystemControl ( I2C_parameters_t myI2Cparameters, BH1790GLC_data_t* myMeasControl1 )
{
	uint8_t		 cmd = 0;
	i2c_status_t aux;

	/* Read the register */
	cmd	 =   BH1790GLC_MEAS_CONTROL1;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );

	/* Parse the data	 */
	myMeasControl1->rdy	 				 =	(BH1790GLC_meas_control1_rdy_t)( cmd & MEAS_CONTROL1_RDY_MASK );
	myMeasControl1->led_lighting_freq	 =	(BH1790GLC_meas_control1_led_lighting_freq_t)( cmd & MEAS_CONTROL1_LED_LIGHTING_FREQ_MASK );
	myMeasControl1->rcycle				 =	(BH1790GLC_meas_control1_rcycle_t)( cmd & MEAS_CONTROL1_RCYCLE_MASK );



	if ( aux == I2C_SUCCESS )
	{
		return   BH1790GLC_SUCCESS;
	}
	else
	{
		return   BH1790GLC_FAILURE;
	}
}
