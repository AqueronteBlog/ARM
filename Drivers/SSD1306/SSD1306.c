/**
 * @brief       SSD1306.c
 * @details     128 x 64 Dot Matrix OLED/PLED Segment/Common Driver with Controller.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/November/2018
 * @version     3/November/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com/ ).
 */

#include "SSD1306.h"


/**
 * @brief       SSD1306_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SSD1306_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        3/November/2018
 * @version     3/November/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
SSD1306_status_t  SSD1306_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
    {
        return   SSD1306_SUCCESS;
    }
    else
    {
        return   SSD1306_FAILURE;
    }
}



/**
 * @brief       SSD1306_SetContrastControl ( I2C_parameters_t , SSD1306_vector_data_t )
 *
 * @details     It sets the constrast value to select 1 out of 256 contrast steps.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myContrastStep:  Constrast value to select 1 out of 256 contrast steps.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SSD1306_SetContrastControl.
 *
 *
 * @author      Manuel Caballero
 * @date        4/November/2018
 * @version     4/November/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SSD1306_status_t  SSD1306_SetContrastControl ( I2C_parameters_t myI2Cparameters, SSD1306_vector_data_t myContrastStep )
{
    uint8_t      cmd[]  =    { 0U, 0U };
    i2c_status_t aux;


    /* Set new constrast value    */
    cmd[0]   =   ( SSD1306_CO_DATA_BYTES | SSD1306_DATA_COMMAND_BIT_COMMAND | SSD1306_CONTROL_BYTE );   // Control byte
    cmd[1]   =   myContrastStep.contrast;                                                               // New contrast value
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


    
    if ( aux == I2C_SUCCESS )
    {
        return   SSD1306_SUCCESS;
    }
    else
    {
        return   SSD1306_FAILURE;
    }
}



/**
 * @brief       SSD1306_SetEntireDisplay ( I2C_parameters_t , SSD1306_entire_display_on_t )
 *
 * @details     It sets if the display's output follows RAM content or ignores it.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myEntireDisplayOn: Display's output follows RAM content or ignores it.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SSD1306_SetEntireDisplay.
 *
 *
 * @author      Manuel Caballero
 * @date        4/November/2018
 * @version     4/November/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SSD1306_status_t  SSD1306_SetEntireDisplay ( I2C_parameters_t myI2Cparameters, SSD1306_entire_display_on_t myEntireDisplayOn )
{
    uint8_t      cmd[]  =    { 0U, 0U };
    i2c_status_t aux;


    /* Update the register    */
    cmd[0]   =   ( SSD1306_CO_DATA_BYTES | SSD1306_DATA_COMMAND_BIT_COMMAND | SSD1306_CONTROL_BYTE );   // Control byte
    cmd[1]   =   myEntireDisplayOn;                                                               
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


    
    if ( aux == I2C_SUCCESS )
    {
        return   SSD1306_SUCCESS;
    }
    else
    {
        return   SSD1306_FAILURE;
    }
}



/**
 * @brief       SSD1306_SetNormalInverseDisplay ( I2C_parameters_t , SSD1306_set_normal_inverse_display_t )
 *
 * @details     It sets normal/inverse display.
 *
 * @param[in]    myI2Cparameters:        I2C parameters.
 * @param[in]    myNormalInverseDisplay: Normal/Inverse display.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SSD1306_SetNormalInverseDisplay.
 *
 *
 * @author      Manuel Caballero
 * @date        4/November/2018
 * @version     4/November/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SSD1306_status_t  SSD1306_SetNormalInverseDisplay ( I2C_parameters_t myI2Cparameters, SSD1306_set_normal_inverse_display_t myNormalInverseDisplay )
{
    uint8_t      cmd[]  =    { 0U, 0U };
    i2c_status_t aux;


    /* Update the register    */
    cmd[0]   =   ( SSD1306_CO_DATA_BYTES | SSD1306_DATA_COMMAND_BIT_COMMAND | SSD1306_CONTROL_BYTE );   // Control byte
    cmd[1]   =   myNormalInverseDisplay;                                                               
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


    
    if ( aux == I2C_SUCCESS )
    {
        return   SSD1306_SUCCESS;
    }
    else
    {
        return   SSD1306_FAILURE;
    }
}



/**
 * @brief       SSD1306_SetDisplay ( I2C_parameters_t , SSD1306_set_display_t )
 *
 * @details     It sets display ON/OFF.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myDisplayMode:   Display is ON/OFF.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SSD1306_SetDisplay.
 *
 *
 * @author      Manuel Caballero
 * @date        4/November/2018
 * @version     4/November/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SSD1306_status_t  SSD1306_SetDisplay ( I2C_parameters_t myI2Cparameters, SSD1306_set_display_t myDisplayMode )
{
    uint8_t      cmd[]  =    { 0U, 0U };
    i2c_status_t aux;


    /* Update the register    */
    cmd[0]   =   ( SSD1306_CO_DATA_BYTES | SSD1306_DATA_COMMAND_BIT_COMMAND | SSD1306_CONTROL_BYTE );   // Control byte
    cmd[1]   =   myDisplayMode;                                                               
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


    
    if ( aux == I2C_SUCCESS )
    {
        return   SSD1306_SUCCESS;
    }
    else
    {
        return   SSD1306_FAILURE;
    }
}