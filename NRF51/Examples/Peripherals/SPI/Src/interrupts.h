/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        27/June/2017
 * @version     27/June/2017    The ORIGIN
 * @pre         NaN
 * @warning     NaN
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "variables.h"


/* INTERRUPT PRTOTYPES */
void SPI0_TWI0_IRQHandler   ( void );
void SPI1_TWI1_IRQHandler   ( void );


/* VARIABLES */
extern uint32_t  changeDataSPIToBeTX;
extern uint8_t   mySPI_RX;
extern uint8_t   mySPI_TX;
extern uint32_t  mySPIS_RX;
extern uint32_t  mySPIS_TX;
