/**
 * @brief       board.h
 * @details     It characterizes the board ( for this example ): NUCLEO-L152RE.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        29/December/2017
 * @version     29/December/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */

#ifndef BOARD_H_
#define BOARD_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
      * @brief   NUCLEO-L152RE LEDs PINOUT
      */
typedef enum
{
    LED_1         =   5              /*!<  NUCLEO-L152RE LED1: 		PA_5  		*/
} NUCLEOL152_led_pinout_t;


/**
      * @brief   NUCLEO-L152RE BUTTONs PINOUT
      */
typedef enum
{
	BUTTON_1      =   13             /*!<  NUCLEO-L152RE USER BUTTON: 	PC_13	*/
} NUCLEOL152_button_pinout_t;

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */
