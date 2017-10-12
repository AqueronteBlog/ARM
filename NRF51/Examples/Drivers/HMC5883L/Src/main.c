/**
 * @brief       main.c
 * @details     [todo]
 *
 *              The rest of the time, the microcontroller is in low power.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        12/October/2017
 * @version     12/October/2017    The ORIGIN
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
#include "HMC5883L.h"


int main( void )
{
    HMC5883L_status_t        aux;
    HMC5883L_vector_data_t   myData;

    /*
    conf_GPIO   ();
    conf_TWI0   ();
    conf_TIMER0 ();
    conf_GPIOTE ();



    mySTATE       =   0;                            // Reset the variable
    myHMC5883LINT  =   0;                            // Reset the variable


    // Configure HMC5883L: P[0-6] OUTPUTs, P7 INPUT
    myData.data   =   ( HMC5883L_P0_OUTPUT_LOW | HMC5883L_P1_OUTPUT_LOW | HMC5883L_P2_OUTPUT_LOW | HMC5883L_P3_OUTPUT_LOW |
                        HMC5883L_P4_OUTPUT_LOW | HMC5883L_P5_OUTPUT_LOW | HMC5883L_P6_OUTPUT_LOW | HMC5883L_P7_INPUT      );

    aux           =    HMC5883L_SetPins ( NRF_TWI0, HMC5883L_ADDRESS_0, myData );



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


        // Change the state of the HMC5883L pins: P[O-6]
    	if ( mySTATE == 0 )
        {
            myData.data   =   ( HMC5883L_P0_OUTPUT_LOW | HMC5883L_P1_OUTPUT_HIGH | HMC5883L_P2_OUTPUT_LOW | HMC5883L_P3_OUTPUT_HIGH |
                                HMC5883L_P4_OUTPUT_LOW | HMC5883L_P5_OUTPUT_HIGH | HMC5883L_P6_OUTPUT_LOW );

            aux           =   HMC5883L_SetPins  ( NRF_TWI0, HMC5883L_ADDRESS_0, myData );
        }
    	else
        {
    	     myData.data  =   ( HMC5883L_P0_OUTPUT_HIGH | HMC5883L_P1_OUTPUT_LOW | HMC5883L_P2_OUTPUT_HIGH | HMC5883L_P3_OUTPUT_LOW |
                                HMC5883L_P4_OUTPUT_HIGH | HMC5883L_P5_OUTPUT_LOW | HMC5883L_P6_OUTPUT_HIGH );

            aux           =   HMC5883L_SetPins  ( NRF_TWI0, HMC5883L_ADDRESS_0, myData );
        }

        if ( myHMC5883LINT == 1 )
        {
        // Status of P7 changed
            aux           =   HMC5883L_ReadPins ( NRF_TWI0, HMC5883L_ADDRESS_0, &myData );

            if ( ( myData.data & HMC5883L_P7_MASK ) == HMC5883L_P7_MASK )
                NRF_GPIO->OUTCLR    =   ( 1UL << LED1 );                    // Turn the LED 1 on when P7 is HIGH
            else
                NRF_GPIO->OUTSET    =   ( 1UL << LED1 );                    // Turn the LED 1 off when P7 is LOW


            myHMC5883LINT  =   0;                                            // Reset the variable
        }

        //__NOP();
    }
    */
}
