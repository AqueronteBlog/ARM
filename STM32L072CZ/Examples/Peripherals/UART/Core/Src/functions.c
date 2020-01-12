/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        18/December/2019
 * @version     18/December/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */


#include "functions.h"

/**
 * @brief       void Conf_Range ( void )
 * @details     It configures the voltage scaling configuration: 1.2V ( Range 3 ).
 *
 *
 * @return      N/A
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
 * @details     It configures GPIOs.
 *
 *					LEDs:
 * 						- LD1:	PB_5
 * 						- LD2:	PA_5
 * 						- LD3:	PB_6
 * 						- LD4:	PB_7
 *
 * 					UART5:
 * 						- UART5_TX:	PB_3
 * 						- UART5_RX:	PB_4
 *
 * @return      N/A
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

	/* UART5:
	 * 	- Alternate function mode
	 */
	GPIOB->MODER	&=	~( GPIO_MODER_MODE3 | GPIO_MODER_MODE4 );
	GPIOB->MODER	|=	 ( GPIO_MODER_MODE3_1 | GPIO_MODER_MODE4_1 );
}



/**
 * @brief       void Conf_UART5 ( uint32_t , uint32_t )
 * @details     It configures UART5.
 *
 *				- UART5:
 * 					-- UART5 BaudRate = 115200, 8-bit, 1-bit STOP, NO Parity
 * 					-- Tx/Rx Interrupts ENABLED
 *
 *
 * @param[in]    myCK:			UART Clock ( f_CK ).
 * @param[in]    myBaudRate:	UART baud rate.
 *
 * @param[out]   N/A.
 *
 *
 *
 * @return      Status of Conf_UART5.
 *
 * @author      Manuel Caballero
 * @date        19/December/2019
 * @version		31/December/2019   myCLK and myBaudRate were added.
 * 				19/December/2019   The ORIGIN
 *
 * @pre         OVER8 is calculated automatically
 * @warning     N/A
 */
uart_status_t Conf_UART5 ( uint32_t myCK, uint32_t myBaudRate )
{
	uint32_t	myUSARTDIV	=	0UL;


	/* UART clock enable	 */
	RCC->APB1ENR	|=	 RCC_APB1ENR_USART5EN;

	/* UART5:
	 * 	- Disable UART5
	 */
	USART5->CR1	&=	~USART_CR1_UE;

	/* UART5:
	 * 	- Worth length: Start bit, 8 data bits, 1 stop bits.
	 * 	- Parity control disabled
	 * 	- Transmitter is disabled
	 * 	- Receiver is disabled
	 */
	USART5->CR1	&=	~( USART_CR1_M1 | USART_CR1_OVER8 | USART_CR1_PCE | USART_CR1_TE | USART_CR1_RE );

	/* UART5:
	 * 	- Auto baud rate detection is disabled
	 * 	- TX pin signal works using the standard logic levels
	 * 	- RX pin signal works using the standard logic levels
	 * 	- TX/RX pins are used as defined in standard pinout
	 * 	- 1 stop bit
	 * 	- CK pin disabled
	 */
	USART5->CR2	&=	~( USART_CR2_ABREN | USART_CR2_TXINV | USART_CR2_RXINV | USART_CR2_SWAP | USART_CR2_STOP | USART_CR2_CLKEN );

	/* UART5:
	 * 	- CTS hardware flow control disabled
	 * 	- RTS hardware flow control disabled
	 * 	- DMA mode is disabled for transmission
	 * 	- DMA mode is disabled for reception
	 * 	- Smartcard Mode disabled
	 * 	- NACK transmission in case of parity error is disabled
	 * 	- Half duplex mode is not selected
	 * 	- IrDA disabled
	 * 	- Error interrupt enable: Interrupt is inhibited
	 */
	USART5->CR3	&=	~( USART_CR3_CTSE | USART_CR3_RTSE | USART_CR3_DMAT | USART_CR3_DMAR | USART_CR3_SCEN | USART_CR3_NACK | USART_CR3_HDSEL | USART_CR3_IREN | USART_CR3_EIE );

	/* UART5
	 *  - Check oversampling by 16 if it isn´t possible, try oversampling by 8. NOTE: It rounds the result by default.
	 */
	USART5->BRR	&=	~( USART_BRR_DIV_FRACTION | USART_BRR_DIV_MANTISSA );

	myUSARTDIV	 =	(uint32_t)( ( myCK / myBaudRate ) + 0.5 );
	if ( myUSARTDIV >= 16 )
	{
		/* Oversampling by 16	 */
		USART5->CR1	&=	~( USART_CR1_OVER8 );

		/* Update mantissa	 */
		USART5->BRR	|=	 ( ( myUSARTDIV & USART_BRR_DIV_MANTISSA_Msk ) << USART_BRR_DIV_MANTISSA_Pos );
	}
	else
	{
		/* Check oversampling by 8	 */
		myUSARTDIV	*=	 2UL;
		if ( myUSARTDIV >= 16 )
		{
			/* Oversampling by 8	 */
			USART5->CR1	|=	 USART_CR1_OVER8;

			/* Update mantissa	 */
			USART5->BRR	|=	 ( ( ( myUSARTDIV & USART_BRR_DIV_MANTISSA_Msk ) >> 1UL ) << USART_BRR_DIV_MANTISSA_Pos );
			USART5->BRR	&=	 0b011;																						// BRR[3] must be kept cleared
		}
		else
		{
			return UART_OVERSAMPLING_INCOMPATIBLE;
		}
	}

	/* Update fraction	 */
	USART5->BRR	|=	 ( ( myUSARTDIV & USART_BRR_DIV_FRACTION_Msk ) << USART_BRR_DIV_FRACTION_Pos );

	/* UART5 Interrupts
	 *  - Clear all interrupt flags ( in those supported modes )
	 */
	USART5->ICR	|=	 ( USART_ICR_PECF | USART_ICR_FECF | USART_ICR_NCF | USART_ICR_ORECF | USART_ICR_IDLECF | USART_ICR_TCCF | USART_ICR_CMCF );

	NVIC_SetPriority ( USART4_5_IRQn, 1 ); 									// Set Priority to 1
	NVIC_EnableIRQ   ( USART4_5_IRQn );  									// Enable UART5_IRQn interrupt in NVIC

	/* Enable UART5, RX and RX interrupt	 */
	USART5->CR1	|=	 ( USART_CR1_RE | USART_CR1_RXNEIE | USART_CR1_UE );


	return UART_SUCCESS;
}
