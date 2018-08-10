/**
 * @brief       main.c
 * @details     [todo]
 *
 * 				The rest of the time, the microcontroller is in sleep mode ( low power ).
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        5/January/2018
 * @version     5/January/2018   The ORIGIN
 * @pre         This firmware was tested on the NUCLEO-L152RE with System Workbench for STM32
 *              ( v1.15.0.201708311556 ).
 * @warning     Although HAL driver was generated, just the Low Power functions are used.
 */


#include "stm32l1xx.h"
#include "board.h"
#include "variables.h"
#include "functions.h"
#include "interrupts.h"
#include "DS1624.h"



int main ( void )
{
	I2C_parameters_t            myDS1624_I2C_parameters;
	DS1624_status_t             aux;
	DS1624_access_config_done_t myDS1624_TempConversionStatus;
	DS1624_vector_data_t        myDS1624_data;


	mySystemCoreClock	 =	 16000000U;			// SYSCLK = 16 MHz
	myUARTClock	 		 =	 16000000U;			// f_CK = 16 MHz

	Conf_GPIO 	 ();
	Conf_CLK  	 ();
	Conf_SYSTICK ( mySystemCoreClock/1000 );	// Milli seconds, SysTick will be disabled although
	Conf_UART 	 ( myUARTClock, 115200 );		// 115200 Baud Rate


	/* I2C definition	 */
//	myDS1624_I2C_parameters.TWIinstance =    NRF_TWI0;
//	myDS1624_I2C_parameters.SDA         =    TWI0_SDA;
//	myDS1624_I2C_parameters.SCL         =    TWI0_SCL;
//	myDS1624_I2C_parameters.ADDR        =    DS1624_ADDRESS_0;
//	myDS1624_I2C_parameters.Freq        =    TWI_FREQUENCY_FREQUENCY_K400;
//	myDS1624_I2C_parameters.SDAport     =    NRF_GPIO;
//	myDS1624_I2C_parameters.SCLport     =    NRF_GPIO;

	/* Configure I2C peripheral	 */
	aux  =   DS1624_Init ( myDS1624_I2C_parameters );


	/* Configure 1SHOT mode	 */
	aux  =   DS1624_SetConversionMode ( myDS1624_I2C_parameters, ACCESS_CONFIG_1SHOT_ONE_TEMPERATURE_CONVERSION );


	while ( 1 )
	{
		HAL_PWR_EnterSLEEPMode( PWR_LOWPOWERREGULATOR_ON, PWR_SLEEPENTRY_WFI );
	}
}
