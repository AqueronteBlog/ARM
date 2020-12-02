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



/* Register: FIFO STATUS PACKET. Single byte with the status of the FIFO or wake up algorithm	*/
/**
  * @brief   WAKE_DETECTED <7>.
  *
  *          NOTE: N/A
  */
typedef enum
{
	FIFO_STATUS_PACKET_WAKE_DETECTED_MASK									=   ( 1U << 7U ),    /*!<  WAKE_DETECTED mask                           */
	FIFO_STATUS_PACKET_WAKE_DETECTED_OTHERWISE								=   ( 0U << 7U ),    /*!<  if in Sleep Mode and wake up event detected  */
	FIFO_STATUS_PACKET_WAKE_DETECTED_SLEEP_MODE_AND_WAKEUP_EVENT_DETECTED	=   ( 1U << 7U )     /*!<  if in Sleep Mode and wake up event detected  */
} EZPYRO_SMD_SENSOR_fifo_status_packet_wake_detected_t;


/**
  * @brief   ERROR_STATUS <6:5>. Register address automatically incremented during a multiple byte access with SPI serial interface
  *
  *          NOTE: Error status.
  */
typedef enum
{
	FIFO_STATUS_ERROR_STATUS_MASK									=   ( 0b11 << 5U ),   		/*!<  ERROR_STATUS mask                            											*/
	FIFO_STATUS_ERROR_STATUS_NO_ERROR								=   ( 0b00 << 5U ),   		/*!<  No error									 											*/
	FIFO_STATUS_ERROR_STATUS_WRITE_FIFO_FULL_OR_READ_FIFO_EMPTY		=   ( 0b01 << 5U ),   		/*!<  Write when FIFO is full (FIFO count = 14) or read when FIFO is empty (FIFO count = 0)  	*/
	FIFO_STATUS_ERROR_STATUS_READ_FIFO_EARLY_TERMINATION			=   ( 0b10 << 5U ),   		/*!<  Detect I2C read FIFO early termination (read less bytes than expected)  				*/
	FIFO_STATUS_ERROR_STATUS_READ_FIFO_EXTRA_BYTES					=   ( 0b11 << 5U )    		/*!<  Detect I2C read FIFO extra (read more bytes than expected)  							*/
} EZPYRO_SMD_SENSOR_fifo_status_packet_error_status_t;


/**
  * @brief   FIFO_COUNT <4:1>.
  *
  *          NOTE: Number of data packets available in the FIFO.
  */
typedef enum
{
	FIFO_STATUS_PACKET_WAKE_DETECTED_MASK							=   ( 0b1111 << 1U )	    /*!<  FIFO_COUNT mask                              */
} EZPYRO_SMD_SENSOR_fifo_status_packet_fifo_count_t;


/**
  * @brief   INVERTED_STATUS <0>.
  *
  *          NOTE: It is an inverse of Interrupt pin output (without masking).
  */
typedef enum
{
	FIFO_STATUS_PACKET_INVERTED_STATUS_MASK								=   ( 1U << 0U ),		/*!<  INVERTED_STATUS mask  								                    */
	FIFO_STATUS_PACKET_INVERTED_STATUS_NORMAL_OPERATION_FIFO_NOT_EMPTY	=   ( 1U << 0U ),		/*!<  In Normal Operation Mode, this bit is set (1) when the FIFO is not empty	*/
	FIFO_STATUS_PACKET_INVERTED_STATUS_NORMAL_OPERATION_FIFO_EMPTY		=   ( 0U << 0U ) 		/*!<  Reset(0) when the FIFO is empty								            */
} EZPYRO_SMD_SENSOR_fifo_status_packet_inverted_status_t;







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
