/**
 * @brief       main.c
 * @details     [TODO]It changes the state of the LEDs using the UART.
 *
 *
 *              This firmware is just an example about how to use the UART on the nrf51422. The system
 *              will handle everything on the Interrupts ( Low power mode selected ).
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        22/June/2017
 * @version     22/June/2017    The ORIGIN
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

        // Evaluate the data
        if ( myRX_buff   ==  'm' )
        {
        // Character '1': Turn LED1 ON and send a message through the UART
            NRF_GPIO->OUTCLR        =   ( 1 << LED1 );
            TX_dataEnable           =   TX_ENABLE;
        }


        // Send which LED was turned ON back through the UART
        if ( TX_dataEnable == TX_ENABLE )
        {
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   myRandomNumber;

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }

            NRF_UART0->TASKS_STARTRX     =   1;                 // Enable reception from UART
            NRF_GPIO->OUTSET             =   ( 1 << LED1 );
        }

    }
}
