#include "adc.h"

void adc_init() {
    ADMUX = (1 << REFS0);       // Reference voltage AVCC (5 V) set in ADC Multiplexer Selection Register
    ADCSRA |= (1 << ADEN);      // Enables ADC in ADC Control and Status Register A
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler to 128 
}

uint16_t adc_read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF8);          // Clears previous channel selection
    ADMUX |= (channel & 0x07);       // Multiplexes channel, ensured it is between 0 and 7
    ADCSRA |= (1 << ADSC);           // Start ADC in Control and Status Register
    while (ADCSRA & (1 << ADSC));    // Polls for Start Conversion bit
    return ADC;                      // Holds the conversion
}