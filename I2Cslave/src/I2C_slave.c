#include "I2C_slave.h"
#include "uart.h"

#define SLAVE_ADDRESS 0x18

volatile uint8_t send_index = 0;
volatile char message[] = "Hello Master\r\n";
static char received_data = 0;

void i2c_slave_init(uint8_t address) {
    TWAR = (address << 1);      // Load slave address (shifted for 7-bit addressing)
    TWCR = (1 << TWEA) |        // Enable ACK
           (1 << TWEN) |        // Enable TWI
           (1 << TWIE) |         // Enable TWI interrupt
           (1 << TWINT);
    sei();                      // Enable global interrupts
}

ISR(TWI_vect) {
    switch (TWSR & 0xF8) {
        case 0xA8:  // Own SLA+R has been received, ACK sent
        case 0xB8:  // Master has received byte and wants more
            TWDR = message[send_index++];  // Load next byte
            TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT) | (1 << TWIE);  // Enable ACK for next byte
            break;

        case 0xC8:  // Master has received last byte, NACK received
            send_index = 0;  // Reset index for next transaction
            TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT) | (1 << TWIE);
            break;

        case 0x60:  // Own SLA+W has been received, ACK sent
            TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT) | (1 << TWIE);
            break;

        case 0x80:  // Data byte received, ACK sent
            received_data = TWDR;  // Read data
            uart_transmit(received_data);
            TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT) | (1 << TWIE);
            break;

        case 0x88:  // Data byte received, NACK sent (end of reception)
        case 0xA0:  // Stop or repeated start received
            send_index = 0;  // Reset index in case of repeated communication
            TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT) | (1 << TWIE);
            break;

        default:
            TWCR = (1 << TWEA) | (1 << TWEN) | (1 << TWINT) | (1 << TWIE);  // Default case to keep I2C working
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
