/**
 * @brief       main.c
 * @details     [TODO].
 *
 *              The rest of the time, the microcontroller is in low power.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        13/February/2018
 * @version     13/February/2018    The ORIGIN
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
#include "bme680_port.h"


volatile I2C_parameters_t   myBME680_I2C_parameters;


/**@brief FUNCTION FOR APPLICATION MAIN ENTRY.
 */
int main( void )
{
    uint8_t  myTX_buff[2]     =   { 0 };



    BME680_status_t             aux;


    conf_GPIO   ();
    conf_UART   ();
    conf_TIMER0 ();



    // I2C definition
    myBME680_I2C_parameters.TWIinstance =    NRF_TWI0;
    myBME680_I2C_parameters.SDA         =    TWI0_SDA;
    myBME680_I2C_parameters.SCL         =    TWI0_SCL;
    myBME680_I2C_parameters.ADDR        =    BME680_I2C_ADDR_PRIMARY;
    myBME680_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
    myBME680_I2C_parameters.SDAport     =    NRF_GPIO;
    myBME680_I2C_parameters.SCLport     =    NRF_GPIO;

    // Configure I2C peripheral
    aux  =   BME680_Init ( myBME680_I2C_parameters );



    struct bme680_dev gas_sensor;

    gas_sensor.dev_id   =   BME680_I2C_ADDR_PRIMARY;
    gas_sensor.intf     =   BME680_I2C_INTF;
    gas_sensor.read     =   user_i2c_read;
    gas_sensor.write    =   user_i2c_write;
    gas_sensor.delay_ms =   user_delay_ms;
    /* amb_temp can be set to 25 prior to configuring the gas sensor
     * or by performing a few temperature readings without operating the gas sensor.
     */
    gas_sensor.amb_temp =   25;


    int8_t rslt = BME680_OK;
    rslt = bme680_init(&gas_sensor);

    mySTATE  =   0;                                 // Reset the variable

    NRF_TIMER0->TASKS_START  =   1;                 // Start Timer0


    //NRF_POWER->SYSTEMOFF = 1;
    NRF_POWER->TASKS_LOWPWR = 1;                // Sub power mode: Low power.
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

//            // Trigger a new temperature conversion
//            aux  =   BME680_StartConvertTemperature ( myBME680_I2C_parameters );
//
//            // Wait until the temperature conversion is completed or timeout
//            myTimeoOut   =   232323;
//            do{
//                aux  =   BME680_IsTemperatureConversionDone ( myBME680_I2C_parameters, &myBME680_TempConversionStatus );
//                myTimeoOut--;
//            } while ( ( ( myBME680_TempConversionStatus & ACCESS_CONFIG_DONE_MASK ) != ACCESS_CONFIG_DONE_CONVERSION_COMPLETE ) && ( myTimeoOut > 0 ) );
//
//            // Check if TimeOut, if so, there was an error ( send: NA ), send the data otherwise
//            if ( myTimeoOut <= 0 )
//            {
//                myTX_buff[0]                 =   'N';
//                myTX_buff[1]                 =   'A';
//            }
//            else
//            {
//                //aux  =   BME680_ReadTemperature    ( myBME680_I2C_parameters, &myBME680_data );
//                aux  =   BME680_ReadRawTemperature ( myBME680_I2C_parameters, &myBME680_data );
//
//                myTX_buff[0]                 =   myBME680_data.MSBTemperature;
//                myTX_buff[1]                 =   myBME680_data.LSBTemperature;
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
            NVIC_EnableIRQ ( TIMER0_IRQn );                                              // Timer Interrupt ENABLED
        }
        NRF_GPIO->OUTSET             =   ( 1UL << LED1 );       // Turn the LED1 off
        //__NOP();
    }
}
