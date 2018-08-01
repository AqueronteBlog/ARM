/**
 * @brief       main.c
 * @details     This project shows how to work with the external sensor: DS1307. It
 *              performs a new reading every one second and send the result through UART.
 *
 *              The rest of the time, the microcontroller is in low power.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        30/July/2018
 * @version     30/July/2018    The ORIGIN
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
#include "functions.h"
#include "variables.h"
#include "DS1307.h"



/**@brief Constants.
 */
#define TX_BUFF_SIZE  64                          /*!<   UART buffer size                                       */


/**@brief Variables.
 */
volatile uint32_t myState;                        /*!<   State that indicates when to perform an ADC sample     */
volatile uint32_t myADCDoneFlag;                  /*!<   It indicates when a new ADC conversion is ready        */
volatile uint8_t  myMessage[ TX_BUFF_SIZE ];      /*!<   Message to be transmitted through the UART             */
volatile uint8_t  *myPtr;                         /*!<   Pointer to point out myMessage                         */



/**@brief Function for application main entry.
 */
int main( void )
{
    I2C_parameters_t         myDS1307_I2C_parameters;
    DS1307_status_t          aux;
    DS1307_vector_data_t     myDS1307_Data;


    conf_GPIO   ();
    conf_TIMER0 ();
    conf_UART   ();



    /* I2C definition   */
    myDS1307_I2C_parameters.TWIinstance =    NRF_TWI0;
    myDS1307_I2C_parameters.SDA         =    TWI0_SDA;
    myDS1307_I2C_parameters.SCL         =    TWI0_SCL;
    myDS1307_I2C_parameters.ADDR        =    DS1307_ADDRESS;
    myDS1307_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
    myDS1307_I2C_parameters.SDAport     =    NRF_GPIO;
    myDS1307_I2C_parameters.SCLport     =    NRF_GPIO;

    /* Configure I2C peripheral */
    aux  =   DS1307_Init            ( myDS1307_I2C_parameters );

    /* Enable the DS1307 oscillator */
    aux  =   DS1307_OscillatorMode  ( myDS1307_I2C_parameters, SECONDS_CH_OSCILLATOR_ENABLED );

    /* Set the day of the week */
    myDS1307_Data.DayOfTheWeek        =   DAY_TUESDAY;
    aux  =   DS1307_SetDayOfTheWeek ( myDS1307_I2C_parameters, myDS1307_Data );

    /* Set the date */
    myDS1307_Data.BCDDate             =   0x31;                                                      // Date: 31
    aux  =   DS1307_SetDate         ( myDS1307_I2C_parameters, myDS1307_Data );

    /* Set the month */
    myDS1307_Data.BCDMonth            =   MONTH_JULY;
    aux  =   DS1307_SetMonth        ( myDS1307_I2C_parameters, myDS1307_Data );

    /* Set the year */
    myDS1307_Data.BCDYear             =   0x18;                                                      // Year: 2018
    aux  =   DS1307_SetYear         ( myDS1307_I2C_parameters, myDS1307_Data );

    /* Set the time */
    myDS1307_Data.BCDTime             =   0x081600;                                                  // Time: 08:16.00
    myDS1307_Data.Time12H_24HMode     =   HOURS_MODE_24H;
    aux  =   DS1307_SetTime         ( myDS1307_I2C_parameters, myDS1307_Data );



    myState  =   0;                             // Reset the variable
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
        if ( myState == 1 )
        {
            /* Get the day of the week */
            aux  =   DS1307_GetDayOfTheWeek ( myDS1307_I2C_parameters, &myDS1307_Data );

            /* Get the day of the date */
            aux  =   DS1307_GetDate         ( myDS1307_I2C_parameters, &myDS1307_Data );

            /* Get the month */
            aux  =   DS1307_GetMonth        ( myDS1307_I2C_parameters, &myDS1307_Data );

            /* Get the year */
            aux  =   DS1307_GetYear         ( myDS1307_I2C_parameters, &myDS1307_Data );

            /* Get the time */
            aux  =   DS1307_GetTime         ( myDS1307_I2C_parameters, &myDS1307_Data );



            /* Transmit result through the UART  */
            sprintf ( (char*)myMessage, "%02x/%02x/%02x %d %02x:%02x.%02x\r\n", myDS1307_Data.BCDDate, myDS1307_Data.BCDMonth, myDS1307_Data.BCDYear, myDS1307_Data.DayOfTheWeek,
                                                                                (uint8_t)( ( myDS1307_Data.BCDTime & 0xFF0000 ) >> 16U ), (uint8_t)( ( myDS1307_Data.BCDTime & 0x00FF00 ) >> 8U ),
                                                                                (uint8_t)( myDS1307_Data.BCDTime & 0x0000FF ) );

            NRF_UART0->TASKS_STOPRX  =   1UL;
            NRF_UART0->TASKS_STOPTX  =   1UL;
            myPtr                    =   &myMessage[0];

            NRF_UART0->TASKS_STARTTX =   1UL;
            NRF_UART0->TXD           =   *myPtr;


            myState             =   0;
    	}

        NRF_GPIO->OUTSET             |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );          // Turn all the LEDs off
        //__NOP();
    }
}
