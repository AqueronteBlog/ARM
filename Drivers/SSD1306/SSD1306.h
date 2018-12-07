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
  * @brief   FUNDAMENTAL COMMAND TABLE
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
    SSD1306_VERTICAL_SCROLL                             =   ( 0b001010 << 2U ),    /*!<  Continuous Vertical Scroll                                                                                                           */
    SSD1306_VERTICAL_SCROLL_DUMMY_BYTE                  =   ( 0b00000000 << 0U ),  /*!<  Dummy byte ( Set as 00h )                                                                                                            */
    SSD1306_VERTICAL_SCROLL_DEFINE_START_PAGE_ADDRESS   =   ( 0b00000000 << 3U ),  /*!<  Define start page address                                                                                                            */
    SSD1306_VERTICAL_SCROLL_SET_TIME_INTERVAL           =   ( 0b00000000 << 3U ),  /*!<  Set time interval between each scroll step in terms of frame frequency                                                               */
    SSD1306_VERTICAL_SCROLL_DEFINE_END_PAGE_ADDRESS     =   ( 0b00000000 << 3U ),  /*!<  Define end page address                                                                                                              */
    SSD1306_VERTICAL_SCROLL_OFFSET                      =   ( 0b00000000 << 6U ),  /*!<  Vertical scrolling offset                                                                                                            */
    
    /* Addressing Setting Command Table  */
    SSD1306_SET_MEMORY_ADDRESSING_MODE                  =   0x20,                  /*!<  Set addressing mode                                                                                                                  */
    SSD1306_SET_COLUMN_ADDRESS                          =   0x21,                  /*!<  Set column address                                                                                                                   */
    SSD1306_SET_PAGE_ADDRESS                            =   0x22,                  /*!<  Set page address                                                                                                                     */
    
    /* Hardware Configuration (Panel resolution & layout related) Command Table  */
    SSD1306_SET_DISPLAY_START_LINE                      =   ( 0b01 << 6U ),        /*!<  Set display RAM display start line register from 0-63                                                                 ( RESET = 40h ) */
    SSD1306_SET_MULTIPLEX_RATIO                         =   0xA8,                  /*!<  Set MUX ratio to N + 1 MUX                                                                                                            */
    SSD1306_SET_DISPLAY_OFFSET                          =   0xD3,                  /*!<  Set vertical shift by COM from 0-63                                                                                                   */
    SSD1306_SET_COM_PINS_HARDWARE_CONFIGURATION         =   0xDA,                  /*!<  Set COM Pins Hardware configuration                                                                                                   */

    /* Timing & Driving Scheme Setting Command Table  */
    SSD1306_SET_DISPLAY_CLOCK_DIVIDE_RATIO_OSC_FREQ     =   0xD5,                  /*!<  Set Display Clock Divide Ratio/ Oscillator Frequency                                                                                  */
    SSD1306_SET_PRE_CHARGE_PERIOD                       =   0xD9,                  /*!<  Set Pre-charge Period                                                                                                                 */
    SSD1306_SET_V_COMH_DESELECT_LEVEL                   =   0xDB,                  /*!<  Set VCOMH Deselect level                                                                                                              */
    SSD1306_NOP                                         =   0xE3                   /*!<  No operation command                                                                                                                  */
} SSD1306_fundamental_command_t;


/**
  * @brief   GRAPHIC ACCELERATION COMMAND TABLE
  */
typedef enum
{
    /*  Scrolling Command Table   */
    SSD1306_DEACTIVATE_SCROLL                           =   0x2E,                  /*!<  Deactivate scroll                                                                                                                    */
    SSD1306_ACTIVATE_SCROLL                             =   0x2F,                  /*!<  Activate scroll                                                                                                                      */                                                                
    SSD1306_SET_VERTICAL_SCROLL_AREA                    =   0xA3                   /*!<  Set vertical scroll area                                                                                                             */                                                                
} SSD1306_graphic_acceleration_command_t;


/**
  * @brief   COMMAND TABLE FOR CHARGE BUMP SETTINGS
  */
typedef enum
{
    /*  Charge Pump Command Table   */
    SSD1306_CHARGE_PUMP_SETTING                         =   0x8D                   /*!<  Charge pump setting                                                                                                                  */
} SSD1306_charge_bump_setting_command_t;





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
    COM_PIN_CONFIGURATION_MASK                =   0b00010010,         /*!<  COM pin configuration mask                                                */
    COM_PIN_CONFIGURATION_SEQUENCTIAL_COM_PIN =   0b00000010,         /*!<  COM pin configuration: Sequential mode                          ( RESET ) */
    COM_PIN_CONFIGURATION_ALTERNATIVE_COM_PIN =   0b00010010          /*!<  COM pin configuration: Alternative mode                                   */
} SSD1306_com_pin_configuration_t;


/* COM LEFT/RIGHT RE-MAP
*/
typedef enum
{
    COM_LEFT_RIGHT_REMAP_MASK               =   0b00100010,           /*!<  COM left/right re-map mask                                                */
    COM_LEFT_RIGHT_REMAP_DISABLED           =   0b00000010,           /*!<  COM left/right re-map: Disabled                                 ( RESET ) */
    COM_LEFT_RIGHT_REMAP_ENABLED            =   0b00100010            /*!<  COM left/right re-map: Enabled                                            */
} SSD1306_com_left_right_re_map_t;



/**
  * @brief   SET DISPLAY CLOCK DIVIDE RATIO/OSCILLATOR FREQUENCY
  */
/* DISPLAY CLOCK DIVIDE RATIO <3:0>
 *  Set the divide ratio to generate DCLK (Display Clock) from CLK. The divide ratio is from 1 to 16,
 *  with reset value = 1. Please refer to section 8.3 for the details relationship of DCLK and CLK.
*/
typedef enum
{
    DISPLAY_CLOCK_DIVIDE_RATIO_MASK         =   0b00001111            /*!<  Display Clock Divide Ratio mask                                           */
} SSD1306_display_clock_divide_ratio_t;


/* OSCILLATOR FREQUENCY <7:4>
 *  Program the oscillator frequency Fosc that is the source of CLK if CLS pin is pulled high. The 4-bit
 * value results in 16 different frequency settings available as shown below. The default setting is 1000b.
*/
typedef enum
{
    OSCILLATOR_FREQUENCY_MASK               =   0b11110000            /*!<  Oscillator Frequency mask                                                 */
} SSD1306_oscillator_frequency_t;


/**
  * @brief   SET V_COMH DESELECT LEVEL
  */
typedef enum
{
    VCOMH_DESELECT_LEVEL_MASK               =   0b01110000,           /*!<  V_COMH deselect level mask                                                */
    VCOMH_DESELECT_LEVEL_0_65XVCC           =   0b00000000,           /*!<  V_COMH deselect level: ~0.65 x VCC                                        */
    VCOMH_DESELECT_LEVEL_0_77XVCC           =   0b00100000,           /*!<  V_COMH deselect level: ~0.77 x VCC                              ( RESET ) */
    VCOMH_DESELECT_LEVEL_0_83XVCC           =   0b00110000            /*!<  V_COMH deselect level: ~0.83 x VCC                                        */
} SSD1306_v_comh_deselect_level_t;



/**
  * @brief   CONTINUOS HORIZONTAL SCROLL SETUP
  */
/* RIGHT/LEFT HORIZONTAL SCROLL SETUP
*/
typedef enum
{
    HORIZONTAL_SCROLL_MASK                  =   0b00100111,           /*!<  Horizontal scroll mask                                                   */
    HORIZONTAL_SCROLL_RIGHT                 =   0b00100110,           /*!<  Horizontal scroll: right direction                                       */
    HORIZONTAL_SCROLL_LEFT                  =   0b00100111            /*!<  Horizontal scroll: left direction                                        */
} SSD1306_horizontal_scroll_t;


