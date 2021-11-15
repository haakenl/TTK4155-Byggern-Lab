/*
 * Timer.h
 *
 * Created: 27.10.2021 10:10:55
 *  Author: haakenl
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "sam.h"

void timer_init(void);
void _delay_ms(uint32_t ms);
void _delay_us(uint32_t us);

volatile uint16_t game_clock;
volatile uint8_t TC0_flag;

#endif /* TIMER_H_ */