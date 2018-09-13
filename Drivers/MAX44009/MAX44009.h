/**
 * @brief       MAX30100.h
 * @details     Pulse Oximeter and Heart-Rate Sensor IC for Wearable Health.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/July/2018
 * @version     9/July/2018    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


#ifndef MAX30100_H_
#define MAX30100_H_

#ifdef __cplusplus
extern "C" {
#endif



/**
  * @brief   DEFAULT ADDRESS
  */
typedef enum
{
    MAX30100_ADDRESS     =   0b1010111                      /*!<   MAX30100 I2C Address                                     */
} MAX30100_address_t;


/* REGISTER MAPS     */
/**
  * @brief   REGISTERS BYTE
  */
typedef enum
{
    MAX30100_INTERRUPT_STATUS       =   0x00,               /*!<  Interrupt Status          ( Read Only  ) ( Default 0x00 ) */
    MAX30100_INTERRUPT_ENABLE       =   0x01,               /*!<  Interrupt Enable          ( Read/Write ) ( Default 0x00 ) */
    MAX30100_FIFO_WRITE_POINTER     =   0x02,               /*!<  FIFO Write Pointer        ( Read/Write ) ( Default 0x00 ) */
    MAX30100_OVER_FLOW_COUNTER      =   0x03,               /*!<  Over Flow Counter         ( Read/Write ) ( Default 0x00 ) */
    MAX30100_FIFO_READ_POINTER      =   0x04,               /*!<  FIFO Read Pointer         ( Read/Write ) ( Default 0x00 ) */
    MAX30100_FIFO_DATA_REGISTER     =   0x05,               /*!<  FIFO Data Register        ( Read/Write ) ( Default 0x00 ) */
    MAX30100_MODE_CONFIGURATION     =   0x06,               /*!<  Mode Configuration        ( Read/Write ) ( Default 0x00 ) */
    MAX30100_SPO2_CONFIGURATION     =   0x07,               /*!<  SpO2 Configuration        ( Read/Write ) ( Default 0x00 ) */
    MAX30100_LED_CONFIGURATION      =   0x09,               /*!<  LED Configuration         ( Read/Write ) ( Default 0x00 ) */
    MAX30100_TEMP_INTEGER           =   0x16,               /*!<  Temperature Integer       ( Read/Write ) ( Default 0x00 ) */
    MAX30100_TEMP_FRACTION          =   0x17,               /*!<  Temperature Fraction      ( Read/Write ) ( Default 0x00 ) */
    MAX30100_REVISION_ID            =   0xFE,               /*!<  T HIGH Register           ( Read Only  ) ( Default ??   ) */
    MAX30100_PART_ID                =   0xFF                /*!<  T HIGH Register           ( Read/Write ) ( Default 0x11 ) */
} MAX30100_register_maps_t;



/* INTERRUPT STATUS  */
/**
  * @brief   FIFO ALMOST FULL FLAG. In SpO2 and heart-rate modes, this interrupt triggers when the FIFO write pointer is the same as
  *                                 the FIFO read pointer minus one, which means that the FIFO has only one unwritten space left. If
  *                                 the FIFO is not read within the next conversion time, the FIFO becomes full and future data is lost.
  */
typedef enum
{
    INTERRUPT_STATUS_A_FULL_MASK        =   ( 1 << 7 ),     /*!<  A_FULL mask                                                   */
    INTERRUPT_STATUS_A_FULL_TRIGGERED   =   ( 1 << 7 )      /*!<  A_FULL is triggered                                           */
} MAX30100_interrupt_status_a_full_flag_t;


/**
  * @brief   TEMPERATURE READY FLAG. When an internal die temperature conversion is finished, this interrupt is triggered so the processor
  *                                  can read the temperature data registers.
  */
typedef enum
{
    INTERRUPT_STATUS_TEMP_RDY_MASK      =   ( 1 << 6 ),     /*!<  TEMP_RDY mask                                                 */
    INTERRUPT_STATUS_TEMP_RDY_TRIGGERED =   ( 1 << 6 )      /*!<  TEMP_RDY is triggered                                         */
} MAX30100_interrupt_status_temp_rdy_flag_t;


/**
  * @brief   HEART RATE DATA READY. In heart rate or SPO2 mode, this interrupt triggers after every data sample is collected. A heart rate
  *                                 data sample consists of one IR data point only. This bit is automatically cleared when the FIFO data
  *                                 register is read.
  */
typedef enum
{
    INTERRUPT_STATUS_HR_RDY_MASK        =   ( 1 << 5 ),     /*!<  HR_RDY mask                                                   */
    INTERRUPT_STATUS_HR_RDY_TRIGGERED   =   ( 1 << 5 )      /*!<  HR_RDY is triggered                                           */
} MAX30100_interrupt_status_hr_rdy_flag_t;


/**
  * @brief   SPO2 DATA READY. In SpO2 mode, this interrupt triggers after every data sample is collected. An SpO2 data sample consists of
  *                           one IR and one red data points. This bit is automatically cleared when the FIFO data register is read.
  */
typedef enum
{
    INTERRUPT_STATUS_SPO2_RDY_MASK      =   ( 1 << 4 ),     /*!<  SPO2_RDY mask                                                 */
    INTERRUPT_STATUS_SPO2_RDY_TRIGGERED =   ( 1 << 4 )      /*!<  SPO2_RDY is triggered                                         */
} MAX30100_interrupt_status_spo2_rdy_flag_t;


/**
  * @brief   POWER READY FLAG. On power-up or after a brownout condition, when the supply voltage VDD transitions from below the UVLO
  *                            voltage to above the UVLO voltage, a power-ready interrupt is triggered to signal that the IC is powered
  *                            up and ready to collect data.
  */
typedef enum
{
    INTERRUPT_STATUS_PWR_RDY_MASK       =   ( 1 << 0 ),     /*!<  PWR_RDY mask                                                  */
    INTERRUPT_STATUS_PWR_RDY_TRIGGERED  =   ( 1 << 0 )      /*!<  PWR_RDY is triggered                                          */
} MAX30100_interrupt_status_pwr_rdy_flag_t;



/* INTERRUPT ENABLE. NOTE: Each source of hardware interrupt, with the exception of power ready, can be disabled in a software register within the MAX30100 IC.
                           The power-ready interrupt cannot be disabled because the digital state of the MAX30100 is reset upon a brownout condition (low power-supply voltage),
                           and the default state is that all the interrupts are disabled. It is important for the system to know that a brownout condition has occurred, and the
                           data within the device is reset as a result.

                           When an interrupt enable bit is set to zero, the corresponding interrupt appears as 1 in the interrupt status register, but the INT pin is not pulled low.
                           The four unused bits (B3:B0) should always be set to zero (disabled) for normal operation
*/
/**
  * @brief   ENB_A_FULL.
  */
typedef enum
{
    INTERRUPT_ENABLE_ENB_A_FULL_MASK        =   ( 1 << 7 ),     /*!<  ENB_A_FULL mask                                               */
    INTERRUPT_ENABLE_ENB_A_FULL_ENABLE      =   ( 1 << 7 ),     /*!<  ENB_A_FULL enables                                            */
    INTERRUPT_ENABLE_ENB_A_FULL_DISABLE     =   ( 0 << 7 )      /*!<  ENB_A_FULL disables                                           */
} MAX30100_interrupt_enable_enb_a_full_t;


/**
  * @brief   ENB_TEP_RDY.
  */
typedef enum
{
    INTERRUPT_ENABLE_ENB_TEP_RDY_MASK       =   ( 1 << 6 ),     /*!<  ENB_TEP_RDY mask                                              */
    INTERRUPT_ENABLE_ENB_TEP_RDY_ENABLE     =   ( 1 << 6 ),     /*!<  ENB_TEP_RDY enables                                           */
    INTERRUPT_ENABLE_ENB_TEP_RDY_DISABLE    =   ( 0 << 6 )      /*!<  ENB_TEP_RDY disables                                          */
} MAX30100_interrupt_enable_enb_tep_rdy_t;


/**
  * @brief   ENB_HR_RDY.
  */
typedef enum
{
    INTERRUPT_ENABLE_ENB_HR_RDY_MASK        =   ( 1 << 5 ),     /*!<  ENB_HR_RDY mask                                               */
    INTERRUPT_ENABLE_ENB_HR_RDY_ENABLE      =   ( 1 << 5 ),     /*!<  ENB_HR_RDY enables                                            */
    INTERRUPT_ENABLE_ENB_HR_RDY_DISABLE     =   ( 0 << 5 )      /*!<  ENB_HR_RDY disables                                           */
} MAX30100_interrupt_enable_enb_hr_rdy_t;


