/**
 * @brief       HX711.c
 * @details     24-Bit Analog-to-Digital Converter (ADC) for Weigh Scales.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        14/September/2017
 * @version     14/September/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

 #include "HX711.h"

/**
 * @brief       HX711_Reset   ( void )
 *
 * @details     It performs an internal reset.
 *
 * @param[in]    NaN.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of HX711_Reset.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2017
 * @version     14/September/2017   The ORIGIN
 * @pre         When PD_SCK pin changes from low to high and stays at high for
 *              longer than 60μs, HX711 enters power down mode.
 *
 *              When PD_SCK returns to low, chip will reset and enter normal
 *              operation mode.
 * @warning     NaN.
 */
HX711_status_t  HX711_Reset   ( NRF_GPIO_Type* myDOUT, NRF_GPIO_Type* myPD_SCK )
{
    _PD_SCK  =  HX711_PIN_HIGH;
    wait_us ( 120 );                                                            // Datasheet p5. At least 60us ( Security Factor: 2*60us = 120us )
    _PD_SCK  =  HX711_PIN_LOW;



    if ( _DOUT == HX711_PIN_HIGH )
        return   HX711_SUCCESS;
    else
        return   HX711_FAILURE;
}



/**
 * @brief       HX711_PowerDown   ( void )
 *
 * @details     It puts the device in power-down mode.
 *
 * @param[in]    NaN.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of HX711_PowerDown.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2017
 * @version     14/September/2017   The ORIGIN
 * @pre         When PD_SCK pin changes from low to high and stays at high for
 *              longer than 60μs, HX711 enters power down mode.
 * @warning     NaN.
 */
HX711_status_t  HX711_PowerDown   ( NRF_GPIO_Type* myDOUT, NRF_GPIO_Type* myPD_SCK )
{
    _PD_SCK  =  HX711_PIN_HIGH;
    wait_us ( 120 );                                                            // Datasheet p5. At least 60us ( Security Factor: 2*60us = 120us )



    if ( _DOUT == HX711_PIN_HIGH )
        return   HX711_SUCCESS;
    else
        return   HX711_FAILURE;
}



