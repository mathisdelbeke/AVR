#include "SPImaster.h" 
#include "uart.h"

const char message[] = "Hello Slave\r\n";

void spi_master_init(void) {
    // Set MOSI and SCK as output, others as input
    DDRB |= (1 << PB3) | (1 << PB5) | (1 << PB2);  // MOSI, SCK, SS as output
    DDRB &= ~(1 << PB4);  // MISO as input

    // Enable SPI, Set as Master, Set clock rate fck/16
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void spi_master_transmit(uint8_t data) {
    SPDR = data; // Load data into the SPI data register
    while (!(SPSR & (1 << SPIF))); // Wait until transmission is complete
}

int main(void) {
    uart_init(9600);
    spi_master_init();
    
    while (1) {
        uart_transmit('t');
        for (int i = 0; message[i] != '\0'; i++) {
            spi_master_transmit(message[i]); 
        }
        _delay_ms(1000);
    }
}
