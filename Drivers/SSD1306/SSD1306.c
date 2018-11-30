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
 * @brief       SSD1306_SendCommand ( I2C_parameters_t , uint8_t )
 *
 * @details     It sends a command byte to SSD1306.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myCommand:       Command.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SSD1306_SendCommand.
 *
 *
 * @author      Manuel Caballero
 * @date        22/November/2018
 * @version     22/November/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SSD1306_status_t  SSD1306_SendCommand ( I2C_parameters_t myI2Cparameters, uint8_t myCommand )
{
    uint8_t      cmd[]  =    { 0U, 0U };
    i2c_status_t aux;


    /* Send a new command value    */
    cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES & SSD1306_CONTROL_BYTE ) );   // Control byte
    cmd[1]   =   myCommand;                                                              
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
 * @brief       SSD1306_SendData ( I2C_parameters_t , uint8_t* , uint8_t )
 *
 * @details     It sends a command byte to SSD1306.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myData:          Data.
 * @param[in]    myDataSize:      Amount of data to be sent.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SSD1306_SendData.
 *
 *
 * @author      Manuel Caballero
 * @date        22/November/2018
 * @version     22/November/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SSD1306_status_t  SSD1306_SendData ( I2C_parameters_t myI2Cparameters, uint8_t* myData, uint8_t myDataSize )
{
    uint8_t      *cmd;
    i2c_status_t aux;

    *cmd++   =   ( SSD1306_DATA_COMMAND_BIT_DATA | ( SSD1306_CO_DATA_BYTES & SSD1306_CONTROL_BYTE ) );   // Control byte
    cmd   =   myData;

    /* Send a new data value    */                                                             
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], myDataSize, I2C_STOP_BIT );


    
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
    SSD1306_status_t aux;


    /* Set new constrast value    */
    aux  =   SSD1306_SendCommand ( myI2Cparameters, myContrastStep.contrast );



    
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
    uint8_t          cmd  =  0U;
    SSD1306_status_t aux;


    /* Update the register    */
    cmd  =   ( SSD1306_ENTIRE_DISPLAY_ON | myEntireDisplayOn );                                                                 
    aux  =   SSD1306_SendCommand ( myI2Cparameters, cmd );


    
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
    uint8_t      cmd  = 0U;
    i2c_status_t aux;


    /* Update the register    */
    cmd  =   ( SSD1306_SET_NORMAL_INVERSE_DISPLAY | myNormalInverseDisplay );
    aux  =   SSD1306_SendCommand ( myI2Cparameters, cmd );


    
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
    uint8_t      cmd  = 0U;
    i2c_status_t aux;


    /* Update the register    */
    cmd  =   ( SSD1306_SET_DISPLAY_ON_OFF | myDisplayMode );   
    aux  =   SSD1306_SendCommand ( myI2Cparameters, cmd );


    
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
 * @brief       SSD1306_SetMultiplexRatio ( I2C_parameters_t , SSD1306_set_multiplex_ratio_t )
 *
 * @details     This command switches the default 63 multiplex mode to any multiplex ratio, ranging from 16 to 63.
 *              The output pads COM0~COM63 will be switched to the corresponding COM signal.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myMultiplexRatio:  Set MUX ratio to N+1 MUX.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SSD1306_SetMultiplexRatio.
 *
 *
 * @author      Manuel Caballero
 * @date        21/November/2018
 * @version     21/November/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SSD1306_status_t  SSD1306_SetMultiplexRatio ( I2C_parameters_t myI2Cparameters, SSD1306_set_multiplex_ratio_t myMultiplexRatio )
{
    uint8_t      cmd[]  =    { 0U, 0U, 0U, 0U };
    i2c_status_t aux;


    /* Update the register    */
    cmd[0]   =   ( SSD1306_CO_DATA_BYTES | SSD1306_DATA_COMMAND_BIT_COMMAND | SSD1306_CONTROL_BYTE );   // Control byte
    cmd[1]   =   SSD1306_SET_MULTIPLEX_RATIO;
    cmd[2]   =   cmd[0];
    cmd[3]   =   myMultiplexRatio;                                                               
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
 * @brief       SSD1306_SetDisplayOffset ( I2C_parameters_t , uint8_t )
 *
 * @details     It sets vertical shift by COM from 0-63.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myDisplayOffset: Vertical shift by COM from 0-63.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SSD1306_SetDisplayOffset.
 *
 *
 * @author      Manuel Caballero
 * @date        21/November/2018
 * @version     21/November/2018   The ORIGIN
 * @pre         The value is reset to 0x00 after RESET.
 * @warning     N/A.
 */
SSD1306_status_t  SSD1306_SetDisplayOffset ( I2C_parameters_t myI2Cparameters, uint8_t myDisplayOffset )
{
    uint8_t      cmd[]  =    { 0U, 0U };
    i2c_status_t aux;

    if ( myDisplayOffset > 63U )
    {
      aux  =   I2C_FAILURE;
    }
    else
    {
      /* Update the register    */
      cmd[0]   =   ( SSD1306_CO_DATA_BYTES | SSD1306_DATA_COMMAND_BIT_COMMAND | SSD1306_SET_DISPLAY_OFFSET );   // Control byte
      cmd[1]   =   myDisplayOffset;                                                               
      aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
    }


    
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
 * @brief       SSD1306_SetDisplayStartLine ( I2C_parameters_t , uint8_t )
 *
 * @details     Set display RAM display start line register from 0-63.
 *
 * @param[in]    myI2Cparameters:     I2C parameters.
 * @param[in]    myDisplayStartLine:  Vertical shift by COM from 0-63.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SSD1306_SetDisplayStartLine.
 *
 *
 * @author      Manuel Caballero
 * @date        21/November/2018
 * @version     21/November/2018   The ORIGIN
 * @pre         Display start line register is reset to 000000b during RESET.
 * @warning     N/A.
 */
SSD1306_status_t  SSD1306_SetDisplayStartLine ( I2C_parameters_t myI2Cparameters, uint8_t myDisplayStartLine )
{
    uint8_t      cmd  =  0U;
    i2c_status_t aux;

    if ( myDisplayStartLine > 63U )
    {
      aux  =   I2C_FAILURE;
    }
    else
    {
      /* Update the register    */
      cmd  =   ( SSD1306_SET_DISPLAY_START_LINE & myDisplayStartLine );
      aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_STOP_BIT );
    }


    
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
 * @brief       SSD1306_SetSegmentReMap ( I2C_parameters_t , SSD1306_set_segment_re_map_t )
 *
 * @details     It sets Segment Re-map.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    mySegmentReMap:  Colum address mapped to SEG0.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SSD1306_SetSegmentReMap.
 *
 *
 * @author      Manuel Caballero
 * @date        21/November/2018
 * @version     21/November/2018   The ORIGIN
 * @pre         Column address 0 is mapped to SEG0 during RESET.
 * @warning     N/A.
 */
SSD1306_status_t  SSD1306_SetSegmentReMap ( I2C_parameters_t myI2Cparameters, SSD1306_set_segment_re_map_t mySegmentReMap )
{
    uint8_t      cmd  =  0U;
    i2c_status_t aux;

    /* Update the register    */
    cmd  =   mySegmentReMap;
    aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_STOP_BIT );


    
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
 * @brief       SSD1306_SetCOM_OutputScanDirection ( I2C_parameters_t , SSD1306_set_com_output_scan_direction_t )
 *
 * @details     It sets COM Output Scan Direction.
 *
 * @param[in]    myI2Cparameters: I2C parameters.
 * @param[in]    myScanDirection: Normal/Remapped mode.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SSD1306_SetCOM_OutputScanDirection.
 *
 *
 * @author      Manuel Caballero
 * @date        21/November/2018
 * @version     21/November/2018   The ORIGIN
 * @pre         Normal mode ( RESET ) Scan from COM0 to COM[N –1].
 * @warning     N/A.
 */
SSD1306_status_t  SSD1306_SetCOM_OutputScanDirection ( I2C_parameters_t myI2Cparameters, SSD1306_set_com_output_scan_direction_t myScanDirection )
{
    uint8_t      cmd  =  0U;
    i2c_status_t aux;

    /* Update the register    */
    cmd  =   myScanDirection;
    aux  =   i2c_write ( myI2Cparameters, &cmd, 1U, I2C_STOP_BIT );


    
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
 * @brief       SSD1306_SetCOM_PinsHardwareConfiguration ( I2C_parameters_t , SSD1306_com_pin_configuration_t , SSD1306_com_left_right_re_map_t )
 *
 * @details     It sets COM Pins Hardware Configuration.
 *
 * @param[in]    myI2Cparameters:         I2C parameters.
 * @param[in]    myCOM_PinConfiguration:  COM pin configuration.
 * @param[in]    myCOM_LeftRightEnable:   COM Left/Right remap.
 *
 * @param[out]   N/A.
 *
 *
 * @return       Status of SSD1306_SetCOM_PinsHardwareConfiguration.
 *
 *
 * @author      Manuel Caballero
 * @date        21/November/2018
 * @version     21/November/2018   The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
SSD1306_status_t  SSD1306_SetCOM_PinsHardwareConfiguration ( I2C_parameters_t myI2Cparameters, SSD1306_com_pin_configuration_t myCOM_PinConfiguration, SSD1306_com_left_right_re_map_t myCOM_LeftRightEnable )
{
    uint8_t      cmd[]  =    { 0U, 0U };
    i2c_status_t aux;

    /* Update the register    */
    cmd[0]   =   ( SSD1306_CO_DATA_BYTES | SSD1306_DATA_COMMAND_BIT_COMMAND | SSD1306_SET_COM_PINS_HARDWARE_CONFIGURATION );  // Control byte
    cmd[1]   =   ( 0x02 | myCOM_PinConfiguration | myCOM_LeftRightEnable );                                                               
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