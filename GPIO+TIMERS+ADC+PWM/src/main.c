#include "millis.h"
#include "uart.h"
#include "adc.h"
#include "pwm_led.h"

int main(void) {
    millis_init();
    uart_init();
    adc_init();
    pwm_led_init();
    rotary_init();
    
    uint16_t analog_value = 0;
    adc_start_conversion(0);

    while (1) {
        check_button();
        print_seconds();
        if (pwm_is_on()) {
            if (adc_is_ready()) {
                analog_value = adc_get_value();
                adc_start_conversion(0);
            }
            set_brightness(analog_value);
        }
    }
}
