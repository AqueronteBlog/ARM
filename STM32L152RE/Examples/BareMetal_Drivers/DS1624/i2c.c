/**
 * @brief       i2c.c
 * @details     STM32L152RE I2C function libraries.
 *              Function file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/January/2018
 * @version     5/January/2018    The ORIGIN
 * @pre         NaN
 * @warning     This file is ONLY for STM32L152RE device.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "i2c.h"


/**
 * @brief       i2c_init   ( I2C_parameters_t )
 * @details     It configures the I2C peripheral.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 *
 * @param[out]   Status of i2c_init.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        15/October/2017
 * @version     15/October/2017     The ORIGIN
 * @pre         I2C communication is by polling mode.
 * @warning     NaN.
 */
i2c_status_t    i2c_init   ( I2C_parameters_t myI2Cparameters )
{
    /* TWI0 pins. GPIO according to Table 258: GPIO configuration ( Reference Manual p.145 ) */
    myI2Cparameters.SCLport->PIN_CNF[myI2Cparameters.SCL]     =     GPIO_PIN_CNF_DIR_Input          <<  GPIO_PIN_CNF_DIR_Pos    |
                                                                    GPIO_PIN_CNF_INPUT_Connect      <<  GPIO_PIN_CNF_INPUT_Pos  |
                                                                    GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos   |
                                                                    GPIO_PIN_CNF_DRIVE_S0D1         <<  GPIO_PIN_CNF_DRIVE_Pos  |
                                                                    GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos;

    myI2Cparameters.SDAport->PIN_CNF[myI2Cparameters.SDA]     =     GPIO_PIN_CNF_DIR_Input          <<  GPIO_PIN_CNF_DIR_Pos    |
                                                                    GPIO_PIN_CNF_INPUT_Connect      <<  GPIO_PIN_CNF_INPUT_Pos  |
                                                                    GPIO_PIN_CNF_PULL_Disabled      <<  GPIO_PIN_CNF_PULL_Pos   |
                                                                    GPIO_PIN_CNF_DRIVE_S0D1         <<  GPIO_PIN_CNF_DRIVE_Pos  |
                                                                    GPIO_PIN_CNF_SENSE_Disabled     <<  GPIO_PIN_CNF_SENSE_Pos;




    /* Stop TWIx */
    myI2Cparameters.TWIinstance->TASKS_STOP     =   1;
    myI2Cparameters.TWIinstance->ENABLE         =   ( TWI_ENABLE_ENABLE_Disabled  <<  TWI_ENABLE_ENABLE_Pos );


    /* Configure the pins */
    myI2Cparameters.TWIinstance->PSELSCL        =   myI2Cparameters.SCL;
    myI2Cparameters.TWIinstance->PSELSDA        =   myI2Cparameters.SDA;


    /* Configure the frequency */
    myI2Cparameters.TWIinstance->FREQUENCY      =   ( myI2Cparameters.Freq << TWI_FREQUENCY_FREQUENCY_Pos );


    /* Disable Interrupts, clear events and all the errors */
    myI2Cparameters.TWIinstance->INTENCLR       =    ( TWI_INTENCLR_STOPPED_Clear  << TWI_INTENCLR_STOPPED_Pos  ) |
                                                     ( TWI_INTENCLR_RXDREADY_Clear << TWI_INTENCLR_RXDREADY_Pos ) |
                                                     ( TWI_INTENCLR_TXDSENT_Clear  << TWI_INTENCLR_TXDSENT_Pos  ) |
                                                     ( TWI_INTENCLR_ERROR_Clear    << TWI_INTENCLR_ERROR_Pos    ) |
                                                     ( TWI_INTENCLR_BB_Clear       << TWI_INTENCLR_BB_Pos       );

    myI2Cparameters.TWIinstance->EVENTS_STOPPED    =   0;
    myI2Cparameters.TWIinstance->EVENTS_RXDREADY   =   0;
    myI2Cparameters.TWIinstance->EVENTS_TXDSENT    =   0;
    myI2Cparameters.TWIinstance->EVENTS_ERROR      =   0;
    myI2Cparameters.TWIinstance->EVENTS_BB         =   0;

    myI2Cparameters.TWIinstance->ERRORSRC       =    ( TWI_ERRORSRC_OVERRUN_Clear << TWI_ERRORSRC_OVERRUN_Pos ) |
                                                     ( TWI_ERRORSRC_ANACK_Clear   << TWI_ERRORSRC_ANACK_Pos   ) |
                                                     ( TWI_ERRORSRC_DNACK_Clear   << TWI_ERRORSRC_DNACK_Pos   );

    /* Configure shorts */
    /*
    NRF_TWI0->SHORTS         =   ( TWI_SHORTS_BB_SUSPEND_Enabled << TWI_SHORTS_BB_SUSPEND_Pos ) |
                                 ( TWI_SHORTS_BB_STOP_Enabled    << TWI_SHORTS_BB_STOP_Pos    );
    */

    /* Enable TWI0 */
    myI2Cparameters.TWIinstance->ENABLE         =   ( TWI_ENABLE_ENABLE_Enabled  <<  TWI_ENABLE_ENABLE_Pos );




    // Peripheral configures successfully
    return I2C_SUCCESS;
}



