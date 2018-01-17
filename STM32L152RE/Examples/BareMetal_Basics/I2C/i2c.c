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
 * @date        5/January/2018
 * @version     5/January/2018     The ORIGIN
 * @pre         I2C communication is by polling mode.
 * @warning     NaN.
 */
i2c_status_t    i2c_init   ( I2C_parameters_t myI2Cparameters )
{
	uint32_t myRightPinAllocation	 =	 0;
	uint32_t myRightAFRRegister		 =	 0;


	/* Reset and Stop I2Cx */
	// Enable the appropriate I2Cx Clock
	if ( myI2Cparameters.I2Cinstance == I2C1 )
		RCC->APB1ENR 					|= 	 RCC_APB1ENR_I2C1EN; 							// I2C1 Enabled
	else
		RCC->APB1ENR 					|= 	 RCC_APB1ENR_I2C2EN; 							// I2C2 Enabled

	myI2Cparameters.I2Cinstance->CR1	|=	 I2C_CR1_SWRST;									// I2C is under reset state
	myI2Cparameters.I2Cinstance->CR1	&=	~I2C_CR1_PE;									// I2C is disabled


	/* Configure the pins */
	// Enable the GPIO Clock
	RCC->AHBENR 						|= 	 RCC_AHBENR_GPIOBEN;

	// Set up the SDA pin
	myI2Cparameters.SDAport->MODER		|=	 ( 0b10 << ( myI2Cparameters.SDA << 1 ) );		// Alternate function mode
	myI2Cparameters.SDAport->OSPEEDR	|=	 ( 0b01 << ( myI2Cparameters.SDA << 1 ) );		// Medium speed
	myI2Cparameters.SDAport->PUPDR	    &=	~( 0b11 << ( myI2Cparameters.SDA << 1 ) );		// No pull-up/pull-down

	if ( myI2Cparameters.SDA > 7 )
	{
		myRightPinAllocation	 =	 8;
		myRightAFRRegister		 =	 1;
	}

	myI2Cparameters.SDAport->AFR[myRightAFRRegister]	 =	 ( 0b0100 << ( ( myI2Cparameters.SDA - myRightPinAllocation ) << 2 ) );	// I2Cx_SDA: AF4

	// Set up the SCL pin
	myI2Cparameters.SCLport->MODER		|=	 ( 0b10 << ( myI2Cparameters.SCL << 1 ) );		// Alternate function mode
	myI2Cparameters.SCLport->OSPEEDR	|=	 ( 0b01 << ( myI2Cparameters.SCL << 1 ) );		// Medium speed
	myI2Cparameters.SCLport->PUPDR	    &=	~( 0b11 << ( myI2Cparameters.SCL << 1 ) );		// No pull-up/pull-down

	if ( myI2Cparameters.SCL > 7 )
	{
		myRightPinAllocation	 =	 8;
		myRightAFRRegister		 =	 1;
	}

	myI2Cparameters.SCLport->AFR[myRightAFRRegister]	 =	 ( 0b0100 << ( ( myI2Cparameters.SCL - myRightPinAllocation ) << 2 ) );	// I2Cx_SCL: AF4



    /* Configure the frequency */ // [TODO] It needs to be developded!!!
//    myI2Cparameters.TWIinstance->FREQUENCY      =   ( myI2Cparameters.Freq << TWI_FREQUENCY_FREQUENCY_Pos );
//
//
    /* Disable ALL Interrupts and DMA request */
	myI2Cparameters.I2Cinstance->CR2	&=	~( I2C_CR2_DMAEN | I2C_CR2_ITBUFEN | I2C_CR2_ITEVTEN | I2C_CR2_ITERREN );



    /* Enable I2Cx */
	myI2Cparameters.I2Cinstance->CR1	&=	~( I2C_CR1_SWRST | I2C_CR1_SMBUS );				// I2C is NOT under reset state, I2C mode
	myI2Cparameters.I2Cinstance->CR1	|=	 I2C_CR1_PE;									// I2C is enabled



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
 * @date        17/January/2018
 * @version     17/January/2018         The ORIGIN
 * @pre         I2C communication is by polling mode.
 * @warning     NaN.
 */
i2c_status_t    i2c_write   ( I2C_parameters_t myI2Cparameters, uint8_t* i2c_buff, uint32_t i2c_data_length, uint32_t i2c_generate_stop )
{
    uint32_t    i                   =   0;
    uint32_t    i2c_timeout1        =   0;



// Start transmission
    // Generate the START condition
    myI2Cparameters.I2Cinstance->CR1	|=	 I2C_CR1_START;
    i2c_timeout1               			 =   I2C_TIMEOUT;
    while( ( ( myI2Cparameters.I2Cinstance->SR1 & I2C_SR1_SB_Msk ) != I2C_SR1_SB ) && ( --i2c_timeout1 ) );       	// [ EV5 ] Wait until the START is transmitted or timeout1

    if ( i2c_timeout1 < 1 )
    	return I2C_FAILURE;


    // Send the ADDRESS
    myI2Cparameters.I2Cinstance->DR	 =	 ( myI2Cparameters.ADDR << 1 ) | I2C_WRITE;
    i2c_timeout1               		 =   I2C_TIMEOUT;
    while( ( ( myI2Cparameters.I2Cinstance->SR1 & I2C_SR1_ADDR_Msk ) != I2C_SR1_ADDR ) && ( --i2c_timeout1 ) );		// Wait until the ADDRESS is transmitted or timeout1

    if ( i2c_timeout1 < 1 )
    	return I2C_FAILURE;


    // Clear ADDRESS: SR1 was read and now SR2 needs to be read
    i2c_timeout1               		 =   I2C_TIMEOUT;
    while( ( ( myI2Cparameters.I2Cinstance->SR2 & I2C_SR2_BUSY_Msk ) == I2C_SR2_BUSY ) && ( --i2c_timeout1 ) );		// [ EV6 ] Wait until the I2C is NOT busy or timeout1

    if ( i2c_timeout1 < 1 )
    	return I2C_FAILURE;


    // Start transmitting data
    for ( i = 0; i < i2c_data_length; i++ )
    {
    	myI2Cparameters.I2Cinstance->DR   =   *i2c_buff;

        i2c_timeout1               =   I2C_TIMEOUT;
        while( ( ( myI2Cparameters.I2Cinstance->SR1 & I2C_SR1_TXE_Msk ) != I2C_SR1_TXE ) && ( --i2c_timeout1 ) );	// [ EV8 ] Wait until the data is transmitted or timeout1

        if ( i2c_timeout1 < 1 )
        	return I2C_FAILURE;
        else
        	i2c_buff++;
    }

    i2c_timeout1               =   I2C_TIMEOUT;
	while( ( ( myI2Cparameters.I2Cinstance->SR1 & I2C_SR1_BTF_Msk ) != I2C_SR1_BTF ) && ( --i2c_timeout1 ) );		// [ EV8_2 ] Wait until the LAST DATA is transmitted or timeout1

 	if ( i2c_timeout1 < 1 )
 		return I2C_FAILURE;


    // Generate a STOP bit if it is required
    if ( i2c_generate_stop == I2C_STOP_BIT )
    {
    	myI2Cparameters.I2Cinstance->CR1	|=	 I2C_CR1_STOP;
        i2c_timeout1               =   I2C_TIMEOUT;
        while( ( ( myI2Cparameters.I2Cinstance->SR2 & I2C_SR2_MSL_Msk ) == I2C_SR2_MSL ) && ( --i2c_timeout1 ) );	// Wait until the STOP is generated or timeout1
    }




    // Check if everything went fine
    if ( i2c_timeout1 < 1 )
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
 * @date        17/January/2018
 * @version     17/January/2018         The ORIGIN
 * @pre         I2C communication is by polling mode.
 * @warning     NaN.
 */
i2c_status_t     i2c_read   ( I2C_parameters_t myI2Cparameters, uint8_t* i2c_buff, uint32_t i2c_data_length )
{
    uint32_t    i                   =   0;
    uint32_t    i2c_timeout1        =   0;


    // Generate the START condition
    myI2Cparameters.I2Cinstance->CR1	|=	 I2C_CR1_START;
    i2c_timeout1               			 =   I2C_TIMEOUT;
    while( ( ( myI2Cparameters.I2Cinstance->SR1 & I2C_SR1_SB_Msk ) != I2C_SR1_SB ) && ( --i2c_timeout1 ) );       	// [ EV5 ] Wait until the START is transmitted or timeout1

    if ( i2c_timeout1 < 1 )
    	return I2C_FAILURE;


    // Send the ADDRESS
    myI2Cparameters.I2Cinstance->DR	 =	 ( myI2Cparameters.ADDR << 1 ) | I2C_READ;
    i2c_timeout1               		 =   I2C_TIMEOUT;
    while( ( ( myI2Cparameters.I2Cinstance->SR1 & I2C_SR1_ADDR_Msk ) != I2C_SR1_ADDR ) && ( --i2c_timeout1 ) );		// Wait until the ADDRESS is transmitted or timeout1

    if ( i2c_timeout1 < 1 )
    	return I2C_FAILURE;


 	// Clear ADDRESS: SR1 was read and now SR2 needs to be read
  	i2c_timeout1               		 =   I2C_TIMEOUT;
   	while( ( ( myI2Cparameters.I2Cinstance->SR2 & I2C_SR2_BUSY_Msk ) == I2C_SR2_BUSY ) && ( --i2c_timeout1 ) );		// [ EV6 ] Wait until the I2C is NOT busy or timeout1

	if ( i2c_timeout1 < 1 )
		return I2C_FAILURE;


    // Read data from i2c bus
    for ( i = 0; i < i2c_data_length; i++ )
    {
    // Wait until the data arrives or timeout
        i2c_timeout1               =   I2C_TIMEOUT;
        while( ( ( myI2Cparameters.I2Cinstance->SR1 & I2C_SR1_RXNE_Msk ) != I2C_SR1_RXNE ) && ( --i2c_timeout1 ) );	// [ EV7 ] Wait until the data is read or timeout1

        if ( i2c_timeout1 < 1 )
        	return I2C_FAILURE;

    // Read data and prepare the next one
        *i2c_buff                  =   myI2Cparameters.I2Cinstance->DR;
        i2c_buff++;
    }


    // Generate a STOP bit
  	myI2Cparameters.I2Cinstance->CR1	|=	 I2C_CR1_STOP;
    i2c_timeout1               =   I2C_TIMEOUT;
    while( ( ( myI2Cparameters.I2Cinstance->SR2 & I2C_SR2_MSL_Msk ) == I2C_SR2_MSL ) && ( --i2c_timeout1 ) );		// Wait until the STOP is generated or timeout1



    // Check if everything went fine
    if ( i2c_timeout1 < 1 )
        return I2C_FAILURE;
    else
        return I2C_SUCCESS;
}
