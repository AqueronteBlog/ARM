/**
 * @brief       MAX7219.c
 * @details     Serially Interfaced, 8-Digit LED Display Drivers.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        28/September/2017
 * @version     28/September/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

 #include "MAX7219.h"


/**
 * @brief       MAX7219_Reset   ( NRF_TWI_Type* )
 *
 * @details     [TODO].
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of MAX7219_Reset.
 *
 *
 * @author      Manuel Caballero
 * @date        28/September/2017
 * @version     28/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
MAX7219_status_t  MAX7219_Reset   ( NRF_TWI_Type* myinstance )
{
    uint8_t     cmd                 =    MAX7219_GENERAL_CALL_RESET;
    uint32_t    aux                 =    0;


    //aux = i2c_write ( myinstance, MAX7219_GENERAL_CALL, &cmd, 1, I2C_STOP_BIT );



    if ( aux == SPI_SUCCESS )
       return   MAX7219_SUCCESS;
    else
       return   MAX7219_FAILURE;
}

