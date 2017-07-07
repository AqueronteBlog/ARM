/**
 * @brief       i2c.c
 * @details     NRF51 I2C function libraries.
 *              Function file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        6/July/2017
 * @version     6/July/2017    The ORIGIN
 * @pre         NaN
 * @warning     This file is ONLY for NRF51 device.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "i2c.h"


/**
 * @brief       uint32_t  i2c_write   ( uint8_t* i2c_buff, uint32_t i2c_data_length )
 * @details     Send data through I2C bus.
 *
 * @param[in]    *i2c_buff:         Data to be transmitted.
 * @param[in]    i2c_data_length:   Amount of data to be transmitted.
 *
 * @param[out]   Status of i2c_write.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        6/July/2017
 * @version     6/July/2017   The ORIGIN
 * @pre         I2C communication is by polling mode.
 * @warning     This function takes for granted that TWI0 is used.
 */
uint32_t    i2c_write   ( uint8_t* i2c_buff, uint32_t i2c_data_length )
{
    uint32_t    i           =   0;
    uint32_t    i2c_timeout =   0;

// Start transmission
    for ( i = 0; i < i2c_data_length; i++ )
    {
        NRF_TWI0->TXD              =   *i2c_buff;
        NRF_TWI0->TASKS_STARTTX    =   1;

        i2c_timeout                =   232323;
        while( ( NRF_TWI0->EVENTS_TXDSENT == 0 ) && ( --i2c_timeout ) );        // Wait until the data is transmitted or timeout
        NRF_TWI0->EVENTS_TXDSENT   =   0;                                       // reset flag

        i2c_buff++;                                                             // Prepare next data to be transmitted
    }

// Check if everything went fine
    if ( i2c_timeout < 1 )
        return I2C_FAILURE;
    else
        return I2C_SUCCESS;
}
