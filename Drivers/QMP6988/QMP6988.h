/**
 * @brief       QMP6988.h
 * @details     Digital Barometric Pressure Sensor.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        12/February/2022
 * @version     12/February/2022    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */
#ifndef QMP6988_H_
#define QMP6988_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESSES
  */
typedef enum
{
    QMP6988_ADDRESS_SDO_HIGH    =   0x56,                		/*!<   QMP6988 I2C Address, SDO High           	*/
	QMP6988_ADDRESS_SDO_LOW     =   0x70                		/*!<   QMP6988 I2C Address, SDO Low           	*/
} QMP6988_addresses_t;




/**
  * @brief   COMMAND REGISTERS
  */
typedef enum
{
	QMP6988_TEMP_TXD0		=   0xFC,			/*!<  Temperature DATA[8:1] in 24bit		*/
    QMP6988_TEMP_TXD1     	=   0xFB,      		/*!<  Temperature DATA[16:9] in 24bit      	*/
    QMP6988_TEMP_TXD2   	=   0xFA,     		/*!<  Temperature DATA[24:17] in 24bit     	*/
    QMP6988_PRESS_TXD0		=   0xF9,        	/*!<  Pressure DATA[8:1] in 24bit          	*/
	QMP6988_PRESS_TXD1		=   0xF8,        	/*!<  Pressure DATA[16:9] in 24bit         	*/
	QMP6988_PRESS_TXD2		=   0xF7,        	/*!<  Pressure DATA[24:17] in 24bit        	*/
	QMP6988_IO_SETUP		=   0xF5,        	/*!<  Set-up		                    	*/
	QMP6988_CTRL_MEAS		=   0xF4,        	/*!<  Control		                    	*/
	QMP6988_DEVICE_STAT		=   0xF3,        	/*!<  Stat			                    	*/
	QMP6988_I2C_SET			=   0xF2,        	/*!<  Master code setting at I2C HS mode   	*/
	QMP6988_IIR_CNT			=   0xF1,        	/*!<  IIR filter co-efficient setting      	*/
	QMP6988_RESET			=   0xE0,        	/*!<  Soft reset	                    	*/
	QMP6988_CHIP_ID			=   0xD1,        	/*!<  CHIP_ID: 5D		                  	*/
	QMP6988_COE_B00_A0_EX	=   0xB8,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_A2_0		=   0xB7,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_A2_1		=   0xB6,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_A1_0		=   0xB5,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_A1_1		=   0xB4,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_A0_0		=   0xB3,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_A0_1		=   0xB2,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_BP3_0		=   0xB1,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_BP3_1		=   0xB0,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_B21_0		=   0xAF,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_B21_1		=   0xAE,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_B12_0		=   0xAD,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_B12_1		=   0xAC,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_BP2_0		=   0xAB,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_BP2_1		=   0xAA,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_B11_0		=   0xA9,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_B11_1		=   0xA8,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_BP1_0		=   0xA7,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_BP1_1		=   0xA6,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_BT2_0		=   0xA5,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_BT2_1		=   0xA4,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_BT1_0		=   0xA3,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_BT1_1		=   0xA2,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_B00_0		=   0xA1,        	/*!<  Compensation Coefficient             	*/
	QMP6988_COE_B00_1		=   0xA0        	/*!<  Compensation Coefficient             	*/
} QMP6988_register_list_t;



// IO SETUP
/**
  * @brief   T_STANDBY <7:5>. Standby time setting
  * 			NOTE: N/A
  */
typedef enum
{
	IO_SETUP_T_STANDBY_MASK				=   ( 0b111 << 5U ),	/*!<  T_STANDBY Mask                     	*/
	IO_SETUP_T_STANDBY_1MS				=   ( 0b000 << 5U ),	/*!<  T_STANDBY: 1ms          	  [Default] */
	IO_SETUP_T_STANDBY_5MS				=   ( 0b001 << 5U ),	/*!<  T_STANDBY: 5ms                    	*/
	IO_SETUP_T_STANDBY_50MS				=   ( 0b010 << 5U ),	/*!<  T_STANDBY: 50ms                    	*/
	IO_SETUP_T_STANDBY_250MS			=   ( 0b011 << 5U ),	/*!<  T_STANDBY: 250ms                    	*/
	IO_SETUP_T_STANDBY_500MS			=   ( 0b100 << 5U ),	/*!<  T_STANDBY: 500ms                    	*/
	IO_SETUP_T_STANDBY_1S				=   ( 0b101 << 5U ),	/*!<  T_STANDBY: 1s                    		*/
	IO_SETUP_T_STANDBY_2S				=   ( 0b110 << 5U ),	/*!<  T_STANDBY: 2s                    		*/
	IO_SETUP_T_STANDBY_4S				=   ( 0b111 << 5U ) 	/*!<  T_STANDBY: 4s                    		*/
} QMP6988_io_setup_t_standby_t;


