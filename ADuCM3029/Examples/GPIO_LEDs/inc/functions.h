/**
 * @brief       functions.h
 * @details     Functions's header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        07/June/2019
 * @version     07/June/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "board.h"
#include <sys/platform.h>
#include "adi_initialize.h"
#include <sys/ADuCM302x_device.h>

#ifndef FUNCTION_H_
#define FUNCTION_H_

#ifdef __cplusplus
extern "C" {
#endif



/**@brief Function prototypes.
 */
void conf_CLK    ( void );
void conf_GPIO   ( void );



/**@brief Constants.
 */



/**@brief Variables.
 */



#ifdef __cplusplus
}
#endif

#endif /* FUNCTION_H_ */
