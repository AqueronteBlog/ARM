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
uint32_t volatile startCycle;                     /*!<   New reading                                                                         */
uint32_t volatile myTX;                           /*!<   It will store the data from the registers ( FICR ) to be transmitted                */
uint8_t  volatile dataToBeTX;                     /*!<   A counter. It indicates how many data it will be transmitted through the UART       */
uint8_t  volatile TX_inProgress;                  /*!<   It indicates if a transmission is in progress                                       */


/**@brief Function for application main entry.
 */
int main(void)
{
    conf_GPIO   ();
    conf_UART   ();
    conf_GPIOTE ();


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


            // Read/Transmit INFO.PART register
            myTX                         =   NRF_FICR->INFO.PART;
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



            // Read/Transmit INFO.VARIANT register
            myTX                         =   NRF_FICR->INFO.VARIANT;
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



            // Read/Transmit INFO.PACKAGE register
            myTX                         =   NRF_FICR->INFO.PACKAGE;
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



            // Read/Transmit INFO.RAM register
            myTX                         =   NRF_FICR->INFO.RAM;
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



            // Read/Transmit INFO.FLASH register
            myTX                         =   NRF_FICR->INFO.FLASH;
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


            // Read/Transmit TEMP.A0 register
            myTX                         =   NRF_FICR->TEMP.A0;
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


            // Read/Transmit TEMP.A1 register
            myTX                         =   NRF_FICR->TEMP.A1;
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


            // Read/Transmit TEMP.A2 register
            myTX                         =   NRF_FICR->TEMP.A2;
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


            // Read/Transmit TEMP.A3 register
            myTX                         =   NRF_FICR->TEMP.A3;
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


            // Read/Transmit TEMP.A4 register
            myTX                         =   NRF_FICR->TEMP.A4;
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


            // Read/Transmit TEMP.A5 register
            myTX                         =   NRF_FICR->TEMP.A5;
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


            // Read/Transmit TEMP.B0 register
            myTX                         =   NRF_FICR->TEMP.B0;
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


            // Read/Transmit TEMP.B1 register
            myTX                         =   NRF_FICR->TEMP.B1;
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


            // Read/Transmit TEMP.B2 register
            myTX                         =   NRF_FICR->TEMP.B2;
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


            // Read/Transmit TEMP.B3 register
            myTX                         =   NRF_FICR->TEMP.B3;
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



            // Read/Transmit TEMP.B4 register
            myTX                         =   NRF_FICR->TEMP.B4;
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



            // Read/Transmit TEMP.B5 register
            myTX                         =   NRF_FICR->TEMP.B5;
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



            // Read/Transmit TEMP.T0 register
            myTX                         =   NRF_FICR->TEMP.T0;
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



            // Read/Transmit TEMP.T1 register
            myTX                         =   NRF_FICR->TEMP.T1;
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



            // Read/Transmit TEMP.T2 register
            myTX                         =   NRF_FICR->TEMP.T2;
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



            // Read/Transmit TEMP.T3 register
            myTX                         =   NRF_FICR->TEMP.T3;
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



            // Read/Transmit TEMP.T4 register
            myTX                         =   NRF_FICR->TEMP.T4;
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



            // Read/Transmit NFC.TAGHEADER0 register
            myTX                         =   NRF_FICR->NFC.TAGHEADER0;
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



            // Read/Transmit NFC.TAGHEADER1 register
            myTX                         =   NRF_FICR->NFC.TAGHEADER1;
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



            // Read/Transmit NFC.TAGHEADER2 register
            myTX                         =   NRF_FICR->NFC.TAGHEADER2;
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



            // Read/Transmit NFC.TAGHEADER3 register
            myTX                         =   NRF_FICR->NFC.TAGHEADER3;
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
