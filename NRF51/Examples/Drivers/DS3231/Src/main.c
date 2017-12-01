/**
 * @brief       main.c
 * @details     [todo].
 *
 *              The rest of the time, the microcontroller is in low power.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        1/December/2017
 * @version     1/December/2017    The ORIGIN
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
#include "DS3231.h"


int main( void )
{
    I2C_parameters_t          myDS3231_I2C_parameters;
    DS3231_status_t           aux;


    conf_GPIO   ();
    conf_TIMER0 ();



    // I2C definition
    myDS3231_I2C_parameters.TWIinstance =    NRF_TWI0;
    myDS3231_I2C_parameters.SDA         =    TWI0_SDA;
    myDS3231_I2C_parameters.SCL         =    TWI0_SCL;
    //myDS3231_I2C_parameters.ADDR        =    DS3231_ADDRESS_0;
    myDS3231_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
    myDS3231_I2C_parameters.SDAport     =    NRF_GPIO;
    myDS3231_I2C_parameters.SCLport     =    NRF_GPIO;

    // Configure I2C peripheral
    //aux  =   DS3231_Init ( myDS3231_I2C_parameters );


    // Reset the device
    //aux  =   DS3231_SoftReset ( myDS3231_I2C_parameters );
    //nrf_delay_us ( 5 );


    //NRF_TIMER0->TASKS_START  =   1;                 // Start Timer0

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
        NRF_GPIO->OUTCLR             =   ( 1UL << LED1 );       // Turn the LED1 on
    	switch ( mySTATE ){
        default:
        case 1:
        // All LEDs: Delay Time = 1% | PWM duty cycle = 99%
            aux  =   DS3231_SetPWM_DutyCycle_AllLEDs ( myDS3231_I2C_parameters, 0, 99 );
            break;

        case 2:
        // All LEDs: Delay Time = 100% | PWM duty cycle = 1%
            aux  =   DS3231_SetPWM_DutyCycle_AllLEDs ( myDS3231_I2C_parameters, 100, 1 );
            break;

        case 3:
        // LED1: Delay Time = 10% | PWM duty cycle = 30%
            aux  =   DS3231_SetPWM_DutyCycle ( myDS3231_I2C_parameters, DS3231_LED1, 10, 30 );

            mySTATE =   0;
            break;
    	}
    	NRF_GPIO->OUTSET             =   ( 1UL << LED1 );       // Turn the LED1 off
        //__NOP();
*/
    }
}
