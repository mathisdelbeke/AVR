#include "pwm_led.h"

#define PWM_PIN PD3
#define BUTTON_PIN PD2

volatile uint8_t button_pressed = 0;   
volatile uint8_t debounce_flag = 0;
uint8_t pwm_on = 0;

void pwm_led_init() {
    pwm_init();
    button_init();
    timer_init();
    interrupts_init();
}

void pwm_init() {
    DDRD |= (1 << PWM_PIN);
    TCCR2A |= (1 << WGM21) | (1 << WGM20);      // Wave Generation Mode bits for Fast PWM for Timer 2
    TCCR2A |= (1 << COM2B1);                    // Compare Output Mode in Timer Counter Control Register
    TCCR2B |= (1 << CS22);                      // Prescaler to 64
}

void set_brightness(uint16_t adc_value) {
    uint16_t brightness = (adc_value * 255UL) / 1024;
    OCR2B = brightness;                         // Output Compare Register A, HIGH if under, LOW if exceeded
                                                // It holds timer value, DC = (OCR2B/255) * 100
}

uint8_t pwm_is_on() {
    return pwm_on;
} 

void button_init() {
    DDRD &= ~(1 << BUTTON_PIN);  
    PORTD |= (1 << BUTTON_PIN); // Enable pull-up
}

void timer_init() {
    TCCR1B |= (1 << WGM12);   // CTC mode
    TIMSK1 |= (1 << OCIE1A);  // Interrupt compare match
    TCCR1B |= (1 << CS12);    // Prescaler 256
    OCR1A = 10000;            // Compare value
}

void interrupts_init() {
    EICRA |= (1 << ISC01);  // Configure falling edge as trigger in External Interrupt Control Register A
    EIMSK |= (1 << INT0);   // Enable INT0 interrupt in External Interrupt Mask Register
    sei();                  // Enable global interrupts
}

void check_button() {           // Poll if interrupt has happened
    if (button_pressed) {
        pwm_on ^= 1; 
        set_brightness(1024);
        button_pressed = 0;
    }
}

ISR(INT0_vect) {            // ISR for external interrupt 0 (INT0)
    if (!debounce_flag) {   // If debounce time has passed
        debounce_flag = 1;
        TCCR1B |= (1 << CS12);  // Start timer
    }
}

ISR(TIMER1_COMPA_vect) {    // When compare value of timer been reached
    button_pressed = 1;     
    debounce_flag = 0;      // Debounce time has passed
    TCCR1B &= ~(1 << CS12); // Stop timer
    TCNT1 = 0;              // reset timer
}
