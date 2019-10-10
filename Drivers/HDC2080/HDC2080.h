/**
 * @brief       HDC2080.h
 * @details     Low-Power Humidity and Temperature Digital Sensor.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/October/2019
 * @version     10/October/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( https://www.nimbus.cit.ie ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESS
  */
typedef enum
{
  HDC2080_ADDRESS     =   0b1011101          /*!<   I2C slave address byte                       */
} HDC2080_address_t;



/**
  * @brief   REGISTERS
  */
typedef enum
{
  HDC2080_ID1        	 =   0x0F,           /*!<  Device ID1			                         */
  HDC2080_ID2         	 =   0x10,           /*!<  Device ID2								     */
  HDC2080_POWER_DOWN      =   0x12,           /*!<  Power down register                           */
  HDC2080_RESET	         =   0x13,           /*!<  Reset register	                             */
  HDC2080_MODE_CONTROL    =   0x14,           /*!<  Mode control register                         */
  HDC2080_STATUS		     =   0x19,           /*!<  Status register                               */
  HDC2080_PRESSURE_MSB    =   0x1A,           /*!<  Pressure data (MSB)  		                 */
  HDC2080_PRESSURE_LSB    =   0x1B,           /*!<  Pressure data (LSB)  		                 */
  HDC2080_PRESSURE_XLSB   =   0x1C,           /*!<  Pressure data (XLSB)  		                 */
  HDC2080_TEMPERATURE_MSB =   0x1D,           /*!<  Temperature data (MSB)                        */
  HDC2080_TEMPERATURE_LSB =   0x1E            /*!<  Temperature data (LSB)                        */
} HDC2080_registers_t;



/**
  * @brief   ID REGISTERS
  */
typedef enum
{
    ID_ID1           	=   0xE0,             			/*!<  ID1 value	                                */
    ID_ID2          	=   0x32              			/*!<  ID2 value	                                */
} HDC2080_id_t;



/**
  * @brief   POWER_DOWN REGISTER
  */
/* PWR_DOWN <0>
 *    NOTE: Power down or active mode.
 */
typedef enum
{
	POWER_DOWN_PWR_DOWN_MASK       	=   ( 1U << 0U ),    /*!<  POWER_DOWN mask                          		*/
	POWER_DOWN_PWR_DOWN_POWER_DOWN	=   ( 0U << 0U ),    /*!<  Power down				    		[ Default ] */
	POWER_DOWN_PWR_DOWN_ACTIVE      =   ( 1U << 0U )     /*!<  Active					                		*/
} HDC2080_power_down_pwr_down_t;


/**
  * @brief   RESET REGISTER
  */
/* RSTB <0>
 *    NOTE: N/A.
 */
typedef enum
{
	RESET_RSTB_MASK       			=   ( 1U << 0U ),    /*!<  RSTB mask                          		       	*/
	RESET_RSTB_RESET          		=   ( 0U << 0U ),    /*!<  Measurement control block is reset  	[ Default ] */
	RESET_RSTB_ACTIVE          		=   ( 1U << 0U )     /*!<  Measurement control block is active  		   	*/
} HDC2080_reset_rstb_t;



/**
  * @brief   MODE_CONTROL REGISTER
  */
/* AVE_NUM <7:5>
 *    NOTE: Set the average number of measurement data.
 */
typedef enum
{
	MODE_CONTROL_AVE_NUM_MASK     	=   ( 0b111 << 5U ), /*!<  AVE_NUM mask                                     */
	MODE_CONTROL_AVE_NUM_SINGLE     =   ( 0b000 << 5U ), /*!<  AVE_NUM: Single                                  */
	MODE_CONTROL_AVE_NUM_AVERAGE_2  =   ( 0b001 << 5U ), /*!<  AVE_NUM: Average of  2 times         [ Default ] */
	MODE_CONTROL_AVE_NUM_AVERAGE_4  =   ( 0b010 << 5U ), /*!<  AVE_NUM: Average of  4 times                     */
	MODE_CONTROL_AVE_NUM_AVERAGE_8  =   ( 0b011 << 5U ), /*!<  AVE_NUM: Average of  8 times                     */
	MODE_CONTROL_AVE_NUM_AVERAGE_16 =   ( 0b100 << 5U ), /*!<  AVE_NUM: Average of 16 times                     */
	MODE_CONTROL_AVE_NUM_AVERAGE_32 =   ( 0b101 << 5U ), /*!<  AVE_NUM: Average of 32 times                     */
	MODE_CONTROL_AVE_NUM_AVERAGE_64 =   ( 0b110 << 5U )  /*!<  AVE_NUM: Average of 64 times                     */
} HDC2080_mode_control_ave_num_t;


/* DREN <4>
 *    NOTE: DRDY pin Enable.
 */
