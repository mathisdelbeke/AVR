#ifndef PWM_H
#define PWM_H

#include <avr/io.h>

void pwm_init();
void set_brightness(uint16_t duty);

#endif 