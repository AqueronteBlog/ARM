/**
 * @brief       main.c
 * @details     [todo]
 *
 *              The CPU remains in low power all the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        5/April/2018
 * @version     5/April/2018    The ORIGIN
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


/**@brief Constants.
 */
#define TX_BUFF_SIZE  32                /*!<   UART buffer size                               */

const uint32_t  NO   = 0;               /*!<   Constant to control the UART0                  */
const uint32_t  YES  = 1;               /*!<   Constant to control the UART0                  */

/**@brief Variables.
 */
uint8_t myRX_buff;                      /*!<   It collects the data from the UART             */
uint8_t myMessage[ TX_BUFF_SIZE ];      /*!<   Message to be transmitted through the UART     */
uint8_t *myPtr;                         /*!<   Pointer to point out myMessage                 */
uint8_t TX_inProgress;                  /*!<   It indicates if a transmission is in progress  */



/**@brief Function for application main entry.
 */
int main(void)
{
    uint32_t TX_dataEnable   =   NO;

    // Initialized the message
    myMessage[ 0 ]   =  'L';
    myMessage[ 1 ]   =  'E';
    myMessage[ 2 ]   =  'D';
    myMessage[ 3 ]   =  ' ';
    myMessage[ 4 ]   =  ' ';
    myMessage[ 5 ]   =  ' ';
    myMessage[ 6 ]   =  'O';
    myMessage[ 7 ]   =  'N';
    myMessage[ 8 ]   =  '\n';

    conf_GPIO   ();
    conf_UART0  ();


    while( 1 )
    {
        //NRF_POWER->SYSTEMOFF = 1;
        NRF_POWER->TASKS_LOWPWR = 1;        // Sub power mode: Low power.

        // Enter System ON sleep mode
        __WFE();
	// Make sure any pending events are cleared
	__SEV();
	__WFE();

        __NOP();


        // Reset and re-start conditions before evaluating the collected data from UART.
        NRF_UART0->TASKS_STOPRX      =   1;
        NRF_UART0->TASKS_STOPTX      =   1;
        myPtr                        =   &myMessage[0];

        // Evaluate the data
        switch ( myRX_buff )
        {
        // Character '1': Turn LED1 ON and send a message through the UART
        case 0x31:
            NRF_P0->OUTCLR          =   ( 1 << LED1 );
            myMessage [ 4 ]         =   '1';
            TX_dataEnable           =   YES;
            break;

        // Character '2': Turn LED2 ON and send a message through the UART
        case 0x32:  
            NRF_P0->OUTCLR          =   ( 1 << LED2 );
            myMessage [ 4 ]         =   '2';
            TX_dataEnable           =   YES;
            break;

        // Character '3': Turn LED3 ON and send a message through the UART
        case 0x33:
            NRF_P0->OUTCLR          =   ( 1 << LED3 );
            myMessage [ 4 ]         =   '3';
            TX_dataEnable           =   YES;
            break;

        // Character '4': Turn LED4 ON and send a message through the UART
        case 0x34:
            NRF_P0->OUTCLR          =   ( 1 << LED4 );
            myMessage [ 4 ]         =   '4';
            TX_dataEnable           =   YES;
            break;

        // Turn all LEDs OFF: DO NOT send anything through the UART
        default:
            for ( uint32_t ii = LED1; ii < ( LED4 + 1 ); ii++ )
                NRF_P0->OUTSET        =   ( 1 << ii );

            TX_dataEnable                =   NO;
            NRF_UART0->TASKS_STARTRX     =   1;
            break;

        }


        // Send which LED was turned ON back through the UART
        if ( TX_dataEnable == YES )
        {
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   *myPtr;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }

            NRF_UART0->TASKS_STARTRX     =   1;             // Enable reception from UART
        }

    }
}


/**
 * @}
 */
