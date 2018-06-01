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
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
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
 * @brief       iAQ_Core_GetNewReading ( I2C_parameters_t , iAQ_Core_vector_data_t* )
 *
 * @details     It performs a new parameters reading from the sensor.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myData:            All parameters: Prediction + Status Flag + Resistance + Tvoc.
 *
 *
 * @return       Status of iAQ_Core_GetNewReading.
 *
 *
 * @author      Manuel Caballero
 * @date        31/May/2018
 * @version     31/May/2018     The ORIGIN
 * @pre         Measurement interval ( continuous ): 1s | Measurement interval ( pulsed ): Max. 11s.
 * @warning     First functional reading after start up is 5 minutes.
 */
iAQ_Core_status_t  iAQ_Core_GetNewReading ( I2C_parameters_t myI2Cparameters, iAQ_Core_vector_data_t* myData )
{
    uint8_t      cmd[9]    =   { 0 };
    i2c_status_t aux       =   0;


    /* Get the data */
    aux = i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


    /* Update the parameters    */
    myData->pred         =  ( ( cmd[0] << 8 ) + cmd[1] );                           // Prediction = ( byte0 * 2^8 ) + byte1
    myData->status       =  cmd[2];
    myData->resistance   =  ( ( cmd[4] << 16 ) + ( cmd[5] << 8 ) + cmd[6] );        // Resistance = ( byte4 * 2^16 ) + ( byte5 * 2^8 ) + byte6
    myData->Tvoc         =  ( ( cmd[7] << 8 ) + cmd[8] );                           // Tvoc       = ( byte7 * 2^8 ) + byte8




    if ( aux == I2C_SUCCESS )
        return   iAQ_Core_SUCCESS;
    else
        return   iAQ_Core_FAILURE;
}
