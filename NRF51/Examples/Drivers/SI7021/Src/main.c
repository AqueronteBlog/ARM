/**
 * @brief       main.c
 * @details     This example shows how to work with the external sensor SI7021, I2C Temperature and
 *              Humidity sensor.
 *
 *              A new humidity and temperature measurement will be triggered every 0.5 seconds by the timer,
 *              the rest of the time, the microcontroller is in low power.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        5/February/2018
 * @version     5/February/2018    The ORIGIN
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
#include "SI7021.h"


int main( void )
{
    I2C_parameters_t           mySI7021_I2C_parameters;

    SI7021_status_t            aux;
    SI7021_vector_data_t       mySI7021_Data;


    conf_GPIO   ();
    conf_TIMER0 ();



    // I2C definition
    mySI7021_I2C_parameters.TWIinstance =    NRF_TWI0;
    mySI7021_I2C_parameters.SDA         =    TWI0_SDA;
    mySI7021_I2C_parameters.SCL         =    TWI0_SCL;
    mySI7021_I2C_parameters.ADDR        =    SI7021_ADDRESS;
    mySI7021_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
    mySI7021_I2C_parameters.SDAport     =    NRF_GPIO;
    mySI7021_I2C_parameters.SCLport     =    NRF_GPIO;

    // Configure I2C peripheral
    aux  =   SI7021_Init ( mySI7021_I2C_parameters );


    // Reset the device
    aux  =   SI7021_SoftReset ( mySI7021_I2C_parameters );
    nrf_delay_ms ( 15 );

    // Configure the device
    aux  =   SI7021_Conf  ( mySI7021_I2C_parameters, SI7021_RESOLUTION_RH_12_TEMP_14, SI7021_HTRE_DISABLED );

    // Get the Electronic Serial Number
    aux  =   SI7021_GetElectronicSerialNumber ( mySI7021_I2C_parameters, &mySI7021_Data );

    // Get the Firmware revision
    aux  =   SI7021_GetFirmwareRevision       ( mySI7021_I2C_parameters, &mySI7021_Data );


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
        // Trigger a new Humidity and Temperature measurement
            NRF_GPIO->OUTCLR             =   ( 1UL << LED1 );       // Turn the LED1 on

            aux = SI7021_TriggerHumidity ( mySI7021_I2C_parameters, SI7021_MEASURE_RELATIVE_HUMIDITY_NO_HOLD_MASTER_MODE );
            break;

        case 2:
        // Get the result: Humidity and Temperature

            aux = SI7021_ReadHumidity           ( mySI7021_I2C_parameters, &mySI7021_Data );
            aux = SI7021_ReadTemperatureFromRH  ( mySI7021_I2C_parameters, &mySI7021_Data );

            mySTATE =   0;
            NRF_GPIO->OUTSET             =   ( 1UL << LED1 );       // Turn the LED1 off
            break;
    	}

        //__NOP();
    }
}
