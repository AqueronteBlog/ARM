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
 * @pre         This code belongs to Nimbus Centre ( https://www.nimbus.cit.ie ).
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
 * @brief       AS7263_I2C_VirtualRegisterByteWrite ( I2C_parameters_t , AS7263_command_register_set_t , uint8_t )
 *
 * @details     I2C Virtual Register Byte Write.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    virtualReg:   		Virtual register.
 * @param[in]    d:   				Byte to write.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS7263_I2C_VirtualRegisterByteWrite.
 *
 *
 * @author      Manuel Caballero
 * @date        05/April/2020
 * @version     05/April/2020   The ORIGIN
 * @pre         The user does NOT need to use this function, this is an internal function
 * @warning     N/A.
 */
AS7263_status_t AS7263_I2C_VirtualRegisterByteWrite	( I2C_parameters_t myI2Cparameters, AS7263_command_register_set_t virtualReg, uint8_t d )
{
	uint8_t		 	cmd[2]		=	{ 0U };
	uint32_t	 	myTimeout  	=	0UL;
	i2c_status_t 	aux;
	AS7263_status_t myStatus	=	AS7263_FAILURE;


	/* 1. Read slave I2C status to see if the write buffer is ready	 */
	myTimeout	 =	 0x23232;
	do{
		cmd[0]	 =   AS7263_STATUS_REGISTER;
		aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
		aux		|=   i2c_read  ( myI2Cparameters, &cmd[0], 1U );
		myTimeout--;
	}while( ( ( cmd[0] & AS7263_STATUS_REGISTER_TX_VALID_MASK) == AS7263_STATUS_REGISTER_TX_VALID_BUSY ) && ( aux == I2C_SUCCESS ) && ( myTimeout > 0UL ) );

	/* Check the status	 */
	if ( ( aux == I2C_SUCCESS ) && ( myTimeout > 0UL ) )
	{
		/* 2. Send the virtual register address (setting bit 7 to indicate a pending write)	 */
		cmd[0]	 =   AS7263_WRITE_REGISTER;
		cmd[1]	 =	 (uint8_t)( virtualReg | 0x80 );
		aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );

		/* 3. Read slave I2C status to see if the write buffer is ready	 */
		myTimeout	 =	 0x23232;
		do{
			cmd[0]	 =   AS7263_STATUS_REGISTER;
			aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
			aux		|=   i2c_read  ( myI2Cparameters, &cmd[0], 1U );
			myTimeout--;
		}while( ( ( cmd[0] & AS7263_STATUS_REGISTER_TX_VALID_MASK) == AS7263_STATUS_REGISTER_TX_VALID_BUSY ) && ( aux == I2C_SUCCESS ) && ( myTimeout > 0UL ) );

		/* Check the status	 */
		if ( ( aux == I2C_SUCCESS ) && ( myTimeout > 0UL ) )
		{
			/* 4. Send the data to complete the operation	 */
			cmd[0]	 =   AS7263_WRITE_REGISTER;
			cmd[1]	 =	 d;
			aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
		}
		else if ( myTimeout < 1UL )
		{
			myStatus	 =	 AS7263_ERROR_TX_PENDING;
		}
		else
		{
			myStatus	 =   AS7263_FAILURE;
		}
	}
	else if ( myTimeout < 1UL )
	{
		myStatus	 =	 AS7263_ERROR_TX_PENDING;
	}
	else
	{
		myStatus	 =   AS7263_FAILURE;
	}


	return myStatus;
}