/**
  * @brief   SPI3_SDIM <2>. Select output type of SDI terminal
  * 			NOTE: N/A
  */
typedef enum
{
	IO_SETUP_SPI3_SDIM_MASK				=   ( 1U << 2U ),		/*!<  SPI3_SDIM Mask                     	*/
	IO_SETUP_SPI3_SDIM_LO_HIZ_OUTPUT	=   ( 0U << 2U ),		/*!<  SPI3_SDIM: Lo/Hiz output    [Default] */
	IO_SETUP_SPI3_SDIM_LO_HI_OUTPUT		=   ( 1U << 2U )		/*!<  SPI3_SDIM: Lo/Hi output               */
} QMP6988_io_setup_spi3_sdim_t;


/**
  * @brief   SPI3W <0>. Change mode between SPI 4-wire and SPI 3-wire
  * 			NOTE: N/A
  */
typedef enum
{
	IO_SETUP_SPI3W_MASK					=   ( 1U << 0U ),		/*!<  SPI3W Mask                     		*/
	IO_SETUP_SPI3W_4_WIRE				=   ( 0U << 0U ),		/*!<  SPI3W: 4-wire			      [Default] */
	IO_SETUP_SPI3W_3_WIRE				=   ( 1U << 0U )		/*!<  SPI3W: 3-wire			                */
} QMP6988_io_setup_spi3w_t;



// CTRL_MEAS
/**
  * @brief   TEMP_AVERAGE <7:5>. Averaging times setting for Temperature measurement
  * 			NOTE: Skip means no measurement.
  */
typedef enum
{
	CTRL_MEAS_TEMP_AVERAGE_MASK			=   ( 0b111 << 5U ),	/*!<  TEMP_AVERAGE Mask                     */
	CTRL_MEAS_TEMP_AVERAGE_SKIP			=   ( 0b000 << 5U ),	/*!<  TEMP_AVERAGE: Skip          [Default] */
	CTRL_MEAS_TEMP_AVERAGE_1			=   ( 0b001 << 5U ),	/*!<  TEMP_AVERAGE:  1                    	*/
	CTRL_MEAS_TEMP_AVERAGE_2			=   ( 0b010 << 5U ),	/*!<  TEMP_AVERAGE:  2                    	*/
	CTRL_MEAS_TEMP_AVERAGE_4			=   ( 0b011 << 5U ),	/*!<  TEMP_AVERAGE:  4                    	*/
	CTRL_MEAS_TEMP_AVERAGE_8			=   ( 0b100 << 5U ),	/*!<  TEMP_AVERAGE:  8                    	*/
	CTRL_MEAS_TEMP_AVERAGE_16			=   ( 0b101 << 5U ),	/*!<  TEMP_AVERAGE: 16                    	*/
	CTRL_MEAS_TEMP_AVERAGE_32			=   ( 0b110 << 5U ),	/*!<  TEMP_AVERAGE: 32                    	*/
	CTRL_MEAS_TEMP_AVERAGE_64			=   ( 0b111 << 5U ) 	/*!<  TEMP_AVERAGE: 64                    	*/
} QMP6988_ctrl_meas_temp_average_t;


/**
  * @brief   PRESS_AVERAGE <4:2>. Averaging times setting for Pressure measurement
  * 			NOTE: Skip means no measurement.
  */
