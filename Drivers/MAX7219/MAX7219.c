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
 * @param[in]    myinstance:    Peripheral's Instance.
 * @param[in]    myMOSIpin:     SPI MOSI pin.
 * @param[in]    myMISOpin:     SPI MISO pin.
 * @param[in]    mySCLKpin:     SPI SCLK ( clock ) pin.
 * @param[in]    myCSpin:       SPI Chip Select pin.
 * @param[in]    mySPI_Freq:    SPI frequency.
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
MAX7219_status_t  MAX7219_Init ( NRF_SPI_Type* myinstance, uint32_t myMOSIpin, uint32_t myMISOpin, uint32_t mySCLKpin, uint32_t myCSpin, uint32_t mySPI_Freq )
{
   spi_status_t    mySPI_status;


// CONFIGURE THE PINOUT AND ENABLE THE SPI
    /* Configure the Chip Select ( CS ) */
    NRF_GPIO->OUTSET               =   ( 1 << myCSpin );                                                  // Release the SPI's bus
    NRF_GPIO->PIN_CNF[ myCSpin ]   =   ( GPIO_PIN_CNF_DIR_Output         <<  GPIO_PIN_CNF_DIR_Pos    ) |
                                       ( GPIO_PIN_CNF_INPUT_Disconnect   <<  GPIO_PIN_CNF_INPUT_Pos  ) |
                                       ( GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos   ) |
                                       ( GPIO_PIN_CNF_DRIVE_S0S1         <<  GPIO_PIN_CNF_DRIVE_Pos  ) |
                                       ( GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos  );



    /* GPIO according to Table 221: GPIO configuration ( Reference Manual p.133 ) */
    NRF_GPIO->OUTSET             =   ( 0 << myMOSIpin );
    NRF_GPIO->OUTSET             =   ( 0 << mySCLKpin );
    NRF_GPIO->DIRCLR             =   ( 1 << myMISOpin );
    NRF_GPIO->DIRSET             =   ( 1 << myMOSIpin );
    NRF_GPIO->DIRSET             =   ( 1 << mySCLKpin );

    /* Disable the SPI */
    myinstance->ENABLE        =   ( SPI_ENABLE_ENABLE_Disabled << SPI_ENABLE_ENABLE_Pos );

    /* Configure the SPI behavior */
    myinstance->CONFIG        =   ( SPI_CONFIG_ORDER_MsbFirst     << SPI_CONFIG_ORDER_Pos ) |
                                  ( SPI_CONFIG_CPHA_Leading       << SPI_CONFIG_CPHA_Pos  ) |
                                  ( SPI_CONFIG_CPOL_ActiveHigh    << SPI_CONFIG_CPOL_Pos  );

    /* Configure the frequency */
    myinstance->FREQUENCY     =   ( mySPI_Freq << SPI_FREQUENCY_FREQUENCY_Pos );

    /* Configure the pins */
    myinstance->PSELSCK       =   mySCLKpin;
    myinstance->PSELMOSI      =   myMOSIpin;
    myinstance->PSELMISO      =   myMISOpin;

    mySPI_CS                  =  myCSpin;
    /* Disable interrupt */
    myinstance->INTENSET      =   ( SPI_INTENCLR_READY_Clear << SPI_INTENCLR_READY_Pos );

    /* Enable the SPI */
    myinstance->ENABLE        =   ( SPI_ENABLE_ENABLE_Enabled << SPI_ENABLE_ENABLE_Pos );


// PUT THE DEVICE IN SHUTDOWN MODE
    mySPI_status     =   MAX7219_Shutdown ( myinstance );






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
MAX7219_status_t  MAX7219_Shutdown ( NRF_SPI_Type* myinstance )
{
    uint8_t  cmd[]              =    { MAX7219_SHUTDOWN, 0 };

    spi_status_t    mySPI_status;

    NRF_GPIO->OUTCLR =   ( 1UL << mySPI_CS );
    mySPI_status     =   spi_transfer ( myinstance, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );
    NRF_GPIO->OUTSET =   ( 1UL << mySPI_CS );        // End communication


    if ( mySPI_status == SPI_SUCCESS )
       return   MAX7219_SUCCESS;
    else
       return   MAX7219_FAILURE;
}
