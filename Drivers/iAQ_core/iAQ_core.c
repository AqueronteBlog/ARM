/**
 * @brief       iAQ_Core.h
 * @details     Indoor air quality module, I2C interface.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        31/May/2018
 * @version     31/May/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "iAQ_Core.h"


/**
 * @brief       iAQ_Core_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of iAQ_Core_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        31/May/2018
 * @version     31/May/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
iAQ_Core_status_t  iAQ_Core_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
        return   iAQ_Core_SUCCESS;
    else
        return   iAQ_Core_FAILURE;
}



/**
 * @brief       iAQ_Core_StartConvertTemperature ( I2C_parameters_t )
 *
 * @details     It triggers a new temperature conversion.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of iAQ_Core_StartConvertTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        21/January/2018
 * @version     21/January/2018     The ORIGIN
 * @pre         Temperature Conversion Time ( t_TC ) 200ms maximum.
 * @warning     N/A.
 */
iAQ_Core_status_t  iAQ_Core_StartConvertTemperature ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd       =   iAQ_Core_START_CONVERT_T;
    i2c_status_t aux       =   0;


    // It triggers a new temperature conversion
    aux = i2c_write ( myI2Cparameters, &cmd, 1, I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
        return   iAQ_Core_SUCCESS;
    else
        return   iAQ_Core_FAILURE;
}


/**
 * @brief       iAQ_Core_StopConvertTemperature ( I2C_parameters_t )
 *
 * @details     It halts the temperature conversion.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of iAQ_Core_StopConvertTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        21/January/2018
 * @version     21/January/2018     The ORIGIN
 * @pre         In continuous conversion mode, a StopConvertT command halt
 *              a continuous conversion. To restart, the StartConvertT
 *              command must be issued. In one-shot mode, a StartConvertT command
 *              must be issued for every temperature reading desired.
 * @warning     N/A.
 */
iAQ_Core_status_t  iAQ_Core_StopConvertTemperature ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd       =   iAQ_Core_STOP_CONVERT_T;
    i2c_status_t aux       =   0;


    // It sends the command
    aux = i2c_write ( myI2Cparameters, &cmd, 1, I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
        return   iAQ_Core_SUCCESS;
    else
        return   iAQ_Core_FAILURE;
}



/**
 * @brief       iAQ_Core_ReadRawTemperature ( I2C_parameters_t , iAQ_Core_vector_data_t* )
 *
 * @details     It reads the last raw temperature conversion result.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myRawTemperature:  Raw temperature ( two bytes ).
 *
 *
 * @return       Status of iAQ_Core_ReadRawTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        22/January/2018
 * @version     22/January/2018     The ORIGIN
 * @pre         DONE bit needs to be checked before calling this function.
 * @warning     N/A.
 */
iAQ_Core_status_t  iAQ_Core_ReadRawTemperature  ( I2C_parameters_t myI2Cparameters, iAQ_Core_vector_data_t* myRawTemperature )
{
    uint8_t      cmd[]     =   { iAQ_Core_READ_TEMPERATURE, 0 };
    i2c_status_t aux       =   0;



    // It sends the command and gets the result otherwise
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    // Parse the data
    myRawTemperature->MSBTemperature     =   cmd[0];
    myRawTemperature->LSBTemperature     =   cmd[1];




    if ( aux == I2C_SUCCESS )
        return   iAQ_Core_SUCCESS;
    else
        return   iAQ_Core_FAILURE;
}



/**
 * @brief       iAQ_Core_ReadTemperature ( I2C_parameters_t , iAQ_Core_vector_data_t* )
 *
 * @details     It reads the last current temperature conversion result.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myTemperature:     Current temperature.
 *
 *
 * @return       Status of iAQ_Core_ReadTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        22/January/2018
 * @version     22/January/2018     The ORIGIN
 * @pre         This function updates the raw temperature variables.
 * @pre         DONE bit needs to be checked before calling this function.
 * @warning     N/A.
 */
iAQ_Core_status_t  iAQ_Core_ReadTemperature  ( I2C_parameters_t myI2Cparameters, iAQ_Core_vector_data_t* myTemperature )
{
    uint8_t      cmd[]     =   { iAQ_Core_READ_TEMPERATURE, 0 };
    i2c_status_t aux       =   0;
    uint32_t     i         =   0;



    // It sends the command and gets the result otherwise
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );


    // Update the raw temperature value
    myTemperature->MSBTemperature     =   cmd[0];
    myTemperature->LSBTemperature     =   cmd[1];


    // Calculate the current temperature
    // Check if the temperature is positive or negative
    if ( ( myTemperature->MSBTemperature & MSB_TEMPERATURE_SIGN_BIT_MASK ) == MSB_TEMPERATURE_SIGN_BIT_NEGATIVE )
    {
    // The temperature is NEGATIVE
        myTemperature->MSBTemperature   -=   1;
        myTemperature->MSBTemperature    =  ~myTemperature->MSBTemperature;

        myTemperature->LSBTemperature   -=   1;
        myTemperature->LSBTemperature    =   ( ~myTemperature->LSBTemperature & 0xF0 );

        myTemperature->Temperature       =   ( -1.0 * myTemperature->MSBTemperature );
    }
    else
    {
    // The temperature is POSITIVE
        myTemperature->Temperature       =   myTemperature->MSBTemperature;
    }


    // Update the decimal value
    for ( i = 0; i < ( myTemperature->LSBTemperature >> 4 ); i++ )
            myTemperature->Temperature  +=   iAQ_Core_TEMPERATURE_RESOLUTION;






    if ( aux == I2C_SUCCESS )
        return   iAQ_Core_SUCCESS;
    else
        return   iAQ_Core_FAILURE;
}



/**
 * @brief       iAQ_Core_GetStatusRegister ( I2C_parameters_t , iAQ_Core_vector_data_t* )
 *
 * @details     It reads the CONFIGURATION/STATUS register.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myStatusRegister:  Current Status register value.
 *
 *
 * @return       Status of iAQ_Core_GetStatusRegister.
 *
 *
 * @author      Manuel Caballero
 * @date        23/January/2018
 * @version     23/January/2018     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
iAQ_Core_status_t  iAQ_Core_GetStatusRegister   ( I2C_parameters_t myI2Cparameters, iAQ_Core_vector_data_t* myStatusRegister )
{
    uint8_t      cmd     =   iAQ_Core_ACCESS_CONFIG;
    i2c_status_t aux     =   0;


    // It sends the command and gets the result
    aux = i2c_write ( myI2Cparameters, &cmd, 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myI2Cparameters, &myStatusRegister->Control_Status_Register, 1 );





    if ( aux == I2C_SUCCESS )
        return   iAQ_Core_SUCCESS;
    else
        return   iAQ_Core_FAILURE;
}



/**
 * @brief       iAQ_Core_SetConversionMode ( I2C_parameters_t , iAQ_Core_access_config_1shot_t )
 *
 * @details     It sets 1SHOT/Continuous temperature conversion mode.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myConversionMode:  ACCESS_CONFIG_1SHOT_ONE_TEMPERATURE_CONVERSION:             1SHOT temperature conversion mode
 *                                  ACCESS_CONFIG_1SHOT_CONTINUOUSLY_TEMPERATURE_CONVERSION:    Continuous temperature conversion mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of iAQ_Core_SetConversionMode.
 *
 *
 * @author      Manuel Caballero
 * @date        23/January/2018
 * @version     23/January/2018     The ORIGIN
 * @pre         N/A
 * @warning     Since the configuration register is implemented in
 *              EEPROM, writes to the register require 10ms to complete.
 *              After issuing a command to write to the configuration register,
 *              no further accesses to the iAQ_Core should be made for at least 10ms.
 */
iAQ_Core_status_t  iAQ_Core_SetConversionMode   ( I2C_parameters_t myI2Cparameters, iAQ_Core_access_config_1shot_t myConversionMode )
{
    uint8_t      cmd[]   =   { iAQ_Core_ACCESS_CONFIG, 0 };
    i2c_status_t aux     =   0;


    // It sends the command and gets the result
    aux = i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myI2Cparameters, &cmd[1], 1 );


    // Mask the bit and check which mode to use
    cmd[1] &= ~ACCESS_CONFIG_1SHOT_MASK;

    if ( myConversionMode == ACCESS_CONFIG_1SHOT_ONE_TEMPERATURE_CONVERSION )
    {
    // 1SHOT Mode
        cmd[1] |=   ACCESS_CONFIG_1SHOT_ONE_TEMPERATURE_CONVERSION;
    }
    else
    {
    // Continuously Mode
        cmd[1] &=  ~ACCESS_CONFIG_1SHOT_ONE_TEMPERATURE_CONVERSION;
    }


    // Update the CONFIGURATION/STATUS register
    aux  =  i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
        return   iAQ_Core_SUCCESS;
    else
        return   iAQ_Core_FAILURE;
}



/**
 * @brief       iAQ_Core_IsTemperatureConversionDone ( I2C_parameters_t , iAQ_Core_vector_data_t* )
 *
 * @details     It checks if a temperature conversion is done.
 *
 * @param[in]    myI2Cparameters:                I2C parameters.
 *
 * @param[out]   myTemperatureConversionStatus:  Temperature conversion bit:
 *                                                  ACCESS_CONFIG_DONE_CONVERSION_COMPLETE
 *                                                  ACCESS_CONFIG_DONE_CONVERSION_IN_PROGRESS.
 *
 *
 * @return       Status of iAQ_Core_IsTemperatureConversionDone.
 *
 *
 * @author      Manuel Caballero
 * @date        24/January/2018
 * @version     24/January/2018     The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
iAQ_Core_status_t iAQ_Core_IsTemperatureConversionDone ( I2C_parameters_t myI2Cparameters, iAQ_Core_access_config_done_t* myTemperatureConversionStatus )
{
    uint8_t      cmd[]     =   { iAQ_Core_ACCESS_CONFIG, 0 };
    i2c_status_t aux       =   0;


    // It sends the command and gets the result
    aux = i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux = i2c_read  ( myI2Cparameters, &cmd[1], 1 );


    // Update the value
    *myTemperatureConversionStatus   =   ( cmd[1] & ACCESS_CONFIG_DONE_MASK );



    if ( aux == I2C_SUCCESS )
        return   iAQ_Core_SUCCESS;
    else
        return   iAQ_Core_FAILURE;
}



/**
 * @brief       iAQ_Core_ReadBytesEEPROM ( I2C_parameters_t , uint8_t , uint8_t* , uint8_t )
 *
 * @details     It reads a certain number of bytes from EEPROM memory.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 * @param[in]    myStartingAddress:     Starting address to read the EEPROM memory.
 * @param[in]    myLength:              Amount of bytes to read.
 *
 * @param[out]   myReadBytesEEPROM:     Read values from EEPROM memory.
 *
 *
 * @return       Status of iAQ_Core_ReadBytesEEPROM.
 *
 *
 * @author      Manuel Caballero
 * @date        25/January/2018
 * @version     25/January/2018     The ORIGIN
 * @pre         N/A.
 * @warning     When the address pointer reaches the end of the 256-byte memory space ( address FFh )
 *              it increments from the end of the memory back to the first location of the memory
 *              ( address 00h ).
 */
iAQ_Core_status_t iAQ_Core_ReadBytesEEPROM ( I2C_parameters_t myI2Cparameters, uint8_t myStartingAddress, uint8_t* myReadBytesEEPROM, uint8_t myLength )
{
    uint8_t      cmd[]     =   { iAQ_Core_ACCESS_MEMORY, 0 };
    i2c_status_t aux       =   0;



    // It sends the command, the address location and gets the result
    cmd[1]   =   myStartingAddress;
    aux = i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_NO_STOP_BIT );
    aux = i2c_read  ( myI2Cparameters, myReadBytesEEPROM, myLength );





    if ( aux == I2C_SUCCESS )
        return   iAQ_Core_SUCCESS;
    else
        return   iAQ_Core_FAILURE;
}



/**
 * @brief       iAQ_Core_WriteBytesEEPROM ( I2C_parameters_t , uint8_t , uint8_t , uint8_t )
 *
 * @details     It writes a certain number of bytes to EEPROM memory.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 * @param[in]    myStartingAddress:     Starting address to write the EEPROM memory.
 * @param[in]    myWriteBytesEEPROM:    Bytes to write to the EEPROM memory.
 * @param[in]    myLength:              Amount of bytes to write.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of iAQ_Core_WriteBytesEEPROM.
 *
 *
 * @author      Manuel Caballero
 * @date        26/January/2018
 * @version     26/January/2018     The ORIGIN
 * @pre         N/A.
 * @warning     The STOP condition causes the iAQ_Core to initiate the write to EEPROM sequence.
 * @warning     If the starting address is 00 and the incoming data is 00 11 22 33 44 55 66 77 88 99,
 *              the result is mem00=88 mem01=99 mem02=22 mem03=33 mem04=44 mem05=55 mem06=66 mem07=77.
 *              The data wraps around and overwrites itself.
 * @warning     EEPROM Write Cycle Time: 50ms ( maximum ). The user must take care of this time!.
 */
iAQ_Core_status_t iAQ_Core_WriteBytesEEPROM ( I2C_parameters_t myI2Cparameters, uint8_t myStartingAddress, uint8_t myWriteBytesEEPROM[], uint8_t myLength )
{
    uint8_t      cmd[ myLength + 2 ];
    uint32_t     i         =     0;
    i2c_status_t aux       =     0;

    // Prepare COMMANDS
    cmd[0]   =   iAQ_Core_ACCESS_MEMORY;
    cmd[1]   =   myStartingAddress;

    // Prepare the payload to be stored into the EEPROM memory
    for ( i = 2 ; i < ( myLength + 2 ); i++ )
        cmd[ i ]       =   myWriteBytesEEPROM[ i - 2 ];

    // It sends the command, the address location as well as the payload
    aux = i2c_write ( myI2Cparameters, &cmd[0], myLength + 2, I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
        return   iAQ_Core_SUCCESS;
    else
        return   iAQ_Core_FAILURE;
}
