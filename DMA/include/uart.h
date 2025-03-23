#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

void uart_init(uint32_t baud);
void uart_transmit(char c);
void uart_print_string(const char *str);
void uart_print_signed(int32_t num);
void uart_print_unsigned(int32_t num);

#endif