/**
 * @brief       spi.c
 * @details     NRF52 SPI function libraries.
 *              Function file.
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

#include "spi.h"


/**
 * @brief       spi_transfer   ( SPI_parameters_t , uint8_t* , uint32_t , uint8_t* , uint32_t )
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
 * @return      Status of spi_transfer
 *
 *
 * @author      Manuel Caballero
 * @date        26/April/2019
 * @version     26/April/2019   The ORIGIN
 * @pre         SPI communication is by polling mode.
 * @warning     N/A.
 */
spi_status_t    spi_transfer ( SPI_parameters_t mySPIparameters, uint8_t* spi_tx_buff, uint32_t spi_tx_length, uint8_t* spi_rx_buff, uint32_t spi_rx_length )
{
    uint32_t     i                   =   0;
    uint32_t     spi_timeout1        =   232323;
    uint32_t     spi_timeout2        =   232323;

    /* Start SPI communication */
    if ( mySPIparameters.SPIenable_line_mode    ==   SPI_ENABLE_LINE_LOW )
    {
        mySPIparameters.CSport->OUTCLR    =   ( 1UL << mySPIparameters.CS );          // Chip Select LOW
    }
    else
    {
        mySPIparameters.CSport->OUTSET    =   ( 1UL << mySPIparameters.CS );          // Chip Select HIGH
    }


    //for( i = 0; i < 4500; i++ );



    /* SPI TX */
    for ( i = 0; i < spi_tx_length; i++ ){
        mySPIparameters.SPIinstance->TXD     =   *spi_tx_buff++;                                // Send data

        spi_timeout1                =   232323;
        while( ( mySPIparameters.SPIinstance->EVENTS_READY == 0 ) && ( --spi_timeout1 ) );      // Wait until the data is transmitted or timeout1
        *spi_rx_buff                =   mySPIparameters.SPIinstance->RXD;                       // Dummy value
        mySPIparameters.SPIinstance->EVENTS_READY    =   0;                                     // reset flag
    }

    /* SPI RX */
    for ( i = 0; i < spi_rx_length; i++ ){
        mySPIparameters.SPIinstance->TXD     =   0x00;                                          // Dummy value

        spi_timeout2                =   232323;
        while( ( mySPIparameters.SPIinstance->EVENTS_READY == 0 ) && ( --spi_timeout2 ) );      // Wait until the data is transmitted or timeout2
        *spi_rx_buff++             =   mySPIparameters.SPIinstance->RXD;                        // Get data
        mySPIparameters.SPIinstance->EVENTS_READY    =   0;                                     // reset flag
    }


    /* End SPI communication. Release the bus  */
    if ( mySPIparameters.SPIenable_line_mode    ==   SPI_ENABLE_LINE_LOW )
    {
        mySPIparameters.CSport->OUTSET    =   ( 1UL << mySPIparameters.CS );
    }
    else
    {
        mySPIparameters.CSport->OUTCLR    =   ( 1UL << mySPIparameters.CS );
    }


    /* Check if everything went fine */
    if ( ( spi_timeout1 < 1 ) || ( spi_timeout2 < 1 ) )
        return SPI_FAILURE;
    else
        return SPI_SUCCESS;
}



