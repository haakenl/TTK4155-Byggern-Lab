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
	motor_init();
	Timer_init();
	
	
	//printf("Welcome PuTTY's\n\r");
	//set_orange_LED;
	set_green_LED;
	
	
	//game.id = 1;
	//game.data_length = 2;
	//game.data[0] = 0;
	//game.data[1] = 0;
		
	game_score = 0;
    game_ended = 1;
	//uint8_t resend_can = 0;
	//uint8_t mail_box = 0;
	
	while (1) 
    {
		if(IR_detection(300) == 1){
			while(IR_detection(1500) == 1);
			game_score = game_score + 1;
		}
		
		if(game_clock >= 600 && game_ended == 0){ //game time = 1 min
			game_ended = 1;
			
			// Send CAN message
			game.id = 1;
			game.data_length = 2;
			game.data[0] = game_score;
			game.data[1] = game_ended;
			while(can_send(&game, 0) == 1);
		}
	
		printf("score = %d\n", game_score);
		printf("Game clock = %d\n", game_clock);
		printf("Game ended = %d\n", game_ended);

    }
}

