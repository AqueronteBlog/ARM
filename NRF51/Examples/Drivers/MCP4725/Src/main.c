/**
 * @brief       main.c
 * @details     This example shows how to work with the external device MCP4725 a 12-Bit
 *              Digital-to-Analog Converter with EEPROM Memory.
 *
 *              [TODO]
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        7/September/2017
 * @version     7/September/2017    The ORIGIN
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
#include "MCP4725.h"


int main( void )
{
    MCP4725_status_t aux;

    //Vector_cal_coeff_t          myCalCoeff;
    //Vector_temp_f               myUT;
    //Vector_pressure_f           myUP;
    //Vector_compensated_data_f   myTrueData;

    conf_GPIO   ();
    conf_TWI0   ();
    conf_TIMER0 ();


    aux = MCP4725_Reset  ( NRF_TWI0 );
    aux = MCP4725_WakeUp ( NRF_TWI0 );


    mySTATE                  =   1;                 // Reset counter

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


		switch ( mySTATE ){
        default:
        case 1:
            NRF_GPIO->OUTCLR             =   ( 1UL << LED1 );       // Turn the LED1 on
            aux = MCP4725_SetNewValue ( NRF_TWI0, MCP4725_ADDRESS_LOW, FAST_MODE, 0 );
            break;

        case 2:
            aux = MCP4725_SetNewValue ( NRF_TWI0, MCP4725_ADDRESS_LOW, WRITE_DAC_AND_EEPROM_REGISTER_MODE, 2048 );
            break;

        case 3:
            aux = MCP4725_SetNewValue ( NRF_TWI0, MCP4725_ADDRESS_LOW, WRITE_DAC_REGISTER_MODE, 4095 );

            mySTATE =   0;
            NRF_GPIO->OUTSET             =   ( 1UL << LED1 );       // Turn the LED1 off
            break;
		}

        //__NOP();

    }
}
