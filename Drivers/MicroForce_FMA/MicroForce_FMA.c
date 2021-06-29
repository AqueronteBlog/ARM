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
 * @warning     N/A
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
 * @brief       MicroForce_FMA_SetWiper   ( SPI_parameters_t , MicroForce_FMA_potentiometer_selection_bits_t , MicroForce_FMA_vector_data_t )
 *
 * @details     It updates the wiper value on the given channel.
 *
 * @param[in]    mySPIparameters:   SPI parameters.
 * @param[in]    myChannel:         Potentiometer 0/1/both.
 * @param[in]    myWiperValue:      New wiper value.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MicroForce_FMA_SetWiper.
 *
 *
 * @author      Manuel Caballero
 * @date        29/June/2021
 * @version     29/June/2021   The ORIGIN
 * @pre         The MCP42XXX contains two independent channels in a 14-pin PDIP, SOIC or TSSOP package while the MCP41XXX is a single-channel device
 *              and is offered in an 8-pin PDIP or SOIC package.
 * @warning     N/A.
 */
MicroForce_FMA_status_t  MicroForce_FMA_SetWiper ( SPI_parameters_t mySPIparameters, MicroForce_FMA_potentiometer_selection_bits_t myChannel, MicroForce_FMA_vector_data_t myWiperValue )
{
    uint8_t         cmd[]   =    { 0, 0 };
    spi_status_t    mySPI_status;


    /* Make the command byte and the new wiper value, update the register then     */
    cmd[0]           =   (uint8_t)( MicroForce_FMA_COMMAND_WRITE_DATA | myChannel );
    cmd[1]           =   (uint8_t)myWiperValue.Dn;
    mySPI_status     =   spi_transfer ( mySPIparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );




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
 * @brief       MicroForce_FMA_SoftwareShutdown   ( SPI_parameters_t , MicroForce_FMA_potentiometer_selection_bits_t )
 *
 * @details     It performs a software shutdown.
 *
 * @param[in]    mySPIparameters:   SPI parameters.
 * @param[in]    myChannel:         Potentiometer 0/1/both.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of MicroForce_FMA_SoftwareShutdown.
 *
 *
 * @author      Manuel Caballero
 * @date        29/June/2021
 * @version     29/June/2021   The ORIGIN
 * @pre         The MCP42XXX contains two independent channels in a 14-pin PDIP, SOIC or TSSOP package while the MCP41XXX is a single-channel device
 *              and is offered in an 8-pin PDIP or SOIC package.
 * @warning     N/A.
 */
MicroForce_FMA_status_t  MicroForce_FMA_SoftwareShutdown ( SPI_parameters_t mySPIparameters, MicroForce_FMA_potentiometer_selection_bits_t myChannel )
{
    uint8_t         cmd[]   =    { 0, 0 };
    spi_status_t    mySPI_status;


    /* Make the command byte, the new wiper value does not take place, update the register then     */
    cmd[0]           =   (uint8_t)( MicroForce_FMA_COMMAND_SHUTDOWN | myChannel );
    cmd[1]           =   0;
    mySPI_status     =   spi_transfer ( mySPIparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), &cmd[0], 0 );




    if ( mySPI_status == SPI_SUCCESS )
    {
        return   MicroForce_FMA_SUCCESS;
    }
    else
    {
        return   MicroForce_FMA_FAILURE;
    }
}
