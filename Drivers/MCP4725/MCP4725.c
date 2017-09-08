/**
 * @brief       MCP4725.c
 * @details     12-Bit Digital-to-Analog Converter with EEPROM Memory.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        7/September/2017
 * @version     7/September/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

 #include "MCP4725.h"


/**
 * @brief       MCP4725_Reset   ( NRF_TWI_Type* )
 *
 * @details     It performs an internal reset similar to a
 *              power-on-reset ( POR ).
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of MCP4725_Reset.
 *
 *
 * @author      Manuel Caballero
 * @date        7/September/2017
 * @version     7/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     The user MUST respect the time it takes this instruction to be
 *              performed ( max. 50ms ).
 */
MCP4725_status_t  MCP4725_Reset   ( NRF_TWI_Type* myinstance )
{
    uint8_t     cmd                 =    MCP4725_GENERAL_CALL_RESET;
    uint32_t    aux                 =    0;


    aux = i2c_write ( myinstance, MCP4725_GENERAL_CALL, &cmd, 1, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   MCP4725_SUCCESS;
    else
       return   MCP4725_FAILURE;
}



/**
 * @brief       MCP4725_WakeUp   ( NRF_TWI_Type* )
 *
 * @details     The power-down bits of the DAC register are set to a normal operation.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of MCP4725_WakeUp.
 *
 *
 * @author      Manuel Caballero
 * @date        7/September/2017
 * @version     7/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
MCP4725_status_t  MCP4725_WakeUp   ( NRF_TWI_Type* myinstance )
{
    uint8_t     cmd                 =    MCP4725_GENERAL_CALL_WAKE_UP;
    uint32_t    aux                 =    0;


    aux = i2c_write ( myinstance, MCP4725_GENERAL_CALL, &cmd, 1, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   MCP4725_SUCCESS;
    else
       return   MCP4725_FAILURE;
}


/**
 * @brief       MCP4725_PowerMode ( NRF_TWI_Type* , MCP4725_address_t , MCP4725_write_command_type_t , MCP4725_operation_mode_t )
 *
 * @details     It configures the power mode of the device.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myWriteCMD:            It writes the command into the DAC or EEPROM/DAC.
 * @param[in]    myPowerMode:           Normal Mode or one of the Power-Down available modes.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of MCP4725_PowerMode.
 *
 *
 * @author      Manuel Caballero
 * @date        7/September/2017
 * @version     7/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
MCP4725_status_t  MCP4725_PowerMode ( NRF_TWI_Type* myinstance, MCP4725_address_t ADDR, MCP4725_write_command_type_t myWriteCMD, MCP4725_operation_mode_t myPowerMode )
{
    uint8_t     cmd[]             =    { 0, 0, 0, 0, 0, 0 };
    uint32_t    aux               =    0;
    uint32_t    dataTX            =    3;


    // Read the device to mask the default value
    aux = i2c_read ( myinstance, ADDR, &cmd[0], 5 );



    // Choose the power mode
    switch ( myPowerMode ){
        default:
        case NORMAL_MODE:
                cmd[0]   =  0;
                break;

        case POWER_DOWN_1KOHM_RESISTIVE_LOAD_MODE:
                cmd[0]   =  0x01;
                break;

        case POWER_DOWN_100KOHM_RESISTIVE_LOAD_MODE:
                cmd[0]   =  0x02;
                break;

        case POWER_DOWN_500KOHM_RESISTIVE_LOAD_MODE:
                cmd[0]   =  0x03;
                break;
    }


    // Prepare the data according to the write mode
    switch ( myWriteCMD ){
        default:
        case FAST_MODE:
                cmd[0] <<=  4;
                cmd[0]  |=  ( ( cmd[1] & 0xF0 ) >> 4 );
                cmd[1]   =  ( ( cmd[1] & 0x0F ) << 4 );
                cmd[1]  |=  ( ( cmd[2] & 0xF0 ) >> 4 );

                dataTX   =   2;
                break;

        case WRITE_DAC_REGISTER_MODE:
                cmd[0] <<=  1;
                cmd[0]  |=  0x40;
                break;

        case WRITE_DAC_AND_EEPROM_REGISTER_MODE:
                cmd[0] <<=  1;
                cmd[0]  |=  0x60;
                break;
    }



    aux = i2c_write ( myinstance, ADDR, &cmd[0], dataTX, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   MCP4725_SUCCESS;
    else
       return   MCP4725_FAILURE;
}



/**
 * @brief       MCP4725_SetNewValue ( NRF_TWI_Type* , MCP4725_address_t , MCP4725_write_command_type_t , Vector_new_dac_value_t )
 *
 * @details     It sends a new output value.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myWriteCMD:            It writes the command into the DAC or EEPROM/DAC.
 * @param[in]    myDACNewValue:         New output value.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of MCP4725_SetNewValue.
 *
 *
 * @author      Manuel Caballero
 * @date        7/September/2017
 * @version     7/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
MCP4725_status_t  MCP4725_SetNewValue   ( NRF_TWI_Type* myinstance, MCP4725_address_t ADDR, MCP4725_write_command_type_t myWriteCMD, Vector_new_dac_value_t myDACNewValue )
{
    uint8_t     cmd[]             =    { 0, 0, 0 };
    uint32_t    aux               =    0;
    uint32_t    dataTX            =    3;


    // 12-Bit of resolution ONLY!
    if ( myDACNewValue.DAC_New_Value > 4095 )
        return  MCP4725_FAILURE;


    // Prepare the data according to the write mode
    cmd[1]  |=  ( ( myDACNewValue.DAC_New_Value & 0xFF0 ) >> 4 );
    cmd[2]  |=  ( ( myDACNewValue.DAC_New_Value & 0x00F ) << 4 );

    switch ( myWriteCMD ){
        default:
        case FAST_MODE:
                cmd[0]  |=  ( ( myDACNewValue.DAC_New_Value & 0xF00 ) >> 8 );
                cmd[1]   =  ( myDACNewValue.DAC_New_Value & 0x0FF );

                dataTX   =   2;
                break;

        case WRITE_DAC_REGISTER_MODE:
                cmd[0]  |=  0x40;
                break;

        case WRITE_DAC_AND_EEPROM_REGISTER_MODE:
                cmd[0]  |=  0x60;
                break;
    }



    aux = i2c_write ( myinstance, ADDR, &cmd[0], dataTX, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
       return   MCP4725_SUCCESS;
    else
       return   MCP4725_FAILURE;
}



/**
 * @brief       MCP4725_EEPROM_Status ( NRF_TWI_Type* , MCP4725_address_t , MCP4725_eeprom_status_t )
 *
 * @details     It gets the eeprom status.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myEEPROM_Status:       EEPROM status.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of MCP4725_EEPROM_Status.
 *
 *
 * @author      Manuel Caballero
 * @date        7/September/2017
 * @version     7/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
MCP4725_status_t  MCP4725_EEPROM_Status ( NRF_TWI_Type* myinstance, MCP4725_address_t ADDR, MCP4725_eeprom_status_t* myEEPROM_Status )
{
    uint8_t     cmd[]             =    { 0, 0, 0, 0, 0 };
    uint32_t    aux               =    0;

    // Read command
    aux = i2c_read ( myinstance, ADDR, &cmd[0], 5 );

    // Update EEPROM status
    *myEEPROM_Status =   ( ( cmd[0] & 0x80 ) >> 7 );



    if ( aux == I2C_SUCCESS )
       return   MCP4725_SUCCESS;
    else
       return   MCP4725_FAILURE;
}



/**
 * @brief       MCP4725_GetEEPROM_Data ( NRF_TWI_Type* , MCP4725_address_t , Vector_data_t* )
 *
 * @details     It gets the eeprom value.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myEEPROMData:          EEPROM value.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of MCP4725_GetEEPROM_Data.
 *
 *
 * @author      Manuel Caballero
 * @date        8/September/2017
 * @version     8/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
MCP4725_status_t  MCP4725_GetEEPROM_Data    ( NRF_TWI_Type* myinstance, MCP4725_address_t ADDR, Vector_data_t* myEEPROMData )
{
    uint8_t     cmd[]             =    { 0, 0, 0, 0, 0 };
    uint32_t    aux               =    0;

    // Read command
    aux = i2c_read ( myinstance, ADDR, &cmd[0], 5 );

    // Read EEPROM value
    myEEPROMData->EEPROM_Data =   ( ( cmd[3] & 0x0F ) << 8 ) | ( cmd[4] );



    if ( aux == I2C_SUCCESS )
       return   MCP4725_SUCCESS;
    else
       return   MCP4725_FAILURE;
}



/**
 * @brief       MCP4725_GetDAC_Data ( NRF_TWI_Type* , MCP4725_address_t , Vector_data_t* )
 *
 * @details     It gets the DAC value.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    ADDR:                  I2C Device's address.
 * @param[in]    myDACData:             DAC value.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of MCP4725_GetDAC_Data.
 *
 *
 * @author      Manuel Caballero
 * @date        8/September/2017
 * @version     8/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
MCP4725_status_t  MCP4725_GetDAC_Data    ( NRF_TWI_Type* myinstance, MCP4725_address_t ADDR, Vector_data_t* myDACData )
{
    uint8_t     cmd[]             =    { 0, 0, 0, 0, 0 };
    uint32_t    aux               =    0;

    // Read command
    aux = i2c_read ( myinstance, ADDR, &cmd[0], 5 );

    // Read DAC value
    myDACData->DAC_Data =   ( ( cmd[1] & 0xF0 ) << 4 ) | ( ( ( ( cmd[1] & 0x0F ) >> 4 ) | ( cmd[2] & 0xF0 ) >> 4 ) );



    if ( aux == I2C_SUCCESS )
       return   MCP4725_SUCCESS;
    else
       return   MCP4725_FAILURE;
}
