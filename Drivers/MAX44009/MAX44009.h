/**
 * @brief       MAX44009.h
 * @details     Industry’s Lowest-Power Ambient Light Sensor with ADC.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        13/September/2018
 * @version     13/September/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


#ifndef MAX44009_H_
#define MAX44009_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
  * @brief   DEFAULT ADDRESS
  */
typedef enum
{
    MAX44009_ADDRESS_A0_GND     =   0b1001010,              /*!<   MAX44009 I2C Address: A0 connected to GND                */
    MAX44009_ADDRESS_A0_VCC     =   0b1001011               /*!<   MAX44009 I2C Address: A0 connected to VCC                */
} MAX44009_address_t;


/* REGISTER MAP     */
/**
  * @brief   REGISTER MAP
  */
typedef enum
{
    MAX44009_INTERRUPT_STATUS           =   0x00,           /*!<  Interrupt Status          ( Read Only  ) ( Default 0x00 ) */
    MAX44009_INTERRUPT_ENABLE           =   0x01,           /*!<  Interrupt Enable          ( Read/Write ) ( Default 0x00 ) */
    MAX44009_CONFIGURATION              =   0x02,           /*!<  Configuration             ( Read/Write ) ( Default 0x03 ) */
    MAX44009_LUX_HIGH_BYTE              =   0x03,           /*!<  Lux High Byte             ( Read Only  ) ( Default 0x00 ) */
    MAX44009_LUX_LOW_BYTE               =   0x04,           /*!<  Lux Low Byte              ( Read Only  ) ( Default 0x00 ) */
    MAX44009_UPPER_THRESHOLD_HIGH_BYTE  =   0x05,           /*!<  Upper Threshold High Byte ( Read/Write ) ( Default 0xFF ) */
    MAX44009_LOWER_THRESHOLD_HIGH_BYTE  =   0x06,           /*!<  Lower Threshold High Byte ( Read/Write ) ( Default 0x00 ) */
    MAX44009_THRESHOLD_TIMER            =   0x07            /*!<  Threshold Timer           ( Read/Write ) ( Default 0xFF ) */
} MAX44009_register_maps_t;



/* INTERRUPT STATUS  */
/**
  * @brief   INTS. If the INTE bit is set to 1, then the INTS status bit is asserted if the light intensity exceeds either upper or lower threshold
  *                limits (as specified by registers 0x05 and 0x06, respectively) for a period longer than that defined by the Threshold
  *                Timer register. This bit resets to 0 after the host reads this register.
  */
typedef enum
{
    INTERRUPT_STATUS_INTS_MASK                                      =   ( 1 << 0 ),     /*!<  INTS mask                                                             */
    INTERRUPT_STATUS_INTS_LIGHT_INTENSITY_OUTSIDE_THRESHOLD_WINDOW  =   ( 1 << 0 ),     /*!<  The light intensity exceeds either upper or lower threshold limits    */
    INTERRUPT_STATUS_INTS_LIGHT_INTENSITY_INSIDE_THRESHOLD_WINDOW   =   ( 1 << 0 )      /*!<  The light intensity is inside threshold window                        */
} MAX44009_interrupt_status_ints_t;



/* INTERRUPT ENABLE. NOTE: Interrupt events set the INTS bit (register 0x00, bit 0) and the INT pin only if the INTE bit is set to 1. If the INTE bit is set
                           ( interrupt is enabled ) and the interrupt condition is triggered, then the INT pin is pulled low ( asserted ) and the INTS bit
                           in the Interrupt Status register is set to 1.
*/
/**
  * @brief   INTS.
  */
typedef enum
{
    INTERRUPT_ENABLE_INTS_MASK        =   ( 1 << 0 ),       /*!<  INTS mask                                     */
    INTERRUPT_ENABLE_INTS_ENABLE      =   ( 1 << 0 ),       /*!<  INTS enables                                  */
    INTERRUPT_ENABLE_INTS_DISABLE     =   ( 0 << 0 )        /*!<  INTS disables                                 */
} MAX44009_interrupt_enable_ints_t;



/* CONFIGURATION  */
/**
  * @brief   CONT ( CONTINUOUS MODE REGISTER ).
  */
typedef enum
{
    CONFIGURATION_CONT_MASK             =   ( 1 << 7 ),     /*!<  CONT mask                                                                                                                     */
    CONFIGURATION_CONT_DEFAULT_MODE     =   ( 0 << 7 ),     /*!<  Default mode. The IC measures lux intensity only once every 800ms regardless of integration time                              */
    CONFIGURATION_CONT_CONTINUOUS_MODE  =   ( 1 << 7 )      /*!<  Continuous mode. The IC continuously measures lux intensity. That is, as soon as one reading is finished, a new one begins    */
} MAX44009_configuration_cont_t;


/**
  * @brief   MANUAL ( MANUAL MODE REGISTER ).
  */
