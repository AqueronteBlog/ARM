/**
 * @brief       ezPyro_SMD_Sensor.h
 * @details     [TODO] ezPyro SMD I2C Pyroelectric Infrared Sensor. Single element or 2x2 array.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        13/October/2020
 * @version     13/October/2020    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"

#ifndef EZPYRO_SMD_SENSOR_H_
#define EZPYRO_SMD_SENSOR_H_

#ifdef __cplusplus
extern "C" {
#endif


/**
  * @brief   DEFAULT ADDRESSES
  */
typedef enum
{
	EZPYRO_SMD_SENSOR_DEFAULT_ADDRESS =   0b1100101	       /*!<   ADDR: Default			                         	*/
} EZPYRO_SMD_SENSOR_addresses_t;


/**
  * @brief   REGISTER MAPPING
  */
typedef enum
{
    EZPYRO_SMD_SENSOR_TEST		       =   0x00,           /*!<  Verify communication by reading the response packet		*/
    EZPYRO_SMD_SENSOR_VERSION	       =   0x02,           /*!<  Version Packet					    						*/
    EZPYRO_SMD_SENSOR_FIFO_STATUS      =   0x04,           /*!<  FIFO Status Packet				    						*/
    EZPYRO_SMD_SENSOR_FIFO_READ_FULL   =   0x06,           /*!<  Read full data packet (17 bytes) of all channels			*/
    EZPYRO_SMD_SENSOR_FIFO_READ_ACTIVE =   0x08,           /*!<  Read data packet (up to 17 bytes) for only active channel	*/
    EZPYRO_SMD_SENSOR_FIFO_CLEAR       =   0x0A,           /*!<  Clear the current Packet (Read pointer moves on next)		*/
    EZPYRO_SMD_SENSOR_FIFO_RESET       =   0x0C,           /*!<  Clear the entire FIFO (Rd/Wr pointer reset with the Empty)	*/
    EZPYRO_SMD_SENSOR_CH_READ	       =   0x0E,           /*!<  Channel Control Packet										*/
    EZPYRO_SMD_SENSOR_CH_WRITE         =   0x10,           /*!<  Channel Control Packet			        					*/
    EZPYRO_SMD_SENSOR_ANA_READ         =   0x12,           /*!<  Analogue Settings											*/
    EZPYRO_SMD_SENSOR_ANA_WRITE        =   0x14,           /*!<  Analogue Settings											*/
    EZPYRO_SMD_SENSOR_WAKE_READ        =   0x16,           /*!<  Wake-up Packet												*/
    EZPYRO_SMD_SENSOR_WAKE_WRITE       =   0x18,           /*!<  Wake-up Packet												*/
    EZPYRO_SMD_SENSOR_ADDR_WRITE       =   0x1E,           /*!<  I2C Address												*/
    EZPYRO_SMD_SENSOR_GO_TO_SLEEP      =   0x20,           /*!<  Put the device in Sleep Mode								*/
    EZPYRO_SMD_SENSOR_WAKE_UP	       =   0x22,           /*!<  Wake up and resume normal mode								*/
    EZPYRO_SMD_SENSOR_RESET_SOFT       =   0x24,           /*!<  Soft reset													*/
	EZPYRO_SMD_SENSOR_RESET_FULL       =   0x26            /*!<  Full reset													*/
} EZPYRO_SMD_SENSOR_register_list_t;



