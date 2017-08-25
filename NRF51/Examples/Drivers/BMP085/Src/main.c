/**
 * @brief       main.c
 * @details     This example shows how to work with the external device BPM085 a Digital
 *              Pressure Sensor.
 *
 *              It transmits the compensated temperature and pressure every 1s thought the UART.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        24/August/2017
 * @version     24/August/2017    The ORIGIN
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
#include "BMP085.h"


int main( void )
{
    uint32_t aux           =       0;
    uint8_t  myTX_buff[]   =      { 0, 0, 0, 0, 0, 0 };

    Vector_cal_coeff_t          myCalCoeff;
    Vector_temp_f               myUT;
    Vector_pressure_f           myUP;
    Vector_compensated_data_f   myTrueData;

    conf_GPIO   ();
    conf_UART   ();
    conf_TWI0   ();
    conf_TIMER0 ();


    aux = BMP085_GetCalibrationCoefficients  ( NRF_TWI0, BMP085_ADDRESS, &myCalCoeff );


    mySTATE                  =   1;                 // Reset counter

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
        //default:
        case 1:
            aux = BMP085_TriggerTemperature ( NRF_TWI0, BMP085_ADDRESS );
            break;

        case 2:
            aux = BMP085_ReadRawTemperature ( NRF_TWI0, BMP085_ADDRESS, &myUT );
            aux = BMP085_TriggerPressure ( NRF_TWI0, BMP085_ADDRESS, PRESSURE_STANDARD_MODE );
            break;
        case 3:
            aux = BMP085_ReadRawPressure ( NRF_TWI0, BMP085_ADDRESS, &myUP );

            myTrueData = BMP085_CalculateCompensated_Temperature_Pressure ( myCalCoeff, myUT, myUP, PRESSURE_STANDARD_MODE );
            // Start transmitting through the UART
            NRF_GPIO->OUTCLR             =   ( 1UL << LED1 );       // Turn the LED1 on

            // X-axis
            myTX_buff[0]                 =   ( myTrueData.Temperature & 0xFF );             // LSB Temperature
            myTX_buff[1]                 =   ( ( myTrueData.Temperature >> 8 ) & 0xFF );    // MSB Temperature
            // Y-axis
            myTX_buff[2]                 =   ( myTrueData.Pressure & 0xFF );                // LSB Pressure
            myTX_buff[3]                 =   ( ( myTrueData.Pressure >> 8 ) & 0xFF );
            // Z-axis
            myTX_buff[4]                 =   ( ( myTrueData.Pressure >> 16 ) & 0xFF );
            myTX_buff[5]                 =   ( ( myTrueData.Pressure >> 24 ) & 0xFF );      // MSB Pressure

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
