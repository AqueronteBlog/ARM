/**
 * @brief       main.c
 * @details     This example shows how to work with the external PCF8574 device. Every 0.5s,
 *              the pins of the PCF8574 will change as following:
 *
 *                  - mySTATE = 0:
 *                      HIGH: P1, P3, P5
 *                      LOW:  P0, P2, P4, P6
 *
 *                  - mySTATE = 1:
 *                      LOW : P1, P3, P5
 *                      HIGH: P0, P2, P4, P6
 *
 *              Besides, if there is a change on P7 ( INPUT pin ), an interrupt will be called
 *              and check the state of P7, if it is high, it will turn the LED1 on if it is low
 *              it will turn it off.
 *
 *              The rest of the time, the microcontroller is in low power.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        11/October/2017
 * @version     11/October/2017    The ORIGIN
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
#include "PCF8574.h"


int main( void )
{
    PCF8574_status_t        aux;
    PCF8574_vector_data_t   myData;

    I2C_parameters_t            myPCF8574_I2C_parameters;



    conf_GPIO   ();
    conf_TIMER0 ();
    conf_GPIOTE ();



    mySTATE       =   0;                            // Reset the variable
    myPCF8574INT  =   0;                            // Reset the variable


    // I2C definition
    myPCF8574_I2C_parameters.TWIinstance =    NRF_TWI0;
    myPCF8574_I2C_parameters.SDA         =    TWI0_SDA;
    myPCF8574_I2C_parameters.SCL         =    TWI0_SCL;
    myPCF8574_I2C_parameters.ADDR        =    PCF8574_ADDRESS_0;
    myPCF8574_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
    myPCF8574_I2C_parameters.SDAport     =    NRF_GPIO;
    myPCF8574_I2C_parameters.SCLport     =    NRF_GPIO;

    // Configure I2C peripheral
    aux      =   PCF8574_Init ( myPCF8574_I2C_parameters );

    // Configure PCF8574: P[0-6] OUTPUTs, P7 INPUT
    myData.data   =   ( PCF8574_P0_OUTPUT_LOW | PCF8574_P1_OUTPUT_LOW | PCF8574_P2_OUTPUT_LOW | PCF8574_P3_OUTPUT_LOW |
                        PCF8574_P4_OUTPUT_LOW | PCF8574_P5_OUTPUT_LOW | PCF8574_P6_OUTPUT_LOW | PCF8574_P7_INPUT      );

    aux           =    PCF8574_SetPins ( myPCF8574_I2C_parameters, myData );



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


        // Change the state of the PCF8574 pins: P[O-6]
    	if ( mySTATE == 0 )
        {
            myData.data   =   ( PCF8574_P0_OUTPUT_LOW | PCF8574_P1_OUTPUT_HIGH | PCF8574_P2_OUTPUT_LOW | PCF8574_P3_OUTPUT_HIGH |
                                PCF8574_P4_OUTPUT_LOW | PCF8574_P5_OUTPUT_HIGH | PCF8574_P6_OUTPUT_LOW );

            aux           =   PCF8574_SetPins  ( myPCF8574_I2C_parameters, myData );
        }
    	else
        {
    	     myData.data  =   ( PCF8574_P0_OUTPUT_HIGH | PCF8574_P1_OUTPUT_LOW | PCF8574_P2_OUTPUT_HIGH | PCF8574_P3_OUTPUT_LOW |
                                PCF8574_P4_OUTPUT_HIGH | PCF8574_P5_OUTPUT_LOW | PCF8574_P6_OUTPUT_HIGH );

            aux           =   PCF8574_SetPins  ( myPCF8574_I2C_parameters, myData );
        }

        if ( myPCF8574INT == 1 )
        {
        // Status of P7 changed
            aux           =   PCF8574_ReadPins ( myPCF8574_I2C_parameters, &myData );

            if ( ( myData.data & PCF8574_P7_MASK ) == PCF8574_P7_MASK )
                NRF_GPIO->OUTCLR    =   ( 1UL << LED1 );                    // Turn the LED 1 on when P7 is HIGH
            else
                NRF_GPIO->OUTSET    =   ( 1UL << LED1 );                    // Turn the LED 1 off when P7 is LOW


            myPCF8574INT  =   0;                                            // Reset the variable
        }

        //__NOP();
    }
}