/* Commands data replay */
typedef enum
{
    CMD_DATA_TEST_OK          =   0b00000001,				/*!<  Command replay TEST Data OK                      			*/
	CMD_DATA_TEST_ERR         =   0b00000010,				/*!<  Command replay TEST Data ERROR                   			*/

	CMD_DATA_FIFO_CLEAR_OK    =   0b00101001,				/*!<  Command replay FIFO_CLEAR Data OK                			*/
	CMD_DATA_FIFO_CLEAR_ERR   =   0b00101010,				/*!<  Command replay FIFO_CLEAR Data ERROR             			*/

	CMD_DATA_FIFO_RESET_OK    =   0b00110001,				/*!<  Command replay FIFO_RESET Data OK                			*/
	CMD_DATA_FIFO_RESET_ERR   =   0b00110010,				/*!<  Command replay FIFO_RESET Data ERROR             			*/

	CMD_DATA_GO_TO_SLEEP_OK   =   0b10000001,				/*!<  Command replay GO_TO_SLEEP Data OK              			*/
	CMD_DATA_GO_TO_SLEEP_ERR  =   0b10000010,				/*!<  Command replay GO_TO_SLEEP Data ERROR            			*/

	CMD_DATA_WAKE_UP_OK   	  =   0b10001001,				/*!<  Command replay WAKE_UP Data OK              				*/
	CMD_DATA_WAKE_UP_ERR      =   0b10001010,				/*!<  Command replay WAKE_UP Data ERROR            				*/

	CMD_DATA_RESET_SOFT_OK    =   0b10010001,				/*!<  Command replay RESET_SOFT Data OK             			*/
	CMD_DATA_RESET_SOFT_ERR   =   0b10010010,				/*!<  Command replay RESET_SOFT Data ERROR          			*/

	CMD_DATA_RESET_FULL_OK    =   0b10011001,				/*!<  Command replay RESET_FULL Data OK             			*/
	CMD_DATA_RESET_FULL_ERR   =   0b10011010				/*!<  Command replay RESET_FULL Data ERROR          			*/
} EZPYRO_SMD_SENSOR_commands_data_ok_err_t;



/* Register: CTRL_REG1	*/
/**
  * @brief   NORM_MOD_EN <7>. Normal mode enable
  *
  *          NOTE: N/A
  */
typedef enum
{
	CTRL_REG1_NORM_MOD_EN_MASK			=   ( 1U << 7U ),     /*!<  NORM_MOD_EN mask                             */
	CTRL_REG1_NORM_MOD_EN_POWER_DOWN	=   ( 0U << 7U ),     /*!<  Power down            		   	   [Default] */
	CTRL_REG1_NORM_MOD_EN_ENABLED       =   ( 1U << 7U )      /*!<  Enabled					                     */
} EZPYRO_SMD_SENSOR_ctrl_reg1_norm_mod_en_t;


/**
  * @brief   IF_ADD_INC <6>. Register address automatically incremented during a multiple byte access with SPI serial interface
  *
  *          NOTE: N/A
  */
typedef enum
{
	CTRL_REG1_IF_ADD_INC_MASK			=   ( 1U << 6U ),     /*!<  IF_ADD_INC mask                              */
	CTRL_REG1_IF_ADD_INC_DISABLED		=   ( 0U << 6U ),     /*!<  Power down            		   	   			 */
	CTRL_REG1_IF_ADD_INC_ENABLED       	=   ( 1U << 6U )      /*!<  Enabled					           [Default] */
} EZPYRO_SMD_SENSOR_ctrl_reg1_if_add_inc_t;


/**
  * @brief   BOOT <3>. Reboot memory content
  *
  *          NOTE: Boot request is executed as soon as the internal oscillator is turned on. It is possible to set the bit while in
  *				   power-down mode, in this case it will be served at the next normal mode.
  */
typedef enum
{
	CTRL_REG1_BOOT_MASK						=   ( 1U << 3U ), /*!<  BOOT mask                              		 */
	CTRL_REG1_BOOT_NORMAL_MODE				=   ( 0U << 3U ), /*!<  Normal mode            		   	   [Default] */
	CTRL_REG1_BOOT_REBOOT_MEMORY_CONTENT	=   ( 1U << 3U )  /*!<  Reboot memory content	           			 */
} EZPYRO_SMD_SENSOR_ctrl_reg1_boot_t;


/**
  * @brief   SW_RESET <2>. Software reset
  *
  *          NOTE: With SW_RESET the values in the writable CTRL registers are changed to the default values.
  *          	   This bit is cleared by hardware at the end of the operation.
  */
typedef enum
{
	CTRL_REG1_SW_RESET_MASK				=   ( 1U << 2U ),     /*!<  SW_RESET mask                                */
	CTRL_REG1_SW_RESET_NORMAL_MODE		=   ( 0U << 2U ),     /*!<  Normal operation            	   [Default] */
	CTRL_REG1_SW_RESET_RESET_DEVICE    	=   ( 1U << 2U )      /*!<  Reset device					             */
} EZPYRO_SMD_SENSOR_ctrl_reg1_sw_reset_t;


/**
  * @brief   DRDY_PULSE <1>. Data ready on INT1 pin
  *
  *          NOTE: N/A.
  */
typedef enum
{
	CTRL_REG1_DRDY_PULSE_MASK			=   ( 1U << 1U ),     /*!<  DRDY_PULSE mask                              */
	CTRL_REG1_DRDY_PULSE_DRDY_LATCHED	=   ( 0U << 1U ),     /*!<  DRDY latched			       	   [Default] */
	CTRL_REG1_DRDY_PULSE_DRDY_PULSED    =   ( 1U << 1U )      /*!<  DRDY pulsed, pulse duration is 1/4 ODR	     */
} EZPYRO_SMD_SENSOR_ctrl_reg1_drdy_pulse_t;


/**
  * @brief   BDU <0>. Block Data Update
  *
  *          NOTE: N/A.
  */
typedef enum
{
	CTRL_REG1_BDU_MASK						=   ( 1U << 0U ),  /*!<  BDU mask  		                             			*/
	CTRL_REG1_BDU_CONTINUOUS_UPDATE			=   ( 0U << 0U ),  /*!<  Continuous update	       	   	   			  [Default] */
	CTRL_REG1_BDU_UPDATE_UNTIL_MSB_LSB_READ	=   ( 1U << 0U )   /*!<  Output registers not updated until MSB and LSB read	*/
} EZPYRO_SMD_SENSOR_ctrl_reg1_bdu_t;



/* Register: INT1_CTRL */
/**
  * @brief   INT1_DRDY <7>. Accelerometer data ready on INT1 pin
  *
  *          NOTE: N/A
  */
typedef enum
{
	INT1_CTRL_INT1_DRDY_MASK          =   ( 1U << 7U ),			/*!<  INT1_DRDY mask                  			*/
	INT1_CTRL_INT1_DRDY_DISABLED      =   ( 0U << 7U ),  		/*!<  Disabled    	   	   			  [Default] */
	INT1_CTRL_INT1_DRDY_ENABLED	      =   ( 1U << 7U )   		/*!<  Enabled									*/
} EZPYRO_SMD_SENSOR_int1_ctrl_int1_drdy_t;


/**
  * @brief   INT1_BOOT <6>. Accelerometer data ready on INT1 pin
  *
  *          NOTE: N/A
  */
typedef enum
{
	INT1_CTRL_INT1_BOOT_MASK          =   ( 1U << 6U ),			/*!<  INT1_BOOT mask                   			*/
	INT1_CTRL_INT1_BOOT_DISABLED      =   ( 0U << 6U ),  		/*!<  Disabled    	   	   			  [Default] */
	INT1_CTRL_INT1_BOOT_ENABLED	      =   ( 1U << 6U )   		/*!<  Enabled									*/
} EZPYRO_SMD_SENSOR_int1_ctrl_int1_boot_t;


/**
  * @brief   INT1_OVR <5>. Overrun flag on INT1 pin
  *
  *          NOTE: N/A
  */
typedef enum
{
	INT1_CTRL_INT1_OVR_MASK           =   ( 1U << 5U ),			/*!<  INT1_OVR mask                   			*/
	INT1_CTRL_INT1_OVR_DISABLED       =   ( 0U << 5U ),  		/*!<  Disabled    	   	   			  [Default] */
	INT1_CTRL_INT1_OVR_ENABLED	      =   ( 1U << 5U )   		/*!<  Enabled									*/
} EZPYRO_SMD_SENSOR_int1_ctrl_int1_ovr_t;


/**
  * @brief   INT1_FSS5 <4>. FSS5 full FIFO flag on INT1 pin
  *
  *          NOTE: N/A
  */
typedef enum
{
	INT1_CTRL_INT1_FSS5_MASK          =   ( 1U << 4U ),			/*!<  INT1_FSS5 mask                   			*/
	INT1_CTRL_INT1_FSS5_DISABLED      =   ( 0U << 4U ),  		/*!<  Disabled    	   	   			  [Default] */
	INT1_CTRL_INT1_FSS5_ENABLED	      =   ( 1U << 4U )   		/*!<  Enabled									*/
} EZPYRO_SMD_SENSOR_int1_ctrl_int1_fss5_t;


