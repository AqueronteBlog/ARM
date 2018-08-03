/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/March/2018
 * @version     9/March/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "stm32l1xx.h"
#include "variables.h"
#include "board.h"

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#ifdef __cplusplus
extern "C" {
#endif


/**@brief Subroutine prototypes.
 */
void RTC_WKUP_IRQHandler ( void );


/**@brief Constants.
 */



/**@brief Variables.
 */
extern volatile uint32_t myLEDstate;



#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */
