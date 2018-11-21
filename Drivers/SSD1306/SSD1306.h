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
    
    /* Set Vertical Scroll Area  */
    /* Check it!   */

    /* Hardware Configuration (Panel resolution & layout related) Command Table  */
    /* Check it!   */
    SSD1306_SET_DISPLAY_START_LINE                      =   0b01111111,            /*!<  Set display RAM display start line register from 0-63                                                                 ( RESET = 40h ) */
    SSD1306_SET_MULTIPLEX_RATIO                         =   0xA8,                  /*!<  Set MUX ratio to N + 1 MUX                                                                                                            */
    SSD1306_SET_DISPLAY_OFFSET                          =   0xD3,                  /*!<  Set vertical shift by COM from 0-63                                                                                                   */
    SSD1306_SET_COM_PINS_HARDWARE_CONFIGURATION         =   0xDA,                  /*!<  Set COM Pins Hardware configuration                                                                                                   */

    /* Timing & Driving Scheme Setting Command Table  */
    /* Check it!   */
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



/* SET MULTIPLEX RATIO
    NOTE: Set MUX ratio to N + 1 MUX
*/
typedef enum
{
    SET_MULTIPLEX_RATIO_MASK                =   ( 111111U << 0U ),  /*!<  Set Multiplex ratio mask                                          */
    SET_MULTIPLEX_RATIO_16MUX               =   15U,                /*!<  Set Multiplex ratio: 16MUX                                        */
    SET_MULTIPLEX_RATIO_17MUX               =   16U,                /*!<  Set Multiplex ratio: 17MUX                                        */
    SET_MULTIPLEX_RATIO_18MUX               =   17U,                /*!<  Set Multiplex ratio: 18MUX                                        */
    SET_MULTIPLEX_RATIO_19MUX               =   18U,                /*!<  Set Multiplex ratio: 19MUX                                        */
    SET_MULTIPLEX_RATIO_20MUX               =   19U,                /*!<  Set Multiplex ratio: 20MUX                                        */
    SET_MULTIPLEX_RATIO_21MUX               =   20U,                /*!<  Set Multiplex ratio: 21MUX                                        */
    SET_MULTIPLEX_RATIO_22MUX               =   21U,                /*!<  Set Multiplex ratio: 22MUX                                        */
    SET_MULTIPLEX_RATIO_23MUX               =   22U,                /*!<  Set Multiplex ratio: 23MUX                                        */
    SET_MULTIPLEX_RATIO_24MUX               =   23U,                /*!<  Set Multiplex ratio: 24MUX                                        */
    SET_MULTIPLEX_RATIO_25MUX               =   24U,                /*!<  Set Multiplex ratio: 25MUX                                        */
    SET_MULTIPLEX_RATIO_26MUX               =   25U,                /*!<  Set Multiplex ratio: 26MUX                                        */
    SET_MULTIPLEX_RATIO_27MUX               =   26U,                /*!<  Set Multiplex ratio: 27MUX                                        */
    SET_MULTIPLEX_RATIO_28MUX               =   27U,                /*!<  Set Multiplex ratio: 28MUX                                        */
    SET_MULTIPLEX_RATIO_29MUX               =   28U,                /*!<  Set Multiplex ratio: 29MUX                                        */
    SET_MULTIPLEX_RATIO_30MUX               =   29U,                /*!<  Set Multiplex ratio: 30MUX                                        */
    SET_MULTIPLEX_RATIO_31MUX               =   30U,                /*!<  Set Multiplex ratio: 31MUX                                        */
    SET_MULTIPLEX_RATIO_32MUX               =   31U,                /*!<  Set Multiplex ratio: 32MUX                                        */
    SET_MULTIPLEX_RATIO_33MUX               =   32U,                /*!<  Set Multiplex ratio: 33MUX                                        */
    SET_MULTIPLEX_RATIO_34MUX               =   33U,                /*!<  Set Multiplex ratio: 34MUX                                        */
    SET_MULTIPLEX_RATIO_35MUX               =   34U,                /*!<  Set Multiplex ratio: 35MUX                                        */
    SET_MULTIPLEX_RATIO_36MUX               =   35U,                /*!<  Set Multiplex ratio: 36MUX                                        */
    SET_MULTIPLEX_RATIO_37MUX               =   36U,                /*!<  Set Multiplex ratio: 37MUX                                        */
    SET_MULTIPLEX_RATIO_38MUX               =   37U,                /*!<  Set Multiplex ratio: 38MUX                                        */
    SET_MULTIPLEX_RATIO_39MUX               =   38U,                /*!<  Set Multiplex ratio: 39MUX                                        */
    SET_MULTIPLEX_RATIO_40MUX               =   39U,                /*!<  Set Multiplex ratio: 40MUX                                        */
    SET_MULTIPLEX_RATIO_41MUX               =   40U,                /*!<  Set Multiplex ratio: 41MUX                                        */
    SET_MULTIPLEX_RATIO_42MUX               =   41U,                /*!<  Set Multiplex ratio: 42MUX                                        */
    SET_MULTIPLEX_RATIO_43MUX               =   42U,                /*!<  Set Multiplex ratio: 43MUX                                        */
    SET_MULTIPLEX_RATIO_44MUX               =   43U,                /*!<  Set Multiplex ratio: 44MUX                                        */
    SET_MULTIPLEX_RATIO_45MUX               =   44U,                /*!<  Set Multiplex ratio: 45MUX                                        */
    SET_MULTIPLEX_RATIO_46MUX               =   45U,                /*!<  Set Multiplex ratio: 46MUX                                        */
    SET_MULTIPLEX_RATIO_47MUX               =   46U,                /*!<  Set Multiplex ratio: 47MUX                                        */
    SET_MULTIPLEX_RATIO_48MUX               =   47U,                /*!<  Set Multiplex ratio: 48MUX                                        */
    SET_MULTIPLEX_RATIO_49MUX               =   48U,                /*!<  Set Multiplex ratio: 49MUX                                        */
    SET_MULTIPLEX_RATIO_50MUX               =   49U,                /*!<  Set Multiplex ratio: 50MUX                                        */
    SET_MULTIPLEX_RATIO_51MUX               =   50U,                /*!<  Set Multiplex ratio: 51MUX                                        */
    SET_MULTIPLEX_RATIO_52MUX               =   51U,                /*!<  Set Multiplex ratio: 52MUX                                        */
    SET_MULTIPLEX_RATIO_53MUX               =   52U,                /*!<  Set Multiplex ratio: 53MUX                                        */
    SET_MULTIPLEX_RATIO_54MUX               =   53U,                /*!<  Set Multiplex ratio: 54MUX                                        */
    SET_MULTIPLEX_RATIO_55MUX               =   54U,                /*!<  Set Multiplex ratio: 55MUX                                        */
    SET_MULTIPLEX_RATIO_56MUX               =   55U,                /*!<  Set Multiplex ratio: 56MUX                                        */
    SET_MULTIPLEX_RATIO_57MUX               =   56U,                /*!<  Set Multiplex ratio: 57MUX                                        */
    SET_MULTIPLEX_RATIO_58MUX               =   57U,                /*!<  Set Multiplex ratio: 58MUX                                        */
    SET_MULTIPLEX_RATIO_59MUX               =   58U,                /*!<  Set Multiplex ratio: 59MUX                                        */
    SET_MULTIPLEX_RATIO_60MUX               =   59U,                /*!<  Set Multiplex ratio: 60MUX                                        */
    SET_MULTIPLEX_RATIO_61MUX               =   60U,                /*!<  Set Multiplex ratio: 61MUX                                        */
    SET_MULTIPLEX_RATIO_62MUX               =   61U,                /*!<  Set Multiplex ratio: 62MUX                                        */
    SET_MULTIPLEX_RATIO_63MUX               =   62U,                /*!<  Set Multiplex ratio: 63MUX                                        */
    SET_MULTIPLEX_RATIO_64MUX               =   63U                 /*!<  Set Multiplex ratio: 64MUX (reset)                                */
} SSD1306_set_multiplex_ratio_t;


