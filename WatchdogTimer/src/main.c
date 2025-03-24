#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include "uart.h"

#define LED_PIN PB5

void variable_delay_ms(uint16_t ms) {
    for (uint16_t i = 0; i < ms; i++) {
        _delay_ms(1);
    }
}

ISR(WDT_vect) {
    uart_print_string("\nSave something before reset\r\n\n");
}

int main(void) {
    uart_init(9600);
    DDRB |= (1 << LED_PIN); 
    PORTB |= (1 << LED_PIN);    // Led will turn off during reset
    uint16_t delay_time = 0;    // Current workload
    
    cli(); // Disable global interrupts
    MCUSR &= ~(1 << WDRF); // Clear Watchdog Reset Flag
    WDTCSR |= (1 << WDCE) | (1 << WDE); // Enable configuration mode
    WDTCSR = (1 << WDIE) | (1 << WDE) | (1 << WDP2) | (1 << WDP1); // Enable interrupt mode, 1s timeout
    sei(); // Enable global interrupts

    while (1) {
        variable_delay_ms(delay_time);  // Simulate workload
        wdt_reset();                    // Reset watchdog timer

        uart_print_string("Delay: ");
        delay_time += 100;              // Increase workload
        uart_print_unsigned(delay_time);
        uart_print_string("\r\n");
    }
}