/**
 * @brief       HX711_SetChannelAndGain   ( HX711_channel_gain_t myChannel_Gain )
 *
 * @details     It sets both the channel and the gain for the next measurement.
 *
 * @param[in]    myChannel_Gain:    Channel and Gain to perform the new measurement.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of HX711_SetChannelAndGain.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2017
 * @version     14/September/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
HX711_status_t  HX711_SetChannelAndGain    ( NRF_GPIO_Type* myDOUT, NRF_GPIO_Type* myPD_SCK, HX711_channel_gain_t myChannel_Gain )
{
    uint32_t myPulses   =    0;
    uint32_t i          =    0;                                                 // Counter and timeout variable

    // Select the gain/channel
    switch ( myChannel_Gain ) {
        default:
        case CHANNEL_A_GAIN_128:
            _HX711_CHANNEL_GAIN  =   CHANNEL_A_GAIN_128;                        // Update the gain parameter
            myPulses             =   25;
            break;

        case CHANNEL_B_GAIN_32:
            _HX711_CHANNEL_GAIN  =   CHANNEL_B_GAIN_32;                         // Update the gain parameter
            myPulses             =   26;
            break;

        case CHANNEL_A_GAIN_64:
            _HX711_CHANNEL_GAIN  =   CHANNEL_A_GAIN_64;                         // Update the gain parameter
            myPulses             =   27;
            break;
    }


    // Wait until the device is ready or timeout
    i        =   23232323;
    _PD_SCK  =  HX711_PIN_LOW;
    while ( ( _DOUT == HX711_PIN_HIGH ) && ( --i ) );

    // Check if something is wrong with the device because of the timeout
    if ( i < 1 )
        return   HX711_FAILURE;

    // Change the gain for the NEXT mesurement ( previous data will be ignored )
    do {
        wait_us ( 1 );                                                          // Datasheet p5. T3 and T4 ( Min. 0.2us | Typ. 1us )
        _PD_SCK  =  HX711_PIN_HIGH;
        wait_us ( 1 );                                                          // Datasheet p5. T3 and T4 ( Min. 0.2us | Typ. 1us )
        _PD_SCK  =  HX711_PIN_LOW;

        myPulses--;
    } while ( myPulses > 0 );




    if ( _DOUT == HX711_PIN_HIGH )
        return   HX711_SUCCESS;
    else
        return   HX711_FAILURE;
}



/**
 * @brief       HX711_GetChannelAndGain   ( void )
 *
 * @details     It gets both the channel and the gain for the current measurement.
 *
 * @param[in]    NaN.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Channel and Gain.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2017
 * @version     14/September/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
HX711_channel_gain_t  HX711_GetChannelAndGain ( void )
{
    return   _HX711_CHANNEL_GAIN;
}



/**
 * @brief       HX711_ReadRawData   ( HX711_channel_gain_t myChannel_Gain, Vector_count_t*, uint32_t )
 *
 * @details     It reads the raw data from the device according to the channel
 *              and its gain.
 *
 * @param[in]    myChannel_Gain:    Channel and Gain to perform the new read.
 * @param[in]    myAverage:         How many measurement we have to get and deliver the average.
 *
 * @param[out]   myNewRawData:      The new value from the device.
 *
 *
 * @return       Status of HX711_ReadRawData.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2017
 * @version     14/September/2017   Gain mode was fixed, now it gets the value
 *                                  a given gain/channel. A timeout was added to
 *                                  avoid the microcontroller gets stuck.
 *              11/September/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
HX711_status_t  HX711_ReadRawData    ( NRF_GPIO_Type* myDOUT, NRF_GPIO_Type* myPD_SCK, HX711_channel_gain_t myChannel_Gain, Vector_count_t* myNewRawData, uint32_t myAverage )
{
    uint32_t i           =   0;                                                 // Counter and timeout variable
    uint32_t ii          =   0;                                                 // Counter variable
    uint32_t myAuxData   =   0;
    uint32_t myPulses    =   0;



    myNewRawData->myRawValue    =   0;                                          // Reset variable at the beginning

    // Check the gain if it is different, update it ( previous data will be ignored! )
    if ( myChannel_Gain != _HX711_CHANNEL_GAIN )
        HX711_SetChannelAndGain ( myChannel_Gain );


    // Start collecting the new measurement as many as myAverage
    for ( ii = 0; ii < myAverage; ii++ ) {
        // Reset the value
        myAuxData    =   0;

        // Wait until the device is ready or timeout
        i        =   23232323;
        _PD_SCK  =  HX711_PIN_LOW;
        while ( ( _DOUT == HX711_PIN_HIGH ) && ( --i ) );

        // Check if something is wrong with the device because of the timeout
        if ( i < 1 )
            return   HX711_FAILURE;


        // Read the data
        for ( i = 0; i < 24; i++ ) {
            wait_us ( 1 );                                                      // Datasheet p5. T3 and T4 ( Min. 0.2us | Typ. 1us )
            _PD_SCK  =  HX711_PIN_HIGH;
            wait_us ( 1 );                                                      // Datasheet p5. T3 and T4 ( Min. 0.2us | Typ. 1us )
            myAuxData    <<=     1;
            _PD_SCK  =  HX711_PIN_LOW;

            // High or Low bit
            if ( _DOUT == HX711_PIN_HIGH )
                myAuxData++;
        }

        // Last bit to release the bus
        wait_us ( 1 );                                                          // Datasheet p5. T3 and T4 ( Min. 0.2us | Typ. 1us )
        _PD_SCK  =  HX711_PIN_HIGH;
        wait_us ( 1 );                                                          // Datasheet p5. T3 and T4 ( Min. 0.2us | Typ. 1us )
        _PD_SCK  =  HX711_PIN_LOW;


        // Depending on the Gain we have to generate more CLK pulses
        switch ( _HX711_CHANNEL_GAIN ) {
            default:
            case CHANNEL_A_GAIN_128:
                myPulses             =   25;
                break;

            case CHANNEL_B_GAIN_32:
                myPulses             =   26;
                break;

            case CHANNEL_A_GAIN_64:
                myPulses             =   27;
                break;
        }

        // Generate those extra pulses for the next measurement
        for ( i = 25; i < myPulses; i++ ) {
            wait_us ( 1 );                                                      // Datasheet p5. T3 and T4 ( Min. 0.2us | Typ. 1us )
            _PD_SCK  =  HX711_PIN_HIGH;
            wait_us ( 1 );                                                      // Datasheet p5. T3 and T4 ( Min. 0.2us | Typ. 1us )
            _PD_SCK  =  HX711_PIN_LOW;
        }

        // Update data to get the average
        myAuxData                  ^=    0x800000;
        myNewRawData->myRawValue   +=    myAuxData;
    }

    myNewRawData->myRawValue    /=    ( float )myAverage;



    if ( _DOUT == HX711_PIN_HIGH )
        return   HX711_SUCCESS;
    else
        return   HX711_FAILURE;
}



/**
 * @brief       HX711_ReadData_WithCalibratedMass ( HX711_channel_gain_t myChannel_Gain, Vector_count_t* myNewRawData, uint32_t myAverage )
 *
 * @details     It reads data with a calibrated mass on the load cell.
 *
 * @param[in]    myChannel_Gain:        Gain/Channel to perform the new measurement.
 * @param[in]    myAverage:             How many data to read.
 *
 * @param[out]   myNewRawData:          myRawValue_WithCalibratedMass ( ADC code taken with calibrated mass ).
 *
 *
 * @return       Status of HX711_ReadData_WithCalibratedMass.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2017
 * @version     14/September/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
HX711_status_t  HX711_ReadData_WithCalibratedMass   ( NRF_GPIO_Type* myDOUT, NRF_GPIO_Type* myPD_SCK, HX711_channel_gain_t myChannel_Gain, Vector_count_t* myNewRawData, uint32_t myAverage )
{
    HX711_status_t        aux;

    // Perform a new bunch of readings
    aux  =   HX711_ReadRawData ( myChannel_Gain, myNewRawData, myAverage );


    // Update the value with a calibrated mass
    myNewRawData->myRawValue_WithCalibratedMass  =   myNewRawData->myRawValue;



    if ( aux == HX711_SUCCESS )
        return   HX711_SUCCESS;
    else
        return   HX711_FAILURE;
}



/**
 * @brief       HX711_ReadData_WithoutMass ( HX711_channel_gain_t myChannel_Gain, Vector_count_t* myNewRawData, uint32_t myAverage )
 *
 * @details     It reads data without any mass on the load cell.
 *
 * @param[in]    myChannel_Gain:        Gain/Channel to perform the new measurement.
 * @param[in]    myAverage:             How many data to read.
 *
 * @param[out]   myNewRawData:          myRawValue_WithoutCalibratedMass ( ADC code taken without any mass ).
 *
 *
 * @return       Status of HX711_ReadData_WithoutMass.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2017
 * @version     14/September/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
HX711_status_t  HX711_ReadData_WithoutMass   ( NRF_GPIO_Type* myDOUT, NRF_GPIO_Type* myPD_SCK, HX711_channel_gain_t myChannel_Gain, Vector_count_t* myNewRawData, uint32_t myAverage )
{
    HX711_status_t        aux;

    // Perform a new bunch of readings
    aux  =   HX711_ReadRawData ( myChannel_Gain, myNewRawData, myAverage );


    // Update the value without any mass
    myNewRawData->myRawValue_WithoutCalibratedMass  =   myNewRawData->myRawValue;



    if ( aux == HX711_SUCCESS )
        return   HX711_SUCCESS;
    else
        return   HX711_FAILURE;
}



/**
 * @brief       HX711_CalculateMass ( Vector_count_t* myNewRawData, uint32_t myCalibratedMass, HX711_scale_t myScaleCalibratedMass )
 *
 * @details     It calculates the mass.
 *
 * @param[in]    myNewRawData:              It has myRawValue_WithCalibratedMass ( ADC code taken with calibrated mass ),
 *                                          myRawValue_WithoutCalibratedMass ( ADC code taken without any mass ) and
 *                                          myRawValue ( the current data taken by the system ).
 * @param[in]    myCalibratedMass:          A known value for the calibrated mass when myRawValue_WithCalibratedMass was
 *                                          calculated.
 * @param[in]    myScaleCalibratedMass:     The range of the calibrated mass ( kg, g, mg or ug ).
 *
 * @param[out]   NaN.
 *
 *
 * @return       The calculated mass.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2017
 * @version     14/September/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
Vector_mass_t  HX711_CalculateMass ( Vector_count_t* myNewRawData, float myCalibratedMass, HX711_scale_t myScaleCalibratedMass )
{
    // Terminology by Texas Instruments: sbau175a.pdf, p8 2.1.1 Calculation of Mass
    float m, w_zs;
    float c_zs, w_fs, c_fs, w_t;
    float c = 0;
    float myFactor   =   1.0;

    Vector_mass_t w;


    // Adapt the scale ( kg as reference )
    switch ( myScaleCalibratedMass ) {
        default:
        case HX711_SCALE_kg:
            // myFactor     =   1.0;
            break;

        case HX711_SCALE_g:
            myFactor     /=   1000.0;
            break;

        case HX711_SCALE_mg:
            myFactor     /=   1000000.0;
            break;

        case HX711_SCALE_ug:
            myFactor     /=   1000000000.0;
            break;

    }


    // Calculate the Calibration Constant ( m )
    w_fs    =    ( myCalibratedMass / myFactor );                               // User-specified calibration mass
    c_zs    =    myNewRawData->myRawValue_WithoutCalibratedMass;                // ADC measurement taken with no load
    c_fs    =    myNewRawData->myRawValue_WithCalibratedMass;                   // ADC code taken with the calibration mass applied

    m       =    ( float )( w_fs / ( ( c_fs ) - c_zs  ) );                      // The Calibration Constant


    // Calculate the zero-scale mass ( w_zs )
    w_zs    =    - ( m * c_zs );


    // Calculate the mass ( w )
    w_t     =    myNewRawData->myRawValue_TareWeight;                           // ADC code taken without any mass after the system is calibrated;
    c       =    myNewRawData->myRawValue;                                      // The ADC code

    w.myMass   =    ( m * c ) + w_zs - w_t;                                     // The mass according to myScaleCalibratedMass


    // Update Internal Parameters
    _HX711_USER_CALIBATED_MASS   =   myCalibratedMass;
    _HX711_SCALE                 =   myScaleCalibratedMass;



    return   w;
}



/**
 * @brief       HX711_SetAutoTare ( HX711_channel_gain_t ,float ,HX711_scale_t ,Vector_count_t* ,float )
 *
 * @details     It reads data without any mass on the load cell after the system is calibrated to calculate the tare weight.
 *
 * @param[in]    myChannel_Gain:            Gain/Channel to perform the new measurement.
 * @param[in]    myCalibratedMass:          A known value for the calibrated mass when myRawValue_WithCalibratedMass was
 *                                          calculated.
 * @param[in]    myScaleCalibratedMass:     The range of the calibrated mass ( kg, g, mg or ug ).
 * @param[in]    myTime:                    How long the auto-set lasts.
 *
 * @param[out]   myNewRawData:              myRawValue_TareWeight ( ADC code taken without any mass ).
 *
 *
 * @return       Status of HX711_SetAutoTare.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2017
 * @version     14/September/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
HX711_status_t  HX711_SetAutoTare   ( NRF_GPIO_Type* myDOUT, NRF_GPIO_Type* myPD_SCK, HX711_channel_gain_t myChannel_Gain, float myCalibratedMass, HX711_scale_t myScaleCalibratedMass, Vector_count_t* myNewRawData, float myTime )
{
    HX711_status_t        aux;
    Vector_mass_t         myCalculatedMass;
    float                 myAuxData = 0;
    uint32_t              i = 0;


    // Perform a new bunch of readings every 1 second
    for ( i = 0; i < myTime; i++ ) {
        aux          =   HX711_ReadRawData ( myChannel_Gain, myNewRawData, 10 );
        myAuxData   +=   myNewRawData->myRawValue;
        wait(1);
    }

    myNewRawData->myRawValue    =    ( float )( myAuxData / myTime );

    // Turn it into mass
    myCalculatedMass     =   HX711_CalculateMass ( myNewRawData, myCalibratedMass, myScaleCalibratedMass );

    // Update the value without any mass
    myNewRawData->myRawValue_TareWeight  =   myCalculatedMass.myMass;


    // Update Internal Parameters
    _HX711_USER_CALIBATED_MASS   =   myCalibratedMass;
    _HX711_SCALE                 =   myScaleCalibratedMass;



    if ( aux == HX711_SUCCESS )
        return   HX711_SUCCESS;
    else
        return   HX711_FAILURE;
}



/**
 * @brief       HX711_SetManualTare ( float myTareWeight )
 *
 * @details     It sets a tare weight manually.
 *
 * @param[in]    myTareWeight:          Tare weight.
 *
 * @param[out]   NaN.
 *
 *
 * @return       myRawValue_TareWeight.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2017
 * @version     14/September/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
Vector_count_t  HX711_SetManualTare   ( float myTareWeight )
{
    Vector_count_t myNewTareWeight;

    // Update the value defined by the user
    myNewTareWeight.myRawValue_TareWeight  =   myTareWeight;



    return   myNewTareWeight;
}



/**
 * @brief       HX711_CalculateVoltage ( Vector_count_t* ,float )
 *
 * @details     It calculates the mass.
 *
 * @param[in]    myChannel_Gain:            Gain/Channel of the measurement.
 * @param[in]    myNewRawData:              myRawValue ( the current data taken by the system ).
 * @param[in]    myVoltageReference:        The voltage at the converter reference input.
 *
 * @param[out]   NaN.
 *
 *
 * @return       The calculated voltage.
 *
 *
 * @author      Manuel Caballero
 * @date        14/September/2017
 * @version     14/September/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
Vector_voltage_t  HX711_CalculateVoltage ( Vector_count_t* myNewRawData, float myVoltageReference )
{
    // Terminology by Texas Instruments: sbau175a.pdf, p12 3.2 Measurement Modes Raw
    float x, B, A;

    Vector_voltage_t v;


    x   =    myNewRawData->myRawValue;
    B   =    ( 16777216.0 - 1.0 );

    // Adatp the gain
    switch ( _HX711_CHANNEL_GAIN ) {
        default:
        case CHANNEL_A_GAIN_128:
            A             =   128.0;
            break;

        case CHANNEL_B_GAIN_32:
            A             =   32.0;
            break;

        case CHANNEL_A_GAIN_64:
            A             =   64.0;
            break;
    }


    // Calculate the voltage ( v )
    v.myVoltage = ( float )( ( x / B ) * ( myVoltageReference / A ) );          // The voltage




    return   v;
}