/**
  * @brief   INT1_FTH <3>. FIFO threshold flag on INT1 pin
  *
  *          NOTE: N/A
  */
typedef enum
{
	INT1_CTRL_INT1_FTH_MASK           =   ( 1U << 3U ),			/*!<  INT1_FTH mask                   			*/
	INT1_CTRL_INT1_FTH_DISABLED       =   ( 0U << 3U ),  		/*!<  Disabled    	   	   			  [Default] */
	INT1_CTRL_INT1_FTH_ENABLED	      =   ( 1U << 3U )   		/*!<  Enabled									*/
} EZPYRO_SMD_SENSOR_int1_ctrl_int1_fth_t;


/**
  * @brief   INT1_EXT <2>. INT1 pin configuration
  *
  *          NOTE: It configures the INT1 pad as output for FIFO flags or as external asynchronous input trigger to FIFO.
  *				   INT2 pad is always available as output for FIFO flags
  */
typedef enum
{
	INT1_CTRL_INT1_EXT_MASK           			=   ( 1U << 2U ),	/*!<  INT1_EXT mask                   			*/
	INT1_CTRL_INT1_EXT_INT1_AS_OUTPUT_INTERRUPT	=   ( 0U << 2U ),  	/*!<  INT1 as output interrupt		  [Default] */
	INT1_CTRL_INT1_EXT_INT1_AS_INPUT_CHANNEL	=   ( 1U << 2U )   	/*!<  INT1 as input channel						*/
} EZPYRO_SMD_SENSOR_int1_ctrl_int1_ext_t;



/* Register: INT2_CTRL */
/**
  * @brief   INT2_DRDY <7>. Accelerometer data ready on INT2 pin
  *
  *          NOTE: N/A
  */
typedef enum
{
	INT2_CTRL_INT2_DRDY_MASK          =   ( 1U << 7U ),			/*!<  INT2_DRDY mask                  			*/
	INT2_CTRL_INT2_DRDY_DISABLED      =   ( 0U << 7U ),  		/*!<  Disabled    	   	   			  [Default] */
	INT2_CTRL_INT2_DRDY_ENABLED	      =   ( 1U << 7U )   		/*!<  Enabled									*/
} EZPYRO_SMD_SENSOR_int2_ctrl_int2_drdy_t;


/**
  * @brief   INT2_BOOT <6>. Accelerometer data ready on INT2 pin
  *
  *          NOTE: N/A
  */
typedef enum
{
	INT2_CTRL_INT2_BOOT_MASK          =   ( 1U << 6U ),			/*!<  INT2_BOOT mask                   			*/
	INT2_CTRL_INT2_BOOT_DISABLED      =   ( 0U << 6U ),  		/*!<  Disabled    	   	   			  [Default] */
	INT2_CTRL_INT2_BOOT_ENABLED	      =   ( 1U << 6U )   		/*!<  Enabled									*/
} EZPYRO_SMD_SENSOR_int2_ctrl_int2_boot_t;


/**
  * @brief   INT2_OVR <5>. Overrun flag on INT2 pin
  *
  *          NOTE: N/A
  */
typedef enum
{
	INT2_CTRL_INT2_OVR_MASK           =   ( 1U << 5U ),			/*!<  INT2_OVR mask                   			*/
	INT2_CTRL_INT2_OVR_DISABLED       =   ( 0U << 5U ),  		/*!<  Disabled    	   	   			  [Default] */
	INT2_CTRL_INT2_OVR_ENABLED	      =   ( 1U << 5U )   		/*!<  Enabled									*/
} EZPYRO_SMD_SENSOR_int2_ctrl_int2_ovr_t;


/**
  * @brief   INT2_FSS5 <4>. FSS5 full FIFO flag on INT2 pin
  *
  *          NOTE: N/A
  */
