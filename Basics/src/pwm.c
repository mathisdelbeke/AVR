#include "pwm.h"
#include "uart.h"

void pwm_init() {
    DDRD |= (1 << PB3);
    PORTD |= (1 << PB3);
        // Set Timer0 to Fast PWM mode (WGM02:0 = 011)
    TCCR2A |= (1 << WGM21) | (1 << WGM20);  // Fast PWM
    TCCR2A |= (1 << COM2B1);  // Non-inverting mode
    
        // Set prescaler to 64 (gives ~976Hz PWM frequency)
    TCCR2B |= (1 << CS22);
}

void set_brightness(uint16_t adc_value) {
    uint16_t brightness = (adc_value * 255UL) / 1024;
    OCR2B = brightness;

    uart_print("ADC: ");
    uart_print_int16(adc_value);
    uart_print(" -> Brightness: ");
    uart_print_int16(brightness);
    uart_print("\r\n");

}
