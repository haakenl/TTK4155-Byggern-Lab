/*
 *pwm.c
 *
 * Created: 20.10.2021 12:33:04
 *  Author: haakenl
 */ 


#include "pwm.h"
#include "sam.h"


void pwm_init(void){
	
	/* Set up PWM */
	//PMC->PMC_SCER = PMC_SCER_PCK0 | PMC_SCER_PCK1 | PMC_SCER_PCK2;	 // Enable all programmable clocks
	PMC->PMC_PCER1 |= PMC_PCER1_PID36;								 // Enable clock on PWM Controller 
	
	// Define Pin 19 on port C as output
	PIOC->PIO_OER |= PIO_PC19;			// PIO Output enable
	PIOC->PIO_PDR |= PIO_PC19;			// P19 Configured as output (silk - PIN45)
	PIOC->PIO_ABSR |= PIO_ABSR_P19;		// Set peripheral MUX to channel B (PWM)
	
	// Setup PWM servo signal
	PWM->PWM_WPCR &= ~PIO_WPMR_WPEN;		// Disable PWM write protection
	REG_PWM_CMR5 = PWM_CMR_CPRE_MCK_DIV_1024 | PWM_CMR_CPOL;	// Set 1024 prescaler and Output wave form start high
	REG_PWM_CPRD5 = 1640;			//CPRD = 20ms * 84MHz/1024
	REG_PWM_CDTY5 = 123;			//CPRY = 1.5ms * 84MHz/1024 (min = 74/max = 172 values)
	REG_PWM_ENA = PWM_ENA_CHID5;	// Enable PWM
}


void set_servo_pos(int value){
	value = value - 38;    //offset compensating for Joystick
 	if (value < 38){	 
		value = 38;
	} 
	REG_PWM_CDTY5 = 74 + value*98/255;	 //CPRY = periode * 84MHz/1024 (min = 74/max = 172 vulues)
}
