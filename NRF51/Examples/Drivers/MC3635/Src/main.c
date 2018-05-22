/**
 * @brief       main.c
 * @details     [todo].
 *
 *              The rest of the time, the microcontroller is in low power.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        6/April/2018
 * @version     6/April/2018    The ORIGIN
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
#include "MC3635.h"


/* GLOBAL VARIABLES */
uint32_t mySTATE;                       /*!<   It indicates the next action to be performed                                       */
uint8_t  dataToBeTX;                    /*!<   A counter. It indicates how many data it will be transmitted through the UART      */
uint32_t TX_inProgress;                 /*!<   It indicates if a transmission is in progress                                      */
uint8_t  *myPtr;                        /*!<   Pointer to point out the data from the external sensor                             */



/* MAIN */
int main( void )
{
//    uint8_t  myTX_buff[4]     =  { 0 };
//    uint32_t myCounterData    =  0;
//    uint32_t myCounterTimeout =  0;


    I2C_parameters_t    myMC3635_I2C_parameters;
    MC3635_status_t     aux;
    MC3635_data_t       myMC3635_data;


    conf_GPIO   ();
    //conf_GPIOTE ();
    conf_UART   ();



    /* I2C definition */
    myMC3635_I2C_parameters.TWIinstance =    NRF_TWI0;
    myMC3635_I2C_parameters.SDA         =    TWI0_SDA;
    myMC3635_I2C_parameters.SCL         =    TWI0_SCL;
    myMC3635_I2C_parameters.ADDR        =    MC3635_ADDRESS_LOW;
    myMC3635_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K100;
    myMC3635_I2C_parameters.SDAport     =    NRF_GPIO;
    myMC3635_I2C_parameters.SCLport     =    NRF_GPIO;

    /* Configure I2C peripheral */
    aux  =   MC3635_Init ( myMC3635_I2C_parameters );


    /* MC3635 Software Reset    */
    aux  =   MC3635_SetSoftwareReset ( myMC3635_I2C_parameters );

    /*  MC3635 in Standby mode  */
    aux  =   MC3635_SetStandbyMode ( myMC3635_I2C_parameters );

    /*  MC3635 initialization sequence  */
    aux  =   MC3635_InitializationSequence ( myMC3635_I2C_parameters );


    /* MC3635 Check Scratch register    */
    myMC3635_data.scratch    =   0x23;
    aux  =   MC3635_WriteScratchpadRegister ( myMC3635_I2C_parameters, myMC3635_data );

    myMC3635_data.scratch    =   0;
    aux  =   MC3635_ReadScratchpadRegister ( myMC3635_I2C_parameters, &myMC3635_data );

    /* MC3635 FIFO disabled   */
    aux  =   MC3635_EnableFIFO ( myMC3635_I2C_parameters, FIFO_C_FIFO_EN_DISABLED );

    /* MC3635 14-bits resolution ( FIFO not in use)   */
    aux  =   MC3635_SetResolution ( myMC3635_I2C_parameters, RANGE_C_RES_14_BITS );

    /* MC3635 16g range    */
    aux  =   MC3635_SetRange ( myMC3635_I2C_parameters, RANGE_C_RANGE_16G );

    /* MC3635 X/Y/Z axis enabled    */
    aux  =   MC3635_EnableAxis ( myMC3635_I2C_parameters, MODE_C_X_AXIS_PD_ENABLED, MODE_C_Y_AXIS_PD_ENABLED, MODE_C_Z_AXIS_PD_ENABLED );

    /* MC3635 CWAKE mode in Low Power enabled and ODR is 54Hz    */
    aux  =   MC3635_SetMode ( myMC3635_I2C_parameters, MODE_C_MCTRL_CWAKE, LOW_POWER_MODE, ODR_7 );


    mySTATE  =   0;                                                                                                 // Reset the variable

    //NRF_POWER->SYSTEMOFF = 1;
    NRF_POWER->TASKS_LOWPWR = 1;                                                                                    // Sub power mode: Low power.
    while( 1 )
    {
//        // Enter System ON sleep mode
//        __WFE();
//        // Make sure any pending events are cleared
//        __SEV();
//        __WFE();

        mySTATE = 1;
        NRF_GPIO->OUTCLR             |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );              // Turn all the LEDs on
        if ( mySTATE == 1 )
        {
            /*  Wait until a new data is available */
            do{
                /* MC3635 Read register Status1    */
                aux  =   MC3635_ReadStatusRegister1 ( myMC3635_I2C_parameters, &myMC3635_data );
            }while( ( myMC3635_data.status_1 & STATUS_1_NEW_DATA_MASK ) == STATUS_1_NEW_DATA_FALSE );                   // [TODO] Dangerous!!! The uC may get stuck here if something goes wrong!
                                                                                                                        // [WORKAROUND] Insert a counter.


            /* MC3635 Read the data    */
            aux  =   MC3635_ReadRawData ( myMC3635_I2C_parameters, &myMC3635_data );


//            NVIC_DisableIRQ ( GPIOTE_IRQn );                                                                            // GPIOTE Interrupt DISABLED
//
//            /*  Get data ( 8-bits, Manchester ).
//
//                NOTE:   Make sure the transmitter is sending data otherwise a little delay will
//                        be introduced by myCounterTimeout.
//            */
//            myMC3635_data.data   =   0;
//
//            for ( myCounterData = 0; myCounterData < 8; myCounterData++ )
//            {
//                /*  Wait until rising edges on CLD pin or Timeout */
//                myCounterTimeout    =   2323;
//                while ( ( ( NRF_GPIO->IN & GPIO_IN_PIN14_Msk ) == ( GPIO_IN_PIN14_Low << GPIO_IN_PIN14_Pos ) ) && ( myCounterTimeout > 0 ) )
//                {
//                    myCounterTimeout--;
//                }
//
//                /*  Process the data */
//                myMC3635_data.data <<=   1;
//
//                if ( ( NRF_GPIO->IN & GPIO_IN_PIN13_Msk )  == ( GPIO_IN_PIN13_High << GPIO_IN_PIN13_Pos ) )
//                {
//                    myMC3635_data.data  |=  1;
//                }
//
//                /*  Wait until CLD pin goes low again or Timeout */
//                myCounterTimeout    =   2323;
//                while ( ( ( NRF_GPIO->IN & GPIO_IN_PIN14_Msk ) == ( GPIO_IN_PIN14_High << GPIO_IN_PIN14_Pos ) ) && ( myCounterTimeout > 0 ) )
//                {
//                    myCounterTimeout--;
//                }
//            }
//
//
//            /* Get RSSI  */
//            aux  =   MC3635_GetRSSI ( myMC3635_SPI_parameters, &myMC3635_data );
//
//
//            /* Prepare the data to be sent */
//            myTX_buff[0]                 =   myMC3635_data.data;
//            myTX_buff[1]                 =   myMC3635_data.rssi1;
//            myTX_buff[2]                 =   myMC3635_data.rssi2;
//            myTX_buff[3]                 =   myMC3635_data.rssi3;
//
//
//            /* Send data through the UART   */
//            myPtr                        =   &myTX_buff[0];
//            TX_inProgress                =   YES;
//            NRF_UART0->TASKS_STARTTX     =   1;
//            NRF_UART0->TXD               =   *myPtr++;                                                              // Start transmission
//
//            /* Wait until the message is transmitted */
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
//            NVIC_EnableIRQ ( GPIOTE_IRQn );                                                                         // GPIOTE Interrupt ENABLED
        }
        NRF_GPIO->OUTSET             |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );          // Turn all the LEDs off
        //__NOP();
    }
}
