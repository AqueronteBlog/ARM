/**
 * @brief       SSD1306.h
 * @details     128 x 64 Dot Matrix OLED/PLED Segment/Common Driver with Controller.
 *              Header file.
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


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"
#include "math.h"

#ifndef SSD1306_H_
#define SSD1306_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
  * @brief   DEFAULT ADDRESS
  */
typedef enum
{
    SSD1306_ADDRESS_SA0_GND    =   0b0111100,              /*!<   SSD1306 I2C Address: SA0 connected to GND                */
    SSD1306_ADDRESS_SA0_VCC    =   0b0111101               /*!<   SSD1306 I2C Address: SA0 connected to VCC                */
} SSD1306_address_t;


/**
  * @brief   CONTROL BYTE
  */
typedef enum
{
    SSD1306_CONTROL_BYTE  =   ( 0b00000000 )               /*!<   Control Byte = | Co | D/C# | 0 | 0 | 0 | 0 | 0 | 0 |   */
} SSD1306_control_byte_t;


/**
  * @brief   Co
  */
typedef enum
{
    SSD1306_CO_DATA_BYTES =   ( 0U << 7U )                 /*!<   The transmission of the following information will contain data bytes only */
} SSD1306_co_t;


/**
  * @brief   DATA/COMMAND SELECTION BIT
  */
typedef enum
{
    SSD1306_DATA_COMMAND_BIT_COMMAND =   ( 0U << 6U ),    /*!<   D/C# = 0 ( COMMAND )                                     */
    SSD1306_DATA_COMMAND_BIT_DATA    =   ( 1U << 6U )     /*!<   D/C# = 1 ( DATA )                                        */
} SSD1306_data_command_selection_bit_t;



/* COMMAND TABLE     */
/**
  * @brief   COMMAND TABLE
  */
typedef enum
{
    /* Fundamental Command Table   */
    SSD1306_SET_CONTRAST_CONTROL                        =   ( 0b10000001 << 0U ),  /*!<  Double byte command to select 1 out of 256 contrast steps. Contrast increases as the value increases ( Read/Write ) ( RESET = 7Fh ) */
    SSD1306_ENTIRE_DISPLAY_ON                           =   ( 0b1010010 << 1U ),   /*!<  Entire Display ON                                                                                    ( Read/Write ) ( RESET = A4h ) */
    SSD1306_SET_NORMAL_INVERSE_DISPLAY                  =   ( 0b1010011 << 1U ),   /*!<  Set Normal/Inverse Display                                                                           ( Read/Write ) ( RESET = A6h ) */
    SSD1306_SET_DISPLAY_ON_OFF                          =   ( 0b1010111 << 1U ),   /*!<  Set Display ON/OFF                                                                                   ( Read/Write ) ( RESET = AEh ) */
    
    /* Horizontal Scrolling Command Table   */
    SSD1306_HORIZONTAL_SCROLL                           =   ( 0b0010011 << 1U ),   /*!<  Continuous Horizontal Scroll                                                                                                        */
    SSD1306_HORIZONTAL_SCROLL_DUMMY_BYTE                =   ( 0b00000000 << 0U ),  /*!<  Dummy byte ( Set as 00h )                                                                                                           */
    SSD1306_HORIZONTAL_SCROLL_DEFINE_START_PAGE_ADDRESS =   ( 0b00000000 << 3U ),  /*!<  Define start page address                                                                                                           */
    SSD1306_HORIZONTAL_SCROLL_SET_TIME_INTERVAL         =   ( 0b00000000 << 3U ),  /*!<  Set time interval between each scroll step in terms of frame frequency                                                              */
    SSD1306_HORIZONTAL_SCROLL_DEFINE_END_PAGE_ADDRESS   =   ( 0b00000000 << 3U ),  /*!<  Define end page address                                                                                                             */
    
    /* Vertical Scrolling Command Table   */
    SSD1306_VERTICAL_SCROLL                             =   ( 0b001010 << 2U ),    /*!<  Continuous Vertical Scroll                                                                                                          */
    SSD1306_VERTICAL_SCROLL_DUMMY_BYTE                  =   ( 0b00000000 << 0U ),  /*!<  Dummy byte ( Set as 00h )                                                                                                           */
    SSD1306_VERTICAL_SCROLL_DEFINE_START_PAGE_ADDRESS   =   ( 0b00000000 << 3U ),  /*!<  Define start page address                                                                                                           */
    SSD1306_VERTICAL_SCROLL_SET_TIME_INTERVAL           =   ( 0b00000000 << 3U ),  /*!<  Set time interval between each scroll step in terms of frame frequency                                                              */
    SSD1306_VERTICAL_SCROLL_DEFINE_END_PAGE_ADDRESS     =   ( 0b00000000 << 3U ),  /*!<  Define end page address                                                                                                             */
    SSD1306_VERTICAL_SCROLL_OFFSET                      =   ( 0b00000000 << 6U ),  /*!<  Vertical scrolling offset                                                                                                           */
    
    /* General Scrolling Command Table   */
    SSD1306_DEACTIVATE_SCROLL                           =   0x2E,                  /*!<  Stop scrolling that is configured by command                                                                                        */
    SSD1306_ACTIVATE_SCROLL                             =   0x2F,                  /*!<  Start scrolling that is configured by the scrolling setup commands                                                                  */
    
} SSD1306_command_table_t;



