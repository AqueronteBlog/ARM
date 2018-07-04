/**
 * @brief       board.h
 * @details     It characterizes the board ( for this example ): nrf52-DK.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        27/March/2018
 * @version     27/March/2018   The ORIGIN
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
} NRF52DK_board_leds_t;



/* BUTTONs */
typedef enum{
  BTN1  = 13,               /*!<   BTN1: P0.13   */
  BTN2  = 14,               /*!<   BTN2: P0.14   */
  BTN3  = 15,               /*!<   BTN3: P0.15   */
  BTN4  = 16                /*!<   BTN4: P0.16   */
} NRF52DK_board_buttons_t;



/* UART0 */
typedef enum{
  UART0_TX  = 6,            /*!<   UART0_TX: P0.6  */
  UART0_RX  = 8             /*!<   UART0_RX: P0.8  */
} NRF52DK_board_uart0_t;



#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */