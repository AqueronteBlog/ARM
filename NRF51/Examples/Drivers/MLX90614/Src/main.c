/**
 * @brief       main.c
 * @details     This example shows how to work with the external sensor MLX90614 Single
 *              and Dual Zone Infra Red Thermometer.
 *
 *              Every 1 second, it reads the ambient temperature ( raw ), object 1 and object 2
 *              temperature ( raw)  as well as the IDs. All data is transmitted through the UART.
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
    uint8_t  myTX_buff[14]   =      { 0 };


    I2C_parameters_t            myMLX90614_I2C_parameters;
    MLX90614_status_t           aux;
    MLX90614_vector_data_t      myMLX90614Data;


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

    while (1)
    {
        aux  =   MLX90614_GetID_Numbers ( myMLX90614_I2C_parameters, &myMLX90614Data );
    }


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


        NRF_GPIO->OUTCLR             =   ( 1UL << LED1 );       // Turn the LED1 on
        if ( mySTATE == 1 )
        {
            NVIC_DisableIRQ ( TIMER0_IRQn );                                            // Timer Interrupt DISABLED

            // Get the data
            aux  =   MLX90614_GetID_Numbers ( myMLX90614_I2C_parameters, &myMLX90614Data );
            aux  =   MLX90614_ReadRawTA     ( myMLX90614_I2C_parameters, &myMLX90614Data );
            aux  =   MLX90614_ReadRawTObj1  ( myMLX90614_I2C_parameters, &myMLX90614Data );
            aux  =   MLX90614_ReadRawTObj2  ( myMLX90614_I2C_parameters, &myMLX90614Data );

            // Parse the data
            myTX_buff[0]                 =   ( myMLX90614Data.RawTA >> 8 ) & 0xFF;     // MSB Raw TA
            myTX_buff[1]                 =   myMLX90614Data.RawTA & 0xFF;              // LSB Raw TA

            myTX_buff[2]                 =   ( myMLX90614Data.RawTObj1 >> 8 ) & 0xFF;  // MSB Raw Tobj1
            myTX_buff[3]                 =   myMLX90614Data.RawTObj1 & 0xFF;           // LSB Raw Tobj1

            myTX_buff[4]                 =   ( myMLX90614Data.RawTObj2 >> 8 ) & 0xFF;  // MSB Raw Tobj2
            myTX_buff[5]                 =   myMLX90614Data.RawTObj2 & 0xFF;           // LSB Raw Tobj2

            myTX_buff[6]                 =   ( myMLX90614Data.ID[0] >> 8 ) & 0xFF;     // MSB ID[0]
            myTX_buff[7]                 =   myMLX90614Data.ID[0] & 0xFF;              // LSB ID[0]

            myTX_buff[8]                 =   ( myMLX90614Data.ID[1] >> 8 ) & 0xFF;     // MSB ID[1]
            myTX_buff[9]                 =   myMLX90614Data.ID[1] & 0xFF;              // LSB ID[1]

            myTX_buff[10]                =   ( myMLX90614Data.ID[2] >> 8 ) & 0xFF;     // MSB ID[2]
            myTX_buff[11]                =   myMLX90614Data.ID[2] & 0xFF;              // LSB ID[2]

            myTX_buff[12]                =   ( myMLX90614Data.ID[3] >> 8 ) & 0xFF;     // MSB ID[3]
            myTX_buff[13]                =   myMLX90614Data.ID[3] & 0xFF;              // LSB ID[3]


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
    }
}
