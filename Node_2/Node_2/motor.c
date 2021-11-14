/*
 * motor.c
 *
 * Created: 27.10.2021 15:47:08
 *  Author: haakenl
 */ 

#include "motor.h"

void motor_init(void){
	enable_motor;
	set_motor_speed(-2000);
	_delay_ms(1000);
	reset_encoder();
	_delay_ms(200);
	set_motor_speed(2000);
	_delay_ms(1000);	
	encoder_range = read_encoder();
	set_motor_speed(0);	
	PID.pos_ref = encoder_range/2;
	PID.Kp = 0.35;
	PID.Ki = PID.Kp/40; 
			
	}
	
	
int16_t read_encoder(void){
	int16_t pos_and_direction = 0;
	enable_encoder;
	sel_MSB_encoder;	
	_delay_us(20);
	pos_and_direction |= ((read_encoder_mask >> 1) << 8);
	sel_LSB_encoder;
	_delay_us(20);
	pos_and_direction |= (read_encoder_mask >> 1);
	//enable_encoder_reset
	//_delay_us(10);
	//disable_encoder_reset;
	disable_encoder;	
	return pos_and_direction;
}


void reset_encoder(void){
	enable_encoder;
	enable_encoder_reset;
	_delay_us(10);
	disable_encoder_reset;
	disable_encoder;
}


void set_motor_speed(int16_t speed_and_direction){
	if (speed_and_direction < 0){
		set_neg_motor_dir;
		set_analog_value(abs(speed_and_direction));
	}
	else{
		set_pos_motor_dir;		
		set_analog_value(abs(speed_and_direction));
	}
}

void update_pos_ref(int16_t ref_pos){
	ref_pos = ref_pos - 38;    //offset compensating for Joystick
	if (ref_pos < 38){
		ref_pos = 38;
	}
	PID.pos_ref = (encoder_range/2)-(ref_pos-115)*100;
}


void PID_regulator(void){
	PID.pos = read_encoder();
		
	if (PID.pos < 0){
		PID.pos = 0;
	}
	if(PID.pos > encoder_range){
		PID.pos = encoder_range; 
	}
	
	if(PID.pos_ref < 0){
		PID.pos_ref = 0;
	}
	
	if(PID.pos_ref > encoder_range){
		PID.pos_ref = encoder_range; 
	}
	
	PID.error = PID.pos_ref - PID.pos;
	
	if(abs(PID.error) < 500){
		PID.error_i = 0;
	}
	else{
		PID.error_i = PID.error_i + PID.error;
	}
	
	PID.output = PID.error*PID.Kp + PID.error_i*PID.Ki;
	
	set_motor_speed((int16_t)PID.output);
}