#include "SPIslave.h"
#include "uart.h"

volatile uint8_t received_data = 0;
volatile uint8_t send_index = 0;
const char message[] = "Hello Master\r\n";
const uint8_t message_length = sizeof(message);

void spi_slave_init(void) {
    // Set MISO as output
    DDRB |= (1 << PB4);  // MISO output
    DDRB &= ~((1 << PB3) | (1 << PB5) | (1 << PB2)); // MOSI, SCK, SS as input

    // Enable SPI in slave mode
    SPCR = (1 << SPE) | (1 << SPIE);
    SPDR = message[0];
    sei();
}

// SPI Interrupt Service Routine (ISR) – triggered when data is received
ISR(SPI_STC_vect) {
    received_data = SPDR; // Read received data
    uart_transmit(received_data);
    SPDR = message[send_index++];
    if (send_index == message_length) send_index = 0;
    
}

int main(void) {
    uart_init(9600);
    spi_slave_init();
    
    while (1) {

    }
}
