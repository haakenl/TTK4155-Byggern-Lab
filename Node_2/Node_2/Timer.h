/*
 * Timer.h
 *
 * Created: 27.10.2021 10:10:55
 *  Author: haakenl
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "sam.h"
#include "IO.h"

void Timer_init(void);
void _delay_ms(uint32_t ms);

uint32_t game_clock;

#endif /* TIMER_H_ */