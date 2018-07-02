/**
 * @brief       main.c
 * @details     [todo].
 *
 *              This firmware is just an example about how to use the NVMC on the nrf52832. The system
 *              will handle everything on the Interrupts ( Low power mode selected ).
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        30/June/2018
 * @version     30/June/2018    The ORIGIN
 * @pre         This firmware was tested on the nrf52-DK with Segger Embedded Studio v3.34a
 *              ( SDK 14.2.0 ).
 * @warning     The softdevice (s132) is taken into account, Bluetooth was not used although.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "nordic_common.h"
#include "nrf.h"
#include "board.h"
#include "functions.h"
#include "interrupts.h"
#include "variables.h"


/**@brief Constants.
 */


/**@brief Variables.
 */
uint32_t volatile startCycle;       /*!<   New reading   */


/**@brief Function for application main entry.
 */
int main(void)
{
    conf_GPIO   ();
    conf_LFCLK  ();
    conf_RTC0   ();


    NRF_RTC0->TASKS_START = 1;    // Start RTC0

    // NRF_POWER->SYSTEMOFF    = 1;
    NRF_POWER->TASKS_LOWPWR = 1;        // Sub power mode: Low power.
    while( 1 )
    {
        // Enter System ON sleep mode
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

/**
 * @}
 */