/* HORIZONTAL SCROLL SETUP: START PAGE ADDRESS
*/
typedef enum
{
    HORIZONTAL_SCROLL_START_PAGE_ADDR_MASK    =   0b00000111,         /*!<  Horizontal scroll start page address mask                                */
    HORIZONTAL_SCROLL_START_PAGE_ADDR_PAGE_0  =   0b00000000,         /*!<  Horizontal scroll start page address: Page 0                             */
    HORIZONTAL_SCROLL_START_PAGE_ADDR_PAGE_1  =   0b00000001,         /*!<  Horizontal scroll start page address: Page 1                             */
    HORIZONTAL_SCROLL_START_PAGE_ADDR_PAGE_2  =   0b00000010,         /*!<  Horizontal scroll start page address: Page 2                             */
    HORIZONTAL_SCROLL_START_PAGE_ADDR_PAGE_3  =   0b00000011,         /*!<  Horizontal scroll start page address: Page 3                             */
    HORIZONTAL_SCROLL_START_PAGE_ADDR_PAGE_4  =   0b00000100,         /*!<  Horizontal scroll start page address: Page 4                             */
    HORIZONTAL_SCROLL_START_PAGE_ADDR_PAGE_5  =   0b00000101,         /*!<  Horizontal scroll start page address: Page 5                             */
    HORIZONTAL_SCROLL_START_PAGE_ADDR_PAGE_6  =   0b00000110,         /*!<  Horizontal scroll start page address: Page 6                             */
    HORIZONTAL_SCROLL_START_PAGE_ADDR_PAGE_7  =   0b00000111          /*!<  Horizontal scroll start page address: Page 7                             */
} SSD1306_horizontal_scroll_start_page_address_t;


/* HORIZONTAL SCROLL SETUP: FRAME FREQUENCY
*/
typedef enum
{
    HORIZONTAL_SCROLL_FRAME_FREQUENCY_MASK        =   0b00000111,     /*!<  Horizontal scroll frame frequency mask                                   */
    HORIZONTAL_SCROLL_FRAME_FREQUENCY_FRAMES_5    =   0b00000000,     /*!<  Horizontal scroll frame frequency:   5 frames                            */
    HORIZONTAL_SCROLL_FRAME_FREQUENCY_FRAMES_64   =   0b00000001,     /*!<  Horizontal scroll frame frequency:  64 frames                            */
    HORIZONTAL_SCROLL_FRAME_FREQUENCY_FRAMES_128  =   0b00000010,     /*!<  Horizontal scroll frame frequency: 128 frames                            */
    HORIZONTAL_SCROLL_FRAME_FREQUENCY_FRAMES_256  =   0b00000011,     /*!<  Horizontal scroll frame frequency: 256 frames                            */
    HORIZONTAL_SCROLL_FRAME_FREQUENCY_FRAMES_3    =   0b00000100,     /*!<  Horizontal scroll frame frequency:   3 frames                            */
    HORIZONTAL_SCROLL_FRAME_FREQUENCY_FRAMES_4    =   0b00000101,     /*!<  Horizontal scroll frame frequency:   4 frames                            */
    HORIZONTAL_SCROLL_FRAME_FREQUENCY_FRAMES_25   =   0b00000110,     /*!<  Horizontal scroll frame frequency:  25 frames                            */
    HORIZONTAL_SCROLL_FRAME_FREQUENCY_FRAMES_2    =   0b00000111      /*!<  Horizontal scroll frame frequency:   2 frames                            */
} SSD1306_horizontal_scroll_frame_frequency_t;


