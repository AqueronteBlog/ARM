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
 * @version     20/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetPowerMode	( spi_parameters_t mySPI_parameters, LIS3DHH_ctrl_reg1_norm_mod_en_t* myPowerMode )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG1 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, (uint8_t*)(&myPowerMode), 1U );




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
 * @version     28/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetRegisterAutoIncrement ( spi_parameters_t mySPI_parameters, LIS3DHH_ctrl_reg1_if_add_inc_t* myIF_ADD_INC )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG1 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, (uint8_t*)(&myIF_ADD_INC), 1U );




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
 * @version     28/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetRebootMemoryContent ( spi_parameters_t mySPI_parameters, LIS3DHH_ctrl_reg1_boot_t* myBoot )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG1 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, (uint8_t*)(&myBoot), 1U );




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
 * @version     28/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetSoftwareResetStatus ( spi_parameters_t mySPI_parameters, LIS3DHH_ctrl_reg1_sw_reset_t* mySW_Reset )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG1 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, (uint8_t*)(&mySW_Reset), 1U );




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
 * @version     28/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetDataReadyOnINT1 ( spi_parameters_t mySPI_parameters, LIS3DHH_ctrl_reg1_drdy_pulse_t* myDRDY_PULSE )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG1 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, (uint8_t*)(&myDRDY_PULSE), 1U );




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
 * @version     28/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetBlockDataUpdate ( spi_parameters_t mySPI_parameters, LIS3DHH_ctrl_reg1_bdu_t* myBDU )
{
	uint8_t      cmd   =    0U;
	spi_status_t mySPI_status;


	/* Read the register	 */
	cmd		 =	 ( LIS3DHH_READ & LIS3DHH_CTRL_REG1 );
	mySPI_status =   spi_transfer ( mySPI_parameters, &cmd, 1U, (uint8_t*)(&myBDU), 1U );




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
