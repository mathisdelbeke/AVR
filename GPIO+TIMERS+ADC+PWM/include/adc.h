#ifndef ADC_H
#define ADC_H

#include <avr/io.h>
#include <avr/interrupt.h>

void adc_init();
void adc_start_conversion(uint8_t channel);
uint16_t adc_read(uint8_t channel);
uint8_t adc_is_ready();
uint16_t adc_get_value();

#endif