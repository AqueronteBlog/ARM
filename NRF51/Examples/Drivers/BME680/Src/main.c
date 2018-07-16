/**
 * @brief       main.c
 * @details     This example shows how to work with the external sensor BME680, it takes
 *              a new measurement as fast as when new data is ready. The driver for the BME680
 *              device is provided by Bosh, so this example shows how to adapt that driver
 *              to nrf51 platform as well.
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
#include <stdio.h>

#include "nrf.h"
#include "nrf_delay.h"
#include "ble.h"
#include "board.h"
#include "variables.h"
#include "functions.h"
#include "bme680_port.h"


/**@brief CONSTANTS.
 */
#define TX_BUFF_SIZE  64                                    /*!<   UART buffer size                               */



/**@brief VARIABLES.
 */
volatile uint8_t            myMessage[ TX_BUFF_SIZE ];      /*!<   Message to be transmitted through the UART     */
volatile uint8_t            *myPtr;                         /*!<   Pointer to point out myMessage                 */
volatile I2C_parameters_t   myBME680_I2C_parameters;




/**@brief FUNCTION FOR APPLICATION MAIN ENTRY.
 */
int main( void )
{
    BME680_status_t             aux;


    conf_GPIO   ();
    conf_UART   ();



    // I2C definition
    myBME680_I2C_parameters.TWIinstance =    NRF_TWI0;
    myBME680_I2C_parameters.SDA         =    TWI0_SDA;
    myBME680_I2C_parameters.SCL         =    TWI0_SCL;
    myBME680_I2C_parameters.ADDR        =    BME680_I2C_ADDR_PRIMARY;
    myBME680_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
    myBME680_I2C_parameters.SDAport     =    NRF_GPIO;
    myBME680_I2C_parameters.SCLport     =    NRF_GPIO;

    // Configure I2C peripheral
    aux  =   BME680_Init_I2C ( myBME680_I2C_parameters );



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


    uint8_t set_required_settings;

    /* Set the temperature, pressure and humidity settings */
    gas_sensor.tph_sett.os_hum = BME680_OS_2X;
    gas_sensor.tph_sett.os_pres = BME680_OS_4X;
    gas_sensor.tph_sett.os_temp = BME680_OS_8X;
    gas_sensor.tph_sett.filter = BME680_FILTER_SIZE_3;

    /* Set the remaining gas sensor settings and link the heating profile */
    gas_sensor.gas_sett.run_gas = BME680_ENABLE_GAS_MEAS;
    /* Create a ramp heat waveform in 3 steps */
    gas_sensor.gas_sett.heatr_temp = 320; /* degree Celsius */
    gas_sensor.gas_sett.heatr_dur = 150; /* milliseconds */

    /* Select the power mode */
    /* Must be set before writing the sensor configuration */
    gas_sensor.power_mode = BME680_FORCED_MODE;

    /* Set the required sensor settings needed */
    set_required_settings = BME680_OST_SEL | BME680_OSP_SEL | BME680_OSH_SEL | BME680_FILTER_SEL | BME680_GAS_SENSOR_SEL;

    /* Set the desired sensor configuration */
    rslt = bme680_set_sensor_settings(set_required_settings,&gas_sensor);

    /* Set the power mode */
    rslt = bme680_set_sensor_mode(&gas_sensor);


    /* Get the total measurement duration so as to sleep or wait till the
     * measurement is complete */
    uint16_t meas_period;
    bme680_get_profile_dur(&meas_period, &gas_sensor);

    struct bme680_field_data data;



    while( 1 )
    {
        /* Delay till the measurement is ready */
        user_delay_ms(meas_period);

        NRF_GPIO->OUTCLR             =   ( 1UL << LED1 );       // Turn the LED1 on


        rslt = bme680_get_sensor_data(&data, &gas_sensor);


        /* Prepare the data to be sent through the UART. NOTE: sprintf does NOT allow float numbers, that is why we round the number and plot them as integer  */
        /* Avoid using measurements from an unstable heating setup */
        if ( data.status & BME680_GASM_VALID_MSK )
        {
            sprintf ( (char*)myMessage, "T: %d degC, P: %d hPa, H %d %%rH, G: %ld ohms\r\n", (int)( 0.5 + ( data.temperature/100.0f ) ), (int)( 0.5 + ( data.pressure / 100.0f ) ), (int)( 0.5 + ( data.humidity / 1000.0f ) ), data.gas_resistance );
        }
        else
        {
            sprintf ( (char*)myMessage, "T: %d degC, P: %d hPa, H %d %%rH\r\n", (int)( 0.5 + ( data.temperature/100.0f ) ), (int)( 0.5 + ( data.pressure / 100.0f ) ), (int)( data.humidity / 1000.0f ) );
        }


        /* Send data through the UART   */
        NRF_UART0->TASKS_STOPRX  =   1;
        NRF_UART0->TASKS_STOPTX  =   1;
        myPtr                    =   &myMessage[0];

        NRF_UART0->TASKS_STARTTX =   1;
        NRF_UART0->TXD           =   *myPtr;



        /* Trigger the next measurement if you would like to read data out continuously */
        if (gas_sensor.power_mode == BME680_FORCED_MODE)
        {
            rslt = bme680_set_sensor_mode(&gas_sensor);
        }

        NRF_GPIO->OUTSET             =   ( 1UL << LED1 );       // Turn the LED1 off
        //__NOP();
    }
}
