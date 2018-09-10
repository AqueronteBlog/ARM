/**
 * @brief       main.c
 * @details     [todo]This example shows how to work with the external device: BMP180. Every 0.5 seconds, a new
 *              task ( trigger temperature, get temperature value, trigger relative humidity, get relative humidity ) is
 *              performed and transmitted through the UART ( Baud Rate: 115200 ). In total, it takes a new sample about
 *              1.5 seconds to be transmitted through the UART.
 *
 *              The rest of the time, the microcontroller is in low power.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/September/2018
 * @version     10/September/2018    The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0 ( SDK 1.1.0 ).
 * @warning     Softdevice S310 was used although the file's name is S130. The softdevice is not used in this example anyway because of Bluetooth was not used.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */
#include <stdio.h>
#include <string.h>

#include "nrf.h"
#include "nrf_delay.h"
#include "ble.h"
#include "board.h"
#include "functions.h"
#include "variables.h"
#include "BMP180.h"



/**@brief Constants.
 */
#define TX_BUFF_SIZE  128                         /*!<   UART buffer size                                       */


/**@brief Variables.
 */
volatile uint32_t myState;                        /*!<   State that indicates when to perform an ADC sample     */
volatile uint8_t  *myPtr;                         /*!<   Pointer to point out myMessage                         */



/**@brief Function for application main entry.
 */
int main( void )
{
    uint8_t  myMessage[ TX_BUFF_SIZE ];           /*!<   Message to be transmitted through the UART             */


    I2C_parameters_t            myBMP180_I2C_parameters;
    BMP180_status_t             aux;
    BMP180_data_t               myBMP180_Data;
    BMP180_calibration_data_t   myBMP180_Calibration_Data;
    BMP180_uncompensated_data_t myBMP180_Uncompensated_Data;



    conf_LFCLK  ();
    conf_GPIO   ();
    conf_UART   ();
    conf_RTC1   ();



    /* I2C definition   */
    myBMP180_I2C_parameters.TWIinstance =    NRF_TWI0;
    myBMP180_I2C_parameters.SDA         =    TWI0_SDA;
    myBMP180_I2C_parameters.SCL         =    TWI0_SCL;
    myBMP180_I2C_parameters.ADDR        =    BMP180_ADDRESS;
    myBMP180_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
    myBMP180_I2C_parameters.SDAport     =    NRF_GPIO;
    myBMP180_I2C_parameters.SCLport     =    NRF_GPIO;

    /* Configure I2C peripheral  */
    aux  =   BMP180_Init            ( myBMP180_I2C_parameters );

    /* Get the chip-id     */
    aux  =   BMP180_GetID           ( myBMP180_I2C_parameters, &myBMP180_Data );

    /* Transmit result through the UART  */
    sprintf ( (char*)myMessage, "Chip-ID: %d\r\n", myBMP180_Data.id );

    NRF_UART0->TASKS_STOPRX  =   1UL;
    NRF_UART0->TASKS_STOPTX  =   1UL;
    myPtr                    =   &myMessage[0];

    NRF_UART0->TASKS_STARTTX =   1UL;
    NRF_UART0->TXD           =   *myPtr;

    /* Get calibration data     */
    aux  =   BMP180_Get_Cal_Param   ( myBMP180_I2C_parameters, &myBMP180_Calibration_Data );

    /* Transmit result through the UART  */
    sprintf ( (char*)myMessage, "AC1: %d, AC2: %d, AC3: %d, AC4: %d, AC5: %d, AC6: %d, B1: %d, B2: %d, MB: %d, MC: %d, MD: %d\r\n", myBMP180_Calibration_Data.ac1, myBMP180_Calibration_Data.ac2,
             myBMP180_Calibration_Data.ac3, myBMP180_Calibration_Data.ac4, myBMP180_Calibration_Data.ac5, myBMP180_Calibration_Data.ac6, myBMP180_Calibration_Data.b1, myBMP180_Calibration_Data.b2,
             myBMP180_Calibration_Data.mb, myBMP180_Calibration_Data.mc, myBMP180_Calibration_Data.md );

    NRF_UART0->TASKS_STOPRX  =   1UL;
    NRF_UART0->TASKS_STOPTX  =   1UL;
    myPtr                    =   &myMessage[0];

    NRF_UART0->TASKS_STARTTX =   1UL;
    NRF_UART0->TXD           =   *myPtr;



    myState  =   0;                             // Reset the variable
    NRF_RTC1->TASKS_START = 1;                  // Start RTC1

    //NRF_POWER->SYSTEMOFF = 1;
    NRF_POWER->TASKS_LOWPWR  =   1;             // Sub power mode: Low power.
    while( 1 )
    {
        /* Enter System ON sleep mode   */
    	__WFE();
    	/* Make sure any pending events are cleared */
    	__SEV();
    	__WFE();


        if ( myState == 1 )
        {
            NRF_GPIO->OUTSET     |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );          // Turn all the LEDs off

            /* Get uncompensated temperature    */
            aux  =   BMP180_Get_UT ( myBMP180_I2C_parameters, &myBMP180_Uncompensated_Data );

            /* Get uncompensated pressure, Resolution: Standard    */
            aux  =   BMP180_Get_UP ( myBMP180_I2C_parameters, PRESSURE_STANDARD_MODE, &myBMP180_Uncompensated_Data );

            /* Calculate the true temperature    */
            myBMP180_Data  =   BMP180_Get_Temperature ( myBMP180_I2C_parameters, myBMP180_Calibration_Data, myBMP180_Uncompensated_Data );

            /* Calculate the true pressure    */
            myBMP180_Data  =   BMP180_Get_CalPressure ( myBMP180_I2C_parameters, myBMP180_Calibration_Data, myBMP180_Data, PRESSURE_STANDARD_MODE, myBMP180_Uncompensated_Data );


            /* Transmit result through the UART  */
            sprintf ( (char*)myMessage, "Temperature: %ld C | Pressure: %ld Pa\r\n", ( myBMP180_Data.temp ), ( myBMP180_Data.press ) );

            NRF_UART0->TASKS_STOPRX  =   1UL;
            NRF_UART0->TASKS_STOPTX  =   1UL;
            myPtr                    =   &myMessage[0];

            NRF_UART0->TASKS_STARTTX =   1UL;
            NRF_UART0->TXD           =   *myPtr;


            /* Reset the variables   */
            myState               =  0;
            NRF_GPIO->OUTCLR     |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );          // Turn all the LEDs on
    	}
        //__NOP();
    }
}
