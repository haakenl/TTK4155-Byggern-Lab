/*
 * motor.h
 *
 * Created: 27.10.2021 15:46:08
 *  Author: haakenl
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include "sam.h"



void motor_init(void);
int16_t read_encoder(void);
void set_motor_speed(int16_t speed_and_direction);
void reset_encoder(void);
void update_pos_ref(int16_t ref_pos);
void pid_regulator(void);
 

typedef struct{
	float kp;
	float ki;
	float kd;
	float dt;
	float error;
	float error_i;
	float pos;
	float pos_ref;
	float output;
	}pid_struct;

int16_t encoder_range;
pid_struct pid;

#endif /* MOTOR_H_ */