typedef enum
{
	INT2_CTRL_INT2_FSS5_MASK          =   ( 1U << 4U ),			/*!<  INT2_FSS5 mask                   			*/
	INT2_CTRL_INT2_FSS5_DISABLED      =   ( 0U << 4U ),  		/*!<  Disabled    	   	   			  [Default] */
	INT2_CTRL_INT2_FSS5_ENABLED	      =   ( 1U << 4U )   		/*!<  Enabled									*/
} EZPYRO_SMD_SENSOR_int2_ctrl_int2_fss5_t;


/**
  * @brief   INT2_FTH <3>. FIFO threshold flag on INT2 pin
  *
  *          NOTE: N/A
  */
typedef enum
{
	INT2_CTRL_INT2_FTH_MASK           =   ( 1U << 3U ),			/*!<  INT2_FTH mask                   			*/
	INT2_CTRL_INT2_FTH_DISABLED       =   ( 0U << 3U ),  		/*!<  Disabled    	   	   			  [Default] */
	INT2_CTRL_INT2_FTH_ENABLED	      =   ( 1U << 3U )   		/*!<  Enabled									*/
} EZPYRO_SMD_SENSOR_int2_ctrl_int2_fth_t;



/* Register: CTRL_REG4	*/
/**
  * @brief   DSP_LP_TYPE <7>. Digital filtering selection
  *
  *          NOTE: N/A
  */
typedef enum
{
	CTRL_REG4_DSP_LP_TYPE_MASK					=   ( 1U << 7U ),	/*!<  DSP_LP_TYPE mask                             */
	CTRL_REG4_DSP_LP_TYPE_FIR_LINEAR_PHASE		=   ( 0U << 7U ),   /*!<  FIR Linear Phase			    	 [Default] */
	CTRL_REG4_DSP_LP_TYPE_IIR_NONLINEAR_PHASE	=   ( 1U << 7U )    /*!<  IIR Nonlinear Phase   	                   */
} EZPYRO_SMD_SENSOR_ctr_reg4_dsp_lp_type_t;


/**
  * @brief   DSP_BW_SEL <6>. User-selectable bandwidth
  *
  *          NOTE: N/A
  */
typedef enum
{
	CTRL_REG4_DSP_BW_SEL_MASK			=   ( 1U << 6U ),	/*!<  DSP_BW_SEL mask                              */
	CTRL_REG4_DSP_BW_SEL_440_HZ_TYP		=   ( 0U << 6U ),   /*!<  440 Hz typ				    	 [Default] */
	CTRL_REG4_DSP_BW_SEL_235_HZ_TYP		=   ( 1U << 6U )    /*!<  235 Hz typ				                   */
} EZPYRO_SMD_SENSOR_ctr_reg4_dsp_bw_sel_t;


/**
  * @brief   ST <5:4>. Self-test enable
  *
  *          NOTE: N/A
  */
typedef enum
{
	CTRL_REG4_ST_MASK					=   ( 0b11 << 4U ),	/*!<  ST mask		                               */
	CTRL_REG4_ST_NORMAL_MODE			=   ( 0b00 << 4U ), /*!<  Normal mode ( Self-test disabled ) [Default] */
	CTRL_REG4_ST_POSITIVE_SIGN_SELFTEST	=   ( 0b01 << 4U ), /*!<  Positive sign self-test				       */
	CTRL_REG4_ST_NEGATIVE_SIGN_SELFTEST	=   ( 0b10 << 4U )  /*!<  Negative sign self-test				       */
} EZPYRO_SMD_SENSOR_ctr_reg4_st_t;


/**
  * @brief   PP_OD_INT2 <3>. Push-pull/open drain selection on INT2 pin
  *
  *          NOTE: N/A
  */
typedef enum
{
	CTRL_REG4_PP_OD_INT2_MASK				=   ( 1U << 3U ),	/*!<  PP_OD_INT2 mask                              */
	CTRL_REG4_PP_OD_INT2_PUSH_PULL_MODE		=   ( 0U << 3U ),   /*!<  push-pull mode			    	 [Default] */
	CTRL_REG4_PP_OD_INT2_OPEM_DRAIN_MODE	=   ( 1U << 3U )    /*!<  open drain mode			                   */
} EZPYRO_SMD_SENSOR_ctr_reg4_pp_od_int2_t;