/* HORIZONTAL SCROLL SETUP: END PAGE ADDRESS
*/
typedef enum
{
    HORIZONTAL_SCROLL_END_PAGE_ADDR_MASK    =   0b00000111,          /*!<  Horizontal scroll end page address mask                                  */
    HORIZONTAL_SCROLL_END_PAGE_ADDR_PAGE_0  =   0b00000000,          /*!<  Horizontal scroll end page address: Page 0                               */
    HORIZONTAL_SCROLL_END_PAGE_ADDR_PAGE_1  =   0b00000001,          /*!<  Horizontal scroll end page address: Page 1                               */
    HORIZONTAL_SCROLL_END_PAGE_ADDR_PAGE_2  =   0b00000010,          /*!<  Horizontal scroll end page address: Page 2                               */
    HORIZONTAL_SCROLL_END_PAGE_ADDR_PAGE_3  =   0b00000011,          /*!<  Horizontal scroll end page address: Page 3                               */
    HORIZONTAL_SCROLL_END_PAGE_ADDR_PAGE_4  =   0b00000100,          /*!<  Horizontal scroll end page address: Page 4                               */
    HORIZONTAL_SCROLL_END_PAGE_ADDR_PAGE_5  =   0b00000101,          /*!<  Horizontal scroll end page address: Page 5                               */
    HORIZONTAL_SCROLL_END_PAGE_ADDR_PAGE_6  =   0b00000110,          /*!<  Horizontal scroll end page address: Page 6                               */
    HORIZONTAL_SCROLL_END_PAGE_ADDR_PAGE_7  =   0b00000111           /*!<  Horizontal scroll end page address: Page 7                               */
} SSD1306_horizontal_scroll_end_page_address_t;


/**
  * @brief   CONTINUOUS VERTICAL AND HORIZONTAL SCROLL SETUP
  */
/* VERTICAL RIGHT/LEFT HORIZONTAL SCROLL SETUP
*/
typedef enum
{
    CONTINUOUS_VERTICAL_HORIZONTAL_SCROLL_MASK    =   0b00101011,     /*!<  Continuous vertical Horizontal scroll mask                               */
    CONTINUOUS_VERTICAL_HORIZONTAL_SCROLL_RIGHT   =   0b00101001,     /*!<  Continuous vertical Horizontal scroll: right direction                   */
    CONTINUOUS_VERTICAL_HORIZONTAL_SCROLL_LEFT    =   0b00101010      /*!<  Continuous vertical Horizontal scroll: left direction                    */
} SSD1306_continuous_vertical_right_left_horizontal_scroll_t;


