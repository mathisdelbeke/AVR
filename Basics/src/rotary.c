#include "rotary.h"
#include "uart.h"

#define ENCODER_CLK_PIN PB4
#define ENCODER_DT_PIN PB3

volatile int16_t rotary_pos = 0;      // Safe range, could be to big
volatile uint8_t prev_clk_state = 1;  // To check if clk changed

void rotary_init() {
    DDRB &= ~((1 << ENCODER_CLK_PIN) | (1 << ENCODER_DT_PIN));
    PORTB |= (1 << ENCODER_CLK_PIN) | (1 << ENCODER_DT_PIN);       
}

int rotary_read() {
    uint8_t clk_state = PINB & (1 << ENCODER_CLK_PIN);
    uint8_t dt_state  = PINB & (1 << ENCODER_DT_PIN);

    if (clk_state != prev_clk_state) {
        if (clk_state == 0) {  
            if (dt_state == 0)
                rotary_pos++;  
            else 
                rotary_pos--;  
        }
    }
    prev_clk_state = clk_state;

    //uart_print_int16(rotary_pos);
    //uart_print("\r\n");
    return rotary_pos;
}