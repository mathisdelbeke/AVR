#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

void adc_init();
uint16_t adc_read(uint8_t channel);

#endif