#ifndef MILLIS_H
#define MILLIS_H

#include <avr/interrupt.h>
#include "uart.h"

void millis_init();
uint32_t millis();
void print_seconds();

#endif