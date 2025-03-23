#include "rotary.h"
#include "uart.h"

#define ENCODER_CLK_PIN PD6
#define ENCODER_DT_PIN PD7
#define ENCODER_SW PD2

#define STEP_SIZE 8

volatile uint8_t position = 0;
volatile uint8_t button_pressed = 0;
volatile uint8_t prev_clk_state = 1;  // To check if clk changed

void rotary_init() {
    DDRD &= ~((1 << ENCODER_CLK_PIN) | (1 << ENCODER_DT_PIN) | (1 << ENCODER_SW));
    PORTD |= (1 << ENCODER_CLK_PIN) | (1 << ENCODER_DT_PIN) | (1 << ENCODER_SW);
    interrupt_init();       
}

uint8_t rotary_read() {
    uint8_t clk_state = PIND & (1 << ENCODER_CLK_PIN);
    uint8_t dt_state  = PIND & (1 << ENCODER_DT_PIN);

    if (clk_state != prev_clk_state) {
        if (clk_state == 0) {  
            if (dt_state == 0)
                position += STEP_SIZE;
            else
                position -= STEP_SIZE;
        }
    }
    prev_clk_state = clk_state;
    return position;
}

void rotary_set_pos(uint8_t pos) {
    position = pos;
}

void interrupt_init() {
    EICRA |= (1 << ISC01);  // Configure falling edge as trigger in External Interrupt Control Register A
    EIMSK |= (1 << INT0);   // Enable INT0 interrupt in External Interrupt Mask Register
    sei();
}

ISR(INT0_vect) {
    _delay_ms(50);
    if (!(PIND & (1 << ENCODER_SW))) { 
        button_pressed = 1;
    }
}

uint8_t is_button_pressed() {
    return button_pressed;
}

void reset_button_pressed() {
    button_pressed = 0;
}