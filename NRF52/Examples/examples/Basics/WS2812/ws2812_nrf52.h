/**
 * @brief       ws2812_nrf52.h
 * @details     NRF52 WS2812 function libraries.
 *              Header file.
 *
 *
 * @return      NA
 *
 * @author      Manuel Caballero
 * @date        16/July/2019
 * @version     16/July/2019    The ORIGIN
 * @pre         N/A
 * @warning     This file is ONLY for NRF52 device.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "nrf.h"
#include "nrf52_bitfields.h"

#ifndef NRF52_WB2812_H_
#define NRF52_WB2812_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief   NRF52 PARAMETERS FOR WB2812
  */
typedef struct{
    /* Port for pins: SDA and SCL  */
    NRF_GPIO_Type* DINport;

    /* Pin number  */
    uint32_t DIN;
} WS2812_parameters_t;



/**
  * @brief   INTERNAL CONSTANTS
  */
typedef enum
{
    WB2812_CON_SUCCESS  =   0x00,
    WB2812_CON_FAILURE  =   0x01
} WS2812_con_status_t;



/**
  * @brief   FUNCTION PROTOTYPES
  */
/** WS2812 init function.
  */
WS2812_con_status_t ws2812_init ( WS2812_parameters_t myWS2812parameters );


#ifdef __cplusplus
}
#endif

#endif /* NRF52_WB2812_H_ */