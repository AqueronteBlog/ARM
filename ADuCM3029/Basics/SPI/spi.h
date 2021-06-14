/**
 * @brief       SPI.h
 * @details     [todo]ADUCM3029 SPI function libraries.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        11/October/2020
 * @version     11/October/2020    The ORIGIN
 * @pre         N/A
 * @warning     This file is ONLY for ADUCM3029 device.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include <system_ADuCM3029.h>

#ifndef ADUCM3029_SPI_H_
#define ADUCM3029_SPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    SPI_TIMEOUT    =   232323
} spi_timeouts_t;


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
    SPI_SUCCESS  	     			=   0x00,
    SPI_FAILURE  		 			=   0x01,
	SPI_ERROR_FREQUENCY_TOO_LOW		=   0x02,
	SPI_ERROR_FREQUENCY_TOO_HIGH  	=   0x03
} spi_status_t;


/**
  * @brief   SPI PARAMETERS
  */
typedef struct{
    /* Port for pins: MISO, MOSI, SCLK and CS  */
	ADI_GPIO_TypeDef* misoPort;
	ADI_GPIO_TypeDef* mosiPort;
	ADI_GPIO_TypeDef* sclkPort;
	ADI_GPIO_TypeDef* csPort;

    /* Pin number  */
    uint32_t miso;
    uint32_t mosi;
    uint32_t sclk;
    uint32_t cs;

    /* SPI frequency in Hz   */
    uint32_t freq;

    /* SPI instance  */
    ADI_SPI_TypeDef* SPIInstance;

    /* Core clock that drives the SPI peripheral in Hz	 */
    uint32_t pclkFrequency;

    /* SPI Mode */
    spi_modes_t SPImode;

    /* SPI Chip Select enable line mode */
    spi_cs_enable_line_t SPIenable_line_mode;

    /* SPI Byte order */
    spi_byte_order_t SPIbyte_order;
} spi_parameters_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** SPI write/read function.
  */
spi_status_t	spi_transfer	( spi_parameters_t mySPIparameters, uint8_t* spi_tx_buff, uint32_t spi_tx_length, uint8_t* spi_rx_buff, uint32_t spi_rx_length );

/** SPI init function.
  */
spi_status_t    spi_init        ( spi_parameters_t mySPIparameters );


#ifdef __cplusplus
}
#endif

#endif /* ADUCM3029_SPI_H_ */