/**
  * @brief   ENB_SO2_RDY.
  */
typedef enum
{
    INTERRUPT_ENABLE_ENB_SO2_RDY_MASK       =   ( 1 << 4 ),     /*!<  ENB_SO2_RDY mask                                              */
    INTERRUPT_ENABLE_ENB_SO2_RDY_ENABLE     =   ( 1 << 4 ),     /*!<  ENB_SO2_RDY enables                                           */
    INTERRUPT_ENABLE_ENB_SO2_RDY_DISABLE    =   ( 0 << 4 )      /*!<  ENB_SO2_RDY disables                                          */
} MAX30100_interrupt_enable_enb_so2_rdy_t;



/* FIFO  */
/**
  * @brief   FIFO WRITE POINTER. The FIFO write pointer points to the location where the MAX30100 writes the next sample. This pointer advances for each sample
  *                              pushed on to the FIFO. It can also be changed through the I2C interface when MODE[2:0] is nonzero.
  */
typedef enum
{
    FIFO_FIFO_WRITE_POINTER_MASK            =   0b00001111      /*!<  FIFO WRITE POINTER mask                                       */
} MAX30100_fifo_fifo_write_pointer_t;


/**
  * @brief   OVER FLOW COUNTER. When the FIFO is full, samples are not pushed on to the FIFO, samples are lost. OVF_COUNTER counts the number of samples lost.
  *                             It saturates at 0xF. When a complete sample is popped from the FIFO (when the read pointer advances), OVF_COUNTER is reset to zero.
  */
typedef enum
{
    FIFO_OVER_FLOW_COUNTER_MASK             =   0b00001111      /*!<  OVER FLOW COUNTER mask                                        */
} MAX30100_fifo_over_flow_counter_t;


/**
  * @brief   FIFO READ POINTER. The FIFO read pointer points to the location from where the processor gets the next sample from the FIFO via the I2C interface.
  *                             This advances each time a sample is popped from the FIFO. The processor can also write to this pointer after reading the samples,
  *                             which would allow rereading samples from the FIFO if there is a data communication error.
  */
typedef enum
{
    FIFO_FIFO_READ_POINTER_MASK             =   0b00001111      /*!<  FIFO READ POINTER mask                                        */
} MAX30100_fifo_fifo_read_pointer_t;



/* MODE CONFIGURATION  */
/**
  * @brief   SHUTDOWN CONTROL. The part can be put into a power-save mode by setting this bit to one. While in power-save mode, all registers retain their values,
  *                            and write/read operations function as normal. All interrupts are cleared to zero in this mode.
  */
typedef enum
{
    MODE_CONFIGURATION_SHDN_MASK        =   ( 1 << 7 ),     /*!<  SHDN mask                                                     */
    MODE_CONFIGURATION_SHDN_ENABLE      =   ( 1 << 7 ),     /*!<  SHDN enables                                                  */
    MODE_CONFIGURATION_SHDN_DISABLE     =   ( 0 << 7 )      /*!<  SHDN disables                                                 */
} MAX30100_mode_configuration_shdn_t;


/**
  * @brief   RESET CONTROL. When the RESET bit is set to one, all configuration, threshold, and data registers are reset to their power-on-state. The only exception is
  *                         writing both RESET and TEMP_EN bits to one at the same time since temperature data registers 0x16 and 0x17 are not cleared. The RESET bit is
  *                         cleared automatically back to zero after the reset sequence is completed.
  */
typedef enum
{
    MODE_CONFIGURATION_RESET_MASK       =   ( 1 << 6 ),     /*!<  RESET mask                                                    */
    MODE_CONFIGURATION_RESET_ENABLE     =   ( 1 << 6 ),     /*!<  RESET enables                                                 */
    MODE_CONFIGURATION_RESET_DISABLE    =   ( 0 << 6 )      /*!<  RESET disables                                                */
} MAX30100_mode_configuration_reset_t;


/**
  * @brief   TEMPERATURE ENABLE. This is a self-clearing bit which, when set, initiates a single temperature reading from the temperature sensor. This bit is cleared
  *                              automatically back to zero at the conclusion of the temperature reading when the bit is set to one in heart rate or SpO2 mode.
  */
