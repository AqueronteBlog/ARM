/**
 * @brief       main.c
 * @details     [todo]xxx.
 *
 *              This firmware is just an example about how to use the I2C on the nrf51422.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        2/August/2017
 * @version     2/August/2017    The ORIGIN
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
#include "BH1750.h"


int main( void )
{
    uint32_t ii             =       0;
    // float    myTEMP         =       0;
    // float    myRH           =       0;
    uint8_t  myRawTemp[]    =       { 0, 0, 0 };
    uint8_t  myRawRH[]      =       { 0, 0, 0 };
    uint32_t aux            =       0;


    conf_GPIO   ();
    conf_UART   ();
    conf_TWI0   ();
    conf_TIMER0 ();


    mySTATE                  =   0;                 // Reset counter

    //HTU21D_SoftReset ( NRF_TWI0, HTU21D_ADDR );
    //HTU21D_Init      ( NRF_TWI0, HTU21D_ADDR, HTU21D_MODE_NO_HOLD_MASTER, USER_REGISTER_RESOLUTION_11RH_11TEMP, USER_REGISTER_HEATER_DISABLED );

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
            //aux = HTU21D_TriggerTemperature ( NRF_TWI0, HTU21D_ADDR );
            break;

        case 2:
            // aux = HTU21D_ReadTemperature    ( NRF_TWI0, HTU21D_ADDR, &myTEMP );
            //aux = HTU21D_ReadRawTemperature ( NRF_TWI0, HTU21D_ADDR, &myRawTemp[0] );
            //aux = HTU21D_TriggerHumidity    ( NRF_TWI0, HTU21D_ADDR );
            break;

        case 3:
            // aux = HTU21D_ReadHumidity       ( NRF_TWI0, HTU21D_ADDR, &myRH );
            //aux = HTU21D_ReadRawTemperature ( NRF_TWI0, HTU21D_ADDR, &myRawRH[0] );

            // Store Temperature & Humidity into the UART TX buffer
            for ( ii = 0; ii < 3; ii++ )                            // Temperature + Checksum: 3 first bytes
                TX_buff[ii]  =  myRawTemp[ii];

            for ( ii = 3; ii < 6; ii++ )                            // Humidity + Checksum: The other 3 bytes
                TX_buff[ii]  =  myRawRH[ii - 3];


            // Start transmitting through the UART
            NRF_GPIO->OUTCLR             =   ( 1UL << LED1 );       // Turn the LED1 on

            myPtr                        =   &TX_buff[0];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   *myPtr++;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }

            mySTATE =   0;
            break;
		}

        //__NOP();

    }
}
