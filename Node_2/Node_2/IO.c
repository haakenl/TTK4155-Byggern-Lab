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
	PIOA -> PIO_PER |= PIO_PER_P19;		// PIO enable
	PIOA -> PIO_OER |= PIO_OER_P19;		// P19 Configured as output (D1)
	// Define Pin 19 on port A as output
	PIOA -> PIO_PER |= PIO_PER_P20;		// PIO enable
	PIOA -> PIO_OER |= PIO_OER_P20;		// P20 Configured as output (D2)
	
	
	/* Set up Solenoid */
	PIOC -> PIO_WPMR &= ~PIO_WPMR_WPEN; // Disable IO Write protection PIOC
	PMC->PMC_PCER0 |= PMC_PCER0_PID13;  // Enable peripheral clock for PIOC	
	// Define Pin 19 on port A as output
	PIOC -> PIO_PER |= PIO_PER_P12;		// PIO enable
	PIOC -> PIO_OER |= PIO_OER_P12;		// P19 Configured as output (D1)
	deactivate_solenoid;
	
	
	/* Set up MJ1 */
	PIOD -> PIO_WPMR &= ~PIO_WPMR_WPEN;	// Disable IO Write protection PIOD
	PMC->PMC_PCER0 |= PMC_PCER0_PID14;  // Enable peripheral clock for PIOD
	// Define Pin 0 on port D as output
	PIOD -> PIO_PER |= PIO_PER_P0;		// PIO enable
	PIOD -> PIO_OER |= PIO_OER_P0;		// P19 Configured as output (!OE enable encoder (Pin3))
	// Define Pin 1 on port D as output
	PIOD -> PIO_PER |= PIO_PER_P1;		// PIO enable
	PIOD -> PIO_OER |= PIO_OER_P1;		// P19 Configured as output (!RST reset encoder (Pin4))
	// Define Pin 2 on port D as output
	PIOD -> PIO_PER |= PIO_PER_P2;		// PIO enable
	PIOD -> PIO_OER |= PIO_OER_P2;		// P19 Configured as output (SEL High/low byte select encoder (pin5))
	// Define Pin 9 on port D as output
	PIOD -> PIO_PER |= PIO_PER_P9;		// PIO enable
	PIOD -> PIO_OER |= PIO_OER_P9;		// P19 Configured as output (EN Enables motor (pin6))
	// Define Pin 10 on port D as output
	PIOD -> PIO_PER |= PIO_PER_P10;		// PIO enable
	PIOD -> PIO_OER |= PIO_OER_P10;		// P19 Configured as output (DIR Set motor direction (Pin7))
	
	
	
	/* Set up MJ2 */
	// Define Pin 1 on port C as input
	PIOC -> PIO_PER |= PIO_PER_P1;		// PIO enable (D0 (Pin3))
	PIOC -> PIO_ODR |= PIO_ODR_P1;		// P1 Configured disabled as output
	// Define Pin 2 on port C as input
	PIOC -> PIO_PER |= PIO_PER_P2;		// PIO enable (D1 (Pin4))
	PIOC -> PIO_ODR |= PIO_ODR_P2;		// P1 Configured disabled as output
	// Define Pin 3 on port C as input
	PIOC -> PIO_PER |= PIO_PER_P3;		// PIO enable (D2 (Pin5))
	PIOC -> PIO_ODR |= PIO_ODR_P3;		// P1 Configured disabled as output
	// Define Pin 4 on port C as input
	PIOC -> PIO_PER |= PIO_PER_P4;		// PIO enable (D3 (Pin6))
	PIOC -> PIO_ODR |= PIO_ODR_P4;		// P1 Configured disabled as output
	// Define Pin 5 on port C as input
	PIOC -> PIO_PER |= PIO_PER_P5;		// PIO enable (D4 (Pin7))
	PIOC -> PIO_ODR |= PIO_ODR_P5;		// P1 Configured disabled as output 
	// Define Pin 6 on port C as input
	PIOC -> PIO_PER |= PIO_PER_P6;		// PIO enable (D5 (Pin8))
	PIOC -> PIO_ODR |= PIO_ODR_P6;		// P1 Configured disabled as output 
	// Define Pin 7 on port C as input
	PIOC -> PIO_PER |= PIO_PER_P7;		// PIO enable (D6 (Pin9))
	PIOC -> PIO_ODR |= PIO_ODR_P7;		// P1 Configured disabled as output
	// Define Pin 8 on port C as input
	PIOC -> PIO_PER |= PIO_PER_P8;		// PIO enable (D7 (Pin10))
	PIOC -> PIO_ODR |= PIO_ODR_P8;		// P1 Configured disabled as output
}

