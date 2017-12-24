/**
 * @brief       main.c
 * @details     [todo].
 *
 *              The rest of the time, the microcontroller is in low power.
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        23/December/2017
 * @version     23/December/2017    The ORIGIN
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
#include "MLX90614.h"


int main( void )
{
    uint8_t  myTX_buff[10]   =      { 0 };


    I2C_parameters_t            myMLX90614_I2C_parameters;
    MLX90614_status_t           aux;



    conf_GPIO   ();
    conf_UART   ();
    conf_TIMER0 ();



    // I2C definition
    myMLX90614_I2C_parameters.TWIinstance =    NRF_TWI0;
    myMLX90614_I2C_parameters.SDA         =    TWI0_SDA;
    myMLX90614_I2C_parameters.SCL         =    TWI0_SCL;
    myMLX90614_I2C_parameters.ADDR        =    MLX90614_ADDRESS;
    myMLX90614_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
    myMLX90614_I2C_parameters.SDAport     =    NRF_GPIO;
    myMLX90614_I2C_parameters.SCLport     =    NRF_GPIO;

    // Configure I2C peripheral
    aux  =   MLX90614_Init ( myMLX90614_I2C_parameters );




    mySTATE  =   0;                                 // Reset the variable

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

/*
        NRF_GPIO->OUTCLR             =   ( 1UL << LED1 );       // Turn the LED1 on
        if ( mySTATE == 1 )
        {
            NVIC_DisableIRQ ( TIMER0_IRQn );                                            // Timer Interrupt DISABLED

            // Get the data
            aux  =   MLX90614_ReadTemperature             ( myMLX90614_I2C_parameters, &myMLX90614_data );
            aux  =   MLX90614_GetDate                     ( myMLX90614_I2C_parameters, &myMLX90614_date_time );
            aux  =   MLX90614_GetTime                     ( myMLX90614_I2C_parameters, &myMLX90614_date_time );

            // Parse the data
            myTX_buff[0]                 =   myMLX90614_date_time.Century;
            myTX_buff[1]                 =   myMLX90614_date_time.Date;
            myTX_buff[2]                 =   myMLX90614_date_time.Month;
            myTX_buff[3]                 =   myMLX90614_date_time.Year;
            myTX_buff[4]                 =   myMLX90614_date_time.DayOfWeek;
            myTX_buff[5]                 =   myMLX90614_date_time.Hours;
            myTX_buff[6]                 =   myMLX90614_date_time.Minutes;
            myTX_buff[7]                 =   myMLX90614_date_time.Seconds;
            myTX_buff[8]                 =   myMLX90614_date_time.Mode_12_n24;
            myTX_buff[9]                 =   myMLX90614_date_time.Mode_nAM_PM;


            myPtr                        =   &myTX_buff[0];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   *myPtr++;                                   // Start transmission

            // Wait until the message is transmitted
            while ( TX_inProgress == YES )
            {
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            mySTATE             =   0;
            NVIC_EnableIRQ ( TIMER0_IRQn );                                              // Timer Interrupt ENABLED
        }
        NRF_GPIO->OUTSET             =   ( 1UL << LED1 );       // Turn the LED1 off
        //__NOP();
        */
    }
}
