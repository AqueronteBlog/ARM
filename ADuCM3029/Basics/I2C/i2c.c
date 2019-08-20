/**
 * @brief       i2c.c
 * @details     ADUCM3029 I2C function libraries.
 *              Function file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        25/July/2019
 * @version     25/July/2019    The ORIGIN
 * @pre         N/A
 * @warning     This file is ONLY for ADUCM3029 device.
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
 * @date        25/July/2019
 * @version     25/July/2019     The ORIGIN
 * @pre         I2C communication is by polling mode.
 * @warning     N/A.
 */
i2c_status_t i2c_init ( I2C_parameters_t myI2Cparameters )
{
	uint8_t i2cHigh	 =	 0U;
	uint8_t i2cLow	 =	 0U;

	/* Multiplexed function 1 for I2C peripheral ( SDA and SCL )	 */
	myI2Cparameters.sclPort->CFG	&=	~( 0b11 << ( myI2Cparameters.scl << 1U ) );
	myI2Cparameters.sclPort->CFG	|=	 ( 0b01 << ( myI2Cparameters.scl << 1U ) );

	myI2Cparameters.sdaPort->CFG	&=	~( 0b11 << ( myI2Cparameters.sda << 1U ) );
	myI2Cparameters.sdaPort->CFG	|=	 ( 0b01 << ( myI2Cparameters.sda << 1U ) );

	/* The drive strength must be enabled for SDA and SCL	 */
	myI2Cparameters.sclPort->DS		|=	 ( 1U << myI2Cparameters.scl );
	myI2Cparameters.sdaPort->DS		|=	 ( 1U << myI2Cparameters.sda );

	/* Check that there is NOT transaction in course to disable the master safely	 */
	while ( ( myI2Cparameters.i2cInstance->MSTAT & ( 1U << BITP_I2C_MSTAT_TCOMP ) ) == ( 1U << BITP_I2C_MSTAT_TCOMP ) );	//[TODO] INSERT TIMEOUT

	/* Disable I2C master	 */
	myI2Cparameters.i2cInstance->MCTL	&=	~( 1U << BITP_I2C_MCTL_MASEN );

	/* Calculate the I2C clock: I2C_DIV.HIGH and I2C_DIV.LOW	 */
	i2cHigh	 =	 (uint8_t)( (float)( ( myI2Cparameters.pclkFrequency / ( 2.0 * myI2Cparameters.freq ) ) + 0.5 ) - 2.0 );
	i2cLow	 =	 ( i2cHigh + 1U );

	/* Both MUST be greater than 0	 */
	if ( ( i2cHigh > 0U ) && ( i2cLow > 0U ) )
	{
		myI2Cparameters.i2cInstance->DIV	 =	 (uint16_t)( ( i2cHigh << BITP_I2C_DIV_HIGH ) | ( i2cLow << BITP_I2C_DIV_LOW ) );
	}
	else
	{
		return I2C_WRONG_FREQUENCY;
	}

	/* Peripheral configured successfully	 */
	return I2C_SUCCESS;
}

/**
 * @brief       i2c_write   ( I2C_parameters_t , uint8_t* , uint32_t , uint32_t  )
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
 * @date        25/July/2019
 * @version     25/July/2019         The ORIGIN
 * @pre         I2C communication is by polling mode.
 * @warning     This function only implements 7-bit address for the moment.
 */
i2c_status_t i2c_write ( I2C_parameters_t myI2Cparameters, uint8_t *i2c_buff, uint32_t i2c_data_length, uint32_t i2c_generate_stop )
{
   uint32_t	i				=	0UL;
   uint32_t i2c_timeout1 	= 	I2C_TIMEOUT;
   uint32_t i2c_timeout2 	= 	I2C_TIMEOUT;


   /* Enable interrupt	 */
   NVIC_SetPriority ( I2C_MST_EVT_IRQn, 0UL );
   NVIC_EnableIRQ   ( I2C_MST_EVT_IRQn );

   /* Enable Master	 */
   myI2Cparameters.i2cInstance->MCTL	|=	( ( 1U << BITP_I2C_MCTL_MASEN ) | ( 1U << BITP_I2C_MCTL_IENMTX ) );

   /* First bit to be transmitted	 */
   myI2Cparameters.i2cInstance->MTX		 =	 *i2c_buff++;

   /* Write. ADDRESS: 7-bit address.	 */
   myI2Cparameters.i2cInstance->ADDR1	 =	 (uint8_t)( ( myI2Cparameters.addr << 1UL ) & 0xFE );
   myI2Cparameters.i2cInstance->ADDR2	 =	 0x00;


   /* Transmission data, more than 1-bit	 */
   /*
   for ( i = 0UL; i < i2c_data_length-1; i++ )
   {
	   while ( ( myI2Cparameters.i2cInstance->MSTAT & ( 1U << BITP_I2C_MSTAT_MTXREQ ) ) != ( 1U << BITP_I2C_MSTAT_MTXREQ ) )
	   {
		   // [todo] insert counter

	   }
	   myI2Cparameters.i2cInstance->MTX		 =	 *i2c_buff++;
   }
*/

   /* Wait for a STOP detected	 */
   while ( ( myI2Cparameters.i2cInstance->MSTAT & ( 1U << BITP_I2C_MSTAT_TCOMP ) ) != ( 1U << BITP_I2C_MSTAT_TCOMP ) )

   /* Disable Master	 */
   myI2Cparameters.i2cInstance->MCTL	&=	( 1U << BITP_I2C_MCTL_MASEN );



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
 * @date        25/July/2019
 * @version     25/July/2019         The ORIGIN
 * @pre         I2C communication is by polling mode.
 * @warning     N/A.
 */
i2c_status_t i2c_read ( I2C_parameters_t myI2Cparameters, uint8_t *i2c_buff, uint32_t i2c_data_length )
{
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




void I2C0_Master_Int_Handler ( void )
{
	pADI_I2C0->MTX		 =	 0x23;
	pADI_I2C0->MSTAT	|=	 ( 1U << BITP_I2C_MSTAT_MTXREQ );
	__NOP();
}
