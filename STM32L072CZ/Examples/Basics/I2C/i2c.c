/**
 * @brief       i2c.c
 * @details     STM32L072CZ I2C function libraries.
 *              Function file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/January/2020
 * @version     16/January/2020    The ORIGIN
 * @pre         N/A
 * @warning     This file is ONLY for STM32L072CZ device.
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
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/January/2020
 * @version     20/January/2020     I2Cclock source was added.
 * 				19/January/2020     Analog filter enabled, all flags are reset.
 * 				16/January/2020     The ORIGIN
 * @pre         I2C communication is by polling mode.
 * @pre         Only 7-bit addressing mode implemented.
 * @warning     N/A.
 */
i2c_status_t i2c_init ( I2C_parameters_t myI2Cparameters )
{

	/* Turn on the I2C peripheral clock	 */
	switch ( myI2Cparameters.i2cClockSource )
	{
	default:
	case I2C_CLOCK_SOURCE_APB:
		if ( myI2Cparameters.i2cInstance == I2C1 )
		{
			RCC->CCIPR		&=	~( RCC_CCIPR_I2C1SEL_Msk );
			RCC->APB1ENR	|=	 ( RCC_APB1ENR_I2C1EN );
		}
		else if ( myI2Cparameters.i2cInstance == I2C2 )
		{
			/* I2C2 has a fixed clock source to PCK1 (APB)	 */
			RCC->APB1ENR	|=	 ( RCC_APB1ENR_I2C2EN );
		}
		else if ( myI2Cparameters.i2cInstance == I2C3 )
		{
			RCC->CCIPR		&=	~( RCC_CCIPR_I2C3SEL_Msk );
			RCC->APB1ENR	|=	 ( RCC_APB1ENR_I2C3EN );
		}
		else
		{
			return I2C_WRONG_I2C_DECLARATION;
		}
		break;


	case I2C_CLOCK_SOURCE_HSI16:
		if ( myI2Cparameters.i2cInstance == I2C1 )
		{
			RCC->CCIPR		&=	~( RCC_CCIPR_I2C1SEL_Msk );
			RCC->CCIPR		|=	 ( RCC_CCIPR_I2C1SEL_1 );
			//RCC->APB1ENR	|=	 ( RCC_APB1ENR_I2C1EN );
		}
		else if ( myI2Cparameters.i2cInstance == I2C2 )
		{
			return I2C_WRONG_I2C_CLOCK_SOURCE;
		}
		else if ( myI2Cparameters.i2cInstance == I2C3 )
		{
			RCC->CCIPR		&=	~( RCC_CCIPR_I2C3SEL_Msk );
			RCC->CCIPR		|=	 ( RCC_CCIPR_I2C1SEL_1 );
			//RCC->APB1ENR	|=	 ( RCC_APB1ENR_I2C3EN );
		}
		else
		{
			return I2C_WRONG_I2C_DECLARATION;
		}
		break;

	case I2C_CLOCK_SOURCE_SYSCLK:
		if ( myI2Cparameters.i2cInstance == I2C1 )
		{
			RCC->CCIPR		&=	~( RCC_CCIPR_I2C1SEL_Msk );
			RCC->CCIPR		|=	 ( RCC_CCIPR_I2C1SEL_0 );
			//RCC->APB1ENR	|=	 ( RCC_APB1ENR_I2C1EN );
		}
		else if ( myI2Cparameters.i2cInstance == I2C2 )
		{
			return I2C_WRONG_I2C_CLOCK_SOURCE;
		}
		else if ( myI2Cparameters.i2cInstance == I2C3 )
		{
			RCC->CCIPR		&=	~( RCC_CCIPR_I2C3SEL_Msk );
			RCC->CCIPR		|=	 ( RCC_CCIPR_I2C1SEL_0 );
			//RCC->APB1ENR	|=	 ( RCC_APB1ENR_I2C3EN );
		}
		else
		{
			return I2C_WRONG_I2C_DECLARATION;
		}
		break;
	}



	/* I2C
	 *  - I2C disabled
	 *  - Transmit (TXIS) interrupt disabled
	 *  - Receive (RXNE) interrupt disabled
	 *  - Not acknowledge (NACKF) received interrupts disabled
	 *  - Stop detection (STOPF) interrupt disabled
	 *  - Transfer Complete interrupt disabled
	 *  - Error detection interrupts disabled
	 *  - Digital filter disabled
	 *  - Analog noise filter enabled
	 *  - DMA mode disabled for transmission
	 *  - DMA mode disabled for reception
	 *  - Slave byte control disabled
	 */
	myI2Cparameters.i2cInstance->CR1	&=	~( I2C_CR1_PE | I2C_CR1_TXIE | I2C_CR1_RXIE | I2C_CR1_NACKIE | I2C_CR1_STOPIE | I2C_CR1_TCIE | I2C_CR1_ERRIE | I2C_CR1_DNF | I2C_CR1_TXDMAEN | I2C_CR1_RXDMAEN | I2C_CR1_SBC );
	myI2Cparameters.i2cInstance->CR1	&=	~( I2C_CR1_ANFOFF );

	/* I2C
	 *  - The master operates in 7-bit addressing mode
	 */
	myI2Cparameters.i2cInstance->CR2	&=	~( I2C_CR2_ADD10 );


	/* Clear all the flags	 */
	myI2Cparameters.i2cInstance->ICR	|=	 ( I2C_ICR_ADDRCF | I2C_ICR_NACKCF | I2C_ICR_STOPCF | I2C_ICR_BERRCF | I2C_ICR_ARLOCF | I2C_ICR_OVRCF | I2C_ICR_PECCF | I2C_ICR_TIMOUTCF | I2C_ICR_ALERTCF );



	/* Peripheral configured successfully	 */
	return I2C_SUCCESS;
}

/**
 * @brief       i2c_write   ( I2C_parameters_t , uint8_t* , uint32_t , i2c_stop_bit_t  )
 * @details     It sends data through I2C bus.
 *
 * @param[in]    myI2Cparameters:       I2C parameters.
 * @param[in]    *i2c_buff:             Data to be transmitted.
 * @param[in]    i2c_data_length:       Amount of data to be transmitted.
 * @param[in]    i2c_generate_stop:     Generate STOP bit or not.
 *
 * @param[out]   Status of i2c_write.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/January/2020
 * @version     16/January/2020         The ORIGIN
 * @pre         I2C communication is by polling mode.
 * @warning     This function only implements 7-bit address for the moment.
 */
i2c_status_t i2c_write ( I2C_parameters_t myI2Cparameters, uint8_t *i2c_buff, uint32_t i2c_data_length, i2c_stop_bit_t i2c_generate_stop )
{
   uint32_t	i				=	0UL;
   uint32_t i2c_timeout1 	= 	I2C_TIMEOUT;
   uint32_t i2c_timeout2 	= 	I2C_TIMEOUT;
   uint32_t i2c_timeout3 	= 	I2C_TIMEOUT;





   /* Check if everything went fine   */
   if ( ( i2c_timeout1 < 1UL ) || ( i2c_timeout2 < 1UL ) || ( i2c_timeout3 < 1UL ) )
   {
	   return I2C_FAILURE;
   }
   else
   {
 	  return I2C_SUCCESS;
   }
}



/**
 * @brief       i2c_read   ( I2C_parameters_t , uint8_t* , uint32_t )
 * @details     It reads data through I2C bus.
 *
 * @param[in]    myI2Cparameters:   I2C parameters.
 * @param[in]    *i2c_buff:         Data to be transmitted.
 * @param[in]    i2c_data_length:   Amount of data to be transmitted.
 *
 * @param[out]   Status of i2c_read.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/January/2020
 * @version     16/January/2020         The ORIGIN
 * @pre         I2C communication is by polling mode.
 * @warning     This function only implements 7-bit address for the moment.
 */
i2c_status_t i2c_read ( I2C_parameters_t myI2Cparameters, uint8_t *i2c_buff, uint32_t i2c_data_length )
{
	uint32_t i			  =	0UL;
	uint32_t i2c_timeout1 = I2C_TIMEOUT;
	uint32_t i2c_timeout2 = I2C_TIMEOUT;





	/* Check if everything went fine   */
	if ( ( i2c_timeout1 < 1U ) || ( i2c_timeout2 < 1U ) )
	{
		return I2C_FAILURE;
	}
	else
	{
		return I2C_SUCCESS;
	}
}
