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
 * @version     11/November/2020    SPI configuration was completed.
 * 				08/November/2020    GPIO configuration was added.
 * 				11/October/2020     The ORIGIN
 * @pre         N/A.
 * @pre         This function only takes into consideration the multiplexed function 1.
 * @pre         This function only takes into consideration CS0 as a chip select.
 * @warning     N/A.
 */
spi_status_t spi_init ( spi_parameters_t mySPIparameters )
{
	/* Make sure the SPI is not in use	 */ // [todo] add a counter for sefty
	do{

	}while( ( mySPIparameters.SPIInstance->STAT & ( 1U << BITP_SPI_STAT_XFRDONE ) ) != ( 1U << BITP_SPI_STAT_XFRDONE ) );

	/* Disable the SPI peripheral	 */
	mySPIparameters.SPIInstance->CTL	&=	~( 1U << BITP_SPI_CTL_SPIEN );

	/* Multiplexed function 1 for SPI peripheral ( MOSI, MISO, SCLK and CS )	 */
	mySPIparameters.mosiPort->CFG	&=	~( 0b11 << ( mySPIparameters.mosi << 1U ) );
	mySPIparameters.mosiPort->CFG	|=	 ( 0b01 << ( mySPIparameters.mosi << 1U ) );

	mySPIparameters.misoPort->CFG	&=	~( 0b11 << ( mySPIparameters.miso << 1U ) );
	mySPIparameters.misoPort->CFG	|=	 ( 0b01 << ( mySPIparameters.miso << 1U ) );

	mySPIparameters.sclkPort->CFG	&=	~( 0b11 << ( mySPIparameters.sclk << 1U ) );
	mySPIparameters.sclkPort->CFG	|=	 ( 0b01 << ( mySPIparameters.sclk << 1U ) );

	mySPIparameters.csPort->CFG		&=	~( 0b11 << ( mySPIparameters.cs << 1U ) );
	mySPIparameters.csPort->CFG		|=	 ( 0b01 << ( mySPIparameters.cs << 1U ) );

	/* SPI: Chip select active mode	 */
	mySPIparameters.SPIInstance->CS_OVERRIDE	&=	~( 0b11 << BITP_SPI_CS_OVERRIDE_CTL );
	if ( mySPIparameters.SPIenable_line_mode == SPI_ENABLE_LINE_HIGH )
	{
		/* CS is forced to drive 'LOW'	 */
		mySPIparameters.SPIInstance->CS_OVERRIDE	|=	 ( 0b10 << BITP_SPI_CS_OVERRIDE_CTL );
	}

	/* SPI: MSB or LSB transmitted first	 */
	mySPIparameters.SPIInstance->CTL	&=	~( 1U << BITP_SPI_CTL_LSB );
	if ( mySPIparameters.SPIbyte_order == SPI_ORDER_LSB_FIRST )
	{
		mySPIparameters.SPIInstance->CTL	|=	 ( 1U << BITP_SPI_CTL_LSB );
	}

	/* SPI: Set CS0 is used always	 */
	mySPIparameters.SPIInstance->CS_CTL	&=	~( 0b1111 << BITP_SPI_CS_CTL_SEL );

	/* SPI: Set working mode according to CPHA and CPOL	 */
	mySPIparameters.SPIInstance->CTL	&=	~( ( 1U << BITP_SPI_CTL_CPOL ) | ( 1U << BITP_SPI_CTL_CPHA ) );
	switch ( mySPIparameters.SPImode )
	{
	default:
	case SPI_MODE_0:
		/* SPI MODE 0: CPOL 0 | CPHA 0	 */
		break;

	case SPI_MODE_1:
		/* SPI MODE 0: CPOL 0 | CPHA 1	 */
		mySPIparameters.SPIInstance->CTL	|=	 ( 1U << BITP_SPI_CTL_CPHA );
		break;

	case SPI_MODE_2:
		/* SPI MODE 0: CPOL 1 | CPHA 0	 */
		mySPIparameters.SPIInstance->CTL	|=	 ( 1U << BITP_SPI_CTL_CPOL );
		break;

	case SPI_MODE_3:
		/* SPI MODE 0: CPOL 1 | CPHA 1	 */
		mySPIparameters.SPIInstance->CTL	|=	 ( ( 1U << BITP_SPI_CTL_CPOL ) | ( 1U << BITP_SPI_CTL_CPHA ) );
		break;
	}

	/* SPI: 4-pin interface	 */
	mySPIparameters.SPIInstance->RD_CTL	&=	~( 1U << BITP_SPI_RD_CTL_THREEPIN );

	/* SPI: Master mode enabled	 */
	mySPIparameters.SPIInstance->CTL	|=	 ( 1U << BITP_SPI_CTL_MASEN );

	/* SPI: No DMA for transfer data	 */
	mySPIparameters.SPIInstance->DMA	&=	~( 1U << BITP_SPI_DMA_EN );

	/* SPI: All interrupts are disabled	 */
	mySPIparameters.SPIInstance->IEN	&=	~( ( 1U << BITP_SPI_IEN_TXEMPTY ) | ( 1U << BITP_SPI_IEN_XFRDONE ) | ( 1U << BITP_SPI_IEN_TXDONE ) | ( 1U << BITP_SPI_IEN_RDY ) | ( 1U << BITP_SPI_IEN_RXOVR ) | ( 1U << BITP_SPI_IEN_TXUNDR ) | ( 1U << BITP_SPI_IEN_CS ) );

	/* SPI: Reset all the STATUS flags	 */
	mySPIparameters.SPIInstance->STAT	|=	 ( ( 1U << BITP_SPI_STAT_RDY ) | ( 1U << BITP_SPI_STAT_CSFALL ) | ( 1U << BITP_SPI_STAT_CSRISE ) | ( 1U << BITP_SPI_STAT_CSERR ) | ( 1U << BITP_SPI_STAT_RXOVR ) | ( 1U << BITP_SPI_STAT_RXIRQ ) | ( 1U << BITP_SPI_STAT_TXIRQ ) | ( 1U << BITP_SPI_STAT_TXUNDR ) | ( 1U << BITP_SPI_STAT_TXDONE ) | ( 1U << BITP_SPI_STAT_TXEMPTY ) );


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