typedef enum
{
    MODE_CONFIGURATION_TEMP_EN_MASK     =   ( 1 << 3 ),     /*!<  TEMP_EN mask                                                  */
    MODE_CONFIGURATION_TEMP_EN_ENABLE   =   ( 1 << 3 ),     /*!<  TEMP_EN enables                                               */
    MODE_CONFIGURATION_TEMP_EN_DISABLE  =   ( 0 << 3 )      /*!<  TEMP_EN disables                                              */
} MAX30100_mode_configuration_temp_en_t;


/**
  * @brief   MODE CONTROL. These bits set the operating state of the MAX30100. Changing modes does not change any other setting, nor does it erase any previously stored
  *                        data inside the data registers.
  */
typedef enum
{
    MODE_CONFIGURATION_MODE_MASK            =   ( 0b111 << 0 ),     /*!<  MODE mask                                                     */
    MODE_CONFIGURATION_MODE_HR_ONLY_ENABLED =   ( 0b010 << 0 ),     /*!<  MODE: HR only enabled                                         */
    MODE_CONFIGURATION_MODE_SPO2_ENABLED    =   ( 0b011 << 0 )      /*!<  MODE: SPO2 enabled                                            */
} MAX30100_mode_configuration_mode_t;



/* SPO2 CONFIGURATION  */
/**
  * @brief   SPO2 HIGH RESOLUTION ENABLE. Set this bit high. The SpO2 ADC resolution is 16-bit with 1.6ms LED pulse width.
  */
typedef enum
{
    SPO2_CONFIGURATION_SPO2_HI_RES_EN_MASK      =   ( 1 << 6 ),     /*!<  SPO2_HI_RES_EN mask                                           */
    SPO2_CONFIGURATION_SPO2_HI_RES_EN_ENABLE    =   ( 1 << 6 ),     /*!<  SPO2_HI_RES_EN enables                                        */
    SPO2_CONFIGURATION_SPO2_HI_RES_EN_DISABLE   =   ( 0 << 6 )      /*!<  SPO2_HI_RES_EN disables                                       */
} MAX30100_spo2_configuration_spo2_hi_res_en_t;


/**
  * @brief   SPO2 SAMPLE RATE CONTROL. These bits define the effective sampling rate, with one sample consisting of one IR pulse/conversion and one RED pulse/conversion.
  *                                    The sample rate and pulse width are related, in that the sample rate sets an upper bound on the pulse width time. If the user selects
  *                                    a sample rate that is too high for the selected LED_PW setting, the highest possible sample rate will instead be programmed into the register.
  */
typedef enum
{
    SPO2_CONFIGURATION_SPO2_SR_MASK             =   ( 0b111 << 2 ),     /*!<  SPO2_SR mask                                                  */
    SPO2_CONFIGURATION_SPO2_SR_50               =   ( 0b000 << 2 ),     /*!<  SPO2_SR 50 samples per second   ( default )                   */
    SPO2_CONFIGURATION_SPO2_SR_100              =   ( 0b001 << 2 ),     /*!<  SPO2_SR 100 samples per second                                */
    SPO2_CONFIGURATION_SPO2_SR_167              =   ( 0b010 << 2 ),     /*!<  SPO2_SR 167 samples per second                                */
    SPO2_CONFIGURATION_SPO2_SR_200              =   ( 0b011 << 2 ),     /*!<  SPO2_SR 200 samples per second                                */
    SPO2_CONFIGURATION_SPO2_SR_400              =   ( 0b100 << 2 ),     /*!<  SPO2_SR 400 samples per second                                */
    SPO2_CONFIGURATION_SPO2_SR_600              =   ( 0b101 << 2 ),     /*!<  SPO2_SR 600 samples per second                                */
    SPO2_CONFIGURATION_SPO2_SR_800              =   ( 0b110 << 2 ),     /*!<  SPO2_SR 800 samples per second                                */
    SPO2_CONFIGURATION_SPO2_SR_1000             =   ( 0b111 << 2 )      /*!<  SPO2_SR 1000 samples per second                               */
} MAX30100_spo2_configuration_spo2_sr_t;


/**
  * @brief   LED PULSE WIDTH CONTROL. These bits set the LED pulse width (the IR and RED have the same pulse width), and therefore, indirectly set the integration time of the ADC in each
  *                                   sample. The ADC resolution is directly related to the integration time.
  */
typedef enum
{
    SPO2_CONFIGURATION_LED_PW_MASK              =   ( 0b11 << 0 ),      /*!<  LED_PW mask                                                   */
    SPO2_CONFIGURATION_LED_PW_200US_13BITS      =   ( 0b00 << 0 ),      /*!<  LED_PW 200us  13-bits ADC   ( default )                       */
    SPO2_CONFIGURATION_LED_PW_400US_14BITS      =   ( 0b01 << 0 ),      /*!<  LED_PW 400us  14-bits ADC                                     */
    SPO2_CONFIGURATION_LED_PW_800US_15BITS      =   ( 0b10 << 0 ),      /*!<  LED_PW 800us  15-bits ADC                                     */
    SPO2_CONFIGURATION_LED_PW_1600US_16BITS     =   ( 0b11 << 0 )       /*!<  LED_PW 1600us 16-bits ADC                                     */
} MAX30100_spo2_configuration_led_pw_t;



/* LED Configuration  */
/**
  * @brief   RED LED CURRENT CONTROL.
  */
typedef enum
{
    LED_CONFIGURATION_RED_PA_MASK              =   ( 0b1111 << 4 ),     /*!<  RED_PA mask                                                   */
    LED_CONFIGURATION_RED_PA_0_0_MA            =   ( 0b0000 << 4 ),     /*!<  RED_PA LED current 0.0mA                                      */
    LED_CONFIGURATION_RED_PA_4_4_MA            =   ( 0b0001 << 4 ),     /*!<  RED_PA LED current 4.4mA                                      */
    LED_CONFIGURATION_RED_PA_7_6_MA            =   ( 0b0010 << 4 ),     /*!<  RED_PA LED current 7.6mA                                      */
    LED_CONFIGURATION_RED_PA_11_0_MA           =   ( 0b0011 << 4 ),     /*!<  RED_PA LED current 11.0mA                                     */
    LED_CONFIGURATION_RED_PA_14_2_MA           =   ( 0b0100 << 4 ),     /*!<  RED_PA LED current 14.2mA                                     */
    LED_CONFIGURATION_RED_PA_17_4_MA           =   ( 0b0101 << 4 ),     /*!<  RED_PA LED current 17.4mA                                     */
    LED_CONFIGURATION_RED_PA_20_8_MA           =   ( 0b0110 << 4 ),     /*!<  RED_PA LED current 20.8mA                                     */
    LED_CONFIGURATION_RED_PA_24_0_MA           =   ( 0b0111 << 4 ),     /*!<  RED_PA LED current 24.0mA                                     */
    LED_CONFIGURATION_RED_PA_27_1_MA           =   ( 0b1000 << 4 ),     /*!<  RED_PA LED current 27.1mA ( default )                         */
    LED_CONFIGURATION_RED_PA_30_6_MA           =   ( 0b1001 << 4 ),     /*!<  RED_PA LED current 30.6mA                                     */
    LED_CONFIGURATION_RED_PA_33_8_MA           =   ( 0b1010 << 4 ),     /*!<  RED_PA LED current 33.8mA                                     */
    LED_CONFIGURATION_RED_PA_37_0_MA           =   ( 0b1011 << 4 ),     /*!<  RED_PA LED current 37.0mA                                     */
    LED_CONFIGURATION_RED_PA_40_2_MA           =   ( 0b1100 << 4 ),     /*!<  RED_PA LED current 40.2mA                                     */
    LED_CONFIGURATION_RED_PA_43_6_MA           =   ( 0b1101 << 4 ),     /*!<  RED_PA LED current 43.6mA                                     */
    LED_CONFIGURATION_RED_PA_46_8_MA           =   ( 0b1110 << 4 ),     /*!<  RED_PA LED current 46.8mA                                     */
    LED_CONFIGURATION_RED_PA_50_0_MA           =   ( 0b1111 << 4 )      /*!<  RED_PA LED current 50.0mA                                     */
} MAX30100_led_configuration_red_pa_t;



/**
  * @brief   IR LED CURRENT CONTROL.
  */
