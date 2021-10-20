/*
 * PWM.h
 *
 * Created: 20.10.2021 12:32:38
 *  Author: haakenl
 */ 


#ifndef PWM_H_
#define PWM_H_

#include "sam.h"

void PWM_init(void);
void set_servo_pos(uint8_t value);


#endif /* PWM_H_ */