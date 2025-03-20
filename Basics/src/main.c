#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.h"
#include "millis.h"
#include "uart.h"
#include "adc.h"

const unsigned long PRINT_DELAY = 1000;
uint32_t last_time = 0;

int main(void) {
    io_init();
    timer_init();
    interrupts_init();
    millis_init();
    uart_init();
    adc_init();
    
    while (1) {
        check_button();
        if ((millis() - last_time) >= PRINT_DELAY) {
            uart_print_int32((last_time / 1000));
            uart_print("\r\n");
            last_time = millis();
        }
        uint16_t analog_value = adc_read(0);
        uart_print("\t\tValue: ");
        uart_print_int16(analog_value);
        uart_print("\r\n");
    }
}
