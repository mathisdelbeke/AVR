#include "millis.h"

volatile uint32_t millis_counter = 0;   // Number of milliseconds that have passed, volatile for external events

void millis_init() {
    TCCR0A = (1 << WGM01);              // Enable Clear Timer on Compare Match mode in Timer/Counter Control Register A Timer 0 
    TCCR0B = (1 << CS01) | (1 << CS00); // Configure prescaler to 64 in Timer/Counter Control B Timer 0
    OCR0A = 249;                        // The compare value in Output Compare Register A Timer 0
    TIMSK0 |= (1 << OCIE0A);            // Enables Timer 0 Compare Match A interrupt in Timer/Counter Interrupt Mask Register Timer 0
}

ISR(TIMER0_COMPA_vect) {                // Called when the timer counter reaches the OCR0A value      
    millis_counter++;                   // A millisecond has passed
}

uint32_t millis() {
    uint32_t ms;
    cli();                              // Disables global interrupts, ensuring value is not modified while being read
    ms = millis_counter;
    sei();                              // Quickly enable global interrupts again
    return ms;
}

