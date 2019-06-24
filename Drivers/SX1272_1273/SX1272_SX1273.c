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
 * @brief       SX1272_SX1273_SetMode ( SPI_parameters_t , SX1272_SX1273_lora_data_t )
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
 * @version     14/June/2019   Long range mode is now a parameter for the user.
 *              13/June/2019   The ORIGIN
 * @pre         This function does NOT modify the current Mode but if it is NOT in Sleep mode,
 *              this functions forces it to be in that state in order to update the LongRangeMode and then,
 *              it restores the original value.
 * @warning     N/A.
 */
SX1272_SX1273_status_t SX1272_SX1273_SetMode ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t myMode )
{
  uint8_t      cmd[2]   =  { 0U };
  uint8_t      aux_reg  =  0U;
  spi_status_t aux;

  /* Read RegOpMode register   */
  cmd[0]  =   ( SX1272_SX1273_REG_OP_MODE & 0x7F );                         // Read access
  aux     =   spi_transfer ( mySPIparameters, &cmd[0], 1U, &cmd[1], 1U );
  
  /* Push the current Mode ( Device modes )  */
  aux_reg  =   ( cmd[1] & LORA_REGOPMODE_MODE_MASK );
  
  /* From now on, the register is going to be written   */
  cmd[0]  |=   0x80;                                                        // Write access

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
  cmd[1]  |=   ( myMode.mode | aux_reg );
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


/**
 * @brief       SX1272_SX1273_GetMode ( SPI_parameters_t , SX1272_SX1273_lora_data_t* )
 *
 * @details     It gets the long range mode: FSK/OOK mode or LoRa mode.
 *
 * @param[in]    mySPIparameters: SPI parameters.   
 *
 * @param[out]   myMode:          FSK/OOK mode or LoRa mode.
 *
 *
 * @return       Status of SX1272_SX1273_GetMode.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2019
 * @version     14/June/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX1272_SX1273_status_t SX1272_SX1273_GetMode ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* myMode )
{
  uint8_t      cmd   =  0U;
  spi_status_t aux;

  /* Read register   */
  cmd  =   ( SX1272_SX1273_REG_OP_MODE & 0x7F );                    // Read access
  aux  =   spi_transfer ( mySPIparameters, &cmd, 1U, &cmd, 1U );
  
  /* Parse the data   */
  myMode->mode   =   (lora_regopmode_long_range_mode_t)( cmd & LORA_REGOPMODE_LONG_RANGE_MODE_MASK );




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
 * @brief       SX1272_SX1273_LoRa_SetSF ( SPI_parameters_t , SX1272_SX1273_lora_data_t )
 *
 * @details     It sets the spreading factor value.
 *
 * @param[in]    mySPIparameters: SPI parameters.   
 * @param[in]    mySF:            Spreading factor value.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of SX1272_SX1273_LoRa_SetSF.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2019
 * @version     14/June/2019   The ORIGIN
 * @pre         N/A.
 * @warning     If SF = 6 the following configuration must be set by the user:
 *                - Header: Implicit mode
 *                - DetectionOptimize: 0b101
 *                - RegDetectionThreshold: 0x0C
 * @warning     If SF = 11 or SF = 12 and BW = 125kHz, the LowDataRateOptimization must be set accordingly.
 */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetSF ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t mySF )
{
  uint8_t      cmd[2]   =  { 0U };
  spi_status_t aux;

  /* Read the register   */
  cmd[0]  =   ( SX1272_SX1273_LORA_REG_MODEM_CONFIG2 & 0x7F );              // Read access
  aux     =   spi_transfer ( mySPIparameters, &cmd[0], 1U, &cmd[1], 1U );
  
  /* Update the new value   */
  cmd[0]  |=   0x80;                                                        // Write access
  cmd[1]  &=  ~LORA_REGMODEMCONFIG2_SPREADING_FACTOR_MASK;
  cmd[1]  |=   mySF.sf;
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


/**
 * @brief       SX1272_SX1273_LoRa_GetSF ( SPI_parameters_t , SX1272_SX1273_lora_data_t* )
 *
 * @details     It gets the spreading factor value.
 *
 * @param[in]    mySPIparameters: SPI parameters.   
 *
 * @param[out]   mySF:            Spreading factor value.
 *
 *
 * @return       Status of SX1272_SX1273_LoRa_GetSF.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2019
 * @version     14/June/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_GetSF ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* mySF )
{
  uint8_t      cmd   =  0U;
  spi_status_t aux;

  /* Read the register   */
  cmd  =   ( SX1272_SX1273_LORA_REG_MODEM_CONFIG2 & 0x7F );       // Read access
  aux  =   spi_transfer ( mySPIparameters, &cmd, 1U, &cmd, 1U );
  
  /* Parse the data   */
  mySF->sf   =   (lora_regmodemconfig2_spreading_factor_t)( LORA_REGMODEMCONFIG2_SPREADING_FACTOR_MASK & cmd);



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
 * @brief       SX1272_SX1273_LoRa_SetCR ( SPI_parameters_t , SX1272_SX1273_lora_data_t )
 *
 * @details     It sets the coding rate value.
 *
 * @param[in]    mySPIparameters: SPI parameters.   
 * @param[in]    myCR:            Coding rate value.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of SX1272_SX1273_LoRa_SetCR.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2019
 * @version     14/June/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetCR ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t myCR )
{
  uint8_t      cmd[2]   =  { 0U };
  spi_status_t aux;

  /* Read the register   */
  cmd[0]  =   ( SX1272_SX1273_LORA_REG_MODEM_CONFIG1 & 0x7F );            // Read access
  aux     =   spi_transfer ( mySPIparameters, &cmd[0], 1U, &cmd[1], 1U );
  
  /* Update the new value   */
  cmd[0]  |=   0x80;                                                      // Write access
  cmd[1]  &=  ~LORA_REGMODEMCONFIG1_CODING_RATE_MASK;
  cmd[1]  |=   myCR.cr;
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


/**
 * @brief       SX1272_SX1273_LoRa_GetCR ( SPI_parameters_t , SX1272_SX1273_lora_data_t* )
 *
 * @details     It gets the coding rate value.
 *
 * @param[in]    mySPIparameters: SPI parameters.   
 *
 * @param[out]   myCR:            Coding rate value.
 *
 *
 * @return       Status of SX1272_SX1273_LoRa_GetCR.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2019
 * @version     14/June/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_GetCR ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* myCR )
{
  uint8_t      cmd   =  0U;
  spi_status_t aux;

  /* Read the register   */
  cmd  =   ( SX1272_SX1273_LORA_REG_MODEM_CONFIG1 & 0x7F );       // Read access
  aux  =   spi_transfer ( mySPIparameters, &cmd, 1U, &cmd, 1U );
  
  /* Parse the data   */
  myCR->cr   =   (lora_regmodemconfig1_coding_rate_t)( LORA_REGMODEMCONFIG1_CODING_RATE_MASK & cmd);



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
 * @brief       SX1272_SX1273_LoRa_SetBW ( SPI_parameters_t , SX1272_SX1273_lora_data_t )
 *
 * @details     It sets the bandwidth value.
 *
 * @param[in]    mySPIparameters: SPI parameters.   
 * @param[in]    myBW:            Bandwidth value.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of SX1272_SX1273_LoRa_SetBW.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2019
 * @version     14/June/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetBW ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t myBW )
{
  uint8_t      cmd[2]   =  { 0U };
  spi_status_t aux;

  /* Read the register   */
  cmd[0]  =   ( SX1272_SX1273_LORA_REG_MODEM_CONFIG1 & 0x7F );            // Read access
  aux     =   spi_transfer ( mySPIparameters, &cmd[0], 1U, &cmd[1], 1U );
  
  /* Update the new value   */
  cmd[0]  |=   0x80;                                                      // Write access
  cmd[1]  &=  ~LORA_REGMODEMCONFIG1_BW_MASK;
  cmd[1]  |=   myBW.bw;
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


/**
 * @brief       SX1272_SX1273_LoRa_GetBW ( SPI_parameters_t , SX1272_SX1273_lora_data_t* )
 *
 * @details     It gets the bandwidth value.
 *
 * @param[in]    mySPIparameters: SPI parameters.   
 *
 * @param[out]   myBW:            Coding rate value.
 *
 *
 * @return       Status of SX1272_SX1273_LoRa_GetBW.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2019
 * @version     14/June/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_GetBW ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* myBW )
{
  uint8_t      cmd   =  0U;
  spi_status_t aux;

  /* Read the register   */
  cmd  =   ( SX1272_SX1273_LORA_REG_MODEM_CONFIG1 & 0x7F );            // Read access
  aux  =   spi_transfer ( mySPIparameters, &cmd, 1U, &cmd, 1U );
  
  /* Parse the data   */
  myBW->bw   =   (lora_regmodemconfig1_bw_t)( LORA_REGMODEMCONFIG1_BW_MASK & cmd);



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
 * @brief       SX1272_SX1273_LoRa_SetPreamble ( SPI_parameters_t , SX1272_SX1273_lora_data_t )
 *
 * @details     It sets the preamble value.
 *
 * @param[in]    mySPIparameters: SPI parameters.   
 * @param[in]    myPreamble:      Preamble value ( 6 - 65535 ).
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of SX1272_SX1273_LoRa_SetPreamble.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2019
 * @version     14/June/2019   The ORIGIN
 * @pre         The address is automatically incremented internally.
 * @warning     N/A.
 */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetPreamble ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t myPreamble )
{
  uint8_t      cmd[3]   =  { 0U };
  spi_status_t aux;
  
  /* Premable must be:  6 - 65535  */
  if ( myPreamble.preamble < 6U )
  {
    return   SX1272_SX1273_FAILURE;
  }
  else
  {
    /* Read the register   */
    cmd[0]  =  ( SX1272_SX1273_LORA_REG_PREAMBLE_MSB | 0x80 );            // Write access
    cmd[1]  =  (uint8_t)( myPreamble.preamble >> 8U );
    cmd[2]  =  (uint8_t)( myPreamble.preamble & 0xFF );
    aux     =  spi_transfer ( mySPIparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );
  }


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
 * @brief       SX1272_SX1273_LoRa_GetPreamble ( SPI_parameters_t , SX1272_SX1273_lora_data_t* )
 *
 * @details     It gets the preamble value.
 *
 * @param[in]    mySPIparameters: SPI parameters.   
 *
 * @param[out]   myPreamble:      Preamble value ( 6 - 65535 ).
 *
 *
 * @return       Status of SX1272_SX1273_LoRa_GetPreamble.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2019
 * @version     14/June/2019   The ORIGIN
 * @pre         The address is automatically incremented internally.
 * @warning     N/A.
 */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_GetPreamble ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* myPreamble )
{
  uint8_t      cmd[2]   =  { 0U };
  spi_status_t aux;

  /* Read the register   */
  cmd[0]  =   ( SX1272_SX1273_LORA_REG_PREAMBLE_MSB & 0x7F );            // Read access
  aux     =   spi_transfer ( mySPIparameters, &cmd[0], 1U, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data   */
  myPreamble->preamble   =   cmd[0];
  myPreamble->preamble <<=   8U;
  myPreamble->preamble  |=   cmd[1];



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
 * @brief       SX1272_SX1273_LoRa_SetHeaderMode ( SPI_parameters_t , SX1272_SX1273_lora_data_t )
 *
 * @details     It sets the header mode.
 *
 * @param[in]    mySPIparameters: SPI parameters.   
 * @param[in]    myHeaderMode:    Header mode: Implicit/Explicit header mode.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of SX1272_SX1273_LoRa_SetHeaderMode.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2019
 * @version     14/June/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetHeaderMode ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t myHeaderMode )
{
  uint8_t      cmd[2]   =  { 0U };
  spi_status_t aux;
  
  /* Read the register   */
  cmd[0]  =   ( SX1272_SX1273_LORA_REG_MODEM_CONFIG1 & 0x7F );            // Read access
  aux     =   spi_transfer ( mySPIparameters, &cmd[0], 1U, &cmd[1], 1U );
  
  /* Update the new value   */
  cmd[0]  |=   0x80;                                                      // Write access
  cmd[1]  &=  ~LORA_REGMODEMCONFIG1_IMPLICIT_HEADER_MODE_ON_MASK;
  cmd[1]  |=   myHeaderMode.headerMode;
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


/**
 * @brief       SX1272_SX1273_LoRa_GetHeaderMode ( SPI_parameters_t , SX1272_SX1273_lora_data_t* )
 *
 * @details     It gets the header mode.
 *
 * @param[in]    mySPIparameters: SPI parameters.   
 *
 * @param[out]   myHeaderMode:    Header mode: Implicit/Explicit header mode.
 *
 *
 * @return       Status of SX1272_SX1273_LoRa_GetHeaderMode.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2019
 * @version     14/June/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_GetHeaderMode ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* myHeaderMode )
{
  uint8_t      cmd   =  0U;
  spi_status_t aux;

  /* Read the register   */
  cmd  =   ( SX1272_SX1273_LORA_REG_MODEM_CONFIG1 & 0x7F );            // Read access
  aux  =   spi_transfer ( mySPIparameters, &cmd, 1U, &cmd, 1U );
  
  /* Parse the data   */
  myHeaderMode->headerMode   =   (lora_regmodemconfig1_implicit_header_mode_on_t)( cmd & LORA_REGMODEMCONFIG1_IMPLICIT_HEADER_MODE_ON_MASK );



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
 * @brief       SX1272_SX1273_LoRa_SetLowDataRateOptimization ( SPI_parameters_t , SX1272_SX1273_lora_data_t )
 *
 * @details     It sets the Low Data Rate Optimization mode.
 *
 * @param[in]    mySPIparameters:           SPI parameters.   
 * @param[in]    myLowDataRateOptimization: Low Data Rate Optimization mode.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of SX1272_SX1273_LoRa_SetLowDataRateOptimization.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2019
 * @version     14/June/2019   The ORIGIN
 * @pre         N/A.
 * @warning     Its use is mandated with spreading factors of 11 and 12 at 125 kHz bandwidth.
 */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetLowDataRateOptimization ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t myLowDataRateOptimization )
{
  uint8_t      cmd[2]   =  { 0U };
  spi_status_t aux;
  
  /* Read the register   */
  cmd[0]  =   ( SX1272_SX1273_LORA_REG_MODEM_CONFIG1 & 0x7F );            // Read access
  aux     =   spi_transfer ( mySPIparameters, &cmd[0], 1U, &cmd[1], 1U );
  
  /* Update the new value   */
  cmd[0]  |=   0x80;                                                      // Write access
  cmd[1]  &=  ~LORA_REGMODEMCONFIG1_LOW_DATA_RATE_OPTIMIZE_MASK;
  cmd[1]  |=   myLowDataRateOptimization.lowDataRateOptimization;
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


/**
 * @brief       SX1272_SX1273_LoRa_GetLowDataRateOptimization ( SPI_parameters_t , SX1272_SX1273_lora_data_t* )
 *
 * @details     It gets the Low Data Rate Optimization mode.
 *
 * @param[in]    mySPIparameters:           SPI parameters.   
 *
 * @param[out]   myLowDataRateOptimization: Low Data Rate Optimization mode.
 *
 *
 * @return       Status of SX1272_SX1273_LoRa_GetLowDataRateOptimization.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2019
 * @version     14/June/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_GetLowDataRateOptimization ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* myLowDataRateOptimization )
{
  uint8_t      cmd   =  0U;
  spi_status_t aux;

  /* Read the register   */
  cmd  =   ( SX1272_SX1273_LORA_REG_MODEM_CONFIG1 & 0x7F );            // Read access
  aux  =   spi_transfer ( mySPIparameters, &cmd, 1U, &cmd, 1U );
  
  /* Parse the data   */
  myLowDataRateOptimization->lowDataRateOptimization   =   (lora_regmodemconfig1_low_data_rate_optimize_t)( cmd & LORA_REGMODEMCONFIG1_LOW_DATA_RATE_OPTIMIZE_MASK );



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
 * @brief       SX1272_SX1273_LoRa_SetHopPeriod ( SPI_parameters_t , SX1272_SX1273_lora_data_t )
 *
 * @details     It sets the Frequency Hopping Period mode.
 *
 * @param[in]    mySPIparameters: SPI parameters.   
 * @param[in]    myHopPeriod:     Frequency Hopping Period value ( 0 - 255 ).
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of SX1272_SX1273_LoRa_SetHopPeriod.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2019
 * @version     14/June/2019   The ORIGIN
 * @pre         0 = disabled.
 * @warning     N/A.
 */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetHopPeriod ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t myHopPeriod )
{
  uint8_t      cmd[2]   =  { 0U };
  spi_status_t aux;
  
  /* Update the new value   */
  cmd[0]   =   ( SX1272_SX1273_LORA_REG_HOP_PERIOD | 0x80 );            // Write access
  cmd[1]   =   myHopPeriod.hopPeriod;
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


/**
 * @brief       SX1272_SX1273_LoRa_GetHopPeriod ( SPI_parameters_t , SX1272_SX1273_lora_data_t* )
 *
 * @details     It gets the Frequency Hopping Period mode.
 *
 * @param[in]    mySPIparameters: SPI parameters.   
 *
 * @param[out]   myHopPeriod:     Frequency Hopping Period value ( 0 - 255 ).
 *
 *
 * @return       Status of SX1272_SX1273_LoRa_GetHopPeriod.
 *
 *
 * @author      Manuel Caballero
 * @date        14/June/2019
 * @version     14/June/2019   The ORIGIN
 * @pre         0 = disabled.
 * @warning     N/A.
 */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_GetHopPeriod  ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* myHopPeriod )
{
  uint8_t      cmd   =  0U;
  spi_status_t aux;

  /* Read the register   */
  cmd  =   ( SX1272_SX1273_LORA_REG_HOP_PERIOD & 0x7F );            // Read access
  aux  =   spi_transfer ( mySPIparameters, &cmd, 1U, &cmd, 1U );
  
  /* Parse the data   */
  myHopPeriod->hopPeriod   =   cmd;



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
 * @brief       SX1272_SX1273_LoRa_SetOperatingMode ( SPI_parameters_t , SX1272_SX1273_lora_data_t )
 *
 * @details     It sets the LoRa operating mode functionality.
 *
 * @param[in]    mySPIparameters:     SPI parameters.   
 * @param[in]    myLoRaOperatingMode: LoRa operating mode functionality.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of SX1272_SX1273_LoRa_SetOperatingMode.
 *
 *
 * @author      Manuel Caballero
 * @date        20/June/2019
 * @version     20/June/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetOperatingMode ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t myLoRaOperatingMode )
{
  uint8_t      cmd[2]   =  { 0U };
  spi_status_t aux;
  
  /* Update the new value   */
  cmd[0]   =   ( SX1272_SX1273_REG_OP_MODE & 0x7F );            // Read access
  aux      =   spi_transfer ( mySPIparameters, &cmd[0], 1U, &cmd[1], 1U );
  
  /* The device must be in LoRa mode   */
  if ( ( cmd[1] & LORA_REGOPMODE_LONG_RANGE_MODE_MASK ) == LORA_REGOPMODE_LONG_RANGE_MODE_FSK_OOK_MODE  )
  {
    return   SX1272_SX1273_FAILURE;
  }
  else
  {
    /* Update the register   */
    cmd[0]  |=   0x80;            // Write access;
    cmd[1]  &=  ~LORA_REGOPMODE_MODE_MASK;
    cmd[1]  |=   myLoRaOperatingMode.loraOperatingMode;
    aux      =   spi_transfer ( mySPIparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );
  }



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
 * @brief       SX1272_SX1273_LoRa_GetOperatingMode ( SPI_parameters_t , SX1272_SX1273_lora_data_t* )
 *
 * @details     It gets LoRa operating mode functionality.
 *
 * @param[in]    mySPIparameters:     SPI parameters.   
 *
 * @param[out]   myLoRaOperatingMode: LoRa operating mode functionality.
 *
 *
 * @return       Status of SX1272_SX1273_LoRa_GetOperatingMode.
 *
 *
 * @author      Manuel Caballero
 * @date        20/June/2019
 * @version     20/June/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_GetOperatingMode ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* myLoRaOperatingMode )
{
  uint8_t      cmd   =  0U;
  spi_status_t aux;

  /* Read the register   */
  cmd  =   ( SX1272_SX1273_REG_OP_MODE & 0x7F );            // Read access
  aux  =   spi_transfer ( mySPIparameters, &cmd, 1U, &cmd, 1U );
  
  /* Parse the data   */
  myLoRaOperatingMode->loraOperatingMode   =   (lora_regopmode_mode_t)( cmd & LORA_REGOPMODE_MODE_MASK );



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
 * @brief       SX1272_SX1273_LoRa_SetAccessSharedReg ( SPI_parameters_t , lora_regopmode_access_shared_reg_t )
 *
 * @details     It allows access to FSK registers page located in address space ( 0x0D:0x3F ) while in LoRa mode.
 *
 * @param[in]    mySPIparameters:   SPI parameters.   
 * @param[in]    myAccessSharedReg: Enable/Disable access.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of SX1272_SX1273_LoRa_SetAccessSharedReg.
 *
 *
 * @author      Manuel Caballero
 * @date        20/June/2019
 * @version     20/June/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetAccessSharedReg ( SPI_parameters_t mySPIparameters, lora_regopmode_access_shared_reg_t myAccessSharedReg )
{
  uint8_t      cmd[2]   =  { 0U };
  spi_status_t aux;
  
  /* Read the register   */
  cmd[0]  =   ( SX1272_SX1273_REG_OP_MODE & 0x7F );                       // Read access
  aux     =   spi_transfer ( mySPIparameters, &cmd[0], 1U, &cmd[1], 1U );
  
  /* Update the new value   */
  cmd[0]  |=   0x80;                                                      // Write access
  cmd[1]  &=  ~LORA_REGOPMODE_ACCESS_SHARED_REG_MASK;
  cmd[1]  |=   myAccessSharedReg;
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


/**
 * @brief       SX1272_SX1273_LoRa_SetFrequency ( SPI_parameters_t , SX1272_SX1273_lora_data_t )
 *
 * @details     It sets the LoRa frequency.
 *
 * @param[in]    mySPIparameters: SPI parameters.   
 * @param[in]    myFrequency:     Frequency.
 *
 * @param[out]   N/A
 *
 *
 * @return       Status of SX1272_SX1273_LoRa_SetFrequency.
 *
 *
 * @author      Manuel Caballero
 * @date        21/June/2019
 * @version     21/June/2019   The ORIGIN
 * @pre         The address is automatically incremented internally.
 * @warning     The device MUST be in SLEEP or STANDBY mode.
 */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetFrequency ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t myFrequency )
{
  uint8_t      cmd[4]   =  { 0U };
  uint32_t     frf      =  0UL;
  spi_status_t aux;
  
  /* Calculate the RF carrier frequency  */
  frf  =   (uint32_t)( (float)( ( myFrequency.frequency * F_2POW19 ) / F_XOSC ) + 0.5 );

  /* Update the register   */
  cmd[0]   =   ( SX1272_SX1273_REG_FRF_MSB | 0x80 );            // Write access
  cmd[1]   =   (uint8_t)( frf >> 16U );                         // MSB Frf 
  cmd[2]   =   (uint8_t)( frf >> 8U );                          // Mib Frf 
  cmd[3]   =   (uint8_t)( frf & 0xFF );                         // LSB Frf 
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


/**
 * @brief       SX1272_SX1273_LoRa_GetFrequency ( SPI_parameters_t , SX1272_SX1273_lora_data_t* )
 *
 * @details     It gets the LoRa frequency.
 *
 * @param[in]    mySPIparameters: SPI parameters.   
 *
 * @param[out]   myFrequency:     Frequency.
 *
 *
 * @return       Status of SX1272_SX1273_LoRa_GetFrequency.
 *
 *
 * @author      Manuel Caballero
 * @date        21/June/2019
 * @version     21/June/2019   The ORIGIN
 * @pre         The address is automatically incremented internally.
 * @pre         This function returns the calculate frequency regarding the value in Frf register.
 * @warning     N/A.
 */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_GetFrequency ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* myFrequency )
{
  uint8_t      cmd[3]   =  { 0U };
  uint32_t     frf      =  0UL;
  spi_status_t aux;

  /* Read the register   */
  cmd[0]  =   ( SX1272_SX1273_REG_FRF_MSB & 0x7F );            // Read access
  aux     =   spi_transfer ( mySPIparameters, &cmd[0], 1U, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data   */
  frf                      =   cmd[0];
  frf                    <<=   8U;
  frf                     |=   cmd[1];
  frf                    <<=   8U;
  frf                     |=   cmd[2];
  myFrequency->frequency   =   (float)( ( F_XOSC * frf ) / F_2POW19 );



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
 * @brief       SX1272_SX1273_LoRa_SetPowerAmplifier ( SPI_parameters_t , SX1272_SX1273_lora_data_t )
 *
 * @details     It sets the RF power amplifier block.
 *
 * @param[in]    mySPIparameters: SPI parameters.   
 * @param[in]    myPaConfig:      PaSelect and OuputPower.
 *
 * @param[out]   myPaConfig:      PaDac value.
 *
 *
 * @return       Status of SX1272_SX1273_LoRa_SetPowerAmplifier.
 *
 *
 * @author      Manuel Caballero
 * @date        24/June/2019
 * @version     24/June/2019   The ORIGIN
 * @pre         This function updates PaDac automatically.
 * @warning     N/A.
 */
SX1272_SX1273_status_t SX1272_SX1273_LoRa_SetPowerAmplifier ( SPI_parameters_t mySPIparameters, SX1272_SX1273_lora_data_t* myPaConfig )
{
  uint8_t      cmd[2]     =  { 0U };
  int8_t       myAuxPower =  0U;
  spi_status_t aux;
  

  /* Identify PA output pin  */
  switch ( myPaConfig->paSelect )
  {
    default:
    case LORA_PA_PA0_OUTPUT_ON_RFIO:      
      /* Check power range: [ -1, +14 ] dBm   */
      if ( ( myPaConfig->p_out >= -1 ) && ( myPaConfig->p_out <= 14 ) )
      {
        myAuxPower   =   ( myPaConfig->p_out + 1 );
      }
      else
      {
        return   SX1272_SX1273_FAILURE;
      }
      
      cmd[1]  =  LORA_REGPACONFIG_PA_SELECT_RFIO_PIN;
      break;

    case LORA_PA_PA1_PA2_COMBINED_ON_PA_BOOST:
      /* Check power range: [ +2, +17 ] dBm   */
      if ( ( myPaConfig->p_out >= 2 ) && ( myPaConfig->p_out <= 17 ) )
      {
        myAuxPower   =   ( myPaConfig->p_out - 2 );
      }
      else
      {
        return   SX1272_SX1273_FAILURE;
      }

      cmd[1]  =  LORA_REGPACONFIG_PA_SELECT_PA_BOOST_PIN;
      break;

    case LORA_PA_PA1_PA2_ON_PA_BOOST_HIGH_OUTPUT_20_DBM:
      /* Check power range: [ +5, +20 ] dBm   */
      if ( ( myPaConfig->p_out >= 5 ) && ( myPaConfig->p_out <= 20 ) )
      {
        myAuxPower   =   ( myPaConfig->p_out - 5 );
      }
      else
      {
        return   SX1272_SX1273_FAILURE;
      }

      cmd[1]  =  LORA_REGPACONFIG_PA_SELECT_PA_BOOST_PIN;
      break;
  }
  
  
  /* Update the register   */
  cmd[0]  =  ( SX1272_SX1273_REG_PA_CONFIG | 0x80 );       // Write access
  cmd[1] |=  ( LORA_REGPACONFIG_OUTPUT_POWER_MASK & myAuxPower );
  aux     =  spi_transfer ( mySPIparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );
  
  /* Update the High Power Settings accordingly ( PaDac )  */
  if ( myPaConfig->paSelect == LORA_PA_PA1_PA2_ON_PA_BOOST_HIGH_OUTPUT_20_DBM )
  {
    myPaConfig->paDac  =   LORA_REGPADAC_PA_DAC_PLUS_20_DBM;
  }
  else
  {
    myPaConfig->paDac  =   LORA_REGPADAC_PA_DAC_DEFAULT_VALUE;
  }
  
  cmd[0]  =  ( SX1272_SX1273_REG_PA_DAC | 0x80 );          // Write access
  cmd[1]  =  myPaConfig->paDac;
  aux     =  spi_transfer ( mySPIparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0U );




  if ( aux == SPI_SUCCESS )
  {
    return   SX1272_SX1273_SUCCESS;
  }
  else
  {
    return   SX1272_SX1273_FAILURE;
  }
}
