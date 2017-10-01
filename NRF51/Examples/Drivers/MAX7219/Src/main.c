/**
 * @brief       main.c
 * @details     [todo].
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        28/September/2017
 * @version     28/September/2017        The ORIGIN
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
#include "MAX7219.h"


int main( void )
{
    MAX7219_status_t            mySPI_status;
    SPI_parameters_t            myMAX7219_SPI_parameters;
    /*
    conf_GPIO   ();
    conf_SPI0   ();
    conf_SPIS1  ();
    conf_TIMER0 ();

    NRF_TIMER0->TASKS_START = 1;            // Start Timer0

*/
    myMAX7219_SPI_parameters.SPIinstance =    NRF_SPI0;
    myMAX7219_SPI_parameters.MOSI        =    SPI0_MOSI;
    myMAX7219_SPI_parameters.MISO        =    SPI0_MISO;
    myMAX7219_SPI_parameters.SCLK        =    SPI0_SCK;
    myMAX7219_SPI_parameters.CS          =    SPI0_CS;
    myMAX7219_SPI_parameters.Freq        =    SPI_FREQUENCY_FREQUENCY_M1;
    myMAX7219_SPI_parameters.MISOport    =    NRF_GPIO;
    myMAX7219_SPI_parameters.MOSIport    =    NRF_GPIO;
    myMAX7219_SPI_parameters.SCLKport    =    NRF_GPIO;
    myMAX7219_SPI_parameters.CSport      =    NRF_GPIO;

    while ( 1 ){
        mySPI_status    =    MAX7219_Init ( myMAX7219_SPI_parameters );
    }


    while( 1 )
    {
        //NRF_POWER->SYSTEMOFF = 1;
        NRF_POWER->TASKS_LOWPWR = 1;        // Sub power mode: Low power.

        // Enter System ON sleep mode
		__WFE();
		// Make sure any pending events are cleared
		__SEV();
		__WFE();
    }
}
