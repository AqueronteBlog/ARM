/**
 * @brief       main.c
 * @details     This project shows how to work with the external sensor: MAX30100. It
 *              performs a new reading every one second and send the result ( temperature ) through UART.
 *
 *              It also reads 16 samples from the FIFO. This application does NOT process the data to
 *              get neither HR nor SpO2, but all the data is available into the buffers that the driver
 *              provides. To get those parameters, the data has to be filtered.
 *
 *              The rest of the time, the microcontroller is in low power.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        9/July/2018
 * @version     9/July/2018    The ORIGIN
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
#include "MAX30100.h"



/**@brief CONSTANTS.
 */
#define TX_BUFF_SIZE  32                        /*!<   UART buffer size                               */



/**@brief VARIABLES.
 */
volatile uint8_t  myMessage[ TX_BUFF_SIZE ];    /*!<   Message to be transmitted through the UART     */
volatile uint8_t  *myPtr;                       /*!<   Pointer to point out myMessage                 */
volatile uint32_t myState;                      /*!<   Variable to perform a new reading              */



/**@brief FUNCTION FOR APPLICATION MAIN ENTRY.
 */
int main( void )
{
    I2C_parameters_t         myMAX30100_I2C_parameters;
    MAX30100_status_t        aux;
    MAX30100_vector_data_t   myMAX30100_Data;


    conf_GPIO   ();
    conf_TIMER0 ();
    conf_UART   ();



    /* I2C definition   */
    myMAX30100_I2C_parameters.TWIinstance =    NRF_TWI0;
    myMAX30100_I2C_parameters.SDA         =    TWI0_SDA;
    myMAX30100_I2C_parameters.SCL         =    TWI0_SCL;
    myMAX30100_I2C_parameters.ADDR        =    MAX30100_ADDRESS;
    myMAX30100_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
    myMAX30100_I2C_parameters.SDAport     =    NRF_GPIO;
    myMAX30100_I2C_parameters.SCLport     =    NRF_GPIO;

    /* Configure I2C peripheral */
    aux  =   MAX30100_Init                      ( myMAX30100_I2C_parameters );

    /* Software reset   */
    aux  =   MAX30100_SoftwareReset             ( myMAX30100_I2C_parameters );

    /* Wait until the software reset is finished    */
    do
    {
        aux  =   MAX30100_PollingSoftwareReset ( myMAX30100_I2C_parameters, &myMAX30100_Data );
    }while( ( myMAX30100_Data.ResetFlag & MODE_CONFIGURATION_RESET_MASK ) != MODE_CONFIGURATION_RESET_DISABLE );    // [TODO] Dangerous!!! The uC may get stuck here if something goes wrong!
                                                                                                                    // [WORKAROUND] Insert a counter.

    /* Shutdown enabled   */
    aux  =   MAX30100_ShutdownControl           ( myMAX30100_I2C_parameters, MODE_CONFIGURATION_SHDN_ENABLE );

    /* Get Revision ID   */
    aux  =   MAX30100_GetRevisionID             ( myMAX30100_I2C_parameters, &myMAX30100_Data );

    /* Get Part ID   */
    aux  =   MAX30100_GetPartID                 ( myMAX30100_I2C_parameters, &myMAX30100_Data );

    /* Set RED LED current: 27.1mA */
    aux  =   MAX30100_SetRed_LED_CurrentControl ( myMAX30100_I2C_parameters, LED_CONFIGURATION_RED_PA_27_1_MA );

    /* Set IR LED current: 50.0mA */
    aux  =   MAX30100_SetIR_LED_CurrentControl  ( myMAX30100_I2C_parameters, LED_CONFIGURATION_IR_PA_50_0_MA );

    /* Set sample rate: 50 samples per second    */
    aux  =   MAX30100_SpO2_SampleRateControl    ( myMAX30100_I2C_parameters, SPO2_CONFIGURATION_SPO2_SR_50 );

    /* Set pulse width/resolution: 200us, 13-bit    */
    myMAX30100_Data.Resolution   =   SPO2_CONFIGURATION_LED_PW_200US_13BITS;
    aux  =   MAX30100_LED_PulseWidthControl     ( myMAX30100_I2C_parameters, myMAX30100_Data );

    /* Mode Control: SpO2 and HR   */
    aux  =   MAX30100_ModeControl               ( myMAX30100_I2C_parameters, MODE_CONFIGURATION_MODE_SPO2_ENABLED );

    /* Reset the FIFO    */
    aux  =   MAX30100_ClearFIFO                 ( myMAX30100_I2C_parameters, &myMAX30100_Data );

    /* Mode Control: SpO2 and HR   */
    aux  =   MAX30100_InterrupEnable            ( myMAX30100_I2C_parameters, ( INTERRUPT_ENABLE_ENB_A_FULL_ENABLE | INTERRUPT_ENABLE_ENB_TEP_RDY_DISABLE | INTERRUPT_ENABLE_ENB_HR_RDY_DISABLE | INTERRUPT_ENABLE_ENB_SO2_RDY_DISABLE ) );

    /* Shutdown disabled   */
    aux  =   MAX30100_ShutdownControl           ( myMAX30100_I2C_parameters, MODE_CONFIGURATION_SHDN_DISABLE );



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
            /* New reading */
            aux  =   MAX30100_TriggerTemperature ( myMAX30100_I2C_parameters );

            /* Wait until the conversion is finished    */
            do
            {
                aux      =   MAX30100_PollingTemperatureConversion ( myMAX30100_I2C_parameters, &myMAX30100_Data );
            }while( ( myMAX30100_Data.TemperatureFlag & MODE_CONFIGURATION_TEMP_EN_MASK ) == MODE_CONFIGURATION_TEMP_EN_ENABLE );   // [TODO] Dangerous!!! The uC may get stuck here if something goes wrong!
                                                                                                                                    // [WORKAROUND] Insert a counter.

            /* Read the new temperature value */
            aux  =   MAX30100_GetTemperature ( myMAX30100_I2C_parameters, &myMAX30100_Data );

            /* Read the FIFO, 16 samples */
            aux  =   MAX30100_ReadFIFO ( myMAX30100_I2C_parameters, &myMAX30100_Data, 16 );

            /* Read Interrupt status   */
            aux  =   MAX30100_ReadInterruptStatus ( myMAX30100_I2C_parameters, &myMAX30100_Data );


            /* Prepare the data to be sent through the UART */
            sprintf ( (char*)myMessage, "Temperature: %d C\r\n", (int)myMAX30100_Data.Temperature );


            /* Send data through the UART   */
            NRF_UART0->TASKS_STOPRX  =   1;
            NRF_UART0->TASKS_STOPTX  =   1;
            myPtr                    =   &myMessage[0];

            NRF_UART0->TASKS_STARTTX =   1;
            NRF_UART0->TXD           =   *myPtr;


            /* Reset the variables   */
            myState                  =   0;
    	}

        NRF_GPIO->OUTSET             |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );          // Turn all the LEDs off
        //__NOP();
    }
}
