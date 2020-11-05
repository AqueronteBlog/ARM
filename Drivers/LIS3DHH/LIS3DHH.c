/**
 * @brief       LIS3DHH.c
 * @details     3D Low Frequency Wakeup Receiver.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        11/October/2020
 * @version     11/October/2020    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */

#include "LIS3DHH.h"


/**
 * @brief       LIS3DHH_Init   ( spi_parameters_t )
 *
 * @details     It configures the SPI pins.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LIS3DHH_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        14/October/2020
 * @version     14/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_Init ( spi_parameters_t mySPI_parameters )
{
    spi_status_t mySPI_status;


    /* Configure the SPI peripheral	 */
    mySPI_status     =   spi_init ( mySPI_parameters );




    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_GetDeviceIdentification ( spi_parameters_t , LIS3DHH_data_t* )
 *
 * @details     It gets the device identification.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myID:				Device identifier.
 *
 *
 * @return       Status of LIS3DHH_GetDeviceIdentification.
 *
 *
 * @author      Manuel Caballero
 * @date        14/October/2020
 * @version     14/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetDeviceIdentification ( spi_parameters_t mySPI_parameters, LIS3DHH_data_t* myID )
{
	uint8_t      cmd   =    ( LIS3DHH_READ | LIS3DHH_WHO_AM_I );
	spi_status_t mySPI_status;


    /* Read the device identifier	 */
    mySPI_status	 =   spi_transfer ( mySPI_parameters, &cmd, 1U, (uint8_t*)(&myID->who_am_i), 1U );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_SetPowerMode ( spi_parameters_t , LIS3DHH_ctrl_reg1_norm_mod_en_t )
 *
 * @details     It sets the power mode: Normal/Power down.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myPowerMode:  		Power mode: CTRL_REG1_NORM_MOD_EN_POWER_DOWN/CTRL_REG1_NORM_MOD_EN_ENABLED.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LIS3DHH_SetPowerMode.
 *
 *
 * @author      Manuel Caballero
 * @date        20/October/2020
 * @version     20/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_SetPowerMode ( spi_parameters_t mySPI_parameters, LIS3DHH_ctrl_reg1_norm_mod_en_t myPowerMode )
{
	uint8_t      cmd[2]   =    { 0U };
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd[0]		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG1 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], 1U, &cmd[1], 1U );

	/* Mask the data and update the register	 */
	cmd[0]		 =	 ( LIS3DHH_WRITE & LIS3DHH_CTRL_REG1 );
	cmd[1]		 =	 ( cmd[1] & CTRL_REG1_NORM_MOD_EN_MASK ) | myPowerMode;
    mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_GetPowerMode ( spi_parameters_t , LIS3DHH_ctrl_reg1_norm_mod_en_t* )
 *
 * @details     It gets the power mode: Normal/Power down.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myPowerMode:  		Power mode: CTRL_REG1_NORM_MOD_EN_POWER_DOWN/CTRL_REG1_NORM_MOD_EN_ENABLED.
 *
 *
 * @return       Status of LIS3DHH_GetPowerMode.
 *
 *
 * @author      Manuel Caballero
 * @date        20/October/2020
 * @version     29/October/2020   The output must be masked! This bug was fixed.
 * 				20/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetPowerMode	( spi_parameters_t mySPI_parameters, LIS3DHH_ctrl_reg1_norm_mod_en_t* myPowerMode )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG1 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 1U );

	/* Mask and parse the data	 */
	*myPowerMode	 =	(LIS3DHH_ctrl_reg1_norm_mod_en_t)( cmd & CTRL_REG1_NORM_MOD_EN_MASK );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_SetRegisterAutoIncrement ( spi_parameters_t , LIS3DHH_ctrl_reg1_if_add_inc_t )
 *
 * @details     It sets the register address automatically incremented during a multiple byte access with SPI serial interface.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myIF_ADD_INC: 		Register address auto increment: CTRL_REG1_IF_ADD_INC_DISABLED/CTRL_REG1_IF_ADD_INC_ENABLED.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LIS3DHH_SetRegisterAutoIncrement.
 *
 *
 * @author      Manuel Caballero
 * @date        28/October/2020
 * @version     28/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_SetRegisterAutoIncrement ( spi_parameters_t mySPI_parameters, LIS3DHH_ctrl_reg1_if_add_inc_t myIF_ADD_INC )
{
	uint8_t      cmd[2]   =    { 0U };
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd[0]		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG1 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], 1U, &cmd[1], 1U );

	/* Mask the data and update the register	 */
	cmd[0]		 =	 ( LIS3DHH_WRITE & LIS3DHH_CTRL_REG1 );
	cmd[1]		 =	 ( cmd[1] & CTRL_REG1_IF_ADD_INC_MASK ) | myIF_ADD_INC;
    mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_GetRegisterAutoIncrement ( spi_parameters_t , LIS3DHH_ctrl_reg1_if_add_inc_t* )
 *
 * @details     It gets the register address automatically incremented during a multiple byte access with SPI serial interface.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myIF_ADD_INC: 		Register address auto increment: CTRL_REG1_IF_ADD_INC_DISABLED/CTRL_REG1_IF_ADD_INC_ENABLED.
 *
 *
 * @return       Status of LIS3DHH_GetRegisterAutoIncrement.
 *
 *
 * @author      Manuel Caballero
 * @date        28/October/2020
 * @version     29/October/2020   The output must be masked! This bug was fixed.
 * 				28/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetRegisterAutoIncrement ( spi_parameters_t mySPI_parameters, LIS3DHH_ctrl_reg1_if_add_inc_t* myIF_ADD_INC )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG1 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 1U );

	/* Mask and parse the data	 */
	*myIF_ADD_INC	 =	(LIS3DHH_ctrl_reg1_if_add_inc_t)( cmd & CTRL_REG1_IF_ADD_INC_MASK );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_SetRebootMemoryContent ( spi_parameters_t , LIS3DHH_ctrl_reg1_boot_t )
 *
 * @details     It sets the reboot memory content.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myBoot: 			Reboot memory content: CTRL_REG1_BOOT_NORMAL_MODE/CTRL_REG1_BOOT_REBOOT_MEMORY_CONTENT.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LIS3DHH_SetRebootMemoryContent.
 *
 *
 * @author      Manuel Caballero
 * @date        28/October/2020
 * @version     28/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_SetRebootMemoryContent ( spi_parameters_t mySPI_parameters, LIS3DHH_ctrl_reg1_boot_t myBoot )
{
	uint8_t      cmd[2]   =    { 0U };
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd[0]		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG1 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], 1U, &cmd[1], 1U );

	/* Mask the data and update the register	 */
	cmd[0]		 =	 ( LIS3DHH_WRITE & LIS3DHH_CTRL_REG1 );
	cmd[1]		 =	 ( cmd[1] & CTRL_REG1_BOOT_MASK ) | myBoot;
    mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_GetRebootMemoryContent ( spi_parameters_t , LIS3DHH_ctrl_reg1_boot_t* )
 *
 * @details     It gets Reboot memory content value.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myBoot: 			Reboot memory content: CTRL_REG1_BOOT_NORMAL_MODE/CTRL_REG1_BOOT_REBOOT_MEMORY_CONTENT.
 *
 *
 * @return       Status of LIS3DHH_GetRebootMemoryContent.
 *
 *
 * @author      Manuel Caballero
 * @date        28/October/2020
 * @version     29/October/2020   The output must be masked! This bug was fixed.
 * 				28/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetRebootMemoryContent ( spi_parameters_t mySPI_parameters, LIS3DHH_ctrl_reg1_boot_t* myBoot )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG1 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 1U );

	/* Mask and parse the data	 */
	*myBoot	 =	(LIS3DHH_ctrl_reg1_boot_t)( cmd & CTRL_REG1_BOOT_MASK );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_SoftwareReset ( spi_parameters_t )
 *
 * @details     It performs a software reset.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LIS3DHH_SoftwareReset.
 *
 *
 * @author      Manuel Caballero
 * @date        28/October/2020
 * @version     28/October/2020   The ORIGIN
 * @pre         This bit is cleared by hardware at the end of the operation.
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_SoftwareReset ( spi_parameters_t mySPI_parameters )
{
	uint8_t      cmd[2]   =    { 0U };
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd[0]		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG1 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], 1U, &cmd[1], 1U );

	/* Mask the data and update the register	 */
	cmd[0]		 =	 ( LIS3DHH_WRITE & LIS3DHH_CTRL_REG1 );
	cmd[1]		 =	 ( cmd[1] & CTRL_REG1_SW_RESET_MASK ) | CTRL_REG1_SW_RESET_RESET_DEVICE;
    mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_GetSoftwareResetStatus ( spi_parameters_t , LIS3DHH_ctrl_reg1_sw_reset_t* )
 *
 * @details     It gets the status of the device after a software reset.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   mySW_Reset: 		Software reset flag: CTRL_REG1_SW_RESET_NORMAL_MODE/CTRL_REG1_SW_RESET_RESET_DEVICE.
 *
 *
 * @return       Status of LIS3DHH_GetSoftwareResetStatus.
 *
 *
 * @author      Manuel Caballero
 * @date        28/October/2020
 * @version     29/October/2020   The output must be masked! This bug was fixed.
 * 				28/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetSoftwareResetStatus ( spi_parameters_t mySPI_parameters, LIS3DHH_ctrl_reg1_sw_reset_t* mySW_Reset )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG1 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 1U );

	/* Mask and parse the data	 */
	*mySW_Reset	 =	(LIS3DHH_ctrl_reg1_sw_reset_t)( cmd & CTRL_REG1_SW_RESET_MASK );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_SetDataReadyOnINT1 ( spi_parameters_t , LIS3DHH_ctrl_reg1_drdy_pulse_t )
 *
 * @details     It sets data ready on INT1 pin.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myDRDY_PULSE: 		Data ready on INT1 pin: CTRL_REG1_DRDY_PULSE_DRDY_LATCHED/CTRL_REG1_DRDY_PULSE_DRDY_PULSED.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LIS3DHH_SetDataReadyOnINT1.
 *
 *
 * @author      Manuel Caballero
 * @date        28/October/2020
 * @version     28/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_SetDataReadyOnINT1 ( spi_parameters_t mySPI_parameters, LIS3DHH_ctrl_reg1_drdy_pulse_t myDRDY_PULSE )
{
	uint8_t      cmd[2]   =    { 0U };
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd[0]		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG1 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], 1U, &cmd[1], 1U );

	/* Mask the data and update the register	 */
	cmd[0]		 =	 ( LIS3DHH_WRITE & LIS3DHH_CTRL_REG1 );
	cmd[1]		 =	 ( cmd[1] & CTRL_REG1_DRDY_PULSE_MASK ) | myDRDY_PULSE;
    mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_GetDataReadyOnINT1 ( spi_parameters_t , LIS3DHH_ctrl_reg1_drdy_pulse_t* )
 *
 * @details     It the status of data ready on INT1 pin.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myDRDY_PULSE: 		Data ready on INT1 pin: CTRL_REG1_DRDY_PULSE_DRDY_LATCHED/CTRL_REG1_DRDY_PULSE_DRDY_PULSED.
 *
 *
 * @return       Status of LIS3DHH_GetDataReadyOnINT1.
 *
 *
 * @author      Manuel Caballero
 * @date        28/October/2020
 * @version     29/October/2020   The output must be masked!, this bug was fixed.
 * 				28/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetDataReadyOnINT1 ( spi_parameters_t mySPI_parameters, LIS3DHH_ctrl_reg1_drdy_pulse_t* myDRDY_PULSE )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG1 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 1U );

	/* Mask and parse the data	 */
	*myDRDY_PULSE	 =	(LIS3DHH_ctrl_reg1_drdy_pulse_t)( cmd & CTRL_REG1_DRDY_PULSE_MASK );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_SetBlockDataUpdate ( spi_parameters_t , LIS3DHH_ctrl_reg1_bdu_t )
 *
 * @details     It sets the block data update.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myBDU: 			Block data update: CTRL_REG1_BDU_CONTINUOUS_UPDATE/CTRL_REG1_BDU_UPDATE_UNTIL_MSB_LSB_READ.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LIS3DHH_SetBlockDataUpdate.
 *
 *
 * @author      Manuel Caballero
 * @date        28/October/2020
 * @version     28/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_SetBlockDataUpdate ( spi_parameters_t mySPI_parameters, LIS3DHH_ctrl_reg1_bdu_t myBDU )
{
	uint8_t      cmd[2]   =    { 0U };
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd[0]		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG1 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], 1U, &cmd[1], 1U );

	/* Mask the data and update the register	 */
	cmd[0]		 =	 ( LIS3DHH_WRITE & LIS3DHH_CTRL_REG1 );
	cmd[1]		 =	 ( cmd[1] & CTRL_REG1_BDU_MASK ) | myBDU;
    mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_GetBlockDataUpdate ( spi_parameters_t , LIS3DHH_ctrl_reg1_bdu_t* )
 *
 * @details     It gets the block data update status.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myBDU: 			Block data update: CTRL_REG1_BDU_CONTINUOUS_UPDATE/CTRL_REG1_BDU_UPDATE_UNTIL_MSB_LSB_READ.
 *
 *
 * @return       Status of LIS3DHH_GetBlockDataUpdate.
 *
 *
 * @author      Manuel Caballero
 * @date        28/October/2020
 * @version     29/October/2020   The output must be masked!, this bug was fixed.
 * 				28/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetBlockDataUpdate ( spi_parameters_t mySPI_parameters, LIS3DHH_ctrl_reg1_bdu_t* myBDU )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG1 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 1U );

	/* Mask and parse the data	 */
	*myBDU	 =	(LIS3DHH_ctrl_reg1_bdu_t)( cmd & CTRL_REG1_BDU_MASK );




    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_SetINT1 ( spi_parameters_t , LIS3DHH_int1_data_t )
 *
 * @details     It sets the set of interrupts INT1 pin.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myINT1: 			Set of interrupts (INT1) on pin.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LIS3DHH_SetINT1.
 *
 *
 * @author      Manuel Caballero
 * @date        28/October/2020
 * @version     28/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_SetINT1 ( spi_parameters_t mySPI_parameters, LIS3DHH_int1_data_t myINT1 )
{
	uint8_t      cmd[2]   =    { 0U };
	spi_status_t mySPI_status;


	/* Update the register	 */
	cmd[0]		 =	 ( LIS3DHH_WRITE & LIS3DHH_INT1_CTRL );
	cmd[1]		 =	 ( myINT1.int1_drdy | myINT1.int1_boot | myINT1.int1_ovr | myINT1.int1_fss5 | myINT1.int1_fth | myINT1.int1_ext );
    mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_GetINT1 ( spi_parameters_t , LIS3DHH_int1_data_t* )
 *
 * @details     It gets the configuration of the set of interrupts INT1 pin.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myINT1: 			Set of interrupts (INT1) on pin..
 *
 *
 * @return       Status of LIS3DHH_GetINT1.
 *
 *
 * @author      Manuel Caballero
 * @date        28/October/2020
 * @version     28/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetINT1 ( spi_parameters_t mySPI_parameters, LIS3DHH_int1_data_t* myINT1 )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_INT1_CTRL );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 1U );

	/* Parse the data	 */
	myINT1->int1_drdy	 =	(LIS3DHH_int1_ctrl_int1_drdy_t)( cmd & INT1_CTRL_INT1_DRDY_MASK );
	myINT1->int1_boot	 =	(LIS3DHH_int1_ctrl_int1_boot_t)( cmd & INT1_CTRL_INT1_BOOT_MASK );
	myINT1->int1_ovr	 =	(LIS3DHH_int1_ctrl_int1_ovr_t)( cmd & INT1_CTRL_INT1_OVR_MASK );
	myINT1->int1_fss5	 =	(LIS3DHH_int1_ctrl_int1_fss5_t)( cmd & INT1_CTRL_INT1_FSS5_MASK );
	myINT1->int1_fth	 =	(LIS3DHH_int1_ctrl_int1_fth_t)( cmd & INT1_CTRL_INT1_FTH_MASK );
	myINT1->int1_ext	 =	(LIS3DHH_int1_ctrl_int1_ext_t)( cmd & INT1_CTRL_INT1_EXT_MASK );




    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_SetINT2 ( spi_parameters_t , LIS3DHH_int2_data_t )
 *
 * @details     It sets the set of interrupts INT2 pin.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myINT2: 			Set of interrupts (INT2) on pin.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LIS3DHH_SetINT2.
 *
 *
 * @author      Manuel Caballero
 * @date        28/October/2020
 * @version     28/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_SetINT2 ( spi_parameters_t mySPI_parameters, LIS3DHH_int2_data_t myINT2 )
{
	uint8_t      cmd[2]   =    { 0U };
	spi_status_t mySPI_status;


	/* Update the register	 */
	cmd[0]		 =	 ( LIS3DHH_WRITE & LIS3DHH_INT2_CTRL );
	cmd[1]		 =	 ( myINT2.int2_drdy | myINT2.int2_boot | myINT2.int2_ovr | myINT2.int2_fss5 | myINT2.int2_fth );
    mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_GetINT2 ( spi_parameters_t , LIS3DHH_int2_data_t* )
 *
 * @details     It gets the configuration of the set of interrupts INT1 pin.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myINT2: 			Set of interrupts (INT2) on pin..
 *
 *
 * @return       Status of LIS3DHH_GetINT2.
 *
 *
 * @author      Manuel Caballero
 * @date        28/October/2020
 * @version     28/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetINT2 ( spi_parameters_t mySPI_parameters, LIS3DHH_int2_data_t* myINT2 )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_INT2_CTRL );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 1U );

	/* Parse the data	 */
	myINT2->int2_drdy	 =	(LIS3DHH_int2_ctrl_int2_drdy_t)( cmd & INT2_CTRL_INT2_DRDY_MASK );
	myINT2->int2_boot	 =	(LIS3DHH_int2_ctrl_int2_boot_t)( cmd & INT2_CTRL_INT2_BOOT_MASK );
	myINT2->int2_ovr	 =	(LIS3DHH_int2_ctrl_int2_ovr_t)( cmd & INT2_CTRL_INT2_OVR_MASK );
	myINT2->int2_fss5	 =	(LIS3DHH_int2_ctrl_int2_fss5_t)( cmd & INT2_CTRL_INT2_FSS5_MASK );
	myINT2->int2_fth	 =	(LIS3DHH_int2_ctrl_int2_fth_t)( cmd & INT2_CTRL_INT2_FTH_MASK );




    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_SetDigitalFilter ( spi_parameters_t , LIS3DHH_ctr_reg4_dsp_lp_type_t )
 *
 * @details     It sets the digital filter.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myDSP_LP_TYPE: 	Digital filtering selection: CTRL_REG4_DSP_LP_TYPE_FIR_LINEAR_PHASE/CTRL_REG4_DSP_LP_TYPE_IIR_NONLINEAR_PHASE.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LIS3DHH_SetDigitalFilter.
 *
 *
 * @author      Manuel Caballero
 * @date        29/October/2020
 * @version     29/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_SetDigitalFilter ( spi_parameters_t mySPI_parameters, LIS3DHH_ctr_reg4_dsp_lp_type_t myDSP_LP_TYPE )
{
	uint8_t      cmd[2]   =    { 0U };
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd[0]		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG4 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], 1U, &cmd[1], 1U );

	/* Mask the data and update the register	 */
	cmd[0]		 =	 ( LIS3DHH_WRITE & LIS3DHH_CTRL_REG4 );
	cmd[1]		 =	 ( ( cmd[1] & CTRL_REG4_DSP_LP_TYPE_MASK ) | myDSP_LP_TYPE ) | 0x01;
    mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_GetDigitalFilter ( spi_parameters_t , LIS3DHH_ctr_reg4_dsp_lp_type_t* )
 *
 * @details     It gets the digital filtering selection.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myDSP_LP_TYPE: 	Digital filtering selection: CTRL_REG4_DSP_LP_TYPE_FIR_LINEAR_PHASE/CTRL_REG4_DSP_LP_TYPE_IIR_NONLINEAR_PHASE.
 *
 *
 * @return       Status of LIS3DHH_GetDigitalFilter.
 *
 *
 * @author      Manuel Caballero
 * @date        29/October/2020
 * @version     29/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetDigitalFilter ( spi_parameters_t mySPI_parameters, LIS3DHH_ctr_reg4_dsp_lp_type_t* myDSP_LP_TYPE )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG4 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 1U );

	/* Mask and parse the data	 */
	*myDSP_LP_TYPE	 =	(LIS3DHH_ctr_reg4_dsp_lp_type_t)( cmd & CTRL_REG4_DSP_LP_TYPE_MASK );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_SetUserBandwidth ( spi_parameters_t , LIS3DHH_ctr_reg4_dsp_bw_sel_t )
 *
 * @details     It sets the user-selectable bandwidth.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myDSP_BW_SEL: 		User-selectable bandwidth: CTRL_REG4_DSP_BW_SEL_440_HZ_TYP/CTRL_REG4_DSP_BW_SEL_235_HZ_TYP.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LIS3DHH_SetUserBandwidth.
 *
 *
 * @author      Manuel Caballero
 * @date        29/October/2020
 * @version     29/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_SetUserBandwidth ( spi_parameters_t mySPI_parameters, LIS3DHH_ctr_reg4_dsp_bw_sel_t myDSP_BW_SEL )
{
	uint8_t      cmd[2]   =    { 0U };
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd[0]		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG4 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], 1U, &cmd[1], 1U );

	/* Mask the data and update the register	 */
	cmd[0]		 =	 ( LIS3DHH_WRITE & LIS3DHH_CTRL_REG4 );
	cmd[1]		 =	 ( ( cmd[1] & CTRL_REG4_DSP_BW_SEL_MASK ) | myDSP_BW_SEL ) | 0x01;
    mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_GetUserBandwidth ( spi_parameters_t , LIS3DHH_ctr_reg4_dsp_bw_sel_t* )
 *
 * @details     It gets the user-selectable bandwidth.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myDSP_BW_SEL: 		User-selectable bandwidth: CTRL_REG4_DSP_BW_SEL_440_HZ_TYP/CTRL_REG4_DSP_BW_SEL_235_HZ_TYP.
 *
 *
 * @return       Status of LIS3DHH_GetUserBandwidth.
 *
 *
 * @author      Manuel Caballero
 * @date        29/October/2020
 * @version     29/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetUserBandwidth ( spi_parameters_t mySPI_parameters, LIS3DHH_ctr_reg4_dsp_bw_sel_t* myDSP_BW_SEL )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG4 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 1U );

	/* Mask and parse the data	 */
	*myDSP_BW_SEL	 =	(LIS3DHH_ctr_reg4_dsp_bw_sel_t)( cmd & CTRL_REG4_DSP_BW_SEL_MASK );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_SetSelfTest ( spi_parameters_t , LIS3DHH_ctr_reg4_st_t )
 *
 * @details     It sets the user-selectable bandwidth.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myST: 				Self-test enable: CTRL_REG4_ST_NORMAL_MODE/CTRL_REG4_ST_POSITIVE_SIGN_SELFTEST/CTRL_REG4_ST_NEGATIVE_SIGN_SELFTEST.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LIS3DHH_SetSelfTest.
 *
 *
 * @author      Manuel Caballero
 * @date        29/October/2020
 * @version     29/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_SetSelfTest ( spi_parameters_t mySPI_parameters, LIS3DHH_ctr_reg4_st_t myST	 )
{
	uint8_t      cmd[2]   =    { 0U };
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd[0]		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG4 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], 1U, &cmd[1], 1U );

	/* Mask the data and update the register	 */
	cmd[0]		 =	 ( LIS3DHH_WRITE & LIS3DHH_CTRL_REG4 );
	cmd[1]		 =	 ( ( cmd[1] & CTRL_REG4_ST_MASK ) | myST ) | 0x01;
    mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_GetSelfTest ( spi_parameters_t , LIS3DHH_ctr_reg4_st_t* )
 *
 * @details     It gets the self-test functionality.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myST: 				Self-test enable: CTRL_REG4_ST_NORMAL_MODE/CTRL_REG4_ST_POSITIVE_SIGN_SELFTEST/CTRL_REG4_ST_NEGATIVE_SIGN_SELFTEST.
 *
 *
 * @return       Status of LIS3DHH_GetSelfTest.
 *
 *
 * @author      Manuel Caballero
 * @date        29/October/2020
 * @version     29/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetSelfTest ( spi_parameters_t mySPI_parameters, LIS3DHH_ctr_reg4_st_t* myST )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG4 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 1U );

	/* Mask and parse the data	 */
	*myST	 =	(LIS3DHH_ctr_reg4_st_t)( cmd & CTRL_REG4_ST_MASK );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_SetINT2_PinMode ( spi_parameters_t , LIS3DHH_ctr_reg4_pp_od_int2_t )
 *
 * @details     It sets the Push-pull/open drain selection on INT2 pin.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myPP_OD_INT2: 		Push-pull/open drain selection on INT2 pin: CTRL_REG4_PP_OD_INT2_PUSH_PULL_MODE/CTRL_REG4_PP_OD_INT2_OPEM_DRAIN_MODE.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LIS3DHH_SetINT2_PinMode.
 *
 *
 * @author      Manuel Caballero
 * @date        29/October/2020
 * @version     29/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_SetINT2_PinMode ( spi_parameters_t mySPI_parameters, LIS3DHH_ctr_reg4_pp_od_int2_t myPP_OD_INT2 )
{
	uint8_t      cmd[2]   =    { 0U };
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd[0]		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG4 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], 1U, &cmd[1], 1U );

	/* Mask the data and update the register	 */
	cmd[0]		 =	 ( LIS3DHH_WRITE & LIS3DHH_CTRL_REG4 );
	cmd[1]		 =	 ( ( cmd[1] & CTRL_REG4_PP_OD_INT2_MASK ) | myPP_OD_INT2 ) | 0x01;
    mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_GetINT2_PinMode ( spi_parameters_t , LIS3DHH_ctr_reg4_pp_od_int2_t* )
 *
 * @details     It gets the Push-pull/open drain selection on INT2 pin.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myPP_OD_INT2: 		Push-pull/open drain selection on INT2 pin: CTRL_REG4_PP_OD_INT2_PUSH_PULL_MODE/CTRL_REG4_PP_OD_INT2_OPEM_DRAIN_MODE.
 *
 *
 * @return       Status of LIS3DHH_GetINT2_PinMode.
 *
 *
 * @author      Manuel Caballero
 * @date        29/October/2020
 * @version     29/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetINT2_PinMode ( spi_parameters_t mySPI_parameters, LIS3DHH_ctr_reg4_pp_od_int2_t* myPP_OD_INT2 )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG4 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 1U );

	/* Mask and parse the data	 */
	*myPP_OD_INT2	 =	(LIS3DHH_ctr_reg4_pp_od_int2_t)( cmd & CTRL_REG4_PP_OD_INT2_MASK );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_SetINT1_PinMode ( spi_parameters_t , LIS3DHH_ctr_reg4_pp_od_int1_t )
 *
 * @details     It sets the Push-pull/open drain selection on INT2 pin.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myPP_OD_INT1: 		Push-pull/open drain selection on INT1 pin: CTRL_REG4_PP_OD_INT1_PUSH_PULL_MODE/CTRL_REG4_PP_OD_INT1_OPEM_DRAIN_MODE.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LIS3DHH_SetINT1_PinMode.
 *
 *
 * @author      Manuel Caballero
 * @date        29/October/2020
 * @version     29/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_SetINT1_PinMode ( spi_parameters_t mySPI_parameters, LIS3DHH_ctr_reg4_pp_od_int1_t myPP_OD_INT1 )
{
	uint8_t      cmd[2]   =    { 0U };
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd[0]		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG4 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], 1U, &cmd[1], 1U );

	/* Mask the data and update the register	 */
	cmd[0]		 =	 ( LIS3DHH_WRITE & LIS3DHH_CTRL_REG4 );
	cmd[1]		 =	 ( ( cmd[1] & CTRL_REG4_PP_OD_INT1_MASK ) | myPP_OD_INT1 ) | 0x01;
    mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_GetINT1_PinMode ( spi_parameters_t , LIS3DHH_ctr_reg4_pp_od_int1_t* )
 *
 * @details     It gets the Push-pull/open drain selection on INT1 pin.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myPP_OD_INT1: 		Push-pull/open drain selection on INT1 pin: CTRL_REG4_PP_OD_INT1_PUSH_PULL_MODE/CTRL_REG4_PP_OD_INT1_OPEM_DRAIN_MODE.
 *
 *
 * @return       Status of LIS3DHH_GetINT1_PinMode.
 *
 *
 * @author      Manuel Caballero
 * @date        29/October/2020
 * @version     29/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetINT1_PinMode ( spi_parameters_t mySPI_parameters, LIS3DHH_ctr_reg4_pp_od_int1_t* myPP_OD_INT1 )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG4 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 1U );

	/* Mask and parse the data	 */
	*myPP_OD_INT1	 =	(LIS3DHH_ctr_reg4_pp_od_int1_t)( cmd & CTRL_REG4_PP_OD_INT1_MASK );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_SetFIFO_MemoryEnable ( spi_parameters_t , LIS3DHH_ctr_reg4_fifo_en_t )
 *
 * @details     It sets the FIFO memory enable.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myFIFO_EN: 		FIFO memory enable: CTRL_REG4_FIFO_EN_DISABLED/CTRL_REG4_FIFO_EN_ENABLED.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LIS3DHH_SetFIFO_MemoryEnable.
 *
 *
 * @author      Manuel Caballero
 * @date        29/October/2020
 * @version     29/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_SetFIFO_MemoryEnable ( spi_parameters_t mySPI_parameters, LIS3DHH_ctr_reg4_fifo_en_t myFIFO_EN )
{
	uint8_t      cmd[2]   =    { 0U };
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd[0]		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG4 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], 1U, &cmd[1], 1U );

	/* Mask the data and update the register	 */
	cmd[0]		 =	 ( LIS3DHH_WRITE & LIS3DHH_CTRL_REG4 );
	cmd[1]		 =	 ( ( cmd[1] & CTRL_REG4_FIFO_EN_MASK ) | myFIFO_EN ) | 0x01;
    mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_GetFIFO_MemoryEnable ( spi_parameters_t , LIS3DHH_ctr_reg4_fifo_en_t* )
 *
 * @details     It gets the FIFO memory enable.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myFIFO_EN: 		FIFO memory enable: CTRL_REG4_FIFO_EN_DISABLED/CTRL_REG4_FIFO_EN_ENABLED.
 *
 *
 * @return       Status of LIS3DHH_GetFIFO_MemoryEnable.
 *
 *
 * @author      Manuel Caballero
 * @date        29/October/2020
 * @version     29/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetFIFO_MemoryEnable ( spi_parameters_t mySPI_parameters, LIS3DHH_ctr_reg4_fifo_en_t* myFIFO_EN )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG4 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 1U );

	/* Mask and parse the data	 */
	*myFIFO_EN	 =	(LIS3DHH_ctr_reg4_fifo_en_t)( cmd & CTRL_REG4_FIFO_EN_MASK );



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_GetRawTemperature ( spi_parameters_t , LIS3DHH_out_temp_data_t* )
 *
 * @details     It gets the raw temperature data output.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myRawTemperature: 	Raw temperature value.
 *
 *
 * @return       Status of LIS3DHH_GetRawTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        30/October/2020
 * @version     30/October/2020   The ORIGIN
 * @pre         This function doesn't consider the register auto increment mode.
 * @warning     This function returns the data shifted thus, the temperature is ready ( Temp<11:0> ).
 */
LIS3DHH_status_t  LIS3DHH_GetRawTemperature	( spi_parameters_t mySPI_parameters, LIS3DHH_out_temp_data_t* myRawTemperature )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_OUT_TEMP_H );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 1U );

	/* Mask and parse the data	 */
	myRawTemperature->raw_temperature	 =	 cmd;
	myRawTemperature->raw_temperature  <<=	 8U;

	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_OUT_TEMP_L );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 1U );

	/* Mask and parse the data	 */
	myRawTemperature->raw_temperature	|=	cmd;

	/* Shift the bits	 */
	myRawTemperature->raw_temperature	>>=	 4U;



    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_GetTemperature ( spi_parameters_t , LIS3DHH_out_temp_data_t* )
 *
 * @details     It gets the current temperature data output in degree Celsius.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myTemperature: 	Temperature value in degree Celsius.
 *
 *
 * @return       Status of LIS3DHH_GetTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        30/October/2020
 * @version     30/October/2020   The ORIGIN
 * @pre         This function updates the raw_temperature variable too.
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetTemperature ( spi_parameters_t mySPI_parameters, LIS3DHH_out_temp_data_t* myTemperature )
{
	LIS3DHH_status_t aux;

	/* Get the raw temperature value	 */
	aux	 =	 LIS3DHH_GetRawTemperature	( mySPI_parameters, (LIS3DHH_out_temp_data_t*)&myTemperature );

	/* Calculate the current temperature value	 */
	myTemperature->temperature	 = (float)( ( myTemperature->raw_temperature / 16.0f ) + 25.0f );


    return   aux;
}



/**
 * @brief       LIS3DHH_GetStatusRegister ( spi_parameters_t , LIS3DHH_out_temp_data_t* )
 *
 * @details     It gets the status register.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myStatus: 			The whole status register value.
 *
 *
 * @return       Status of LIS3DHH_GetStatusRegister.
 *
 *
 * @author      Manuel Caballero
 * @date        03/November/2020
 * @version     03/November/2020   The ORIGIN
 * @pre         The returned value must be masked.
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetStatusRegister ( spi_parameters_t mySPI_parameters, uint8_t* myStatus )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_STATUS );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, (uint8_t*)&myStatus, 1U );




    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_GetRawAcceleration ( spi_parameters_t , LIS3DHH_raw_out_data_t* )
 *
 * @details     It gets the raw Linear acceleration sensor X/Y/Z-axis outputs.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myRawAcceleration: It gets the raw data from all the axis ( X/Y/Z-axis ).
 *
 *
 * @return       Status of LIS3DHH_GetRawAcceleration.
 *
 *
 * @author      Manuel Caballero
 * @date        05/November/2020
 * @version     05/November/2020   The ORIGIN
 * @pre         N/A.
 * @warning     This function takes for granted that auto-increment functionality is enabled.
 */
LIS3DHH_status_t  LIS3DHH_GetRawAcceleration ( spi_parameters_t mySPI_parameters, LIS3DHH_raw_out_data_t* myRawAcceleration )
{
	uint8_t      cmd[6]   =    { 0U };
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd[0]		 =	 ( LIS3DHH_READ & LIS3DHH_OUT_X_L_XL );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd[0], 1U, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

	/* Parse the data	 */
	myRawAcceleration->out_x	 =	 cmd[1];
	myRawAcceleration->out_x   <<=	 8U;
	myRawAcceleration->out_x	|=	 cmd[0];

	myRawAcceleration->out_y	 =	 cmd[3];
	myRawAcceleration->out_y   <<=	 8U;
	myRawAcceleration->out_y	|=	 cmd[2];

	myRawAcceleration->out_z	 =	 cmd[5];
	myRawAcceleration->out_z   <<=	 8U;
	myRawAcceleration->out_z	|=	 cmd[4];




    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}

