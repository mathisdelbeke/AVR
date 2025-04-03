#include "SPIslave.h"
#include "uart.h"

void spi_slave_init(void) {
    // Set MISO as output
    DDRB |= (1 << PB4);  // MISO output
    DDRB &= ~((1 << PB3) | (1 << PB5) | (1 << PB2)); // MOSI, SCK, SS as input

    // Enable SPI in slave mode
    SPCR = (1 << SPE);
}

uint8_t spi_slave_receive(void) {
    while (!(SPSR & (1 << SPIF))); // Wait for reception complete
    return SPDR; // Return received data
}

int main(void) {
    uart_init(9600);
    spi_slave_init();
    
    while (1) {
        uint8_t received_data = spi_slave_receive();
        uart_transmit(received_data);
        uart_print_string("\r\n");
    }
}
