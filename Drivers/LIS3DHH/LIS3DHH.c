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
 * @details     It configures the SPI pins and resets all the LIS3DHH register ( default value ) and resets its status.
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
 * @date        22/February/2018
 * @version     27/February/2018   PRESET_DEFAULT and CLEAR_WAKE functions were added.
 *              22/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
LIS3DHH_status_t  LIS3DHH_Init ( spi_parameters_t mySPI_parameters )
{
    uint8_t             cmd   =    0;
    spi_status_t        mySPI_status;


    // Configure the SPI peripheral
    mySPI_status     =   spi_init ( mySPI_parameters );




    if ( mySPI_status == SPI_SUCCESS )
        return   LIS3DHH_SUCCESS;
    else
        return   LIS3DHH_FAILURE;
}
