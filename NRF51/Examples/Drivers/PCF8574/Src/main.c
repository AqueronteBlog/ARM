/**
 * @brief       main.c
 * @details     [TODO]
 *
 *              The voltage will change every 0.5 seconds by the timer, the rest of the time, the
 *              microcontroller is in low power.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        11/October/2017
 * @version     11/October/2017    The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     Softdevice S310 was used although the file's name is S130. The softdevice
 *              is not used in this example anyway because of Bluetooth was not used.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "nrf.h"
#include "ble.h"
#include "variables.h"
#include "functions.h"
#include "PCF8574.h"


int main( void )
{
    PCF8574_status_t        aux;
    PCF8574_vector_data_t   myData;

    conf_GPIO   ();
    conf_TWI0   ();
    conf_TIMER0 ();



    NRF_TIMER0->TASKS_START  =   1;                 // Start Timer0

    while( 1 )
    {
        //NRF_POWER->SYSTEMOFF = 1;
        NRF_POWER->TASKS_LOWPWR = 1;                // Sub power mode: Low power.

        // Enter System ON sleep mode
    	__WFE();
    	// Make sure any pending events are cleared
    	__SEV();
    	__WFE();


    	if ( mySTATE )
        {
            myData.data   =   ( PCF8574_P0_OUTPUT_LOW | PCF8574_P1_OUTPUT_HIGH | PCF8574_P2_OUTPUT_LOW | PCF8574_P3_OUTPUT_HIGH |
                                PCF8574_P4_OUTPUT_LOW | PCF8574_P5_OUTPUT_HIGH | PCF8574_P6_OUTPUT_LOW | PCF8574_P7_OUTPUT_HIGH );

            aux           =   PCF8574_SetPins ( NRF_TWI0, PCF8574_ADDRESS_0, myData );
        }
    	else
        {
    	     myData.data  =   ( PCF8574_P0_OUTPUT_HIGH | PCF8574_P1_OUTPUT_LOW | PCF8574_P2_OUTPUT_HIGH | PCF8574_P3_OUTPUT_LOW |
                                PCF8574_P4_OUTPUT_HIGH | PCF8574_P5_OUTPUT_LOW | PCF8574_P6_OUTPUT_HIGH | PCF8574_P7_OUTPUT_LOW );

            aux           =   PCF8574_SetPins ( NRF_TWI0, PCF8574_ADDRESS_0, myData );
        }

        //__NOP();

    }
}
