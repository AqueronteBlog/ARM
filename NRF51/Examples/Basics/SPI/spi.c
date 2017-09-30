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
 * @brief       spi_transfer   ( NRF_SPI_Type* , uint8_t* , uint32_t , uint8_t* , uint32_t , uint32_t )
 *
 * @details     Send/Receive data through the SPI bus.
 *
 * @param[in]    myinstance:            SPI instance.
 * @param[in]    spi_tx_buff:           Data to be transmitted through SPI bus.
 * @param[in]    spi_tx_length:         Amount of data to be transmitted through SPI bus.
 * @param[in]    spi_rx_length:         Amount of data to be read through SPI bus.
 * @param[in]    spi_cs_pin:            Chip select pin.
 *
 * @param[out]   spi_rx_buff:           Data from the SPI bus.
 *
 *
 * @return      Status of spi_transfer
 *
 *
 * @author      Manuel Caballero
 * @date        26/September/2017
 * @version     30/September/2017   SPI transmission according to what the datasheet says.
 *                                  Chip select pin is added ( better for abstraction ).
 *              26/September/2017   The ORIGIN
 * @pre         SPI communication is by polling mode.
 * @warning     NaN.
 */
spi_status_t    spi_transfer ( NRF_SPI_Type* myinstance, uint8_t* spi_tx_buff, uint32_t spi_tx_length, uint8_t* spi_rx_buff, uint32_t spi_rx_length, uint32_t spi_cs_pin )
{
    uint32_t     i                   =   0;
    uint32_t     spi_timeout1        =   0;
    uint32_t     spi_timeout2        =   0;


    NRF_GPIO->OUTCLR    =   ( 1UL << spi_cs_pin );                               // Start SPI communication. Chip Select LOW


    myinstance->TXD     =   *spi_tx_buff++;                                      // Send first byte
    spi_tx_length--;


// SPI TX
    for ( i = 0; i < spi_tx_length; i++ ){
        myinstance->TXD        =   *spi_tx_buff++;                                // Send data

        spi_timeout1                =   10;     //232323;
        while( ( myinstance->EVENTS_READY == 0 ) && ( --spi_timeout1 ) );         // Wait until the data is transmitted or timeout1
        *spi_rx_buff                =   myinstance->RXD;                          // Dummy value
        myinstance->EVENTS_READY    =   0;                                        // reset flag
    }

// SPI RX
    for ( i = 0; i < spi_rx_length; i++ ){
        myinstance->TXD        =   0x00;                                          // Dummy value

        spi_timeout2                =   10; //232323;
        while( ( myinstance->EVENTS_READY == 0 ) && ( --spi_timeout2 ) );         // Wait until the data is transmitted or timeout2
        *spi_rx_buff++             =   myinstance->RXD;                           // Get data
        myinstance->EVENTS_READY    =   0;                                        // reset flag
    }


    NRF_GPIO->OUTSET     =   ( 1UL << spi_cs_pin );                               // End SPI communication ( release the bus ).Chip Select HIGH



    // Check if everything went fine
    if ( ( spi_timeout1 < 1 ) || ( spi_timeout2 < 1 ) )
        return SPI_FAILURE;
    else
        return SPI_SUCCESS;
}
