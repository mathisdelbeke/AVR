#include "SPImaster.h" 
#include "uart.h"

volatile uint8_t spi_received_data = 0;  
volatile uint8_t spi_transmission_complete = 0;  

const char message[] = "Hello Slave\r\n";

void spi_master_init(void) {
    DDRB |= (1 << PB3) | (1 << PB5) | (1 << PB2);  // MOSI, SCK, SS as output
    DDRB &= ~(1 << PB4);  // MISO as input

    // Enable SPI, Set as Master, Set clock rate fck/16, enable interrupt
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0) | (1 << SPIE);
    sei();
}

uint8_t spi_master_transmit(uint8_t data) {
    spi_transmission_complete = 0;
    SPDR = data; // Load data into the SPI data register
    while (!spi_transmission_complete); // Wait until response
    return spi_received_data;
}

ISR(SPI_STC_vect) {
    spi_received_data = SPDR;  // Read received data
    spi_transmission_complete = 1; 
}

int main(void) {
    uart_init(9600);
    spi_master_init();
    
    uint8_t received_byte = 0;
    while (1) {
        for (int i = 0; message[i] != '\0'; i++) {
            received_byte = spi_master_transmit(message[i]);
            uart_transmit(received_byte);
            _delay_ms(10);
        }
        _delay_ms(1000);
    }
}
