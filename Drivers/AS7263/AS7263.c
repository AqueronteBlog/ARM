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
 * @version     12/April/2020   If everything goes fine, it has to return success.
 * 				05/April/2020   The ORIGIN
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

			myStatus =	 AS7263_SUCCESS;
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



/**
 * @brief       AS7263_I2C_VirtualRegisterByteRead ( I2C_parameters_t , AS7263_command_register_set_t , uint8_t* )
 *
 * @details     I2C Virtual Register Byte Read.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    virtualReg:   		Virtual register.
 *
 * @param[out]   d:   				Byte to read.
 *
 *
 * @return       Status of AS7263_I2C_VirtualRegisterByteRead.
 *
 *
 * @author      Manuel Caballero
 * @date        12/April/2020
 * @version     12/April/2020   The ORIGIN
 * @pre         The user does NOT need to use this function, this is an internal function
 * @warning     N/A.
 */
AS7263_status_t AS7263_I2C_VirtualRegisterByteRead	( I2C_parameters_t myI2Cparameters, AS7263_command_register_set_t virtualReg, uint8_t* d )
{
	uint8_t		 	cmd[2]		=	{ 0U };
	uint32_t	 	myTimeout  	=	0UL;
	i2c_status_t 	aux;
	AS7263_status_t myStatus	=	AS7263_FAILURE;


	/* 1. Read slave I2C status to see if the read buffer is ready	 */
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

		/* 3. Read slave I2C status to see if the read buffer is ready	 */
		myTimeout	 =	 0x23232;
		do{
			cmd[0]	 =   AS7263_STATUS_REGISTER;
			aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_NO_STOP_BIT );
			aux		|=   i2c_read  ( myI2Cparameters, &cmd[0], 1U );
			myTimeout--;
		}while( ( ( cmd[0] & AS7263_STATUS_REGISTER_RX_VALID_MASK) == AS7263_STATUS_REGISTER_RX_VALID_BUSY ) && ( aux == I2C_SUCCESS ) && ( myTimeout > 0UL ) );

		/* Check the status	 */
		if ( ( aux == I2C_SUCCESS ) && ( myTimeout > 0UL ) )
		{
			/* 4. Read the data to complete the operation	 */
			cmd[0]	 =   AS7263_READ_REGISTER;
			aux	 	 =   i2c_write ( myI2Cparameters, &cmd[0], 1U, I2C_STOP_BIT );

			*d	 	 =	 cmd[0];
			myStatus =	 AS7263_SUCCESS;
		}
		else if ( myTimeout < 1UL )
		{
			myStatus	 =	 AS7263_ERROR_RX_PENDING;
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



/**
 * @brief       AS7263_GetDeviceType ( I2C_parameters_t , AS7263_hw_version* )
 *
 * @details     Get device type number.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myDeviceType:   	Device type number.
 *
 *
 * @return       Status of AS7263_GetDeviceType.
 *
 *
 * @author      Manuel Caballero
 * @date        12/April/2020
 * @version     12/April/2020   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetDeviceType ( I2C_parameters_t myI2Cparameters, AS7263_hw_version* myDeviceType )
{
	uint8_t		 	cmd	=	0U;
	AS7263_status_t aux	=	AS7263_FAILURE;


	/* Read the register	 */
	cmd	 =   AS7263_DEVICE_TYPE;
	aux	 =   AS7263_I2C_VirtualRegisterByteRead	( myI2Cparameters, cmd, &myDeviceType->device_type );



	return aux;
}



/**
 * @brief       AS7263_GetHardwareVersion ( I2C_parameters_t , AS7263_hw_version* )
 *
 * @details     Get HW version.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myHWversion:   	Hardware version.
 *
 *
 * @return       Status of AS7263_GetHardwareVersion.
 *
 *
 * @author      Manuel Caballero
 * @date        12/April/2020
 * @version     12/April/2020   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetHardwareVersion ( I2C_parameters_t myI2Cparameters, AS7263_hw_version* myHWversion )
{
	uint8_t		 	cmd	=	0U;
	AS7263_status_t aux	=	AS7263_FAILURE;


	/* Read the register	 */
	cmd	 =   AS7263_HW_VERSION;
	aux	 =   AS7263_I2C_VirtualRegisterByteRead	( myI2Cparameters, cmd, &myHWversion->hw_version );



	return aux;
}



/**
 * @brief       AS7263_GetFirmwareVersion ( I2C_parameters_t , AS7263_fw_version* )
 *
 * @details     Get FW version.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myFWversion:   	Firmware version parameters.
 *
 *
 * @return       Status of AS7263_GetFirmwareVersion.
 *
 *
 * @author      Manuel Caballero
 * @date        12/April/2020
 * @version     12/April/2020   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetFirmwareVersion ( I2C_parameters_t myI2Cparameters, AS7263_fw_version* myFWversion )
{
	uint8_t		 	cmd			=	0U;
	AS7263_status_t aux			=	AS7263_FAILURE;


	/* Read the second FW register	 */
	cmd	 =   AS7263_FW_VERSION_2;
	aux	|=   AS7263_I2C_VirtualRegisterByteRead	( myI2Cparameters, cmd, &cmd );

	myFWversion->major_version 	 =	 (uint8_t)( cmd & FW_VERSION_MAJOR_VERSION_MASK );
	myFWversion->minor_version	 =	 (uint8_t)( cmd & FW_VERSION_MINOR_VERSION_5_2_MASK );
	myFWversion->minor_version <<=	 2U;

	/* Read the first FW register	 */
	cmd	 =   AS7263_FW_VERSION_1;
	aux	 =   AS7263_I2C_VirtualRegisterByteRead	( myI2Cparameters, cmd, &cmd );

	myFWversion->subversion	 	 =	 (uint8_t)( cmd & FW_VERSION_SUB_VERSION_MASK );
	myFWversion->minor_version	|=	 (uint8_t)( cmd & FW_VERSION_MINOR_VERSION_1_0_MASK );



	return aux;
}



/**
 * @brief       AS7263_SetSoftReset ( I2C_parameters_t )
 *
 * @details     Set softreset.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS7263_SetSoftReset.
 *
 *
 * @author      Manuel Caballero
 * @date        12/April/2020
 * @version     12/April/2020   The ORIGIN
 * @pre         The user must check the device has rebooted correctly before starting a new communication again.
 * @warning     N/A.
 */
AS7263_status_t AS7263_SetSoftReset ( I2C_parameters_t myI2Cparameters )
{
	uint8_t		 	cmd[2]	=	{ 0U };
	AS7263_status_t aux		=	AS7263_FAILURE;

	/* Read the register	 */
	cmd[0]	 =   AS7263_CONTROL_SETUP;
	aux	 	 =   AS7263_I2C_VirtualRegisterByteRead ( myI2Cparameters, cmd[0], &cmd[1] );

	/* Parse the data and Write the register	 */
	cmd[1]	&=   CONTROL_SETUP_RST_MASK;
	cmd[1]	|=   CONTROL_SETUP_RST_SOFTRESET;
	aux		 =   AS7263_I2C_VirtualRegisterByteWrite ( myI2Cparameters, cmd[0], cmd[1] );



	return aux;
}



/**
 * @brief       AS7263_GetSoftResetStatus ( I2C_parameters_t , AS7263_control_setup_rst* )
 *
 * @details     Get softreset status.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRST:				Softreset status.
 *
 *
 * @return       Status of AS7263_GetSoftResetStatus.
 *
 *
 * @author      Manuel Caballero
 * @date        12/April/2020
 * @version     12/April/2020   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetSoftResetStatus ( I2C_parameters_t myI2Cparameters, AS7263_control_setup_rst* myRST )
{
	uint8_t		 	cmd	=	0U;
	AS7263_status_t aux	=	AS7263_FAILURE;

	/* Read the register	 */
	cmd	 =   AS7263_CONTROL_SETUP;
	aux	 =   AS7263_I2C_VirtualRegisterByteRead ( myI2Cparameters, cmd, &cmd );

	/* Parse the data	 */
	*myRST	 =	 (AS7263_control_setup_rst)( cmd & CONTROL_SETUP_RST_MASK );



	return aux;
}



/**
 * @brief       AS7263_SetEnableIntPinOutput ( I2C_parameters_t , AS7263_control_setup_int )
 *
 * @details     Set enable/disable interrupt pin output.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myINT:   			INT pin output enable/disable.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS7263_SetEnableIntPinOutput.
 *
 *
 * @author      Manuel Caballero
 * @date        12/April/2020
 * @version     12/April/2020   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS7263_status_t AS7263_SetEnableIntPinOutput ( I2C_parameters_t myI2Cparameters, AS7263_control_setup_int myINT )
{
	uint8_t		 	cmd[2]	=	{ 0U };
	AS7263_status_t aux		=	AS7263_FAILURE;

	/* Read the register	 */
	cmd[0]	 =   AS7263_CONTROL_SETUP;
	aux	 	 =   AS7263_I2C_VirtualRegisterByteRead ( myI2Cparameters, cmd[0], &cmd[1] );

	/* Parse the data and Write the register	 */
	cmd[1]	&=   CONTROL_SETUP_INT_MASK;
	cmd[1]	|=   myINT;
	aux		 =   AS7263_I2C_VirtualRegisterByteWrite ( myI2Cparameters, cmd[0], cmd[1] );



	return aux;
}



/**
 * @brief       AS7263_GetEnableIntPinOutput ( I2C_parameters_t , AS7263_control_setup_int* )
 *
 * @details     Get enable/disable interrupt pin output status.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myINT:   			INT pin output enable/disable status.
 *
 *
 * @return       Status of AS7263_GetEnableIntPinOutput.
 *
 *
 * @author      Manuel Caballero
 * @date        12/April/2020
 * @version     12/April/2020   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetEnableIntPinOutput ( I2C_parameters_t myI2Cparameters, AS7263_control_setup_int* myINT )
{
	uint8_t		 	cmd	=	0U;
	AS7263_status_t aux	=	AS7263_FAILURE;

	/* Read the register	 */
	cmd	 =   AS7263_CONTROL_SETUP;
	aux	 =   AS7263_I2C_VirtualRegisterByteRead ( myI2Cparameters, cmd, &cmd );

	/* Parse the data	 */
	*myINT	 =	 (AS7263_control_setup_int)( cmd & CONTROL_SETUP_INT_MASK );



	return aux;
}



/**
 * @brief       AS7263_SetChannelsGain ( I2C_parameters_t , AS7263_control_setup_gain )
 *
 * @details     Set sensor channel gain setting ( all channels ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myGAIN:   			Gain for all channels.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS7263_SetChannelsGain.
 *
 *
 * @author      Manuel Caballero
 * @date        07/May/2020
 * @version     07/May/2020   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS7263_status_t AS7263_SetChannelsGain ( I2C_parameters_t myI2Cparameters, AS7263_control_setup_gain myGAIN )
{
	uint8_t		 	cmd[2]	=	{ 0U };
	AS7263_status_t aux		=	AS7263_FAILURE;

	/* Read the register	 */
	cmd[0]	 =   AS7263_CONTROL_SETUP;
	aux	 	 =   AS7263_I2C_VirtualRegisterByteRead ( myI2Cparameters, cmd[0], &cmd[1] );

	/* Parse the data and Write the register	 */
	cmd[1]	&=   CONTROL_SETUP_GAIN_MASK;
	cmd[1]	|=   myGAIN;
	aux		 =   AS7263_I2C_VirtualRegisterByteWrite ( myI2Cparameters, cmd[0], cmd[1] );



	return aux;
}



/**
 * @brief       AS7263_GetChannelsGain ( I2C_parameters_t , AS7263_control_setup_gain* )
 *
 * @details     Get sensor channel gain setting ( all channels ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myGAIN:   			Gain for all channels.
 *
 *
 * @return       Status of AS7263_GetChannelsGain.
 *
 *
 * @author      Manuel Caballero
 * @date        07/May/2020
 * @version     07/May/2020   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetChannelsGain ( I2C_parameters_t myI2Cparameters, AS7263_control_setup_gain* myGAIN )
{
	uint8_t		 	cmd	=	0U;
	AS7263_status_t aux	=	AS7263_FAILURE;

	/* Read the register	 */
	cmd	 =   AS7263_CONTROL_SETUP;
	aux	 =   AS7263_I2C_VirtualRegisterByteRead ( myI2Cparameters, cmd, &cmd );

	/* Parse the data	 */
	*myGAIN	 =	 (AS7263_control_setup_gain)( cmd & CONTROL_SETUP_GAIN_MASK );



	return aux;
}



/**
 * @brief       AS7263_SetDataConversionType ( I2C_parameters_t , AS7263_control_setup_bank )
 *
 * @details     Set data conversion type.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myBANK:   			Data conversion type.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS7263_SetDataConversionType.
 *
 *
 * @author      Manuel Caballero
 * @date        07/May/2020
 * @version     07/May/2020   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS7263_status_t AS7263_SetDataConversionType ( I2C_parameters_t myI2Cparameters, AS7263_control_setup_bank myBANK )
{
	uint8_t		 	cmd[2]	=	{ 0U };
	AS7263_status_t aux		=	AS7263_FAILURE;

	/* Read the register	 */
	cmd[0]	 =   AS7263_CONTROL_SETUP;
	aux	 	 =   AS7263_I2C_VirtualRegisterByteRead ( myI2Cparameters, cmd[0], &cmd[1] );

	/* Parse the data and Write the register	 */
	cmd[1]	&=   CONTROL_SETUP_BANK_MASK;
	cmd[1]	|=   myBANK;
	aux		 =   AS7263_I2C_VirtualRegisterByteWrite ( myI2Cparameters, cmd[0], cmd[1] );



	return aux;
}



