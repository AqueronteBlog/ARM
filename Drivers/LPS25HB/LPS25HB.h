/**
 * @brief       LPS25HB.h
 * @details     Capacitive digital sensor for relative humidity and temperature.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        08/June/2019
 * @version     08/June/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESS
  */
typedef enum
{
  LPS25HB_ADDRESS     =   0b1011111          /*!<   I2C slave address byte                       */
} LPS25HB_address_t;



/**
  * @brief   REGISTERS
  */
typedef enum
{
  LPS25HB_WHO_AM_I        =   0x0F,           /*!<  Device identification                         */
  LPS25HB_AV_CONF         =   0x10,           /*!<  Humidity and temperature resolution mode      */
  LPS25HB_CTRL_REG1       =   0x20,           /*!<  Control register 1                            */
  LPS25HB_CTRL_REG2       =   0x21,           /*!<  Control register 2                            */
  LPS25HB_CTRL_REG3       =   0x22,           /*!<  Control register 3                            */
  LPS25HB_STATUS_REG      =   0x27,           /*!<  Status register                               */
  LPS25HB_HUMIDITY_OUT_L  =   0x28,           /*!<  Relative humidity data (LSB)                  */
  LPS25HB_HUMIDITY_OUT_H  =   0x29,           /*!<  Relative humidity data (MSB)                  */
  LPS25HB_TEMP_OUT_L      =   0x2A,           /*!<  Temperature data (LSB)                        */
  LPS25HB_TEMP_OUT_H      =   0x2B,           /*!<  Temperature data (MSB)                        */
  LPS25HB_CALIB_0         =   0x30,           /*!<  Calibration register                          */
  LPS25HB_CALIB_1         =   0x31,           /*!<  Calibration register                          */
  LPS25HB_CALIB_2         =   0x32,           /*!<  Calibration register                          */
  LPS25HB_CALIB_3         =   0x33,           /*!<  Calibration register                          */
  LPS25HB_CALIB_4         =   0x34,           /*!<  Calibration register                          */
  LPS25HB_CALIB_5         =   0x35,           /*!<  Calibration register                          */
  LPS25HB_CALIB_6         =   0x36,           /*!<  Calibration register                          */
  LPS25HB_CALIB_7         =   0x37,           /*!<  Calibration register                          */
  LPS25HB_CALIB_8         =   0x38,           /*!<  Calibration register                          */
  LPS25HB_CALIB_9         =   0x39,           /*!<  Calibration register                          */
  LPS25HB_CALIB_A         =   0x3A,           /*!<  Calibration register                          */
  LPS25HB_CALIB_B         =   0x3B,           /*!<  Calibration register                          */
  LPS25HB_CALIB_C         =   0x3C,           /*!<  Calibration register                          */
  LPS25HB_CALIB_D         =   0x3D,           /*!<  Calibration register                          */
  LPS25HB_CALIB_E         =   0x3E,           /*!<  Calibration register                          */
  LPS25HB_CALIB_F         =   0x3F            /*!<  Calibration register                          */
} LPS25HB_registers_t;



/**
  * @brief   WHO_AM_I REGISTER
  */
typedef enum
{
    WHO_AM_I_MASK           =   0xFF,             /*!<  WHO_AM_I mask                               */
    WHO_AM_I_VALUE          =   0xBC              /*!<  WHO_AM_I value                              */
} LPS25HB_who_am_i_t;



/**
  * @brief   AV_CONF REGISTER
  */
/* AVGT <5:3>
 *    NOTE: Numbers of averaged temperature samples ( 2-256 ).
 */
typedef enum
{
    AV_CONF_AVGT_MASK       =   ( 0b111 << 3U ),    /*!<  AVGT mask                                   */
    AV_CONF_AVGT_2          =   ( 0b000 << 3U ),    /*!<  AVGT Nr. internal average 2                 */
    AV_CONF_AVGT_4          =   ( 0b001 << 3U ),    /*!<  AVGT Nr. internal average 4                 */
    AV_CONF_AVGT_8          =   ( 0b010 << 3U ),    /*!<  AVGT Nr. internal average 8                 */
    AV_CONF_AVGT_16         =   ( 0b011 << 3U ),    /*!<  AVGT Nr. internal average 16    [ Default ] */
    AV_CONF_AVGT_32         =   ( 0b100 << 3U ),    /*!<  AVGT Nr. internal average 32                */
    AV_CONF_AVGT_64         =   ( 0b101 << 3U ),    /*!<  AVGT Nr. internal average 64                */
    AV_CONF_AVGT_128        =   ( 0b110 << 3U ),    /*!<  AVGT Nr. internal average 128               */
    AV_CONF_AVGT_256        =   ( 0b111 << 3U )     /*!<  AVGT Nr. internal average 256               */
} LPS25HB_av_config_avgt_t;


/* AVGH <2:0>
 *    NOTE: Numbers of averaged humidity samples ( 4-512 ).
 */
typedef enum
{
    AV_CONF_AVGH_MASK       =   ( 0b111 << 0U ),    /*!<  AVGH mask                                   */
    AV_CONF_AVGH_4          =   ( 0b000 << 0U ),    /*!<  AVGH Nr. internal average 4                 */
    AV_CONF_AVGH_8          =   ( 0b001 << 0U ),    /*!<  AVGH Nr. internal average 8                 */
    AV_CONF_AVGH_16         =   ( 0b010 << 0U ),    /*!<  AVGH Nr. internal average 16                */
    AV_CONF_AVGH_32         =   ( 0b011 << 0U ),    /*!<  AVGH Nr. internal average 32    [ Default ] */
    AV_CONF_AVGH_64         =   ( 0b100 << 0U ),    /*!<  AVGH Nr. internal average 64                */
    AV_CONF_AVGH_128        =   ( 0b101 << 0U ),    /*!<  AVGH Nr. internal average 128               */
    AV_CONF_AVGH_256        =   ( 0b110 << 0U ),    /*!<  AVGH Nr. internal average 256               */
    AV_CONF_AVGH_512        =   ( 0b111 << 0U )     /*!<  AVGH Nr. internal average 512               */
} LPS25HB_av_config_avgh_t;



/**
  * @brief   CTRL_REG1 REGISTER
  */
/* PD <7>
 *    NOTE: Power-down control.
 */
typedef enum
{
    CTRL_REG1_PD_MASK            =   ( 1U << 7U ),   /*!<  PD mask                                     */
    CTRL_REG1_PD_POWER_DOWN_MODE =   ( 0U << 7U ),   /*!<  PD power-down mode              [ Default ] */
    CTRL_REG1_PD_ACTIVE_MODE     =   ( 1U << 7U )    /*!<  PD active mode                              */
} LPS25HB_ctrl_reg1_pd_t;


/* BDU <2>
 *    NOTE: Block data update.
 */
typedef enum
{
    CTRL_REG1_BDU_MASK               =   ( 1U << 2U ),  /*!<  BDU mask                                                            */
    CTRL_REG1_BDU_CONTINUOUS_UPDATE  =   ( 0U << 2U ),  /*!<  Continuous update                                                   */
    CTRL_REG1_BDU_DEFAULT_MODE       =   ( 1U << 2U )   /*!<  Output registers not updated until MSB and LSB reading  [ Default ] */
} LPS25HB_ctrl_reg1_bdu_t;


/* ODR <1:0>
 *    NOTE: Output data rate selection.
 */
typedef enum
{
    CTRL_REG1_ODR_MASK               =   ( 0b11 << 0U ),  /*!<  ODR mask                                                            */
    CTRL_REG1_ODR_ONE_SHOT           =   ( 0b00 << 0U ),  /*!<  One-shot                                                            */
    CTRL_REG1_ODR_1_HZ               =   ( 0b01 << 0U ),  /*!<  1 Hz                                                                */
    CTRL_REG1_ODR_7_HZ               =   ( 0b10 << 0U ),  /*!<  7 Hz                                                                */
    CTRL_REG1_ODR_12_5_HZ            =   ( 0b11 << 0U )   /*!<  12.5 Hz                                                             */
} LPS25HB_ctrl_reg1_odr_t;



/**
  * @brief   CTRL_REG2 REGISTER
  */
/* BOOT <7>
 *    NOTE: Reboot memory content.
 */
