/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        18/December/2019
 * @version     18/December/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */


#include "functions.h"

/**
 * @brief       void Conf_CLK ( void )
 * @details     It configures the CLKs.
 * 					- LPTIM: LSI
 *
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        18/December/2019
 * @version		18/December/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void Conf_CLK ( void )
{
	/* LSI enabled	 */
	RCC->CSR	|=	 ( RCC_CSR_LSION );

	/* Wait until LSI is ready	 */
	while ( ( RCC->CSR & RCC_CSR_LSIRDY_Msk ) != RCC_CSR_LSIRDY );

	/* LPTIM: LSI	 */
	RCC->CCIPR	&=	 ~( RCC_CCIPR_LPTIM1SEL );
	RCC->CCIPR	|=	  ( RCC_CCIPR_LPTIM1SEL_0 );
}



/**
 * @brief       void Conf_Range ( void )
 * @details     It configures the voltage scaling configuration: 1.2V ( Range 3 ).
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        18/December/2019
 * @version		18/December/2019   The ORIGIN
 * @pre         N/A
 * @warning     Make sure that the f_CORE <= 4.2MHz.
 */
void Conf_Range ( void )
{
	/* Wait until Regulator is ready in the selected voltage range	 */
	while ( ( PWR->CSR & PWR_CSR_VOSF_Msk ) == PWR_CSR_VOSF );

	/* Voltage scaling configuration: 1.2V ( range 3 )	 */
	PWR->CR	&=	 ~( PWR_CR_VOS );
	PWR->CR	|=	  ( PWR_CR_VOS_0 | PWR_CR_VOS_1 );

	/* Wait until Regulator is ready in the selected voltage range	 */
	while ( ( PWR->CSR & PWR_CSR_VOSF_Msk ) == PWR_CSR_VOSF );
}



/**
 * @brief       void Conf_GPIO ( void )
 * @details     It configures GPIO to work with the LEDs.
 *
 *					LEDs:
 * 						- LD1:	PB_5
 * 						- LD2:	PA_5
 * 						- LD3:	PB_6
 * 						- LD4:	PB_7
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        18/December/2019
 * @version		18/December/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void Conf_GPIO ( void )
{
	/* GPIOA and GPIOB Periph clocks enable	 */
	RCC->IOPENR	|=	 ( RCC_IOPENR_GPIOAEN | RCC_IOPENR_GPIOBEN );

	/* GPIOB Mode: General purpose output mode	 */
	GPIOB->MODER	&=	~( GPIO_MODER_MODE5 | GPIO_MODER_MODE6 | GPIO_MODER_MODE7 );
	GPIOB->MODER	|=	 ( GPIO_MODER_MODE5_0 | GPIO_MODER_MODE6_0 | GPIO_MODER_MODE7_0 );

	/* GPIOB Output type: Output push-pull	 */
	GPIOB->OTYPER	&=	~( GPIO_OTYPER_OT_5 | GPIO_OTYPER_OT_6 | GPIO_OTYPER_OT_7 );

	/* GPIOB Output speed: Low speed	 */
	GPIOB->OSPEEDR	&=	~( GPIO_OSPEEDER_OSPEED5 | GPIO_OSPEEDER_OSPEED6 | GPIO_OSPEEDER_OSPEED7 );

	/* GPIOB Output: No pull-up, pull-down	 */
	GPIOB->PUPDR	&=	~( GPIO_PUPDR_PUPD5 | GPIO_PUPDR_PUPD6 | GPIO_PUPDR_PUPD7 );

	/* GPIOB Output: PA_5, PA_6 and PA_7 reset	 */
	GPIOB->BSRR	|=	 ( GPIO_BSRR_BR_5 | GPIO_BSRR_BR_6 | GPIO_BSRR_BR_7 );

	/* GPIOA Mode: General purpose output mode	 */
	GPIOA->MODER	&=	~( GPIO_MODER_MODE5 );
	GPIOA->MODER	|=	 GPIO_MODER_MODE5_0;

	/* GPIOA Output type: Output push-pull	 */
	GPIOA->OTYPER	&=	~GPIO_OTYPER_OT_5;

	/* GPIOA Output speed: Low speed	 */
	GPIOA->OSPEEDR	&=	~GPIO_OSPEEDER_OSPEED5;

	/* GPIOA Output: No pull-up, pull-down	 */
	GPIOA->PUPDR	&=	~GPIO_PUPDR_PUPD5;

	/* GPIOA Output: PB_6 reset	 */
	GPIOA->BSRR	|=	 GPIO_BSRR_BR_5;
}



/**
 * @brief       void Conf_LPTIM ( void )
 * @details     It configures low-power timer LPTIM.
 *
 *				-LPTIM:
 * 					-- f_lptim = LSI = 32.768 kHz
 * 					-- ARRM Interrupt ENABLED.
 * 					-- Overflow: Every 1 second ( ARR / LSI ) = ( 32768 / 32768 ) = 1s
 *
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        18/December/2019
 * @version		18/December/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void Conf_LPTIM ( void )
{
	/* Low-power Timer LPTIM clock enable	 */
	RCC->APB1ENR	|=	 RCC_APB1ENR_LPTIM1EN;

	/* Timer LPTIM:
	 * 	- Disable timer LPTIM
	 */
	LPTIM1->CR	&=	~( LPTIM_CR_ENABLE );

	/* LPTIM:
	 *  - The counter is incremented following each internal clock pulse
	 *  - Trigger: Software trigger (counting start is initiated by software)
	 *  - Clock prescaler: f_LPTIM/1
	 *  - CKSEL: LPTIM is clocked by internal clock source (APB clock or any of the embedded oscillators)
	 */
	LPTIM1->CFGR	&=	~( LPTIM_CFGR_COUNTMODE | LPTIM_CFGR_TRIGSEL | LPTIM_CFGR_PRESC | LPTIM_CFGR_CKSEL );

	/* Autoreload register update OK Clear Flag	 */
	LPTIM1->ICR	|=	 ( LPTIM_ICR_ARRMCF );

	/* Enable Interrupt	 */
	NVIC_SetPriority ( LPTIM1_IRQn, 1 ); 							// Set Priority to 1
	NVIC_EnableIRQ   ( LPTIM1_IRQn );  								// Enable LPTIM1_IRQn interrupt in NVIC

	/* ARRM interrupt enabled	 */
	LPTIM1->IER	|=	 LPTIM_IER_ARRMIE;
}
