/*
 * ADC.h
 *
 * Created: 08.09.2021 12:51:33
 *  Author: haakenl
 */ 


#ifndef ADC_H_
#define ADC_H_



uint8_t joy_x_offset;
uint8_t joy_y_offset;
uint8_t joy_deadband;

typedef struct {
	unsigned int joy_x;
	unsigned int joy_y;
	unsigned int slider_left;
	unsigned int slider_right;
} adc_pos;

typedef enum {LEFT, RIGHT, UP, DOWN, NEUTRAL} adc_direction;


void adc_init();
void joystick_calibrate();

adc_pos adc_read();
adc_direction joystick_direction();
adc_direction debounce_joystick_direction();
unsigned int adc_to_prosent(unsigned int value);


#endif /* ADC_H_ */


