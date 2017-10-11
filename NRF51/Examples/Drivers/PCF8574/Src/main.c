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
 * @date        22/September/2017
 * @version     22/September/2017    The ORIGIN
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
#include "PCF8591.h"


int main( void )
{
    uint8_t                 myNewDAC_value   =   128;

    PCF8591_status_t        aux;
    PCF8591_vector_data_t   myADC_Data;

    conf_GPIO   ();
    conf_TWI0   ();
    //conf_TIMER0 ();

    //aux = PCF8591_SetADC  ( NRF_TWI0, PCF8591_ADDRESS_0, PCF8591_FOUR_SINGLE_ENDED_INPUTS, PCF8591_AUTO_INCREMENT_ENABLED, PCF8591_CHANNEL_0 );
    aux = PCF8591_SetDAC  ( NRF_TWI0, PCF8591_ADDRESS_0, PCF8591_DAC_ENABLED );
    while(1)
    {
        aux = PCF8591_SetADC  ( NRF_TWI0, PCF8591_ADDRESS_0, PCF8591_FOUR_SINGLE_ENDED_INPUTS, PCF8591_AUTO_INCREMENT_ENABLED, PCF8591_CHANNEL_0 );
        aux = PCF8591_ReadADC ( NRF_TWI0, PCF8591_ADDRESS_0, &myADC_Data );

        aux = PCF8591_NewDACValue ( NRF_TWI0, PCF8591_ADDRESS_0, myNewDAC_value );

        if ( myNewDAC_value < 246 )
            myNewDAC_value  +=  10;
        else
            myNewDAC_value   =   0;
    }


    /*

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
        // Vout ~ 0V
            NRF_GPIO->OUTCLR             =   ( 1UL << LED1 );       // Turn the LED1 on
            myNewDACData.DAC_New_Value   =   0;
            aux = MCP4725_SetNewValue ( NRF_TWI0, MCP4725_ADDRESS_LOW, FAST_MODE, myNewDACData );
            break;

        case 2:
        // Vout = ~ ( Vref * 0.5 )
            myNewDACData.DAC_New_Value   =   2048;
            aux = MCP4725_SetNewValue ( NRF_TWI0, MCP4725_ADDRESS_LOW, WRITE_DAC_AND_EEPROM_REGISTER_MODE, myNewDACData );
            break;

        case 3:
        // Vout ~ Vref
            myNewDACData.DAC_New_Value   =   4095;
            aux = MCP4725_SetNewValue ( NRF_TWI0, MCP4725_ADDRESS_LOW, WRITE_DAC_REGISTER_MODE, myNewDACData );

            mySTATE =   0;
            NRF_GPIO->OUTSET             =   ( 1UL << LED1 );       // Turn the LED1 off
            break;
    	}

        //__NOP();

    }
    */
}
