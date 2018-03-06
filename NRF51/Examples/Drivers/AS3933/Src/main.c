/**
 * @brief       main.c
 * @details     [TODO].
 *
 *              The rest of the time, the microcontroller is in low power.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        22/February/2018
 * @version     22/February/2018    The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     Softdevice S310 was used although the file's name is S130. The softdevice
 *              is not used in this example anyway because of Bluetooth was not used.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "nrf.h"
#include "nrf_delay.h"
#include "ble.h"
#include "variables.h"
#include "functions.h"
#include "AS3933.h"


int main( void )
{
    SPI_parameters_t    myAS3933_SPI_parameters;
    AS3933_status_t     aux;
    AS3933_data_t       myAS3933_data;


    conf_GPIO   ();
    //conf_UART   ();
    //conf_TIMER0 ();


    // SPI definition
    myAS3933_SPI_parameters.SPIinstance         =    NRF_SPI0;
    myAS3933_SPI_parameters.MOSI                =    SPI0_MOSI;
    myAS3933_SPI_parameters.MISO                =    SPI0_MISO;
    myAS3933_SPI_parameters.SCLK                =    SPI0_SCK;
    myAS3933_SPI_parameters.CS                  =    SPI0_CS;
    myAS3933_SPI_parameters.Freq                =    SPI_FREQUENCY_FREQUENCY_M1;
    myAS3933_SPI_parameters.MISOport            =    NRF_GPIO;
    myAS3933_SPI_parameters.MOSIport            =    NRF_GPIO;
    myAS3933_SPI_parameters.SCLKport            =    NRF_GPIO;
    myAS3933_SPI_parameters.CSport              =    NRF_GPIO;
    myAS3933_SPI_parameters.SPIbyte_order       =    SPI_ORDER_MSB_FIRST;
    myAS3933_SPI_parameters.SPImode             =    SPI_MODE_1;
    myAS3933_SPI_parameters.SPIenable_line_mode =    SPI_ENABLE_LINE_HIGH;



    // Configure SPI peripheral
    aux  =   AS3933_Init ( myAS3933_SPI_parameters );

    myAS3933_data.patt1b     =   TS1_WAKEUP_PATTERN_PATT1B;
    myAS3933_data.patt2b     =   TS2_WAKEUP_PATTERN_PATT2B;
    aux  =   AS3933_SetWakeUpPattern    ( myAS3933_SPI_parameters, myAS3933_data );
    aux  =   AS3933_GetWakeUpPattern    ( myAS3933_SPI_parameters, &myAS3933_data );



    mySTATE  =   0;                                 // Reset the variable

    //NRF_TIMER0->TASKS_START  =   1;                 // Start Timer0

    while( 1 )
    {
        //NRF_POWER->SYSTEMOFF = 1;
        NRF_POWER->TASKS_LOWPWR = 1;                // Sub power mode: Low power.

        // Enter System ON sleep mode
        __WFE();
        // Make sure any pending events are cleared
        __SEV();
        __WFE();


        NRF_GPIO->OUTCLR             =   ( 1UL << LED1 );       // Turn the LED1 on
//        if ( mySTATE == 1 )
//        {
//            NVIC_DisableIRQ ( TIMER0_IRQn );                                            // Timer Interrupt DISABLED
//
//            // Trigger a new temperature conversion
//            aux  =   AS3933_StartConvertTemperature ( myAS3933_I2C_parameters );
//
//            // Wait until the temperature conversion is completed or timeout
//            myTimeoOut   =   232323;
//            do{
//                aux  =   AS3933_IsTemperatureConversionDone ( myAS3933_I2C_parameters, &myAS3933_TempConversionStatus );
//                myTimeoOut--;
//            } while ( ( ( myAS3933_TempConversionStatus & ACCESS_CONFIG_DONE_MASK ) != ACCESS_CONFIG_DONE_CONVERSION_COMPLETE ) && ( myTimeoOut > 0 ) );
//
//            // Check if TimeOut, if so, there was an error ( send: NA ), send the data otherwise
//            if ( myTimeoOut <= 0 )
//            {
//                myTX_buff[0]                 =   'N';
//                myTX_buff[1]                 =   'A';
//            }
//            else
//            {
//                //aux  =   AS3933_ReadTemperature    ( myAS3933_I2C_parameters, &myAS3933_data );
//                aux  =   AS3933_ReadRawTemperature ( myAS3933_I2C_parameters, &myAS3933_data );
//
//                myTX_buff[0]                 =   myAS3933_data.MSBTemperature;
//                myTX_buff[1]                 =   myAS3933_data.LSBTemperature;
//            }
//
//
//            myPtr                        =   &myTX_buff[0];
//            TX_inProgress                =   YES;
//            NRF_UART0->TASKS_STARTTX     =   1;
//            NRF_UART0->TXD               =   *myPtr++;                                   // Start transmission
//
//            // Wait until the message is transmitted
//            while ( TX_inProgress == YES )
//            {
//                __WFE();
//                // Make sure any pending events are cleared
//                __SEV();
//                __WFE();
//            }
//
//
//            mySTATE             =   0;
//            NVIC_EnableIRQ ( TIMER0_IRQn );                                              // Timer Interrupt ENABLED
//        }
        NRF_GPIO->OUTSET             =   ( 1UL << LED1 );       // Turn the LED1 off
        //__NOP();
    }
}
