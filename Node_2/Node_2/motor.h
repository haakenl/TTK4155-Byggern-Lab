/*
 * motor.h
 *
 * Created: 27.10.2021 15:46:08
 *  Author: haakenl
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include "sam.h"
#include "Timer.h"
#include "IO.h"
#include "Analog_IO.h"
#include "stdlib.h"


void motor_init(void);
int16_t read_encoder(void);
void set_motor_speed(int16_t speed_and_direction);
void reset_encoder(void);
void update_pos_ref(uint16_t ref_pos);
void PID_regulator(void);
 

typedef struct{
	float Kp;
	float Ki;
	float Kd;
	float dt;
	float error;
	float error_i;
	float pos;
	float pos_ref;
	float output;
	}PID_struct;

int16_t encoder_range;
PID_struct PID;

#endif /* MOTOR_H_ */