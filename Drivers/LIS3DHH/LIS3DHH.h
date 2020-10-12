/**
 * @brief       LIS3DHH.h
 * @details     MEMS motion sensor: Three-axis digital output accelerometer.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        11/October/2020
 * @version     11/October/2020    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "spi.h"

#ifndef LIS3DHH_H_
#define LIS3DHH_H_

#ifdef __cplusplus
extern "C" {
#endif


/* SPI COMMAND STRUCTURE */
/**
  * @brief   MODE. ( B15:B14 )
  */
typedef enum
{
    LIS3DHH_WRITE            =   ( 0x00 << 6 ),  /*!<  WRITE                 */
    LIS3DHH_READ             =   ( 0x01 << 6 ),  /*!<  READ                  */
    LIS3DHH_DIRECT_COMMAND   =   ( 0x03 << 6 )   /*!<  DIRECT COMMAND        */
} LIS3DHH_spi_command_structure_mode_t;


/**
  * @brief   REGISTER MAPPING
  */
typedef enum
{
    LIS3DHH_WHO_AM_I         =   0x0F,           /*!<  Device identification register						*/
    LIS3DHH_CTRL_REG1        =   0x20,           /*!<  Control register 1			    					*/
    LIS3DHH_INT1_CTRL        =   0x21,           /*!<  INT1 pin control register	    					*/
    LIS3DHH_INT2_CTRL        =   0x22,           /*!<  INT2 pin control register	    					*/
    LIS3DHH_CTRL_REG4        =   0x23,           /*!<  Control register 4			    					*/
    LIS3DHH_CTRL_REG5        =   0x24,           /*!<  Control register 5			    					*/
    LIS3DHH_OUT_TEMP_L       =   0x25,           /*!<  Temperature data output register 					*/
    LIS3DHH_OUT_TEMP_H       =   0x26,           /*!<  Temperature data output register 					*/
    LIS3DHH_STATUS           =   0x27,           /*!<  Status register			        					*/
    LIS3DHH_OUT_X_L_XL       =   0x28,           /*!<  Linear acceleration sensor X-axis output register	*/
    LIS3DHH_OUT_X_H_XL       =   0x29,           /*!<  Linear acceleration sensor X-axis output register	*/
    LIS3DHH_OUT_Y_L_XL       =   0x2A,           /*!<  Linear acceleration sensor Y-axis output register	*/
    LIS3DHH_OUT_Y_H_XL       =   0x2B,           /*!<  Linear acceleration sensor Y-axis output register	*/
    LIS3DHH_OUT_Z_L_XL       =   0x2C,           /*!<  Linear acceleration sensor Z-axis output register	*/
    LIS3DHH_OUT_Z_H_XL       =   0x2D,           /*!<  Linear acceleration sensor Z-axis output register	*/
    LIS3DHH_FIFO_CTRL        =   0x2E,           /*!<  FIFO control register								*/
    LIS3DHH_FIFO_SRC         =   0x2F            /*!<  FIFO status register									*/
} LIS3DHH_register_mapping_t;


/* Register: WHO_AM_I */
/**
  * @brief   WHO_AM_I fixed value
  *
  *          NOTE: N/A
  */
typedef enum
{
    WHO_I_AM_VALUE          =   0b00010001			/*!<  Fixed value                      			*/
} LIS3DHH_who_i_am_t;



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
} LIS3DHH_ctrl_reg1_norm_mod_en_t;


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
} LIS3DHH_ctrl_reg1_if_add_inc_t;


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
} LIS3DHH_ctrl_reg1_boot_t;


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
} LIS3DHH_ctrl_reg1_sw_reset_t;


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
} LIS3DHH_ctrl_reg1_drdy_pulse_t;


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
} LIS3DHH_ctrl_reg1_bdu_t;



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
} LIS3DHH_int1_ctrl_int1_drdy_t;


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
} LIS3DHH_int1_ctrl_int1_boot_t;


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
} LIS3DHH_int1_ctrl_int1_ovr_t;


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
} LIS3DHH_int1_ctrl_int1_fss5_t;


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
} LIS3DHH_int1_ctrl_int1_fth_t;


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
} LIS3DHH_int1_ctrl_int1_ext_t;



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
} LIS3DHH_int2_ctrl_int2_drdy_t;


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
} LIS3DHH_int2_ctrl_int2_boot_t;


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
} LIS3DHH_int2_ctrl_int2_ovr_t;


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
} LIS3DHH_int2_ctrl_int2_fss5_t;


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
} LIS3DHH_int2_ctrl_int2_fth_t;



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
} LIS3DHH_ctr_reg4_dsp_lp_type_t;


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
} LIS3DHH_ctr_reg4_dsp_bw_sel_t;


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
} LIS3DHH_ctr_reg4_st_t;


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
} LIS3DHH_ctr_reg4_pp_od_int2_t;


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
} LIS3DHH_ctr_reg4_pp_od_int1_t;


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
} LIS3DHH_ctr_reg4_fifo_en_t;



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
} LIS3DHH_ctr_reg5_fifo_spi_hs_on_t;



/* Register: OUT_TEMP	*/
/**
  * @brief   OUT_TEMP_L <7:4>. Temperature data output LSB.
  *
  *          NOTE: N/A
  */
typedef enum
{
	OUT_TEMP_L_MASK			=   0b11110000    /*!<  OUT_TEMP_L mask	  	                   */
} LIS3DHH_out_temp_l_t;






#ifndef LIS3DHH_VECTOR_STRUCT_H
#define LIS3DHH_VECTOR_STRUCT_H
/* LIS3DHH DATA */
typedef struct
{
    int8_t      f_wake;                  /*!<  False wakeup register                */
    uint8_t     patt2b;                  /*!<  Wakeup pattern PATT2B ( Manchester ) */
    uint8_t     patt1b;                  /*!<  Wakeup pattern PATT1B ( Manchester ) */
    uint8_t     rssi1;                   /*!<  RSSI1 Channel 1                      */
    uint8_t     rssi2;                   /*!<  RSSI2 Channel 2                      */
    uint8_t     rssi3;                   /*!<  RSSI3 Channel 3                      */

    uint32_t    data;                    /*!<  Data                                 */
} LIS3DHH_data_t;
#endif



/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    LIS3DHH_SUCCESS     =       0,
    LIS3DHH_FAILURE     =       1
} LIS3DHH_status_t;





/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the SPI peripheral.
    */
LIS3DHH_status_t  LIS3DHH_Init                            ( spi_parameters_t mySPI_parameters                                                                                                                         );



#ifdef __cplusplus
}
#endif

#endif /* LIS3DHH_H_ */
