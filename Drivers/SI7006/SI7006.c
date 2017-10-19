/**
 * @brief       SI7006.c
 * @details     I2C HUMIDITY AND TEMPERATURE SENSOR.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        19/October/2017
 * @version     19/October/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "SI7006.h"


/**
 * @brief       SI7006_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of SI7006_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        19/October/2017
 * @version     19/October/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
SI7006_status_t  SI7006_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
        return   SI7006_SUCCESS;
    else
        return   SI7006_FAILURE;
}



/**
 * @brief       SI7006_SetADC ( I2C_parameters_t , SI7006_conf_parameters_t )
 *
 * @details     It configures the ADC.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myConfParameters:  Parameters to configure the device.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of SI7006_SetADC.
 *
 *
 * @author      Manuel Caballero
 * @date        22/September/2017
 * @version     17/October/2017     The driver was improved, less code.
 *              16/October/2017     Adapted to the new I2C driver.
 *              22/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
SI7006_status_t  SI7006_SetADC ( I2C_parameters_t myI2Cparameters, SI7006_conf_parameters_t myConfParameters )
{
    uint8_t     cmd                 =    0;
    uint32_t    aux                 =    0;


    // ANALOG INPUT PROGRAMMING
    cmd  |=  myConfParameters.ANALOG_INPUT_PROGRAMMING;

    // AUTO-INCREMENT FLAG
    cmd  |=  myConfParameters.AUTO_INCREMENT_STATUS;

    // A/D CHANNEL NUMBER
    cmd  |=  myConfParameters.CHANNEL_NUMBER;



    // Mask DAC
    cmd  |=  myConfParameters.DAC_STATUS;



    // Update Control Byte
    aux = i2c_write ( myI2Cparameters, &cmd, 1, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   SI7006_SUCCESS;
    else
        return   SI7006_FAILURE;
}



/**
 * @brief       SI7006_ReadADC ( I2C_parameters_t , SI7006_conf_parameters_t , SI7006_vector_data_t*  )
 *
 * @details     It gets the ADC result from the device.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myConfParameters:  Parameters to configure the device.
 *
 * @param[out]   myADC_Data:        ADC result into the chosen channel.
 *
 *
 * @return       Status of SI7006_ReadADC.
 *
 *
 * @author      Manuel Caballero
 * @date        22/September/2017
 * @version     17/October/2017     The driver was improved, less code.
 *              16/October/2017     Adapted to the new I2C driver.
 *              22/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
SI7006_status_t  SI7006_ReadADC ( I2C_parameters_t myI2Cparameters, SI7006_conf_parameters_t myConfParameters, SI7006_vector_data_t* myADC_Data )
{
    uint8_t     cmd[]               =    { 0, 0, 0, 0, 0 };
    uint32_t    aux                 =    0;
    uint32_t    i                   =    0;




    if ( myConfParameters.AUTO_INCREMENT_STATUS == SI7006_AUTO_INCREMENT_ENABLED )
        i    =   5;
    else
        i    =   2;



    aux = i2c_read ( myI2Cparameters, &cmd[0], i );



    // Store the data in the right position
    switch ( myConfParameters.CHANNEL_NUMBER )
    {
    default:
    case SI7006_CHANNEL_0:
        myADC_Data->ADC_Channel_0    =   cmd[ 1 ];

        if ( myConfParameters.AUTO_INCREMENT_STATUS == SI7006_AUTO_INCREMENT_ENABLED )
        {
            myADC_Data->ADC_Channel_1    =   cmd[ 2 ];
            myADC_Data->ADC_Channel_2    =   cmd[ 3 ];
            myADC_Data->ADC_Channel_3    =   cmd[ 4 ];
        }
        break;

    case SI7006_CHANNEL_1:
        myADC_Data->ADC_Channel_1    =   cmd[ 1 ];

        if ( myConfParameters.AUTO_INCREMENT_STATUS == SI7006_AUTO_INCREMENT_ENABLED )
        {
            myADC_Data->ADC_Channel_2    =   cmd[ 2 ];
            myADC_Data->ADC_Channel_3    =   cmd[ 3 ];
            myADC_Data->ADC_Channel_0    =   cmd[ 4 ];
        }
        break;

    case SI7006_CHANNEL_2:
        myADC_Data->ADC_Channel_2    =   cmd[ 1 ];

        if ( myConfParameters.AUTO_INCREMENT_STATUS == SI7006_AUTO_INCREMENT_ENABLED )
        {
            myADC_Data->ADC_Channel_3    =   cmd[ 2 ];
            myADC_Data->ADC_Channel_0    =   cmd[ 3 ];
            myADC_Data->ADC_Channel_1    =   cmd[ 4 ];
        }
        break;

    case SI7006_CHANNEL_3:
        myADC_Data->ADC_Channel_3    =   cmd[ 1 ];

        if ( myConfParameters.AUTO_INCREMENT_STATUS == SI7006_AUTO_INCREMENT_ENABLED )
        {
            myADC_Data->ADC_Channel_0    =   cmd[ 2 ];
            myADC_Data->ADC_Channel_1    =   cmd[ 3 ];
            myADC_Data->ADC_Channel_2    =   cmd[ 4 ];
        }
        break;
    }




    if ( aux == I2C_SUCCESS )
        return   SI7006_SUCCESS;
    else
        return   SI7006_FAILURE;
}



/**
 * @brief       SI7006_SetDAC ( I2C_parameters_t , SI7006_conf_parameters_t )
 *
 * @details     It enables/disables the DAC.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myConfParameters:  Parameters to configure the device.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of SI7006_SetDAC.
 *
 *
 * @author      Manuel Caballero
 * @date        24/September/2017
 * @version     17/October/2017     The driver was improved, less code.
 *              16/October/2017     Adapted to the new I2C driver.
 *              24/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
SI7006_status_t  SI7006_SetDAC ( I2C_parameters_t myI2Cparameters, SI7006_conf_parameters_t myConfParameters )
{
    uint8_t     cmd                 =    0;
    uint32_t    aux                 =    0;


    // Mask ANALOG INPUT PROGRAMMING
    cmd  |=  myConfParameters.ANALOG_INPUT_PROGRAMMING;


    // Mask AUTO-INCREMENT FLAG
    cmd  |=  myConfParameters.AUTO_INCREMENT_STATUS;


    // Mask A/D CHANNEL NUMBER
    cmd  |=  myConfParameters.CHANNEL_NUMBER;



    // DAC
    cmd  |=  myConfParameters.DAC_STATUS;



    // Update Control Byte
    aux = i2c_write ( myI2Cparameters, &cmd, 1, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   SI7006_SUCCESS;
    else
        return   SI7006_FAILURE;
}



/**
 * @brief       SI7006_NewDACValue ( I2C_parameters_t , SI7006_conf_parameters_t , uint8_t )
 *
 * @details     It enables/disables the DAC.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myConfParameters:  Parameters to configure the device.
 * @param[in]    myNewDACValue:     New DAC value.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of SI7006_NewDACValue.
 *
 *
 * @author      Manuel Caballero
 * @date        24/September/2017
 * @version     17/October/2017     The driver was improved, less code.
 *              16/October/2017     Adapted to the new I2C driver.
 *              24/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
SI7006_status_t  SI7006_NewDACValue ( I2C_parameters_t myI2Cparameters, SI7006_conf_parameters_t myConfParameters, uint8_t myNewDACValue )
{
    uint8_t     cmd[]               =    { 0, 0 };
    uint32_t    aux                 =    0;


    // Mask ANALOG INPUT PROGRAMMING
    cmd[ 0 ]  |=  myConfParameters.ANALOG_INPUT_PROGRAMMING;


    // Mask AUTO-INCREMENT FLAG
    cmd[ 0 ]  |=  myConfParameters.AUTO_INCREMENT_STATUS;


    // Mask A/D CHANNEL NUMBER
    cmd[ 0 ]  |=  myConfParameters.CHANNEL_NUMBER;


    // Mask DAC
    cmd[ 0 ]  |=  myConfParameters.DAC_STATUS;




    // Update Control Byte + DAC output
    cmd[ 1 ]     =   myNewDACValue;
    aux = i2c_write ( myI2Cparameters, &cmd[0], 2, I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
        return   SI7006_SUCCESS;
    else
        return   SI7006_FAILURE;
}