/* ENTIRE DISPLAY ON  */
typedef enum
{
    ENTIRE_DISPLAY_ON_MASK                  =   ( 1U << 0U ),     /*!<  Entire Display ON mask                                              */
    ENTIRE_DISPLAY_ON_RESUME_TO_RAM_CONTENT =   ( 0U << 0U ),     /*!<  Resume to RAM content display ( RESET ). Output follows RAM content */
    ENTIRE_DISPLAY_ON_IGNORE_RAM_CONTENT    =   ( 1U << 0U )      /*!<  Entire display ON Output ignores RAM content                        */
} SSD1306_entire_display_on_t;


/* SET NORMAL/INVERSE DISPLAY  */
typedef enum
{
    SET_DISPLAY_MASK                        =   ( 1U << 0U ),     /*!<  Set Display mask                                                    */
    SET_DISPLAY_NORMAL_DISPLAY              =   ( 0U << 0U ),     /*!<  Normal display ( RESET )                                            */
    SET_DISPLAY_INVERSE_DISPLAY             =   ( 1U << 0U )      /*!<  Inverse display                                                     */
} SSD1306_set_normal_inverse_display_t;


/* SET DISPLAY ON/OFF  */
typedef enum
{
    SET_DISPLAY_ON_OFF_MASK                 =   ( 1U << 0U ),     /*!<  Set Display on/off mask                                             */
    SET_DISPLAY_ON_OFF_DISPLAY_OFF          =   ( 0U << 0U ),     /*!<  Display OFF ( sleep mode ) ( RESET )                                */
    SET_DISPLAY_ON_OFF_DISPLAY_ON           =   ( 1U << 0U )      /*!<  Display ON in normal mode                                           */
} SSD1306_set_display_t;



#ifndef SSD1306_VECTOR_STRUCT_H
#define SSD1306_VECTOR_STRUCT_H
typedef struct
{
    uint8_t contrast;               /*!<  Display constrats         */
} SSD1306_vector_data_t;
#endif



/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    SSD1306_SUCCESS     =       0,
    SSD1306_FAILURE     =       1
} SSD1306_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
SSD1306_status_t  SSD1306_Init                    ( I2C_parameters_t myI2Cparameters                                                              );

/** It sets the constrast value to select 1 out of 256 contrast steps.
  */
SSD1306_status_t  SSD1306_SetContrastControl      ( I2C_parameters_t myI2Cparameters, SSD1306_vector_data_t myContrastStep                        );

/** It sets if the display's output follows RAM content or ignores it.
  */
SSD1306_status_t  SSD1306_SetEntireDisplay        ( I2C_parameters_t myI2Cparameters, SSD1306_entire_display_on_t myEntireDisplayOn               );

/** It sets normal/inverse display.
  */
SSD1306_status_t  SSD1306_SetNormalInverseDisplay ( I2C_parameters_t myI2Cparameters, SSD1306_set_normal_inverse_display_t myNormalInverseDisplay );

/** It sets display ON/OFF.
  */
SSD1306_status_t  SSD1306_SetDisplay              ( I2C_parameters_t myI2Cparameters, SSD1306_set_display_t myDisplayMode                         );


#ifdef __cplusplus
}
#endif

#endif /* SSD1306_H */
