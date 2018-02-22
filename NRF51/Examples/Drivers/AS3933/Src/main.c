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
    uint8_t  myTX_buff[2]     =   { 0 };
    uint8_t  myDataInEEPROM[] =   { 0x23, 0x23, 0x23 };
    uint32_t myTimeoOut       =   0;


//    I2C_parameters_t            myDS1624_I2C_parameters;
//    DS1624_status_t             aux;
//    DS1624_access_config_done_t myDS1624_TempConversionStatus;
//    DS1624_vector_data_t        myDS1624_data;


    conf_GPIO   ();
    conf_UART   ();
    conf_TIMER0 ();


//
//    // I2C definition
//    myDS1624_I2C_parameters.TWIinstance =    NRF_TWI0;
//    myDS1624_I2C_parameters.SDA         =    TWI0_SDA;
//    myDS1624_I2C_parameters.SCL         =    TWI0_SCL;
//    myDS1624_I2C_parameters.ADDR        =    DS1624_ADDRESS_0;
//    myDS1624_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
//    myDS1624_I2C_parameters.SDAport     =    NRF_GPIO;
//    myDS1624_I2C_parameters.SCLport     =    NRF_GPIO;
//
//    // Configure I2C peripheral
//    aux  =   DS1624_Init ( myDS1624_I2C_parameters );
//
//
//    // Configure 1SHOT mode
//    aux  =   DS1624_SetConversionMode ( myDS1624_I2C_parameters, ACCESS_CONFIG_1SHOT_ONE_TEMPERATURE_CONVERSION );
//    nrf_delay_ms ( 50 );
//
//    // Write myDataInEEPROM into EEPROM memory ( address: 0x13 )
//    aux  =   DS1624_WriteBytesEEPROM  ( myDS1624_I2C_parameters, 0x13, myDataInEEPROM, sizeof( myDataInEEPROM )/sizeof( myDataInEEPROM[0] ) );
//    nrf_delay_ms ( 50 );
//
//    // Read EEPROM memory ( address: 0x13 ), just to check if the data was stored correctly
//    myDataInEEPROM[0]    =   0;
//    myDataInEEPROM[1]    =   0;
//    myDataInEEPROM[2]    =   0;
//
//    aux  =   DS1624_ReadBytesEEPROM   ( myDS1624_I2C_parameters, 0x13, &myDataInEEPROM[0], sizeof( myDataInEEPROM )/sizeof( myDataInEEPROM[0] ) );
//


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
//            aux  =   DS1624_StartConvertTemperature ( myDS1624_I2C_parameters );
//
//            // Wait until the temperature conversion is completed or timeout
//            myTimeoOut   =   232323;
//            do{
//                aux  =   DS1624_IsTemperatureConversionDone ( myDS1624_I2C_parameters, &myDS1624_TempConversionStatus );
//                myTimeoOut--;
//            } while ( ( ( myDS1624_TempConversionStatus & ACCESS_CONFIG_DONE_MASK ) != ACCESS_CONFIG_DONE_CONVERSION_COMPLETE ) && ( myTimeoOut > 0 ) );
//
//            // Check if TimeOut, if so, there was an error ( send: NA ), send the data otherwise
//            if ( myTimeoOut <= 0 )
//            {
//                myTX_buff[0]                 =   'N';
//                myTX_buff[1]                 =   'A';
//            }
//            else
//            {
//                //aux  =   DS1624_ReadTemperature    ( myDS1624_I2C_parameters, &myDS1624_data );
//                aux  =   DS1624_ReadRawTemperature ( myDS1624_I2C_parameters, &myDS1624_data );
//
//                myTX_buff[0]                 =   myDS1624_data.MSBTemperature;
//                myTX_buff[1]                 =   myDS1624_data.LSBTemperature;
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
