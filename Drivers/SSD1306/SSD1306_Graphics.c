/**
 * @brief       SSD1306_Graphics.c
 * @details     Grpahics functionalities for 128 x 64 Dot Matrix OLED/PLED Segment/Common Driver with Controller.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        18/December/2018
 * @version     18/December/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com/ ).
 */

#include "SSD1306_Graphics.h"


///**
// * @brief       SSD1306_Init ( I2C_parameters_t )
// *
// * @details     It configures the I2C peripheral.
// *
// * @param[in]    myI2Cparameters:       I2C parameters.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_Init.
// *
// *
// * @author      Manuel Caballero
// * @date        3/November/2018
// * @version     3/November/2018   The ORIGIN
// * @pre         N/A
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_Init ( I2C_parameters_t myI2Cparameters )
//{
//    i2c_status_t aux;
//
//    aux  =   i2c_init ( myI2Cparameters );
//
//
//
//    if ( aux == I2C_SUCCESS )
//    {
//        return   SSD1306_SUCCESS;
//    }
//    else
//    {
//        return   SSD1306_FAILURE;
//    }
//}
//
//
//
/////**
//// * @brief       SSD1306_SendData ( I2C_parameters_t , uint8_t* , uint8_t )
//// *
//// * @details     It sends a command byte to SSD1306.
//// *
//// * @param[in]    myI2Cparameters: I2C parameters.
//// * @param[in]    myData:          Data.
//// * @param[in]    myDataSize:      Amount of data to be sent.
//// *
//// * @param[out]   N/A.
//// *
//// *
//// * @return       Status of SSD1306_SendData.
//// *
//// *
//// * @author      Manuel Caballero
//// * @date        22/November/2018
//// * @version     22/November/2018   The ORIGIN
//// * @pre         N/A.
//// * @warning     N/A.
//// */
////SSD1306_status_t  SSD1306_SendData ( I2C_parameters_t myI2Cparameters, uint8_t* myData, uint8_t myDataSize )
////{
////    uint8_t      *cmd;
////    i2c_status_t aux;
////
////    *cmd++   =   ( SSD1306_DATA_COMMAND_BIT_DATA | ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
////    cmd   =   myData;
////
////    /* Send a new data value    */                                                             
////    aux      =   i2c_write ( myI2Cparameters, &cmd[0], myDataSize, I2C_STOP_BIT );
////
////
////    
////    if ( aux == I2C_SUCCESS )
////    {
////        return   SSD1306_SUCCESS;
////    }
////    else
////    {
////        return   SSD1306_FAILURE;
////    }
////}
//
//
//
///**
// * @brief       SSD1306_SetContrastControl ( I2C_parameters_t , SSD1306_vector_data_t )
// *
// * @details     It sets the constrast value to select 1 out of 256 contrast steps.
// *
// * @param[in]    myI2Cparameters: I2C parameters.
// * @param[in]    myContrastStep:  Constrast value to select 1 out of 256 contrast steps.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SetContrastControl.
// *
// *
// * @author      Manuel Caballero
// * @date        4/November/2018
// * @version     8/December/2018   Fixed! The command register must be sent first!
// *              4/November/2018   The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SetContrastControl ( I2C_parameters_t myI2Cparameters, SSD1306_vector_data_t myContrastStep )
//{
//    uint8_t      cmd[]  =    { 0U, 0U, 0U };
//    i2c_status_t aux;
//
//
//    /* Update the register    */
//    cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//    cmd[1]   =   SSD1306_SET_CONTRAST_CONTROL;                                                              // Data byte
//    cmd[2]   =   myContrastStep.contrast;                                                                   // Data byte
//    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//    
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SetEntireDisplay ( I2C_parameters_t , SSD1306_entire_display_on_t )
// *
// * @details     It sets if the display's output follows RAM content or ignores it.
// *
// * @param[in]    myI2Cparameters:   I2C parameters.
// * @param[in]    myEntireDisplayOn: Display's output follows RAM content or ignores it.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SetEntireDisplay.
// *
// *
// * @author      Manuel Caballero
// * @date        4/November/2018
// * @version     4/November/2018   The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SetEntireDisplay ( I2C_parameters_t myI2Cparameters, SSD1306_entire_display_on_t myEntireDisplayOn )
//{
//    uint8_t      cmd[]  =    { 0U, 0U };
//    i2c_status_t aux;
//
//
//    /* Update the register    */
//    cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//    cmd[1]   =   ( SSD1306_ENTIRE_DISPLAY_ON | myEntireDisplayOn );                                         // Data byte
//    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//    
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SetNormalInverseDisplay ( I2C_parameters_t , SSD1306_set_normal_inverse_display_t )
// *
// * @details     It sets normal/inverse display.
// *
// * @param[in]    myI2Cparameters:        I2C parameters.
// * @param[in]    myNormalInverseDisplay: Normal/Inverse display.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SetNormalInverseDisplay.
// *
// *
// * @author      Manuel Caballero
// * @date        4/November/2018
// * @version     4/November/2018   The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SetNormalInverseDisplay ( I2C_parameters_t myI2Cparameters, SSD1306_set_normal_inverse_display_t myNormalInverseDisplay )
//{
//    uint8_t      cmd[]  =    { 0U, 0U };
//    i2c_status_t aux;
//
//
//    /* Update the register    */
//    cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//    cmd[1]   =   ( SSD1306_SET_NORMAL_INVERSE_DISPLAY | myNormalInverseDisplay );                           // Data byte
//    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//    
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SetDisplay ( I2C_parameters_t , SSD1306_set_display_t )
// *
// * @details     It sets display ON/OFF.
// *
// * @param[in]    myI2Cparameters: I2C parameters.
// * @param[in]    myDisplayMode:   Display is ON/OFF.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SetDisplay.
// *
// *
// * @author      Manuel Caballero
// * @date        4/November/2018
// * @version     4/November/2018   The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SetDisplay ( I2C_parameters_t myI2Cparameters, SSD1306_set_display_t myDisplayMode )
//{
//    uint8_t      cmd[]  =    { 0U, 0U };
//    i2c_status_t aux;
//
//
//    /* Update the register    */
//    cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//    cmd[1]   =   ( SSD1306_SET_DISPLAY_ON_OFF | myDisplayMode );                                            // Data byte
//    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//    
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SetMultiplexRatio ( I2C_parameters_t , SSD1306_set_multiplex_ratio_t )
// *
// * @details     This command switches the default 63 multiplex mode to any multiplex ratio, ranging from 16 to 63.
// *              The output pads COM0~COM63 will be switched to the corresponding COM signal.
// *
// * @param[in]    myI2Cparameters:   I2C parameters.
// * @param[in]    myMultiplexRatio:  Set MUX ratio to N+1 MUX.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SetMultiplexRatio.
// *
// *
// * @author      Manuel Caballero
// * @date        21/November/2018
// * @version     3/December/2018    Updated to the new architecture
// *              21/November/2018   The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SetMultiplexRatio ( I2C_parameters_t myI2Cparameters, SSD1306_set_multiplex_ratio_t myMultiplexRatio )
//{
//    uint8_t      cmd[]  =    { 0U, 0U, 0U };
//    i2c_status_t aux;
//
//
//    /* Update the register    */
//    cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//    cmd[1]   =   SSD1306_SET_MULTIPLEX_RATIO;                                                               // Data byte
//    cmd[2]   =   myMultiplexRatio;                                                                          // Data byte
//    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//    
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SetDisplayOffset ( I2C_parameters_t , uint8_t )
// *
// * @details     It sets vertical shift by COM from 0-63.
// *
// * @param[in]    myI2Cparameters: I2C parameters.
// * @param[in]    myDisplayOffset: Vertical shift by COM from 0-63.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SetDisplayOffset.
// *
// *
// * @author      Manuel Caballero
// * @date        21/November/2018
// * @version     21/November/2018   The ORIGIN
// * @pre         The value is reset to 0x00 after RESET.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SetDisplayOffset ( I2C_parameters_t myI2Cparameters, uint8_t myDisplayOffset )
//{
//    uint8_t      cmd[]  =    { 0U, 0U, 0U };
//    i2c_status_t aux;
//
//
//    if ( myDisplayOffset > 63U )
//    {
//      aux  =   I2C_FAILURE;
//    }
//    else
//    {
//      /* Update the register    */
//      cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//      cmd[1]   =   SSD1306_SET_DISPLAY_OFFSET;                                                                // Data byte
//      cmd[2]   =   myDisplayOffset;                                                                           // Data byte
//      aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//    }
//
//
//    
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SetDisplayStartLine ( I2C_parameters_t , uint8_t )
// *
// * @details     Set display RAM display start line register from 0-63.
// *
// * @param[in]    myI2Cparameters:     I2C parameters.
// * @param[in]    myDisplayStartLine:  Vertical shift by COM from 0-63.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SetDisplayStartLine.
// *
// *
// * @author      Manuel Caballero
// * @date        21/November/2018
// * @version     3/December/2018    Updated to the new architecture
// *              21/November/2018   The ORIGIN
// * @pre         Display start line register is reset to 000000b during RESET.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SetDisplayStartLine ( I2C_parameters_t myI2Cparameters, uint8_t myDisplayStartLine )
//{
//    uint8_t      cmd[]  =    { 0U, 0U };
//    i2c_status_t aux;
//
//
//    if ( myDisplayStartLine > 63U )
//    {
//      aux  =   I2C_FAILURE;
//    }
//    else
//    {
//      /* Update the register    */
//      cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//      cmd[1]   =   ( SSD1306_SET_DISPLAY_START_LINE | myDisplayStartLine );                                   // Data byte
//      aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//    }
//    
//
//    
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SetSegmentReMap ( I2C_parameters_t , SSD1306_set_segment_re_map_t )
// *
// * @details     It sets Segment Re-map.
// *
// * @param[in]    myI2Cparameters: I2C parameters.
// * @param[in]    mySegmentReMap:  Colum address mapped to SEG0.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SetSegmentReMap.
// *
// *
// * @author      Manuel Caballero
// * @date        21/November/2018
// * @version     3/December/2018    Updated to the new architecture
// *              21/November/2018   The ORIGIN
// * @pre         Column address 0 is mapped to SEG0 during RESET.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SetSegmentReMap ( I2C_parameters_t myI2Cparameters, SSD1306_set_segment_re_map_t mySegmentReMap )
//{
//    uint8_t      cmd[]  =    { 0U, 0U };
//    i2c_status_t aux;
//
//
//    /* Update the register    */
//    cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//    cmd[1]   =   mySegmentReMap;                                                                            // Data byte
//    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//    
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SetCOM_OutputScanDirection ( I2C_parameters_t , SSD1306_set_com_output_scan_direction_t )
// *
// * @details     It sets COM Output Scan Direction.
// *
// * @param[in]    myI2Cparameters: I2C parameters.
// * @param[in]    myScanDirection: Normal/Remapped mode.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SetCOM_OutputScanDirection.
// *
// *
// * @author      Manuel Caballero
// * @date        21/November/2018
// * @version     3/December/2018    Updated to the new architecture
// *              21/November/2018   The ORIGIN
// * @pre         Normal mode ( RESET ) Scan from COM0 to COM[N –1].
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SetCOM_OutputScanDirection ( I2C_parameters_t myI2Cparameters, SSD1306_set_com_output_scan_direction_t myScanDirection )
//{
//    uint8_t      cmd[]  =    { 0U, 0U };
//    i2c_status_t aux;
//
//
//    /* Update the register    */
//    cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//    cmd[1]   =   myScanDirection;                                                                           // Data byte
//    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//    
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SetCOM_PinsHardwareConfiguration ( I2C_parameters_t , SSD1306_com_pin_configuration_t , SSD1306_com_left_right_re_map_t )
// *
// * @details     It sets COM Pins Hardware Configuration.
// *
// * @param[in]    myI2Cparameters:         I2C parameters.
// * @param[in]    myCOM_PinConfiguration:  COM pin configuration.
// * @param[in]    myCOM_LeftRightEnable:   COM Left/Right remap.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SetCOM_PinsHardwareConfiguration.
// *
// *
// * @author      Manuel Caballero
// * @date        21/November/2018
// * @version     3/December/2018    Updated to the new architecture
// *              21/November/2018   The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SetCOM_PinsHardwareConfiguration ( I2C_parameters_t myI2Cparameters, SSD1306_com_pin_configuration_t myCOM_PinConfiguration, SSD1306_com_left_right_re_map_t myCOM_LeftRightEnable )
//{
//    uint8_t      cmd[]  =    { 0U, 0U, 0U };
//    i2c_status_t aux;
//
//
//    /* Update the register    */
//    cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//    cmd[1]   =   SSD1306_SET_COM_PINS_HARDWARE_CONFIGURATION;                                               // Data byte
//    cmd[2]   =   ( myCOM_PinConfiguration | myCOM_LeftRightEnable );                                        // Data byte
//    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//    
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SetDisplayClockDivideRatio_OscFreq ( I2C_parameters_t , uint8_t , uint8_t )
// *
// * @details     It sets Display Clock Divide Ratio/Oscillator Frequency.
// *
// * @param[in]    myI2Cparameters:           I2C parameters.
// * @param[in]    myOscillatorFrequency:     Set the divide ratio to generate DCLK (Display Clock) from CLK. 
// *                                          The divide ratio is from 1 to 16, with reset value = 1.
// * @param[in]    myDisplayClockDivideRatio: Program the oscillator frequency Fosc that is the source of CLK.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SetDisplayClockDivideRatio_OscFreq.
// *
// *
// * @author      Manuel Caballero
// * @date        3/December/2018
// * @version     3/December/2018    The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SetDisplayClockDivideRatio_OscFreq ( I2C_parameters_t myI2Cparameters, uint8_t myOscillatorFrequency, uint8_t myDisplayClockDivideRatio )
//{
//    uint8_t      cmd[]  =    { 0U, 0U, 0U };
//    i2c_status_t aux;
//
//    
//    if ( ( myOscillatorFrequency > 0x0F ) || ( myDisplayClockDivideRatio > 0x0E ) )
//    {
//      return I2C_FAILURE;
//    }
//    else
//    {
//      /* Update the register    */
//      cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//      cmd[1]   =   SSD1306_SET_DISPLAY_CLOCK_DIVIDE_RATIO_OSC_FREQ;                                           // Data byte
//      cmd[2]   =   ( ( myOscillatorFrequency << 4U ) | myDisplayClockDivideRatio );                           // Data byte
//      aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//    }
//
//
//    
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SePreChargePeriod ( I2C_parameters_t , uint8_t , uint8_t )
// *
// * @details     It sets Display Clock Divide Ratio/Oscillator Frequency.
// *
// * @param[in]    myI2Cparameters:    I2C parameters.
// * @param[in]    myPreChargePeriod1: Phase 1. Set the duration of the pre-charge period ( RESET = 2h ).
// * @param[in]    myPreChargePeriod2: Phase 2. Set the duration of the pre-charge period ( RESET = 2h ).
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SePreChargePeriod.
// *
// *
// * @author      Manuel Caballero
// * @date        3/December/2018
// * @version     3/December/2018    The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SePreChargePeriod ( I2C_parameters_t myI2Cparameters, uint8_t myPreChargePeriodPhase1, uint8_t myPreChargePeriodPhase2 )
//{
//    uint8_t      cmd[]  =    { 0U, 0U, 0U };
//    i2c_status_t aux;
//
//    
//    if ( ( ( myPreChargePeriodPhase1 == 0x00 ) || ( myPreChargePeriodPhase1 == 0x0F ) ) || ( ( myPreChargePeriodPhase2 == 0x00 ) || ( myPreChargePeriodPhase2 == 0x0F ) ) )
//    {
//      return I2C_FAILURE;
//    }
//    else
//    {
//      /* Update the register    */
//      cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//      cmd[1]   =   SSD1306_SET_PRE_CHARGE_PERIOD;                                                             // Data byte
//      cmd[2]   =   ( myPreChargePeriodPhase2 << 4U ) | ( myPreChargePeriodPhase1 );                           // Data byte
//      aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//    }
//
//
//    
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SeVCOMH_DeselectLevel ( I2C_parameters_t , SSD1306_v_comh_deselect_level_t )
// *
// * @details     It adjusts the VCOMH regulator output.
// *
// * @param[in]    myI2Cparameters:       I2C parameters.
// * @param[in]    myVCOMH_DeselctLevel:  V_COMH deselect level.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SeVCOMH_DeselectLevel.
// *
// *
// * @author      Manuel Caballero
// * @date        3/December/2018
// * @version     3/December/2018    The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SeVCOMH_DeselectLevel ( I2C_parameters_t myI2Cparameters, SSD1306_v_comh_deselect_level_t myVCOMH_DeselctLevel )
//{
//    uint8_t      cmd[]  =    { 0U, 0U, 0U };
//    i2c_status_t aux;
//
//    
//    /* Update the register    */
//    cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//    cmd[1]   =   SSD1306_SET_V_COMH_DESELECT_LEVEL;                                                         // Data byte
//    cmd[2]   =   myVCOMH_DeselctLevel;                                                                      // Data byte
//    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_NopCommand ( I2C_parameters_t )
// *
// * @details     No Operation Command.
// *
// * @param[in]    myI2Cparameters:       I2C parameters.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_NopCommand.
// *
// *
// * @author      Manuel Caballero
// * @date        3/December/2018
// * @version     3/December/2018    The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_NopCommand ( I2C_parameters_t myI2Cparameters )
//{
//    uint8_t      cmd[]  =    { 0U, 0U };
//    i2c_status_t aux;
//
//    
//    /* Update the register    */
//    cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//    cmd[1]   =   SSD1306_NOP;                                                                               // Data byte
//    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SetHorizontalScrollSetup ( I2C_parameters_t , SSD1306_horizontal_scroll_t , SSD1306_horizontal_scroll_start_page_address_t , SSD1306_horizontal_scroll_frame_frequency_t, SSD1306_horizontal_scroll_end_page_address_t )
// *
// * @details     No Operation Command.
// *
// * @param[in]    myI2Cparameters:             I2C parameters.
// * @param[in]    myRightLeftHorizontalScroll: Right/Left horizontal scroll.
// * @param[in]    myStartPageAddr:             Define start page address.
// * @param[in]    myFrames:                    Frame frequency.
// * @param[in]    myEndPageAddr:               Define end page address.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SetHorizontalScrollSetup.
// *
// *
// * @author      Manuel Caballero
// * @date        4/December/2018
// * @version     4/December/2018    The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SetHorizontalScrollSetup ( I2C_parameters_t myI2Cparameters, SSD1306_horizontal_scroll_t myRightLeftHorizontalScroll, SSD1306_horizontal_scroll_start_page_address_t myStartPageAddr, SSD1306_horizontal_scroll_frame_frequency_t myFrames, SSD1306_horizontal_scroll_end_page_address_t myEndPageAddr )
//{
//    uint8_t      cmd[8]  =    { 0U };
//    i2c_status_t aux;
//
//    
//    /* Update the register    */
//    cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//    cmd[1]   =   myRightLeftHorizontalScroll;                                                               // Data byte
//    cmd[2]   =   0x00;                                                                                      // Data byte ( dummy byte ) 
//    cmd[3]   =   myStartPageAddr;                                                                           // Data byte ( start page )
//    cmd[4]   =   myFrames;                                                                                  // Data byte ( frame frequency )
//    cmd[5]   =   myEndPageAddr;                                                                             // Data byte ( end page )
//    cmd[6]  =   0x00;                                                                                      // Data byte ( dummy byte ) 
//    cmd[7]  =   0xFF;                                                                                      // Data byte ( dummy byte ) 
//    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SetContinuousHorizontalVerticalScrollSetup ( I2C_parameters_t , SSD1306_horizontal_scroll_t , SSD1306_horizontal_scroll_start_page_address_t , SSD1306_horizontal_scroll_frame_frequency_t, SSD1306_horizontal_scroll_end_page_address_t , SSD1306_vertical_scrolling_offset_t )
// *
// * @details     No Operation Command.
// *
// * @param[in]    myI2Cparameters:                           I2C parameters.
// * @param[in]    myContinuousVerticalHorizontalScrollSetup: Continuos Vertical Right/Left horizontal scroll.
// * @param[in]    myStartPageAddr:                           Define start page address.
// * @param[in]    myFrames:                                  Frame frequency.
// * @param[in]    myEndPageAddr:                             Define end page address.
// * @param[in]    myVerticalScrollingOffset:                 Define vertical scrolling offset.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SetContinuousHorizontalVerticalScrollSetup.
// *
// *
// * @author      Manuel Caballero
// * @date        5/December/2018
// * @version     5/December/2018    The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SetContinuousHorizontalVerticalScrollSetup ( I2C_parameters_t myI2Cparameters, SSD1306_continuous_vertical_right_left_horizontal_scroll_t myContinuousVerticalHorizontalScrollSetup, SSD1306_horizontal_scroll_start_page_address_t myStartPageAddr, SSD1306_horizontal_scroll_frame_frequency_t myFrames, SSD1306_horizontal_scroll_end_page_address_t myEndPageAddr, SSD1306_vertical_scrolling_offset_t myVerticalScrollingOffset )
//{
//    uint8_t      cmd[6]  =    { 0U };
//    i2c_status_t aux;
//
//    
//    /* Update the register    */
//    cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//    cmd[1]   =   myContinuousVerticalHorizontalScrollSetup;                                                 // Data byte ( Vertical and Right/Left Horizontal Scroll )
//    cmd[2]   =   0x00;                                                                                      // Data byte ( dummy byte ) 
//    cmd[3]   =   myStartPageAddr;                                                                           // Data byte ( start page )
//    cmd[4]   =   myFrames;                                                                                  // Data byte ( frame frequency )
//    cmd[5]   =   myEndPageAddr;                                                                             // Data byte ( end page )
//    cmd[6]  =   myVerticalScrollingOffset;                                                                 // Data byte ( Vertical scrolling offset )  
//    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_DeactivateScroll ( I2C_parameters_t )
// *
// * @details     Deactivate Scroll.
// *
// * @param[in]    myI2Cparameters: I2C parameters.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_DeactivateScroll.
// *
// *
// * @author      Manuel Caballero
// * @date        5/December/2018
// * @version     5/December/2018    The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_DeactivateScroll ( I2C_parameters_t myI2Cparameters )
//{
//    uint8_t      cmd[]  =    { 0U, 0U };
//    i2c_status_t aux;
//
//    
//    /* Update the register    */
//    cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//    cmd[1]   =   SSD1306_DEACTIVATE_SCROLL;                                                                 // Data byte 
//    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_ActivateScroll ( I2C_parameters_t )
// *
// * @details     Activate Scroll.
// *
// * @param[in]    myI2Cparameters: I2C parameters.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_ActivateScroll.
// *
// *
// * @author      Manuel Caballero
// * @date        5/December/2018
// * @version     5/December/2018    The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_ActivateScroll ( I2C_parameters_t myI2Cparameters )
//{
//    uint8_t      cmd[]  =    { 0U, 0U };
//    i2c_status_t aux;
//
//    
//    /* Update the register    */
//    cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//    cmd[1]   =   SSD1306_ACTIVATE_SCROLL;                                                                   // Data byte 
//    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SetVerticalScrollArea ( I2C_parameters_t , uint8_t , uint8_t )
// *
// * @details     Set Vertical Scroll Area.
// *
// * @param[in]    myI2Cparameters:     I2C parameters.
// * @param[in]    myNoRowsTopFixArea:  Set No. of rows in top fixed area.
// * @param[in]    NoRowsScrollArea:    Set No. of rows in scroll area.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SetVerticalScrollArea.
// *
// *
// * @author      Manuel Caballero
// * @date        5/December/2018
// * @version     5/December/2018    The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SetVerticalScrollArea ( I2C_parameters_t myI2Cparameters, uint8_t myNoRowsTopFixArea, uint8_t NoRowsScrollArea )
//{
//    uint8_t      cmd[4]  =    { 0U };
//    i2c_status_t aux;
//
//    
//    if ( ( myNoRowsTopFixArea > 0x3F ) || ( NoRowsScrollArea > 0x7F ) )
//    {
//      return  SSD1306_FAILURE;
//    }
//    else
//    {
//      /* Update the register    */
//      cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//      cmd[1]   =   SSD1306_SET_VERTICAL_SCROLL_AREA;                                                          // Data byte 
//      cmd[2]   =   myNoRowsTopFixArea;                                                                        // Data byte ( Set No. of rows in top fixed area )
//      cmd[3]   =   NoRowsScrollArea;                                                                          // Data byte ( Set No. of rows in scroll area )   
//      aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//    }
//    
//
//
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SetMemoryAddressingMode ( I2C_parameters_t , SSD1306_addressing_mode_t )
// *
// * @details     Set Memory Addressing Mode.
// *
// * @param[in]    myI2Cparameters:         I2C parameters.
// * @param[in]    myMemoryAddressingMode:  Memory addressing mode.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SetMemoryAddressingMode.
// *
// *
// * @author      Manuel Caballero
// * @date        6/December/2018
// * @version     6/December/2018    The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SetMemoryAddressingMode ( I2C_parameters_t myI2Cparameters, SSD1306_addressing_mode_t myMemoryAddressingMode )
//{
//    uint8_t      cmd[]  =    { 0U, 0U, 0U };
//    i2c_status_t aux;
//
//    
//    /* Update the register    */
//    cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//    cmd[1]   =   SSD1306_SET_MEMORY_ADDRESSING_MODE;                                                        // Data byte 
//    cmd[2]   =   myMemoryAddressingMode;                                                                    // Data byte 
//    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//
//
//
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SetLowerColumnStartAddressForPageAddressingMode ( I2C_parameters_t , uint8_t )
// *
// * @details     Set Lower Column Start Address for Page Addressing Mode.
// *
// * @param[in]    myI2Cparameters:           I2C parameters.
// * @param[in]    myLowerColumnStartAddress: Lower column start address.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SetLowerColumnStartAddressForPageAddressingMode.
// *
// *
// * @author      Manuel Caballero
// * @date        6/December/2018
// * @version     6/December/2018    The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SetLowerColumnStartAddressForPageAddressingMode ( I2C_parameters_t myI2Cparameters, uint8_t myLowerColumnStartAddress )
//{
//    uint8_t      cmd[]  =    { 0U, 0U };
//    i2c_status_t aux;
//
//    
//    if ( myLowerColumnStartAddress > 0x0F )
//    {
//      return  SSD1306_FAILURE;
//    }
//    else
//    {
//      /* Update the register    */
//      cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//      cmd[1]   =   myLowerColumnStartAddress;                                                                 // Data byte 
//      aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//    }
//    
//
//
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SetHigherColumnStartAddressForPageAddressingMode ( I2C_parameters_t , uint8_t )
// *
// * @details     Set Higher Column Start Address for Page Addressing Mode.
// *
// * @param[in]    myI2Cparameters:             I2C parameters.
// * @param[in]    myHigherColumnStartAddress:  Higher column start address.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SetHigherColumnStartAddressForPageAddressingMode.
// *
// *
// * @author      Manuel Caballero
// * @date        6/December/2018
// * @version     6/December/2018    The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SetHigherColumnStartAddressForPageAddressingMode ( I2C_parameters_t myI2Cparameters, uint8_t myHigherColumnStartAddress )
//{
//    uint8_t      cmd[]  =    { 0U, 0U };
//    i2c_status_t aux;
//
//    
//    myHigherColumnStartAddress  |=   0x10;
//    if ( myHigherColumnStartAddress > 0x1F )
//    {
//      return  SSD1306_FAILURE;
//    }
//    else
//    {
//      /* Update the register    */
//      cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//      cmd[1]   =   myHigherColumnStartAddress;                                                                // Data byte 
//      aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//    }
//    
//
//
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SetColumnAddress ( I2C_parameters_t , uint8_t , uint8_t )
// *
// * @details     Set Column Address.
// *
// * @param[in]    myI2Cparameters:       I2C parameters.
// * @param[in]    myColumnStartAddress:  Column start address.
// * @param[in]    myColumnEndAddress:    Column end address.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SetColumnAddress.
// *
// *
// * @author      Manuel Caballero
// * @date        6/December/2018
// * @version     6/December/2018    The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SetColumnAddress ( I2C_parameters_t myI2Cparameters, uint8_t myColumnStartAddress, uint8_t myColumnEndAddress )
//{
//    uint8_t      cmd[4]  =    { 0U };
//    i2c_status_t aux;
//
//    
//    if ( ( myColumnStartAddress > 127U ) || ( myColumnEndAddress > 127U ) )
//    {
//      return  SSD1306_FAILURE;
//    }
//    else
//    {
//      /* Update the register    */
//      cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//      cmd[1]   =   SSD1306_SET_COLUMN_ADDRESS;                                                                // Data byte 
//      cmd[2]   =   myColumnStartAddress;                                                                      // Data byte 
//      cmd[3]   =   myColumnEndAddress;                                                                        // Data byte 
//      aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//    }
//    
//
//
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SetPageAddress ( I2C_parameters_t , uint8_t , uint8_t )
// *
// * @details     Set Page Address.
// *
// * @param[in]    myI2Cparameters:     I2C parameters.
// * @param[in]    myPageStartAddress:  Page start address.
// * @param[in]    myPageEndAddress:    Page end address.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SetPageAddress.
// *
// *
// * @author      Manuel Caballero
// * @date        6/December/2018
// * @version     6/December/2018    The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SetPageAddress ( I2C_parameters_t myI2Cparameters, uint8_t myPageStartAddress, uint8_t myPageEndAddress )
//{
//    uint8_t      cmd[4]  =    { 0U };
//    i2c_status_t aux;
//
//    
//    if ( ( myPageStartAddress > 7U ) || ( myPageEndAddress > 7U ) )
//    {
//      return  SSD1306_FAILURE;
//    }
//    else
//    {
//      /* Update the register    */
//      cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//      cmd[1]   =   SSD1306_SET_PAGE_ADDRESS;                                                                  // Data byte 
//      cmd[2]   =   myPageStartAddress;                                                                        // Data byte 
//      cmd[3]   =   myPageEndAddress;                                                                          // Data byte 
//      aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//    }
//    
//
//
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SetPageAddressForPageAddressingMode ( I2C_parameters_t , SSD1306_page_start_address_mode_t )
// *
// * @details     Set Page Start Address for Page Addressing Mode.
// *
// * @param[in]    myI2Cparameters: I2C parameters.
// * @param[in]    myPageAddress:   Page start address.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SetPageAddressForPageAddressingMode.
// *
// *
// * @author      Manuel Caballero
// * @date        6/December/2018
// * @version     6/December/2018    The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SetPageAddressForPageAddressingMode ( I2C_parameters_t myI2Cparameters, SSD1306_page_start_address_mode_t myPageAddress )
//{
//    uint8_t      cmd[2]  =    { 0U };
//    i2c_status_t aux;
//
//    
//    /* Update the register    */
//    cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//    cmd[1]   =   myPageAddress;                                                                             // Data byte  
//    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//    
//
//
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}
//
//
//
///**
// * @brief       SSD1306_SetChargePumpSetting ( I2C_parameters_t , SSD1306_charge_pump_t )
// *
// * @details     Set Charge Pump Setting.
// *
// * @param[in]    myI2Cparameters: I2C parameters.
// * @param[in]    myChargePump:    Charge pump setting.
// *
// * @param[out]   N/A.
// *
// *
// * @return       Status of SSD1306_SetChargePumpSetting.
// *
// *
// * @author      Manuel Caballero
// * @date        7/December/2018
// * @version     7/December/2018    The ORIGIN
// * @pre         N/A.
// * @warning     N/A.
// */
//SSD1306_status_t  SSD1306_SetChargePumpSetting ( I2C_parameters_t myI2Cparameters, SSD1306_charge_pump_t myChargePump )
//{
//    uint8_t      cmd[3]  =    { 0U };
//    i2c_status_t aux;
//
//    
//    /* Update the register    */
//    cmd[0]   =   ( SSD1306_DATA_COMMAND_BIT_COMMAND & ( SSD1306_CO_DATA_BYTES_STREAMING & SSD1306_CONTROL_BYTE ) );   // Control byte
//    cmd[1]   =   SSD1306_CHARGE_PUMP_SETTING;                                                               // Data byte
//    cmd[2]   =   myChargePump;                                                                              // Data byte  
//    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );
//    
//
//
//    if ( aux == I2C_SUCCESS )
//    {
//      return  SSD1306_SUCCESS;
//    }
//    else
//    {
//      return  SSD1306_FAILURE;
//    }
//}