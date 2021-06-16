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
 * @version     14/November/2020    SPI frequency calculator was added ( errors functionality included ).
 * 				11/November/2020    SPI configuration was completed.
 * 				08/November/2020    GPIO configuration was added.
 * 				11/October/2020     The ORIGIN
 * @pre         N/A.
 * @pre         This function only takes into consideration the multiplexed function 1.
 * @pre         This function only takes into consideration CS0 as a chip select.
 * @warning     N/A.
 */
spi_status_t spi_init ( spi_parameters_t mySPIparameters )
{
	uint32_t spi_frequency_div	 =	 0UL;
	uint32_t spi_frequency_mul	 =	 0UL;

//	/* Make sure the SPI is not in use	 */ // [todo] add a counter for sefty
//	do{
//
//	}while( ( mySPIparameters.SPIInstance->STAT & ( 1U << BITP_SPI_STAT_XFRDONE ) ) != ( 1U << BITP_SPI_STAT_XFRDONE ) );

	/* Disable the SPI peripheral	 */
	mySPIparameters.SPIInstance->CTL	&=	~( 1U << BITP_SPI_CTL_SPIEN );

	/* SPI: Configure the SPI frequency	 */
	if ( mySPIparameters.freq > 13000000UL )
	{
		/* SPI frequency cannot be greater than 13MHz	 */
		return SPI_ERROR_FREQUENCY_TOO_HIGH;
	}
	else
	{
		spi_frequency_mul	 =	 ( mySPIparameters.freq << 1UL );	// SPI_freq * 2
		if ( spi_frequency_mul > mySPIparameters.pclkFrequency )
		{
			return SPI_ERROR_FREQUENCY_TOO_HIGH;
		}
		else
		{
			spi_frequency_div	 =	 (uint32_t)( ( mySPIparameters.pclkFrequency - spi_frequency_mul )/spi_frequency_mul );
			if ( spi_frequency_div > 63UL )
			{
				return SPI_ERROR_FREQUENCY_TOO_LOW;
			}
			else
			{
				mySPIparameters.SPIInstance->DIV	&=	~0x003F;
				mySPIparameters.SPIInstance->DIV	|=	 (uint16_t)( spi_frequency_div << BITP_SPI_DIV_VALUE );

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
			}
		}
	}


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
 * @version     16/November/2020    SPI Tx and Rx were added, timeouts were added too.
 * 				08/November/2020    SPI ON/OFF was added.
 * 				07/October/2020     The ORIGIN
 * @pre         SPI communication is by polling mode.
 * @warning     N/A.
 */
spi_status_t spi_transfer ( spi_parameters_t mySPIparameters, uint8_t* spi_tx_buff, uint32_t spi_tx_length, uint8_t* spi_rx_buff, uint32_t spi_rx_length )
{
	uint32_t i	 			= 0UL;
	uint32_t spi_timeout1	= 0UL;
	uint32_t spi_timeout2   = 0UL;


//	/* Make sure the SPI is not in use	 */ // [todo] add a counter for sefty
//	do{
//
//	}while( ( mySPIparameters.SPIInstance->STAT & ( 1U << BITP_SPI_STAT_XFRDONE ) ) != ( 1U << BITP_SPI_STAT_XFRDONE ) );

	/* Turn on the SPI, Continuous transfer and flush for Tx and Rx FIFO enabled	 */
	mySPIparameters.SPIInstance->CTL	|=	 ( ( 1U << BITP_SPI_CTL_SPIEN ) | ( 1U << BITP_SPI_CTL_TFLUSH ) | ( 1U << BITP_SPI_CTL_RFLUSH ) );

	/* Frame disabled	 */
	mySPIparameters.SPIInstance->CNT	&=	~( 1U << BITP_SPI_CNT_FRAMECONT );


	/* SPI: Transmit data	 */
	mySPIparameters.SPIInstance->CTL	&=	~( 1U << BITP_SPI_CTL_TFLUSH );				// Flush for Tx disabled
	mySPIparameters.SPIInstance->CTL	|=	 ( 1U << BITP_SPI_CTL_TIM );				// Initiate transfer with a write to the SPI_TX register.
	//mySPIparameters.SPIInstance->CNT	|=	 ( spi_tx_length << BITP_SPI_CNT_VALUE );	// Bytes to be transfered

	mySPIparameters.SPIInstance->RD_CTL	|=	 ( 1U << BITP_SPI_RD_CTL_CMDEN );			// Read mode command is enabled [todo] this can go to spi_init function


	for ( i = 0UL; i < spi_tx_length; i++ )
	{
		spi_timeout1	 =	 232323UL;
		while( ( ( mySPIparameters.SPIInstance->FIFO_STAT & ( 1U << BITP_SPI_FIFO_STAT_TX ) ) != ( 1U << BITP_SPI_FIFO_STAT_TX ) ) && ( --spi_timeout1 ) );      // Wait until the TX FIFO is empty or timeout1
		mySPIparameters.SPIInstance->TX	 =	 *spi_tx_buff++;                            // Send byte

		spi_timeout1	 =	 232323UL;
		while( ( ( mySPIparameters.SPIInstance->STAT & ( 1U << BITP_SPI_STAT_TXDONE ) ) != ( 1U << BITP_SPI_STAT_TXDONE ) ) && ( --spi_timeout1 ) );      // Wait until the data is transmitted or timeout1
		mySPIparameters.SPIInstance->STAT	|=	 ( 1U << BITP_SPI_STAT_TXDONE );		// Clear the flag
	}

	/* SPI: Receive data	 */
	mySPIparameters.SPIInstance->CTL	|=	 ( 1U << BITP_SPI_CTL_TFLUSH );				// Flush for Tx enabled
	mySPIparameters.SPIInstance->CTL	&=	~( 1U << BITP_SPI_CTL_RFLUSH );				// Flush for Rx disabled
	mySPIparameters.SPIInstance->CTL	&=	~( 1U << BITP_SPI_CTL_TIM );				// initiate transfer with a read of the SPI_RX register.
	mySPIparameters.SPIInstance->CNT	|=	 ( spi_rx_length << BITP_SPI_CNT_VALUE );	// Bytes to be transfered

	for ( i = 0UL; i < spi_rx_length; i++ )
	{
		*spi_rx_buff++	 =   mySPIparameters.SPIInstance->RX;							// Read byte

		spi_timeout2	 =	 232323UL;
		while( ( ( mySPIparameters.SPIInstance->STAT & ( 1U << BITP_SPI_STAT_RXIRQ ) ) != ( 1U << BITP_SPI_STAT_RXIRQ ) ) && ( --spi_timeout2 ) );      // Wait until the data is received or timeout2
		mySPIparameters.SPIInstance->STAT	|=	 ( 1U << BITP_SPI_STAT_RXIRQ );			// Clear the flag
	}




	/* Turn off the SPI	 */
	mySPIparameters.SPIInstance->CTL	&=	~( 1U << BITP_SPI_CTL_SPIEN );


	/* Check if everything went fine */
	if ( ( spi_timeout1 < 1UL ) || ( spi_timeout2 < 1UL ) )
	{
		return SPI_FAILURE;
	}
	else
	{
		return SPI_SUCCESS;
	}
}
