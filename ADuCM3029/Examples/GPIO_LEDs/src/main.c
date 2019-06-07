/**
 * @brief       main.c
 * @details     [todo]This example shows how to work with the external device: HTS221. Every 1 seconds, a new
 *              temperature/humidity value is read and the data is transmitted through the UART ( Baud Rate: 230400 ).
 *
 *              The microcontroller is in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        07/June/2019
 * @version     07/June/2019    The ORIGIN
 * @pre         This firmware was tested on the ADICUP3029 with CrossCore Embedded Studio v2.8.3.0.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */

#include <sys/platform.h>
#include "adi_initialize.h"
//#include <sys/ADuCM302x.h>
#include <sys/ADuCM302x_device.h>
#include "board.h"
#include "functions.h"
#include "interrupts.h"



/**@brief Constants.
 */



/**@brief Variables.
 */





/**@brief Function for application main entry.
 */
int main(int argc, char *argv[])
{
	/**
	 * Initialize managed drivers and/or services that have been added to 
	 * the project.
	 * @return zero on success 
	 */
	adi_initComponents();
	
	/* Begin adding your custom code here */
	pADI_GPIO0->CFG	|=	 ( 1UL << BITP_GPIO_CFG_PIN15 );



	return 0;
}

