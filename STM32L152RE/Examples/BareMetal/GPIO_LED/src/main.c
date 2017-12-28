/**
 * @brief       main.c
 * @details     [todo].
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        26/December/2017
 * @version     26/December/2017   The ORIGIN
 * @pre         This firmware was tested on the NUCLEO-L152RE with System Workbench for STM32
 *              ( v1.15.0.201708311556 ).
 * @warning     Although HAL driver was generated, it was not used for this example.
 */


#include "stm32l1xx.h"
#include "board.h"
#include "variables.h"
#include "functions.h"
#include "interrupts.h"


extern void conf_GPIO( void );
extern void conf_CLK ( void );


int main(void)
{
	HAL_Init  ();

	conf_GPIO ();
	conf_CLK  ();


	while ( 1 )
	{
		if ( ( GPIOA->ODR & GPIO_ODR_ODR_5 ) == GPIO_ODR_ODR_5 )
			GPIOA->BRR	=	GPIO_BRR_BR_5;
		else
			GPIOA->BSRR	=	GPIO_BSRR_BS_5;

		HAL_Delay ( 500 );
	}
}