/* VERTICAL SCROLLING OFFSET
*/
typedef enum
{
    VERTICAL_SCROLLING_OFFSET_MASK   =   0b11111111,                  /*!<  Vertical scrolling offset mask                                           */
    VERTICAL_SCROLLING_OFFSET_ROW_0  =   0b00000000,                  /*!<  Vertical scrolling offset:  0 row                                        */
    VERTICAL_SCROLLING_OFFSET_ROW_1  =   0b00000001,                  /*!<  Vertical scrolling offset:  1 row                                        */
    VERTICAL_SCROLLING_OFFSET_ROW_2  =   0b00000010,                  /*!<  Vertical scrolling offset:  2 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_3  =   0b00000011,                  /*!<  Vertical scrolling offset:  3 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_4  =   0b00000100,                  /*!<  Vertical scrolling offset:  4 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_5  =   0b00000101,                  /*!<  Vertical scrolling offset:  5 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_6  =   0b00000110,                  /*!<  Vertical scrolling offset:  6 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_7  =   0b00000111,                  /*!<  Vertical scrolling offset:  7 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_8  =   0b00001000,                  /*!<  Vertical scrolling offset:  8 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_9  =   0b00001001,                  /*!<  Vertical scrolling offset:  9 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_10 =   0b00001010,                  /*!<  Vertical scrolling offset: 10 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_11 =   0b00001011,                  /*!<  Vertical scrolling offset: 11 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_12 =   0b00001100,                  /*!<  Vertical scrolling offset: 12 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_13 =   0b00001101,                  /*!<  Vertical scrolling offset: 13 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_14 =   0b00001110,                  /*!<  Vertical scrolling offset: 14 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_15 =   0b00001111,                  /*!<  Vertical scrolling offset: 15 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_16 =   0b00010000,                  /*!<  Vertical scrolling offset: 16 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_17 =   0b00010001,                  /*!<  Vertical scrolling offset: 17 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_18 =   0b00010010,                  /*!<  Vertical scrolling offset: 18 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_19 =   0b00010011,                  /*!<  Vertical scrolling offset: 19 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_20 =   0b00010100,                  /*!<  Vertical scrolling offset: 20 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_21 =   0b00010101,                  /*!<  Vertical scrolling offset: 21 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_22 =   0b00010110,                  /*!<  Vertical scrolling offset: 22 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_23 =   0b00010111,                  /*!<  Vertical scrolling offset: 23 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_24 =   0b00011000,                  /*!<  Vertical scrolling offset: 24 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_25 =   0b00011001,                  /*!<  Vertical scrolling offset: 25 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_26 =   0b00011010,                  /*!<  Vertical scrolling offset: 26 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_27 =   0b00011011,                  /*!<  Vertical scrolling offset: 27 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_28 =   0b00011100,                  /*!<  Vertical scrolling offset: 28 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_29 =   0b00011101,                  /*!<  Vertical scrolling offset: 29 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_30 =   0b00011110,                  /*!<  Vertical scrolling offset: 30 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_31 =   0b00011111,                  /*!<  Vertical scrolling offset: 31 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_32 =   0b00100000,                  /*!<  Vertical scrolling offset: 32 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_33 =   0b00100001,                  /*!<  Vertical scrolling offset: 33 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_34 =   0b00100010,                  /*!<  Vertical scrolling offset: 34 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_35 =   0b00100011,                  /*!<  Vertical scrolling offset: 35 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_36 =   0b00100100,                  /*!<  Vertical scrolling offset: 36 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_37 =   0b00100101,                  /*!<  Vertical scrolling offset: 37 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_38 =   0b00100110,                  /*!<  Vertical scrolling offset: 38 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_39 =   0b00100111,                  /*!<  Vertical scrolling offset: 39 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_40 =   0b00101000,                  /*!<  Vertical scrolling offset: 40 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_41 =   0b00101001,                  /*!<  Vertical scrolling offset: 41 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_42 =   0b00101010,                  /*!<  Vertical scrolling offset: 42 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_43 =   0b00101011,                  /*!<  Vertical scrolling offset: 43 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_44 =   0b00101100,                  /*!<  Vertical scrolling offset: 44 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_45 =   0b00101101,                  /*!<  Vertical scrolling offset: 45 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_46 =   0b00101110,                  /*!<  Vertical scrolling offset: 46 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_47 =   0b00101111,                  /*!<  Vertical scrolling offset: 47 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_48 =   0b00110000,                  /*!<  Vertical scrolling offset: 48 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_49 =   0b00110001,                  /*!<  Vertical scrolling offset: 49 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_50 =   0b00110010,                  /*!<  Vertical scrolling offset: 50 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_51 =   0b00110011,                  /*!<  Vertical scrolling offset: 51 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_52 =   0b00110100,                  /*!<  Vertical scrolling offset: 52 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_53 =   0b00110101,                  /*!<  Vertical scrolling offset: 53 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_54 =   0b00110110,                  /*!<  Vertical scrolling offset: 54 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_55 =   0b00110111,                  /*!<  Vertical scrolling offset: 55 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_56 =   0b00111000,                  /*!<  Vertical scrolling offset: 56 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_57 =   0b00111001,                  /*!<  Vertical scrolling offset: 57 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_58 =   0b00111010,                  /*!<  Vertical scrolling offset: 58 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_59 =   0b00111011,                  /*!<  Vertical scrolling offset: 59 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_60 =   0b00111100,                  /*!<  Vertical scrolling offset: 60 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_61 =   0b00111101,                  /*!<  Vertical scrolling offset: 61 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_62 =   0b00111110,                  /*!<  Vertical scrolling offset: 62 rows                                       */
    VERTICAL_SCROLLING_OFFSET_ROW_63 =   0b00111111                   /*!<  Vertical scrolling offset: 63 rows                                       */
} SSD1306_vertical_scrolling_offset_t;


/**
  * @brief   SET MEMORY ADDRESSING MODE
  */
/* ADDRESSING MODE
*/
typedef enum
{
    ADDRESSING_MODE_MASK        =   0b11111111,                       /*!<  Addressing mode mask                                                     */
    ADDRESSING_MODE_HORIZONTAL  =   0b11111100,                       /*!<  Horizontal addressing mode                                               */
    ADDRESSING_MODE_VERTICAL    =   0b11111101,                       /*!<  Vertical addressing mode                                                 */
    ADDRESSING_MODE_PAGE        =   0b11111110                        /*!<  Page addressing mode                                           ( RESET ) */
} SSD1306_addressing_mode_t;


/**
  * @brief   SET PAGE START ADDRESS FOR PAGE ADDRESSING MODE
  */
typedef enum
{
    PAGE_START_ADDRESS_MASK     =   0b10110111,                       /*!<  Page starts address mode mask                                            */
    PAGE_START_ADDRESS_PAGE_0   =   0b10110000,                       /*!<  Page start address: PAGE0                                                */
    PAGE_START_ADDRESS_PAGE_1   =   0b10110001,                       /*!<  Page start address: PAGE1                                                */
    PAGE_START_ADDRESS_PAGE_2   =   0b10110010,                       /*!<  Page start address: PAGE2                                                */
    PAGE_START_ADDRESS_PAGE_3   =   0b10110011,                       /*!<  Page start address: PAGE3                                                */
    PAGE_START_ADDRESS_PAGE_4   =   0b10110100,                       /*!<  Page start address: PAGE4                                                */
    PAGE_START_ADDRESS_PAGE_5   =   0b10110101,                       /*!<  Page start address: PAGE5                                                */
    PAGE_START_ADDRESS_PAGE_6   =   0b10110110,                       /*!<  Page start address: PAGE6                                                */
    PAGE_START_ADDRESS_PAGE_7   =   0b10110111,                       /*!<  Page start address: PAGE7                                                */
} SSD1306_page_start_address_mode_t;


/**
  * @brief   CHARGE PUMP SETTING
  */
/* CHARGE PUMP
*/
typedef enum
{
    CHARGE_PUMP_MASK                                  =   0b11010100, /*!<  Charge pump mask                                                         */
    CHARGE_PUMP_DISABLE_CHARGE_PUMP                   =   0b00010000, /*!<  Disable charge pump                                            ( RESET ) */
    CHARGE_PUMP_ENABLE_CHARGE_PUMP_DURING_DISPLAY_ON  =   0b00010100  /*!<  Enable charge pump during display on                                     */
} SSD1306_charge_pump_t;






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
SSD1306_status_t  SSD1306_Init                                            ( I2C_parameters_t myI2Cparameters                                                                                                                                                                                                                                                                                                                                                        );

/** It sets the constrast value to select 1 out of 256 contrast steps.
  */
SSD1306_status_t  SSD1306_SetContrastControl                              ( I2C_parameters_t myI2Cparameters, SSD1306_vector_data_t myContrastStep                                                                                                                                                                                                                                                                                                                  );

/** It sets if the display's output follows RAM content or ignores it.
  */
SSD1306_status_t  SSD1306_SetEntireDisplay                                ( I2C_parameters_t myI2Cparameters, SSD1306_entire_display_on_t myEntireDisplayOn                                                                                                                                                                                                                                                                                                         );

/** It sets normal/inverse display.
  */
SSD1306_status_t  SSD1306_SetNormalInverseDisplay                         ( I2C_parameters_t myI2Cparameters, SSD1306_set_normal_inverse_display_t myNormalInverseDisplay                                                                                                                                                                                                                                                                                           );

/** It sets display ON/OFF.
  */
SSD1306_status_t  SSD1306_SetDisplay                                      ( I2C_parameters_t myI2Cparameters, SSD1306_set_display_t myDisplayMode                                                                                                                                                                                                                                                                                                                   );

/** This command switches the default 63 multiplex mode to any multiplex ratio, ranging from 16 to 63. The output pads COM0-COM63 will be switched to the corresponding COM signal.
  */
SSD1306_status_t  SSD1306_SetMultiplexRatio                               ( I2C_parameters_t myI2Cparameters, SSD1306_set_multiplex_ratio_t myMultiplexRatio                                                                                                                                                                                                                                                                                                        );

/** Set vertical shift by COM from 0-63.
  */
SSD1306_status_t  SSD1306_SetDisplayOffset                                ( I2C_parameters_t myI2Cparameters, uint8_t myDisplayOffset                                                                                                                                                                                                                                                                                                                               );

/** Set display RAM display start line register from 0-63.
  */
SSD1306_status_t  SSD1306_SetDisplayStartLine                             ( I2C_parameters_t myI2Cparameters, uint8_t myDisplayStartLine                                                                                                                                                                                                                                                                                                                            );

/** Set Segment Re-map.
  */
SSD1306_status_t  SSD1306_SetSegmentReMap                                 ( I2C_parameters_t myI2Cparameters, SSD1306_set_segment_re_map_t mySegmentReMap                                                                                                                                                                                                                                                                                                           );

/** Set COM Output Scan Direction.
  */
SSD1306_status_t  SSD1306_SetCOM_OutputScanDirection                      ( I2C_parameters_t myI2Cparameters, SSD1306_set_com_output_scan_direction_t myScanDirection                                                                                                                                                                                                                                                                                               );

/** Set COM Pins Hardware Configuration.
  */
SSD1306_status_t  SSD1306_SetCOM_PinsHardwareConfiguration                ( I2C_parameters_t myI2Cparameters, SSD1306_com_pin_configuration_t myCOM_PinConfiguration, SSD1306_com_left_right_re_map_t myCOM_LeftRightEnable                                                                                                                                                                                                                                         );

/** Set Display Clock Divide Ratio/Oscillator Frequency.
  */
SSD1306_status_t  SSD1306_SetDisplayClockDivideRatio_OscFreq              ( I2C_parameters_t myI2Cparameters, uint8_t myOscillatorFrequency, uint8_t myDisplayClockDivideRatio                                                                                                                                                                                                                                                                                      );

/** Set Pre-charge Period.
  */
SSD1306_status_t  SSD1306_SePreChargePeriod                               ( I2C_parameters_t myI2Cparameters, uint8_t myPreChargePeriodPhase1, uint8_t myPreChargePeriodPhase2                                                                                                                                                                                                                                                                                      );

/** It adjusts the VCOMH regulator output.
  */
SSD1306_status_t  SSD1306_SeVCOMH_DeselectLevel                           ( I2C_parameters_t myI2Cparameters, SSD1306_v_comh_deselect_level_t myVCOMH_DeselctLevel                                                                                                                                                                                                                                                                                                  );

/** No Operation Command.
  */
SSD1306_status_t  SSD1306_NopCommand                                      ( I2C_parameters_t myI2Cparameters                                                                                                                                                                                                                                                                                                                                                        );

/** Horizontal scroll setup.
  */
SSD1306_status_t  SSD1306_SetHorizontalScrollSetup                        ( I2C_parameters_t myI2Cparameters, SSD1306_horizontal_scroll_t myRightLeftHorizontalScroll, SSD1306_horizontal_scroll_start_page_address_t myStartPageAddr, SSD1306_horizontal_scroll_frame_frequency_t myFrames, SSD1306_horizontal_scroll_end_page_address_t myEndPageAddr                                                                                                             );

/** Continuous Vertical and Horizontal Scroll Setup.
  */
SSD1306_status_t  SSD1306_SetContinuousHorizontalVerticalScrollSetup      ( I2C_parameters_t myI2Cparameters, SSD1306_continuous_vertical_right_left_horizontal_scroll_t myContinuousVerticalHorizontalScrollSetup, SSD1306_horizontal_scroll_start_page_address_t myStartPageAddr, SSD1306_horizontal_scroll_frame_frequency_t myFrames, SSD1306_horizontal_scroll_end_page_address_t myEndPageAddr, SSD1306_vertical_scrolling_offset_t myVerticalScrollingOffset );

/** Deactivate Scroll.
  */
SSD1306_status_t  SSD1306_DeactivateScroll                                ( I2C_parameters_t myI2Cparameters                                                                                                                                                                                                                                                                                                                                                        );

/** Activate Scroll.
  */
SSD1306_status_t  SSD1306_ActivateScroll                                  ( I2C_parameters_t myI2Cparameters                                                                                                                                                                                                                                                                                                                                                        );

/** Set Vertical Scroll Area.
  */
SSD1306_status_t  SSD1306_SetVerticalScrollArea                           ( I2C_parameters_t myI2Cparameters, uint8_t myNoRowsTopFixArea, uint8_t NoRowsScrollArea                                                                                                                                                                                                                                                                                                  );

/** Set Memory Addressing Mode.
  */
SSD1306_status_t  SSD1306_SetMemoryAddressingMode                         ( I2C_parameters_t myI2Cparameters, SSD1306_addressing_mode_t myMemoryAddressingMode                                                                                                                                                                                                                                                                                                      );

/** Set Column Address.
  */
SSD1306_status_t  SSD1306_SetColumnAddress                                ( I2C_parameters_t myI2Cparameters, uint8_t myColumnStartAddress, uint8_t myColumnEndAddress                                                                                                                                                                                                                                                                                              );

/** Set Page Address.
  */
SSD1306_status_t  SSD1306_SetPageAddress                                  ( I2C_parameters_t myI2Cparameters, uint8_t myPageStartAddress, uint8_t myPageEndAddress                                                                                                                                                                                                                                                                                                  );

/** Set Lower Column Start Address for Page Addressing Mode.
  */
SSD1306_status_t  SSD1306_SetLowerColumnStartAddressForPageAddressingMode ( I2C_parameters_t myI2Cparameters, uint8_t myLowerColumnStartAddress                                                                                                                                                                                                                                                                                                                     );

/** Set Higher Column Start Address for Page Addressing Mode.
  */
SSD1306_status_t  SSD1306_SetHigherColumnStartAddressForPageAddressingMode( I2C_parameters_t myI2Cparameters, uint8_t myHigherColumnStartAddress                                                                                                                                                                                                                                                                                                                    );

/** Set Page Start Address for Page Addressing Mode.
  */
SSD1306_status_t  SSD1306_SetPageAddressForPageAddressingMode             ( I2C_parameters_t myI2Cparameters, SSD1306_page_start_address_mode_t myPageAddress                                                                                                                                                                                                                                                                                                       );

/** Set Charge Pump Setting.
  */
SSD1306_status_t  SSD1306_SetChargePumpSetting                            ( I2C_parameters_t myI2Cparameters, SSD1306_charge_pump_t myChargePump                                                                                                                                                                                                                                                                                                                    );




#ifdef __cplusplus
}
#endif

#endif /* SSD1306_H */