typedef enum
{
	CTRL_MEAS_PRESS_AVERAGE_MASK		=   ( 0b111 << 2U ),	/*!<  PRESS_AVERAGE Mask                    */
	CTRL_MEAS_PRESS_AVERAGE_SKIP		=   ( 0b000 << 2U ),	/*!<  PRESS_AVERAGE: Skip         [Default] */
	CTRL_MEAS_PRESS_AVERAGE_1			=   ( 0b001 << 2U ),	/*!<  PRESS_AVERAGE:  1                    	*/
	CTRL_MEAS_PRESS_AVERAGE_2			=   ( 0b010 << 2U ),	/*!<  PRESS_AVERAGE:  2                    	*/
	CTRL_MEAS_PRESS_AVERAGE_4			=   ( 0b011 << 2U ),	/*!<  PRESS_AVERAGE:  4                    	*/
	CTRL_MEAS_PRESS_AVERAGE_8			=   ( 0b100 << 2U ),	/*!<  PRESS_AVERAGE:  8                    	*/
	CTRL_MEAS_PRESS_AVERAGE_16			=   ( 0b101 << 2U ),	/*!<  PRESS_AVERAGE: 16                    	*/
	CTRL_MEAS_PRESS_AVERAGE_32			=   ( 0b110 << 2U ),	/*!<  PRESS_AVERAGE: 32                    	*/
	CTRL_MEAS_PRESS_AVERAGE_64			=   ( 0b111 << 2U ) 	/*!<  PRESS_AVERAGE: 64                    	*/
} QMP6988_ctrl_meas_press_average_t;


/**
  * @brief   POWER_MODE <1:0>. Operation mode setting
  * 			NOTE: N/A.
  */
typedef enum
{
	CTRL_MEAS_POWER_MODE_MASK			=   ( 0b11 << 0U ),		/*!<  POWER_MODE Mask                    	*/
	CTRL_MEAS_POWER_MODE_SLEEP_MODE		=   ( 0b00 << 0U ),		/*!<  POWER_MODE: Sleep mode      [Default] */
	CTRL_MEAS_POWER_MODE_FORCED_MODE	=   ( 0b01 << 0U ),		/*!<  POWER_MODE: Forced mode              	*/
	CTRL_MEAS_POWER_MODE_NORMAL_MODE	=   ( 0b11 << 0U )		/*!<  POWER_MODE: Normal mode              	*/
} QMP6988_ctrl_meas_power_mode_t;



// DEVICE_STAT
/**
  * @brief   MEASURE <3>. Device operation status
  * 			NOTE: This value automatically changes.
  */
typedef enum
{
	DEVICE_STAT_MEASURE_MASK			=   ( 1U << 3U ),		/*!<  MEASURE Mask                     									*/
	DEVICE_STAT_MEASURE_DONE			=   ( 0U << 3U ),		/*!<  Finish a measurement, waiting for next measurement	[Default] 	*/
	DEVICE_STAT_MEASURE_BUSY			=   ( 1U << 3U )		/*!<  On a measurement, waiting for finishing the data store         	*/
} QMP6988_device_stat_measure_t;


/**
  * @brief   OTP_UPDATE <0>. The status of OTP data access
  * 			NOTE: This value automatically changes.
  */
typedef enum
{
	DEVICE_STAT_OTP_UPDATE_MASK			=   ( 1U << 0U ),		/*!<  OTP_UPDATE Mask                  			*/
	DEVICE_STAT_OTP_UPDATE_DONE			=   ( 0U << 0U ),		/*!<  No accessing OTP data			[Default] 	*/
	DEVICE_STAT_OTP_UPDATE_BUSY			=   ( 1U << 0U )		/*!<  While accessing OTP data				 	*/
} QMP6988_device_otp_update_t;



// I2C_SET
/**
  * @brief   MASTER_CODE <2:0>. Master code setting at I2C high-speed mode
  * 			NOTE: N/A.
  */
