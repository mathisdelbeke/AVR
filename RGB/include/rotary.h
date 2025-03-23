#ifndef ROTARY_H
#define ROTARY_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void rotary_init();
uint8_t rotary_read();
void rotary_set_pos(uint8_t pos);
void interrupt_init();
uint8_t is_button_pressed();
void reset_button_pressed();

#endif