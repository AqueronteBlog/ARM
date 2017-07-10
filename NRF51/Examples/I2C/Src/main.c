/**
 * @brief       main.c
 * @details     [todo] xxx.
 *
 *              This firmware is just an example about how to use the I2C on the nrf51422. The system
 *              will handle everything on the Interruptions ( Low power mode selected ).
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        30/June/2017
 * @version     30/June/2017    The ORIGIN
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
#include "HTU21D.h"


int main( void )
{
    float    myTEMP =   0;
    float    myRH   =   0;
    uint32_t aux    =   0;

    conf_GPIO   ();
    conf_UART   ();
    conf_TWI0   ();
    conf_TIMER0 ();


    mySTATE                  =   0;                 // Reset counter
    NRF_TWI0->ADDRESS        =   HTU21D_ADDR;       // HTU21D device address

    HTU21D_SoftReset ();
    HTU21D_Init      ( HTU21D_MODE_NO_HOLD_MASTER, USER_REGISTER_RESOLUTION_12RH_14TEMP, USER_REGISTER_HEATER_DISABLED );

    NRF_TIMER0->TASKS_START  =   1;                 // Start Timer0


    while( 1 )
    {
        //NRF_POWER->SYSTEMOFF = 1;
        NRF_POWER->TASKS_LOWPWR = 1;        // Sub power mode: Low power.

        // Enter System ON sleep mode
		__WFE();
		// Make sure any pending events are cleared
		__SEV();
		__WFE();

		switch ( mySTATE ){
        case 1:
            aux = HTU21D_TriggerTemperature ();
            break;

        case 2:
            aux = HTU21D_ReadTemperature ( &myTEMP );
            aux = HTU21D_TriggerHumidity ();
            break;

        case 3:
            HTU21D_ReadHumidity ( &myRH );
            __NOP();
            mySTATE =   0;
            break;

        default:
            mySTATE =   0;
            break;
		}

        //__NOP();

    }
}