typedef enum
{
    CTRL_REG2_BOOT_MASK                   =   ( 1U << 7U ), /*!<  BOOT mask                                   */
    CTRL_REG2_BOOT_NORMAL_MODE            =   ( 0U << 7U ), /*!<  normal mode                     [ Default ] */
    CTRL_REG2_BOOT_REBOOT_MEMORY_CONTENT  =   ( 1U << 7U )  /*!<  reboot memory content                       */
} LPS25HB_ctrl_reg2_boot_t;


/* Heater <1>
 *    NOTE: Controling an internal heating element.
 */
typedef enum
{
    CTRL_REG2_HEATER_MASK                 =   ( 1U << 1U ), /*!<  Heater mask                                 */
    CTRL_REG2_HEATER_HEATER_DISABLED      =   ( 0U << 1U ), /*!<  Heater disabled                 [ Default ] */
    CTRL_REG2_HEATER_HEATER_ENABLED       =   ( 1U << 1U )  /*!<  Heater enabled                              */
} LPS25HB_ctrl_reg2_heater_t;


/* ONE_SHOT <0>
 *    NOTE: One-shot enable.
 */
typedef enum
{
    CTRL_REG2_ONE_SHOT_MASK               =   ( 1U << 0U ), /*!<  ONE_SHOT mask                               */
    CTRL_REG2_ONE_SHOT_WAITING            =   ( 0U << 0U ), /*!<  waiting for start of conversion [ Default ] */
    CTRL_REG2_ONE_SHOT_START              =   ( 1U << 0U )  /*!<  start for a new dataset                     */
} LPS25HB_ctrl_reg2_one_shot_t;



/**
  * @brief   CTRL_REG3 REGISTER
  */
/* DRDY_H_L <7>
 *    NOTE: Data Ready output signal active high, low.
 */
typedef enum
{
    CTRL_REG3_DRDY_H_L_MASK               =   ( 1U << 7U ), /*!<  DRDY_H_L mask                               */
    CTRL_REG3_DRDY_H_L_ACTIVE_HIGH        =   ( 0U << 7U ), /*!<  active high                     [ Default ] */
    CTRL_REG3_DRDY_H_L_ACTIVE_LOW         =   ( 1U << 7U )  /*!<  active low                                  */
} LPS25HB_ctrl_reg3_drdy_h_l_t;


/* PP_OD <6>
 *    NOTE: Push-pull / Open Drain selection on pin 3 (DRDY).
 */
typedef enum
{
    CTRL_REG3_PP_OD_MASK                  =   ( 1U << 6U ), /*!<  PP_OD mask                                  */
    CTRL_REG3_PP_OD_PUSH_PULL             =   ( 0U << 6U ), /*!<  push-pull                       [ Default ] */
    CTRL_REG3_PP_OD_OPEN_DRAIN            =   ( 1U << 6U )  /*!<  open drain                                  */
} LPS25HB_ctrl_reg3_pp_od_t;


/* DRDY_EN <2>
 *    NOTE: Data Ready enable.
 */
typedef enum
{
    CTRL_REG3_DRDY_EN_MASK                =   ( 1U << 2U ), /*!<  DRDY_EN mask                                */
    CTRL_REG3_DRDY_DATA_READY_DISABLED    =   ( 0U << 2U ), /*!<  Data Ready disabled             [ Default ] */
    CTRL_REG3_DRDY_DATA_READY_ENABLED     =   ( 1U << 2U )  /*!<  Data Ready signal available on pin 3        */
} LPS25HB_ctrl_reg3_drdy_en_t;



/**
  * @brief   STATUS_REG REGISTER
  *
  *   NOTE: H_DA is set to 1 whenever a new humidity sample is available. H_DA is cleared anytime
  *         HUMIDITY_OUT_H (29h) register is read. T_DA is set to 1 whenever a new temperature sample is available. T_DA is cleared anytime TEMP_OUT_H (2Bh) register is read.
  */
/* H_DA <1>
 *    NOTE: Humidity data available.
 */
typedef enum
{
    STATUS_REGISTER_H_DA_MASK               =   ( 1U << 1U ), /*!<  H_DA mask                                   */
    STATUS_REGISTER_H_DA_DATA_NOT_AVAILABLE =   ( 0U << 1U ), /*!<  new data for humidity is not yet available  */
    STATUS_REGISTER_H_DA_DATA_AVAILABLE     =   ( 1U << 1U )  /*!<  new data for humidity is available          */
} LPS25HB_status_reg_h_da_t;


