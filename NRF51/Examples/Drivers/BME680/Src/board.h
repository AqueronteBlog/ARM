/**
 * @brief       board.h
 * @details     It characterizes the board ( for this example ): nrf51-DK.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        5/May/2017
 * @version     30/June/2017    TWI0 pins added.
 *              2/June/2017     Uart0 pins added.
 *              5/May/2017      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

/* LEDs */
#define LED1        21     /*!<   LED1: P0.21   */
#define LED2        22     /*!<   LED2: P0.22   */
#define LED3        23     /*!<   LED3: P0.23   */
#define LED4        24     /*!<   LED4: P0.24   */

/* UART0 */
#define UART0_TX    9      /*!<   UART TX: P0.9    */
#define UART0_RX    11     /*!<   UART RX: P0.11   */

/* TWI0 */
#define TWI0_SCL    7      /*!<   TWI0 SCL: P0.7    */
#define TWI0_SDA    30     /*!<   TWI0 SDA: P0.30   */
