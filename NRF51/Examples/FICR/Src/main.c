/**
 * @brief       main.c
 * @details     This firmware sends all the FICR registers through the UART ( LSB first )
 *              every time the button 1 is pressed.
 *
 *              The code is NOT optimized on purpose, this way it is easy to read one
 *              of the FICR's registers.
 *
 *              The microcontroller will remain in low power until it occurs an interruption.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        26/June/2017
 * @version     26/June/2017   The ORIGIN
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


int main( void )
{
    conf_GPIO   ();
    conf_UART   ();
    conf_GPIOTE ();


    while( 1 )
    {
        //NRF_POWER->SYSTEMOFF = 1;
        NRF_POWER->TASKS_LOWPWR = 1;                                    // Sub power mode: Low power.

        __WFE();
		// Make sure any pending events are cleared
		__SEV();
		__WFE();


        if ( startCycle  ==  1 )
        {
        // Read and transmit the data from the registers ( FICR )
            NRF_GPIO->OUTCLR             =   ( 1 << LED1 );             // Tun the LED1 on

            // Read/Transmit Code Memory Page Size register
            myTX                         =   NRF_FICR->CODEPAGESIZE;
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit Code memory size in number of pages register
            myTX                         =   NRF_FICR->CODESIZE;
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit RAM block size register
            myTX                         =   NRF_FICR->NUMRAMBLOCK;
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit Size of RAM block 0 register
            myTX                         =   NRF_FICR->SIZERAMBLOCK[0];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit Identification number for the HW register
            myTX                         =   NRF_FICR->CONFIGID;
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit DEVICEID[0] contains the least significant bits of the device identifier register
            myTX                         =   NRF_FICR->DEVICEID[0];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit DEVICEID[1] contains the least significant bits of the device identifier register
            myTX                         =   NRF_FICR->DEVICEID[1];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit Encryption Root register
            myTX                         =   NRF_FICR->ER[0];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit Encryption Root register
            myTX                         =   NRF_FICR->ER[1];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit Encryption Root register
            myTX                         =   NRF_FICR->ER[2];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit Encryption Root register
            myTX                         =   NRF_FICR->ER[3];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit Identity Root register
            myTX                         =   NRF_FICR->IR[0];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit Identity Root register
            myTX                         =   NRF_FICR->IR[1];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit Identity Root register
            myTX                         =   NRF_FICR->IR[2];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit Identity Root register
            myTX                         =   NRF_FICR->IR[3];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit Device address type register
            myTX                         =   NRF_FICR->DEVICEADDRTYPE;
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit DEVICEADDR[0] contains the least significant bits of the device address register
            myTX                         =   NRF_FICR->DEVICEADDR[0];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit DEVICEADDR[1] contains the least significant bits of the device address register
            myTX                         =   NRF_FICR->DEVICEADDR[1];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit OVERRIDEEN register
            myTX                         =   NRF_FICR->OVERRIDEEN;
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit Override values for 1Mbit proprietary mode register
            myTX                         =   NRF_FICR->NRF_1MBIT[0];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit Override values for 1Mbit proprietary mode register
            myTX                         =   NRF_FICR->NRF_1MBIT[1];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit Override values for 1Mbit proprietary mode register
            myTX                         =   NRF_FICR->NRF_1MBIT[2];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit Override values for 1Mbit proprietary mode register
            myTX                         =   NRF_FICR->NRF_1MBIT[3];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit Override values for 1Mbit proprietary mode register
            myTX                         =   NRF_FICR->NRF_1MBIT[4];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit BLE_1MBIT register
            myTX                         =   NRF_FICR->BLE_1MBIT[0];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit BLE_1MBIT register
            myTX                         =   NRF_FICR->BLE_1MBIT[1];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit BLE_1MBIT register
            myTX                         =   NRF_FICR->BLE_1MBIT[2];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit BLE_1MBIT register
            myTX                         =   NRF_FICR->BLE_1MBIT[3];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            // Read/Transmit BLE_1MBIT register
            myTX                         =   NRF_FICR->BLE_1MBIT[4];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myTX;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            startCycle          =   0;                      // Reset the variable
            NRF_GPIO->OUTSET    =   ( 1 << LED1 );          // Turn the LED1 off
        }
    }
}
