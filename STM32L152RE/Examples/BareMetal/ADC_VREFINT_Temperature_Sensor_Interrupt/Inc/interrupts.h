/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        28/September/2018
 * @version     28/September/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "stm32l1xx.h"
#include "variables.h"
#include "board.h"

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#ifdef __cplusplus
extern "C" {
#endif


/**@brief Subroutine prototypes.
 */
void RTC_WKUP_IRQHandler ( void );
void USART2_IRQHandler 	 ( void );
void ADC1_IRQHandler 	 ( void );


/**@brief Constants.
 */
/* ADC channels	 */
typedef enum{
  INTERNAL_TEMPERATURE_TRIGGERED	=   0UL,      /*!< A new internal temperature measurement was triggered	 	 */
  VDD_TRIGGERED  					=   1UL       /*!< A new VDD measurement was triggered      				 */
} adc_channels_t;


/**@brief Variables.
 */
extern volatile system_state_machine_t 	myState;
extern volatile uint8_t  				*myPtr;
extern volatile uint32_t 				myRawADC_value;

adc_channels_t							myNextADC_Measurement;

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */
