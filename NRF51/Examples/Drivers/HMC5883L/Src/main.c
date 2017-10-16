/**
 * @brief       main.c
 * @details     This example shows how to work with the external HMC5883L device,
 *              a 3-Axis Digital Compass IC ( Magnetometer ). It collects a data every
 *              ~ 1s and transmits them through the UART.
 *
 *              The rest of the time, the microcontroller is in low power.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        12/October/2017
 * @version     12/October/2017    The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0
 *              ( SDK 1.1.0 ).
 * @warning     Softdevice S310 was used although the file's name is S130. The softdevice
 *              is not used in this example anyway because of Bluetooth was not used.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "nrf.h"
#include "ble.h"
#include "variables.h"
#include "functions.h"
#include "HMC5883L.h"


#define    X_Offset    0
#define    Y_Offset    0
#define    Z_Offset    0



int main( void )
{
    uint8_t  myTX_buff[12]   =      { 0 };

    I2C_parameters_t         myHMC5883L_I2C_parameters;

    HMC5883L_status_t        aux;
    HMC5883L_vector_data_t   myData;


    conf_GPIO   ();
    conf_UART   ();
    conf_TIMER0 ();



    mySTATE  =   0;                            // Reset the variable



    // I2C definition
    myHMC5883L_I2C_parameters.TWIinstance =    NRF_TWI0;
    myHMC5883L_I2C_parameters.SDA         =    TWI0_SDA;
    myHMC5883L_I2C_parameters.SCL         =    TWI0_SCL;
    myHMC5883L_I2C_parameters.ADDR        =    HMC5883L_ADDRESS;
    myHMC5883L_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
    myHMC5883L_I2C_parameters.SDAport     =    NRF_GPIO;
    myHMC5883L_I2C_parameters.SCLport     =    NRF_GPIO;

    // Configure I2C peripheral
    aux      =   HMC5883L_Init ( myHMC5883L_I2C_parameters );


    // Configure the device
    aux      =   HMC5883L_Conf ( myHMC5883L_I2C_parameters, CONF_REG_A_SAMPLE_1, CONF_REG_A_DATARATE_15_HZ, CONF_REG_A_MODE_NORMAL,
                                 CONF_REG_B_GAIN_1_3_GA, MODE_REG_HIGH_SPEED_I2C_DISABLED, MODE_REG_MODE_IDLE );

    // Get the IDs
    aux  =   HMC5883L_GetIdentificationRegister ( myHMC5883L_I2C_parameters, HMC5883L_IDENTIFICATION_REGISTER_A, &myData );
    aux  =   HMC5883L_GetIdentificationRegister ( myHMC5883L_I2C_parameters, HMC5883L_IDENTIFICATION_REGISTER_B, &myData );
    aux  =   HMC5883L_GetIdentificationRegister ( myHMC5883L_I2C_parameters, HMC5883L_IDENTIFICATION_REGISTER_C, &myData );



    NRF_TIMER0->TASKS_START  =   1;                 // Start Timer0


    while( 1 )
    {
        //NRF_POWER->SYSTEMOFF = 1;
        NRF_POWER->TASKS_LOWPWR = 1;                // Sub power mode: Low power.

        // Enter System ON sleep mode
        __WFE();
        // Make sure any pending events are cleared
        __SEV();
        __WFE();



        if ( mySTATE == 1 )
        {
            NRF_GPIO->OUTCLR        =   ( 1UL << LED1 );                                // Turn the LED1 on

            NVIC_DisableIRQ ( TIMER0_IRQn );                                            // Timer Interrupt DISABLED


            // Wait until a new data arrives
            // NOTE: Add a counter, if something goes wrong, the uC may get stuck here!
            do
            {
                aux  =   HMC5883L_GetStatus ( myHMC5883L_I2C_parameters, &myData );
            }
            while ( ( myData.Status & STATUS_REG_RDY_MASK )  != STATUS_REG_RDY_ENABLED );

            // Get the new measurement
            aux  =   HMC5883L_GetCompensatedDataOutput  ( myHMC5883L_I2C_parameters, &myData, X_Offset, Y_Offset, Z_Offset );
            aux  =   HMC5883L_SetMode                   ( myHMC5883L_I2C_parameters, MODE_REG_MODE_SINGLE );

            // Magnetometer X-axis
            myTX_buff[0]                 =   ( ( uint32_t )myData.DataOutput_X & 0xFF );            // LSB MAG_X
            myTX_buff[1]                 =   ( ( uint32_t )myData.DataOutput_X >> 8 )  & 0xFF;
            myTX_buff[2]                 =   ( ( uint32_t )myData.DataOutput_X >> 16 ) & 0xFF;
            myTX_buff[3]                 =   ( ( uint32_t )myData.DataOutput_X >> 24 ) & 0xFF;      // MSB MAG_X

            // Magnetometer Y-axis
            myTX_buff[4]                 =   ( ( uint32_t )myData.DataOutput_Y & 0xFF );            // LSB MAG_Y
            myTX_buff[5]                 =   ( ( uint32_t )myData.DataOutput_Y >> 8 )  & 0xFF;
            myTX_buff[6]                 =   ( ( uint32_t )myData.DataOutput_Y >> 16 ) & 0xFF;
            myTX_buff[7]                 =   ( ( uint32_t )myData.DataOutput_Y >> 24 ) & 0xFF;      // MSB MAG_Y

            // Magnetometer Z-axis
            myTX_buff[8]                 =   ( ( uint32_t )myData.DataOutput_Z & 0xFF );            // LSB MAG_Z
            myTX_buff[9]                 =   ( ( uint32_t )myData.DataOutput_Z >> 8 )  & 0xFF;
            myTX_buff[10]                =   ( ( uint32_t )myData.DataOutput_Z >> 16 ) & 0xFF;
            myTX_buff[11]                =   ( ( uint32_t )myData.DataOutput_Z >> 24 ) & 0xFF;      // MSB MAG_Z


            myPtr                        =   &myTX_buff[0];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   *myPtr++;                                   // Start transmission

            // Wait until the message is transmitted
            while ( TX_inProgress == YES ){
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            mySTATE             =   0;
            NVIC_EnableIRQ ( TIMER0_IRQn );                                              // Timer Interrupt ENABLED

            NRF_GPIO->OUTSET    =   ( 1UL << LED1 );                                     // Turn the LED1 off
        }
        //__NOP();
    }
}
