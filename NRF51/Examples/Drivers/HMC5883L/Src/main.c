/**
 * @brief       main.c
 * @details     [todo]
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
    HMC5883L_status_t        aux;
    HMC5883L_vector_data_t   myData;


    conf_GPIO   ();
    conf_TWI0   ();
    conf_TIMER0 ();



    mySTATE  =   0;                            // Reset the variable


    // Configure the device
    aux      =   HMC5883L_Conf ( NRF_TWI0, HMC5883L_ADDRESS, CONF_REG_A_SAMPLE_1, CONF_REG_A_DATARATE_15_HZ, CONF_REG_A_MODE_NORMAL,
                                 CONF_REG_B_GAIN_1_3_GA, MODE_REG_HIGH_SPEED_I2C_DISABLED, MODE_REG_MODE_IDLE );

    // Get the IDs
    aux  =   HMC5883L_GetIdentificationRegister ( NRF_TWI0, HMC5883L_ADDRESS, HMC5883L_IDENTIFICATION_REGISTER_A, &myData );
    aux  =   HMC5883L_GetIdentificationRegister ( NRF_TWI0, HMC5883L_ADDRESS, HMC5883L_IDENTIFICATION_REGISTER_B, &myData );
    aux  =   HMC5883L_GetIdentificationRegister ( NRF_TWI0, HMC5883L_ADDRESS, HMC5883L_IDENTIFICATION_REGISTER_C, &myData );



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
            // Wait until a new data arrives
            // NOTE: Add a counter, if something goes wrong, the uC may get stuck here!
            do
            {
                aux  =   HMC5883L_GetStatus ( NRF_TWI0, HMC5883L_ADDRESS, &myData );
            }
            while ( ( myData.Status & STATUS_REG_RDY_MASK )  != STATUS_REG_RDY_ENABLED );

            // Get the new measurement
            aux  =   HMC5883L_GetCompensatedDataOutput  ( NRF_TWI0, HMC5883L_ADDRESS, &myData, X_Offset, Y_Offset, Z_Offset );
            aux  =   HMC5883L_SetMode                   ( NRF_TWI0, HMC5883L_ADDRESS, MODE_REG_MODE_SINGLE );
        }
        //__NOP();
    }
}
