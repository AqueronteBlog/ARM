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


/* REGISTER MAP     */
/**
  * @brief   REGISTER MAP
  */
typedef enum
{
    SSD1306_INTERRUPT_STATUS           =   0x00,           /*!<  Interrupt Status          ( Read Only  ) ( Default 0x00 ) */
    SSD1306_INTERRUPT_ENABLE           =   0x01,           /*!<  Interrupt Enable          ( Read/Write ) ( Default 0x00 ) */
    SSD1306_CONFIGURATION              =   0x02,           /*!<  Configuration             ( Read/Write ) ( Default 0x03 ) */
    SSD1306_LUX_HIGH_BYTE              =   0x03,           /*!<  Lux High Byte             ( Read Only  ) ( Default 0x00 ) */
    SSD1306_LUX_LOW_BYTE               =   0x04,           /*!<  Lux Low Byte              ( Read Only  ) ( Default 0x00 ) */
    SSD1306_UPPER_THRESHOLD_HIGH_BYTE  =   0x05,           /*!<  Upper Threshold High Byte ( Read/Write ) ( Default 0xFF ) */
    SSD1306_LOWER_THRESHOLD_HIGH_BYTE  =   0x06,           /*!<  Lower Threshold High Byte ( Read/Write ) ( Default 0x00 ) */
    SSD1306_THRESHOLD_TIMER            =   0x07            /*!<  Threshold Timer           ( Read/Write ) ( Default 0xFF ) */
} SSD1306_register_maps_t;



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
    INTERRUPT_STATUS_INTS_LIGHT_INTENSITY_INSIDE_THRESHOLD_WINDOW   =   ( 0 << 0 )      /*!<  The light intensity is inside threshold window                        */
} SSD1306_interrupt_status_ints_t;



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
} SSD1306_interrupt_enable_ints_t;



/* CONFIGURATION  */
/**
  * @brief   CONT ( CONTINUOUS MODE REGISTER ).
  */
typedef enum
{
    CONFIGURATION_CONT_MASK             =   ( 1 << 7 ),     /*!<  CONT mask                                                                                                                     */
    CONFIGURATION_CONT_DEFAULT_MODE     =   ( 0 << 7 ),     /*!<  Default mode. The IC measures lux intensity only once every 800ms regardless of integration time                              */
    CONFIGURATION_CONT_CONTINUOUS_MODE  =   ( 1 << 7 )      /*!<  Continuous mode. The IC continuously measures lux intensity. That is, as soon as one reading is finished, a new one begins    */
} SSD1306_configuration_cont_t;


/**
  * @brief   MANUAL ( MANUAL MODE REGISTER ).
  */
typedef enum
{
    CONFIGURATION_MANUAL_MASK           =   ( 1 << 6 ),     /*!<  MANUAL mask                                                                                                                   */
    CONFIGURATION_MANUAL_DEFAULT_MODE   =   ( 0 << 6 ),     /*!<  Default mode. CDR, TIM[2:0] bits are automatically determined by the internal auto-ranging circuitry of the IC                */
    CONFIGURATION_MANUAL_MANUAL_MODE    =   ( 1 << 6 )      /*!<  Manual mode. CDR, and TIM[2:0] bits can be programmed by the user                                                             */
} SSD1306_configuration_manual_t;


/**
  * @brief   CDR ( CURRENT DIVISION RATIO ).
  */
typedef enum
{
    CONFIGURATION_CDR_MASK                  =   ( 0 << 3 ), /*!<  CDR mask                                                                                                                      */
    CONFIGURATION_CDR_CURRENT_NOT_DIVIDED   =   ( 0 << 3 ), /*!<  Current not divided. All of the photo-diode current goes to the ADC                                                           */
    CONFIGURATION_CDR_CURRENT_DIVIDED_1_8   =   ( 1 << 3 )  /*!<  Only 1/8 of the photo-diode current goes to the ADC. This mode is used in high-brightness situations                          */
} SSD1306_configuration_cdr_t;


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
    CONFIGURATION_TIM_50_MS         =   ( 0b100 << 0 ),     /*!<  Integration timer 50ms    ( Manual mode only )                                                                        */
    CONFIGURATION_TIM_25_MS         =   ( 0b101 << 0 ),     /*!<  Integration timer 25ms    ( Manual mode only )                                                                        */
    CONFIGURATION_TIM_12_5_MS       =   ( 0b110 << 0 ),     /*!<  Integration timer 12.5ms  ( Manual mode only )                                                                        */
    CONFIGURATION_TIM_6_25_MS       =   ( 0b111 << 0 )      /*!<  Integration timer 6.25ms  ( Manual mode only )                                                                        */
} SSD1306_configuration_tim_t;



/* LUX HIGH-BYTE REGISTER  */
/**
  * @brief   EXPONENT AND MANTISSA.
  */
typedef enum
{
    LUX_HIGH_BYTE_EXPONENT_MASK     =   ( 0b1111 << 4 ),    /*!<  Exponent mask                                                     */
    LUX_HIGH_BYTE_MANTISSA_MASK     =   ( 0b1111 << 0 )     /*!<  Mantissa mask                                                     */
} SSD1306_lux_high_byte_register_t;


/* LUX LOW-BYTE REGISTER  */
/**
  * @brief   MANTISSA.
  */
typedef enum
{
    LUX_LOW_BYTE_MANTISSA_MASK      =   ( 0b1111 << 0 )     /*!<  Mantissa mask                                                     */
} SSD1306_lux_low_byte_register_t;


