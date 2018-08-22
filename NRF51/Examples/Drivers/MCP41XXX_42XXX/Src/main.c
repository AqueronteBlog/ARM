/**
 * @brief       main.c
 * @details     [todo]This example shows how to work with the external device: MCP41XXX_42XXX. Every 1 seconds, a new
 *              sample is performed and transmitted through the UART ( Baud Rate: 230400 ).
 *
 *              The rest of the time, the microcontroller is in low power.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        21/August/2018
 * @version     21/August/2018    The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     Softdevice S310 was used although the file's name is S130. The softdevice
 *              is not used in this example anyway because of Bluetooth was not used.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */
#include <stdio.h>

#include "nrf.h"
#include "nrf_delay.h"
#include "ble.h"
#include "board.h"
#include "functions.h"
#include "variables.h"
#include "MCP41XXX_42XXX.h"



/**@brief Constants.
 */
#define TX_BUFF_SIZE  64                          /*!<   UART buffer size                                       */


/**@brief Variables.
 */
volatile uint32_t myState;                        /*!<   State that indicates when to perform an ADC sample     */
volatile uint8_t  myMessage[ TX_BUFF_SIZE ];      /*!<   Message to be transmitted through the UART             */
volatile uint8_t  *myPtr;                         /*!<   Pointer to point out myMessage                         */



/**@brief Function for application main entry.
 */
int main( void )
{
    uint32_t                        myTrimState  =   0;
    SPI_parameters_t                myMCP41XXX_42XXX_SPI_parameters;
    MCP41XXX_42XXX_status_t         aux;
    MCP41XXX_42XXX_vector_data_t    myMCP41XXX_42XXX_Data;


    conf_CLK    ();
    conf_GPIO   ();
    conf_UART   ();
    conf_TIMER0 ();



    /* SPI definition */
    myMCP41XXX_42XXX_SPI_parameters.SPIinstance         =    NRF_SPI0;
    myMCP41XXX_42XXX_SPI_parameters.MOSI                =    SPI0_MOSI;
    myMCP41XXX_42XXX_SPI_parameters.MISO                =    SPI0_MISO;
    myMCP41XXX_42XXX_SPI_parameters.SCLK                =    SPI0_SCK;
    myMCP41XXX_42XXX_SPI_parameters.CS                  =    SPI0_CS;
    myMCP41XXX_42XXX_SPI_parameters.Freq                =    SPI_FREQUENCY_FREQUENCY_M1;
    myMCP41XXX_42XXX_SPI_parameters.MISOport            =    NRF_GPIO;
    myMCP41XXX_42XXX_SPI_parameters.MOSIport            =    NRF_GPIO;
    myMCP41XXX_42XXX_SPI_parameters.SCLKport            =    NRF_GPIO;
    myMCP41XXX_42XXX_SPI_parameters.CSport              =    NRF_GPIO;
    myMCP41XXX_42XXX_SPI_parameters.SPIbyte_order       =    SPI_ORDER_MSB_FIRST;
    myMCP41XXX_42XXX_SPI_parameters.SPImode             =    SPI_MODE_0;
    myMCP41XXX_42XXX_SPI_parameters.SPIenable_line_mode =    SPI_ENABLE_LINE_LOW;

    /* Configure SPI peripheral */
    aux  =   MCP41XXX_42XXX_Init            ( myMCP41XXX_42XXX_SPI_parameters );





    myState  =   0;                             // Reset the variable
    NRF_TIMER0->TASKS_START  =   1;             // Start Timer0

    //NRF_POWER->SYSTEMOFF = 1;
    NRF_POWER->TASKS_LOWPWR  =   1;             // Sub power mode: Low power.
    while( 1 )
    {
        /* Enter System ON sleep mode   */
    	__WFE();
    	/* Make sure any pending events are cleared */
    	__SEV();
    	__WFE();


    	NRF_GPIO->OUTCLR             |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );          // Turn all the LEDs on
        if ( myState == 1 )
        {
            /* Change the wiper value */
            switch ( myTrimState )
            {
                case 0:
                    /* Wiper value 0%    */
                    myMCP41XXX_42XXX_Data.Dn     =   0x00;
                    aux  =   MCP41XXX_42XXX_SetWiper ( myMCP41XXX_42XXX_SPI_parameters, MCP41XXX_42XXX_POTENTIOMETER_COMMAND_POTENTIOMETER_0, myMCP41XXX_42XXX_Data );
                    myTrimState  =   50;
                    break;

                default:
                case 50:
                    /* Wiper value 50%    */
                    myMCP41XXX_42XXX_Data.Dn     =   0x80;
                    aux  =   MCP41XXX_42XXX_SetWiper ( myMCP41XXX_42XXX_SPI_parameters, MCP41XXX_42XXX_POTENTIOMETER_COMMAND_POTENTIOMETER_0, myMCP41XXX_42XXX_Data );
                    myTrimState  =   100;
                    break;

                case 100:
                    /* Wiper value 100%    */
                    myMCP41XXX_42XXX_Data.Dn     =   0xFF;
                    aux  =   MCP41XXX_42XXX_SetWiper ( myMCP41XXX_42XXX_SPI_parameters, MCP41XXX_42XXX_POTENTIOMETER_COMMAND_POTENTIOMETER_0, myMCP41XXX_42XXX_Data );
                    myTrimState  =   0;
                    break;
            }


            /* Reset the variables   */
            myState             =   0;
    	}

        NRF_GPIO->OUTSET             |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );          // Turn all the LEDs off
        //__NOP();
    }
}
