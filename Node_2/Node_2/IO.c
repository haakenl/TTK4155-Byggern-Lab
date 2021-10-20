/*
 * IO.c
 *
 * Created: 10/13/2021 1:21:12 PM
 *  Author: HLunn
 */ 

#include "IO.h"

void IO_Init(void){
	
	PIOC -> PIO_WPMR &= ~PIO_WPMR_WPEN;	// Disable IO Write protection
	
	/* Set up LEDS */
	PMC->PMC_PCER0 |= PMC_PCER0_PID11;  // Enable peripheral clock for PIOA

	// Define Pin 19 on port A as output
	PIOA -> PIO_PER |= PIO_PER_P19;		// PIO Output enable
	PIOA -> PIO_OER |= PIO_OER_P19;		// P19 Configured as output (D1)

	// Define Pin 19 on port A as output
	PIOA -> PIO_PER |= PIO_PER_P20;		// PIO Output enable
	PIOA -> PIO_OER |= PIO_OER_P20;		// P19 Configured as output (D2)
}

