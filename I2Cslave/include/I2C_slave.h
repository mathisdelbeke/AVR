#ifndef I2C_SLAVE_H
#define I2C_SLAVE_H

#include <avr/io.h>
#include <avr/interrupt.h>

void i2c_slave_init(uint8_t address);

#endif