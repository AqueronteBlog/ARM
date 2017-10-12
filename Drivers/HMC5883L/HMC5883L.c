/**
 * @brief       PCF8574.h
 * @details     Remote 8-bit I/O expander for I2C-bus with interrupt.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        11/October/2017
 * @version     11/October/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "PCF8574.h"


/**
 * @brief       PCF8574_SetPins ( NRF_TWI_Type* , PCF8574_address_t , PCF8574_vector_data_t )
 *
 * @details     It configures the port of the device.
 *
 * @param[in]    myinstance:        Peripheral's Instance.
 * @param[in]    myPCF8574Addr:     I2C Device address.
 * @param[in]    myConfDATA:        Data to set up the device.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of PCF8574_SetPins.
 *
 *
 * @author      Manuel Caballero
 * @date        11/October/2017
 * @version     11/October/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
PCF8574_status_t  PCF8574_SetPins   ( NRF_TWI_Type* myinstance, PCF8574_address_t myPCF8574Addr, PCF8574_vector_data_t  myConfDATA )
{
    uint32_t     aux     =    0;


    // Configure the ports of the device
    aux = i2c_write ( myinstance, myPCF8574Addr, &myConfDATA.data, 1, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   PCF8574_SUCCESS;
    else
        return   PCF8574_FAILURE;
}



/**
 * @brief       PCF8574_ReadPins ( NRF_TWI_Type* , PCF8574_address_t , PCF8574_vector_data_t*  )
 *
 * @details     It gets the data from the device ( port status ).
 *
 * @param[in]    myinstance:        Peripheral's Instance.
 * @param[in]    myPCF8574Addr:     I2C Device address.
 *
 * @param[out]   myReadDATA:        ADC result into the chosen channel.
 *
 *
 * @return       Status of PCF8574_ReadPins.
 *
 *
 * @author      Manuel Caballero
 * @date        11/October/2017
 * @version     11/October/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
PCF8574_status_t  PCF8574_ReadPins ( NRF_TWI_Type* myinstance, PCF8574_address_t myPCF8574Addr, PCF8574_vector_data_t* myReadDATA )
{
    uint32_t     aux  =    0;


    // Read the port
    aux = i2c_read ( myinstance, myPCF8574Addr, &myReadDATA->data, 1 );




    if ( aux == I2C_SUCCESS )
        return   PCF8574_SUCCESS;
    else
        return   PCF8574_FAILURE;
}
