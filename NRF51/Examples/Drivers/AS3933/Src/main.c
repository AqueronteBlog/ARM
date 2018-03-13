/**
 * @brief       main.c
 * @details     This example shows how to work with the external sensor AS3933
 *              ( 3D Low Frequency Wakeup Receiver ). Every time the transmitter sends
 *              a right pattern, it wakes the microcontroller up and it starts
 *              reading the data ( 8-bits, Manchester ).
 *
 *              The data as well as the RSSIs are sent through the UART.
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


/* GLOBAL VARIABLES */
uint32_t mySTATE;                       /*!<   It indicates the next action to be performed                                       */
uint8_t  dataToBeTX;                    /*!<   A counter. It indicates how many data it will be transmitted through the UART      */
uint32_t TX_inProgress;                 /*!<   It indicates if a transmission is in progress                                      */
uint8_t  *myPtr;                        /*!<   Pointer to point out the data from the external sensor                             */



/* MAIN */
int main( void )
{
    uint8_t  myTX_buff[4]     =  { 0 };
    uint32_t myCounterData    =  0;
    uint32_t myCounterTimeout =  0;


    SPI_parameters_t    myAS3933_SPI_parameters;
    AS3933_status_t     aux;
    AS3933_data_t       myAS3933_data;


    conf_GPIO   ();
    conf_GPIOTE ();
    conf_UART   ();



    /* SPI definition */
    myAS3933_SPI_parameters.SPIinstance         =    NRF_SPI0;
    myAS3933_SPI_parameters.MOSI                =    SPI0_MOSI;
    myAS3933_SPI_parameters.MISO                =    SPI0_MISO;
    myAS3933_SPI_parameters.SCLK                =    SPI0_SCK;
    myAS3933_SPI_parameters.CS                  =    SPI0_CS;
    myAS3933_SPI_parameters.Freq                =    SPI_FREQUENCY_FREQUENCY_M1;
    myAS3933_SPI_parameters.MISOport            =    NRF_GPIO;
    myAS3933_SPI_parameters.MOSIport            =    NRF_GPIO;
    myAS3933_SPI_parameters.SCLKport            =    NRF_GPIO;
    myAS3933_SPI_parameters.CSport              =    NRF_GPIO;
    myAS3933_SPI_parameters.SPIbyte_order       =    SPI_ORDER_MSB_FIRST;
    myAS3933_SPI_parameters.SPImode             =    SPI_MODE_1;
    myAS3933_SPI_parameters.SPIenable_line_mode =    SPI_ENABLE_LINE_HIGH;



    /* Configure SPI peripheral */
    aux  =   AS3933_Init ( myAS3933_SPI_parameters );

    /* Write and Read the wakeup pattern */
    myAS3933_data.patt1b     =   TS1_WAKEUP_PATTERN_PATT1B;
    myAS3933_data.patt2b     =   TS2_WAKEUP_PATTERN_PATT2B;
    aux  =   AS3933_SetWakeUpPattern    ( myAS3933_SPI_parameters, myAS3933_data );
    aux  =   AS3933_GetWakeUpPattern    ( myAS3933_SPI_parameters, &myAS3933_data );

    /* Configure All channels in Listening mode */
    aux  =   AS3933_SetLowPowerMode ( myAS3933_SPI_parameters, AS3933_CH1_ON_CH2_ON_CH3_ON, AS3933_STANDARD_LISTENING_MODE, 0 );

    /* Configure Crystal oscillator enabled without output signal displayed on CL_DAT pin */
    aux  =   AS3933_SetClockGenerator ( myAS3933_SPI_parameters, EN_XTAL_ENABLED, CLOCK_GEN_DIS_DISABLED );

    /* Configure Antenna dumper disabled */
    aux  =   AS3933_SetAntennaDamper ( myAS3933_SPI_parameters, ATT_ON_DISABLED, 0 );

    /* Configure Envelop detector time constant = 4096 symbol rate */
    aux  =   AS3933_SetEnvelopDetector ( myAS3933_SPI_parameters, FS_ENV_SYMBOL_RATE_4096 );

    /* Configure Data slicer. Threshold disabled, 2.3ms preamble length */
    aux  =   AS3933_SetDataSlicer ( myAS3933_SPI_parameters, ABS_HY_DISABLED, FS_SCL_PREAMBLE_LENGTH_2_3 );

    /* Configure Comparator Hysteresis. Both edges, 40mV */
    aux  =   AS3933_SetComparatorHysteresis ( myAS3933_SPI_parameters, HY_POS_HYSTERESIS_BOTH_EDGES, HY_20M_COMPARATOR_HYSTERESIS_40MV );

    /* Configure Gain reduction, No gain reduction at all */
    aux  =   AS3933_SetGainReduction ( myAS3933_SPI_parameters, GR_GAIN_REDUCTION_NO_GAIN_REDUCTION );

    /* Configure Operating frequency range: 95-150 kHz */
    aux  =   AS3933_SetOperatingFrequencyRange ( myAS3933_SPI_parameters, BAND_SEL_RANGE_95_150_KHZ );

    /* Configure Frequency detection tolerance: Tight */
    aux  =   AS3933_SetFrequencyDetectionTolerance  ( myAS3933_SPI_parameters, AS3933_TOLERANCE_TIGHT );

    /* Configure Sensitivity boost: Disabled */
    aux  =   AS3933_SetGainBoost ( myAS3933_SPI_parameters, G_BOOST_DISABLED );

    /* Configure AGC: AGC acting only on the first carrier burst is disabled and AGC operating in both direction ( up-down ) */
    aux  =   AS3933_SetAGC ( myAS3933_SPI_parameters, AGC_TLIM_DISABLED, AGC_UD_UP_DOWN_MODE );

    /* Configure Do mask data before wakeup */
    aux  =   AS3933_SetDataMask ( myAS3933_SPI_parameters, DAT_MASK_ENABLED );

    /* Configure Clock Generator: Crystal oscillator enabled, do NOT clock signal on CL_DAT pin  */
    aux  =   AS3933_SetClockGenerator ( myAS3933_SPI_parameters, EN_XTAL_ENABLED, CLOCK_GEN_DIS_DISABLED );

    /* Configure Correlator: Enabled, 16 bit pattern and Manchester decoder enabled  */
    aux  =   AS3933_SetCorrelator ( myAS3933_SPI_parameters, EN_WPAT_ENABLED, PATT32_16_BITS, T_HBIT_BIT_RATE_12, EN_MANCH_ENABLED );

    /* Configure Automatic Timeout: 50ms  */
    aux  =   AS3933_SetAutomaticTimeOut ( myAS3933_SPI_parameters, T_OUT_50_MSEC );

    /* Configure Input capacitor bank: NO capacitance in any channels  */
    aux  =   AS3933_SetParallelTuningCapacitance ( myAS3933_SPI_parameters, AS3933_CHANNEL_LF1P, AS3933_CAPACITANCE_ADDS_NONE );
    aux  =   AS3933_SetParallelTuningCapacitance ( myAS3933_SPI_parameters, AS3933_CHANNEL_LF2P, AS3933_CAPACITANCE_ADDS_NONE );
    aux  =   AS3933_SetParallelTuningCapacitance ( myAS3933_SPI_parameters, AS3933_CHANNEL_LF3P, AS3933_CAPACITANCE_ADDS_NONE );

    /* Configure Artificial wakeup: Disabled  */
    aux  =   AS3933_SetArtificialWakeUp ( myAS3933_SPI_parameters, T_AUTO_NO_ARTIFICIAL_WAKEUP );


    mySTATE  =   0;                                                                                                     // Reset the variable

    while( 1 )
    {
        //NRF_POWER->SYSTEMOFF = 1;
        NRF_POWER->TASKS_LOWPWR = 1;                                                                                    // Sub power mode: Low power.

        // Enter System ON sleep mode
        __WFE();
        // Make sure any pending events are cleared
        __SEV();
        __WFE();


        NRF_GPIO->OUTCLR             |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );              // Turn all the LEDs on
        if ( mySTATE == 1 )
        {
            NVIC_DisableIRQ ( GPIOTE_IRQn );                                                                            // GPIOTE Interrupt DISABLED

            /*  Get data ( 8-bits, Manchester ).

                NOTE:   Make sure the transmitter is sending data otherwise a little delay will
                        be introduced by myCounterTimeout.
            */
            myAS3933_data.data   =   0;

            for ( myCounterData = 0; myCounterData < 8; myCounterData++ )
            {
                /*  Wait until rising edges on CLD pin or Timeout */
                myCounterTimeout    =   2323;
                while ( ( ( NRF_GPIO->IN & GPIO_IN_PIN14_Msk ) == ( GPIO_IN_PIN14_Low << GPIO_IN_PIN14_Pos ) ) && ( myCounterTimeout > 0 ) )
                {
                    myCounterTimeout--;
                }

                /*  Process the data */
                myAS3933_data.data <<=   1;

                if ( ( NRF_GPIO->IN & GPIO_IN_PIN13_Msk )  == ( GPIO_IN_PIN13_High << GPIO_IN_PIN13_Pos ) )
                {
                    myAS3933_data.data  |=  1;
                }

                /*  Wait until CLD pin goes low again or Timeout */
                myCounterTimeout    =   2323;
                while ( ( ( NRF_GPIO->IN & GPIO_IN_PIN14_Msk ) == ( GPIO_IN_PIN14_High << GPIO_IN_PIN14_Pos ) ) && ( myCounterTimeout > 0 ) )
                {
                    myCounterTimeout--;
                }
            }


            /* Get RSSI  */
            aux  =   AS3933_GetRSSI ( myAS3933_SPI_parameters, &myAS3933_data );


            /* Prepare the data to be sent */
            myTX_buff[0]                 =   myAS3933_data.data;
            myTX_buff[1]                 =   myAS3933_data.rssi1;
            myTX_buff[2]                 =   myAS3933_data.rssi2;
            myTX_buff[3]                 =   myAS3933_data.rssi3;


            /* Send data through the UART   */
            myPtr                        =   &myTX_buff[0];
            TX_inProgress                =   YES;
            NRF_UART0->TASKS_STARTTX     =   1;
            NRF_UART0->TXD               =   *myPtr++;                                                              // Start transmission

            /* Wait until the message is transmitted */
            while ( TX_inProgress == YES )
            {
                __WFE();
                // Make sure any pending events are cleared
                __SEV();
                __WFE();
            }


            mySTATE             =   0;
            NVIC_EnableIRQ ( GPIOTE_IRQn );                                                                         // GPIOTE Interrupt ENABLED
        }
        NRF_GPIO->OUTSET             |= ( ( 1 << LED1 ) | ( 1 << LED2 ) | ( 1 << LED3 ) | ( 1 << LED4 ) );          // Turn all the LEDs off
        //__NOP();
    }
}
