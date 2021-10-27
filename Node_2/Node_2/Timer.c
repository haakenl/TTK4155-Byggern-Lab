/*
 * Timer.c
 *
 * Created: 27.10.2021 10:11:14
 *  Author: haakenl
 */ 

#include "Timer.h"

void _delay_ms(uint32_t ms) //NB max value is 1597ms 
{
	SysTick->LOAD = 10.5e3 * ms; //MCK = 10.5MHz 
	SysTick->CTRL = SysTick_CTRL_ENABLE_Msk; // Enable SysTick
	while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)); // Wait until Systick timer is finished
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; // Disable SysTick
}

void Timer_init(void){
									 
	/* Setup Timer 0 */
	PMC->PMC_PCER0 |= PMC_PCER0_PID27;		// Enable clock on TC0
	TC0->TC_WPMR &= ~TC_WPMR_WPEN;			// Disable TC write protection
	REG_TC0_CMR0 |= TC_CMR_TCCLKS_TIMER_CLOCK3 | TC_CMR_ENETRG;		// Set 32 prescaler and resets on compare match
	REG_TC0_IER0 |= TC_IER_CPCS;	// Enable interrupt on compare match
	REG_TC0_RC0 = 2625;				// counts = 1ms/(32/MCK)
	
	NVIC_EnableIRQ(TC0_IRQn);		// Enable timer counter interrupt
	REG_TC0_CCR0 |= TC_CCR_CLKEN|TC_CCR_SWTRG;		// Enable Timer 0
	game_clock = 0;
}

void TC0_Handler(void){

	uint32_t SR0_flag = REG_TC0_SR0;  // Interrupt flag is cleared by reading  
	REG_TC0_CCR0 |= TC_CCR_SWTRG;	  // Enable Timer 0

	game_clock ++;
	
	//if (game_clock == 1e3){
	//	set_orange_LED;
	//	game_clock = 0;
	//}	
}
