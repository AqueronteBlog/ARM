/**
 * @brief       board.h
 * @details     It characterizes the board ( for this example ): nrf52-DK.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/March/2018
 * @version     10/March/2018   The ORIGIN
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


/* SPI0 */
typedef enum{
  SPI0_SCK  = 29,           /*!<   SPI0 SCLK: P0.29   */
  SPI0_MOSI = 25,           /*!<   SPI0 MOSI: P0.25   */
  SPI0_MISO = 28,           /*!<   SPI0 MISO: P0.28   */
  SPI0_CS   = 5             /*!<   SPI0 CS:   P0.5    */
} NRF52DK_board_spi0_t;


/* SPIS1 */
typedef enum{
  SPIS1_SCK  = 3,           /*!<   SPIS1 SCLK: P0.3  */
  SPIS1_MOSI = 2,           /*!<   SPIS1 MOSI: P0.2  */
  SPIS1_MISO = 1,           /*!<   SPIS1 MISO: P0.1  */
  SPIS1_CS   = 4            /*!<   SPIS1 CS:   P0.4  */
} NRF52DK_board_spis1_t;



#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */