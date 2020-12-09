/**
 * @brief       ezPyro_SMD_Sensor.c
 * @details     [todo]ezPyro SMD I2C Pyroelectric Infrared Sensor. Single element or 2x2 array.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        13/October/2020
 * @version     13/October/2020    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */

#include "ezPyro_SMD_Sensor.h"


/**
 * @brief       EZPYRO_SMD_SENSOR_Init   ( I2C_parameters_t )
 *
 * @details     It configures the I2C pins.
 *
 * @param[in]    myI2C_parameters:  I2C instance
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of EZPYRO_SMD_SENSOR_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        13/October/2020
 * @version     13/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
EZPYRO_SMD_SENSOR_status_t EZPYRO_SMD_SENSOR_Init ( I2C_parameters_t myI2C_parameters )
{
    i2c_status_t myI2C_status;


    /* Configure the I2C peripheral	 */
    myI2C_status     =   i2c_init ( myI2C_parameters );




    if ( myI2C_status == I2C_SUCCESS )
    {
        return   EZPYRO_SMD_SENSOR_SUCCESS;
    }
    else
    {
        return   EZPYRO_SMD_SENSOR_FAILURE;
    }
}



/**
 * @brief       EZPYRO_SMD_SENSOR_SendCommand   ( I2C_parameters_t , EZPYRO_SMD_SENSOR_command_list_t , EZPYRO_SMD_SENSOR_commands_data_ok_err_t* )
 *
 * @details     It sends a command to the sensor.
 *
 * @param[in]    myI2C_parameters:  I2C instance.
 * @param[in]    myCommand:  		Command value.
 *
 * @param[out]   myCommandResponse:	Response from the sensor, OK/Err.
 *
 *
 * @return       Status of EZPYRO_SMD_SENSOR_SendCommand.
 *
 *
 * @author      Manuel Caballero
 * @date        04/December/2020
 * @version     04/December/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
EZPYRO_SMD_SENSOR_status_t EZPYRO_SMD_SENSOR_SendCommand ( I2C_parameters_t myI2C_parameters, EZPYRO_SMD_SENSOR_command_list_t myCommand, EZPYRO_SMD_SENSOR_commands_data_ok_err_t* myCommandResponse )
{
    i2c_status_t myI2C_status;

    /* Send the command	 */
    myI2C_status	 =	 i2c_write ( myI2C_parameters, &myCommand, 1U, I2C_NO_STOP_BIT );

    /* Get response from the sensor	 */
    myI2C_status	 =	 i2c_read ( myI2C_parameters, (uint8_t*)&myCommandResponse, 1U );



    if ( myI2C_status == I2C_SUCCESS )
    {
        return   EZPYRO_SMD_SENSOR_SUCCESS;
    }
    else
    {
        return   EZPYRO_SMD_SENSOR_FAILURE;
    }
}



/**
 * @brief       EZPYRO_SMD_SENSOR_GetVersionPacket   ( I2C_parameters_t , uint8_t* )
 *
 * @details     It gets the version packet.
 *
 * @param[in]    myI2C_parameters:  I2C instance.
 *
 * @param[out]   myVersionPacket:	Version packet.
 *
 *
 * @return       Status of EZPYRO_SMD_SENSOR_GetVersionPacket.
 *
 *
 * @author      Manuel Caballero
 * @date        04/December/2020
 * @version     04/December/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
EZPYRO_SMD_SENSOR_status_t EZPYRO_SMD_SENSOR_GetVersionPacket ( I2C_parameters_t myI2C_parameters, uint8_t* myVersionPacket )
{
	uint8_t		 cmd = 0U;
    i2c_status_t myI2C_status;

    /* Send data	 */
    cmd				 =	 EZPYRO_SMD_SENSOR_VERSION;
    myI2C_status	 =	 i2c_write ( myI2C_parameters, &cmd, 1U, I2C_NO_STOP_BIT );

    /* Get data	 */
    myI2C_status	 =	 i2c_read ( myI2C_parameters, (uint8_t*)&myVersionPacket, 1U );



    if ( myI2C_status == I2C_SUCCESS )
    {
        return   EZPYRO_SMD_SENSOR_SUCCESS;
    }
    else
    {
        return   EZPYRO_SMD_SENSOR_FAILURE;
    }
}



/**
 * @brief       EZPYRO_SMD_SENSOR_GetFIFO_StatusPacket   ( I2C_parameters_t , uint8_t* )
 *
 * @details     It gets the FIFO status packet ( whole register ).
 *
 * @param[in]    myI2C_parameters:  I2C instance.
 *
 * @param[out]   myFS:				FIFO status packet register.
 *
 *
 * @return       Status of EZPYRO_SMD_SENSOR_GetFIFO_StatusPacket.
 *
 *
 * @author      Manuel Caballero
 * @date        04/December/2020
 * @version     04/December/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
EZPYRO_SMD_SENSOR_status_t EZPYRO_SMD_SENSOR_GetFIFO_StatusPacket ( I2C_parameters_t myI2C_parameters, uint8_t* myFS )
{
	uint8_t		 cmd = 0U;
    i2c_status_t myI2C_status;

    /* Send data	 */
    cmd				 =	 EZPYRO_SMD_SENSOR_FIFO_STATUS;
    myI2C_status	 =	 i2c_write ( myI2C_parameters, &cmd, 1U, I2C_NO_STOP_BIT );

    /* Get data	 */
    myI2C_status	 =	 i2c_read ( myI2C_parameters, (uint8_t*)&myFS, 1U );



    if ( myI2C_status == I2C_SUCCESS )
    {
        return   EZPYRO_SMD_SENSOR_SUCCESS;
    }
    else
    {
        return   EZPYRO_SMD_SENSOR_FAILURE;
    }
}



/**
 * @brief       EZPYRO_SMD_SENSOR_GetNumberDataInFIFO   ( I2C_parameters_t , uint8_t* )
 *
 * @details     It gets the number of data packets available in the FIFO.
 *
 * @param[in]    myI2C_parameters:  I2C instance.
 *
 * @param[out]   myFIFO_count:		FIFO count.
 *
 *
 * @return       Status of EZPYRO_SMD_SENSOR_GetNumberDataInFIFO.
 *
 *
 * @author      Manuel Caballero
 * @date        04/December/2020
 * @version     04/December/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
EZPYRO_SMD_SENSOR_status_t EZPYRO_SMD_SENSOR_GetNumberDataInFIFO ( I2C_parameters_t myI2C_parameters, uint8_t* myFIFO_count )
{
	EZPYRO_SMD_SENSOR_status_t myEZPYRO_SMD_SENSOR_status;

    /* Send data	 */
	myEZPYRO_SMD_SENSOR_status	 =	 EZPYRO_SMD_SENSOR_GetFIFO_StatusPacket ( myI2C_parameters, (uint8_t*)&myFIFO_count );

    /* Parse the data	 */
    *myFIFO_count	&=	 FS_FIFO_COUNT_MASK;
    *myFIFO_count  >>=	 1U;


    return   myEZPYRO_SMD_SENSOR_status;
}



/**
 * @brief       EZPYRO_SMD_SENSOR_GetChannelControlPacket   ( I2C_parameters_t , EZPYRO_SMD_SENSOR_ccp_channel_t* )
 *
 * @details     It reads the channel control packet ( all the channels from channel 0 to channel 4 ).
 *
 * @param[in]    myI2C_parameters:  I2C instance.
 *
 * @param[out]   myCCP:				Channel control packet ( all the channels ).
 *
 *
 * @return       Status of EZPYRO_SMD_SENSOR_GetChannelControlPacket.
 *
 *
 * @author      Manuel Caballero
 * @date        04/December/2020
 * @version     04/December/2020   The ORIGIN
 * @pre         This function reads and updates the configuration for all the channels.
 * @warning     N/A.
 */
