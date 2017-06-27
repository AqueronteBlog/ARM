/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        27/June/2017
 * @version     27/June/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "interrupts.h"


/**
 * @brief       void SPI0_IRQHandler ()
 * @details     [TODO] XXX.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        27/June/2017
 * @version     27/June/2017   The ORIGIN
 * @pre         The LEDs are connected like Common Anode.
 * @warning     NaN
 */
void SPI0_IRQHandler()
{
    if ( ( NRF_SPI0->EVENTS_READY != 0 ) && ( ( NRF_SPI0->INTENSET & SPI_INTENCLR_READY_Msk ) != 0 ) )
    {
        mySPI_RX         =   ( NRF_SPI0->RXD & 0xFF );  // Dummy value

        // All data was transmitted
        NRF_GPIO->OUTSET =   ( 1UL << SPI0_CS );        // End communication
        NRF_GPIO->OUTSET =   ( 1UL << LED1 );           // Turn the LED1 off


        NRF_SPI0->EVENTS_READY = 0;                     // Clear ( flag )
    }
}




/**
 * @brief       void SPIS1_IRQHandler ()
 * @details     [TODO] XXX
 *
 *
 * @return      NaN
 *
 * @author      Manuel Caballero
 * @date        27/June/2017
 * @version     27/June/2017   The ORIGIN
 * @pre         The LED3 is connected like Common Anode.
 * @warning     NaN
 */
void SPIS1_IRQHandler()
{
    // Check for SPI semaphore acquired event.
    if ( NRF_SPIS1->EVENTS_ACQUIRED != 0 )
    {
        NRF_SPIS1->EVENTS_ACQUIRED = 0;                 // Clear ( flag ) compare register 0 event

        /*
        switch (m_spi_state)
        {
            case SPI_BUFFER_RESOURCE_REQUESTED:
                NRF_SPIS1->TXDPTR = (uint32_t)mp_spi_tx_buf;
                NRF_SPIS1->RXDPTR = (uint32_t)mp_spi_rx_buf;
                NRF_SPIS1->MAXRX  = m_spi_rx_buf_size;
                NRF_SPIS1->MAXTX  = m_spi_tx_buf_size;

                NRF_SPIS1->TASKS_RELEASE = 1u;

                sm_state_change(SPI_BUFFER_RESOURCE_CONFIGURED);
                break;

            default:
                // No implementation required.
                break;
        }
        */
    }

    // Check for SPI transaction complete event.
    if (NRF_SPIS1->EVENTS_END != 0)
    {
        NRF_SPIS1->EVENTS_END = 0;                  // Clear ( flag ) compare register 0 event

        /*
        switch (m_spi_state)
        {
            case SPI_BUFFER_RESOURCE_CONFIGURED:
                sm_state_change(SPI_XFER_COMPLETED);
                break;

            default:
                // No implementation required.
                break;
        }
        */
    }
}
