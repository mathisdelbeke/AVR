#ifndef RGB_H
#define RGB_H

#include <avr/io.h>

void rgb_init();
void pwms_init();
void timer1_init();
void timer2_init();
void set_brightness_r(uint8_t val);
void set_brightness_g(uint8_t val);
void set_brightness_b(uint8_t val);

#endif 