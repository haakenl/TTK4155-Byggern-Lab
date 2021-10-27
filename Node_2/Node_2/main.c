/*
 * Node_2.c
 *
 * Created: 10/9/2021 1:10:26 PM
 * Author : HLunn
 */ 

#include <stdio.h>
#include <stdarg.h>
#include "sam.h"
#include "uart_and_printf/uart.h"
#include "uart_and_printf/printf_stdarg.h"
#include "can/can_controller.h"
#include "IO.h"
#include "Analog_IO.h"
#include "PWM.h"
#include "Timer.h"


CAN_MESSAGE game_over;




int main(void)
{
	/* Initialize the SAM system */
    SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer
		
	configure_uart();
	//can_init_def_tx_rx_mb(0x00290561);
	can_init_def_tx_rx_mb(0x00290165);		//see can config sheet on github
	IO_Init();
	Analog_IO_init();
	PWM_init();
	Timer_init();
	
	
	//printf("Welcome PuTTY's\n\r");
	//set_orange_LED;
	
	game_over.id = 1;
	game_over.data_length = 1;
	game_over.data[0] = 0;
	//set_green_LED;
	
	
    while (1) 
    {
		clear_green_LED;
		if(Read_IR_VALUE < 100){
			set_green_LED;
			//can_send(&game_over, 0);
			while(Read_IR_VALUE < 500);
		}
		
		
		if((PIOC->PIO_PDSR & PIO_PDSR_P1) == 1){
		set_orange_LED;	
		}
		clear_orange_LED;
		
		
		//_delay_ms(1000);|
		//set_orange_LED
		//_delay_ms(1000);
		//clear_orange_LED;
		

    }
}
#define read_pin(port, pin) (port->PIO_PDSR & pin)

