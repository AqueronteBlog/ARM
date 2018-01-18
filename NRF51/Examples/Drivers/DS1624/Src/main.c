/**
 * @brief       main.c
 * @details     [TODO].
 *
 *              The rest of the time, the microcontroller is in low power.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        18/January/2018
 * @version     18/January/2018    The ORIGIN
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
#include "DS1624.h"


int main( void )
{
    uint8_t  myTX_buff[10]   =      { 0 };


    I2C_parameters_t            myDS3231_I2C_parameters;
//    DS3231_status_t             aux;
//    DS3231_vector_data_t        myDS3231_data;
//    DS3231_vector_date_time_t   myDS3231_date_time;
//
//
//    conf_GPIO   ();
//    conf_UART   ();
//    conf_TIMER0 ();
//
//
//
//    // I2C definition
//    myDS3231_I2C_parameters.TWIinstance =    NRF_TWI0;
//    myDS3231_I2C_parameters.SDA         =    TWI0_SDA;
//    myDS3231_I2C_parameters.SCL         =    TWI0_SCL;
//    myDS3231_I2C_parameters.ADDR        =    DS3231_ADDRESS;
//    myDS3231_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
//    myDS3231_I2C_parameters.SDAport     =    NRF_GPIO;
//    myDS3231_I2C_parameters.SCLport     =    NRF_GPIO;
//
//    // Configure I2C peripheral
//    aux  =   DS3231_Init ( myDS3231_I2C_parameters );
//
//
//    // Disable the 32kHz output pin
//    aux  =   DS3231_Status32kHzPin      ( myDS3231_I2C_parameters, STATUS_ENABLE_32KHZ_OUTPUT_DISABLED );
//
//
//    // DATE: 20/12/17  Century = 1  Wednesday ( = 3 )
//    myDS3231_date_time.Date         =   20;
//    myDS3231_date_time.Month        =   12;
//    myDS3231_date_time.Year         =   17;
//    myDS3231_date_time.Century      =   MONTH_CENTURY_MASK;
//    myDS3231_date_time.DayOfWeek    =   3;
//    aux  =   DS3231_SetDate ( myDS3231_I2C_parameters, myDS3231_date_time );
//
//
//    // TIME: 11:22:33  12h PM
//    myDS3231_date_time.Hours         =   11;
//    myDS3231_date_time.Minutes       =   22;
//    myDS3231_date_time.Seconds       =   33;
//    myDS3231_date_time.Mode_12_n24   =   HOURS_12_ENABLED;
//    myDS3231_date_time.Mode_nAM_PM   =   HOURS_PM_ENABLED;
//    aux  =   DS3231_SetTime ( myDS3231_I2C_parameters, myDS3231_date_time );


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


//        NRF_GPIO->OUTCLR             =   ( 1UL << LED1 );       // Turn the LED1 on
//        if ( mySTATE == 1 )
//        {
//            NVIC_DisableIRQ ( TIMER0_IRQn );                                            // Timer Interrupt DISABLED
//
//            // Get the data
//            aux  =   DS3231_ReadTemperature             ( myDS3231_I2C_parameters, &myDS3231_data );
//            aux  =   DS3231_GetDate                     ( myDS3231_I2C_parameters, &myDS3231_date_time );
//            aux  =   DS3231_GetTime                     ( myDS3231_I2C_parameters, &myDS3231_date_time );
//
//            // Parse the data
//            myTX_buff[0]                 =   myDS3231_date_time.Century;
//            myTX_buff[1]                 =   myDS3231_date_time.Date;
//            myTX_buff[2]                 =   myDS3231_date_time.Month;
//            myTX_buff[3]                 =   myDS3231_date_time.Year;
//            myTX_buff[4]                 =   myDS3231_date_time.DayOfWeek;
//            myTX_buff[5]                 =   myDS3231_date_time.Hours;
//            myTX_buff[6]                 =   myDS3231_date_time.Minutes;
//            myTX_buff[7]                 =   myDS3231_date_time.Seconds;
//            myTX_buff[8]                 =   myDS3231_date_time.Mode_12_n24;
//            myTX_buff[9]                 =   myDS3231_date_time.Mode_nAM_PM;
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
//        NRF_GPIO->OUTSET             =   ( 1UL << LED1 );       // Turn the LED1 off
//        //__NOP();
    }
}
