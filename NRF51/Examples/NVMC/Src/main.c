/**
 * @brief       main.c
 * @details     It writes the value 0x23232323 into NRF51 non-volatile memory. Every 125ms,
 *              the system will check if the value 0x23232323 is stored in a specific memory
 *              location, if so, it will erase that location, if not, it will write that value.
 *
 *              This firmware is just an example about how to use the NVMC on the nrf51422.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        12/July/2017
 * @version     12/July/2017    The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     Softdevice S310 was used although the file's name is S130. The softdevice
 *              is not used in this example anyway because of Bluetooth was not used.
 * @pre         This project has to be tested by the Debugger.
 * @pre         Be aware of the timing of one flash write operation ( NRF51 Product Specification
 *              p.64 8.22 Non-Volatile Memory Controller (NVMC) specifications ).
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "nrf.h"
#include "ble.h"
#include "variables.h"
#include "functions.h"


int main( void )
{
    uint32_t myPageNumber         =  ( NRF_FICR->CODESIZE - 1 );
    uint32_t *myPageAddress       =  ( uint32_t * ) ( myPageNumber * NRF_FICR->CODEPAGESIZE );
    uint32_t myValue              =  0x23232323;


    conf_GPIO   ();
    conf_LFCLK  ();
    conf_RTC0   ();


    NRF_RTC0->TASKS_START = 1;    // Start RTC0


    while( 1 )
    {
        // NRF_POWER->SYSTEMOFF    = 1;
        NRF_POWER->TASKS_LOWPWR = 1;        // Sub power mode: Low power.

        // Enter System ON sleep mode
		__WFE();
		// Make sure any pending events are cleared
		__SEV();
		__WFE();


		if ( writeNVMC  ==  YES )
        {
            NRF_GPIO->OUTCLR         =   ( 1UL << LED1 );

            if ( *myPageAddress == myValue )
            {
            // Erase Page Memory
                NRF_NVMC->CONFIG     =   ( NVMC_CONFIG_WEN_Een << NVMC_CONFIG_WEN_Pos );
                while ( NRF_NVMC->READY == NVMC_READY_READY_Busy );                         // [ NOTE ]  This is dangerous, it can block the uC.
                                                                                            //           Insert a counter to handle that problem.

                NRF_NVMC->ERASEPAGE  = ( uint32_t )myPageAddress;

                NRF_NVMC->CONFIG     =   ( NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos );
                while ( NRF_NVMC->READY == NVMC_READY_READY_Busy );                         // [ NOTE ]  This is dangerous, it can block the uC.
                                                                                            //           Insert a counter to handle that problem.

                NRF_NVMC->CONFIG     =   ( NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos );
                while ( NRF_NVMC->READY == NVMC_READY_READY_Busy );                         // [ NOTE ]  This is dangerous, it can block the uC.
                                                                                            //           Insert a counter to handle that problem.
            }
            else
            {
            // Write my desired value
                NRF_NVMC->CONFIG     =   ( NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos );
                while ( NRF_NVMC->READY == NVMC_READY_READY_Busy );                         // [ NOTE ]  This is dangerous, it can block the uC.
                                                                                            //           Insert a counter to handle that problem.

                *myPageAddress       =   myValue;
                NRF_NVMC->CONFIG     =   ( NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos );
                while ( NRF_NVMC->READY == NVMC_READY_READY_Busy );                         // [ NOTE ]  This is dangerous, it can block the uC.
                                                                                            //           Insert a counter to handle that problem.
            }

            writeNVMC                =   NO;
            NRF_GPIO->OUTSET         =   ( 1UL << LED1 );
        }
    }
}
