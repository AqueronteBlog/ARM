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
 * @version     16/January/2020     The ORIGIN
 * @pre         I2C communication is by polling mode.
 * @warning     N/A.
 */
i2c_status_t i2c_init ( I2C_parameters_t myI2Cparameters )
{

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
