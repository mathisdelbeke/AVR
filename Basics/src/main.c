#include "io.h"
#include "millis.h"
#include "uart.h"
#include "adc.h"
#include "pwm.h"

int main(void) {
    io_init();
    timer_init();
    interrupts_init();
    millis_init();
    uart_init();
    adc_init();
    pwm_init();
    
    while (1) {
        check_button();
        print_seconds();
        uint16_t analog_value = adc_read(0);
        set_brightness(analog_value);
    }
}
