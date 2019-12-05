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
 * @brief       VEML6030_GetManufacturerID ( I2C_parameters_t , VEML6030_data_t* )
 *
 * @details     It gets the manufacturer ID.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myManufacturerID:	Manufacturer ID.
 *
 *
 * @return       Status of VEML6030_GetManufacturerID.
 *
 *
 * @author      Manuel Caballero
 * @date        19/November/2019
 * @version     19/November/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
VEML6030_status_t VEML6030_GetManufacturerID ( I2C_parameters_t myI2Cparameters, VEML6030_data_t* myManufacturerID )
{
	uint8_t		 cmd = 0;
	i2c_status_t aux;

	/* Read the register */
	//cmd	 =   VEML6030_MANUFACTURER_ID;
	aux	 =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_NO_STOP_BIT );
	aux	 =   i2c_read  ( myI2Cparameters, &cmd, 1U );


	/* Parse data   */
	myManufacturerID->manufacturer_id	=	 cmd;



	if ( aux == I2C_SUCCESS )
	{
		return   VEML6030_SUCCESS;
	}
	else
	{
		return   VEML6030_FAILURE;
	}
}



