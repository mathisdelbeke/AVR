#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

void uart_init();
void uart_transmit_busy(char c);
void uart_transmit_interrupt(char c);
void uart_print(const char *str);
void uart_print_int32(uint32_t num);
void uart_print_int16(uint16_t num);

#endif