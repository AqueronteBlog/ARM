/**
 * @brief       MAX7219.c
 * @details     Serially Interfaced, 8-Digit LED Display Drivers.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        28/September/2017
 * @version     28/September/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

 #include "MAX7219.h"


/**
 * @brief       MAX7219_Init   ( NRF_SPI_Type* , uint32_t , uint32_t , uint32_t , uint32_t )
 *
 * @details     It configures the SPI pins and put the device in shutdown mode.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin and SPI frequency.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of MAX7219_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        28/September/2017
 * @version     28/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
MAX7219_status_t  MAX7219_Init ( MAX7219_spi_parameters_t mySPI_parameters )
{
   spi_status_t    mySPI_status;


// CONFIGURE THE PINOUT AND ENABLE THE SPI
    /* Configure the Chip Select ( CS ) */
    NRF_GPIO->OUTSET                           =   ( 1 << mySPI_parameters.CS );                                                  // Release the SPI's bus
    NRF_GPIO->PIN_CNF[ mySPI_parameters.CS ]   =   ( GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos    ) |
                                                   ( GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos  ) |
                                                   ( GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos   ) |
                                                   ( GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos  ) |
                                                   ( GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos  );



    /* GPIO according to Table 221: GPIO configuration ( Reference Manual p.133 ) */
    NRF_GPIO->OUTSET             =   ( 0 << mySPI_parameters.MOSI );
    NRF_GPIO->OUTSET             =   ( 0 << mySPI_parameters.SCLK );
    NRF_GPIO->DIRCLR             =   ( 1 << mySPI_parameters.MISO );
    NRF_GPIO->DIRSET             =   ( 1 << mySPI_parameters.MOSI );
    NRF_GPIO->DIRSET             =   ( 1 << mySPI_parameters.SCLK );

    /* Disable the SPI */
    mySPI_parameters.SPIinstance->ENABLE        =   ( SPI_ENABLE_ENABLE_Disabled << SPI_ENABLE_ENABLE_Pos );

    /* Configure the SPI behavior */
    mySPI_parameters.SPIinstance->CONFIG        =   ( SPI_CONFIG_ORDER_MsbFirst     << SPI_CONFIG_ORDER_Pos ) |
                                                    ( SPI_CONFIG_CPHA_Leading       << SPI_CONFIG_CPHA_Pos  ) |
                                                    ( SPI_CONFIG_CPOL_ActiveHigh    << SPI_CONFIG_CPOL_Pos  );

    /* Configure the frequency */
    mySPI_parameters.SPIinstance->FREQUENCY     =   ( mySPI_parameters.Freq << SPI_FREQUENCY_FREQUENCY_Pos );

    /* Configure the pins */
    mySPI_parameters.SPIinstance->PSELSCK       =   mySPI_parameters.SCLK;
    mySPI_parameters.SPIinstance->PSELMOSI      =   mySPI_parameters.MOSI;
    mySPI_parameters.SPIinstance->PSELMISO      =   mySPI_parameters.MISO;


    /* Disable interrupt */
    mySPI_parameters.SPIinstance->INTENSET      =   ( SPI_INTENCLR_READY_Clear << SPI_INTENCLR_READY_Pos );

    /* Enable the SPI */
    mySPI_parameters.SPIinstance->ENABLE        =   ( SPI_ENABLE_ENABLE_Enabled << SPI_ENABLE_ENABLE_Pos );


// PUT THE DEVICE IN SHUTDOWN MODE
    mySPI_status     =   MAX7219_Shutdown ( mySPI_parameters );






    if ( mySPI_status == SPI_SUCCESS )
       return   MAX7219_SUCCESS;
    else
       return   MAX7219_FAILURE;
}



/**
 * @brief       MAX7219_Shutdown   ( NRF_SPI_Type* )
 *
 * @details     It puts the device in shutdown mode.
 *
 * @param[in]    myinstance:    Peripheral's Instance.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of MAX7219_Shutdown.
 *
 *
 * @author      Manuel Caballero
 * @date        29/September/2017
 * @version     29/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
MAX7219_status_t  MAX7219_Shutdown ( MAX7219_spi_parameters_t mySPI_parameters )
{
    uint8_t  cmd[]              =    { 0x0F, 1 };

    spi_status_t    mySPI_status;


    mySPI_status     =   spi_transfer ( mySPI_parameters.SPIinstance, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0, mySPI_parameters.CS );



    if ( mySPI_status == SPI_SUCCESS )
       return   MAX7219_SUCCESS;
    else
       return   MAX7219_FAILURE;
}
