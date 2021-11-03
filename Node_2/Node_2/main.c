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
#include "motor.h"


CAN_MESSAGE game_over;


int main(void)
{
	/* Initialize the SAM system */
    SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer
		
	configure_uart();
	can_init_def_tx_rx_mb(0x00290165);		//see can config sheet on github
	IO_Init();
	Analog_IO_init();
	PWM_init();
	Timer_init();
	motor_init();
	
	
	//printf("Welcome PuTTY's\n\r");
	//set_orange_LED;
	
	game_over.id = 1;
	game_over.data_length = 1;
	game_over.data[0] = 0;
	//set_green_LED;
	
	
	game_score = 0;
    while (1) 
    {
		if(IR_detection() == 1){
			game_score = game_score + 1;
			printf("score = %d\n", game_score);
			//while(IR_detection() == 1);
		}
		
		
		//if(game_clock == 60000){
			//game_over.data[0] = game_score;
			//can_send(game_over, 1);
		//}
		
		
		
		if(TC0_flag == 1){
			TC0_flag  == 0;
			PID_regulator();	
		}
		
		
		//_delay_ms(1000);
		//printf("score = %d\n", game_score);
	
	
		//_delay_ms(1000);
		//test = read_encoder();	
		//printf("test %d\n",test);
		//printf("encoder range %d\n", encoder_range);
    }
}

