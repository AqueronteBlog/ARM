/**
 * @brief       MicroForce_FMA.c
 * @details     MicroForce Sensors, Compensated/Amplified.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        29/June/2021
 * @version     29/June/2021    The ORIGIN
 * @pre         N/A.
 * @warning     This driver only supports SPI communication: FMAMSDXX005WCSC3,FMAMSDXX015WCSC3 and FMAMSDXX025WCSC3.
 * @pre         This code belongs to Nimbus Centre ( https://www.nimbus.cit.ie ).
 */

 #include "MicroForce_FMA.h"


/**
 * @brief       MicroForce_FMA_Init ( SPI_parameters_t )
 *
 * @details     It configures the SPI peripheral.
 *
 * @param[in]    mySPIparameters:       SPI parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MicroForce_FMA_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        29/June/2021
 * @version     29/June/2021   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
MicroForce_FMA_status_t  MicroForce_FMA_Init ( SPI_parameters_t mySPIparameters )
{
  spi_status_t    mySPI_status;


  mySPI_status  =   spi_init ( mySPIparameters );



  if ( mySPI_status == SPI_SUCCESS )
  {
    return   MicroForce_FMA_SUCCESS;
  }
  else
  {
    return   MicroForce_FMA_FAILURE;
  }
}



/**
 * @brief       MicroForce_FMA_GetRawForce   ( SPI_parameters_t , MicroForce_FMA_status_bits_data_t* , uint16_t* )
 *
 * @details     It gets the raw force data.
 *
 * @param[in]    mySPIparameters: SPI parameters.
 *
 * @param[out]   myStatus:        Status bits data.
 * @param[out]   myRawBridgeData: Raw bridge data.
 *
 *
 * @return       Status of MicroForce_FMA_GetRawForce.
 *
 *
 * @author      Manuel Caballero
 * @date        29/June/2021
 * @version     29/June/2021   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MicroForce_FMA_status_t  MicroForce_FMA_GetRawForce ( SPI_parameters_t mySPIparameters, MicroForce_FMA_status_bits_data_t* myStatus, uint16_t* myRawBridgeData )
{
  uint8_t         cmd[]   =    { 0, 0 };
  spi_status_t    mySPI_status;

  /* Get the data     */
  mySPI_status     =   spi_transfer ( mySPIparameters, &cmd[0], 0U, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  myStatus->status_bits  =  (MicroForce_FMA_status_bits_t)( cmd[0] & MicroForce_FMA_STATUS_BITS_MASK );
  
  *myRawBridgeData       =  ( cmd[0] & 0x3F );
  *myRawBridgeData     <<=  8U;
  *myRawBridgeData      |=  cmd[1];



  if ( mySPI_status == SPI_SUCCESS )
  {
    return   MicroForce_FMA_SUCCESS;
  }
  else
  {
    return   MicroForce_FMA_FAILURE;
  }
}



/**
 * @brief       MicroForce_FMA_SoftwareShutdown   ( MicroForce_FMA_transfer_function_t , uint8_t , uint16_t )
 *
 * @details     It calculates the force data in Newton (N).
 *
 * @param[in]    myBridgeData:    Raw bridge data.
 * @param[in]    myCalibration:   Calibration point.
 * @param[in]    myForceRange:    Force range.
 *
 * @param[out]   N/A
 *
 *
 * @return       Force value in Newton.
 *
 *
 * @author      Manuel Caballero
 * @date        29/June/2021
 * @version     29/June/2021   The ORIGIN
 * @pre         The function: MicroForce_FMA_GetRawForce must be called to update the bridge data values.
 * @warning     N/A.
 */
