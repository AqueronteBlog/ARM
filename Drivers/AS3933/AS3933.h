/**
 * @brief       AS3933.h
 * @details     3D Low Frequency Wakeup Receiver.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/February/2018
 * @version     22/February/2018    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "spi.h"


/* SPI COMMAND STRUCTURE */
/**
  * @brief   MODE. ( B15:B14 )
  */
typedef enum
{
    AS3933_WRITE            =   0x00,           /*!<  WRITE                 */
    AS3933_READ             =   0x01,           /*!<  READ                  */
    AS3933_DIRECT_COMMAND   =   0x03            /*!<  DIRECT COMMAND        */
} AS3933_spi_command_structure_mode_t;


/**
  * @brief   READ/WRITE REGISTER ( B13:B8 )
  */
typedef enum
{
    AS3933_R0               =   0x00,           /*!<  R0  register          */
    AS3933_R1               =   0x01,           /*!<  R1  register          */
    AS3933_R2               =   0x02,           /*!<  R3  register          */
    AS3933_R3               =   0x03,           /*!<  R4  register          */
    AS3933_R4               =   0x04,           /*!<  R5  register          */
    AS3933_R5               =   0x05,           /*!<  R6  register          */
    AS3933_R6               =   0x06,           /*!<  R7  register          */
    AS3933_R7               =   0x07,           /*!<  R8  register          */
    AS3933_R8               =   0x08,           /*!<  R9  register          */
    AS3933_R9               =   0x09,           /*!<  R10 register          */
    AS3933_R10              =   0x0A,           /*!<  R11 register          */
    AS3933_R11              =   0x0B,           /*!<  R11 register          */
    AS3933_R12              =   0x0C,           /*!<  R12 register          */
    AS3933_R13              =   0x0D,           /*!<  R13 register          */
    AS3933_R14              =   0x0E,           /*!<  R14 register          */
    AS3933_R15              =   0x0F,           /*!<  R15 register          */
    AS3933_R16              =   0x10,           /*!<  R16 register          */
    AS3933_R17              =   0x11,           /*!<  R17 register          */
    AS3933_R18              =   0x12,           /*!<  R18 register          */
    AS3933_R19              =   0x13            /*!<  R19 register          */
} AS3933_spi_command_structure_registers_t;


/* SPI DIRECT COMMANDS */
/**
  * @brief   DIRECT COMMANDS. ( B13:B8 )
  */
typedef enum
{
    CLEAR_WAKE              =   0x00,           /*!<  Clears the wake state of the chip. In case the chip has woken up (WAKE pin is high) the chip is set back to listening mode    */
    RESET_RSSI              =   0x01,           /*!<  Resets the RSSI measurement                                                                                                   */
    CALIB_RC_OSC            =   0x02,           /*!<  Starts the trimming procedure of the internal RC oscillator                                                                   */
    CLEAR_FALSE             =   0x03,           /*!<  Resets the false wakeup register ( R13 = 00 )                                                                                 */
    PRESET_DEFAULT          =   0x04,           /*!<  Sets all register in the default mode                                                                                         */
    CALIB_RCO_LC            =   0x05            /*!<  Calibration of the RC-oscillator with the external LC tank                                                                    */
} AS3933_spi_direct_commands_t;









#ifndef AS3933_VECTOR_STRUCT_H
#define AS3933_VECTOR_STRUCT_H
/* No-Decode Mode Data Bits */
typedef struct
{
    uint8_t mySEG;                  /*!<  D7: DP | D6: A | D5: B | D4: C | D3: D | D2: E | D1: F | D0: G   */
} AS3933_no_decode_b_t;
#endif



/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    AS3933_SUCCESS     =       0,
    AS3933_FAILURE     =       1
} AS3933_status_t;





/**
  * @brief   FUNCTION PROTOTYPES
  */
AS3933_status_t  AS3933_Init              ( SPI_parameters_t mySPI_parameters                                                         );
