/**
 * @brief       main.c
 * @details     This example works with the external external device: ADXL345,
 *              3-Axis, ±2 g/±4 g/±8 g/±16 g Digital Accelerometer.
 *
 *              It gets a new measurement every 1s and transmits the data thought the UART.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        11/August/2017
 * @version     18/August/2017    All functions tested and final example ready.
 *              11/August/2017    The ORIGIN
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
#include "ADXL345.h"


int main( void )
{
    uint32_t aux           =       0;
    uint8_t  myTX_buff[]   =      { 0, 0, 0, 0, 0, 0 };

    Vector_t                    myXYZVector, *myXYZptr = &myXYZVector;


    conf_GPIO   ();
    conf_UART   ();
    conf_TWI0   ();
    conf_TIMER0 ();


    ADXL345_Init   ( NRF_TWI0, ADXL345_ALT_ADDRESS_LOW, BW_RATE_LOW_POWER_Disabled, BW_RATE_RATE_100HZ,
                     DATA_FORMAT_INT_INVERT_Disabled, DATA_FORMAT_FULL_RES_Enabled, DATA_FORMAT_JUSTIFY_Disabled,
                     DATA_FORMAT_RANGE_4_G );


    ADXL345_PowerMode ( NRF_TWI0, ADXL345_ALT_ADDRESS_LOW, MEASURE_MODE );


    mySTATE                  =   0;                 // Reset counter

    NRF_TIMER0->TASKS_START  =   1;                 // Start Timer0


    while( 1 )
    {
        //NRF_POWER->SYSTEMOFF = 1;
        NRF_POWER->TASKS_LOWPWR = 1;                // Sub power mode: Low power.

        // Enter System ON sleep mode
		__WFE();
		// Make sure any pending events are cleared
		__SEV();
		__WFE();

		switch ( mySTATE ){
        default:
        case 1:
            aux = ADXL345_ReadRawData       ( NRF_TWI0, ADXL345_ALT_ADDRESS_LOW, &myXYZptr[0] );
            break;

        case 2:
            // Start transmitting through the UART
            NRF_GPIO->OUTCLR             =   ( 1UL << LED1 );       // Turn the LED1 on

            // X-axis
            myTX_buff[0]                 =   ( myXYZVector.XAxis & 0xFF );
            myTX_buff[1]                 =   ( ( myXYZVector.XAxis >> 8 ) & 0xFF );
            // Y-axis
            myTX_buff[2]                 =   ( myXYZVector.YAxis & 0xFF );
            myTX_buff[3]                 =   ( ( myXYZVector.YAxis >> 8 ) & 0xFF );
            // Z-axis
            myTX_buff[4]                 =   ( myXYZVector.ZAxis & 0xFF );
            myTX_buff[5]                 =   ( ( myXYZVector.ZAxis >> 8 ) & 0xFF );

            myPtr                        =   &myTX_buff[0];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   *myPtr++;              // MSB to be transmitted

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }

            mySTATE =   0;
            break;
		}

        //__NOP();

    }
}
