/**
 * @brief       board.h
 * @details     It characterizes the board ( for this example ): ADICUP3029.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        07/June/2019
 * @version     04/July/2019   Switches were added
 * 				07/June/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include <stdio.h>
#include <system_ADuCM3029.h>


#ifndef BOARD_H_
#define BOARD_H_


#ifdef __cplusplus
extern "C" {
#endif

/**@brief LEDs.
 */
typedef enum{
  DS3  = (uint16_t)( 1U << 0U ),		/*!<   LED1: P2_00   */
  DS4  = (uint16_t)( 1U << 15U )	 	/*!<   LED2: P1_15   */
} ADICUP3029_board_leds_t;


/**@brief SWITCHES.
 */
typedef enum{
  S4  = (uint16_t)( 1U << 2U ),			/*!<   WIFI_RST<-->GPIO34_WIFI: P2_02   */
  S3  = (uint16_t)( 1U << 15U )	 		/*!<   S3: P1_01   						*/
} ADICUP3029_board_switches_t;


#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */
