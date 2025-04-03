#ifndef SPI_SLAVE_H
#define SPI_SLAVE_H

#include <avr/io.h>

void spi_slave_init(void);
uint8_t spi_slave_receive(void);

#endif 