EZPYRO_SMD_SENSOR_status_t EZPYRO_SMD_SENSOR_GetChannelControlPacket ( I2C_parameters_t myI2C_parameters, EZPYRO_SMD_SENSOR_ccp_channel_t* myCCP	 )
{
	uint8_t		 cmd[5] = { 0U };
    i2c_status_t myI2C_status;

    /* Send data	 */
    cmd[0]			 =	 EZPYRO_SMD_SENSOR_CH_READ;
    myI2C_status	 =	 i2c_write ( myI2C_parameters, &cmd[0], 1U, I2C_NO_STOP_BIT );

    /* Get data	 */
    myI2C_status	 =	 i2c_read ( myI2C_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data	 */
    /* Channel 0	 */
    myCCP->ch0.cx_tc	 =	(EZPYRO_SMD_SENSOR_ccp_ch_tc_t)( cmd[0] & CCP_CH_TC_MASK );
    myCCP->ch0.cx_hp	 =	(EZPYRO_SMD_SENSOR_ccp_ch_hp_t)( cmd[0] & CCP_CH_HP_MASK );
    myCCP->ch0.cx_g		 =	(EZPYRO_SMD_SENSOR_ccp_ch_g_t)( cmd[0] & CCP_CH_G_MASK );
    myCCP->ch0.cx_st	 =	(EZPYRO_SMD_SENSOR_ccp_ch_st_t)( cmd[0] & CCP_CH_ST_MASK );

    /* Channel 1	*/
    myCCP->ch1.cx_tc	 =	(EZPYRO_SMD_SENSOR_ccp_ch_tc_t)( cmd[1] & CCP_CH_TC_MASK );
    myCCP->ch1.cx_hp	 =	(EZPYRO_SMD_SENSOR_ccp_ch_hp_t)( cmd[1] & CCP_CH_HP_MASK );
    myCCP->ch1.cx_g		 =	(EZPYRO_SMD_SENSOR_ccp_ch_g_t)( cmd[1] & CCP_CH_G_MASK );
    myCCP->ch1.cx_st	 =	(EZPYRO_SMD_SENSOR_ccp_ch_st_t)( cmd[1] & CCP_CH_ST_MASK );

    /* Channel 2	*/
    myCCP->ch2.cx_tc	 =	(EZPYRO_SMD_SENSOR_ccp_ch_tc_t)( cmd[2] & CCP_CH_TC_MASK );
    myCCP->ch2.cx_hp	 =	(EZPYRO_SMD_SENSOR_ccp_ch_hp_t)( cmd[2] & CCP_CH_HP_MASK );
    myCCP->ch2.cx_g		 =	(EZPYRO_SMD_SENSOR_ccp_ch_g_t)( cmd[2] & CCP_CH_G_MASK );
    myCCP->ch2.cx_st	 =	(EZPYRO_SMD_SENSOR_ccp_ch_st_t)( cmd[2] & CCP_CH_ST_MASK );

    /* Channel 3	*/
    myCCP->ch3.cx_tc	 =	(EZPYRO_SMD_SENSOR_ccp_ch_tc_t)( cmd[3] & CCP_CH_TC_MASK );
    myCCP->ch3.cx_hp	 =	(EZPYRO_SMD_SENSOR_ccp_ch_hp_t)( cmd[3] & CCP_CH_HP_MASK );
    myCCP->ch3.cx_g		 =	(EZPYRO_SMD_SENSOR_ccp_ch_g_t)( cmd[3] & CCP_CH_G_MASK );
    myCCP->ch3.cx_st	 =	(EZPYRO_SMD_SENSOR_ccp_ch_st_t)( cmd[3] & CCP_CH_ST_MASK );

    /* Channel 4	*/
    myCCP->ch4.cx_tc	 =	(EZPYRO_SMD_SENSOR_ccp_ch_tc_t)( cmd[4] & CCP_CH_TC_MASK );
    myCCP->ch4.cx_hp	 =	(EZPYRO_SMD_SENSOR_ccp_ch_hp_t)( cmd[4] & CCP_CH_HP_MASK );
    myCCP->ch4.cx_g		 =	(EZPYRO_SMD_SENSOR_ccp_ch_g_t)( cmd[4] & CCP_CH_G_MASK );
    myCCP->ch4.cx_st	 =	(EZPYRO_SMD_SENSOR_ccp_ch_st_t)( cmd[4] & CCP_CH_ST_MASK );



    if ( myI2C_status == I2C_SUCCESS )
    {
        return   EZPYRO_SMD_SENSOR_SUCCESS;
    }
    else
    {
        return   EZPYRO_SMD_SENSOR_FAILURE;
    }
}



/**
 * @brief       EZPYRO_SMD_SENSOR_SetChannelControlPacket   ( I2C_parameters_t , EZPYRO_SMD_SENSOR_ccp_channel_t )
 *
 * @details     It configures the channel control packet ( it can configure just one channel, two/three channels or all at the same time ).
 *
 * @param[in]    myI2C_parameters:  I2C instance.
 * @param[in]    myCCP:				Channel control packet.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of EZPYRO_SMD_SENSOR_SetChannelControlPacket.
 *
 *
 * @author      Manuel Caballero
 * @date        04/December/2020
 * @version     04/December/2020   The ORIGIN
 * @pre         When this register is modified (by the host) the current FIFO will be flushed automatically by the internal circuit.
 * @warning     Before using this function, the user MUST call the function: EZPYRO_SMD_SENSOR_GetChannelControlPacket in order to mask the values.
 */
EZPYRO_SMD_SENSOR_status_t EZPYRO_SMD_SENSOR_SetChannelControlPacket ( I2C_parameters_t myI2C_parameters, EZPYRO_SMD_SENSOR_ccp_channel_t myCCP	)
{
	uint8_t			cmd[6] = { 0U };
    i2c_status_t 	myI2C_status;

    /* Send data	 */
    cmd[0]			 =	 EZPYRO_SMD_SENSOR_CH_WRITE;
    cmd[1]			 =	 ( myCCP.ch0.cx_tc | myCCP.ch0.cx_hp | myCCP.ch0.cx_g | myCCP.ch0.cx_st );
    cmd[2]			 =	 ( myCCP.ch1.cx_tc | myCCP.ch1.cx_hp | myCCP.ch1.cx_g | myCCP.ch1.cx_st );
    cmd[3]			 =	 ( myCCP.ch2.cx_tc | myCCP.ch2.cx_hp | myCCP.ch2.cx_g | myCCP.ch2.cx_st );
    cmd[4]			 =	 ( myCCP.ch3.cx_tc | myCCP.ch3.cx_hp | myCCP.ch3.cx_g | myCCP.ch3.cx_st );
    cmd[5]			 =	 ( myCCP.ch4.cx_tc | myCCP.ch4.cx_hp | myCCP.ch4.cx_g | myCCP.ch4.cx_st );
    myI2C_status	 =	 i2c_write ( myI2C_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( myI2C_status == I2C_SUCCESS )
    {
        return   EZPYRO_SMD_SENSOR_SUCCESS;
    }
    else
    {
        return   EZPYRO_SMD_SENSOR_FAILURE;
    }
}



/**
 * @brief       EZPYRO_SMD_SENSOR_GetAnalogueFrontEndPacket   ( I2C_parameters_t , EZPYRO_SMD_SENSOR_afep_t* )
 *
 * @details     It reads the analogue front end packet register.
 *
 * @param[in]    myI2C_parameters:  I2C instance.
 *
 * @param[out]   myAFEP:			Analogue Front end package register.
 *
 *
 * @return       Status of EZPYRO_SMD_SENSOR_GetAnalogueFrontEndPacket.
 *
 *
 * @author      Manuel Caballero
 * @date        08/December/2020
 * @version     08/December/2020   The ORIGIN
 * @pre         This function reads and updates the configuration for the whole register.
 * @warning     N/A.
 */
EZPYRO_SMD_SENSOR_status_t EZPYRO_SMD_SENSOR_GetAnalogueFrontEndPacket	( I2C_parameters_t myI2C_parameters, EZPYRO_SMD_SENSOR_afep_t* myAFEP )
{
	uint8_t		 cmd[2] = { 0U };
    i2c_status_t myI2C_status;

    /* Send data	 */
    cmd[0]			 =	 EZPYRO_SMD_SENSOR_ANA_READ;
    myI2C_status	 =	 i2c_write ( myI2C_parameters, &cmd[0], 1U, I2C_NO_STOP_BIT );

    /* Get data	 */
    myI2C_status	 =	 i2c_read ( myI2C_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data	 */
    myAFEP->sampling_rate	 =	  cmd[0];

    myAFEP->lp	 			 =	(EZPYRO_SMD_SENSOR_afep_byte1_lp_t)( cmd[1] & AFEP_BYTE1_LP_MASK );
    myAFEP->hp				 =	(EZPYRO_SMD_SENSOR_afep_byte1_hp_t)( cmd[1] & AFEP_BYTE1_HP_MASK );
    myAFEP->c_lp			 =	(EZPYRO_SMD_SENSOR_afep_byte1_c_lp_t)( cmd[1] & AFEP_BYTE1_C_LP_MASK );
    myAFEP->clk_out			 =	(EZPYRO_SMD_SENSOR_afep_byte1_clk_out_t)( cmd[1] & AFEP_BYTE1_CLK_OUT_MASK );
    myAFEP->sync			 =	(EZPYRO_SMD_SENSOR_afep_byte1_sync_t)( cmd[1] & AFEP_BYTE1_SYNC_MASK );
    myAFEP->int_mode		 =	(EZPYRO_SMD_SENSOR_afep_byte1_int_t)( cmd[1] & AFEP_BYTE1_INT_MASK );



    if ( myI2C_status == I2C_SUCCESS )
    {
        return   EZPYRO_SMD_SENSOR_SUCCESS;
    }
    else
    {
        return   EZPYRO_SMD_SENSOR_FAILURE;
    }
}



/**
 * @brief       EZPYRO_SMD_SENSOR_SetAnalogueFrontEndPacket   ( I2C_parameters_t , EZPYRO_SMD_SENSOR_afep_t )
 *
 * @details     It sets the analogue front end packet register.
 *
 * @param[in]    myI2C_parameters:  I2C instance.
 * @param[in]    myAFEP:			Analogue Front end package register.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of EZPYRO_SMD_SENSOR_SetAnalogueFrontEndPacket.
 *
 *
 * @author      Manuel Caballero
 * @date        08/December/2020
 * @version     08/December/2020   The ORIGIN
 * @pre         N/A.
 * @warning     Before using this function, the user MUST call the function: EZPYRO_SMD_SENSOR_GetAnalogueFrontEndPacket in order to mask the values.
 */
EZPYRO_SMD_SENSOR_status_t EZPYRO_SMD_SENSOR_SetAnalogueFrontEndPacket ( I2C_parameters_t myI2C_parameters, EZPYRO_SMD_SENSOR_afep_t myAFEP	)
{
	uint8_t			cmd[3] = { 0U };
    i2c_status_t 	myI2C_status;

    /* Send data	 */
    cmd[0]			 =	 EZPYRO_SMD_SENSOR_ANA_WRITE;
    cmd[1]			 =	 myAFEP.sampling_rate;
    cmd[2]			 =	 ( myAFEP.lp | myAFEP.hp | myAFEP.c_lp | myAFEP.clk_out | myAFEP.sync | myAFEP.int_mode ) & 0xFD;
    myI2C_status	 =	 i2c_write ( myI2C_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( myI2C_status == I2C_SUCCESS )
    {
        return   EZPYRO_SMD_SENSOR_SUCCESS;
    }
    else
    {
        return   EZPYRO_SMD_SENSOR_FAILURE;
    }
}



/**
 * @brief       EZPYRO_SMD_SENSOR_SetI2C_AddressPacket   ( I2C_parameters_t , uint8_t )
 *
 * @details     It sets a new I2C address packet.
 *
 * @param[in]    myI2C_parameters:  I2C instance.
 * @param[in]    myI2CADD:			A new I2C address for the device.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of EZPYRO_SMD_SENSOR_SetI2C_AddressPacket.
 *
 *
 * @author      Manuel Caballero
 * @date        08/December/2020
 * @version     08/December/2020   The ORIGIN
 * @pre         This function shifts the I2C address to MSB to make reading easier with read/write bit.
 * @warning     N/A.
 */
EZPYRO_SMD_SENSOR_status_t EZPYRO_SMD_SENSOR_SetI2C_AddressPacket ( I2C_parameters_t myI2C_parameters, uint8_t myI2CADD )
{
	uint8_t		 cmd[2] = { 0U };
    i2c_status_t myI2C_status;

    /* Send data	 */
    cmd[0]			 =	 EZPYRO_SMD_SENSOR_ADDR_WRITE;
    cmd[1]			 =	 ( myI2CADD << 1U );
    myI2C_status	 =	 i2c_write ( myI2C_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( myI2C_status == I2C_SUCCESS )
    {
        return   EZPYRO_SMD_SENSOR_SUCCESS;
    }
    else
    {
        return   EZPYRO_SMD_SENSOR_FAILURE;
    }
}



/**
 * @brief       EZPYRO_SMD_SENSOR_GetWakeUpPacket   ( I2C_parameters_t , EZPYRO_SMD_SENSOR_wup_t* )
 *
 * @details     It reads the wake-up packet register.
 *
 * @param[in]    myI2C_parameters:  I2C instance.
 *
 * @param[out]   myWUP:				Wake-up packet register.
 *
 *
 * @return       Status of EZPYRO_SMD_SENSOR_GetWakeUpPacket.
 *
 *
 * @author      Manuel Caballero
 * @date        09/December/2020
 * @version     09/December/2020   The ORIGIN
 * @pre         This function reads and updates the configuration for the whole register.
 * @warning     N/A.
 */
EZPYRO_SMD_SENSOR_status_t EZPYRO_SMD_SENSOR_GetWakeUpPacket ( I2C_parameters_t myI2C_parameters, EZPYRO_SMD_SENSOR_wup_t* myWUP )
{
	uint8_t		 cmd[6] = { 0U };
    i2c_status_t myI2C_status;

    /* Send data	 */
    cmd[0]			 =	 EZPYRO_SMD_SENSOR_WAKE_READ;
    myI2C_status	 =	 i2c_write ( myI2C_parameters, &cmd[0], 1U, I2C_NO_STOP_BIT );

    /* Get data	 */
    myI2C_status	 =	 i2c_read ( myI2C_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data	 */
    myWUP->uht				 =	  cmd[0];
    myWUP->ult				 =	  cmd[1];

    myWUP->lht				 =	  cmd[2];
    myWUP->llt				 =	  cmd[3];

    myWUP->wt				 =	  cmd[4];

    myWUP->ch_settings.st	 =	 (EZPYRO_SMD_SENSOR_ch_setting_st_t)( cmd[5] & CH_SETTING_ST_MASK );
    myWUP->ch_settings.dp	 =	 (EZPYRO_SMD_SENSOR_ch_setting_dp_t)( cmd[5] & CH_SETTING_DP_MASK );
    myWUP->ch_settings.ch	 =	 (EZPYRO_SMD_SENSOR_ch_setting_ch_t)( cmd[5] & CH_SETTING_CH_MASK );



    if ( myI2C_status == I2C_SUCCESS )
    {
        return   EZPYRO_SMD_SENSOR_SUCCESS;
    }
    else
    {
        return   EZPYRO_SMD_SENSOR_FAILURE;
    }
}



/**
 * @brief       EZPYRO_SMD_SENSOR_SetWakeUpPacket   ( I2C_parameters_t , EZPYRO_SMD_SENSOR_wup_t )
 *
 * @details     It sets the wake-up packet register.
 *
 * @param[in]    myI2C_parameters:  I2C instance.
 * @param[in]    myWUP:				Wake-up packet register.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of EZPYRO_SMD_SENSOR_SetWakeUpPacket.
 *
 *
 * @author      Manuel Caballero
 * @date        09/December/2020
 * @version     09/December/2020   The ORIGIN
 * @pre         N/A.
 * @warning     Before using this function, the user MUST call the function: EZPYRO_SMD_SENSOR_GetWakeUpPacket in order to mask the values.
 */
EZPYRO_SMD_SENSOR_status_t EZPYRO_SMD_SENSOR_SetWakeUpPacket ( I2C_parameters_t myI2C_parameters, EZPYRO_SMD_SENSOR_wup_t myWUP )
{
	uint8_t			cmd[7] = { 0U };
    i2c_status_t 	myI2C_status;

    /* Send data	 */
    cmd[0]			 =	 EZPYRO_SMD_SENSOR_WAKE_WRITE;
    cmd[1]			 =	 myWUP.uht;
    cmd[2]			 =	 myWUP.ult;
    cmd[3]			 =	 myWUP.lht;
    cmd[4]			 =	 myWUP.llt;
    cmd[5]			 =	 myWUP.wt;
    cmd[6]			 =	 ( myWUP.ch_settings.st | myWUP.ch_settings.dp | myWUP.ch_settings.ch );
    myI2C_status	 =	 i2c_write ( myI2C_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( myI2C_status == I2C_SUCCESS )
    {
        return   EZPYRO_SMD_SENSOR_SUCCESS;
    }
    else
    {
        return   EZPYRO_SMD_SENSOR_FAILURE;
    }
}



/**
 * @brief       EZPYRO_SMD_SENSOR_GetFIFO_DataPacketFull   ( I2C_parameters_t , EZPYRO_SMD_SENSOR_fifo_dpf_t* )
 *
 * @details     It reads the FIFO data packet full register ( all the channels and the frame counter ).
 *
 * @param[in]    myI2C_parameters:  I2C instance.
 *
 * @param[out]   myFIFO_DPF:		FIFO data packet full register.
 *
 *
 * @return       Status of EZPYRO_SMD_SENSOR_GetFIFO_DataPacketFull.
 *
 *
 * @author      Manuel Caballero
 * @date        09/December/2020
 * @version     09/December/2020   The ORIGIN
 * @pre         This function reads and updates the configuration for the whole register.
 * @warning     N/A.
 */
EZPYRO_SMD_SENSOR_status_t EZPYRO_SMD_SENSOR_GetFIFO_DataPacketFull	( I2C_parameters_t myI2C_parameters, EZPYRO_SMD_SENSOR_fifo_dpf_t* myFIFO_DPF )
{
	uint8_t		 cmd[17] = { 0U };
    i2c_status_t myI2C_status;

    /* Send data	 */
    cmd[0]			 =	 EZPYRO_SMD_SENSOR_FIFO_READ_FULL;
    myI2C_status	 =	 i2c_write ( myI2C_parameters, &cmd[0], 1U, I2C_NO_STOP_BIT );

    /* Get data	 */
    myI2C_status	 =	 i2c_read ( myI2C_parameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );

    /* Parse the data	 */
    myFIFO_DPF->ch0_data	   =	  cmd[0];
    myFIFO_DPF->ch0_data     <<=	  8U;
    myFIFO_DPF->ch0_data	  |=	  cmd[1];
    myFIFO_DPF->ch0_data     <<=	  8U;
    myFIFO_DPF->ch0_data	  |=	  cmd[2];

    myFIFO_DPF->ch1_data	   =	  cmd[3];
    myFIFO_DPF->ch1_data     <<=	  8U;
    myFIFO_DPF->ch1_data	  |=	  cmd[4];
    myFIFO_DPF->ch1_data     <<=	  8U;
    myFIFO_DPF->ch1_data	  |=	  cmd[5];

    myFIFO_DPF->ch2_data	   =	  cmd[6];
    myFIFO_DPF->ch2_data     <<=	  8U;
    myFIFO_DPF->ch2_data	  |=	  cmd[7];
    myFIFO_DPF->ch2_data     <<=	  8U;
    myFIFO_DPF->ch2_data	  |=	  cmd[8];

    myFIFO_DPF->ch3_data	   =	  cmd[9];
    myFIFO_DPF->ch3_data     <<=	  8U;
    myFIFO_DPF->ch3_data	  |=	  cmd[10];
    myFIFO_DPF->ch3_data     <<=	  8U;
    myFIFO_DPF->ch3_data	  |=	  cmd[11];

    myFIFO_DPF->ch4_data	   =	  cmd[12];
    myFIFO_DPF->ch4_data     <<=	  8U;
    myFIFO_DPF->ch4_data	  |=	  cmd[13];
    myFIFO_DPF->ch4_data     <<=	  8U;
    myFIFO_DPF->ch4_data	  |=	  cmd[14];

    myFIFO_DPF->frame_count	   =	  cmd[15];
    myFIFO_DPF->frame_count	 <<=	  8U;
    myFIFO_DPF->frame_count	  |=	  cmd[16];




    if ( myI2C_status == I2C_SUCCESS )
    {
    	if ( ( myFIFO_DPF->ch0_data & 0x800000 ) == 0x800000 )
    	{
    		return   EZPYRO_SMD_SENSOR_SUCCESS_CH0_OVER_RANGE;
    	}
    	else if ( ( myFIFO_DPF->ch1_data & 0x800000 ) == 0x800000 )
    	{
    		return   EZPYRO_SMD_SENSOR_SUCCESS_CH1_OVER_RANGE;
    	}
    	else if ( ( myFIFO_DPF->ch2_data & 0x800000 ) == 0x800000 )
    	{
    		return   EZPYRO_SMD_SENSOR_SUCCESS_CH2_OVER_RANGE;
    	}
    	else if ( ( myFIFO_DPF->ch3_data & 0x800000 ) == 0x800000 )
    	{
    		return   EZPYRO_SMD_SENSOR_SUCCESS_CH3_OVER_RANGE;
    	}
    	else if ( ( myFIFO_DPF->ch4_data & 0x800000 ) == 0x800000 )
    	{
    		return   EZPYRO_SMD_SENSOR_SUCCESS_CH4_OVER_RANGE;
    	}
    	else
    	{
    		return   EZPYRO_SMD_SENSOR_SUCCESS;
    	}
    }
    else
    {
        return   EZPYRO_SMD_SENSOR_FAILURE;
    }
}
