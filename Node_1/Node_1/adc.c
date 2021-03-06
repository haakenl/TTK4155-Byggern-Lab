/*
 * adc.c
 *
 * Created: 08.09.2021 12:51:20
 *  Author: haakenl
 */ 

#define F_CPU 4915200
#include <util/delay.h>
#include <stdlib.h>

#include "adc.h"
#include "io.h"

/* ADC init */
void adc_init(){
	// Set timer/counter0 to PB0 (2.5MHz clock to ADC)
	set_bit(adc_clk_reg, adc_clk_pin); // Set PB0 as output
	set_bit(TCCR0,WGM01); // Set CTC Mode
	set_bit(TCCR0, COM00); // Toggle on Compare match
	set_bit(TCCR0,CS00); // Turn of prescaler 
	
	// Set initial center value for x and y on joystick
	joy_x_offset = 170;
	joy_y_offset = 170;
	joy_deadband = 60;
}	

/* ACD should be in hardwire mode */
adc_pos adc_read(){
	adc_pos return_pos;
	volatile uint8_t *ext_ADC = (uint8_t * ) 0x1400; // Start address for the ADC channels	
	ext_ADC[0] = 0;	
	//Parallel bus is set up to wait one cycle, this gives the ADC time to prepare data transfere.
	return_pos.joy_y = ext_ADC[0];
	return_pos.joy_x = ext_ADC[0];
	return_pos.slider_left = ext_ADC[0];
	return_pos.slider_right = ext_ADC[0];
	
	return return_pos;
}

/* Calibrates center position of joystick used by the menu system */
void joystick_calibrate(){
	adc_pos pos = adc_read(); //Dummy read
	double AVG_joy_x = 0;
	double AVG_joy_y = 0;
	
	for(int i = 0; i<10; i++) {	
		pos = adc_read();
		AVG_joy_x = AVG_joy_x + pos.joy_x; 
		AVG_joy_y = AVG_joy_y + pos.joy_y;
	}
	
	joy_x_offset = AVG_joy_x/10;
	joy_y_offset = AVG_joy_y/10;
}

/* Determine the location of the joystick based on its distance from the center */
adc_direction joystick_direction(){
	adc_pos pos = adc_read();
	

	int x = pos.joy_x;
	int y = pos.joy_y;
	
	if(abs(y-joy_y_offset) > joy_deadband){
		if(y-joy_y_offset < 0){
			return DOWN;
		}
		else{
			return UP;
		}
	}
	else if(abs(x-joy_x_offset) > joy_deadband){
		if(x-joy_x_offset < 0){
			return LEFT;	
		}
		else{
			return RIGHT;
		}
	}
	else{
		return NEUTRAL;
	}
}


adc_direction debounce_joystick_direction(){
		adc_direction current_direction;
		adc_direction debounce_direction;
		
		current_direction = joystick_direction();
		_delay_ms(100);
		debounce_direction = joystick_direction();
		
		if (current_direction == debounce_direction){
			return current_direction;
		}
		else{
			return NEUTRAL;
		}		
}

unsigned int adc_to_prosent(unsigned int value){
	return value*100/255;
}
