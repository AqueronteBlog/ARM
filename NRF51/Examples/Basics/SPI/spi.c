/**
 * @brief       spi.c
 * @details     NRF51 SPI function libraries.
 *              Function file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        26/September/2017
 * @version     26/September/2017    The ORIGIN
 * @pre         NaN
 * @warning     This file is ONLY for NRF51 device.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "spi.h"


/**
 * @brief       spi_transfer   ( NRF_TWI_Type* , uint8_t* , uint32_t , uint8_t* , uint32_t )
 *
 * @details     Send/Receive data through the SPI bus.
 *
 * @param[in]    myinstance:            SPI instance.
 * @param[in]    spi_tx_buff:           Data to be transmitted through SPI bus.
 * @param[in]    spi_tx_length:         Amount of data to be transmitted through SPI bus.
 * @param[in]    spi_rx_length:         Amount of data to be read through SPI bus.
 *
 * @param[out]   spi_rx_buff:           Data from the SPI bus.
 *
 *
 * @return      Status of spi_transfer
 *
 *
 * @author      Manuel Caballero
 * @date        26/September/2017
 * @version     26/September/2017   The ORIGIN
 * @pre         SPI communication is by polling mode.
 * @warning     NaN.
 */
spi_status_t    spi_transfer ( NRF_TWI_Type* myinstance, uint8_t* spi_tx_buff, uint32_t spi_tx_length, uint8_t* spi_rx_buff, uint32_t spi_rx_length )
{
    spi_status_t mySPI_status,



// Start transmission



    // Check if everything went fine
    if ( ( i2c_timeout1 < 1 ) || ( i2c_timeout2 < 1 ) )
        return SPI_FAILURE;
    else
        return SPI_SUCCESS;
}
