/**
 * @brief       spi_mod.h
 * @details     NRF51 pseudo-SPI function libraries.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        3/October/2017
 * @version     3/October/2017    The ORIGIN
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
    SPI_MOD_SUCCESS  =   0x00,
    SPI_MOD_FAILURE  =   0x01
} spi_mod_status_t;



/**
  * @brief   PSEUDO-SPI PARAMETERS
  */
typedef struct{
    // Port for pins: MOSI, MISO, SCLK and CS
    NRF_GPIO_Type* MOSIport;
    NRF_GPIO_Type* MISOport;
    NRF_GPIO_Type* SCLKport;
    NRF_GPIO_Type* CSport;

    // Pin number
    uint32_t MOSI;
    uint32_t MISO;
    uint32_t SCLK;
    uint32_t CS;

    // SPI frequency
    uint32_t Freq;

    // SPI instance
    NRF_SPI_Type* SPIinstance;
} SPI_mod_parameters_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
spi_mod_status_t    spi_mod_transfer    ( NRF_SPI_Type* myinstance, uint8_t* spi_tx_buff, uint32_t spi_tx_length, uint8_t* spi_rx_buff, uint32_t spi_rx_length, uint32_t spi_cs_pin, NRF_GPIO_Type* myCSport );
spi_mod_status_t    spi_mod_init        ( SPI_mod_parameters_t mySPIparameters );
