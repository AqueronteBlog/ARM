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
 * @brief       MAX7219_Init   ( SPI_mod_parameters_t )
 *
 * @details     It configures the SPI pins and put the device in shutdown mode.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of MAX7219_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        28/September/2017
 * @version     1/October/2017      The abstraction was improved
 *              28/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
MAX7219_status_t  MAX7219_Init ( SPI_mod_parameters_t mySPI_parameters )
{
    spi_mod_status_t    mySPI_status;
    MAX7219_status_t    myMAX7219_status;


    // Configure the SPI peripheral
    mySPI_status     =   spi_mod_init ( mySPI_parameters );


    // Put the device in shutdown mode
    myMAX7219_status =   MAX7219_Mode ( mySPI_parameters, SHUTDOWN_MODE );




    if ( ( mySPI_status == SPI_MOD_SUCCESS ) && ( myMAX7219_status == MAX7219_SUCCESS ) )
       return   MAX7219_SUCCESS;
    else
       return   MAX7219_FAILURE;
}



/**
 * @brief       MAX7219_Mode   ( SPI_mod_parameters_t , MAX7219_shutdown_reg_t )
 *
 * @details     It puts the device in shutdown mode.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myMAX7219mode:     Shutdown or Normal operation mode.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of MAX7219_Mode.
 *
 *
 * @author      Manuel Caballero
 * @date        29/September/2017
 * @version     1/October/2017      The abstraction was improved, the name was changed, now one function is useful for two
 *                                  purpose: Shutdown/Normal operation mode.
 *              29/September/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
MAX7219_status_t  MAX7219_Mode  ( SPI_mod_parameters_t mySPI_parameters, MAX7219_shutdown_reg_t myMAX7219mode )
{
    uint8_t  cmd[]   =    { SHUTDOWN, 0 };

    spi_mod_status_t           mySPI_status;


    cmd[ 1 ]     =   myMAX7219mode;


    mySPI_status =   spi_mod_transfer ( mySPI_parameters.SPIinstance, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0, mySPI_parameters.CS, mySPI_parameters.CSport );



    if ( mySPI_status == SPI_MOD_SUCCESS )
       return   MAX7219_SUCCESS;
    else
       return   MAX7219_FAILURE;
}



/**
 * @brief       MAX7219_DisplayTest   ( SPI_mod_parameters_t , MAX7219_display_test_reg_t )
 *
 * @details     It turns all the LEDs on ( Test mode enabled ) or normal operation.
 *
 * @param[in]    mySPI_parameters:          SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myMAX7219DisplayTestMode:  Mode: Test or Normal operation.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of MAX7219_DisplayTest.
 *
 *
 * @author      Manuel Caballero
 * @date        3/October/2017
 * @version     3/October/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
MAX7219_status_t  MAX7219_DisplayTest ( SPI_mod_parameters_t mySPI_parameters, MAX7219_display_test_reg_t myMAX7219DisplayTestMode )
{
    uint8_t  cmd[]   =    { DISPLAY_TEST, 0 };

    spi_mod_status_t           mySPI_status;


    cmd[ 1 ]     =   myMAX7219DisplayTestMode;


    mySPI_status =   spi_transfer ( mySPI_parameters.SPIinstance, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0, mySPI_parameters.CS, mySPI_parameters.CSport );



    if ( mySPI_status == SPI_MOD_SUCCESS )
       return   MAX7219_SUCCESS;
    else
       return   MAX7219_FAILURE;
}



/**
 * @brief       MAX7219_DecodeMode   ( SPI_mod_parameters_t , MAX7219_decode_mode_reg_t )
 *
 * @details     It enables and configures the decode-mode or turns it off.
 *
 * @param[in]    mySPI_parameters:      SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myMAX7219DecodeMode:   Decode-mode option.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of MAX7219_DecodeMode.
 *
 *
 * @author      Manuel Caballero
 * @date        3/October/2017
 * @version     3/October/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
MAX7219_status_t  MAX7219_DecodeMode ( SPI_mod_parameters_t mySPI_parameters, MAX7219_decode_mode_reg_t myMAX7219DecodeMode )
{
    uint8_t  cmd[]   =    { DECODE_MODE, 0 };

    spi_mod_status_t           mySPI_status;


    cmd[ 1 ]     =   myMAX7219DecodeMode;


    mySPI_status =   spi_transfer ( mySPI_parameters.SPIinstance, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0, mySPI_parameters.CS, mySPI_parameters.CSport );



    if ( mySPI_status == SPI_MOD_SUCCESS )
       return   MAX7219_SUCCESS;
    else
       return   MAX7219_FAILURE;
}



/**
 * @brief       MAX7219_SetIntensity   ( SPI_mod_parameters_t , MAX7219_intensity_reg_t )
 *
 * @details     It configures the intensity of the device.
 *
 * @param[in]    mySPI_parameters:      SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    myMAX7219Intensity:    Intensity option.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of MAX7219_SetIntensity.
 *
 *
 * @author      Manuel Caballero
 * @date        3/October/2017
 * @version     3/October/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
MAX7219_status_t  MAX7219_SetIntensity ( SPI_mod_parameters_t mySPI_parameters, MAX7219_intensity_reg_t myMAX7219Intensity )
{
    uint8_t  cmd[]   =    { INTENSITY, 0 };

    spi_mod_status_t           mySPI_status;


    cmd[ 1 ]     =   myMAX7219Intensity;


    mySPI_status =   spi_transfer ( mySPI_parameters.SPIinstance, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0, mySPI_parameters.CS, mySPI_parameters.CSport );



    if ( mySPI_status == SPI_MOD_SUCCESS )
       return   MAX7219_SUCCESS;
    else
       return   MAX7219_FAILURE;
}



/**
 * @brief       MAX7219_SetScanLimit   ( SPI_mod_parameters_t , MAX7219_scan_limit_reg_t )
 *
 * @details     It configures duty cycle of the device.
 *
 * @param[in]    mySPI_parameters:          SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    MAX7219_scan_limit_reg_t:  Duty cycle option.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of MAX7219_SetScanLimit.
 *
 *
 * @author      Manuel Caballero
 * @date        3/October/2017
 * @version     3/October/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
MAX7219_status_t  MAX7219_SetScanLimit ( SPI_mod_parameters_t mySPI_parameters, MAX7219_scan_limit_reg_t myMAX7219ScanLimit )
{
    uint8_t  cmd[]   =    { SCAN_LIMIT, 0 };

    spi_mod_status_t           mySPI_status;


    cmd[ 1 ]     =   myMAX7219ScanLimit;


    mySPI_status =   spi_transfer ( mySPI_parameters.SPIinstance, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0, mySPI_parameters.CS, mySPI_parameters.CSport );



    if ( mySPI_status == SPI_MOD_SUCCESS )
       return   MAX7219_SUCCESS;
    else
       return   MAX7219_FAILURE;
}
