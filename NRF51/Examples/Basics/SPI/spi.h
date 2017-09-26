/**
 * @brief       spi.h
 * @details     NRF51 SPI function libraries.
 *              Header file.
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

#include "nrf.h"
#include "nrf51_bitfields.h"


/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    SPI_SUCCESS  =   0x00,
    SPI_FAILURE  =   0x01
} spi_status_t;



/**
  * @brief   FUNCTION PROTOTYPES
  */
spi_status_t    spi_transfer    ( NRF_TWI_Type* myinstance, uint8_t* spi_tx_buff, uint32_t spi_tx_length, uint8_t* spi_rx_buff, uint32_t spi_rx_length );
