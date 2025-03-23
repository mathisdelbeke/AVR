#include "rgb.h"
#include "uart.h"

#define PWM_R PB1
#define PWM_G PB2
#define PWM_B PD3

#define TIMER1_TOP 39999

void rgb_init() {
    pwms_init();
    timer1_init();
    timer2_init();
}

void pwms_init() {
    DDRD |= (1 << PWM_B);
    DDRB |= (1 << PWM_R) | (1 << PWM_G);
}

void timer1_init() {
    // Timer1 set as Fast PWM till TOP value and prescaler 8
    // OC1A and OC1B pins clear when their compare value is matched
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11);
    ICR1 = TIMER1_TOP; // TOP value until Timer1 resets, not max
}

void timer2_init() {
    // Timer2 set as Fast PWM till max and prescaler 8
    TCCR2A = (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B = (1 << CS21);
    OCR2B = 0;
}

void set_brightness_r(uint8_t val) {
    // Val needs to be mapped to 0 - 39999 range
    OCR1A = (val * TIMER1_TOP) / 255;
}

void set_brightness_g(uint8_t val) {
    // Val needs to be mapped to 0 - 39999 range
    OCR1B = (val * TIMER1_TOP) / 255;   
}

void set_brightness_b(uint8_t val) {
    // Timer2 has also range of 255
    OCR2B = val;   
}

