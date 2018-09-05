/**
 * @brief       main.c
 * @details     This example shows how to work with the external device: SHT2X. Every 0.5 seconds, a new
 *              task ( trigger temperature, get temperature value, trigger relative humidity, get relative humidity ) is
 *              performed and transmitted through the UART ( Baud Rate: 115200 ). In total, it takes a new sample about
 *              1.5 seconds to be transmitted through the UART.
 *
 *              The rest of the time, the microcontroller is in low power.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        3/September/2018
 * @version     3/September/2018    The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0 ( SDK 1.1.0 ).
 * @warning     Softdevice S310 was used although the file's name is S130. The softdevice
 *              is not used in this example anyway because of Bluetooth was not used.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */
#include <stdio.h>
#include <string.h>

#include "nrf.h"
#include "nrf_delay.h"
#include "ble.h"
#include "board.h"
#include "functions.h"
#include "variables.h"
#include "SHT2X.h"



/**@brief Constants.
 */
#define TX_BUFF_SIZE  64                          /*!<   UART buffer size                                       */


/**@brief Variables.
 */
volatile uint32_t myState;                        /*!<   State that indicates when to perform an ADC sample     */
volatile uint8_t  *myPtr;                         /*!<   Pointer to point out myMessage                         */



/**@brief Function for application main entry.
 */
int main( void )
{
    uint8_t  myMessage[ TX_BUFF_SIZE ];           /*!<   Message to be transmitted through the UART             */
    char     myBatteryMessage[5]  =  "";


    I2C_parameters_t        mySHT2X_I2C_parameters;
    SHT2X_status_t          aux;
    SHT2X_vector_data_t     mySHT2X_Data;



    conf_LFCLK  ();
    conf_GPIO   ();
    conf_UART   ();
    conf_RTC1   ();



    /* I2C definition   */
    mySHT2X_I2C_parameters.TWIinstance =    NRF_TWI0;
    mySHT2X_I2C_parameters.SDA         =    TWI0_SDA;
    mySHT2X_I2C_parameters.SCL         =    TWI0_SCL;
    mySHT2X_I2C_parameters.ADDR        =    SHT2X_ADDRESS;
    mySHT2X_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
    mySHT2X_I2C_parameters.SDAport     =    NRF_GPIO;
    mySHT2X_I2C_parameters.SCLport     =    NRF_GPIO;

    /* Configure I2C peripheral  */
    aux  =   SHT2X_Init            ( mySHT2X_I2C_parameters );

    /* Configure the device: Resolution Temperature: 14-bit and Humidity: 12-bit, Heater is disabled     */
    aux  =   SHT2X_Conf            ( mySHT2X_I2C_parameters, USER_REGISTER_RESOLUTION_12RH_14TEMP, USER_REGISTER_HEATER_DISABLED );

    /* Get the serial number     */
    aux  =   SHT2X_GetSerialNumber ( mySHT2X_I2C_parameters, &mySHT2X_Data );

    /* Transmit result through the UART  */
    sprintf ( (char*)myMessage, "ID: %ld\r\n", (long int)mySHT2X_Data.SerialNumber );

    NRF_UART0->TASKS_STOPRX  =   1UL;
    NRF_UART0->TASKS_STOPTX  =   1UL;
    myPtr                    =   &myMessage[0];

    NRF_UART0->TASKS_STARTTX =   1UL;
    NRF_UART0->TXD           =   *myPtr;



    myState  =   0;                             // Reset the variable
    NRF_RTC1->TASKS_START = 1;                  // Start RTC1

    //NRF_POWER->SYSTEMOFF = 1;
    NRF_POWER->TASKS_LOWPWR  =   1;             // Sub power mode: Low power.
    while( 1 )
    {
        /* Enter System ON sleep mode   */
    	__WFE();
    	/* Make sure any pending events are cleared */
    	__SEV();
    	__WFE();


        switch ( myState )
        {
            default:
            case 1:
                NRF_GPIO->OUTSET     |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );          // Turn all the LEDs off

                /* Trigger a new temperature measurement     */
                aux  =   SHT2X_TriggerTemperature ( mySHT2X_I2C_parameters, SHT2X_NO_HOLD_MASTER_MODE );
                break;

            case 2:
                /* Get the temperature   */
                aux  =   SHT2X_ReadTemperature    ( mySHT2X_I2C_parameters, &mySHT2X_Data );

                /* Trigger a new relative humidity measurement     */
                aux  =   SHT2X_TriggerHumidity    ( mySHT2X_I2C_parameters, SHT2X_NO_HOLD_MASTER_MODE );
                break;

            case 3:
                /* Get the relative humidity     */
                aux  =   SHT2X_ReadHumidity       ( mySHT2X_I2C_parameters, &mySHT2X_Data );

                /* Get the battery status    */
                aux  =   SHT2X_BatteryStatus      ( mySHT2X_I2C_parameters, &mySHT2X_Data );

                /* Prepare the message for the battery status  */
                if ( ( mySHT2X_Data.BatteryStatus & USER_REGISTER_STATUS_END_BATTERY_MASK ) == USER_REGISTER_STATUS_END_BATTERY_HIGH_2V25 )
                {
                    strcpy( myBatteryMessage, "GOOD" );
                }
                else
                {
                    strcpy( myBatteryMessage, "BAD" );
                }

                /* Transmit result through the UART  */
                sprintf ( (char*)myMessage, "Temperature: %d C | RH: %d | Battery: %s\r\n", (uint8_t)( mySHT2X_Data.Temperature + 0.5f ), (uint8_t)( mySHT2X_Data.RelativeHumidity + 0.5f ), myBatteryMessage );

                NRF_UART0->TASKS_STOPRX  =   1UL;
                NRF_UART0->TASKS_STOPTX  =   1UL;
                myPtr                    =   &myMessage[0];

                NRF_UART0->TASKS_STARTTX =   1UL;
                NRF_UART0->TXD           =   *myPtr;


                /* Reset the variables   */
                myState               =  0;
                NRF_GPIO->OUTCLR     |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );          // Turn all the LEDs on
                break;
    	}
        //__NOP();
    }
}