typedef enum
{
    LED_CONFIGURATION_IR_PA_MASK               =   ( 0b1111 << 0 ),     /*!<  IR_PA mask                                                    */
    LED_CONFIGURATION_IR_PA_0_0_MA             =   ( 0b0000 << 0 ),     /*!<  IR_PA LED current 0.0mA                                       */
    LED_CONFIGURATION_IR_PA_4_4_MA             =   ( 0b0001 << 0 ),     /*!<  IR_PA LED current 4.4mA                                       */
    LED_CONFIGURATION_IR_PA_7_6_MA             =   ( 0b0010 << 0 ),     /*!<  IR_PA LED current 7.6mA                                       */
    LED_CONFIGURATION_IR_PA_11_0_MA            =   ( 0b0011 << 0 ),     /*!<  IR_PA LED current 11.0mA                                      */
    LED_CONFIGURATION_IR_PA_14_2_MA            =   ( 0b0100 << 0 ),     /*!<  IR_PA LED current 14.2mA                                      */
    LED_CONFIGURATION_IR_PA_17_4_MA            =   ( 0b0101 << 0 ),     /*!<  IR_PA LED current 17.4mA                                      */
    LED_CONFIGURATION_IR_PA_20_8_MA            =   ( 0b0110 << 0 ),     /*!<  IR_PA LED current 20.8mA                                      */
    LED_CONFIGURATION_IR_PA_24_0_MA            =   ( 0b0111 << 0 ),     /*!<  IR_PA LED current 24.0mA                                      */
    LED_CONFIGURATION_IR_PA_27_1_MA            =   ( 0b1000 << 0 ),     /*!<  IR_PA LED current 27.1mA                                      */
    LED_CONFIGURATION_IR_PA_30_6_MA            =   ( 0b1001 << 0 ),     /*!<  IR_PA LED current 30.6mA                                      */
    LED_CONFIGURATION_IR_PA_33_8_MA            =   ( 0b1010 << 0 ),     /*!<  IR_PA LED current 33.8mA                                      */
    LED_CONFIGURATION_IR_PA_37_0_MA            =   ( 0b1011 << 0 ),     /*!<  IR_PA LED current 37.0mA                                      */
    LED_CONFIGURATION_IR_PA_40_2_MA            =   ( 0b1100 << 0 ),     /*!<  IR_PA LED current 40.2mA                                      */
    LED_CONFIGURATION_IR_PA_43_6_MA            =   ( 0b1101 << 0 ),     /*!<  IR_PA LED current 43.6mA                                      */
    LED_CONFIGURATION_IR_PA_46_8_MA            =   ( 0b1110 << 0 ),     /*!<  IR_PA LED current 46.8mA                                      */
    LED_CONFIGURATION_IR_PA_50_0_MA            =   ( 0b1111 << 0 )      /*!<  IR_PA LED current 50.0mA ( default )                         */
} MAX30100_led_configuration_ir_pa_t;





#ifndef MAX30100_VECTOR_STRUCT_H
#define MAX30100_VECTOR_STRUCT_H
typedef struct
{
    uint8_t  FIFO_buff[64];                                          /*!<  FIFO buffer                           */
    uint8_t  FIFO_wr_ptr;                                            /*!<  FIFO write pointer                    */
    uint8_t  OVF_counter;                                            /*!<  FIFO Overflow counter                 */
    uint8_t  FIFO_rd_ptr;                                            /*!<  FIFO read pointer                     */

    uint16_t FIFO_IR_samples[16];                                    /*!<  FIFO IR buffer                        */
    uint16_t FIFO_RED_samples[16];                                   /*!<  FIFO RED buffer                       */

    float    Temperature;                                            /*!<  Processed temperature                 */

    int8_t   Temp_Integer;                                           /*!<  Raw Temperature: Integer part         */
    int8_t   Temp_Fraction;                                          /*!<  Raw Temperature: Fraction part        */

    MAX30100_mode_configuration_temp_en_t TemperatureFlag;           /*!<  Temperature flag for polling mode     */
    MAX30100_mode_configuration_reset_t   ResetFlag;                 /*!<  Software Reset flag for polling mode  */

    MAX30100_spo2_configuration_led_pw_t  Resolution;                /*!<  Pulse width/Resolution                */

    uint8_t  InterruptStatus;                                        /*!<  Interrupt status value                */
    uint8_t  RevisionID;                                             /*!<  Revision ID                           */
    uint8_t  PartID;                                                 /*!<  Part ID                               */
} MAX30100_vector_data_t;
#endif