/* SET SEGMENT RE-MAP
*/
typedef enum
{
    SET_SEGMENT_RE_MAP_MASK                 =   0b10100001,         /*!<  Set Segment re-map mask                                           */
    SET_SEGMENT_RE_MAP_COL_0_SEG0           =   0b10100000,         /*!<  Set column address 0 is mapped to SEG0                  ( RESET ) */
    SET_SEGMENT_RE_MAP_COL_127_SEG0         =   0b10100001          /*!<  Set column address 127 is mapped to SEG0                          */
} SSD1306_set_segment_re_map_t;



/* SET COM OUTPUT SCAN DIRECTION
*/
typedef enum
{
    SET_SCAN_DIR_MASK                       =   0b11001000,         /*!<  Set COM Output Scan Direction mask                                        */
    SET_SCAN_DIR_NORMAL_MODE                =   0b11000000,         /*!<  Normal mode. Scan from COM0 to COM[N –1]                        ( RESET ) */
    SET_SCAN_DIR_REMAPPED_MODE              =   0b11001000          /*!<  Remapped mode. Scan from COM[N-1] to COM0. Where N is the Multiplex ratio */
} SSD1306_set_com_output_scan_direction_t;



/**
  * @brief   SET COM PINS HARDWARE CONFIGURATION
  */
