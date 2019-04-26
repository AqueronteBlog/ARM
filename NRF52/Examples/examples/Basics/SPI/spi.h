/**
 * @brief       spi.h
 * @details     NRF52 SPI function libraries.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        26/April/2019
 * @version     26/April/2019    The ORIGIN
 * @pre         N/A
 * @warning     This file is ONLY for NRF52 device.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "nrf.h"
#include "nrf52_bitfields.h"


#ifndef SPI_H_
#define SPI_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
  * @brief   SPI MODES.
  *
  *             NOTES:
  *                 CPOL: Clock Polarity.
  *                 CPHA: Clock Phase.
  */
typedef enum
{
    SPI_MODE_0  =   0x00,           /*!<  SPI MODE 0: CPOL 0 | CPHA 0          */
    SPI_MODE_1  =   0x01,           /*!<  SPI MODE 1: CPOL 0 | CPHA 1          */
    SPI_MODE_2  =   0x02,           /*!<  SPI MODE 2: CPOL 1 | CPHA 0          */
    SPI_MODE_3  =   0x03            /*!<  SPI MODE 3: CPOL 1 | CPHA 1          */
} spi_modes_t;


/**
  * @brief   SPI ENABLE LINE MODE.
  *
  *             NOTES:
  *                 How the Chip select is active: High or Low
  */
typedef enum
{
    SPI_ENABLE_LINE_HIGH  =   0x00,         /*!<  Chip Select is Active High                */
    SPI_ENABLE_LINE_LOW   =   0x01          /*!<  Chip Select is Active Low ( Standard )    */
} spi_cs_enable_line_t;


/**
  * @brief   SPI BYTE ORDER.
  *
  */
typedef enum
{
    SPI_ORDER_MSB_FIRST  =   0x00,          /*!<  MSB is sent first                         */
    SPI_ORDER_LSB_FIRST  =   0x01           /*!<  LSB is sent first                         */
} spi_byte_order_t;


/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    SPI_SUCCESS  =   0x00,
    SPI_FAILURE  =   0x01
} spi_status_t;



/**
  * @brief   SPI PARAMETERS
  */
typedef struct{
    /* Port for pins: MOSI, MISO, SCLK and CS */
    NRF_GPIO_Type* MOSIport;
    NRF_GPIO_Type* MISOport;
    NRF_GPIO_Type* SCLKport;
    NRF_GPIO_Type* CSport;

    /* Pin number */
    uint32_t MOSI;
    uint32_t MISO;
    uint32_t SCLK;
    uint32_t CS;

    /* SPI frequency */
    uint32_t Freq;

    /* SPI Mode */
    spi_modes_t SPImode;

    /* SPI Chip Select enable line mode */
    spi_cs_enable_line_t SPIenable_line_mode;

    /* SPI Byte order */
    spi_byte_order_t SPIbyte_order;

    /* SPI instance */
    NRF_SPI_Type* SPIinstance;
} SPI_parameters_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
spi_status_t    spi_transfer    ( SPI_parameters_t mySPIparameters, uint8_t* spi_tx_buff, uint32_t spi_tx_length, uint8_t* spi_rx_buff, uint32_t spi_rx_length );
spi_status_t    spi_init        ( SPI_parameters_t mySPIparameters );


#ifdef __cplusplus
}
#endif

#endif /* SPI_H_ */
