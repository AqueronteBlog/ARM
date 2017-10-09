/**
 * @brief       main.c
 * @details     This example shows how to work with the external device MAX7219. It uses 8 7-Seg
 *              digits and plots from 7 to 0 on them. It will change the DP status every 1 second.
 *
 *              The rest of the time, the system remains in low power.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        28/September/2017
 * @version     9/October/2017           The whole firmware.
 *              28/September/2017        The ORIGIN
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
#include "MAX7219.h"


int main( void )
{
    uint32_t                i    =   0;

    MAX7219_status_t        mySPI_status;
    SPI_parameters_t        myMAX7219_SPI_parameters;


    conf_GPIO   ();
    conf_TIMER0 ();



    // SPI definition
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


    // Configure SPI and put the device in shutdown mode
    mySPI_status    =    MAX7219_Init        ( myMAX7219_SPI_parameters );
    nrf_delay_us ( 10 );

    // BCD code ON
    mySPI_status    =    MAX7219_DecodeMode  ( myMAX7219_SPI_parameters, DECODE_DIGITS_7_0 );
    nrf_delay_us ( 10 );

    // 7 digits available
    mySPI_status    =    MAX7219_SetScanLimit( myMAX7219_SPI_parameters, DISPLAY_DIGIT_0_1_2_3_4_5_6_7 );
    nrf_delay_us ( 10 );

    // Configure the intensity
    mySPI_status    =    MAX7219_SetIntensity( myMAX7219_SPI_parameters, DUTY_CICLE_9_32 );
    nrf_delay_us ( 10 );

    // Clear all the digits
    for ( i = SET_DIGIT_0; i <= SET_DIGIT_7; i++ )
    {
        mySPI_status    =    MAX7219_SetDigit ( myMAX7219_SPI_parameters, i, CHARACTER_BLANK, DP_DISABLED );
        nrf_delay_us ( 10 );
    }

    // Test Mode Enabled: All displays ON
    mySPI_status    =    MAX7219_DisplayTest ( myMAX7219_SPI_parameters, DISPLAY_TEST_MODE );
    nrf_delay_ms ( 2500 );

    // Test Mode Disabled
    mySPI_status    =    MAX7219_DisplayTest ( myMAX7219_SPI_parameters, DISPLAY_NORMAL_OPERATION );
    nrf_delay_us ( 10 );

    // Device in normal operation mode
    mySPI_status    =    MAX7219_Mode        ( myMAX7219_SPI_parameters, NORMAL_OPERATION );



    NRF_TIMER0->TASKS_START = 1;            // Start Timer0

    while ( 1 )
    {
        //NRF_POWER->SYSTEMOFF = 1;
        NRF_POWER->TASKS_LOWPWR = 1;        // Sub power mode: Low power.

        // Enter System ON sleep mode
        __WFE();
        // Make sure any pending events are cleared
        __SEV();
        __WFE();


        // Change the DP status on the digits
        NRF_GPIO->OUTCLR    =   ( 1UL << LED1 );            // Turn the LED 1 on

        if ( changeDP_status == ON )
        {
        // DP OFF
            mySPI_status    =    MAX7219_SetDigit ( myMAX7219_SPI_parameters, SET_DIGIT_0, CHARACTER_0, DP_DISABLED );
            nrf_delay_us ( 10 );
            mySPI_status    =    MAX7219_SetDigit ( myMAX7219_SPI_parameters, SET_DIGIT_1, CHARACTER_1, DP_DISABLED );
            nrf_delay_us ( 10 );
            mySPI_status    =    MAX7219_SetDigit ( myMAX7219_SPI_parameters, SET_DIGIT_2, CHARACTER_2, DP_DISABLED );
            nrf_delay_us ( 10 );
            mySPI_status    =    MAX7219_SetDigit ( myMAX7219_SPI_parameters, SET_DIGIT_3, CHARACTER_3, DP_DISABLED );
            nrf_delay_us ( 10 );
            mySPI_status    =    MAX7219_SetDigit ( myMAX7219_SPI_parameters, SET_DIGIT_4, CHARACTER_4, DP_DISABLED );
            nrf_delay_us ( 10 );
            mySPI_status    =    MAX7219_SetDigit ( myMAX7219_SPI_parameters, SET_DIGIT_5, CHARACTER_5, DP_DISABLED );
            nrf_delay_us ( 10 );
            mySPI_status    =    MAX7219_SetDigit ( myMAX7219_SPI_parameters, SET_DIGIT_6, CHARACTER_6, DP_DISABLED );
            nrf_delay_us ( 10 );
            mySPI_status    =    MAX7219_SetDigit ( myMAX7219_SPI_parameters, SET_DIGIT_7, CHARACTER_7, DP_DISABLED );
        }
        else
        {
        // DP ON
            mySPI_status    =    MAX7219_SetDigit ( myMAX7219_SPI_parameters, SET_DIGIT_0, CHARACTER_0, DP_ENABLED );
            nrf_delay_us ( 10 );
            mySPI_status    =    MAX7219_SetDigit ( myMAX7219_SPI_parameters, SET_DIGIT_1, CHARACTER_1, DP_ENABLED );
            nrf_delay_us ( 10 );
            mySPI_status    =    MAX7219_SetDigit ( myMAX7219_SPI_parameters, SET_DIGIT_2, CHARACTER_2, DP_ENABLED );
            nrf_delay_us ( 10 );
            mySPI_status    =    MAX7219_SetDigit ( myMAX7219_SPI_parameters, SET_DIGIT_3, CHARACTER_3, DP_ENABLED );
            nrf_delay_us ( 10 );
            mySPI_status    =    MAX7219_SetDigit ( myMAX7219_SPI_parameters, SET_DIGIT_4, CHARACTER_4, DP_ENABLED );
            nrf_delay_us ( 10 );
            mySPI_status    =    MAX7219_SetDigit ( myMAX7219_SPI_parameters, SET_DIGIT_5, CHARACTER_5, DP_ENABLED );
            nrf_delay_us ( 10 );
            mySPI_status    =    MAX7219_SetDigit ( myMAX7219_SPI_parameters, SET_DIGIT_6, CHARACTER_6, DP_ENABLED );
            nrf_delay_us ( 10 );
            mySPI_status    =    MAX7219_SetDigit ( myMAX7219_SPI_parameters, SET_DIGIT_7, CHARACTER_7, DP_ENABLED );
        }

        NRF_GPIO->OUTSET    =   ( 1UL << LED1 );            // Turn the LED 1 off
    }
}
