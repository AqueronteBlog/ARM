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


/**
 * @brief       uint32_t  i2c_read   ( uint8_t* i2c_buff, uint32_t i2c_data_length )
 * @details     Read data through I2C bus.
 *
 * @param[in]    *i2c_buff:         Data to be transmitted.
 * @param[in]    i2c_data_length:   Amount of data to be transmitted.
 *
 * @param[out]   Status of i2c_read.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        7/July/2017
 * @version     7/July/2017   The ORIGIN
 * @pre         I2C communication is by polling mode.
 * @warning     This function takes for granted that TWI0 is used.
 */
uint32_t    i2c_read   ( uint8_t* i2c_buff, uint32_t i2c_data_length )
{
    uint32_t    i           =   0;
    uint32_t    i2c_timeout =   0;

// Start reading
    NRF_TWI0->TASKS_STARTRX    =   1;

    for ( i = 0; i < i2c_data_length - 1; i++ )
    {
        NRF_TWI0->SHORTS           =   ( TWI_SHORTS_BB_SUSPEND_Enabled << TWI_SHORTS_BB_SUSPEND_Pos );

        i2c_timeout                =   232323;
        while( ( NRF_TWI0->EVENTS_RXDREADY == 0 ) && ( --i2c_timeout ) );       // Wait until the data is read or timeout
        NRF_TWI0->EVENTS_RXDREADY  =   0;                                       // reset flag

        *i2c_buff                  =   NRF_TWI0->RXD;
        i2c_buff++;                                                             // Prepare next data to be read
        NRF_TWI0->TASKS_RESUME     =   1;
    }


    NRF_TWI0->SHORTS           =   ( TWI_SHORTS_BB_STOP_Enabled << TWI_SHORTS_BB_STOP_Pos );

    i2c_timeout                =   232323;
    while( ( NRF_TWI0->EVENTS_RXDREADY == 0 ) && ( --i2c_timeout ) );           // Wait until the data is read or timeout
    NRF_TWI0->EVENTS_RXDREADY  =   0;                                           // reset flag

    *i2c_buff                  =   NRF_TWI0->RXD;                               // Read the last byte

    i2c_timeout                =   232323;
    while( ( NRF_TWI0->EVENTS_STOPPED == 0 ) && ( --i2c_timeout ) );
    NRF_TWI0->EVENTS_STOPPED   =   0;
    NRF_TWI0->TASKS_STOP       =   1;


// Check if everything went fine
    if ( i2c_timeout < 1 )
        return I2C_FAILURE;
    else
        return I2C_SUCCESS;
}