/**
 * @brief       i2c_write   ( I2C_parameters_t , uint8_t* , uint32_t , uint32_t  )
 * @details     Send data through I2C bus.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 * @param[in]    *i2c_buff:             Data to be transmitted.
 * @param[in]    i2c_data_length:       Amount of data to be transmitted.
 * @param[in]    i2c_generate_stop:     Generate STOP bit or not.
 *
 * @param[out]   Status of i2c_write.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        6/July/2017
 * @version     15/October/2017     Library was updated to be more abstract.
 *              6/July/2017         The ORIGIN
 * @pre         I2C communication is by polling mode.
 * @warning     NaN.
 */
i2c_status_t    i2c_write   ( I2C_parameters_t myI2Cparameters, uint8_t* i2c_buff, uint32_t i2c_data_length, uint32_t i2c_generate_stop )
{
    uint32_t    i                   =   0;
    uint32_t    i2c_timeout1        =   0;
    uint32_t    i2c_timeout2        =   0;
    uint32_t    i2c_default_addr    =   0;


    // Save the default i2c address and set the one for this device
    i2c_default_addr                       =   myI2Cparameters.TWIinstance->ADDRESS;
    myI2Cparameters.TWIinstance->ADDRESS   =   myI2Cparameters.ADDR;


// Start transmission
    // Reset flag and start event
    myI2Cparameters.TWIinstance->EVENTS_TXDSENT   =   0;
    myI2Cparameters.TWIinstance->TASKS_STARTTX    =   1;

    // Start transmitting data
    for ( i = 0; i < i2c_data_length; i++ )
    {
        myI2Cparameters.TWIinstance->TXD   =   *i2c_buff;

        i2c_timeout1               =   I2C_TIMEOUT;
        while( ( myI2Cparameters.TWIinstance->EVENTS_TXDSENT == 0 ) && ( --i2c_timeout1 ) );       // Wait until the data is transmitted or timeout1
        myI2Cparameters.TWIinstance->EVENTS_TXDSENT   =   0;                                       // reset flag

        i2c_buff++;
    }

    // Generate a STOP bit if it is required
    if ( i2c_generate_stop == I2C_STOP_BIT )
    {
        myI2Cparameters.TWIinstance->EVENTS_STOPPED   =   0;
        myI2Cparameters.TWIinstance->TASKS_STOP       =   1;
        i2c_timeout2               =   I2C_TIMEOUT;
        while( ( myI2Cparameters.TWIinstance->EVENTS_STOPPED == 0 ) && ( --i2c_timeout2 ) );
        myI2Cparameters.TWIinstance->EVENTS_STOPPED   =   0;
    }


    // Restore the default I2C address
    myI2Cparameters.TWIinstance->ADDRESS  =   i2c_default_addr;


    // Check if everything went fine
    if ( ( i2c_timeout1 < 1 ) || ( i2c_timeout2 < 1 ) )
        return I2C_FAILURE;
    else
        return I2C_SUCCESS;
}



