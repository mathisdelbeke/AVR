#include "adc.h"

volatile uint16_t adc_result;   // Holds value if complete
volatile uint8_t adc_ready = 0; // Flag to indicate completion

void adc_init() {
    ADMUX = (1 << REFS0);       // Reference voltage AVCC (5 V) set in ADC Multiplexer Selection Register
    ADCSRA |= (1 << ADEN);      // Enables ADC in ADC Control and Status Register A
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler to 128
    ADCSRA |= (1 << ADIE);      // Enable ADC interrupt
    sei();  
}

void adc_start_conversion(uint8_t channel) {
    ADMUX = (ADMUX & 0xF8) | (channel & 0x07);  // Select ADC channel
    ADCSRA |= (1 << ADSC);                      // Start ADC conversion
}

uint16_t adc_read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF8);          // Clears previous channel selection
    ADMUX |= (channel & 0x07);       // Multiplexes channel, ensured it is between 0 and 7
    ADCSRA |= (1 << ADSC);           // Start ADC in Control and Status Register
    while (ADCSRA & (1 << ADSC));    // Polls for Start Conversion bit
    return ADC;                      // Holds the conversion
}

uint8_t adc_is_ready() {
    return adc_ready;
}

uint16_t adc_get_value() {
    adc_ready = 0;              // Clear flag after reading
    return adc_result;
}

ISR(ADC_vect) {
    adc_result = ADC;           // ADC is register that holds the value
    adc_ready = 1;              // Ready to get value
}

