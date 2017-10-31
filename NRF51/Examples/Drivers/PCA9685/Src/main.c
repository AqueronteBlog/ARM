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
#include "nrf_delay.h"
#include "ble.h"
#include "variables.h"
#include "functions.h"
#include "SI7006.h"


int main( void )
{
    I2C_parameters_t           mySI7006_I2C_parameters;

    SI7006_status_t            aux;
    SI7006_vector_data_t       mySI7006_Data;


    conf_GPIO   ();
    conf_TIMER0 ();



    // I2C definition
    mySI7006_I2C_parameters.TWIinstance =    NRF_TWI0;
    mySI7006_I2C_parameters.SDA         =    TWI0_SDA;
    mySI7006_I2C_parameters.SCL         =    TWI0_SCL;
    mySI7006_I2C_parameters.ADDR        =    SI7006_ADDRESS;
    mySI7006_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
    mySI7006_I2C_parameters.SDAport     =    NRF_GPIO;
    mySI7006_I2C_parameters.SCLport     =    NRF_GPIO;

    // Configure I2C peripheral
    aux  =   SI7006_Init ( mySI7006_I2C_parameters );


    // Reset the device
    aux  =   SI7006_SoftReset ( mySI7006_I2C_parameters );
    nrf_delay_ms ( 15 );

    // Configure the device
    aux  =   SI7006_Conf  ( mySI7006_I2C_parameters, SI7006_RESOLUTION_RH_12_TEMP_14, SI7006_HTRE_DISABLED );

    // Get the Electronic Serial Number
    aux  =   SI7006_GetElectronicSerialNumber ( mySI7006_I2C_parameters, &mySI7006_Data );

    // Get the Firmware revision
    aux  =   SI7006_GetFirmwareRevision       ( mySI7006_I2C_parameters, &mySI7006_Data );


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

            aux = SI7006_TriggerHumidity ( mySI7006_I2C_parameters, SI7006_MEASURE_RELATIVE_HUMIDITY_NO_HOLD_MASTER_MODE );
            break;

        case 2:
        // Get the result: Humidity and Temperature

            aux = SI7006_ReadHumidity           ( mySI7006_I2C_parameters, &mySI7006_Data );
            aux = SI7006_ReadTemperatureFromRH  ( mySI7006_I2C_parameters, &mySI7006_Data );

            mySTATE =   0;
            NRF_GPIO->OUTSET             =   ( 1UL << LED1 );       // Turn the LED1 off
            break;
    	}

        //__NOP();
    }
}