float  MicroForce_FMA_CalculateForce ( MicroForce_FMA_transfer_function_t myCalibration, uint8_t myForceRange, uint16_t myRawBridgeData )
{
  uint16_t output_max;
  uint16_t output_min;
  uint8_t  force_range;

  
  /* It calculates the calibration point depending on the Transfer Function point of the device selected. ( Datasheet. FIGURE 2. NOMENCLATURE AND ORDER GUIDE 32347833 Issue D )   */
  if ( myCalibration == MicroForce_FMA_TRANSFER_FUNCTION_10_TO_90 )
  {
    output_max   =   14745U;
    output_min   =   1638U;
  }
  else
  {
    output_max   =   13107U;
    output_min   =   3276U;
  }


  /* It calculates the force in N  */
  return  (float)( ( myRawBridgeData - output_min ) * myForceRange )/( output_max - output_min );
}



/**
 * @brief       MicroForce_FMA_GetRaw8bitTemperature   ( SPI_parameters_t , MicroForce_FMA_status_bits_data_t* , uint8_t* )
 *
 * @details     It gets the raw 8-bit temperature.
 *
 * @param[in]    mySPIparameters: SPI parameters.
 *
 * @param[out]   myStatus:        Status bits data.
 * @param[out]   myRaw8bitTemp:   Raw 8-bit Temperature data.
 *
 *
 * @return       Status of MicroForce_FMA_GetRaw8bitTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        29/June/2021
 * @version     29/June/2021   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MicroForce_FMA_status_t  MicroForce_FMA_GetRaw8bitTemperature ( SPI_parameters_t mySPIparameters, MicroForce_FMA_status_bits_data_t* myStatus, uint8_t* myRaw8bitTemp )
{
  uint8_t         cmd[]   =    { 0, 0, 0 };
  spi_status_t    mySPI_status;

  /* Get the data     */
  mySPI_status     =   spi_transfer ( mySPIparameters, &cmd[0], 0U, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  myStatus->status_bits  =  (MicroForce_FMA_status_bits_t)( cmd[0] & MicroForce_FMA_STATUS_BITS_MASK );
  
  *myRaw8bitTemp         =  cmd[2];



  if ( mySPI_status == SPI_SUCCESS )
  {
    return   MicroForce_FMA_SUCCESS;
  }
  else
  {
    return   MicroForce_FMA_FAILURE;
  }
}



/**
 * @brief       MicroForce_FMA_GetRaw11bitTemperature   ( SPI_parameters_t , MicroForce_FMA_status_bits_data_t* , uint16_t* )
 *
 * @details     It gets the raw 11-bit temperature.
 *
 * @param[in]    mySPIparameters: SPI parameters.
 *
 * @param[out]   myStatus:        Status bits data.
 * @param[out]   myRaw11bitTemp:  Raw 11-bit Temperature data.
 *
 *
 * @return       Status of MicroForce_FMA_GetRaw11bitTemperature.
 *
 *
 * @author      Manuel Caballero
 * @date        29/June/2021
 * @version     29/June/2021   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MicroForce_FMA_status_t  MicroForce_FMA_GetRaw11bitTemperature ( SPI_parameters_t mySPIparameters, MicroForce_FMA_status_bits_data_t* myStatus, uint16_t* myRaw11bitTemp )
{
  uint8_t         cmd[]   =    { 0, 0, 0, 0 };
  spi_status_t    mySPI_status;

  /* Get the data     */
  mySPI_status     =   spi_transfer ( mySPIparameters, &cmd[0], 0U, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  myStatus->status_bits  =  (MicroForce_FMA_status_bits_t)( cmd[0] & MicroForce_FMA_STATUS_BITS_MASK );
  
  *myRaw11bitTemp        =  cmd[2];
  *myRaw11bitTemp      <<=  8U;
  *myRaw11bitTemp       |=  cmd[3];
  
  *myRaw11bitTemp      >>=  5U;


  if ( mySPI_status == SPI_SUCCESS )
  {
    return   MicroForce_FMA_SUCCESS;
  }
  else
  {
    return   MicroForce_FMA_FAILURE;
  }
}



