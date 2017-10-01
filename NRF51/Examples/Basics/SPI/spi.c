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



/**
 * @brief       spi_init     ( SPI_parameters_t )
 *
 * @details     It configures the SPI peripheral.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   NaN.
 *
 *
 * @return      Status of spi_init
 *
 *
 * @author      Manuel Caballero
 * @date        1/October/2017
 * @version     1/October/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
spi_status_t    spi_init     ( SPI_parameters_t mySPIparameters )
{
// CONFIGURE THE PINOUT AND ENABLE THE SPI
    /* Configure the Chip Select ( CS ) */
    mySPIparameters.CSport->OUTSET                          =   ( 1 << mySPIparameters.CS );                                                  // Release the SPI's bus
    mySPIparameters.CSport->PIN_CNF[ mySPIparameters.CS ]   =   ( GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos    ) |
                                                                ( GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos  ) |
                                                                ( GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos   ) |
                                                                ( GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos  ) |
                                                                ( GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos  );


    /* GPIO according to Table 221: GPIO configuration ( Reference Manual p.133 ) */
    mySPIparameters.MOSIport->OUTSET        =   ( 0 << mySPIparameters.MOSI );
    mySPIparameters.SCLKport->OUTSET        =   ( 0 << mySPIparameters.SCLK );
    mySPIparameters.MISOport->DIRCLR        =   ( 1 << mySPIparameters.MISO );
    mySPIparameters.MOSIport->DIRSET        =   ( 1 << mySPIparameters.MOSI );
    mySPIparameters.SCLKport->DIRSET        =   ( 1 << mySPIparameters.SCLK );

    /* Disable the SPI */
    mySPIparameters.SPIinstance->ENABLE     =   ( SPI_ENABLE_ENABLE_Disabled << SPI_ENABLE_ENABLE_Pos );

    /* Configure the SPI behavior */
    mySPIparameters.SPIinstance->CONFIG     =   ( SPI_CONFIG_ORDER_MsbFirst     << SPI_CONFIG_ORDER_Pos ) |
                                                ( SPI_CONFIG_CPHA_Leading       << SPI_CONFIG_CPHA_Pos  ) |
                                                ( SPI_CONFIG_CPOL_ActiveHigh    << SPI_CONFIG_CPOL_Pos  );

    /* Configure the frequency */
    mySPIparameters.SPIinstance->FREQUENCY  =   ( mySPIparameters.Freq << SPI_FREQUENCY_FREQUENCY_Pos );

    /* Configure the pins */
    mySPIparameters.SPIinstance->PSELSCK    =   mySPIparameters.SCLK;
    mySPIparameters.SPIinstance->PSELMOSI   =   mySPIparameters.MOSI;
    mySPIparameters.SPIinstance->PSELMISO   =   mySPIparameters.MISO;


    /* Disable interrupt */
    mySPIparameters.SPIinstance->INTENSET      =   ( SPI_INTENCLR_READY_Clear << SPI_INTENCLR_READY_Pos );

    /* Enable the SPI */
    mySPIparameters.SPIinstance->ENABLE        =   ( SPI_ENABLE_ENABLE_Enabled << SPI_ENABLE_ENABLE_Pos );


    return SPI_SUCCESS;
}
