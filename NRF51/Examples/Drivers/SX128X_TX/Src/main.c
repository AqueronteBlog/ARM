/**
 * @brief       main.c
 * @details     [TODO]This example shows how to work with the external device: SX128X. Every 2 seconds, a new
 *              task ( get uncompensated temperature and pressure and get true temperature and pressure ) is
 *              performed and transmitted through the UART ( Baud Rate: 115200 ).
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
#include "SX128X.h"



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


//    I2C_parameters_t            mySX128X_I2C_parameters;
//    SX128X_status_t             aux;
//    SX128X_chip_id_data_t       mySX128X_ChipID;
//    SX128X_temperature_data_t   mySX128X_TemperatureData;
//    SX128X_pressure_data_t      mySX128X_PressureData;
//    SX128X_calibration_data_t   mySX128X_Calibration_Data;
//    SX128X_uncompensated_data_t mySX128X_Uncompensated_Data;



    conf_LFCLK  ();
    conf_GPIO   ();
    conf_UART   ();
    conf_RTC1   ();


//
//    /* I2C definition   */
//    mySX128X_I2C_parameters.TWIinstance =    NRF_TWI0;
//    mySX128X_I2C_parameters.SDA         =    TWI0_SDA;
//    mySX128X_I2C_parameters.SCL         =    TWI0_SCL;
//    mySX128X_I2C_parameters.ADDR        =    SX128X_ADDRESS;
//    mySX128X_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
//    mySX128X_I2C_parameters.SDAport     =    NRF_GPIO;
//    mySX128X_I2C_parameters.SCLport     =    NRF_GPIO;
//
//    /* Configure I2C peripheral  */
//    aux  =   SX128X_Init            ( mySX128X_I2C_parameters );
//
//    /* Get the chip-id     */
//    aux  =   SX128X_GetID           ( mySX128X_I2C_parameters, &mySX128X_ChipID );
//
//    /* Transmit result through the UART  */
//    sprintf ( (char*)myMessage, "Chip-ID: %d\r\n", mySX128X_ChipID.id );
//
//    NRF_UART0->TASKS_STOPRX  =   1UL;
//    NRF_UART0->TASKS_STOPTX  =   1UL;
//    myPtr                    =   &myMessage[0];
//
//    NRF_UART0->TASKS_STARTTX =   1UL;
//    NRF_UART0->TXD           =   *myPtr;
//
//    nrf_delay_ms ( 500 );
//
//
//    /* Get calibration data     */
//    aux  =   SX128X_Get_Cal_Param   ( mySX128X_I2C_parameters, &mySX128X_Calibration_Data );
//
//    /* Transmit result through the UART  */
//    sprintf ( (char*)myMessage, "AC1: %d, AC2: %d, AC3: %d, AC4: %d, AC5: %d, AC6: %d, B1: %d, B2: %d, MB: %d, MC: %d, MD: %d\r\n", mySX128X_Calibration_Data.ac1, mySX128X_Calibration_Data.ac2,
//             mySX128X_Calibration_Data.ac3, mySX128X_Calibration_Data.ac4, mySX128X_Calibration_Data.ac5, mySX128X_Calibration_Data.ac6, mySX128X_Calibration_Data.b1, mySX128X_Calibration_Data.b2,
//             mySX128X_Calibration_Data.mb, mySX128X_Calibration_Data.mc, mySX128X_Calibration_Data.md );
//
//    NRF_UART0->TASKS_STOPRX  =   1UL;
//    NRF_UART0->TASKS_STOPTX  =   1UL;
//    myPtr                    =   &myMessage[0];
//
//    NRF_UART0->TASKS_STARTTX =   1UL;
//    NRF_UART0->TXD           =   *myPtr;

    nrf_delay_ms ( 500 );



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
            NRF_GPIO->OUTCLR     |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );          // Turn all the LEDs on

//            /* Get uncompensated temperature    */
//            aux  =   SX128X_Get_UT ( mySX128X_I2C_parameters, &mySX128X_Uncompensated_Data );
//
//            /* Get uncompensated pressure, Resolution: Standard    */
//            aux  =   SX128X_Get_UP ( mySX128X_I2C_parameters, PRESSURE_STANDARD_MODE, &mySX128X_Uncompensated_Data );
//
//            /* Calculate the true temperature    */
//            mySX128X_TemperatureData  =   SX128X_Get_Temperature ( mySX128X_Calibration_Data, mySX128X_Uncompensated_Data );
//
//            /* Calculate the true pressure    */
//            mySX128X_PressureData  =   SX128X_Get_CalPressure ( mySX128X_Calibration_Data, mySX128X_TemperatureData, PRESSURE_STANDARD_MODE, mySX128X_Uncompensated_Data );
//
//
//            /* Transmit result through the UART  */
//            sprintf ( (char*)myMessage, "Temperature: %ld C | Pressure: %ld Pa\r\n", (int32_t)( ( mySX128X_TemperatureData.temp / 10.0f ) + 0.5f ), ( mySX128X_PressureData.press ) );
//
//            NRF_UART0->TASKS_STOPRX  =   1UL;
//            NRF_UART0->TASKS_STOPTX  =   1UL;
//            myPtr                    =   &myMessage[0];
//
//            NRF_UART0->TASKS_STARTTX =   1UL;
//            NRF_UART0->TXD           =   *myPtr;


            /* Reset the variables   */
            myState               =  0;
            NRF_GPIO->OUTSET     |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );          // Turn all the LEDs off
    	}
        //__NOP();
    }
}