/* UPPER THRESHOLD HIGH-BYTE REGISTER  */
/**
  * @brief   EXPONENT AND MANTISSA.
  */
typedef enum
{
    UPPER_THRESHOLD_HIGH_BYTE_EXPONENT_MASK =   ( 0b1111 << 4 ),    /*!<  Exponent mask                                                     */
    UPPER_THRESHOLD_HIGH_BYTE_MANTISSA_MASK =   ( 0b1111 << 0 )     /*!<  Mantissa mask                                                     */
} SSD1306_upper_threshold_high_byte_register_t;


/* LOWER THRESHOLD HIGH-BYTE REGISTER  */
/**
  * @brief   EXPONENT AND MANTISSA.
  */
typedef enum
{
    LOWER_THRESHOLD_HIGH_BYTE_EXPONENT_MASK =   ( 0b1111 << 4 ),    /*!<  Exponent mask                                                     */
    LOWER_THRESHOLD_HIGH_BYTE_MANTISSA_MASK =   ( 0b1111 << 0 )     /*!<  Mantissa mask                                                     */
} SSD1306_Lower_threshold_high_byte_register_t;



/*
    AUXILIAR REGISTERS

    NOTE: These definitions are for better understanding in order to use the driver
*/
/* DEVICE RESOLUTION  */
/**
  * @brief   DEVICE RESOLUTION.
  */
typedef enum
{
    RESOLUTION_NORMAL_RESOLUTION   =   0,       /*!<  Normal resolution   ( LUX = 2^( exponent ) x mantissa x 0.72  )      */
    RESOLUTION_EXTENDED_RESOLUTION =   1        /*!<  Extended resolution ( LUX = 2^( exponent ) x mantissa x 0.045 )      */
} SSD1306_device_resolution_t;







#ifndef SSD1306_VECTOR_STRUCT_H
#define SSD1306_VECTOR_STRUCT_H
typedef struct
{
    float                               lux;                    /*!<  LUX                       */

    uint8_t                             lux_lower_threshold;    /*!<  LUX lower threshold       */
    uint8_t                             lux_upper_threshold;    /*!<  LUX upper threshold       */

    uint16_t                            threshold_timer_us;     /*!<  Timer threshold           */

    SSD1306_interrupt_status_ints_t    interruptStatus;        /*!<  Interrupt status value    */
    SSD1306_configuration_cdr_t        cdr;                    /*!<  Current division ratio    */
    SSD1306_configuration_tim_t        tim;                    /*!<  integration time          */
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
SSD1306_status_t  SSD1306_Init                    ( I2C_parameters_t myI2Cparameters                                                                                                  );

/** It gets the interrupt status value.
  */
SSD1306_status_t  SSD1306_ReadInterruptStatus     ( I2C_parameters_t myI2Cparameters, SSD1306_vector_data_t* myInterruptStatus                                                       );

/** It enables/disables the interrupt.
  */
SSD1306_status_t  SSD1306_InterrupEnable          ( I2C_parameters_t myI2Cparameters, SSD1306_interrupt_enable_ints_t myInterruptEnable                                              );

/** It configures the device.
  */
SSD1306_status_t  SSD1306_Configuration           ( I2C_parameters_t myI2Cparameters, SSD1306_configuration_cont_t myContinuousMode, SSD1306_configuration_manual_t myManualMode,
                                                      SSD1306_configuration_cdr_t myCurrentRatio, SSD1306_configuration_tim_t myIntegrationTime                                       );

/** It gets the current division ratio
  */
SSD1306_status_t  SSD1306_GetCurrentDivisionRatio ( I2C_parameters_t myI2Cparameters, SSD1306_vector_data_t* myCDR                                                                   );

/** It gets the integration time
  */
SSD1306_status_t  SSD1306_GetIntegrationTime      ( I2C_parameters_t myI2Cparameters, SSD1306_vector_data_t* myTIM                                                                   );

/** It gets the Lux value regarding of the resolution.
  */
SSD1306_status_t  SSD1306_GetLux                  ( I2C_parameters_t myI2Cparameters, SSD1306_device_resolution_t myResolution, SSD1306_vector_data_t* myLux                        );

/** It sets the upper threshold high-byte
  */
SSD1306_status_t  SSD1306_SetUpperThreshold       ( I2C_parameters_t myI2Cparameters, SSD1306_vector_data_t myUpperThreshold                                                         );

/** It sets the lower threshold high-byte
  */
SSD1306_status_t  SSD1306_SetLowerThreshold       ( I2C_parameters_t myI2Cparameters, SSD1306_vector_data_t myLowerThreshold                                                         );

/** It gets the upper threshold high-byte
  */
SSD1306_status_t  SSD1306_GetUpperThreshold       ( I2C_parameters_t myI2Cparameters, SSD1306_vector_data_t* myUpperThreshold                                                        );

/** It gets the lower threshold high-byte
  */
SSD1306_status_t  SSD1306_GetLowerThreshold       ( I2C_parameters_t myI2Cparameters, SSD1306_vector_data_t* myLowerThreshold                                                        );

/** It sets the threshold timer register
  */
SSD1306_status_t  SSD1306_SetThresholdTimer       ( I2C_parameters_t myI2Cparameters, SSD1306_vector_data_t myThresholdTimer_us                                                      );

/** It gets the threshold timer register
  */
SSD1306_status_t  SSD1306_GetThresholdTimer       ( I2C_parameters_t myI2Cparameters, SSD1306_vector_data_t* myThresholdTimer_us                                                     );


#ifdef __cplusplus
}
#endif

#endif /* SSD1306_H */
