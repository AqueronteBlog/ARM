#include "nrf.h"
#include "nrf51_bitfields.h"
#include "board.h"

typedef enum{
    ON,
    OFF
}LEDs_state;


uint32_t changeLEDsSTATE     =   ON;
