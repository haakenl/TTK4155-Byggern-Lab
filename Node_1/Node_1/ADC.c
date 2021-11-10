/*
 * ADC.c
 *
 * Created: 08.09.2021 12:51:20
 *  Author: haakenl
 */ 

#include "ADC.h"

void ADC_init(){
	// Set timer/counter0 to PD0 (2.5MHz clock to ADC)
	set_bit(DDRB, PB0); // Set PB0 as output
	set_bit(TCCR0,WGM01); // Set CTC Mode
	set_bit(TCCR0, COM00); // Toggle on Compare match
	set_bit(TCCR0,CS00); // Turn of prescaler 
	
	// Set initial center value for x and y on joystick
	joy_x_offset = 170;
	joy_y_offset = 170;
	joy_deadband = 60;
}	

// Should read current position values for joystick with values from 0-255
ADC_pos ADC_read(){
	ADC_pos return_pos;
	volatile uint8_t *ext_ADC = (uint8_t * ) 0x1400; // Start address for the ADC channels	
	ext_ADC[0] = 0;	
	//Parralell bus is set up to wait one cycle  //Bør byttes med while og interrupt flag. (busy sig) vis nødvendig
	return_pos.joy_y = ext_ADC[0];
	return_pos.joy_x = ext_ADC[0];
	return_pos.slider_left = ext_ADC[0];
	return_pos.slider_right = ext_ADC[0];
	
	return return_pos;
}

void joystick_calibrate(){
	ADC_pos pos = ADC_read(); //Dummy read
	double AVG_joy_x;
	double AVG_joy_y;
	
	for(int i = 0; i<10; i++) {	
		pos = ADC_read();
		AVG_joy_x = AVG_joy_x + pos.joy_x; 
		AVG_joy_y = AVG_joy_y + pos.joy_y;
	}
	
	joy_x_offset = AVG_joy_x/10;
	joy_y_offset = AVG_joy_y/10;
}

/* Determine the location of the joystick based on its distance from the center */
ADC_direction joystick_direction(){
	ADC_pos pos = ADC_read();
	

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


ADC_direction debounce_joystick_direction(){
		ADC_direction current_direction;
		ADC_direction debounce_direction;
		
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

unsigned int ADC_to_prosent(unsigned int value){
	return value*100/255;
}
