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
    Vector_mass_t           myCalculatedMass;
    Vector_voltage_t        myCalculatedVoltage;


    conf_GPIO   ();
    conf_TIMER0 ();

    // Configure the pins to handle the HX711 device ( P0.12: DOUT, P0.13: PD_SCK )
    myHX711pins = HX711_Init ( 12, 13 );

    aux = HX711_PowerDown   ( myHX711pins );
    aux = HX711_Reset       ( myHX711pins );
    nrf_delay_ms ( 1000 );


    // CALIBRATION time start!
    // 1. REMOVE THE MASS ON THE LOAD CELL ( ALL LEDs OFF ). Read data without any mass on the load cell
    aux = HX711_ReadData_WithoutMass ( myHX711pins, CHANNEL_A_GAIN_128, &myData, 4 );

    NRF_GPIO->OUTCLR    =   ( 1UL << LED1 );
    nrf_delay_ms ( 3000 );

    // 2. PUT A KNOWN MASS ON THE LOAD CELL ( JUST LED1 ON ). Read data with an user-specified calibration mass
    aux = HX711_ReadData_WithCalibratedMass ( myHX711pins, CHANNEL_A_GAIN_128, &myData, 4 );
    // CALIBRATION time end!


    // [ OPTIONAL ] REMOVE THE MASS ON THE LOAD CELL ( JUST LED2 ON ). Read the device without any mass to calculate the tare weight for 5 seconds
    NRF_GPIO->OUTSET    =   ( 1UL << LED1 );
    NRF_GPIO->OUTCLR    =   ( 1UL << LED2 );
    nrf_delay_ms ( 3000 );
    NRF_GPIO->OUTSET    =   ( 1UL << LED2 );

    // Calculating the tare weight ( JUST LED3 ON )
    NRF_GPIO->OUTCLR    =   ( 1UL << LED3 );
    aux = HX711_SetAutoTare ( myHX711pins, CHANNEL_A_GAIN_128, 1.0, HX711_SCALE_kg, &myData, 5 );
    NRF_GPIO->OUTSET    =   ( 1UL << LED3 );




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


		if ( myNewMeasurement == YES ){
            NRF_GPIO->OUTCLR    =   ( 1UL << LED4 );

            aux                 =    HX711_ReadRawData       ( myHX711pins, CHANNEL_A_GAIN_128, &myData, 4 );
            myCalculatedMass    =    HX711_CalculateMass     ( &myData, 1.0, HX711_SCALE_kg );
            myCalculatedVoltage =    HX711_CalculateVoltage  ( &myData, 5.0 );

            myNewMeasurement    =   NO;

            NRF_GPIO->OUTSET    =   ( 1UL << LED4 );
		}

        //__NOP();

    }
}
