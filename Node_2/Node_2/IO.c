/*
 * IO.c
 *
 * Created: 10/13/2021 1:21:12 PM
 *  Author: HLunn
 */ 

#include "IO.h"

void IO_Init(void){
	
	/* Set up LEDS */
	PIOA -> PIO_WPMR &= ~PIO_WPMR_WPEN;	// Disable IO Write protection PIOA
	PMC->PMC_PCER0 |= PMC_PCER0_PID11;  // Enable peripheral clock for PIOA

	// Define Pin 19 on port A as output
	PIOA -> PIO_PER |= PIO_PER_P19;		// PIO Output enable
	PIOA -> PIO_OER |= PIO_OER_P19;		// P19 Configured as output (D1)

	// Define Pin 19 on port A as output
	PIOA -> PIO_PER |= PIO_PER_P20;		// PIO Output enable
	PIOA -> PIO_OER |= PIO_OER_P20;		// P20 Configured as output (D2)
	
	
	/* Set up Solenoid */
	PIOC -> PIO_WPMR &= ~PIO_WPMR_WPEN; // Disable IO Write protection PIOC
	PMC->PMC_PCER0 |= PMC_PCER0_PID13;  // Enable peripheral clock for PIOC
	
	// Define Pin 19 on port A as output
	PIOC -> PIO_PER |= PIO_PER_P12;		// PIO Output enable
	PIOC -> PIO_OER |= PIO_OER_P12;		// P19 Configured as output (D1)
	deactivate_solenoid;
}

