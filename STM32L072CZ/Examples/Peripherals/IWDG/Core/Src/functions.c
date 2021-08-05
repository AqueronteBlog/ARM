/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        05/August/2021
 * @version     05/August/2021   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */


#include "functions.h"

/**
 * @brief       void conf_GPIO  ( void )
 * @details     It configures GPIO to work with the LEDs.
 *
 *					LEDs:
 * 						- LD1:	PB_5
 * 						- LD2:	PA_5
 * 						- LD3:	PB_6
 * 						- LD4:	PB_7
 *
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        05/August/2021
 * @version		05/August/2021   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO  ( void )
{
	/* GPIOA and GPIOB Periph clocks enable	 */
	RCC->IOPENR	|=	 ( RCC_IOPENR_GPIOAEN | RCC_IOPENR_GPIOBEN );

	/* GPIOB Mode: General purpose output mode	 */
	GPIOB->MODER	&=	~( GPIO_MODER_MODE5_Msk | GPIO_MODER_MODE6_Msk | GPIO_MODER_MODE7_Msk );
	GPIOB->MODER	|=	 ( GPIO_MODER_MODE5_0 | GPIO_MODER_MODE6_0 | GPIO_MODER_MODE7_0 );

	/* GPIOB Output type: Output push-pull	 */
	GPIOB->OTYPER	&=	~( GPIO_OTYPER_OT_5 | GPIO_OTYPER_OT_6 | GPIO_OTYPER_OT_7 );

	/* GPIOB Output speed: Low speed	 */
	GPIOB->OSPEEDR	&=	~( GPIO_OSPEEDER_OSPEED5_Msk | GPIO_OSPEEDER_OSPEED6_Msk | GPIO_OSPEEDER_OSPEED7_Msk );

	/* GPIOB Output: No pull-up, pull-down	 */
	GPIOB->PUPDR	&=	~( GPIO_PUPDR_PUPD5_Msk | GPIO_PUPDR_PUPD6_Msk | GPIO_PUPDR_PUPD7_Msk );

	/* GPIOB Output: PA_5, PA_6 and PA_7 reset	 */
	GPIOB->BSRR	|=	 ( GPIO_BSRR_BR_5 | GPIO_BSRR_BR_6 | GPIO_BSRR_BR_7 );

	/* GPIOA Mode: General purpose output mode	 */
	GPIOA->MODER	&=	~( GPIO_MODER_MODE5_Msk );
	GPIOA->MODER	|=	 GPIO_MODER_MODE5_0;

	/* GPIOA Output type: Output push-pull	 */
	GPIOA->OTYPER	&=	~GPIO_OTYPER_OT_5;

	/* GPIOA Output speed: Low speed	 */
	GPIOA->OSPEEDR	&=	~GPIO_OSPEEDER_OSPEED5_Msk;

	/* GPIOA Output: No pull-up, pull-down	 */
	GPIOA->PUPDR	&=	~GPIO_PUPDR_PUPD5_Msk;

	/* GPIOA Output: PB_6 reset	 */
	GPIOA->BSRR	|=	 GPIO_BSRR_BR_5;
}


/**
 * @brief       void conf_Range ( void )
 * @details     It configures the voltage scaling configuration: 1.2V ( Range 3 ).
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        05/August/2021
 * @version		05/August/2021   The ORIGIN
 * @pre         N/A
 * @warning     Make sure that the f_CORE <= 4.2MHz.
 */
void conf_Range ( void )
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
 * @brief       void conf_IWDG ( void )
 * @details     It configures the independent watchdog (IWDG).
 *
 * 				- f_IWDG = f_LSI/4 = 37000/32 = 1156.25Hz
 * 				- Prescaler: 32
 * 				- Overflow ( Reset ): IWDG_RLR/f_IWDG = 578/1156.25 ~ 0.5s
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        05/August/2021
 * @version		05/August/2021   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void conf_IWDG ( void )
{
	/* Enable the IWDG	 */
	IWDG->KR	=	 ( 0x0000CCCC << IWDG_KR_KEY_Pos );

	/* Enable the register access	 */
	IWDG->KR	=	 ( 0x00005555 << IWDG_KR_KEY_Pos );

	/* Write the prescaler: /32	 */
	while ( ( IWDG->SR & IWDG_SR_PVU_Msk ) == IWDG_SR_PVU );	// Prescaler value can be updated only when PVU bit is reset
	IWDG->PR	=	~( IWDG_PR_PR_0 | IWDG_PR_PR_1 | IWDG_PR_PR_2 );
	IWDG->PR   |=	 ( IWDG_PR_PR_0 | IWDG_PR_PR_1 );

	/* Write the Reload register: 578 (overflow/reset every 0.5s )	 */
	while ( ( IWDG->SR & IWDG_SR_RVU_Msk ) == IWDG_SR_RVU );	// Reload value can be updated only when RVU bit is reset
	IWDG->RLR	=	 ( 578U << IWDG_RLR_RL_Pos );
	while ( ( IWDG->SR & IWDG_SR_RVU_Msk ) == IWDG_SR_RVU );	// Reload value can be updated only when RVU bit is reset

	/* Refresh the counter value	 */
	IWDG->KR	=	 ( 0x0000AAAA << IWDG_KR_KEY_Pos );
}
