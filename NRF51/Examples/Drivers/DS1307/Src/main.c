/**
 * @brief       main.c
 * @details     [TODO]This project shows how to work with the external sensor: DS1307. It
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
    uint8_t  myTX_buff[2]     =  { 0 };


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
    aux  =   DS1307_Init                        ( myDS1307_I2C_parameters );




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



            /* Transmit result through the UART  */
            //sprintf ( (char*)myMessage, "VDD: %d mV\r\n", (int)( myVDD * 1000.0f ) );

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
