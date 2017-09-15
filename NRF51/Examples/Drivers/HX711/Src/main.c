/**
 * @brief       main.c
 * @details     [TODO] XXX.
 *
 *
 *              The voltage will change every 0.5 seconds by the timer, the rest of the time, the
 *              microcontroller is in low power.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        14/September/2017
 * @version     14/September/2017    The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     Softdevice S310 was used although the file's name is S130. The softdevice
 *              is not used in this example anyway because of Bluetooth was not used.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "nrf.h"
#include "nrf_delay.h"
#include "ble.h"
#include "variables.h"
#include "functions.h"
#include "HX711.h"


int main( void )
{
    HX711_status_t          aux;
    HX711_pins_t            myHX711pins;
    Vector_count_t          myData;


    conf_GPIO   ();
    //conf_TIMER0 ();

    // Configure the pins to handle the HX711 device ( P0.12: DOUT, P0.13: PD_SCK )
    myHX711pins = HX711_Init ( 12, 13 );

    aux = HX711_PowerDown   ( myHX711pins );
    aux = HX711_Reset       ( myHX711pins );
    nrf_delay_ms ( 1000 );

    aux = HX711_ReadData_WithoutMass ( myHX711pins, CHANNEL_A_GAIN_128, &myData, 4 );


    while(1);

/*
    // Read the default data in both EEPROM and DAC
    aux = MCP4725_GetDAC_Data    ( NRF_TWI0, MCP4725_ADDRESS_LOW, &myDefaultData );
    aux = MCP4725_GetEEPROM_Data ( NRF_TWI0, MCP4725_ADDRESS_LOW, &myDefaultData );


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
