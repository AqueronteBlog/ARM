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
 * @brief       PCF8591_SetADC ( NRF_TWI_Type* , PCF8591_address_t , PCF8591_analog_input_programming_t , PCF8591_auto_increment_status_t , PCF8591_channel_number_t )
 *
 * @details     It configures the ADC.
 *
 * @param[in]    myinstance:        Peripheral's Instance.
 * @param[in]    myPCF8591Addr:     I2C Device address.
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
 * @version     22/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
PCF8591_status_t  PCF8591_SetADC ( NRF_TWI_Type* myinstance, PCF8591_address_t myPCF8591Addr, PCF8591_analog_input_programming_t myAnalogInputs, PCF8591_auto_increment_status_t myAutoIncrement, PCF8591_channel_number_t myADCchannel )
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



    // Update Control Byte
    aux = i2c_write ( myinstance, myPCF8591Addr, &cmd, 1, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   PCF8591_SUCCESS;
    else
        return   PCF8591_FAILURE;
}



/**
 * @brief       PCF8591_ReadADC ( NRF_TWI_Type* , PCF8591_address_t , PCF8591_vector_data_t*  )
 *
 * @details     It gets the ADC result from the device.
 *
 * @param[in]    myinstance:        Peripheral's Instance.
 * @param[in]    myPCF8591Addr:     I2C Device address.
 *
 * @param[out]   myADC_Data:        ADC result into the chosen channel.
 *
 *
 * @return       Status of PCF8591_ReadADC.
 *
 *
 * @author      Manuel Caballero
 * @date        22/September/2017
 * @version     22/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
PCF8591_status_t  PCF8591_ReadADC ( NRF_TWI_Type* myinstance, PCF8591_address_t myPCF8591Addr, PCF8591_vector_data_t* myADC_Data )
{
    uint8_t     cmd[]               =    { 0, 0, 0, 0 };
    uint32_t    aux                 =    0;
    uint32_t    myNumberReadings    =    0;
    uint32_t    i                   =    0;




    aux = i2c_read ( myinstance, myPCF8591Addr, &cmd[0], 2 );

    if ( _AUTO_INCREMENT_STATUS == PCF8591_AUTO_INCREMENT_ENABLED )
    {
        for ( i = 2; i < 3; i++ )
        {
            aux = i2c_read ( myinstance, myPCF8591Addr, &cmd[ i ], 1 );
        }

    }


    // Store the data in the right position  CHANGE!!!
    switch ( _CHANNEL_NUMBER )
    {
    default:
    case PCF8591_CHANNEL_0:
        myADC_Data->ADC_Channel_0    =   cmd[ 1 ];

        if ( _AUTO_INCREMENT_STATUS == PCF8591_AUTO_INCREMENT_ENABLED )
        {
            myADC_Data->ADC_Channel_1    =   cmd[ 3 ];
            myADC_Data->ADC_Channel_2    =   cmd[ 5 ];
            myADC_Data->ADC_Channel_3    =   cmd[ 7 ];
        }
        break;

    case PCF8591_CHANNEL_1:
        myADC_Data->ADC_Channel_1    =   cmd[ 1 ];

        if ( _AUTO_INCREMENT_STATUS == PCF8591_AUTO_INCREMENT_ENABLED )
        {
            myADC_Data->ADC_Channel_2    =   cmd[ 3 ];
            myADC_Data->ADC_Channel_3    =   cmd[ 5 ];
            myADC_Data->ADC_Channel_0    =   cmd[ 7 ];
        }
        break;

    case PCF8591_CHANNEL_2:
        myADC_Data->ADC_Channel_2    =   cmd[ 1 ];

        if ( _AUTO_INCREMENT_STATUS == PCF8591_AUTO_INCREMENT_ENABLED )
        {
            myADC_Data->ADC_Channel_3    =   cmd[ 3 ];
            myADC_Data->ADC_Channel_0    =   cmd[ 5 ];
            myADC_Data->ADC_Channel_1    =   cmd[ 7 ];
        }
        break;

    case PCF8591_CHANNEL_3:
        myADC_Data->ADC_Channel_3    =   cmd[ 1 ];

        if ( _AUTO_INCREMENT_STATUS == PCF8591_AUTO_INCREMENT_ENABLED )
        {
            myADC_Data->ADC_Channel_0    =   cmd[ 3 ];
            myADC_Data->ADC_Channel_1    =   cmd[ 5 ];
            myADC_Data->ADC_Channel_2    =   cmd[ 7 ];
        }
        break;
    }




    if ( aux == I2C_SUCCESS )
        return   PCF8591_SUCCESS;
    else
        return   PCF8591_FAILURE;
}
