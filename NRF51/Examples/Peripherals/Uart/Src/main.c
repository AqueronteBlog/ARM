/**
 * @brief       main.c
 * @details     It changes the state of the LEDs using the UART.
 *
 *              It will depend on what character the user sends through the UART:
 *                  - '1':  LED1 ON. Message replay: "LED 1 ON".
 *                  - '2':  LED2 ON. Message replay: "LED 2 ON".
 *                  - '3':  LED3 ON. Message replay: "LED 3 ON".
 *                  - '4':  LED1 ON. Message replay: "LED 4 ON".
 *                  - Another character will turn all the LEDs OFF without any message back through the UART.
 *
 *              This firmware is just an example about how to use the UART on the nrf51822. The system
 *              will handle everything on the Interrupts ( Low power mode selected ).
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        2/June/2017
 * @version     2/June/2017    The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     Softdevice S310 was used although the file's name is S130. The softdevice
 *              is not used in this example anyway because of Bluetooth was not used.
 */

#include "nrf.h"
#include "ble.h"
#include "variables.h"
#include "functions.h"


#define TX_ENABLE   1
#define TX_DISABLE  0


int main( void )
{
    uint32_t TX_dataEnable   =   TX_DISABLE;

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
    conf_UART   ();


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
            NRF_GPIO->OUTCLR        =   ( 1 << LED1 );
            myMessage [ 4 ]         =   '1';
            TX_dataEnable           =   TX_ENABLE;
            break;

        // Character '2': Turn LED2 ON and send a message through the UART
        case 0x32:
            NRF_GPIO->OUTCLR        =   ( 1 << LED2 );
            myMessage [ 4 ]         =   '2';
            TX_dataEnable           =   TX_ENABLE;
            break;

        // Character '3': Turn LED3 ON and send a message through the UART
        case 0x33:
            NRF_GPIO->OUTCLR        =   ( 1 << LED3 );
            myMessage [ 4 ]         =   '3';
            TX_dataEnable           =   TX_ENABLE;
            break;

        // Character '4': Turn LED4 ON and send a message through the UART
        case 0x34:
            NRF_GPIO->OUTCLR        =   ( 1 << LED4 );
            myMessage [ 4 ]         =   '4';
            TX_dataEnable           =   TX_ENABLE;
            break;

        // Turn all LEDs OFF: DO NOT send anything through the UART
        default:
            for ( uint32_t ii = LED1; ii < ( LED4 + 1 ); ii++ )
                NRF_GPIO->OUTSET        =   ( 1 << ii );

            TX_dataEnable                =   TX_DISABLE;
            NRF_UART0->TASKS_STARTRX     =   1;
            break;

        }


        // Send which LED was turned ON back through the UART
        if ( TX_dataEnable == TX_ENABLE )
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
