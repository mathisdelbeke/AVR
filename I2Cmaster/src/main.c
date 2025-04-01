#include "uart.h"
#include "I2C_master.h"
#include <util/delay.h>

int main() {
	uart_init(9600);
	i2c_init();

	char message[] = "Hello Slave\r\n";
	uint8_t data = 0;

	while(1) {
		i2c_start();
		i2c_write_address(0x30);
		for (uint8_t i = 0; message[i] != '\0'; i++) {
			i2c_write_data(message[i]);
		}
		i2c_stop();

		_delay_ms(2000);
	}
	return 0;
}
	/*
		i2c_start();
		i2c_write_address(0x11);
		data = i2c_read_data(0);
		uart_print_unsigned(data);
		i2c_stop();
		*/