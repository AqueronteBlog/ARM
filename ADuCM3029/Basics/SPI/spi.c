/**
 * @brief       spi.c
 * @details     ADUCM3029 SPI function libraries.
 *              Function file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        11/October/2020
 * @version     11/October/2020    The ORIGIN
 * @pre         N/A
 * @warning     This file is ONLY for ADUCM3029 device.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "spi.h"

/**
 * @brief       spi_init   ( spi_parameters_t )
 *
 * @details     It configures the SPI peripheral.
 *
 * @param[in]    mySPIparameters:       SPI parameters.
 *
 * @param[out]   Status of SPI_init.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        11/October/2020
 * @version     08/November/2020    GPIO configuration was added.
 * 				11/October/2020     The ORIGIN
 * @pre         N/A.
 * @pre         This function only takes into consideration the multiplexed function 1.
 * @warning     N/A.
 */
spi_status_t spi_init ( spi_parameters_t mySPIparameters )
{
	/* Multiplexed function 1 for SPI peripheral ( MOSI, MISO, SCLK and CS )	 */
	mySPIparameters.mosiPort->CFG	&=	~( 0b11 << ( mySPIparameters.mosi << 1U ) );
	mySPIparameters.mosiPort->CFG	|=	 ( 0b01 << ( mySPIparameters.mosi << 1U ) );

	mySPIparameters.misoPort->CFG	&=	~( 0b11 << ( mySPIparameters.miso << 1U ) );
	mySPIparameters.misoPort->CFG	|=	 ( 0b01 << ( mySPIparameters.miso << 1U ) );

	mySPIparameters.sclkPort->CFG	&=	~( 0b11 << ( mySPIparameters.sclk << 1U ) );
	mySPIparameters.sclkPort->CFG	|=	 ( 0b01 << ( mySPIparameters.sclk << 1U ) );

	mySPIparameters.csPort->CFG		&=	~( 0b11 << ( mySPIparameters.cs << 1U ) );
	mySPIparameters.csPort->CFG		|=	 ( 0b01 << ( mySPIparameters.cs << 1U ) );

	/* Peripheral configured successfully	 */
	return SPI_SUCCESS;
}



/**
 * @brief       spi_transfer ( spi_parameters_t , uint8_t* , uint32_t , uint8_t* , uint32_t  )
 *
 * @details     Send/Receive data through the SPI bus.
 *
 * @param[in]    mySPI_parameters:      SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    spi_tx_buff:           Data to be transmitted through SPI bus.
 * @param[in]    spi_tx_length:         Amount of data to be transmitted through SPI bus.
 * @param[in]    spi_rx_length:         Amount of data to be read through SPI bus.
 *
 * @param[out]   spi_rx_buff:           Data from the SPI bus.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        07/October/2020
 * @version     08/November/2020    SPI ON/OFF was added.
 * 				07/October/2020     The ORIGIN
 * @pre         SPI communication is by polling mode.
 * @warning     N/A.
 */
spi_status_t spi_transfer ( spi_parameters_t mySPIparameters, uint8_t* spi_tx_buff, uint32_t spi_tx_length, uint8_t* spi_rx_buff, uint32_t spi_rx_length )
{
	/* Turn on the SPI	 */
	mySPIparameters.SPIInstance->CTL	|=	 ( 1U << BITP_SPI_CTL_SPIEN );



	/* Turn off the SPI	 */
	mySPIparameters.SPIInstance->CTL	&=	~( 1U << BITP_SPI_CTL_SPIEN );


	/* Peripheral configured successfully	 */
	return SPI_SUCCESS;
}
