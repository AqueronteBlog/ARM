/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        26/December/2017
 * @version     26/December/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN
 */
#include "interrupts.h"

/**
 * @brief       void SysTick_Handler ()
 * @details     It increments myDelay every 1ms.
 *
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        28/December/2017
 * @version     28/December/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 */
void SysTick_Handler(void)
{
	myDelay++;
}