typedef enum
{
	MODE_CONTROL_DREN_MASK     		=   ( 1U << 4U ), 	/*!<  DREN mask                             	        */
	MODE_CONTROL_DREN_DRDY_DISABLE	=   ( 0U << 4U ), 	/*!<  DRDY pin Disable                     	[ Default ] */
	MODE_CONTROL_DREN_DRDY_ENABLE 	=   ( 1U << 4U )  	/*!<  DRDY pin Enable                     				*/
} HDC2080_mode_control_dren_t;


/* MODE <1:0>
 *    NOTE: Set measurement mode.
 */
typedef enum
{
	MODE_CONTROL_MODE_MASK     		=   ( 0b11 << 0U ), /*!<  MODE mask                                        */
	MODE_CONTROL_MODE_STAND_BY      =   ( 0b00 << 0U ), /*!<  Stand by                             [ Default ] */
	MODE_CONTROL_MODE_ONE_SHOT		=   ( 0b01 << 0U ), /*!<  One shot                    					   */
	MODE_CONTROL_MODE_CONTINUOUS    =   ( 0b10 << 0U )  /*!<  Continuous				                       */
} HDC2080_mode_control_mode_t;


/**
  * @brief   STATUS REGISTER
  */
/* RD_DRDY <0>
 *    NOTE: Pressure and temperature measurement data ready bit.
 */
typedef enum
{
	STATUS_RD_DRDY_MASK       		=   ( 1U << 0U ),    /*!<  RD_DRDY mask                      		       						*/
	STATUS_RD_DRDY_DATA_MEASURING   =   ( 0U << 0U ),    /*!<  Measurement data output is not yet available (measuring)	[ Default ] */
	STATUS_RD_DRDY_DATA_AVAILABLE	=   ( 1U << 0U )     /*!<  Measurement data output is available								   	*/
} HDC2080_reset_rd_drdy_t;





#ifndef HDC2080_VECTOR_STRUCT_H
#define HDC2080_VECTOR_STRUCT_H
typedef struct
{
    /* Output registers  */
    int32_t rawPressure;     						/*!<  Raw pressure                  */
    int16_t	rawTemperature;  						/*!<  Raw temperature               */

    float   pressure;        						/*!<  Pressure value                */
    float   temperature;     						/*!<  Temperature value             */

    /* Mode control	 */
    HDC2080_mode_control_ave_num_t ave_num;		/*!<  Average number of measurement */
    HDC2080_mode_control_dren_t	  dren;			/*!<  DRDY pin Enable	            */
    HDC2080_mode_control_mode_t	  mode;			/*!<  Set measurement mode	        */

    /* Device status	 */
    HDC2080_power_down_pwr_down_t pwr_down;		/*!<  Power mode		            */
    HDC2080_reset_rstb_t			 rstb;			/*!<  Reset				            */
    HDC2080_reset_rd_drdy_t		 rd_drdy;		/*!<  Status flag		            */

    /* Device identification   */
    uint8_t id1;        							/*!<  Device ID1                    */
    uint8_t id2;        							/*!<  Device ID2                    */
} HDC2080_data_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    HDC2080_SUCCESS     =       0,
    HDC2080_FAILURE     =       1
} HDC2080_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
HDC2080_status_t HDC2080_Init               ( I2C_parameters_t myI2Cparameters                                );

/** It gets the device identifications.
  */
HDC2080_status_t HDC2080_GetDeviceID        ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myDeviceID	);

/** It sets the power-down mode.
  */
HDC2080_status_t HDC2080_SetPowerDown       ( I2C_parameters_t myI2Cparameters, HDC2080_data_t myPwrDown	);

/** It gets the power-down mode.
  */
HDC2080_status_t HDC2080_GetPowerDown       ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myPwrDown	);

/** It sets the soft-reset.
  */
HDC2080_status_t HDC2080_SetSoftReset       ( I2C_parameters_t myI2Cparameters, HDC2080_data_t myRSTB		);

/** It gets the reset flag.
  */
HDC2080_status_t HDC2080_GetSoftResetFlag   ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myRSTB		);

/** It sets the mode control.
  */
HDC2080_status_t HDC2080_SetModeControl     ( I2C_parameters_t myI2Cparameters, HDC2080_data_t myModeCont	);

/** It gets the mode control.
  */
HDC2080_status_t HDC2080_GetModeControl	  ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myModeCont	);

/** It gets the status flag.
  */
HDC2080_status_t HDC2080_GetStatus		  ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myRD_DRDY	);

/** It gets the raw pressure.
  */
HDC2080_status_t HDC2080_GetRawPressure     ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myRawP		);

/** It gets the raw temperature.
  */
HDC2080_status_t HDC2080_GetRawTemperature  ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myRawT		);

/** It gets the pressure.
  */
HDC2080_status_t HDC2080_GetPressure     	  ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myP		);

/** It gets the temperature.
  */
HDC2080_status_t HDC2080_GetTemperature  	  ( I2C_parameters_t myI2Cparameters, HDC2080_data_t* myT		);
