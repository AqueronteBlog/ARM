/**
 * @brief       AS3933.c
 * @details     3D Low Frequency Wakeup Receiver.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/February/2018
 * @version     22/February/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */

#include "AS3933.h"


/**
 * @brief       AS3933_Init   ( SPI_parameters_t )
 *
 * @details     It configures the SPI pins and put the device in shutdown mode.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of AS3933_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        22/February/2018
 * @version     22/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
AS3933_status_t  AS3933_Init ( SPI_parameters_t mySPI_parameters )
{
    spi_status_t        mySPI_status;
    AS3933_status_t    myAS3933_status;


    // Configure the SPI peripheral
    mySPI_status     =   spi_init ( mySPI_parameters );


    // Put the device in shutdown mode





    if ( ( mySPI_status == SPI_SUCCESS ) && ( myAS3933_status == AS3933_SUCCESS ) )
        return   AS3933_SUCCESS;
    else
        return   AS3933_FAILURE;
}
