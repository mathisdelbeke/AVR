#include "io.h"

#define LED_PIN PB5
#define BUTTON_PIN PD2

volatile uint8_t button_pressed = 0;   
volatile uint8_t debounce_flag = 0;

ISR(TIMER1_COMPA_vect) {    // When compare value of timer been reached
    debounce_flag = 1;      // Set flag to indicate debounce delay has passed
}

ISR(INT0_vect) {            // ISR for external interrupt 0 (INT0)
    if (debounce_flag) {    // Only if the timer has set the debounce flag
        debounce_flag = 0;  
        button_pressed = 1;  
    }
}

void interrupts_init() {
    EICRA |= (1 << ISC01);  // Configure falling edge as trigger in External Interrupt Control Register A
    EIMSK |= (1 << INT0);   // Enable INT0 interrupt in External Interrupt Mask Register
    sei();                  // Enable global interrupts
}

void timer_init() {
    TCCR1B |= (1 << WGM12);   // CTC mode
    TIMSK1 |= (1 << OCIE1A);  // Interrupt compare match
    TCCR1B |= (1 << CS12);    // Prescaler 256
    OCR1A = 15500;            // Compare value
}

void io_init() {
    DDRB |= (1 << LED_PIN); 
    DDRD &= ~(1 << BUTTON_PIN);  
    PORTD |= (1 << BUTTON_PIN);  // Enable pull-up resistor on BUTTON_PIN
}

void check_button() {
    if (button_pressed) {
        PORTB ^= (1 << LED_PIN);
        button_pressed = 0;
    }
}

