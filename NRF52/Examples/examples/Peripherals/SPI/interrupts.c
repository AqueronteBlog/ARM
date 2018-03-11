/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/March/2018
 * @version     10/March/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "interrupts.h"



/**
 * @brief       void TIMER0_IRQHandler ()
 * @details     Timer interruption. Checks if there is an interruption
 *              of Timer0 and start sending data through the SPI.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/March/2018
 * @version     10/March/2018   The ORIGIN
 * @pre         The LEDs are connected like Common Anode.
 * @warning     N/A
 */
void TIMER0_IRQHandler()
{
    if ( ( NRF_TIMER0->EVENTS_COMPARE[0] != 0 ) && ( ( NRF_TIMER0->INTENSET & TIMER_INTENSET_COMPARE0_Msk ) != 0 ) )
    {
	NRF_P0->OUTCLR =  ( 1UL << LED1 );


        NRF_TIMER0->EVENTS_COMPARE[0] = 0;                      // Clear ( flag ) compare register 0 event

        // Start a SPI's communication
        NRF_P0->OUTCLR =  ( 1UL << SPI0_CS );

        // Change the MOSI data every time
        if ( changeDataSPIToBeTX == 1 )
        {
            changeDataSPIToBeTX  =   0;
            NRF_SPI0->TXD        =   0x01;
        }
        else
        {
            changeDataSPIToBeTX  =   1;
            NRF_SPI0->TXD        =   0x10;
        }
    }
}


/**
 * @brief       void SPI0_TWI0_IRQHandler ()
 * @details     Every time a data is sent, a byte has to be read in return.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/March/2018
 * @version     10/March/2018   The ORIGIN
 * @pre         The LEDs are connected like Common Anode.
 * @warning     N/A
 */
void SPI0_TWI0_IRQHandler()
{
    if ( ( NRF_SPI0->EVENTS_READY != 0 ) && ( ( NRF_SPI0->INTENSET & SPI_INTENCLR_READY_Msk ) != 0 ) )
    {
        mySPI_RX         =   ( NRF_SPI0->RXD & 0xFF );  // Dummy value

        // All data was transmitted
        NRF_P0->OUTSET =   ( 1UL << SPI0_CS );          // End communication
        NRF_P0->OUTSET =   ( 1UL << LED1 );             // Turn the LED1 off


        NRF_SPI0->EVENTS_READY = 0;                     // Clear ( flag )
    }
}




/**
 * @brief       void SPI1_TWI1_IRQHandler ()
 * @details     It changes the byte to be transmitted every time that a SPI
 *              transaction starts.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/March/2018
 * @version     10/March/2018   The ORIGIN
 * @pre         The LED3 is connected like Common Anode.
 * @warning     N/A
 */
void SPI1_TWI1_IRQHandler()
{
    // Check for SPI semaphore acquired event.
    if ( ( NRF_SPIS1->EVENTS_ACQUIRED != 0 ) && ( ( NRF_SPIS1->INTENSET & SPIS_INTENSET_ACQUIRED_Msk ) != 0 ) )
    {
        NRF_P0->OUTCLR =  ( 1UL << LED2 );

        NRF_SPIS1->EVENTS_ACQUIRED = 0;             // Clear ( flag ) compare register 0 event

        // It changes the MISO data depending of the previous data that was received
        if ( mySPIS_RX    ==  0x01 )
            mySPIS_TX = 0xBE;
        else
            mySPIS_TX = 0xEF;

        NRF_SPIS1->TASKS_RELEASE = 1;
    }

    // Check for SPI transaction complete event.
    if ( ( NRF_SPIS1->EVENTS_END != 0 ) && ( ( NRF_SPIS1->INTENSET & SPIS_INTENSET_END_Msk ) != 0 ) )
    {
        NRF_SPIS1->EVENTS_END = 0;                // Clear ( flag ) compare register 0 event

        NRF_P0->OUTSET =   ( 1UL << LED2 );       // Turn the LED2 off
    }
}