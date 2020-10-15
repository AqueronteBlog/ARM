/**
 * @brief       LIS3DHH.c
 * @details     3D Low Frequency Wakeup Receiver.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        11/October/2020
 * @version     11/October/2020    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */

#include "LIS3DHH.h"


/**
 * @brief       LIS3DHH_Init   ( spi_parameters_t )
 *
 * @details     It configures the SPI pins.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of LIS3DHH_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        14/October/2020
 * @version     14/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_Init ( spi_parameters_t mySPI_parameters )
{
    spi_status_t mySPI_status;


    /* Configure the SPI peripheral	 */
    mySPI_status     =   spi_init ( mySPI_parameters );




    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}



/**
 * @brief       LIS3DHH_GetDeviceIdentification ( spi_parameters_t , LIS3DHH_data_t* )
 *
 * @details     It gets the device identification.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   myID:				Device identifier.
 *
 *
 * @return       Status of LIS3DHH_GetDeviceIdentification.
 *
 *
 * @author      Manuel Caballero
 * @date        14/October/2020
 * @version     14/October/2020   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_GetDeviceIdentification ( spi_parameters_t mySPI_parameters, LIS3DHH_data_t* myID )
{
	uint8_t      cmd   =    ( LIS3DHH_READ | LIS3DHH_WHO_AM_I );
	spi_status_t mySPI_status;


    /* Read the device identifier	 */
    mySPI_status	 =   spi_transfer ( mySPI_parameters, &cmd, 1U, (uint8_t*)(&myID->who_am_i), 1U );





    if ( mySPI_status == SPI_SUCCESS )
    {
        return   LIS3DHH_SUCCESS;
    }
    else
    {
        return   LIS3DHH_FAILURE;
    }
}