/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    MAX30100_SUCCESS     =       0,
    MAX30100_FAILURE     =       1
} MAX30100_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
MAX30100_status_t  MAX30100_Init                            ( I2C_parameters_t myI2Cparameters                                                              );

/** It gets the interrupt status value.
  */
MAX30100_status_t  MAX30100_ReadInterruptStatus             ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myInterruptStatus                   );

/** It sets which interrupt is enabled/disabled.
  */
MAX30100_status_t  MAX30100_InterrupEnable                  ( I2C_parameters_t myI2Cparameters, uint8_t myInterruptEnable                                   );

/** It sets the power mode.
  */
MAX30100_status_t  MAX30100_ShutdownControl                 ( I2C_parameters_t myI2Cparameters, MAX30100_mode_configuration_shdn_t myPowerMode              );

/** It performs a software reset.
  */
MAX30100_status_t  MAX30100_SoftwareReset                   ( I2C_parameters_t myI2Cparameters                                                              );

/** It checks if the software reset was completed by polling mode.
  */
MAX30100_status_t  MAX30100_PollingSoftwareReset            ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myResetFlag                         );

/** It initiates a single temperature reading from the temperature sensor.
  */
MAX30100_status_t  MAX30100_TriggerTemperature              ( I2C_parameters_t myI2Cparameters                                                              );

/** It checks if the temperature conversion was completed by polling mode.
  */
MAX30100_status_t  MAX30100_PollingTemperatureConversion    ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myTempFlag                          );

/** It sets the operating state of the MAX30100.
  */
MAX30100_status_t  MAX30100_ModeControl                     ( I2C_parameters_t myI2Cparameters, MAX30100_mode_configuration_mode_t myModeControl            );

/** It sets the SpO2 ADC resolution is 16-bit with 1.6ms LED pulse width.
  */
MAX30100_status_t  MAX30100_SpO2_HighResolution             ( I2C_parameters_t myI2Cparameters, MAX30100_spo2_configuration_spo2_hi_res_en_t myRes          );

/** It defines the effective sampling rate.
  */
MAX30100_status_t  MAX30100_SpO2_SampleRateControl          ( I2C_parameters_t myI2Cparameters, MAX30100_spo2_configuration_spo2_sr_t mySampleRate          );

/** It sets the LED pulse width.
  */
MAX30100_status_t  MAX30100_LED_PulseWidthControl           ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t myLEDWidth                           );

/** It gets the LED pulse width.
  */
MAX30100_status_t  MAX30100_Get_LED_PulseWidthControl       ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myLEDWidth                          );

/** It sets the current level of the Red LED.
  */
MAX30100_status_t  MAX30100_SetRed_LED_CurrentControl       ( I2C_parameters_t myI2Cparameters, MAX30100_led_configuration_red_pa_t myRedLED                );

/** It sets the current level of the IR LED.
  */
MAX30100_status_t  MAX30100_SetIR_LED_CurrentControl        ( I2C_parameters_t myI2Cparameters, MAX30100_led_configuration_ir_pa_t myIRLED                  );

/** It gets the raw temperature data ( temperature integer and temperature fraction ).
  */
MAX30100_status_t  MAX30100_GetRawTemperature               ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myRawTemperature                    );

/** It gets the temperature value.
  */
MAX30100_status_t  MAX30100_GetTemperature                  ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myTemperature                       );

/** It gets the revision ID.
  */
MAX30100_status_t  MAX30100_GetRevisionID                   ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myRevisionID                        );

/** It gets the part ID.
  */
MAX30100_status_t  MAX30100_GetPartID                       ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myPartID                            );

/** It gets data from the FIFO.
  */
MAX30100_status_t  MAX30100_ReadFIFO                        ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myDATA, uint32_t myNumSamplesToRead );

/** It clears the FIFO registers.
  */
MAX30100_status_t  MAX30100_ClearFIFO                       ( I2C_parameters_t myI2Cparameters, MAX30100_vector_data_t* myDATA                              );


#ifdef __cplusplus
}
#endif

#endif /* MAX30100_H */