/**
 * @brief       AS7263_GetDataConversionType ( I2C_parameters_t , AS7263_control_setup_bank* )
 *
 * @details     Get data conversion type.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myBANK:   			Data conversion type.
 *
 *
 * @return       Status of AS7263_GetDataConversionType.
 *
 *
 * @author      Manuel Caballero
 * @date        07/May/2020
 * @version     07/May/2020   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetDataConversionType ( I2C_parameters_t myI2Cparameters, AS7263_control_setup_bank* myBANK )
{
	uint8_t		 	cmd	=	0U;
	AS7263_status_t aux	=	AS7263_FAILURE;

	/* Read the register	 */
	cmd	 =   AS7263_CONTROL_SETUP;
	aux	 =   AS7263_I2C_VirtualRegisterByteRead ( myI2Cparameters, cmd, &cmd );

	/* Parse the data	 */
	*myBANK	 =	 (AS7263_control_setup_bank)( cmd & CONTROL_SETUP_BANK_MASK );



	return aux;
}



/**
 * @brief       AS7263_GetDataReadyFlag ( I2C_parameters_t , AS7263_control_setup_data_rdy* )
 *
 * @details     Get data ready flag.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myDATA_RDY:   		Data ready flag value.
 *
 *
 * @return       Status of AS7263_GetDataReadyFlag.
 *
 *
 * @author      Manuel Caballero
 * @date        07/May/2020
 * @version     07/May/2020   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetDataReadyFlag	( I2C_parameters_t myI2Cparameters, AS7263_control_setup_data_rdy* myDATA_RDY )
{
	uint8_t		 	cmd	=	0U;
	AS7263_status_t aux	=	AS7263_FAILURE;

	/* Read the register	 */
	cmd	 =   AS7263_CONTROL_SETUP;
	aux	 =   AS7263_I2C_VirtualRegisterByteRead ( myI2Cparameters, cmd, &cmd );

	/* Parse the data	 */
	*myDATA_RDY	 =	 (AS7263_control_setup_data_rdy)( cmd & CONTROL_SETUP_DATA_RDY_MASK );



	return aux;
}



/**
 * @brief       AS7263_SetIntegrationTime ( I2C_parameters_t , uint8_t* )
 *
 * @details     Set integration time: Integration time = <value> * 2.8ms.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myINT_T:   		Integration time = <value> * 2.8ms.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS7263_SetIntegrationTime.
 *
 *
 * @author      Manuel Caballero
 * @date        07/May/2020
 * @version     07/May/2020   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
AS7263_status_t AS7263_SetIntegrationTime ( I2C_parameters_t myI2Cparameters, uint8_t myINT_T )
{
	uint8_t		 	cmd[2]	=	{ 0U };
	AS7263_status_t aux		=	AS7263_FAILURE;

	/* Write the register	 */
	cmd[0]	 =   AS7263_INT_T;
	cmd[1]	 =   myINT_T;
	aux		 =   AS7263_I2C_VirtualRegisterByteWrite ( myI2Cparameters, cmd[0], cmd[1] );



	return aux;
}



/**
 * @brief       AS7263_GetIntegrationTime ( I2C_parameters_t , uint8_t* )
 *
 * @details     Get integration time: Integration time = <value> * 2.8ms.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myINT_T:   		Integration time = <value> * 2.8ms.
 *
 *
 * @return       Status of AS7263_GetIntegrationTime.
 *
 *
 * @author      Manuel Caballero
 * @date        07/May/2020
 * @version     07/May/2020   The ORIGIN
 * @pre         This function returns a raw data, the user must multiply the value by 2.8ms in order
 * 				to calculate the integration time.
 * @warning     N/A.
 */
AS7263_status_t AS7263_GetIntegrationTime ( I2C_parameters_t myI2Cparameters, uint8_t* myINT_T )
{
	uint8_t		 	cmd	=	0U;
	AS7263_status_t aux	=	AS7263_FAILURE;

	/* Read the register	 */
	cmd	 =   AS7263_INT_T;
	aux	 =   AS7263_I2C_VirtualRegisterByteRead ( myI2Cparameters, cmd, &cmd );

	/* Parse the data	 */
	*myINT_T	 =	 cmd;



	return aux;
}