/**
 * @brief       spi_init     ( SPI_parameters_t )
 *
 * @details     It configures the SPI peripheral.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of spi_init
 *
 *
 * @author      Manuel Caballero
 * @date        26/April/2019
 * @version     26/April/2019      The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
spi_status_t    spi_init     ( SPI_parameters_t mySPIparameters )
{
    uint8_t mySPI_CPOL          =   0;
    uint8_t mySPI_CPHA          =   0;
    uint8_t mySPI_ByteOrder     =   0;


// CONFIGURE THE PINOUT AND ENABLE THE SPI
    /* Configure the Chip Select ( CS ) */
    mySPIparameters.CSport->PIN_CNF[ mySPIparameters.CS ]   =   ( GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos    ) |
                                                                ( GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos  ) |
                                                                ( GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos   ) |
                                                                ( GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos  ) |
                                                                ( GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos  );

    /* Release the SPI's bus */
    if ( mySPIparameters.SPIenable_line_mode == SPI_ENABLE_LINE_LOW )
    {
        mySPIparameters.CSport->OUTSET    =   ( 1UL << mySPIparameters.CS );
    }
    else
    {
        mySPIparameters.CSport->OUTCLR    =   ( 1UL << mySPIparameters.CS );
    }



    /* GPIO according to Table 122: GPIO configuration ( Reference Manual p.514 ) */
    mySPIparameters.MOSIport->OUTSET        =   ( 0 << mySPIparameters.MOSI );
    mySPIparameters.SCLKport->OUTSET        =   ( 0 << mySPIparameters.SCLK );
    mySPIparameters.MISOport->DIRCLR        =   ( 1 << mySPIparameters.MISO );
    mySPIparameters.MOSIport->DIRSET        =   ( 1 << mySPIparameters.MOSI );
    mySPIparameters.SCLKport->DIRSET        =   ( 1 << mySPIparameters.SCLK );

    /* Disable the SPI */
    mySPIparameters.SPIinstance->ENABLE     =   ( SPI_ENABLE_ENABLE_Disabled << SPI_ENABLE_ENABLE_Pos );

    /* Configure the SPI behavior */
    // SPI Mode
    switch ( mySPIparameters.SPImode ){
    default:
    case SPI_MODE_0:
            mySPI_CPOL   =   SPI_CONFIG_CPOL_ActiveHigh;
            mySPI_CPHA   =   SPI_CONFIG_CPHA_Leading;
            break;

    case SPI_MODE_1:
            mySPI_CPOL   =   SPI_CONFIG_CPOL_ActiveHigh;
            mySPI_CPHA   =   SPI_CONFIG_CPHA_Trailing;
            break;

    case SPI_MODE_2:
            mySPI_CPOL   =   SPI_CONFIG_CPOL_ActiveLow;
            mySPI_CPHA   =   SPI_CONFIG_CPHA_Leading;
            break;

    case SPI_MODE_3:
            mySPI_CPOL   =   SPI_CONFIG_CPOL_ActiveLow;
            mySPI_CPHA   =   SPI_CONFIG_CPHA_Trailing;
            break;
    }

    // SPI Byte order
    if ( mySPIparameters.SPIbyte_order  ==  SPI_ORDER_MSB_FIRST )
    {
        mySPI_ByteOrder  =   SPI_CONFIG_ORDER_MsbFirst;
    }
    else
    {
        mySPI_ByteOrder  =   SPI_CONFIG_ORDER_LsbFirst;
    }


    mySPIparameters.SPIinstance->CONFIG     =   ( mySPI_ByteOrder   << SPI_CONFIG_ORDER_Pos ) |
                                                ( mySPI_CPHA        << SPI_CONFIG_CPHA_Pos  ) |
                                                ( mySPI_CPOL        << SPI_CONFIG_CPOL_Pos  );

    /* Configure the frequency */
    mySPIparameters.SPIinstance->FREQUENCY  =   ( mySPIparameters.Freq << SPI_FREQUENCY_FREQUENCY_Pos );

    /* Configure the pins */
    mySPIparameters.SPIinstance->PSELSCK    =   mySPIparameters.SCLK;
    mySPIparameters.SPIinstance->PSELMOSI   =   mySPIparameters.MOSI;
    mySPIparameters.SPIinstance->PSELMISO   =   mySPIparameters.MISO;


    /* Disable interrupt */
    mySPIparameters.SPIinstance->INTENSET   =   ( SPI_INTENCLR_READY_Clear << SPI_INTENCLR_READY_Pos );

    /* Enable the SPI */
    mySPIparameters.SPIinstance->ENABLE     =   ( SPI_ENABLE_ENABLE_Enabled << SPI_ENABLE_ENABLE_Pos );


    return SPI_SUCCESS;
}
