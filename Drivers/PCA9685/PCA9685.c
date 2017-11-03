/**
 * @brief       PCA9685.h
 * @details     16-channel, 12-bit PWM Fm+ I2C-bus LED controller.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        31/October/2017
 * @version     31/October/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "PCA9685.h"


/**
 * @brief       PCA9685_Init ( I2C_parameters_t )
 *
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of PCA9685_Init.
 *
 *
 * @author      Manuel Caballero
 * @date        31/October/2017
 * @version     31/October/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
PCA9685_status_t  PCA9685_Init ( I2C_parameters_t myI2Cparameters )
{
    i2c_status_t aux;

    aux  =   i2c_init ( myI2Cparameters );



    if ( aux == I2C_SUCCESS )
        return   PCA9685_SUCCESS;
    else
        return   PCA9685_FAILURE;
}



/**
 * @brief       PCA9685_SoftReset ( I2C_parameters_t )
 *
 * @details     It performs a software reset.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of PCA9685_SoftReset.
 *
 *
 * @author      Manuel Caballero
 * @date        1/November/2017
 * @version     1/November/2017     The ORIGIN
 * @pre         The device will be ready to be addressed again within
 *              the specified bus free time ( t_BUF ).
 * @warning     NaN.
 */
PCA9685_status_t  PCA9685_SoftReset   ( I2C_parameters_t myI2Cparameters )
{
    uint8_t      cmd   =   SWRST;
    i2c_status_t aux;


    myI2Cparameters.ADDR    =   GENERAL_CALL_ADDRESS;


    aux = i2c_write ( myI2Cparameters, &cmd, 1, I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   PCA9685_SUCCESS;
    else
        return   PCA9685_FAILURE;
}




/**
 * @brief       PCA9685_SetMode ( I2C_parameters_t , PCA9685_mode1_sleep_t )
 *
 * @details     It configures the device in Low power mode or in Normal operation
 *              mode.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myMode:            Sleep or Normal mode.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of PCA9685_SetMode.
 *
 *
 * @author      Manuel Caballero
 * @date        2/November/2017
 * @version     2/November/2017     The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
PCA9685_status_t  PCA9685_SetMode   ( I2C_parameters_t myI2Cparameters, PCA9685_mode1_sleep_t myMode )
{
    uint8_t      cmd[]   =   { MODE1, 0 };
    i2c_status_t aux;


    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &cmd[1], 1 );
    cmd[1]  &=  ~MODE1_SLEEP_MASK;
    cmd[1]  |=   myMode;


    aux = i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    if ( aux == I2C_SUCCESS )
        return   PCA9685_SUCCESS;
    else
        return   PCA9685_FAILURE;
}




/**
 * @brief       PCA9685_SetPWM_Freq ( I2C_parameters_t , float )
 *
 * @details     It sets a new PWM frequency.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myNewFrequency:    New PWM frequency.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of PCA9685_SetPWM_Freq.
 *
 *
 * @author      Manuel Caballero
 * @date        2/November/2017
 * @version     2/November/2017     The ORIGIN
 * @pre         This library can ONLY work with the internal clock, otherwise
 *              PCA9685_INTERNAL_CLOCK must be changed in the header file.
 * @warning     NaN.
 */
PCA9685_status_t  PCA9685_SetPWM_Freq ( I2C_parameters_t myI2Cparameters, float myNewFrequency )
{
    uint8_t      cmd[]       =   { MODE1, 0 };
    uint8_t      prev_mode1  =   0;
    //float        aux_pre     =   0;
    i2c_status_t aux;


    // The maximum PWM frequency is 1526 Hz and the minimum PWM frequency is 24 Hz.
    if ( ( myNewFrequency < 24 ) || ( myNewFrequency > 1526 ) )
        return   PCA9685_FAILURE;


    // The device MUST be in SLEEP mode
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], 1, I2C_NO_STOP_BIT );
    aux      =   i2c_read  ( myI2Cparameters, &prev_mode1, 1 );
    cmd[1]   =   ( prev_mode1 | MODE1_SLEEP_ENABLED );
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


    // Calculate the new PWM frequency
    if ( myNewFrequency == 24 )
        cmd[1]   =   255;
    else
        cmd[1]   =   _MYROUND ( ( PCA9685_INTERNAL_CLOCK / ( PCA9685_ADC_STEPS * myNewFrequency ) ) - 1 );


    cmd[0]   =   PRE_SCALE;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );


    // Restore the device's mode
    cmd[0]   =   MODE1;
    cmd[1]   =   prev_mode1;
    aux      =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );




    if ( aux == I2C_SUCCESS )
        return   PCA9685_SUCCESS;
    else
        return   PCA9685_FAILURE;
}




/**
 * @brief       PCA9685_SetPWM_DutyCycle ( I2C_parameters_t , PCA9685_led_channel_t , uint8_t , uint8_t )
 *
 * @details     It sets a new PWM duty cycle on the given LED ( channel ).
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    myLEDchannel:      Chosen LED ( channel ).
 * @param[in]    myDelay:           PWM delay.
 * @param[in]    myPWM_DutyCycle:   PWM duty cycle.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of PCA9685_SetPWM_DutyCycle.
 *
 *
 * @author      Manuel Caballero
 * @date        3/November/2017
 * @version     3/November/2017     The ORIGIN
 * @pre         Datasheet p.15 ( Example 1 and Example 2).
 * @warning     NaN.
 */
PCA9685_status_t  PCA9685_SetPWM_DutyCycle ( I2C_parameters_t myI2Cparameters, PCA9685_led_channel_t myLEDchannel, uint8_t myDelay, uint8_t myPWM_DutyCycle )
{
    uint8_t      cmd[]       =   { 0, 0 };
    uint32_t     myAux       =   0;

    i2c_status_t aux;


    // The range is from 0% up to 100%.
    if ( ( myDelay > 100 ) || ( myPWM_DutyCycle > 100 ) )
        return   PCA9685_FAILURE;



    // DELAY TIME: LEDn_ON_L + LEDn_ON_H
    myAux   =   _MYROUND ( ( myDelay / 100.0 ) * PCA9685_ADC_STEPS ) - 1;

    // LEDn_ON_L
    cmd[0]  =   LED0_ON_L + ( myLEDchannel << 2 );
    cmd[1]  =   ( myAux & 0xFF );

    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );

    // LEDn_ON_H
    cmd[0]  =   LED0_ON_H + ( myLEDchannel << 2 );
    cmd[1]  =   ( ( myAux >> 8 ) & 0xFF );

    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );



    // LED OFF TIME: LEDn_OFF_L + LEDn_OFF_H
    myAux  +=    _MYROUND ( ( myPWM_DutyCycle / 100.0 ) * PCA9685_ADC_STEPS );

    if ( ( myDelay + myPWM_DutyCycle ) <= 100 )
        myAux--;
    else
        myAux   +=   -4096;


    // LEDn_OFF_L
    cmd[0]  =   LED0_OFF_L + ( myLEDchannel << 2 );
    cmd[1]  =   ( myAux & 0xFF );

    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );

    // LEDn_OFF_H
    cmd[0]  =   LED0_OFF_H + ( myLEDchannel << 2 );
    cmd[1]  =   ( ( myAux >> 8 ) & 0xFF );

    aux     =   i2c_write ( myI2Cparameters, &cmd[0], sizeof( cmd )/sizeof( cmd[0] ), I2C_STOP_BIT );






    if ( aux == I2C_SUCCESS )
        return   PCA9685_SUCCESS;
    else
        return   PCA9685_FAILURE;
}
