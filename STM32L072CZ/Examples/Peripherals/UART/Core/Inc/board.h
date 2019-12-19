/**
 * @brief       board.h
 * @details     It characterizes the board ( for this example ): B-L072Z-LRWAN1.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        29/September/2019
 * @version     29/September/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "stm32l0xx_hal.h"


#ifndef BOARD_H_
#define BOARD_H_

/**
  * @brief   LEDs
*/
typedef enum
{
    LD1         =   5,             /*!<  PB_5                        */
	LD2         =   5,             /*!<  PA_5                        */
	LD3         =   6,             /*!<  PB_6                        */
	LD4         =   7              /*!<  PB_7                        */
} B_L072Z_LRWAN1_leds_t;


/**
  * @brief   UART5
*/
typedef enum
{
	USART5_TX   =   3,             /*!<  PB_3                        */
	USART5_RX   =   4              /*!<  PB_4                        */
} B_L072Z_LRWAN1_uart5_t;

#endif /* BOARD_H_ */
