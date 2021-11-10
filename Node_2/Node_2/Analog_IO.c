/*
 * Analog_IO.c
 *
 * Created: 23.10.2021 11:45:33
 *  Author: haakenl
 */ 

#include "Analog_IO.h"
#include "Timer.h"

void Analog_IO_init(void){
	/* Set up IR detection ADC */
	ADC -> ADC_WPMR &= ~ADC_WPMR_WPEN;		// Disable ADC Write protection 
	PMC -> PMC_PCER1 |= PMC_PCER1_PID37;	// Enable peripheral clock for ADC

	// Define ADC7 on port A PIN 16
	ADC -> ADC_MR = ADC_MR_FREERUN | ADC_MR_PRESCAL(255);		// ADC set to Freerun mode, default single ended mode and prescaler
 	ADC -> ADC_CHER |= ADC_CHER_CH7;		// Enables channel 7
	ADC -> ADC_CR |= ADC_CR_START;			// Begins analog-to-digital conversion
	
	/*Spørr studass om hvordan vi kan bruke adc til å til å trigge et flag isteden for */
	//ADC -> ADC_IER |= ADC_IER_COMPE;		// Enables channel 7
	//ADC -> ADC_EMR = ADC_EMR_CMPMODE_LOW| ADC_EMR_CMPSEL(7) | ADC_EMR_CMPFILTER(5); 
	//ADC -> ADC_CWR = ADC_CWR_LOWTHRES(800); 	

	/* Set up motor DAC (MJEX) */
	DACC -> DACC_WPMR &= ~ DACC_WPMR_WPEN;	// Disable DAC Write protection 
	PMC -> PMC_PCER1 |= PMC_PCER1_PID38;	// Enable peripheral clock for DAC
	
	// Define DAC1 on port B PIN 16
	DACC -> DACC_MR |= DACC_MR_USER_SEL_CHANNEL1;	// Selects channel 1
	DACC -> DACC_CHER |= DACC_CHER_CH1;				// Enables channel 1
	DACC -> DACC_CDR = 0;							// Set initial value to zero.
}

//void ADC_Handler(void){
//	game_score = game_score + 1;
//	set_green_LED;
//}

uint8_t IR_detection(uint16_t threshold){
	//uint8_t ir_blocked = 0;
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