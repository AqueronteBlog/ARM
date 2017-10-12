/**
 * @brief       HMC5883L.h
 * @details     3-Axis Digital Compass IC.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        12/October/2017
 * @version     12/October/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "HMC5883L.h"


/**
 * @brief       HMC5883L_SetPins ( NRF_TWI_Type* , HMC5883L_address_t , HMC5883L_vector_data_t )
 *
 * @details     It configures the port of the device.
 *
 * @param[in]    myinstance:        Peripheral's Instance.
 * @param[in]    myHMC5883LAddr:     I2C Device address.
 * @param[in]    myConfDATA:        Data to set up the device.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of HMC5883L_SetPins.
 *
 *
 * @author      Manuel Caballero
 * @date        11/October/2017
 * @version     11/October/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
HMC5883L_status_t  HMC5883L_SetPins   ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_vector_data_t  myConfDATA )
{
    uint32_t     aux     =    0;


    // Configure the ports of the device
    aux = i2c_write ( myinstance, myHMC5883LAddr, &myConfDATA, 1, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   HMC5883L_SUCCESS;
    else
        return   HMC5883L_FAILURE;
}



/**
 * @brief       HMC5883L_ReadPins ( NRF_TWI_Type* , HMC5883L_address_t , HMC5883L_vector_data_t*  )
 *
 * @details     It gets the data from the device ( port status ).
 *
 * @param[in]    myinstance:        Peripheral's Instance.
 * @param[in]    myHMC5883LAddr:     I2C Device address.
 *
 * @param[out]   myReadDATA:        ADC result into the chosen channel.
 *
 *
 * @return       Status of HMC5883L_ReadPins.
 *
 *
 * @author      Manuel Caballero
 * @date        11/October/2017
 * @version     11/October/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
HMC5883L_status_t  HMC5883L_ReadPins ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_vector_data_t* myReadDATA )
{
    uint32_t     aux  =    0;


    // Read the port
    aux = i2c_read ( myinstance, myHMC5883LAddr, &myReadDATA, 1 );




    if ( aux == I2C_SUCCESS )
        return   HMC5883L_SUCCESS;
    else
        return   HMC5883L_FAILURE;
}