/* T_DA <0>
 *    NOTE: Temperature data available.
 */
typedef enum
{
    STATUS_REGISTER_T_DA_MASK               =   ( 1U << 0U ), /*!<  T_DA mask                                     */
    STATUS_REGISTER_T_DA_DATA_NOT_AVAILABLE =   ( 0U << 0U ), /*!<  new data for temperature is not yet available */
    STATUS_REGISTER_T_DA_DATA_AVAILABLE     =   ( 1U << 0U )  /*!<  new data for temperature is available         */
} LPS25HB_status_reg_t_da_t;



/**
  * @brief   HUMIDITY_OUT_L REGISTER
  *
  *   NOTE: Relative humidity data (LSB)
. *
  */
typedef enum
{
    HUMIDITY_OUT_L_MASK               =   0xFF                  /*!<  Humidity data LSB mask                     */
} LPS25HB_humidity_out_l_t;



/**
  * @brief   HUMIDITY_OUT_H REGISTER
  *
  *   NOTE: Relative humidity data (LSB)
. *
  */
typedef enum
{
    HUMIDITY_OUT_H_MASK               =   0xFF                  /*!<  Humidity data MSB mask                     */
} LPS25HB_humidity_out_h_t;



/**
  * @brief   TEMP_OUT_L REGISTER
  *
  *   NOTE: Temperature data (LSB)
. *
  */
typedef enum
{
    TEMP_OUT_L_MASK                   =   0xFF                  /*!<  Temperature data LSB mask                 */
} LPS25HB_temp_out_l_t;



/**
  * @brief   TEMP_OUT_H REGISTER
  *
  *   NOTE: Temperature data (MSB)
. *
  */
typedef enum
{
    TEMP_OUT_H_MASK                   =   0xFF                  /*!<  Temperature data MSB mask                 */
} LPS25HB_temp_out_h_t;





#ifndef LPS25HB_VECTOR_STRUCT_H
#define LPS25HB_VECTOR_STRUCT_H
typedef struct
{
    /* Output registers  */
    int16_t   rawHumidity;     /*!<  Raw humidity                  */
    int16_t   rawTemperature;  /*!<  Raw temperature               */

    float     humidity;        /*!<  Humidity value                */
    float     temperature;     /*!<  Temperature value             */

    /* Calibration registers  */
    uint8_t   h0_rH_x2;        /*!<  Calibration register          */
    uint8_t   h1_rH_x2;        /*!<  Calibration register          */
    uint8_t   t0_degC_x8;      /*!<  Calibration register          */
    uint8_t   t1_degC_x8;      /*!<  Calibration register          */
    uint8_t   t1_T0_msb;       /*!<  Calibration register          */
    int16_t   h0_T0_OUT;       /*!<  Calibration register          */
    int16_t   h1_T0_OUT;       /*!<  Calibration register          */
    int16_t   t0_OUT;          /*!<  Calibration register          */
    int16_t   t1_OUT;          /*!<  Calibration register          */

    int16_t   t0_degC;         /*!<  Calibration result            */
    int16_t   t1_degC;         /*!<  Calibration result            */
    int16_t   h0_RH;           /*!<  Calibration result            */
    int16_t   h1_RH;           /*!<  Calibration result            */

    /* Device identification   */
    uint8_t   deviceID;        /*!<  Device ID                     */

    /* Device configuration   */
    LPS25HB_av_config_avgt_t     temperatureResolution;  /*!<  Temperature resolution        */
    LPS25HB_av_config_avgh_t     humidityResolution;     /*!<  Humidity resolution           */

    LPS25HB_ctrl_reg1_bdu_t      bdu;                    /*!<  Block data update             */
    LPS25HB_ctrl_reg1_odr_t      odr;                    /*!<  Output data rate              */
    LPS25HB_ctrl_reg2_boot_t     boot;                   /*!<  Reboot mode content           */
    LPS25HB_ctrl_reg2_heater_t   heater;                 /*!<  Heater                        */
    LPS25HB_ctrl_reg2_one_shot_t one_shot;               /*!<  One-Shot                      */

    /* Device status   */
    LPS25HB_status_reg_h_da_t    h_da;                   /*!<  Humidity data available       */
    LPS25HB_status_reg_t_da_t    t_da;                   /*!<  Temperature data available    */
} LPS25HB_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    LPS25HB_SUCCESS     =       0,
    LPS25HB_FAILURE     =       1
} LPS25HB_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
LPS25HB_status_t LPS25HB_Init               ( I2C_parameters_t myI2Cparameters                                          );

/** It gets the device identification.
  */
LPS25HB_status_t LPS25HB_GetDeviceID        ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myDeviceID               );

/** It sets humidity and temperature resolution mode.
  */
LPS25HB_status_t LPS25HB_SetResolution      ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t myTempHumResolution       );

/** It gets humidity and temperature resolution mode.
  */
LPS25HB_status_t LPS25HB_GetResolution      ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myTempHumResolution      );

/** It sets power-down control mode.
  */
LPS25HB_status_t LPS25HB_SetPowerDown       ( I2C_parameters_t myI2Cparameters, LPS25HB_ctrl_reg1_pd_t myPowerMode       );

/** It sets the block data update.
  */
LPS25HB_status_t LPS25HB_SetBlockDataUpdate ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t myBDU                     );

/** It gets the block data update.
  */
LPS25HB_status_t LPS25HB_GetBlockDataUpdate ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myBDU                    );

/** It sets the output data rate ( ODR ).
  */
LPS25HB_status_t LPS25HB_SetOutputDataRate  ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t  myODR                    );

/** It gets the output data rate ( ODR ).
  */
LPS25HB_status_t LPS25HB_GetOutputDataRate  ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myODR                    );

/** It sets reboot memory content.
  */
LPS25HB_status_t LPS25HB_SetBoot            ( I2C_parameters_t myI2Cparameters                                          );

/** It gets reboot memory content.
  */
LPS25HB_status_t LPS25HB_GetBoot            ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myBOOT                   );

/** It sets heater mode: Enabled/Disabled.
  */
LPS25HB_status_t LPS25HB_SetHeater          ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t  myHeater                 );

/** It gets heater mode.
  */
LPS25HB_status_t LPS25HB_GetHeater          ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myHeater                 );

/** It sets one-shot, new data set.
  */
LPS25HB_status_t LPS25HB_SetOneShot         ( I2C_parameters_t myI2Cparameters                                          );

/** It gets one-shot flag.
  */
LPS25HB_status_t LPS25HB_GetOneShot         ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myOneShot                );

/** It sets data ready output signal active high/low.
  */
LPS25HB_status_t LPS25HB_SetDataReadyOuput  ( I2C_parameters_t myI2Cparameters, LPS25HB_ctrl_reg3_drdy_h_l_t myDRDY_H_L  );

/** It sets Push-pull/Open Drain selection on pin 3 ( DRDY ).
  */
LPS25HB_status_t LPS25HB_SetSelectionOnPin3 ( I2C_parameters_t myI2Cparameters, LPS25HB_ctrl_reg3_pp_od_t myDRDY         );

/** It sets data ready enable.
  */
LPS25HB_status_t LPS25HB_SetDataReadyEnable ( I2C_parameters_t myI2Cparameters, LPS25HB_ctrl_reg3_drdy_en_t myDRDY_EN    );

/** It gets humidity data available flag.
  */
LPS25HB_status_t LPS25HB_GetHumidityDataAvailable ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myHumidityFlag     );

/** It gets temperature data available flag.
  */
LPS25HB_status_t LPS25HB_GetTemperatureDataAvailable  ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myTemperatureFlag  );

/** It gets raw humidity.
  */
LPS25HB_status_t LPS25HB_GetRawHumidity             ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myRawHumidity            );

/** It gets raw temperature.
  */
LPS25HB_status_t LPS25HB_GetRawTemperature          ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myRawTemperature         );

/** It gets calibration coefficients.
  */
LPS25HB_status_t LPS25HB_GetCalibrationCoefficients ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myCoeff           );

/** It gets the current temperature value in Celsius degrees.
  */
LPS25HB_status_t LPS25HB_GetTemperature             ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myTemperature     );

/** It gets the current humidity value.
  */
LPS25HB_status_t LPS25HB_GetHumidity                ( I2C_parameters_t myI2Cparameters, LPS25HB_data_t* myHumidity        );