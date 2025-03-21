#include "pwm.h"

#define PWM_PIN PD3

void pwm_init() {
    DDRD |= (1 << PWM_PIN);
    PORTD |= (1 << PWM_PIN);
    TCCR2A |= (1 << WGM21) | (1 << WGM20);      // Wave Generation Mode bits for Fast PWM for Timer 2
    TCCR2A |= (1 << COM2B1);                    // Compare Output Mode in Timer Counter Control Register
    TCCR2B |= (1 << CS22);                      // Prescaler to 64
}

void set_brightness(uint16_t adc_value) {
    uint16_t brightness = (adc_value * 255UL) / 1024;
    OCR2B = brightness;                         // Output Compare Register, HIGH if under, LOW if exceeded
                                                // It holds timer value, DC = (OCR2B/255) * 100
    uart_print("ADC: ");
    uart_print_int16(adc_value);
    uart_print(" -> Brightness: ");
    uart_print_int16(brightness);
    uart_print("\r\n");
}
