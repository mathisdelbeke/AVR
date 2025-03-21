#ifndef IO_H
#define IO_H

#include <avr/io.h>
#include <avr/interrupt.h>

void interrupts_init();
void timer_init();
void io_init();
void check_button();

#endif