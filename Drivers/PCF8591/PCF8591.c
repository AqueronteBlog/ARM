/**
 * @brief       PCF8591.c
 * @details     8-bit A/D and D/A converter.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        22/September/2017
 * @version     22/September/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "PCF8591.h"


/**
 * @brief       PCF8591_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of PCF8591_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        16/October/2017
 * @version     16/October/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
PCF8591_status_t  PCF8591_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
        return   PCF8591_SUCCESS;
    else
        return   PCF8591_FAILURE;
}



/**
 * @brief       PCF8591_SetADC ( I2C_parameters_t , PCF8591_analog_input_programming_t , PCF8591_auto_increment_status_t , PCF8591_channel_number_t )
 *
 * @details     It configures the ADC.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myAnalogInputs:    The analog input programming.
 * @param[in]    myAutoIncrement:   Auto-increment flag enabled/disabled.
 * @param[in]    myADCchannel:      ADC Channel number.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of PCF8591_SetADC.
 *
 *
 * @author      Manuel Caballero
 * @date        22/September/2017
 * @version     16/October/2017     Adapted to the new I2C driver.
 *              22/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
PCF8591_status_t  PCF8591_SetADC ( I2C_parameters_t myI2Cparameters, PCF8591_analog_input_programming_t myAnalogInputs, PCF8591_auto_increment_status_t myAutoIncrement, PCF8591_channel_number_t myADCchannel )
{
    uint8_t     cmd                 =    0;
    uint32_t    aux                 =    0;


    // ANALOG INPUT PROGRAMMING
    switch ( myAnalogInputs )
    {
    default:
    case PCF8591_FOUR_SINGLE_ENDED_INPUTS:
        // cmd  &=  0xCF;
        break;

    case PCF8591_THREE_DIFFERENTIAL_INPUTS:
        cmd  |=  0x10;
        break;

    case PCF8591_SINGLE_ENDED_AND_DIFFERENTIAL_MIXED:
        cmd  |=  0x20;
        break;

    case PCF8591_TWO_DIFFERENTIAL_INPUTS:
        cmd  |=  0x30;
        break;
    }

    _ANALOG_INPUT_PROGRAMMING    =   myAnalogInputs;


    // AUTO-INCREMENT FLAG
    if ( myAutoIncrement == PCF8591_AUTO_INCREMENT_ENABLED )
        cmd  |=  0x04;


    _AUTO_INCREMENT_STATUS   =   myAutoIncrement;



    // A/D CHANNEL NUMBER
    switch ( myADCchannel )
    {
    default:
    case PCF8591_CHANNEL_0:
        // cmd  &=  0xFC;
        break;

    case PCF8591_CHANNEL_1:
        cmd  |=  0x01;
        break;

    case PCF8591_CHANNEL_2:
        cmd  |=  0x02;
        break;

    case PCF8591_CHANNEL_3:
        cmd  |=  0x03;
        break;
    }


    _CHANNEL_NUMBER   =   myADCchannel;



    // Mask DAC
    if ( _DAC_STATUS == PCF8591_DAC_ENABLED )
        cmd  |=  0x40;




    // Update Control Byte
    aux = i2c_write ( myI2Cparameters, &cmd, 1, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   PCF8591_SUCCESS;
    else
        return   PCF8591_FAILURE;
}



/**
 * @brief       PCF8591_ReadADC ( I2C_parameters_t , PCF8591_vector_data_t*  )
 *
 * @details     It gets the ADC result from the device.
 *
 * @param[in]    myI2Cparameters:   I2C parameters
 *
 * @param[out]   myADC_Data:        ADC result into the chosen channel.
 *
 *
 * @return       Status of PCF8591_ReadADC.
 *
 *
 * @author      Manuel Caballero
 * @date        22/September/2017
 * @version     16/October/2017     Adapted to the new I2C driver.
 *              22/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
PCF8591_status_t  PCF8591_ReadADC ( I2C_parameters_t myI2Cparameters, PCF8591_vector_data_t* myADC_Data )
{
    uint8_t     cmd[]               =    { 0, 0, 0, 0, 0 };
    uint32_t    aux                 =    0;
    uint32_t    i                   =    0;




    if ( _AUTO_INCREMENT_STATUS == PCF8591_AUTO_INCREMENT_ENABLED )
        i    =   5;
    else
        i    =   2;



    aux = i2c_read ( myI2Cparameters, &cmd[0], i );



    // Store the data in the right position
    switch ( _CHANNEL_NUMBER )
    {
    default:
    case PCF8591_CHANNEL_0:
        myADC_Data->ADC_Channel_0    =   cmd[ 1 ];

        if ( _AUTO_INCREMENT_STATUS == PCF8591_AUTO_INCREMENT_ENABLED )
        {
            myADC_Data->ADC_Channel_1    =   cmd[ 2 ];
            myADC_Data->ADC_Channel_2    =   cmd[ 3 ];
            myADC_Data->ADC_Channel_3    =   cmd[ 4 ];
        }
        break;

    case PCF8591_CHANNEL_1:
        myADC_Data->ADC_Channel_1    =   cmd[ 1 ];

        if ( _AUTO_INCREMENT_STATUS == PCF8591_AUTO_INCREMENT_ENABLED )
        {
            myADC_Data->ADC_Channel_2    =   cmd[ 2 ];
            myADC_Data->ADC_Channel_3    =   cmd[ 3 ];
            myADC_Data->ADC_Channel_0    =   cmd[ 4 ];
        }
        break;

    case PCF8591_CHANNEL_2:
        myADC_Data->ADC_Channel_2    =   cmd[ 1 ];

        if ( _AUTO_INCREMENT_STATUS == PCF8591_AUTO_INCREMENT_ENABLED )
        {
            myADC_Data->ADC_Channel_3    =   cmd[ 2 ];
            myADC_Data->ADC_Channel_0    =   cmd[ 3 ];
            myADC_Data->ADC_Channel_1    =   cmd[ 4 ];
        }
        break;

    case PCF8591_CHANNEL_3:
        myADC_Data->ADC_Channel_3    =   cmd[ 1 ];

        if ( _AUTO_INCREMENT_STATUS == PCF8591_AUTO_INCREMENT_ENABLED )
        {
            myADC_Data->ADC_Channel_0    =   cmd[ 2 ];
            myADC_Data->ADC_Channel_1    =   cmd[ 3 ];
            myADC_Data->ADC_Channel_2    =   cmd[ 4 ];
        }
        break;
    }




    if ( aux == I2C_SUCCESS )
        return   PCF8591_SUCCESS;
    else
        return   PCF8591_FAILURE;
}



/**
 * @brief       PCF8591_SetDAC ( I2C_parameters_t , PCF8591_dac_status_t )
 *
 * @details     It enables/disables the DAC.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myDAC_Status:      Enable/Disable DAC.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of PCF8591_SetDAC.
 *
 *
 * @author      Manuel Caballero
 * @date        24/September/2017
 * @version     16/October/2017     Adapted to the new I2C driver.
 *              24/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
PCF8591_status_t  PCF8591_SetDAC ( I2C_parameters_t myI2Cparameters, PCF8591_dac_status_t myDAC_Status )
{
    uint8_t     cmd                 =    0;
    uint32_t    aux                 =    0;


    // Mask ANALOG INPUT PROGRAMMING
    switch ( _ANALOG_INPUT_PROGRAMMING )
    {
    default:
    case PCF8591_FOUR_SINGLE_ENDED_INPUTS:
        // cmd  &=  0xCF;
        break;

    case PCF8591_THREE_DIFFERENTIAL_INPUTS:
        cmd  |=  0x10;
        break;

    case PCF8591_SINGLE_ENDED_AND_DIFFERENTIAL_MIXED:
        cmd  |=  0x20;
        break;

    case PCF8591_TWO_DIFFERENTIAL_INPUTS:
        cmd  |=  0x30;
        break;
    }


    // Mask AUTO-INCREMENT FLAG
    if ( _AUTO_INCREMENT_STATUS == PCF8591_AUTO_INCREMENT_ENABLED )
        cmd  |=  0x04;



    // Mask A/D CHANNEL NUMBER
    switch ( _CHANNEL_NUMBER )
    {
    default:
    case PCF8591_CHANNEL_0:
        // cmd  &=  0xFC;
        break;

    case PCF8591_CHANNEL_1:
        cmd  |=  0x01;
        break;

    case PCF8591_CHANNEL_2:
        cmd  |=  0x02;
        break;

    case PCF8591_CHANNEL_3:
        cmd  |=  0x03;
        break;
    }



    // DAC
    if ( myDAC_Status == PCF8591_DAC_ENABLED )
        cmd  |=  0x40;


    _DAC_STATUS  =   myDAC_Status;



    // Update Control Byte
    aux = i2c_write ( myI2Cparameters, &cmd, 1, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   PCF8591_SUCCESS;
    else
        return   PCF8591_FAILURE;
}



/**
 * @brief       PCF8591_NewDACValue ( I2C_parameters_t , uint8_t )
 *
 * @details     It enables/disables the DAC.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myNewDACValue:     New DAC value.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of PCF8591_NewDACValue.
 *
 *
 * @author      Manuel Caballero
 * @date        24/September/2017
 * @version     16/October/2017     Adapted to the new I2C driver.
 *              24/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
PCF8591_status_t  PCF8591_NewDACValue ( I2C_parameters_t myI2Cparameters, uint8_t myNewDACValue )
{
    uint8_t     cmd[]               =    { 0, 0 };
    uint32_t    aux                 =    0;


    // Mask ANALOG INPUT PROGRAMMING
    switch ( _ANALOG_INPUT_PROGRAMMING )
    {
    default:
    case PCF8591_FOUR_SINGLE_ENDED_INPUTS:
        // cmd[ 0 ]  &=  0xCF;
        break;

    case PCF8591_THREE_DIFFERENTIAL_INPUTS:
        cmd[ 0 ]  |=  0x10;
        break;

    case PCF8591_SINGLE_ENDED_AND_DIFFERENTIAL_MIXED:
        cmd[ 0 ]  |=  0x20;
        break;

    case PCF8591_TWO_DIFFERENTIAL_INPUTS:
        cmd[ 0 ]  |=  0x30;
        break;
    }


    // Mask AUTO-INCREMENT FLAG
    if ( _AUTO_INCREMENT_STATUS == PCF8591_AUTO_INCREMENT_ENABLED )
        cmd[ 0 ]  |=  0x04;



    // Mask A/D CHANNEL NUMBER
    switch ( _CHANNEL_NUMBER )
    {
    default:
    case PCF8591_CHANNEL_0:
        // cmd[ 0 ]  &=  0xFC;
        break;

    case PCF8591_CHANNEL_1:
        cmd[ 0 ]  |=  0x01;
        break;

    case PCF8591_CHANNEL_2:
        cmd[ 0 ]  |=  0x02;
        break;

    case PCF8591_CHANNEL_3:
        cmd[ 0 ]  |=  0x03;
        break;
    }



    // Mask DAC
    if ( _DAC_STATUS == PCF8591_DAC_ENABLED )
        cmd[ 0 ]  |=  0x40;



    // Update Control Byte + DAC output
    cmd[ 1 ]     =   myNewDACValue;
    aux = i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
        return   PCF8591_SUCCESS;
    else
        return   PCF8591_FAILURE;
}
