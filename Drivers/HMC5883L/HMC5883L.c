/**
 * @brief       HMC5883L.h
 * @details     3-Axis Digital Compass IC.
 *              Functions file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        12/October/2017
 * @version     12/October/2017    The ORIGIN
 * @pre         NaN.
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "HMC5883L.h"


/**
 * @brief       HMC5883L_Conf ( NRF_TWI_Type* , HMC5883L_address_t , HMC5883L_register_list_t , HMC5883L_conf_reg_a_samples_t , HMC5883L_conf_reg_a_dor_t , HMC5883L_conf_reg_a_measurement_mode_t
 *                              HMC5883L_conf_reg_b_gain_t , HMC5883L_mode_register_high_speed_t , HMC5883L_mode_register_operation_mode_t )
 *
 * @details     It configures the device.
 *
 * @param[in]    myinstance:            Peripheral's Instance.
 * @param[in]    myHMC5883LAddr:        I2C Device address.
 * @param[in]    mySamples:             Number of average samples.
 * @param[in]    myDataRate:            Data output rate.
 * @param[in]    myMeasurementMode:     Measurement mode.
 * @param[in]    myGain:                Gain.
 * @param[in]    myI2CMode:             I2C High Speed / Normal speed.
 * @param[in]    myOperationMode:       Operation mode.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of HMC5883L_Conf.
 *
 *
 * @author      Manuel Caballero
 * @date        12/October/2017
 * @version     12/October/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
HMC5883L_status_t  HMC5883L_Conf ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_conf_reg_a_samples_t mySamples, HMC5883L_conf_reg_a_dor_t myDataRate,
                                   HMC5883L_conf_reg_a_measurement_mode_t myMeasurementMode, HMC5883L_conf_reg_b_gain_t myGain, HMC5883L_mode_register_high_speed_t myI2CMode,
                                   HMC5883L_mode_register_operation_mode_t myOperationMode )
{
    uint8_t     cmd[]  =   { 0, 0 };
    uint32_t    aux    =   0;


// CONFIGURATION REGISTER A
    cmd[0]  =    HMC5883L_CONFIGURATION_REGISTER_A;

    // Number of Samples Averaged
    cmd[1]  =   mySamples;

    // Data Output Rate Bits
    cmd[1] |=   myDataRate;

    // Data Output Rate Bits
    cmd[1] |=   myDataRate;

    // Measurement Configuration Bits
    cmd[1] |=   myMeasurementMode;


    // Write the command to Configuration Register A
    aux = i2c_write ( myinstance, myHMC5883LAddr, &cmd[0], 2, I2C_STOP_BIT );



// CONFIGURATION REGISTER A
    cmd[0]  =    HMC5883L_CONFIGURATION_REGISTER_B;

    // Gain Configuration Bits
    cmd[1]  =   myGain;

    // Write the command to Configuration Register B
    aux = i2c_write ( myinstance, myHMC5883LAddr, &cmd[0], 2, I2C_STOP_BIT );



// MODE REGISTER
    cmd[0]  =    HMC5883L_MODE_REGISTER;

    // High Speed I2C, 3400kHz
    cmd[1]  =   myI2CMode;

    // Mode Select Bits
    cmd[1] |=   myOperationMode;


    // Write the command to Mode Register
    aux = i2c_write ( myinstance, myHMC5883LAddr, &cmd[0], 2, I2C_STOP_BIT );





    if ( aux == I2C_SUCCESS )
        return   HMC5883L_SUCCESS;
    else
        return   HMC5883L_FAILURE;
}



/**
 * @brief       HMC5883L_GetIdentificationRegister ( NRF_TWI_Type* , HMC5883L_address_t , HMC5883L_register_list_t , HMC5883L_vector_data_t*  )
 *
 * @details     It gets the identification register.
 *
 * @param[in]    myinstance:        Peripheral's Instance.
 * @param[in]    myHMC5883LAddr:    I2C Device address.
 * @param[in]    myID_reg:          Identification register to be read.
 *
 * @param[out]   myID:            Identification register value.
 *
 *
 * @return       Status of HMC5883L_GetIdentificationRegister.
 *
 *
 * @author      Manuel Caballero
 * @date        12/October/2017
 * @version     12/October/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
HMC5883L_status_t  HMC5883L_GetIdentificationRegister ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_register_list_t myID_reg, HMC5883L_vector_data_t* myID )
{
    uint8_t     cmd  =   0;
    uint32_t    aux  =   0;


    // Write the command
    aux = i2c_write ( myinstance, myHMC5883LAddr, &myID_reg, 1, I2C_NO_STOP_BIT );

    // Read the data
    aux = i2c_read  ( myinstance, myHMC5883LAddr, &cmd, 1 );



    // Choose which ID was requested
    switch ( myID_reg )
    {
    case HMC5883L_IDENTIFICATION_REGISTER_A:
        myID->IdentificationRegisterA    =   cmd;
        break;

    case HMC5883L_IDENTIFICATION_REGISTER_B:
        myID->IdentificationRegisterA    =   cmd;
        break;

    case HMC5883L_IDENTIFICATION_REGISTER_C:
        myID->IdentificationRegisterA    =   cmd;
        break;

    default:
        return   HMC5883L_FAILURE;
    }




    if ( aux == I2C_SUCCESS )
        return   HMC5883L_SUCCESS;
    else
        return   HMC5883L_FAILURE;
}



/**
 * @brief       HMC5883L_GetRawDataOutput ( NRF_TWI_Type* , HMC5883L_address_t , HMC5883L_vector_data_t*  )
 *
 * @details     It gets X, Y and Z data output.
 *
 * @param[in]    myinstance:        Peripheral's Instance.
 * @param[in]    myHMC5883LAddr:    I2C Device address.
 *
 * @param[out]   myData:            X, Y and Z data output.
 *
 *
 * @return       Status of HMC5883L_GetRawDataOutput.
 *
 *
 * @author      Manuel Caballero
 * @date        12/October/2017
 * @version     12/October/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
HMC5883L_status_t  HMC5883L_GetRawDataOutput ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_vector_data_t* myData )
{
    uint8_t     cmd[]  =   { HMC5883L_DATA_OUTPUT_X_MSB, 0, 0, 0, 0, 0 };
    uint32_t    aux    =   0;


    // Write the command
    aux = i2c_write ( myinstance, myHMC5883LAddr, &cmd[0], 1, I2C_NO_STOP_BIT );

    // Read all data
    aux = i2c_read  ( myinstance, myHMC5883LAddr, &cmd[0], 6 );


    // Parse the data
    myData->DataOutput_X     =   ( ( cmd[0] << 8 ) | cmd[1] );
    myData->DataOutput_Y     =   ( ( cmd[2] << 8 ) | cmd[3] );
    myData->DataOutput_Z     =   ( ( cmd[4] << 8 ) | cmd[5] );




    if ( aux == I2C_SUCCESS )
        return   HMC5883L_SUCCESS;
    else
        return   HMC5883L_FAILURE;
}



/**
 * @brief       HMC5883L_GetStatus ( NRF_TWI_Type* , HMC5883L_address_t , HMC5883L_vector_data_t*  )
 *
 * @details     It reads the status register.
 *
 * @param[in]    myinstance:        Peripheral's Instance.
 * @param[in]    myHMC5883LAddr:    I2C Device address.
 *
 * @param[out]   myStatus:          Current status of the device.
 *
 *
 * @return       Status of HMC5883L_GetStatus.
 *
 *
 * @author      Manuel Caballero
 * @date        12/October/2017
 * @version     12/October/2017   The ORIGIN
 * @pre         NaN
 * @warning     NaN.
 */
