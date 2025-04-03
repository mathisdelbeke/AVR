#ifndef SPI_MASTER_H
#define SPI_MASTER_H

#include <avr/io.h>
#include <util/delay.h>

void spi_master_init(void);
void spi_master_transmit(uint8_t data);

#endif 