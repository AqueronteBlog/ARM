//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************

#include "msp.h"
#include "variables.h"
#include "functions.h"
#include "interrupts.h"


void main(void)
{
	uint32_t i;


	conf_WDT	();
	conf_IO 	();
	conf_TA		();

	
	__enable_irq();

	while (1){
		NVIC_ClearPendingIRQ 	( PORT1_IRQn );
		NVIC_EnableIRQ			( PORT1_IRQn );
		__sleep					();
		NVIC_DisableIRQ			( PORT1_IRQn );
		for ( i = 0; i < 120000; i++ );
	}
}