HMC5883L_status_t  HMC5883L_GetStatus ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_vector_data_t* myStatus )
{
    uint8_t     cmd    =   HMC5883L_STATUS_REGISTER;
    uint32_t    aux    =   0;


    // Write the command
    aux = i2c_write ( myinstance, myHMC5883LAddr, &cmd, 1, I2C_NO_STOP_BIT );

    // Read the status register
    aux = i2c_read  ( myinstance, myHMC5883LAddr, &myStatus->Status, 1 );




    if ( aux == I2C_SUCCESS )
        return   HMC5883L_SUCCESS;
    else
        return   HMC5883L_FAILURE;
}



/**
 * @brief       HMC5883L_ReadRegister ( NRF_TWI_Type* , HMC5883L_address_t , HMC5883L_register_list_t , uint8_t*  )
 *
 * @details     It reads a register.
 *
 * @param[in]    myinstance:        Peripheral's Instance.
 * @param[in]    myHMC5883LAddr:    I2C Device address.
 * @param[in]    myRegister:        The register to be read.
 *
 * @param[out]   myRegisterData:    The value of the register.
 *
 *
 * @return       Status of HMC5883L_ReadRegister.
 *
 *
 * @author      Manuel Caballero
 * @date        12/October/2017
 * @version     12/October/2017   The ORIGIN
 * @pre         This function neither reads the OUTPUTs nor the Status register.
 * @warning     NaN.
 */