/**
 * @brief       MicroForce_FMA_Calculate8bitTemperature   ( uint8_t )
 *
 * @details     It calculates the 8-bit temperature in Celsius degree.
 *
 * @param[in]    myRawTemperature:  Raw 8-bit temperature value.
 *
 * @param[out]   N/A
 *
 *
 * @return       Temperature value in Celsius degree.
 *
 *
 * @author      Manuel Caballero
 * @date        29/June/2021
 * @version     29/June/2021   The ORIGIN
 * @pre         The function:MicroForce_FMA_GetRaw8bitTemperature must be called to update the temperature value.
 * @warning     N/A.
 */
float  MicroForce_FMA_Calculate8bitTemperature ( uint8_t myRawTemperature )
{
  uint16_t aux_temp;

  
  /* It processes the data correctly. ( Datasheet. Equation 3: Temperature Conversion Function   */
  aux_temp   =   (uint16_t)myRawTemperature;
  aux_temp <<=   3U;
  aux_temp  &=   0x7F8;

  /* It calculates the temperature in C  */
  return  (float)( ( ( aux_temp / 2047.0 ) * 200.0 ) - 50.0 );
}



/**
 * @brief       MicroForce_FMA_Calculate11bitTemperature   ( uint16_t )
 *
 * @details     It calculates the 11-bit temperature in Celsius degree.
 *
 * @param[in]    myRawTemperature:  Raw 11-bit temperature value.
 *
 * @param[out]   N/A
 *
 *
 * @return       Temperature value in Celsius degree.
 *
 *
 * @author      Manuel Caballero
 * @date        29/June/2021
 * @version     29/June/2021   The ORIGIN
 * @pre         The function:MicroForce_FMA_GetRaw11bitTemperature must be called to update the temperature value.
 * @warning     N/A.
 */
float  MicroForce_FMA_Calculate11bitTemperature ( uint16_t myRawTemperature )
{
  /* It calculates the temperature in C  */
  return  (float)( ( ( myRawTemperature / 2047.0 ) * 200.0 ) - 50.0 );
}



/**
 * @brief       MicroForce_FMA_GetAllRawData   ( SPI_parameters_t , MicroForce_FMA_status_bits_data_t* , uint16_t* , uint16_t*  )
 *
 * @details     gets the all raw data ( bridge data and 11-bit temperature ).
 *
 * @param[in]    mySPIparameters: SPI parameters.
 *
 * @param[out]   myStatus:        Status bits data.
 * @param[out]   myRawBridgeData: Raw bridge data.
 * @param[out]   myRaw11bitTemp:  Raw 11-bit Temperature data.
 *
 *
 * @return       Status of MicroForce_FMA_GetAllRawData.
 *
 *
 * @author      Manuel Caballero
 * @date        29/June/2021
 * @version     29/June/2021   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
MicroForce_FMA_status_t  MicroForce_FMA_GetAllRawData ( SPI_parameters_t mySPIparameters, MicroForce_FMA_status_bits_data_t* myStatus, uint16_t* myRawBridgeData, uint16_t* myRaw11bitTemp )
{
  uint8_t         cmd[]   =    { 0, 0, 0, 0 };
  spi_status_t    mySPI_status;

  /* Get the data     */
  mySPI_status     =   spi_transfer ( mySPIparameters, &cmd[0], 0U, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ) );
  
  /* Parse the data  */
  myStatus->status_bits  =  (MicroForce_FMA_status_bits_t)( cmd[0] & MicroForce_FMA_STATUS_BITS_MASK );
  
  *myRawBridgeData       =  ( cmd[0] & 0x3F );
  *myRawBridgeData     <<=  8U;
  *myRawBridgeData      |=  cmd[1];
           
  *myRaw11bitTemp        =  cmd[2];
  *myRaw11bitTemp      <<=  8U;
  *myRaw11bitTemp       |=  cmd[3];
  
  *myRaw11bitTemp      >>=  5U;



  if ( mySPI_status == SPI_SUCCESS )
  {
    return   MicroForce_FMA_SUCCESS;
  }
  else
  {
    return   MicroForce_FMA_FAILURE;
  }
}
