#include <avr/io.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "uart.h"

#define LED_PIN PB5

void variable_delay_ms(uint16_t ms) {
    for (uint16_t i = 0; i < ms; i++) {
        _delay_ms(1);
    }
}

int main(void) {
    uart_init(9600);
    DDRB |= (1 << LED_PIN); 
    PORTB |= (1 << LED_PIN);    // Led will turn off during reset
    uint16_t delay_time = 0;    // Current workload
    
    wdt_enable(WDTO_1S);        // Enable Watchdog Timer with a 1s timeout


    while (1) {
        variable_delay_ms(delay_time);  // Simulate workload
        wdt_reset();                    // Reset watchdog timer

        uart_print_string("Delay: ");
        delay_time += 100;              // Increase workload
        uart_print_unsigned(delay_time);
        uart_print_string("\r\n");
    }
}
