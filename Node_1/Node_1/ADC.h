/*
 * ADC.h
 *
 * Created: 08.09.2021 12:51:33
 *  Author: haakenl
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "config.h"



// Global variabels:
uint8_t joy_x_offset;
uint8_t joy_y_offset;
uint8_t joy_deadband;

typedef struct {
	unsigned int joy_x;
	unsigned int joy_y;
	unsigned int slider_left;
	unsigned int slider_right;
} ADC_pos;

typedef enum {LEFT, RIGHT, UP, DOWN, NEUTRAL} ADC_direction;


void ADC_init();
void joystick_calibrate();

ADC_pos ADC_read();
ADC_direction joystick_direction();
ADC_direction debounce_joystick_direction();
unsigned int ADC_to_prosent(unsigned int value);


#endif /* ADC_H_ */


