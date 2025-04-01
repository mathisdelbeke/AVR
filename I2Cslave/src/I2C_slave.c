#include "I2C_slave.h"
#include "uart.h"

#include <util/delay.h>

#define SLAVE_ADDRESS (0x30 >> 1)

static char received_data = 0;

void i2c_slave_init(uint8_t address) {
    TWAR = (address << 1);      // Load slave address (shifted for 7-bit addressing)
    TWCR = (1 << TWEA) |        // Enable ACK
           (1 << TWEN) |        // Enable TWI
           (1 << TWIE);         // Enable TWI interrupt
    sei();                      // Enable global interrupts
}

ISR(TWI_vect) {
    switch (TWSR & 0xF8) {  // Mask out prescaler bits and check status
        case 0x60:  // SLA+W received (master wants to write)
        case 0x68:  // Arbitration lost, SLA+W received
            TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT) | (1 << TWIE); // Acknowledge and wait for data
            break;

        case 0x80:  // Data received, ACK returned
        case 0x88:  // Data received, NACK returned
            received_data = TWDR;  // Read data
            uart_transmit(received_data);
            TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT) | (1 << TWIE); // ACK next byte
            break;

        case 0xA8:  // SLA+R received, master wants data
        case 0xB0:  // Arbitration lost, SLA+R received
            TWDR = 0x55;  // Example data to send
            TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWIE); // Clear flag to send data
            break;

        case 0xC0:  // Data transmitted, NACK received (end of transmission)
        case 0xC8:  // Data transmitted, ACK received (continue sending)
            TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT) | (1 << TWIE); // Ready for next transmission
            break;

        case 0xA0:  // STOP or repeated START received
            TWCR = (1 << TWEN) | (1 << TWEA) | (1 << TWINT) | (1 << TWIE); // Reset TWI logic
            break;
    }
}

int main() {
    uart_init(9600);
    i2c_slave_init(SLAVE_ADDRESS);
    uart_print_string("Slave ready\r\n");
    while (1) {
        // Other tasks
    }
}
