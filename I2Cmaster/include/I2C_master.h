#ifndef I2C_MASTER_H
#define I2C_MASTER_H

#include <avr/io.h>
#include "uart.h"

void i2c_init();
void i2c_start(void);
void i2c_write_address(uint8_t address);
void i2c_write_data(uint8_t data);
uint8_t i2c_read_data(uint8_t ack);
void i2c_stop(void);

#endif