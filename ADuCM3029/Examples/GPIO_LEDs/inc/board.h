/**
 * @brief       board.h
 * @details     It characterizes the board ( for this example ): ADICUP3029.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        07/June/2019
 * @version     07/June/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include <stdio.h>

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



#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */
