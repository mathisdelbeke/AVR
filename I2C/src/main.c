#include "uart.h"
#include "I2C.h"

#include <util/delay.h>

int main() {
	uart_init(9600);
	i2c_init();

	uint8_t data = 0;
	while(1) {
		uart_print_string("waiting start\r\n");
		i2c_start();
		uart_print_string("started for write\r\n");
		i2c_write_address(0x10);
		uart_print_string("address for write\r\n");
		i2c_write_data('1');
		uart_print_string("Done waiting write");
		i2c_stop();

		i2c_start();
		uart_print_string("started for read\r\n");
		i2c_write_address(0x11);
		uart_print_string("address for read\r\n");
		data = i2c_read_data(0);
		uart_print_string("Done waiting read");
		uart_print_string("data: ");
		uart_print_unsigned(data);
		uart_print_string("\r\n");
		i2c_stop();
	}
	return 0;
}
