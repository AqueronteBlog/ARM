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
 * @brief       uint32_t  i2c_write   ( uint8_t* i2c_buff, uint32_t i2c_data_length, uint32_t i2c_generate_stop )
 * @details     Send data through I2C bus.
 *
 * @param[in]    *i2c_buff:             Data to be transmitted.
 * @param[in]    i2c_data_length:       Amount of data to be transmitted.
 * @param[in]    i2c_generate_stop:     Amount of data to be transmitted.
 *
 * @param[out]   Status of i2c_write:   I2C_STOP_BIT:       Generate a STOP bit.
 *                                      I2C_NO_STOP_BIT:    DO NOT generate a STOP bit
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
uint32_t    i2c_write   ( NRF_TWI_Type* myinstance, uint8_t* i2c_buff, uint32_t i2c_data_length, uint32_t i2c_generate_stop )
{
    uint32_t    i           =   0;
    uint32_t    i2c_timeout =   0;

// Start transmission
    // Reset flag and start event
    myinstance->EVENTS_TXDSENT   =   0;
    //NRF_TWI0->EVENTS_TXDSENT   =   0;
    myinstance->TASKS_STARTTX    =   1;

    // Start transmitting data
    for ( i = 0; i < i2c_data_length; i++ )
    {
        myinstance->TXD              =   *i2c_buff;

        i2c_timeout                =   232323;
        while( ( myinstance->EVENTS_TXDSENT == 0 ) && ( --i2c_timeout ) );        // Wait until the data is transmitted or timeout
        myinstance->EVENTS_TXDSENT   =   0;                                       // reset flag

        i2c_buff++;
    }

    // Generate a STOP bit if it is required
    if ( i2c_generate_stop == I2C_STOP_BIT )
    {
        myinstance->EVENTS_STOPPED   =   0;
        myinstance->TASKS_STOP       =   1;
        i2c_timeout                =   232323;
        while( ( myinstance->EVENTS_STOPPED == 0 ) && ( --i2c_timeout ) );
        myinstance->EVENTS_STOPPED   =   0;
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
uint32_t    i2c_read   ( NRF_TWI_Type* myinstance, uint8_t* i2c_buff, uint32_t i2c_data_length )
{
    uint32_t    i           =   0;
    uint32_t    i2c_timeout =   0;


// Start reading
    // Clear the shortcuts
    myinstance->SHORTS           =   ( TWI_SHORTS_BB_STOP_Disabled   << TWI_SHORTS_BB_STOP_Pos    );
    myinstance->SHORTS           =   ( TWI_SHORTS_BB_SUSPEND_Enabled << TWI_SHORTS_BB_SUSPEND_Pos );


    // Reset flag and start reading
    myinstance->EVENTS_RXDREADY  =   0;
    myinstance->TASKS_STARTRX    =   1;


    // Read data from i2c bus
    for ( i = 0; i < i2c_data_length; i++ )
    {
    // Enable the right shortcut ( NRF51 Reference Manual 28.5 Master read sequence. Figure 65 )
        if ( i == ( i2c_data_length - 1 ) )
            myinstance->SHORTS           =   ( TWI_SHORTS_BB_STOP_Enabled << TWI_SHORTS_BB_STOP_Pos );
        else
            myinstance->SHORTS           =   ( TWI_SHORTS_BB_SUSPEND_Enabled << TWI_SHORTS_BB_SUSPEND_Pos );

    // It releases the bus
        myinstance->TASKS_RESUME     =   1;                                     // NOTE: This is important to be here otherwise the STOP event
                                                                                //       will be clocked one byte later.

    // Wait until the data arrives or timeout
        i2c_timeout                =   232323;
        while( ( myinstance->EVENTS_RXDREADY == 0 ) && ( --i2c_timeout ) );     // Wait until the data is read or timeout
        myinstance->EVENTS_RXDREADY  =   0;                                     // reset flag

    // Read data and prepare the next one
        *i2c_buff                  =   myinstance->RXD;
        i2c_buff++;
    }


    // Wait until the STOP event is produced or timeout
    i2c_timeout                =   232323;
    while( ( myinstance->EVENTS_STOPPED == 0 ) && ( --i2c_timeout ) );
    myinstance->EVENTS_STOPPED   =   0;


    // Reset shortcuts
    myinstance->SHORTS           =   ( TWI_SHORTS_BB_SUSPEND_Disabled << TWI_SHORTS_BB_SUSPEND_Pos );
    myinstance->SHORTS           =   ( TWI_SHORTS_BB_STOP_Disabled << TWI_SHORTS_BB_STOP_Pos );

    // Check if everything went fine
    if ( i2c_timeout < 1 )
        return I2C_FAILURE;
    else
        return I2C_SUCCESS;
}
