/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision: 00 $
   Last changed by:    $Author: $
   Last changed date:  $Date:  $
   ID:                 $Id:  $

**********************************************************************/

#include "nrf.h"
#include "ble.h"
#include "variables.h"
#include "functions.h"


int main( void )
{
    conf_GPIO ();


    while( 1 )
    {
        NRF_GPIO->OUTSET |= ( LED1 | LED2 | LED3 | LED4 );
        // [TODO] delay
        NRF_GPIO->OUTCLR |= ( LED1 | LED2 | LED3 | LED4 );
        // [TODO] delay
    }
}