typedef enum
{
	I2C_SET_MASTER_CODE_MASK			=   ( 0b111 << 0U ),	/*!<  MASTER_CODE Mask                     	*/
	I2C_SET_MASTER_CODE_H08				=   ( 0b000 << 0U ),	/*!<  MASTER_CODE: 0x08           			*/
	I2C_SET_MASTER_CODE_H09				=   ( 0b001 << 0U ),	/*!<  MASTER_CODE: 0x09           [Default] */
	I2C_SET_MASTER_CODE_H0A				=   ( 0b010 << 0U ),	/*!<  MASTER_CODE: 0x0A                    	*/
	I2C_SET_MASTER_CODE_H0B				=   ( 0b011 << 0U ),	/*!<  MASTER_CODE: 0x0B                    	*/
	I2C_SET_MASTER_CODE_H0C				=   ( 0b100 << 0U ),	/*!<  MASTER_CODE: 0x0C                    	*/
	I2C_SET_MASTER_CODE_HOD				=   ( 0b101 << 0U ),	/*!<  MASTER_CODE: 0x0D                    	*/
	I2C_SET_MASTER_CODE_HOE				=   ( 0b110 << 0U ),	/*!<  MASTER_CODE: 0x0E                    	*/
	I2C_SET_MASTER_CODE_H0F				=   ( 0b111 << 0U ) 	/*!<  MASTER_CODE: 0x0F                    	*/
} QMP6988_i2c_set_master_code_t;



// IIR
/**
  * @brief   FILTER <2:0>. IIR filter co-efficient setting
  * 			NOTE: Write access to this register address, IIR filter will be initialized.
  */
typedef enum
{
	IIR_FILTER_MASK						=   ( 0b111 << 0U ),	/*!<  FILTER Mask                     		*/
	IIR_FILTER_OFF						=   ( 0b000 << 0U ),	/*!<  FILTER: OFF           	  [Default] */
	IIR_FILTER_N_2						=   ( 0b001 << 0U ),	/*!<  FILTER: N = 2           				*/
	IIR_FILTER_N_4						=   ( 0b010 << 0U ),	/*!<  FILTER: N = 4                    		*/
	IIR_FILTER_N_8						=   ( 0b011 << 0U ),	/*!<  FILTER: N = 8                    		*/
	IIR_FILTER_N_16						=   ( 0b100 << 0U ),	/*!<  FILTER: N = 16                    	*/
	IIR_FILTER_N_32			 			=   ( 0b101 << 0U )		/*!<  FILTER: N = 32                    	*/
} QMP6988_iir_filter_t;



// RESET
/**
  * @brief   RESET <7:0>. Reset Control. When input 'E6h', the software reset will be effective
  * 			NOTE: Except for that, nothing is to happen.
  */
typedef enum
{
	RESET_RESET_COMMAND					=   ( 0xE6 << 0U )		/*!<  Reset command	                		*/
} QMP6988_reset_reset_t;



// CHIP_ID
/**
  * @brief   CHIP_ID <7:0>. Chip ID Confirmation
  * 			NOTE: N/A.
  */
typedef enum
{
	CHIP_ID_CHIP_ID						=   ( 0x5C << 0U )		/*!<  Chip ID		                		*/
} QMP6988_chip_id_chip_id_t;





#ifndef QMP6988_VECTOR_STRUCT_H
#define QMP6988_VECTOR_STRUCT_H
/* No compensated data	*/
typedef struct
{
	uint32_t	dt;											/*!<  Raw temperature data 					*/
	uint32_t	dp;											/*!<  Raw pressure data 					*/
} QMP6988_raw_measured_data_t;


/* Compensated data	*/
typedef struct
{
	float 		temperature;								/*!<  Temperature		 					*/
	float	 	pressure;									/*!<  Pressure          					*/
} QMP6988_compensated_measured_data_t;


/* Compensation coefficients (raw values)	*/
typedef struct
{
	int32_t 	raw_b00;									/*!<  Raw Compensation Coefficient: b00		*/
	int32_t 	raw_a0;										/*!<  Raw Compensation Coefficient: a0		*/
	int16_t 	raw_a2;										/*!<  Raw Compensation Coefficient: a2		*/
	int16_t 	raw_a1;										/*!<  Raw Compensation Coefficient: a1		*/
	int16_t 	raw_bp3;									/*!<  Raw Compensation Coefficient: bp3		*/
	int16_t 	raw_b21;									/*!<  Raw Compensation Coefficient: b21		*/
	int16_t 	raw_b12;									/*!<  Raw Compensation Coefficient: b12		*/
	int16_t 	raw_bp2;									/*!<  Raw Compensation Coefficient: bp2		*/
	int16_t 	raw_b11;									/*!<  Raw Compensation Coefficient: b11		*/
	int16_t 	raw_bp1;									/*!<  Raw Compensation Coefficient: bp1		*/
	int16_t 	raw_bt2;									/*!<  Raw Compensation Coefficient: bt2		*/
	int16_t 	raw_bt1;									/*!<  Raw Compensation Coefficient: bt1		*/
} QMP6988_raw_compensation_coefficients_t;


/* Compensation coefficients	*/
typedef struct
{
	int32_t		b00;										/*!<  Compensation Coefficient: b00			*/
	int32_t		a0;											/*!<  Compensation Coefficient: a0			*/
	int32_t		a2;											/*!<  Compensation Coefficient: a2			*/
	int32_t		a1;											/*!<  Compensation Coefficient: a1			*/
	uint64_t	bp3;										/*!<  Compensation Coefficient: bp3			*/
	uint64_t	b21;										/*!<  Compensation Coefficient: b21			*/
	uint64_t	b12;										/*!<  Compensation Coefficient: b12			*/
	uint64_t	bp2;										/*!<  Compensation Coefficient: bp2			*/
	uint64_t	b11;										/*!<  Compensation Coefficient: b11			*/
	uint64_t	bp1;										/*!<  Compensation Coefficient: bp1			*/
	uint64_t	bt2;										/*!<  Compensation Coefficient: bt2			*/
	uint64_t	bt1;										/*!<  Compensation Coefficient: bt1			*/
} QMP6988_compensation_coefficients_t;



/* User's variables	*/
typedef struct
{
	QMP6988_raw_measured_data_t				raw_txd;		/*!<  Non compensated data					*/
	QMP6988_compensated_measured_data_t		txd;			/*!<  Compensated data   					*/

	QMP6988_ctrl_meas_temp_average_t		temp_average;	/*!<  Temperature average times				*/
	QMP6988_ctrl_meas_press_average_t		press_average;	/*!<  Pressure average times				*/

	QMP6988_raw_compensation_coefficients_t	raw_k;			/*!<  Raw Compensation Coefficients			*/
	QMP6988_compensation_coefficients_t		k;				/*!<  Compensation Coefficients				*/

	QMP6988_iir_filter_t					filter;			/*!<  IIR filter co-efficient				*/

	uint8_t									device_stat;	/*!<  Device stat: Measure and OTP_update	*/

	QMP6988_ctrl_meas_power_mode_t			power_mode;		/*!<  Power mode setting					*/

	QMP6988_io_setup_t_standby_t			t_standby;		/*!<  Standby time setting					*/

    uint8_t  								chip_id;		/*!<  Chip ID              					*/
} QMP6988_user_data_t;
#endif





/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    QMP6988_SUCCESS     =       0,
    QMP6988_FAILURE     =       1
} QMP6988_status_t;



/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C bus.
 */
QMP6988_status_t  QMP6988_Init               				( I2C_parameters_t myI2Cparameters 													);

/** It gets the raw compensation coefficients.
 */
QMP6988_status_t  QMP6988_GetRawCompensationCoefficients	( I2C_parameters_t myI2Cparameters, QMP6988_raw_compensation_coefficients_t* myRawK	);

/** It gets the chip ID.
 */
QMP6988_status_t  QMP6988_GetChipID				          	( I2C_parameters_t myI2Cparameters, uint8_t* myChipID								);

/** It performs a software reset.
 */
QMP6988_status_t  QMP6988_SoftReset				          	( I2C_parameters_t myI2Cparameters													);

/** It sets the IIR filter co-efficient.
 */
QMP6988_status_t  QMP6988_SetIIR_Filter				        ( I2C_parameters_t myI2Cparameters, QMP6988_iir_filter_t myFilter					);

/** It gets the IIR filter co-efficient.
 */
QMP6988_status_t  QMP6988_GetIIR_Filter				        ( I2C_parameters_t myI2Cparameters, QMP6988_iir_filter_t* myFilter					);

/** It sets the master code setting at I2C HS mode.
 */
QMP6988_status_t  QMP6988_SetMasterCodeI2C			        ( I2C_parameters_t myI2Cparameters, QMP6988_i2c_set_master_code_t myMasterCode		);

/** It gets the master code setting at I2C HS mode.
 */
QMP6988_status_t  QMP6988_GetMasterCodeI2C			        ( I2C_parameters_t myI2Cparameters, QMP6988_i2c_set_master_code_t* myMasterCode		);

/** It gets the device stat.
 */
QMP6988_status_t  QMP6988_GetDeviceStat			        	( I2C_parameters_t myI2Cparameters, uint8_t* myDeviceStat							);

/** It sets the power mode.
 */
QMP6988_status_t  QMP6988_SetPowerMode			        	( I2C_parameters_t myI2Cparameters, QMP6988_ctrl_meas_power_mode_t myPowerMode		);

/** It gets the power mode.
 */
QMP6988_status_t  QMP6988_GetPowerMode			        	( I2C_parameters_t myI2Cparameters, QMP6988_ctrl_meas_power_mode_t* myPowerMode		);

/** It sets the temperature averaging time.
 */
QMP6988_status_t  QMP6988_SetTemperatureAverage	        	( I2C_parameters_t myI2Cparameters, QMP6988_ctrl_meas_temp_average_t myTempAvrg		);

/** It gets the temperature averaging time.
 */
QMP6988_status_t  QMP6988_GetTemperatureAverage			    ( I2C_parameters_t myI2Cparameters, QMP6988_ctrl_meas_temp_average_t* myTempAvrg	);

/** It sets the pressure averaging time.
 */
QMP6988_status_t  QMP6988_SetPressureAverage	        	( I2C_parameters_t myI2Cparameters, QMP6988_ctrl_meas_press_average_t myPressAvrg	);

/** It gets the pressure averaging time.
 */
QMP6988_status_t  QMP6988_GetPressureAverage			    ( I2C_parameters_t myI2Cparameters, QMP6988_ctrl_meas_press_average_t* myPressAvrg	);

/** It sets the standby time setting.
 */
QMP6988_status_t  QMP6988_SetStandbyTimeSetting	        	( I2C_parameters_t myI2Cparameters, QMP6988_io_setup_t_standby_t myStandbyTime		);

/** It gets the standby time setting.
 */
QMP6988_status_t  QMP6988_GetStandbyTimeSetting			    ( I2C_parameters_t myI2Cparameters, QMP6988_io_setup_t_standby_t* myStandbyTime		);

/** It sets the SPI mode setting (4 or 3 wire).
 */
QMP6988_status_t  QMP6988_SetSPI_ModeSetting	        	( I2C_parameters_t myI2Cparameters, QMP6988_io_setup_spi3w_t mySPI					);

/** It gets the SPI mode setting (4 or 3 wire).
 */
QMP6988_status_t  QMP6988_GetSPI_ModeSetting			    ( I2C_parameters_t myI2Cparameters, QMP6988_io_setup_spi3w_t* mySPI					);

/** It sets the selected output type of SDI terminal.
 */
QMP6988_status_t  QMP6988_SetSDI_Output			        	( I2C_parameters_t myI2Cparameters, QMP6988_io_setup_spi3_sdim_t mySDI				);

/** It gets the selected output type of SDI terminal.
 */
QMP6988_status_t  QMP6988_GetSDI_Output					    ( I2C_parameters_t myI2Cparameters, QMP6988_io_setup_spi3_sdim_t* mySDI				);

/** It gets the raw temperature data and raw pressure data.
 */
QMP6988_status_t  QMP6988_GetRawMeasurements			    ( I2C_parameters_t myI2Cparameters, QMP6988_raw_measured_data_t* myData				);

/** It calculates the compensation coefficients.
 */
QMP6988_compensation_coefficients_t	QMP6988_CalculateCompensationCoefficients	( QMP6988_raw_compensation_coefficients_t myRawK				);

/** It calculates the compensated temperature value.
 */
QMP6988_compensated_measured_data_t	QMP6988_CalculateCompensatedMeasuredData	( QMP6988_raw_measured_data_t myData, QMP6988_compensation_coefficients_t myK );

/** It calculates the conversion factor. K = A + ( S * OTP ) / 32767.
 */
float QMP6988_CalculateK	( float a, float s, uint16_t otp );

/** It calculates the conversion factor. K = OTP / 16.
 */
float QMP6988_CalculateK0	( uint32_t otp );



#ifdef __cplusplus
}
#endif

#endif /* QMP6988_H */
