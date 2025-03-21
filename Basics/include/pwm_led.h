#ifndef PWM_LED_H
#define PWM_LED_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"

void pwm_led_init();
void pwm_init();
void set_brightness(uint16_t duty);
uint8_t pwm_is_on();
void button_init();
void interrupts_init();
void check_button();

#endif 