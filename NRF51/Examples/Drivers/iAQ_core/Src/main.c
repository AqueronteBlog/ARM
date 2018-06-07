/**
 * @brief       main.c
 * @details     [todo]
 *
 *              the rest of the time, the microcontroller is in low power.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        4/June/2018
 * @version     4/June/2018    The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     Softdevice S310 was used although the file's name is S130. The softdevice
 *              is not used in this example anyway because of Bluetooth was not used.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "nrf.h"
#include "nrf_delay.h"
#include "ble.h"
#include "board.h"
#include "functions.h"
#include "variables.h"
#include "iAQ_Core.h"



/* GLOBAL VARIABLES */
uint32_t volatile mySTATE;                       /*!<   It indicates the next action to be performed                                       */
uint8_t  volatile dataToBeTX;                    /*!<   A counter. It indicates how many data it will be transmitted through the UART      */
uint32_t volatile TX_inProgress;                 /*!<   It indicates if a transmission is in progress                                      */
uint8_t  volatile *myPtr;                        /*!<   Pointer to point out the data from the external sensor                             */



/* MAIN */
int main( void )
{
    uint8_t  myTX_buff[7]     =  { 0 };
    uint32_t myWarmUpCounter  =   0;


    I2C_parameters_t           myiAQ_Core_I2C_parameters;
    iAQ_Core_status_t          aux;
    iAQ_Core_vector_data_t     myiAQ_Core_Data;


    conf_GPIO   ();
    conf_TIMER0 ();
    conf_UART   ();



    /* I2C definition   */
    myiAQ_Core_I2C_parameters.TWIinstance =    NRF_TWI0;
    myiAQ_Core_I2C_parameters.SDA         =    TWI0_SDA;
    myiAQ_Core_I2C_parameters.SCL         =    TWI0_SCL;
    myiAQ_Core_I2C_parameters.ADDR        =    iAQ_Core_ADDRESS;
    myiAQ_Core_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
    myiAQ_Core_I2C_parameters.SDAport     =    NRF_GPIO;
    myiAQ_Core_I2C_parameters.SCLport     =    NRF_GPIO;

    /* Configure I2C peripheral */
    aux  =   iAQ_Core_Init ( myiAQ_Core_I2C_parameters );


    /* iAQ-Core warm up is at least 5 minutes ( 300 * 1s ) or when the sensor is ready  */
    do
    {
        aux  =   iAQ_Core_GetNewReading ( myiAQ_Core_I2C_parameters, &myiAQ_Core_Data );
        nrf_delay_ms ( 1000 );
        myWarmUpCounter++;
    }while( ( myWarmUpCounter < 300 ) && ( myiAQ_Core_Data.status == iAQ_Core_STATUS_RUNIN ) );


    mySTATE  =   0;                             // Reset the variable
    NRF_TIMER0->TASKS_START  =   1;             // Start Timer0

    //NRF_POWER->SYSTEMOFF = 1;
    NRF_POWER->TASKS_LOWPWR  =   1;             // Sub power mode: Low power.
    while( 1 )
    {
        /* Enter System ON sleep mode   */
    	__WFE();
    	/* Make sure any pending events are cleared */
    	__SEV();
    	__WFE();


    	NRF_GPIO->OUTCLR             |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );          // Turn all the LEDs on
        if ( mySTATE == 1 )
        {
            /* New reading */
            do
            {
                aux      =   iAQ_Core_GetNewReading ( myiAQ_Core_I2C_parameters, &myiAQ_Core_Data );
            }while( myiAQ_Core_Data.status != iAQ_Core_STATUS_OK );                                         // [TODO] Dangerous!!! The uC may get stuck here if something goes wrong!
                                                                                                            // [WORKAROUND] Insert a counter.

            /* Prepare the data to be sent through the UART */
            myTX_buff[0]                 =   ( myiAQ_Core_Data.pred >> 8 ) & 0xFF;                          // Prediction (CO2 eq. ppm): MSB
            myTX_buff[1]                 =   ( myiAQ_Core_Data.pred & 0xFF );                               // Prediction (CO2 eq. ppm): LSB
            myTX_buff[2]                 =   ( myiAQ_Core_Data.Tvoc >> 8 ) & 0xFF;                          // Prediction (TVOC eq. ppb): MSB
            myTX_buff[3]                 =   ( myiAQ_Core_Data.Tvoc & 0xFF );                               // Prediction (TVOC eq. ppb): LSB
            myTX_buff[4]                 =   ( myiAQ_Core_Data.resistance >> 16 ) & 0xFF;                   // Sensor resistance: MSB
            myTX_buff[5]                 =   ( myiAQ_Core_Data.resistance >> 8 ) & 0xFF;                    // Sensor resistance
            myTX_buff[6]                 =   ( myiAQ_Core_Data.resistance & 0xFF );                         // Sensor resistance: LSB


            /* Send data through the UART   */
            myPtr                        =   &myTX_buff[0];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   *myPtr++;                                                      // Start transmission

            /* Wait until the message is transmitted */
            while ( TX_inProgress == YES )
            {
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            mySTATE             =   0;
    	}

        NRF_GPIO->OUTSET             |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );          // Turn all the LEDs off
        //__NOP();
    }
}