/**
  * @brief   PP_OD_INT1 <2>. Push-pull/open drain selection on INT1 pin
  *
  *          NOTE: N/A
  */
typedef enum
{
	CTRL_REG4_PP_OD_INT1_MASK				=   ( 1U << 2U ),	/*!<  PP_OD_INT1 mask                              */
	CTRL_REG4_PP_OD_INT1_PUSH_PULL_MODE		=   ( 0U << 2U ),   /*!<  push-pull mode			    	 [Default] */
	CTRL_REG4_PP_OD_INT1_OPEM_DRAIN_MODE	=   ( 1U << 2U )    /*!<  open drain mode			                   */
} EZPYRO_SMD_SENSOR_ctr_reg4_pp_od_int1_t;


/**
  * @brief   FIFO_EN <1>. FIFO memory enable
  *
  *          NOTE: N/A
  */
typedef enum
{
	CTRL_REG4_FIFO_EN_MASK			=   ( 1U << 1U ),	/*!<  FIFO_EN mask                                 */
	CTRL_REG4_FIFO_EN_DISABLED		=   ( 0U << 1U ),   /*!<  Disabled					    	 [Default] */
	CTRL_REG4_FIFO_EN_ENABLED		=   ( 1U << 1U )    /*!<  Enabled					                   */
} EZPYRO_SMD_SENSOR_ctr_reg4_fifo_en_t;



/* Register: CTRL_REG5	*/
/**
  * @brief   FIFO_SPI_HS_ON <0>. Enables the SPI high speed configuration for the FIFO block that is used to guarantee a minimum duration of the
  * 							 window in which writing operation of RAM output is blocked. This bit is recommended for SPI clock frequencies
  *								 higher than 6 MHz.
  *
  *          NOTE: N/A
  */
typedef enum
{
	CTRL_REG5_FIFO_SPI_HS_ON_MASK		=   ( 1U << 0U ),	/*!<  FIFO_SPI_HS_ON mask                          */
	CTRL_REG5_FIFO_SPI_HS_ON_DISABLED	=   ( 0U << 0U ),   /*!<  Disabled					    	 [Default] */
	CTRL_REG5_FIFO_SPI_HS_ON_ENABLED	=   ( 1U << 0U )    /*!<  Enabled				  	                   */
} EZPYRO_SMD_SENSOR_ctr_reg5_fifo_spi_hs_on_t;



/* Register: OUT_TEMP	*/
/**
  * @brief   OUT_TEMP_L <7:4>. Temperature data output LSB.
  *
  *          NOTE: N/A
  */
typedef enum
{
	OUT_TEMP_L_MASK			=   0b11110000    /*!<  OUT_TEMP_L mask	  	                   */
} EZPYRO_SMD_SENSOR_out_temp_l_t;






#ifndef EZPYRO_SMD_SENSOR_VECTOR_STRUCT_H
#define EZPYRO_SMD_SENSOR_VECTOR_STRUCT_H
/* EZPYRO_SMD_SENSOR DATA */
typedef struct
{
    int8_t      f_wake;                  /*!<  False wakeup register                */
    uint8_t     patt2b;                  /*!<  Wakeup pattern PATT2B ( Manchester ) */
    uint8_t     patt1b;                  /*!<  Wakeup pattern PATT1B ( Manchester ) */
    uint8_t     rssi1;                   /*!<  RSSI1 Channel 1                      */
    uint8_t     rssi2;                   /*!<  RSSI2 Channel 2                      */
    uint8_t     rssi3;                   /*!<  RSSI3 Channel 3                      */

    uint32_t    data;                    /*!<  Data                                 */
} EZPYRO_SMD_SENSOR_data_t;
#endif



/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    EZPYRO_SMD_SENSOR_SUCCESS     =       0,
    EZPYRO_SMD_SENSOR_FAILURE     =       1
} EZPYRO_SMD_SENSOR_status_t;





/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the SPI peripheral.
    */
EZPYRO_SMD_SENSOR_status_t  EZPYRO_SMD_SENSOR_Init                            ( I2C_parameters_t myI2C_parameters                                                                                                                         );



#ifdef __cplusplus
}
#endif

#endif /* EZPYRO_SMD_SENSOR_H_ */
