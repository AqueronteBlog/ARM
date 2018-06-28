/**
 * @brief       main.c
 * @details     It writes the value 0x23232323 into NRF51 non-volatile memory. Every 125ms,
 *              the system will check if the value 0x23232323 is stored in a specific memory
 *              location, if so, it will erase that location, if not, it will write that value.
 *
 *              This firmware is just an example about how to use the NVMC on the nrf52832. The system
 *              will handle everything on the Interrupts ( Low power mode selected ).
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/April/2018
 * @version     16/April/2018    The ORIGIN
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
uint32_t writeNVMC;       /*!<   writeNVMC = YES:    Write on NVMC.
                                 writeNVMC = NO:     Do nothing.    */


/**@brief Function for application main entry.
 */
int main(void)
{
    uint32_t myPageNumber         =  ( NRF_FICR->CODESIZE - 1 ); 
    //uint32_t *myPageAddress       =  ( uint32_t * ) ( myPageNumber * NRF_FICR->CODEPAGESIZE );
    uint32_t *myPageAddress       =  ( uint32_t * ) 0x10001088 + 12;
    uint32_t myValue              =  0x23232323;


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


/**
 * @}
 */