/* COM PIN CONFIGURATION
*/
typedef enum
{
    COM_PIN_CONFIGURATION_MASK                =   0b00010000,         /*!<  COM pin configuration mask                                                */
    COM_PIN_CONFIGURATION_SEQUENCTIAL_COM_PIN =   0b00000000,         /*!<  COM pin configuration: Sequential mode                          ( RESET ) */
    COM_PIN_CONFIGURATION_ALTERNATIVE_COM_PIN =   0b00010000          /*!<  COM pin configuration: Alternative mode                                   */
} SSD1306_com_pin_configuration_t;


/* COM LEFT/RIGHT RE-MAP
*/
typedef enum
{
    COM_LEFT_RIGHT_REMAP_MASK               =   0b00100000,           /*!<  COM left/right re-map mask                                                */
    COM_LEFT_RIGHT_REMAP_DISABLED           =   0b00000000,           /*!<  COM left/right re-map: Disabled                                 ( RESET ) */
    COM_LEFT_RIGHT_REMAP_ENABLED            =   0b00100000            /*!<  COM left/right re-map: Enabled                                            */
} SSD1306_com_left_right_re_map_t;






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



/** This command switches the default 63 multiplex mode to any multiplex ratio, ranging from 16 to 63. The
    output pads COM0-COM63 will be switched to the corresponding COM signal.
  */
SSD1306_status_t  SSD1306_SetMultiplexRatio                 ( I2C_parameters_t myI2Cparameters, SSD1306_set_multiplex_ratio_t myMultiplexRatio                                                                );

/** Set vertical shift by COM from 0-63.
  */
SSD1306_status_t  SSD1306_SetDisplayOffset                  ( I2C_parameters_t myI2Cparameters, uint8_t myDisplayOffset                                                                                       );

/** Set display RAM display start line register from 0-63.
  */
SSD1306_status_t  SSD1306_SetDisplayStartLine               ( I2C_parameters_t myI2Cparameters, uint8_t myDisplayStartLine                                                                                    );

/** Set Segment Re-map.
  */
SSD1306_status_t  SSD1306_SetSegmentReMap                   ( I2C_parameters_t myI2Cparameters, SSD1306_set_segment_re_map_t mySegmentReMap                                                                   );

/** Set COM Output Scan Direction.
  */
SSD1306_status_t  SSD1306_SetCOM_OutputScanDirection        ( I2C_parameters_t myI2Cparameters, SSD1306_set_com_output_scan_direction_t myScanDirection                                                       );

/** Set COM Pins Hardware Configuration.
  */
SSD1306_status_t  SSD1306_SetCOM_PinsHardwareConfiguration  ( I2C_parameters_t myI2Cparameters, SSD1306_com_pin_configuration_t myCOM_PinConfiguration, SSD1306_com_left_right_re_map_t myCOM_LeftRightEnable );


#ifdef __cplusplus
}
#endif

#endif /* SSD1306_H */
