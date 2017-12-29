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
      * @brief   NUCLEO-L152RE PINOUT
      */
typedef enum
{
    LED_1         =   5,              /*!<  NUCLEO-L152RE LED1: 		PA_5  		*/
	BUTTON_1      =   13              /*!<  NUCLEO-L152RE USER BUTTON: 	PC_13		*/
} NUCLEOL152_pin_name_t;

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */
