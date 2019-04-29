/**
 * @brief       SX1272_SX1273.c
 * @details     SX1272/73 - 860 MHz to 1020 MHz Low Power Long Range Transceiver.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        29/April/2019
 * @version     29/April/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( https://www.nimbus.cit.ie ). All rights reserved.
 */

#include "SX1272_SX1273.h"


/**
 * @brief       SX1272_SX1273_Init ( SPI_parameters_t )
 *
 * @details     It configures the SPI peripheral.
 *
 * @param[in]    mySPIparameters: SPI parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SX1272_SX1273_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        29/April/2019
 * @version     29/April/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SX1272_SX1273_status_t SX1272_SX1273_Init ( SPI_parameters_t mySPIparameters )
{
  spi_status_t aux;

  aux  =   spi_init ( mySPIparameters );



  if ( aux == SPI_SUCCESS )
  {
    return   SX1272_SX1273_SUCCESS;
  }
  else
  {
    return   SX1272_SX1273_FAILURE;
  }
}
