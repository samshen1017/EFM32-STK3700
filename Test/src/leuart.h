#ifndef LEUART_H
#define LEUART_H

#include <stdint.h>
#include <stdbool.h>
#include "em_chip.h"
#include "em_cmu.h"
#include "em_leuart.h"
#include "em_gpio.h"

#define LEUART_LOCATION    LEUART_ROUTE_LOCATION_LOC0
#define LEUART_TXPORT      gpioPortD
#define LEUART_TXPIN       4
#define LEUART_RXPORT      gpioPortD
#define LEUART_RXPIN       5

extern void leuart_init(void);
extern void leuart_write(uint8_t *data, uint32_t size);
extern void leuart_read(uint8_t *buf);
#endif

