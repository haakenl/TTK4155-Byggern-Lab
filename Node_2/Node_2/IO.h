/*
 * IO.h
 *
 * Created: 10/13/2021 1:20:51 PM
 *  Author: HLunn
 */ 


#ifndef IO_H_
#define IO_H_

#include "sam.h"

#define set_orange_LED PIOA -> PIO_SODR |= PIO_SODR_P19;	// Set P19 (D1)
#define clear_orange_LED PIOA -> PIO_CODR |= PIO_SODR_P19;	// Clear P19 (D1)

#define set_green_LED	PIOA -> PIO_SODR |= PIO_SODR_P20;	// Set P20 (D2)
#define clear_green_LED PIOA -> PIO_CODR |= PIO_SODR_P20;	// Clear P20 (D3)

#define deactivate_solenoid	PIOC -> PIO_SODR |= PIO_SODR_P12;	// Set P12 (solenoid)
#define activate_solenoid PIOC -> PIO_CODR |= PIO_SODR_P12;		// Clear P12 (solenoid)


void IO_Init(void);

#endif /* IO_H_ */