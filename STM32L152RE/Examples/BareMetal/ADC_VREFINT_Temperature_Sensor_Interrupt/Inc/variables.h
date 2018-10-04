/**
 * @brief       variables.h
 * @details     Constants and variables used by the example.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        28/September/2018
 * @version     28/September/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "stm32l1xx.h"

#ifndef VARIABLES_H_
#define VARIABLES_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Macros
 */
#define _ROUND32U( x )  ( uint32_t )( x + 0.5 )

/**
 * @brief   Constants
 */
/* STATE MACHINE	 */
typedef enum{
  STATE_SLEEP_MODE                 		=   0UL,      /*!< System in Low Power         						 */
  STATE_TRIGGER_INTERNAL_TEMPERATURE	=   1UL,      /*!< Trigger a new internal temperature measurement	 	 */
  STATE_GET_RAW_TEMPERATURE_DATA		=   2UL,      /*!< Get raw internal temperature value      		 	 */
  STATE_TRIGGER_VDD  					=   3UL,      /*!< Trigger a new VDD measurement      			 	 */
  STATE_GET_RAW_VDD_DATA		        =   4UL,      /*!< Get raw VDD value      						 	 */
  STATE_PROCESS_ALL_DATA			    =   5UL,      /*!< Process all data, both temperature and VDD data	 */
  STATE_SEND_DATA_THROUGH_UART          =   6UL       /*!< Send all data through the UART      				 */
} system_state_machine_t;

/**
 * @brief   Variables
 */



#ifdef __cplusplus
}
#endif

#endif /* VARIABLES_H_ */
