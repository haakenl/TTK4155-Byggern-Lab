/*
 * analog_io.c
 *
 * Created: 23.10.2021 11:45:33
 *  Author: haakenl
 */ 

#include "analog_io.h"
#include "timer.h"


void analog_io_init(void){
	/* Set up IR detection ADC */
	ADC -> ADC_WPMR &= ~ADC_WPMR_WPEN;		// Disable ADC Write protection 
	PMC -> PMC_PCER1 |= PMC_PCER1_PID37;	// Enable peripheral clock for ADC

	// Define ADC7 on port A PIN 16
	ADC -> ADC_MR = ADC_MR_FREERUN | ADC_MR_PRESCAL(255);		// ADC set to Freerun mode, default single ended mode and prescaler
 	ADC -> ADC_CHER |= ADC_CHER_CH7;		// Enables channel 7
	ADC -> ADC_CR |= ADC_CR_START;			// Begins analog-to-digital conversion

	/* Set up motor DAC (MJEX) */
	DACC -> DACC_WPMR &= ~ DACC_WPMR_WPEN;	// Disable DAC Write protection 
	PMC -> PMC_PCER1 |= PMC_PCER1_PID38;	// Enable peripheral clock for DAC
	
	// Define DAC1 on port B PIN 16
	DACC -> DACC_MR |= DACC_MR_USER_SEL_CHANNEL1;	// Selects channel 1
	DACC -> DACC_CHER |= DACC_CHER_CH1;				// Enables channel 1
	DACC -> DACC_CDR = 0;							// Set initial value to zero.
}

uint8_t ir_detection(uint16_t threshold){
	if(Read_IR_VALUE < threshold){
		return 1;
	}
	return 0;
}
			

void set_analog_value(uint16_t value){
	if(value > 4095){
		value = 4095;
	}
	DACC -> DACC_CDR = value;//*4095/100;	 
}
