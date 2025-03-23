#include "uart.h"
#include "rgb.h"
#include "rotary.h"

int main() {
    uart_init();
    rotary_init();
    rgb_init();

    uint8_t pos_r = 0;
    uint8_t pos_g = 0;
    uint8_t pos_b = 0;

    uint8_t led_selected = 0;
    uint8_t new_val = 0;

    while(1) {
        if (is_button_pressed()) {
            reset_button_pressed();
            led_selected = (led_selected + 1) % 3;
            if (led_selected == 0) rotary_set_pos(pos_r);
            else if (led_selected == 1) rotary_set_pos(pos_g);
            else if (led_selected == 2) rotary_set_pos(pos_b);
        }

        new_val = rotary_read();

        if (led_selected == 0) {
            pos_r = new_val;
            set_brightness_r(new_val);
        }
        else if (led_selected == 1) {
            pos_g = new_val;
            set_brightness_g(new_val);
        }
        else if (led_selected == 2) {
            pos_b = new_val;
            set_brightness_b(new_val);
        }

        uart_print("\tR: ");
        uart_print_int16(pos_r);
        uart_print("\tG: ");
        uart_print_int16(pos_g);
        uart_print("\tB: ");
        uart_print_int16(pos_b);
        uart_print("\r\n");
    }
}