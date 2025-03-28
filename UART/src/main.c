#include "uart.h"

int main() {
    uart_init(9600);

    uart_print_string("test\r\n");
    uart_print_signed(-12345);
    uart_print_string("\r\n");
    uart_print_unsigned(12345);
    uart_print_string("\r\n");
    while(1) {
        while (uart_available()) {
            char received_char = uart_read();
            uart_transmit(received_char);
        }
    }
}