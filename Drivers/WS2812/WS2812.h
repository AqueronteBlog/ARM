/**
 * @brief       WS2812.h
 * @details     Intelligent control LED integrated light source.
 *              Header file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        16/July/2019
 * @version     16/July/2019    The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */


#include "stdint.h"
#include "stdbool.h"
#include "ws2812_nrf52.h"


/**
  * @brief   DATA TRANSFER TIME
  *           NOTE: Time in ns.
  */
typedef enum
{
  WS2812_DATA_TRANSFER_TIME_T0H       =   350,      /*!<   TOH: 0.35 us             */
  WS2812_DATA_TRANSFER_TIME_T0L       =   800,      /*!<   TOH: 0.80 us             */
  WS2812_DATA_TRANSFER_TIME_T1H       =   700,      /*!<   TOH: 0.70 us             */
  WS2812_DATA_TRANSFER_TIME_T1L       =   600,      /*!<   TOH: 0.60 us             */
  WS2812_DATA_TRANSFER_TIME_TOLERANCE =   150,      /*!<   Tolerance: ±0.15 us      */
  WS2812_DATA_TRANSFER_TIME_RES       =   50000     /*!<   Reset code: above 50 us  */
} WS2812_data_transfer_time_t;




/**
  * @brief   TYPEDEF DEFINITIONS
  */
/** Delay function pointer which must be mapped to the platform specific function of the user.
  */
typedef void (*ws2812_delay_fptr_t)( uint32_t myDelay_ns );




#ifndef WS2812_VECTOR_STRUCT_H
#define WS2812_VECTOR_STRUCT_H
typedef struct
{
  ws2812_delay_fptr_t delay_ns;         /*!<  Function to pointer, delay in ns  */
} WS2812_com_t;


typedef struct
{
  uint32_t  numberOfLEDs;               /*!<  Number of LEDs                    */
} WS2812_data_t;


typedef struct
{
  uint16_t  red;                        /*!<  Value for Red color               */
  uint16_t  green;                      /*!<  Value for Green color             */
  uint16_t  blue;                       /*!<  Value for Blue color              */
} WS2812_num_leds_t;
#endif




/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
  WS2812_SUCCESS     =       0,
  WS2812_FAILURE     =       1
} WS2812_status_t;




/**
  * @brief   FUNCTION PROTOTYPES
  */
/** It configures the platform.
  */
WS2812_status_t WS2812_Init           ( WS2812_parameters_t myWS2812parameters                    );

/** It sends data.
  */
WS2812_status_t WS2812_SendLEDsBuffer ( WS2812_num_leds_t* myLEDsBuffer, WS2812_data_t myNumLEDs  );


