#include "uart.h"

#define BAUD 9600
#define F_CPU 16000000UL                         // UL ensures that constant is treaded as Unsigned Long
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1) // Value to have 9600 bits per seconds    

void uart_init() {
    UBRR0H = (UBRR_VALUE >> 8);             // USART Baud Rate Register, upper 8 bits
    UBRR0L = UBRR_VALUE;                    // USART Buad Rate Register, lower 8 bits
    UCSR0B = (1 << TXEN0);                  // Transmit enabled (TX) in USART Control and Status Register B
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Configures 8-bit data, 1 stop bit and no parity in USART Control and Status Register C
}

void uart_transmit(char c) {
    while (!(UCSR0A & (1 << UDRE0)));       // Poll buffer by reading Data Register Empty bit in USART Control and Status Register A
    UDR0 = c;                               // Load the char into USART Data Register
}

void uart_print(const char *str) {          // Start with pointer to the first char of the string
    while (*str) {                          // While the pointer is not null
        uart_transmit(*str++);              // Derefernce pointer first to use it as input and then increment the pointer
    }
}

void uart_print_int(int32_t num) {
    char buffer[12];                        // Max chars needed for int32_t numbers
    itoa(num, buffer, 10);                  // Convert number into chars
    uart_print(buffer);
}

