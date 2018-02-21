/**
 * @brief       board.h
 * @details     It characterizes the board ( for this example ): nrf52-DK.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/February/2018
 * @version     17/February/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#ifndef BOARD_H_
#define BOARD_H_

#ifdef __cplusplus
extern "C" {
#endif

/* LEDs */
typedef enum{
  LED1  = 17,               /*!<   LED1: P0.17   */
  LED2  = 18,               /*!<   LED2: P0.18   */
  LED3  = 19,               /*!<   LED3: P0.19   */
  LED4  = 20                /*!<   LED4: P0.20   */
} NRF52DK_board_LEDS_t;

//typedef enum{
//  LED1  = 13,               /*!<   LED1: P0.13   */
//  LED2  = 14,               /*!<   LED2: P0.14   */
//  LED3  = 15,               /*!<   LED3: P0.15   */
//  LED4  = 16                /*!<   LED4: P0.16   */
//} NRF52DKPreview_board_LEDS_t;


#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */