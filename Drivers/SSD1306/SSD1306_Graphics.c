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
