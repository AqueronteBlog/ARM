/**
 * @brief       board.h
 * @details     It characterizes the board ( for this example ): nrf51-DK.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        6/April/2018
 * @version     6/April/2018      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to Nimbus Centre ( http://www.nimbus.cit.ie ).
 */

#ifndef BOARD_H_
#define BOARD_H_

#ifdef __cplusplus
extern "C" {
#endif

/* LEDs */
typedef enum{
  LED1  = 21,               /*!<   LED1: P0.21   */
  LED2  = 22,               /*!<   LED2: P0.22   */
  LED3  = 23,               /*!<   LED3: P0.23   */
  LED4  = 24                /*!<   LED4: P0.24   */
} NRF51DK_board_leds_t;


/* UART0 */
typedef enum{
  UART0_TX  =   9,          /*!<   UART TX: P0.9    */
  UART0_RX  =   11          /*!<   UART RX: P0.11   */
} NRF51DK_board_uart0_t;


/* TWI0 */
typedef enum{
  TWI0_SCL  =   7,          /*!<   TWI0 SCL: P0.7    */
  TWI0_SDA  =   30          /*!<   TWI0 SDA: P0.30   */
} NRF51DK_board_twi0_t;


/* SPI0 */
typedef enum{
  SPI0_SCK  = 29,           /*!<   SPI0 SCLK: P0.29   */
  SPI0_MOSI = 25,           /*!<   SPI0 MOSI: P0.25   */
  SPI0_MISO = 28,           /*!<   SPI0 MISO: P0.28   */
  SPI0_CS   = 5             /*!<   SPI0 CS:   P0.5    */
} NRF51DK_board_spi0_t;



#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */
