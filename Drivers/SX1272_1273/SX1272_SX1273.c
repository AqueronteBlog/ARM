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


/**
 * @brief       SX1272_SX1273_SetMode ( SPI_parameters_t , lora_regopmode_long_range_mode_t )
 *
 * @details     It sets the long range mode: FSK/OOK mode or LoRa mode.
 *
 * @param[in]    mySPIparameters: SPI parameters.
 * @param[in]    myMode:          FSK/OOK mode or LoRa mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SX1272_SX1273_SetMode.
 *
 *
 * @author      Manuel Caballero
 * @date        13/June/2019
 * @version     13/June/2019   The ORIGIN
 * @pre         This function does NOT modify the current Mode but if it is NOT in Sleep mode,
 *              this functions forces it to be in that state in order to update the LongRangeMode and then,
 *              it restores the original value.
 * @warning     N/A.
 */
SX1272_SX1273_status_t SX1272_SX1273_SetMode ( SPI_parameters_t mySPIparameters, lora_regopmode_long_range_mode_t myMode )
{
  uint8_t      cmd[2]   =  { 0U };
  uint8_t      aux_reg  =  0U;
  spi_status_t aux;

  /* Read RegOpMode register   */
  cmd[0]  =   SX1272_SX1273_REG_OP_MODE;
  aux     =   spi_transfer ( mySPIparameters, &cmd[0], 1, &cmd[1], 1 );
  
  /* Push the current Mode ( Device modes )  */
  aux_reg  =   ( cmd[1] & LORA_REGOPMODE_MODE_MASK );

  /* The device MUST be in Sleep mode  */
  if ( aux_reg != LORA_REGOPMODE_MODE_SLEEP )
  {
    /* Force it to be in Sleep mode  */
    cmd[1]  &=  ~LORA_REGOPMODE_MODE_MASK;
    cmd[1]  |=   LORA_REGOPMODE_MODE_SLEEP;

    aux      =   spi_transfer ( mySPIparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );
  }
  else
  {
    /* The device is already in Slepp mode   */
  }

  /* Update the register with the previous Mode ( Device modes )   */
  cmd[1]  &=  ~LORA_REGOPMODE_LONG_RANGE_MODE_MASK;
  cmd[1]  |=   ( myMode | aux_reg );
  aux      =   spi_transfer ( mySPIparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );




  if ( aux == SPI_SUCCESS )
  {
    return   SX1272_SX1273_SUCCESS;
  }
  else
  {
    return   SX1272_SX1273_FAILURE;
  }
}
