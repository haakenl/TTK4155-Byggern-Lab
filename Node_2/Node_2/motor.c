/*
 * motor.c
 *
 * Created: 27.10.2021 15:47:08
 *  Author: haakenl
 */ 

#include "stdlib.h"
#include "motor.h"
#include "timer.h"
#include "io.h"
#include "analog_io.h"

/* Setup motor reset the encoder, reads encoder range and set PI parameters */
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
	pid.pos_ref = encoder_range/2;
	pid.kp = 0.35;
	pid.ki = pid.kp/40; 			
}
	
/* Read encoder */	
int16_t read_encoder(void){
	int16_t pos_and_direction = 0;
	enable_encoder;
	sel_MSB_encoder;	
	_delay_us(20);
	pos_and_direction |= ((read_encoder_mask >> 1) << 8);
	sel_LSB_encoder;
	_delay_us(20);
	pos_and_direction |= (read_encoder_mask >> 1);
	disable_encoder;	
	return pos_and_direction;
}

/* Reset encoder */
void reset_encoder(void){
	enable_encoder;
	enable_encoder_reset;
	_delay_us(10);
	disable_encoder_reset;
	disable_encoder;
}

/* Update motor speed and direction */
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

/* Update PID reference based on 8-bit unsigned value */
void update_pos_ref(int16_t ref_pos){
	ref_pos = ref_pos - 38;    //offset compensating for Joystick
	if (ref_pos < 38){
		ref_pos = 38;
	}
	pid.pos_ref = (encoder_range/2)-(ref_pos-115)*100;
}

/* Updates PID regulator this function needs to be run every 10mS */
void pid_regulator(void){
	pid.pos = read_encoder();
		
	if (pid.pos < 0){
		pid.pos = 0;
	}
	if(pid.pos > encoder_range){
		pid.pos = encoder_range; 
	}
	
	if(pid.pos_ref < 0){
		pid.pos_ref = 0;
	}
	
	if(pid.pos_ref > encoder_range){
		pid.pos_ref = encoder_range; 
	}
	
	
	pid.error = pid.pos_ref - pid.pos;
	
	if(abs(pid.error) < 500){
		pid.error_i = 0;
	}
	else{
		pid.error_i = pid.error_i + pid.error;
	}
		
	pid.output = pid.error*pid.kp + pid.error_i*pid.ki;
	
	set_motor_speed((int16_t)pid.output);
}