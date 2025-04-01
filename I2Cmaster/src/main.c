#include "uart.h"
#include "I2C_master.h"
#include <util/delay.h>

#define WRITE_ADDRESS ((0x18 << 1) | 0)
#define READ_ADDRESS ((0x18 << 1) | 1)

int main() {
	uart_init(9600);
	i2c_init();

	char message[] = "Hello Slave\r\n";
	uint8_t character = 1;

	while(1) {
		i2c_start();
		i2c_write_address(WRITE_ADDRESS);
		for (uint8_t i = 0; message[i] != '\0'; i++) {
			i2c_write_data(message[i]);
		}
		i2c_stop();

		_delay_ms(2000);	
		
		i2c_start();
		i2c_write_address(READ_ADDRESS);
		do {
			character = i2c_read_data(1);
			uart_transmit(character);
		} while (character != '\0');
		i2c_read_data(0);
		i2c_stop();

		_delay_ms(2000);
	}
	return 0;
}