typedef enum
{
    CONFIGURATION_MANUAL_MASK           =   ( 1 << 6 ),     /*!<  MANUAL mask                                                                                                                   */
    CONFIGURATION_MANUAL_DEFAULT_MODE   =   ( 0 << 6 ),     /*!<  Default mode. CDR, TIM[2:0] bits are automatically determined by the internal auto-ranging circuitry of the IC                */
    CONFIGURATION_MANUAL_MANUAL_MODE    =   ( 1 << 6 )      /*!<  Manual mode. CDR, and TIM[2:0] bits can be programmed by the user                                                             */
} MAX44009_configuration_manual_t;


/**
  * @brief   CDR ( CURRENT DIVISION RATIO ).
  */
typedef enum
{
    CONFIGURATION_CDR_MASK                  =   ( 0 << 3 ), /*!<  CDR mask                                                                                                                      */
    CONFIGURATION_CDR_CURRENT_NOT_DIVIDED   =   ( 0 << 3 ), /*!<  Current not divided. All of the photo-diode current goes to the ADC                                                           */
    CONFIGURATION_CDR_CURRENT_DIVIDED_1_8   =   ( 1 << 3 )  /*!<  Only 1/8 of the photo-diode current goes to the ADC. This mode is used in high-brightness situations                          */
} MAX44009_configuration_cdr_t;


/**
  * @brief   TIM ( INTEGRATION TIMER BITS ).
  */
typedef enum
{
    CONFIGURATION_TIM_MASK          =   ( 0b111 << 0 ),     /*!<  TIM mask                                                                                                              */
    CONFIGURATION_TIM_800_MS        =   ( 0b000 << 0 ),     /*!<  Integration timer 800ms   ( This is a preferred mode for boosting low-light sensitivity )                             */
    CONFIGURATION_TIM_400_MS        =   ( 0b001 << 0 ),     /*!<  Integration timer 400ms                                                                                               */
    CONFIGURATION_TIM_200_MS        =   ( 0b010 << 0 ),     /*!<  Integration timer 200ms                                                                                               */
    CONFIGURATION_TIM_100_MS        =   ( 0b011 << 0 ),     /*!<  Integration timer 100ms   ( This is a preferred mode for high-brightness applications )                               */
    CONFIGURATION_TIM_50_MS         =   ( 0b100 << 0 ),     /*!<  Integration timer 50ms    ( Manual mode only )                                                                        */                                                                                            */
    CONFIGURATION_TIM_25_MS         =   ( 0b101 << 0 ),     /*!<  Integration timer 25ms    ( Manual mode only )                                                                        */
    CONFIGURATION_TIM_12_5_MS       =   ( 0b110 << 0 ),     /*!<  Integration timer 12.5ms  ( Manual mode only )                                                                        */
    CONFIGURATION_TIM_6_25_MS       =   ( 0b111 << 0 )      /*!<  Integration timer 6.25ms  ( Manual mode only )                                                                        */
} MAX44009_configuration_tim_t;



/* LUX HIGH-BYTE REGISTER  */
/**
  * @brief   EXPONENT AND MANTISSA.
  */
typedef enum
{
    LUX_HIGH_BYTE_EXPONENT_MASK     =   ( 0b1111 << 4 ),    /*!<  Exponent mask                                                     */
    LUX_HIGH_BYTE_MANTISSA_MASK     =   ( 0b1111 << 0 )     /*!<  Mantissa mask                                                     */
} MAX44009_lux_high_byte_register_t;


/* LUX LOW-BYTE REGISTER  */
/**
  * @brief   MANTISSA.
  */
typedef enum
{
    LUX_LOW_BYTE_MANTISSA_MASK      =   ( 0b1111 << 0 )     /*!<  Mantissa mask                                                     */
} MAX44009_lux_low_byte_register_t;


/* UPPER THRESHOLD HIGH-BYTE REGISTER  */
/**
  * @brief   EXPONENT AND MANTISSA.
  */
typedef enum
{
    UPPER_THRESHOLD_HIGH_BYTE_EXPONENT_MASK =   ( 0b1111 << 4 ),    /*!<  Exponent mask                                                     */
    UPPER_THRESHOLD_HIGH_BYTE_MANTISSA_MASK =   ( 0b1111 << 0 )     /*!<  Mantissa mask                                                     */
} MAX44009_upper_threshold_high_byte_register_t;


/* LOWER THRESHOLD HIGH-BYTE REGISTER  */
/**
  * @brief   EXPONENT AND MANTISSA.
  */
typedef enum
{
    LOWER_THRESHOLD_HIGH_BYTE_EXPONENT_MASK =   ( 0b1111 << 4 ),    /*!<  Exponent mask                                                     */
    LOWER_THRESHOLD_HIGH_BYTE_MANTISSA_MASK =   ( 0b1111 << 0 )     /*!<  Mantissa mask                                                     */
} MAX44009_Lower_threshold_high_byte_register_t;





