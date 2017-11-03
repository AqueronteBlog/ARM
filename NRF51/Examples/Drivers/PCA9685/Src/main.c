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
 * @date        31/October/2017
 * @version     31/October/2017    The ORIGIN
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
#include "PCA9685.h"


int main( void )
{
    I2C_parameters_t           myPCA9685_I2C_parameters;

    PCA9685_status_t           aux;
    //PCA9685_vector_data_t      myPCA9685_Data;


    conf_GPIO   ();
    conf_TIMER0 ();



    // I2C definition
    myPCA9685_I2C_parameters.TWIinstance =    NRF_TWI0;
    myPCA9685_I2C_parameters.SDA         =    TWI0_SDA;
    myPCA9685_I2C_parameters.SCL         =    TWI0_SCL;
    myPCA9685_I2C_parameters.ADDR        =    PCA9685_ADDRESS_0;
    myPCA9685_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
    myPCA9685_I2C_parameters.SDAport     =    NRF_GPIO;
    myPCA9685_I2C_parameters.SCLport     =    NRF_GPIO;

    // Configure I2C peripheral
    aux  =   PCA9685_Init ( myPCA9685_I2C_parameters );


    // Reset the device
    aux  =   PCA9685_SoftReset ( myPCA9685_I2C_parameters );
    nrf_delay_us ( 5 );


    aux  =   PCA9685_SetPWM_Freq ( myPCA9685_I2C_parameters, 60 );

    aux  =   PCA9685_SetMode ( myPCA9685_I2C_parameters, MODE1_SLEEP_DISABLED );

    aux  =   PCA9685_SetPWM_DutyCycle ( myPCA9685_I2C_parameters, PCA9685_LED3, 1, 95 );       // LED3: Delay Time = 1% | PWM duty cycle = 50%
    __NOP();

/*

    // Configure the device
    aux  =   PCA9685_Conf  ( myPCA9685_I2C_parameters, PCA9685_RESOLUTION_RH_12_TEMP_14, PCA9685_HTRE_DISABLED );

    // Get the Electronic Serial Number
    aux  =   PCA9685_GetElectronicSerialNumber ( myPCA9685_I2C_parameters, &myPCA9685_Data );

    // Get the Firmware revision
    aux  =   PCA9685_GetFirmwareRevision       ( myPCA9685_I2C_parameters, &myPCA9685_Data );


    NRF_TIMER0->TASKS_START  =   1;                 // Start Timer0

*/
    while( 1 )
    {
        //NRF_POWER->SYSTEMOFF = 1;
        NRF_POWER->TASKS_LOWPWR = 1;                // Sub power mode: Low power.

        // Enter System ON sleep mode
    	__WFE();
    	// Make sure any pending events are cleared
    	__SEV();
    	__WFE();

/*
    	switch ( mySTATE ){
        default:
        case 1:
        // Trigger a new Humidity and Temperature measurement
            NRF_GPIO->OUTCLR             =   ( 1UL << LED1 );       // Turn the LED1 on

            aux = PCA9685_TriggerHumidity ( myPCA9685_I2C_parameters, PCA9685_MEASURE_RELATIVE_HUMIDITY_NO_HOLD_MASTER_MODE );
            break;

        case 2:
        // Get the result: Humidity and Temperature

            aux = PCA9685_ReadHumidity           ( myPCA9685_I2C_parameters, &myPCA9685_Data );
            aux = PCA9685_ReadTemperatureFromRH  ( myPCA9685_I2C_parameters, &myPCA9685_Data );

            mySTATE =   0;
            NRF_GPIO->OUTSET             =   ( 1UL << LED1 );       // Turn the LED1 off
            break;
    	}
*/
        //__NOP();
    }
}