/**
 * @brief       i2c_read   ( I2C_parameters_t , uint8_t* , uint32_t )
 * @details     Read data through I2C bus.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    *i2c_buff:         Data to be transmitted.
 * @param[in]    i2c_data_length:   Amount of data to be transmitted.
 *
 * @param[out]   Status of i2c_read.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        7/July/2017
 * @version     15/October/2017     Library was updated to be more abstract.
 *              7/July/2017         The ORIGIN
 * @pre         I2C communication is by polling mode.
 * @warning     NaN.
 */
i2c_status_t     i2c_read   ( I2C_parameters_t myI2Cparameters, uint8_t* i2c_buff, uint32_t i2c_data_length )
{
    uint32_t    i                   =   0;
    uint32_t    i2c_timeout1        =   0;
    uint32_t    i2c_timeout2        =   0;
    uint32_t    i2c_default_addr    =   0;


    // Save the default i2c address and set the one for this device
    i2c_default_addr                      =   myI2Cparameters.TWIinstance->ADDRESS;
    myI2Cparameters.TWIinstance->ADDRESS  =   myI2Cparameters.ADDR;


// Start reading
    // Clear the shortcuts
    myI2Cparameters.TWIinstance->SHORTS           =   ( TWI_SHORTS_BB_STOP_Disabled   << TWI_SHORTS_BB_STOP_Pos    );
    myI2Cparameters.TWIinstance->SHORTS           =   ( TWI_SHORTS_BB_SUSPEND_Enabled << TWI_SHORTS_BB_SUSPEND_Pos );


    // Reset flag and start reading
    myI2Cparameters.TWIinstance->EVENTS_RXDREADY  =   0;
    myI2Cparameters.TWIinstance->TASKS_STARTRX    =   1;


    // Read data from i2c bus
    for ( i = 0; i < i2c_data_length; i++ )
    {
    // Enable the right shortcut ( NRF51 Reference Manual 28.5 Master read sequence. Figure 65 )
        if ( i == ( i2c_data_length - 1 ) )
            myI2Cparameters.TWIinstance->SHORTS    =   ( TWI_SHORTS_BB_STOP_Enabled << TWI_SHORTS_BB_STOP_Pos );
        else
            myI2Cparameters.TWIinstance->SHORTS    =   ( TWI_SHORTS_BB_SUSPEND_Enabled << TWI_SHORTS_BB_SUSPEND_Pos );

    // It releases the bus
        myI2Cparameters.TWIinstance->TASKS_RESUME     =   1;                // NOTE: This is important to be here otherwise the STOP event
                                                                            //       will be clocked one byte later.

    // Wait until the data arrives or timeout
        i2c_timeout1               =   I2C_TIMEOUT;
        while( ( myI2Cparameters.TWIinstance->EVENTS_RXDREADY == 0 ) && ( --i2c_timeout1 ) );    // Wait until the data is read or timeout1
        myI2Cparameters.TWIinstance->EVENTS_RXDREADY  =   0;                                     // reset flag

    // Read data and prepare the next one
        *i2c_buff                  =   myI2Cparameters.TWIinstance->RXD;
        i2c_buff++;
    }


    // Wait until the STOP event is produced or timeout2
    i2c_timeout2                 =   I2C_TIMEOUT;
    while( ( myI2Cparameters.TWIinstance->EVENTS_STOPPED == 0 ) && ( --i2c_timeout2 ) );
    myI2Cparameters.TWIinstance->EVENTS_STOPPED   =   0;


    // Reset shortcuts
    myI2Cparameters.TWIinstance->SHORTS    =   ( TWI_SHORTS_BB_SUSPEND_Disabled << TWI_SHORTS_BB_SUSPEND_Pos );
    myI2Cparameters.TWIinstance->SHORTS    =   ( TWI_SHORTS_BB_STOP_Disabled    << TWI_SHORTS_BB_STOP_Pos );


    // Restore the default I2C address
    myI2Cparameters.TWIinstance->ADDRESS  =   i2c_default_addr;


    // Check if everything went fine
    if ( ( i2c_timeout1 < 1 ) || ( i2c_timeout2 < 1 ) )
        return I2C_FAILURE;
    else
        return I2C_SUCCESS;
}
