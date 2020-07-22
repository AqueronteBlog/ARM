/**
 * @brief       SFM4100.h
 * @details     Low-cost Digital Mass Flow Meter for Gases.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/July/2020
 * @version     22/July/2020    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( https://www.nimbus.cit.ie ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "i2c.h"


/**
  * @brief   DEFAULT ADDRESSES
  */
typedef enum
{
  SFM4100_ADDRESS_AIR   =   0b0000001,       /*!<   I2C slave address for Air	*/
  SFM4100_ADDRESS_O2	=   0b0000010,       /*!<   I2C slave address for O2    */
  SFM4100_ADDRESS_CO2   =   0b0000011,       /*!<   I2C slave address for CO2   */
  SFM4100_ADDRESS_N2O   =   0b0000100,       /*!<   I2C slave address for N2O   */
  SFM4100_ADDRESS_AR    =   0b0000101        /*!<   I2C slave address for Ar    */
} SFM4100_addresses_t;



/**
  * @brief   REGISTER MAP
  */
typedef enum
{
  SFM4100_TRIGGER_FLOW_MEASUREMENT    =   0xF1,	/*!<  Trigger flow measurement	*/
  SFM4100_SOFT_RESET		          =   0xFE  /*!<  Soft reset              	*/
} SFM4100_register_map_t;


/* Scale factor	 */
#define	SFM4100_SCALE_FACTOR	(int16_t)1U
#define SFM4100_POLYNOMIAL 		0x131 			/*!<  P(x)=x^8+x^5+x^4+1 = 100110001	 */


#ifndef SFM4100_VECTOR_STRUCT_H
#define SFM4100_VECTOR_STRUCT_H
/* Physical values	 */
typedef struct
{
	float     flow_slm;				/*!<  Flow in slm                	*/
	float     flow_sccm;       		/*!<  Flow in sccm               	*/
	int16_t   raw_flow;       		/*!<  Raw flow value               	*/
} SFM4100_physical_values_t;


/* CRC values	 */
typedef struct
{
	uint8_t   current_crc;			/*!<  Current CRC value		        */
	uint8_t   calculated_crc;       /*!<  Calculated CRC value		   	*/
} SFM4100_crc_values_t;



/* USER: User's global variables	 */
typedef struct
{
	/* Output  */
	SFM4100_physical_values_t	conversion; 	/*!<  Conversion values		*/

	/* CRC  */
	SFM4100_crc_values_t		crc;           	/*!<  CRC               	*/
} SFM4100_data_t;
#endif




/**
  * @brief   ERROR STATUS. INTERNAL CONSTANTS
  */
typedef enum
{
    SFM4100_SUCCESS               =   0U,   /*!<  I2C communication success                       */
    SFM4100_FAILURE               =   1U,   /*!<  I2C communication failure                       */
    SFM4100_DATA_CORRUPTED        =   2U    /*!<  CRC						                      */
} SFM4100_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the I2C peripheral.
  */
SFM4100_status_t SFM4100_Init           ( I2C_parameters_t myI2Cparameters  							);

/** It triggers a softreset.
  */
SFM4100_status_t SFM4100_SoftReset      ( I2C_parameters_t myI2Cparameters                            	);

/** It gets the raw flow value.
  */
SFM4100_status_t SFM4100_GetRawFlow		( I2C_parameters_t myI2Cparameters, SFM4100_data_t* myRawFlow	);

/** It gets the current flow value.
  */
SFM4100_status_t SFM4100_GetFlow	    ( I2C_parameters_t myI2Cparameters, SFM4100_data_t* myFlow     	);

/** It calculates the CRC after a the flow value is read.
  */
SFM4100_status_t SFM4100_CalculateCRC	( SFM4100_data_t* myCRC  										);
