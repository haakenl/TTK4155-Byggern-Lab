/*
 * IO.c
 *
 * Created: 10/13/2021 1:21:12 PM
 *  Author: HLunn
 */ 

#include "io.h"

void io_init(void){
	
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
	disable_encoder;
	
	// Define Pin 1 on port D as output
	PIOD -> PIO_PER |= PIO_PER_P1;		// PIO enable
	PIOD -> PIO_OER |= PIO_OER_P1;		// P19 Configured as output (!RST reset encoder (Pin4))
	disable_encoder_reset;
	
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
	// Define Pin 1 to 8 on port C as input
	PIOC -> PIO_PER |= 0x1FE;
	PIOC -> PIO_ODR |= 0x1FE;
}