HMC5883L_status_t  HMC5883L_ReadRegister ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_register_list_t myRegister, uint8_t* myRegisterData )
{
    uint32_t    aux    =   0;


    // Only three register can be read: Configuration Register A, Configuration Register B and Mode Register
    // NOTE: This function neither reads the OUTPUTs nor the Status register
    if ( myRegister > HMC5883L_MODE_REGISTER )
        return   HMC5883L_FAILURE;


    // Write the command
    aux = i2c_write ( myinstance, myHMC5883LAddr, &myRegister, 1, I2C_NO_STOP_BIT );

    // Read the register
    aux = i2c_read  ( myinstance, myHMC5883LAddr, myRegisterData, 1 );




    if ( aux == I2C_SUCCESS )
        return   HMC5883L_SUCCESS;
    else
        return   HMC5883L_FAILURE;
}



/**
 * @brief       HMC5883L_SetNumSample ( NRF_TWI_Type* , HMC5883L_address_t , HMC5883L_conf_reg_a_samples_t )
 *
 * @details     It configures the number of samples averaged.
 *
 * @param[in]    myinstance:        Peripheral's Instance.
 * @param[in]    myHMC5883LAddr:    I2C Device address.
 * @param[in]    mySamples:         New Number of samples averaged.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of HMC5883L_SetNumSample.
 *
 *
 * @author      Manuel Caballero
 * @date        12/October/2017
 * @version     12/October/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
HMC5883L_status_t  HMC5883L_SetNumSample ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_conf_reg_a_samples_t mySamples )
{
    uint8_t     cmd    =   HMC5883L_CONFIGURATION_REGISTER_A;
    uint32_t    aux    =   0;



    // Write the command
    aux = i2c_write ( myinstance, myHMC5883LAddr, &cmd, 1, I2C_NO_STOP_BIT );

    // Read the configuration register A
    aux = i2c_read  ( myinstance, myHMC5883LAddr, &cmd, 1 );


    // Check if they are different, if so, update the value
    if ( ( cmd & CONF_REG_A_SAMPLE_MASK ) !=   mySamples )
    {
        // Mask [ MA1 to MA0 ] Number of Samples
        cmd &=   ~CONF_REG_A_SAMPLE_MASK;

        // Update number of samples
        cmd |=   mySamples;

        // Write the new value
        aux = i2c_write ( myinstance, myHMC5883LAddr, &cmd, 1, I2C_STOP_BIT );
    }




    if ( aux == I2C_SUCCESS )
        return   HMC5883L_SUCCESS;
    else
        return   HMC5883L_FAILURE;
}



/**
 * @brief       HMC5883L_SetDataRate ( NRF_TWI_Type* , HMC5883L_address_t , HMC5883L_conf_reg_a_dor_t )
 *
 * @details     It configures the data rate.
 *
 * @param[in]    myinstance:        Peripheral's Instance.
 * @param[in]    myHMC5883LAddr:    I2C Device address.
 * @param[in]    myDataRate:        New data rate.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of HMC5883L_SetDataRate.
 *
 *
 * @author      Manuel Caballero
 * @date        12/October/2017
 * @version     12/October/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
HMC5883L_status_t  HMC5883L_SetDataRate ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_conf_reg_a_dor_t myDataRate )
{
    uint8_t     cmd    =   HMC5883L_CONFIGURATION_REGISTER_A;
    uint32_t    aux    =   0;



    // Write the command
    aux = i2c_write ( myinstance, myHMC5883LAddr, &cmd, 1, I2C_NO_STOP_BIT );

    // Read the configuration register A
    aux = i2c_read  ( myinstance, myHMC5883LAddr, &cmd, 1 );


    // Check if they are different, if so, update the value
    if ( ( cmd & CONF_REG_A_DATARATE_MASK ) !=   myDataRate )
    {
        // Mask [ DO2 to DO0 ] Data Output Rate Bits
        cmd &=   ~CONF_REG_A_DATARATE_MASK;

        // Update Data Output Rate Bits
        cmd |=   myDataRate;

        // Write the new value
        aux = i2c_write ( myinstance, myHMC5883LAddr, &cmd, 1, I2C_STOP_BIT );
    }




    if ( aux == I2C_SUCCESS )
        return   HMC5883L_SUCCESS;
    else
        return   HMC5883L_FAILURE;
}



/**
 * @brief       HMC5883L_SetMeasurementConf ( NRF_TWI_Type* , HMC5883L_address_t , HMC5883L_conf_reg_a_measurement_mode_t )
 *
 * @details     It configures the measurement configuration bits.
 *
 * @param[in]    myinstance:        Peripheral's Instance.
 * @param[in]    myHMC5883LAddr:    I2C Device address.
 * @param[in]    myMeasurementMode: New measurement mode.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of HMC5883L_SetMeasurementConf.
 *
 *
 * @author      Manuel Caballero
 * @date        12/October/2017
 * @version     12/October/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
HMC5883L_status_t  HMC5883L_SetMeasurementConf ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_conf_reg_a_measurement_mode_t myMeasurementMode )
{
    uint8_t     cmd    =   HMC5883L_CONFIGURATION_REGISTER_A;
    uint32_t    aux    =   0;



    // Write the command
    aux = i2c_write ( myinstance, myHMC5883LAddr, &cmd, 1, I2C_NO_STOP_BIT );

    // Read the configuration register A
    aux = i2c_read  ( myinstance, myHMC5883LAddr, &cmd, 1 );


    // Check if they are different, if so, update the value
    if ( ( cmd & CONF_REG_A_MODE_MASK ) !=   myMeasurementMode )
    {
        // Mask [ MS1 to MS0 ] Measurement Configuration Bits
        cmd &=   ~CONF_REG_A_MODE_MASK;

        // Update Measurement Configuration Bits
        cmd |=   myMeasurementMode;

        // Write the new value
        aux = i2c_write ( myinstance, myHMC5883LAddr, &cmd, 1, I2C_STOP_BIT );
    }




    if ( aux == I2C_SUCCESS )
        return   HMC5883L_SUCCESS;
    else
        return   HMC5883L_FAILURE;
}



/**
 * @brief       HMC5883L_SetGain ( NRF_TWI_Type* , HMC5883L_address_t , HMC5883L_conf_reg_b_gain_t )
 *
 * @details     It configures the gain/resolution.
 *
 * @param[in]    myinstance:        Peripheral's Instance.
 * @param[in]    myHMC5883LAddr:    I2C Device address.
 * @param[in]    myGain:            New gain/resolution.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of HMC5883L_SetGain.
 *
 *
 * @author      Manuel Caballero
 * @date        12/October/2017
 * @version     12/October/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
HMC5883L_status_t  HMC5883L_SetGain ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_conf_reg_b_gain_t myGain )
{
    uint8_t     cmd    =   HMC5883L_CONFIGURATION_REGISTER_B;
    uint32_t    aux    =   0;



    // Write the command
    aux = i2c_write ( myinstance, myHMC5883LAddr, &cmd, 1, I2C_NO_STOP_BIT );

    // Read the configuration register B
    aux = i2c_read  ( myinstance, myHMC5883LAddr, &cmd, 1 );


    // Check if they are different, if so, update the value
    if ( ( cmd & CONF_REG_B_GAIN_MASK ) !=   myGain )
    {
        // Mask [ GN2 to GN0 ] Gain Configuration Bits
        cmd &=   ~CONF_REG_B_GAIN_MASK;

        // Update Gain Configuration Bits
        cmd |=   myGain;

        // Write the new value
        aux = i2c_write ( myinstance, myHMC5883LAddr, &cmd, 1, I2C_STOP_BIT );
    }




    if ( aux == I2C_SUCCESS )
        return   HMC5883L_SUCCESS;
    else
        return   HMC5883L_FAILURE;
}



/**
 * @brief       HMC5883L_SetMode ( NRF_TWI_Type* , HMC5883L_address_t , HMC5883L_mode_register_operation_mode_t )
 *
 * @details     It configures the operation mode.
 *
 * @param[in]    myinstance:        Peripheral's Instance.
 * @param[in]    myHMC5883LAddr:    I2C Device address.
 * @param[in]    myOperationMode:   New operation mode.
 *
 * @param[out]   NaN.
 *
 *
 * @return       Status of HMC5883L_SetMode.
 *
 *
 * @author      Manuel Caballero
 * @date        12/October/2017
 * @version     12/October/2017   The ORIGIN
 * @pre         NaN.
 * @warning     NaN.
 */
HMC5883L_status_t  HMC5883L_SetMode ( NRF_TWI_Type* myinstance, HMC5883L_address_t myHMC5883LAddr, HMC5883L_mode_register_operation_mode_t myOperationMode )
{
    uint8_t     cmd    =   HMC5883L_MODE_REGISTER;
    uint32_t    aux    =   0;



    // Write the command
    aux = i2c_write ( myinstance, myHMC5883LAddr, &cmd, 1, I2C_NO_STOP_BIT );

    // Read the Mode register bit
    aux = i2c_read  ( myinstance, myHMC5883LAddr, &cmd, 1 );


    // Check if they are different, if so, update the value
    if ( ( cmd & MODE_REG_MODE_MASK ) !=   myOperationMode )
    {
        // Mask [ MD1 to MD0 ] Mode Select Bits
        cmd &=   ~MODE_REG_MODE_MASK;

        // Update Mode Select Bits
        cmd |=   myOperationMode;

        // Write the new value
        aux = i2c_write ( myinstance, myHMC5883LAddr, &cmd, 1, I2C_STOP_BIT );
    }




    if ( aux == I2C_SUCCESS )
        return   HMC5883L_SUCCESS;
    else
        return   HMC5883L_FAILURE;
}
