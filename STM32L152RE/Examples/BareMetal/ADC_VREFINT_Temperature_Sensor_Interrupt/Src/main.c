/**
 * @brief       main.c
 * @details     This example shows how to read the internal temperature sensor and calculates the actual V_DDA by interrupt mode. Every one
 * 				second, the data will be transmitted through the UART ( 230400 baud rate ). Two ADC channels are read in regular sequence.
 *
 * 				The microcontroller will remain in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        28/September/2018
 * @version     28/September/2018   The ORIGIN
 * @pre         This firmware was tested on the NUCLEO-L152RE with Atollic TrueSTUDIO for STM32 ( v9.0.1 ). This project was
 * 				generated using SMT32CubeMX ( used to generate a template ).
 * @warning     Although HAL driver was generated, just the Low Power functions are used.
 */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l1xx_hal.h"

/* USER CODE BEGIN Includes */
#include "board.h"
#include "variables.h"
#include "functions.h"
#include "interrupts.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
#define VREFINT_CAL						((uint16_t*) ((uint32_t)0x1FF800F8))	/*!<   Embedded internal reference voltage calibration values at temperature of 30C and VDD = 3V				*/

#define TS_CAL2  						((uint16_t*) ((uint32_t)0x1FF800FE))	/*!<   Temperature sensor calibration value acquired at 110°C and VDD = 3V	*/
#define TS_CAL1	  						((uint16_t*) ((uint32_t)0x1FF800FA))	/*!<   Temperature sensor calibration value acquired at 30°C and VDD = 3V	*/
#define TEMPSENSOR_CAL1_TEMP			30.0f                    				/*!<   Internal temperature sensor, temperature at which temperature sensor has been calibrated in production 	*/
#define TEMPSENSOR_CAL2_TEMP 			110.0f                    				/*!<   Internal temperature sensor, temperature at which temperature sensor has been calibrated in production	*/
#define CALIBRATION_REFERENCE_VOLTAGE	3.0f									/*!<   VDD for calibration data												*/
#define REFERENCE_VOLTAGE				3.3f									/*!<   Current VDD for the system											*/


#define TX_BUFF_SIZE  128	                     			/*!<   UART buffer size                              		*/
#define UART_CLK	  16000000UL                  			/*!<   UART f_CK = 16 MHz                              		*/

volatile uint32_t mySystemCoreClock;						/*!<  System CLK in MHz  		   							*/
volatile uint32_t myUARTClock;								/*!<  UART CLK in MHz  		   	   							*/

volatile system_state_machine_t	myState;           			/*!<  State machine for this example						*/

volatile uint8_t  myMessage[ TX_BUFF_SIZE ];      			/*!<  Message to be transmitted through the UART         	*/
volatile uint8_t  *myPtr;                         			/*!<  Pointer to point out myMessage                     	*/

volatile uint32_t myRawADC_value;                     		/*!<  It stores the raw ADC value							*/
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  int32_t	ts_data	 		=	0UL;
  int32_t	vrefint_data	=	0UL;
  float		myTemperature	=	0UL;
  float		myCalculatedVDD	=	0UL;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  Conf_CLK   ();

  /* Range 2: System frequency up to 16 MHz	 */
  __HAL_PWR_VOLTAGESCALING_CONFIG ( PWR_REGULATOR_VOLTAGE_SCALE2 );
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */
  Conf_GPIO  ();
  Conf_USART ( UART_CLK, 230400 );				// 230400 Baud Rate
  Conf_ADC   ();
  Conf_RTC   ();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  myState	 =	 STATE_SLEEP_MODE;
  while (1)
  {
	  /* Check myState	 */
	  switch ( myState )
	  {
	  	  default:
	  	  case STATE_SLEEP_MODE:
	  		  /* Low power: Sleep mode	 */
	  		  HAL_PWR_EnterSLEEPMode ( PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI );
	  		  break;

	  	  case STATE_TRIGGER_INTERNAL_TEMPERATURE:
	  		  GPIOA->BSRR	 =	 ( 1UL << LED_1 );							// Turn it ON

	  		  /* Disable RTC WakeUp IRQ  */
	  		  NVIC_DisableIRQ ( RTC_WKUP_IRQn );

	  		  /* Start a conversion for Temperature Sensor	 */
	  		  ADC1->CR2	|=	 ADC_CR2_SWSTART;

	  		  /* Go to sleep mode, the states are changed in the interrupts mostly	 */
	  		  myState	 	 =	 STATE_SLEEP_MODE;
	  		  break;

	  	  case STATE_GET_RAW_TEMPERATURE_DATA:
	  		  /* Read the result  */
	  		  ts_data	 =	 myRawADC_value;

	  		  /* Trigger a new ADC measurement	 */
	  		  myState	 	 =	 STATE_TRIGGER_VDD;

	  	  case STATE_TRIGGER_VDD:
	  		  /* Start a conversion for V_REFINT	 */
	  		  ADC1->CR2	|=	 ADC_CR2_SWSTART;

	  		  /* Go to sleep mode, the states are changed in the interrupts mostly	 */
	  		  myState	 	 =	 STATE_SLEEP_MODE;
	  		  break;

	  	  case STATE_GET_RAW_VDD_DATA:
	  		  /* Read the result  */
	  		  vrefint_data	 =	 myRawADC_value;

	  		  /* Process all the data	 */
	  		  myState	 	 =	 STATE_PROCESS_ALL_DATA;

	  	  case STATE_PROCESS_ALL_DATA:
	  		/* Calculate the true temperature
	  		 * 	NOTE:
	  		 * 		Because of all the calibration data was taken at VDDA = 3V and our system is
	  		 * 		powered at VDDA = 3.3V, the ts_data must be normalized by using the formula below:
	  		 *
	  		 * 			ts_data_normalised = VDDA*ts_data/3
	  		 *
	  		 * 		Ref: AN3964 Application note, 1.2 Temperature measurement and data processing, p6/14
	  		 */
	  		  myTemperature	 =	 (float)( ( TEMPSENSOR_CAL2_TEMP - TEMPSENSOR_CAL1_TEMP )/( *TS_CAL2 - *TS_CAL1 ) ) * ( ( ts_data * ( REFERENCE_VOLTAGE / CALIBRATION_REFERENCE_VOLTAGE ) ) - *TS_CAL1 ) + 30.0f;

	  		  /* Calculate the actual V_DDA
	  		   * 	NOTE:
	  		   * 		VDDA = 3 V x VREFINT_CAL / VREFINT_DATA
	  		   *
	  		   * 		Ref: CD00240193 Reference Manual, Calculating the actual VDDA voltage using the internal reference voltage, p288/911
	  		   */
	  		  myCalculatedVDD	 =	 (float)( ( 3.0f * *VREFINT_CAL )/vrefint_data );

	  		  /* Send all the data through the UART	 */
	  		  myState	 	 =	 STATE_SEND_DATA_THROUGH_UART;

	  	  case STATE_SEND_DATA_THROUGH_UART:
	  		  /* Parse the data	 */
	  		  sprintf ( (char*)myMessage, "Temperature: %ld C, V_DDA: %ld mV\r\n", (int32_t)( myTemperature + 0.5f ), (int32_t)( 1000.0f * myCalculatedVDD ) );

	  		  /* Transmit data through the UART	 */
	  		  myPtr   	 =   &myMessage[0];
	  		  USART2->DR	 =	 *myPtr;
	  		  USART2->CR1	|=	 USART_CR1_TE;		// Transmitter Enabled

	  		  /* Reset variables	 */
	  		  myState	 	 =	 STATE_SLEEP_MODE;
	  		  break;
	  	  }

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
