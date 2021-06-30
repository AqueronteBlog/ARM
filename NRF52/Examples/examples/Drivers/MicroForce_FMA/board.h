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

/**@brief LEDs.
 */
typedef enum{
  LED1  = 17,               /*!<   LED1: P0.17   */
  LED2  = 18,               /*!<   LED2: P0.18   */
  LED3  = 19,               /*!<   LED3: P0.19   */
  LED4  = 20                /*!<   LED4: P0.20   */
} NRF52DK_board_leds_t;


/**@brief UART0.
 */
typedef enum{
  UART0_TX  = 6,            /*!<   UART0_TX: P0.6  */
  UART0_RX  = 8             /*!<   UART0_RX: P0.8  */
} NRF52DK_board_uart0_t;


/**@brief TWI0.
 */
typedef enum{
  TWI0_SCL  =   27,         /*!<   TWI0 SCL: P0.27   */
  TWI0_SDA  =   26          /*!<   TWI0 SDA: P0.26   */
} NRF52DK_board_twi0_t;


/**@brief SPI0.
 */
typedef enum{
  SPI0_SCK  =   29,         /*!<   SPI0 SCLK: P0.29  */
  SPI0_MOSI =   25,         /*!<   SPI0 MOSI: P0.25  */
  SPI0_MISO =   28,         /*!<   SPI0 MISO: P0.28  */
  SPI0_CS   =   5           /*!<   SPI0 CS:   P0.5   */
} NRF52DK_board_spi0_t;


#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */