/**
 * @brief       MCP4725.h
 * @details     12-Bit Digital-to-Analog Converter with EEPROM Memory.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        7/September/2017
 * @version     7/September/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESSES ( NOTE1: The A2 and A1 are programmed to '00' (default), if not requested by customer.
  *                              NOTE2: On my board, the A2 and A1 are programmed to '01'. )
  */
typedef enum{
    MCP4725_ADDRESS_LOW     =   0x62,                   /*!<   A0 pin ties to GND                                            */
    MCP4725_ADDRESS_HIGH    =   0x63                    /*!<   A0 pin ties to VDD                                            */
} MCP4725_address_t;


/**
  * @brief   COMMANDS
  */
#define MCP4725_GENERAL_CALL             0x00              /*!<   The MCP4725 device acknowledges the general call address                             */

/* General Call Commands */
/**
  * @brief   GENERAL CALL COMMANDS
  */
#define MCP4725_GENERAL_CALL_RESET       0x06              /*!<  Perform an internal reset similar to a power-on-reset (POR).                          */
#define MCP4725_GENERAL_CALL_WAKE_UP     0x09              /*!<  The power-down bits of the DAC register are set to a normal operation.                */





/* Commands Registers */
/**
  * @brief   WRITE COMMAND TYPE
  */
typedef enum{
    FAST_MODE                              =   0,           /*!<  This command is used to change the DAC register. EEPROM is not affected.              */
    WRITE_DAC_REGISTER_MODE                =   1,           /*!<  Load configuration bits and data code to the DAC Register.                            */
    WRITE_DAC_AND_EEPROM_REGISTER_MODE     =   2            /*!<  Load configuration bits and data code to the DAC Register and also write the EEPROM.  */
} MCP4725_write_command_type_t;



/**
  * @brief   POWER-DOWN MODE
  */
typedef enum{
    NORMAL_MODE                                 =   0,      /*!<  Normal Mode.                                                                          */
    POWER_DOWN_1KOHM_RESISTIVE_LOAD_MODE        =   1,      /*!<  Power-Down Mode. 1 k‎Ω resistor to ground.                                             */
    POWER_DOWN_100KOHM_RESISTIVE_LOAD_MODE      =   2,      /*!<  Power-Down Mode. 100 k‎Ω resistor to ground.                                           */
    POWER_DOWN_500KOHM_RESISTIVE_LOAD_MODE      =   3       /*!<  Power-Down Mode. 500 k‎Ω resistor to ground.                                           */
} MCP4725_operation_mode_t;



/**
  * @brief   READY/#BUSY BIT
  */
typedef enum{
    EEPROM_BUSY                                 =   0,      /*!<  EEPROM write is not completed.                                                        */
    EEPROM_READY                                =   1       /*!<  EEPROM write is complete.                                                             */
} MCP4725_eeprom_status_t;







/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum{
    MCP4725_SUCCESS     =       0,
    MCP4725_FAILURE     =       1
} MCP4725_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
MCP4725_status_t  MCP4725_Reset                 ( NRF_TWI_Type* myinstance );
MCP4725_status_t  MCP4725_WakeUp                ( NRF_TWI_Type* myinstance );
MCP4725_status_t  MCP4725_PowerMode             ( NRF_TWI_Type* myinstance, MCP4725_address_t ADDR, MCP4725_write_command_type_t myWriteCMD, MCP4725_operation_mode_t myPowerMode );
MCP4725_status_t  MCP4725_SetNewValue           ( NRF_TWI_Type* myinstance, MCP4725_address_t ADDR, MCP4725_write_command_type_t myWriteCMD, uint32_t myDACNewValue );
MCP4725_status_t  MCP4725_EEPROM_Status         ( NRF_TWI_Type* myinstance, MCP4725_address_t ADDR, MCP4725_eeprom_status_t* myEEPROM_Status );