#ifndef MAX44009_VECTOR_STRUCT_H
#define MAX44009_VECTOR_STRUCT_H
typedef struct
{
    float       lux;                    /*!<  Lux                   */

    uint8_t     lux_lower_threshold;    /*!<  LUX lower threshold   */
    uint8_t     lux_upper_threshold;    /*!<  LUX upper threshold   */

    uint16_t    threshold_timer;        /*!<  Timer threshold       */
} MAX44009_vector_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    MAX44009_SUCCESS     =       0,
    MAX44009_FAILURE     =       1
} MAX44009_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
MAX44009_status_t  MAX44009_Init                            ( I2C_parameters_t myI2Cparameters                                                              );

/** It gets the interrupt status value.
  */
MAX44009_status_t  MAX44009_ReadInterruptStatus             ( I2C_parameters_t myI2Cparameters, MAX44009_vector_data_t* myInterruptStatus                   );

/** It sets which interrupt is enabled/disabled.
  */
MAX44009_status_t  MAX44009_InterrupEnable                  ( I2C_parameters_t myI2Cparameters, uint8_t myInterruptEnable                                   );

/** It sets the power mode.
  */
MAX44009_status_t  MAX44009_ShutdownControl                 ( I2C_parameters_t myI2Cparameters, MAX44009_mode_configuration_shdn_t myPowerMode              );

/** It performs a software reset.
  */
MAX44009_status_t  MAX44009_SoftwareReset                   ( I2C_parameters_t myI2Cparameters                                                              );

/** It checks if the software reset was completed by polling mode.
  */
MAX44009_status_t  MAX44009_PollingSoftwareReset            ( I2C_parameters_t myI2Cparameters, MAX44009_vector_data_t* myResetFlag                         );

/** It initiates a single temperature reading from the temperature sensor.
  */
MAX44009_status_t  MAX44009_TriggerTemperature              ( I2C_parameters_t myI2Cparameters                                                              );

/** It checks if the temperature conversion was completed by polling mode.
  */
MAX44009_status_t  MAX44009_PollingTemperatureConversion    ( I2C_parameters_t myI2Cparameters, MAX44009_vector_data_t* myTempFlag                          );

/** It sets the operating state of the MAX44009.
  */
MAX44009_status_t  MAX44009_ModeControl                     ( I2C_parameters_t myI2Cparameters, MAX44009_mode_configuration_mode_t myModeControl            );

/** It sets the SpO2 ADC resolution is 16-bit with 1.6ms LED pulse width.
  */
MAX44009_status_t  MAX44009_SpO2_HighResolution             ( I2C_parameters_t myI2Cparameters, MAX44009_spo2_configuration_spo2_hi_res_en_t myRes          );

/** It defines the effective sampling rate.
  */
MAX44009_status_t  MAX44009_SpO2_SampleRateControl          ( I2C_parameters_t myI2Cparameters, MAX44009_spo2_configuration_spo2_sr_t mySampleRate          );

/** It sets the LED pulse width.
  */
MAX44009_status_t  MAX44009_LED_PulseWidthControl           ( I2C_parameters_t myI2Cparameters, MAX44009_vector_data_t myLEDWidth                           );

/** It gets the LED pulse width.
  */
MAX44009_status_t  MAX44009_Get_LED_PulseWidthControl       ( I2C_parameters_t myI2Cparameters, MAX44009_vector_data_t* myLEDWidth                          );

/** It sets the current level of the Red LED.
  */
MAX44009_status_t  MAX44009_SetRed_LED_CurrentControl       ( I2C_parameters_t myI2Cparameters, MAX44009_led_configuration_red_pa_t myRedLED                );

/** It sets the current level of the IR LED.
  */
MAX44009_status_t  MAX44009_SetIR_LED_CurrentControl        ( I2C_parameters_t myI2Cparameters, MAX44009_led_configuration_ir_pa_t myIRLED                  );

/** It gets the raw temperature data ( temperature integer and temperature fraction ).
  */
MAX44009_status_t  MAX44009_GetRawTemperature               ( I2C_parameters_t myI2Cparameters, MAX44009_vector_data_t* myRawTemperature                    );

/** It gets the temperature value.
  */
MAX44009_status_t  MAX44009_GetTemperature                  ( I2C_parameters_t myI2Cparameters, MAX44009_vector_data_t* myTemperature                       );

/** It gets the revision ID.
  */
MAX44009_status_t  MAX44009_GetRevisionID                   ( I2C_parameters_t myI2Cparameters, MAX44009_vector_data_t* myRevisionID                        );

/** It gets the part ID.
  */
MAX44009_status_t  MAX44009_GetPartID                       ( I2C_parameters_t myI2Cparameters, MAX44009_vector_data_t* myPartID                            );

/** It gets data from the FIFO.
  */
MAX44009_status_t  MAX44009_ReadFIFO                        ( I2C_parameters_t myI2Cparameters, MAX44009_vector_data_t* myDATA, uint32_t myNumSamplesToRead );

/** It clears the FIFO registers.
  */
MAX44009_status_t  MAX44009_ClearFIFO                       ( I2C_parameters_t myI2Cparameters, MAX44009_vector_data_t* myDATA                              );


#ifdef __cplusplus
}
#endif

#endif /* MAX44009_H */
