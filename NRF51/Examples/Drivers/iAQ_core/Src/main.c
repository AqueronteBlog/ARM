/**
 * @brief       main.c
 * @details     [todo]
 *
 *              the rest of the time, the microcontroller is in low power.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        4/June/2018
 * @version     4/June/2018    The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     Softdevice S310 was used although the file's name is S130. The softdevice
 *              is not used in this example anyway because of Bluetooth was not used.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "nrf.h"
#include "nrf_delay.h"
#include "ble.h"
#include "board.h"
#include "functions.h"
#include "iAQ_Core.h"



/* GLOBAL VARIABLES */
uint32_t volatile mySTATE;                       /*!<   It indicates the next action to be performed                                       */



/* MAIN */
int main( void )
{
    uint32_t                   myWarmUpCounter   =   0;


    I2C_parameters_t           myiAQ_Core_I2C_parameters;

    iAQ_Core_status_t          aux;
    iAQ_Core_vector_data_t     myiAQ_Core_Data;


    conf_GPIO   ();
    conf_TIMER0 ();



    /* I2C definition   */
    myiAQ_Core_I2C_parameters.TWIinstance =    NRF_TWI0;
    myiAQ_Core_I2C_parameters.SDA         =    TWI0_SDA;
    myiAQ_Core_I2C_parameters.SCL         =    TWI0_SCL;
    myiAQ_Core_I2C_parameters.ADDR        =    iAQ_Core_ADDRESS;
    myiAQ_Core_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
    myiAQ_Core_I2C_parameters.SDAport     =    NRF_GPIO;
    myiAQ_Core_I2C_parameters.SCLport     =    NRF_GPIO;

    /* Configure I2C peripheral */
    aux  =   iAQ_Core_Init ( myiAQ_Core_I2C_parameters );


    /* iAQ-Core warm up is at least 5 minutes ( 300 * 1s ) or when the sensor is ready  */
    do
    {
        aux  =   iAQ_Core_GetNewReading ( myiAQ_Core_I2C_parameters, &myiAQ_Core_Data );
        nrf_delay_ms ( 1000 );
        myWarmUpCounter++;
    }while( ( myWarmUpCounter < 300 ) && ( myiAQ_Core_Data.status == iAQ_Core_STATUS_RUNIN ) );


    mySTATE = 1;
//    NRF_TIMER0->TASKS_START  =   1;             // Start Timer0

    //NRF_POWER->SYSTEMOFF = 1;
    NRF_POWER->TASKS_LOWPWR  =   1;             // Sub power mode: Low power.
    while( 1 )
    {
//        /* Enter System ON sleep mode   */
//    	__WFE();
//    	/* Make sure any pending events are cleared */
//    	__SEV();
//    	__WFE();


    	if ( mySTATE == 1 )
        {
            /* New reading */
            do
            {
                aux      =   iAQ_Core_GetNewReading ( myiAQ_Core_I2C_parameters, &myiAQ_Core_Data );
            }while( myiAQ_Core_Data.status != iAQ_Core_STATUS_OK );                                         // [TODO] Dangerous!!! The uC may get stuck here if something goes wrong!
                                                                                                            // [WORKAROUND] Insert a counter.



//            mySTATE  =   0;
    	}

        //__NOP();
    }
}
