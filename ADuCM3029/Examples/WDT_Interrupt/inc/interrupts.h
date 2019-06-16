/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        13/June/2019
 * @version     13/June/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "board.h"
#include <sys/platform.h>
#include "adi_initialize.h"
#include <sys/ADuCM302x_device.h>


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "board.h"


/**@brief Subroutine prototypes.
 */
extern void WDog_Tmr_Int_Handler ( void );


/**@brief Constants.
 */



/**@brief Variables.
 */
extern volatile uint32_t myState;


#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */
