/**
 * @brief       SX128X.c
 * @details     SX1280/SX1281. Long Range, Low Power, 2.4 GHz Transceiver with Ranging Capability.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        29/January/2019
 * @version     29/January/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ). All rights reserved.
 */

#include "SX128X.h"


/**
 * @brief       SX128X_Init ( SPI_parameters_t )
 *
 * @details     It configures the SPI peripheral.
 *
 * @param[in]    mySPI_parameters:       SPI parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SX128X_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        22/January/2019
 * @version     22/January/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SX128X_status_t  SX128X_Init ( SPI_parameters_t mySPI_parameters )
{
    spi_status_t aux;

    aux  =   spi_init ( mySPI_parameters );



    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}



/**
 * @brief       GetStatus ( SPI_parameters_t, SX128X_data_t* )
 *
 * @details     It gets the transceiver status.
 *
 * @param[in]    mySPI_parameters:  SPI parameters.
 *
 * @param[out]   myStatus:          Status of the transceiver.
 *
 *
 * @return       Status of GetStatus.
 *
 *
 * @author      Manuel Caballero
 * @date        07/February/2019
 * @version     07/February/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SX128X_status_t  GetStatus ( SPI_parameters_t mySPI_parameters, SX128X_data_t* myStatus )
{
    uint8_t      cmd   =    0U;
    spi_status_t aux;

    /* Send command  */
    cmd     =   SX128X_GET_STATUS;
    aux     =   spi_transfer ( mySPI_parameters, &cmd, 1U, &cmd, 1U );

    /* Parse the data    */
    myStatus->status     =   cmd;




    if ( aux == SPI_SUCCESS )
    {
        return   SX128X_SUCCESS;
    }
    else
    {
        return   SX128X_FAILURE;
    }
}
