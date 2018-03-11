/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/March/2018
 * @version     10/March/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "variables.h"

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#ifdef __cplusplus
extern "C" {
#endif


/* INTERRUPT PRTOTYPES */
void SPI0_TWI0_IRQHandler   ( void );
void SPI1_TWI1_IRQHandler   ( void );


/* VARIABLES */
extern uint32_t  changeDataSPIToBeTX;
extern uint8_t   mySPI_RX;
extern uint8_t   mySPI_TX;
extern uint32_t  mySPIS_RX;
extern uint32_t  mySPIS_TX;


/* VARIABLES */


#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */