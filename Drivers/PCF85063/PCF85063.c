/**
 * @brief       PCF85063.c
 * @details     Tiny Real-Time Clock/calendar.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/January/2019
 * @version     22/January/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ). All rights reserved.
 */

#include "PCF85063.h"


/**
 * @brief       PCF85063_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF85063_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        18/January/2019
 * @version     18/January/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
        return   PCF85063_SUCCESS;
    else
        return   PCF85063_FAILURE;
}



/**
 * @brief       PCF85063_SetPins ( I2C_parameters_t , PCF85063_vector_data_t )
 *
 * @details     It configures the port of the device.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myConfDATA:        Data to set up the device.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of PCF85063_SetPins.
 *
 *
 * @author      Manuel Caballero
 * @date        11/January/2019
 * @version     18/January/2019     Adapted to the new I2C driver.
 *              11/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_SetPins   ( I2C_parameters_t myI2Cparameters, PCF85063_vector_data_t  myConfDATA )
{
    uint32_t     aux     =    0;


    // Configure the ports of the device
    aux = i2c_write ( myI2Cparameters, &myConfDATA.data, 1, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   PCF85063_SUCCESS;
    else
        return   PCF85063_FAILURE;
}



/**
 * @brief       PCF85063_ReadPins ( I2C_parameters_t , PCF85063_vector_data_t*  )
 *
 * @details     It gets the data from the device ( port status ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   myReadDATA:        ADC result into the chosen channel.
 *
 *
 * @return       Status of PCF85063_ReadPins.
 *
 *
 * @author      Manuel Caballero
 * @date        11/January/2019
 * @version     18/January/2019     Adapted to the new I2C driver.
 *              11/January/2019     The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
PCF85063_status_t  PCF85063_ReadPins ( I2C_parameters_t myI2Cparameters, PCF85063_vector_data_t* myReadDATA )
{
    uint32_t     aux  =    0;


    // Read the port
    aux = i2c_read ( myI2Cparameters, &myReadDATA->data, 1 );




    if ( aux == I2C_SUCCESS )
        return   PCF85063_SUCCESS;
    else
        return   PCF85063_FAILURE;
}
