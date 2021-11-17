/*
 * Node_2.c
 *
 * Created: 10/9/2021 1:10:26 PM
 * Author : HLunn
 */ 


#include "sam.h"
#include "uart_and_printf/uart.h"
#include "uart_and_printf/printf_stdarg.h"
#include "can/can_controller.h"
#include "io.h"
#include "analog_io.h"
#include "pwm.h"
#include "motor.h"
#include "timer.h"




int main(void)
{
	/* Initialize the SAM system */
    SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer
	
	/* Initialized node 2 */	
	configure_uart();
	can_init_def_tx_rx_mb(0x00290165);		//see can config sheet on github
	io_init();
	analog_io_init();
	pwm_init();
	motor_init();
	timer_init();
	
	
	//printf("Welcome PuTTY's\n\r");
	//set_orange_LED;
	set_green_LED;
	
	/* Set node 2 in waiting mode */
	game_score = 0;
	game_run = 0;
	
	/* Send initial CAN message with game play */
	game.id = 1;
	game.data_length = 2;
	game.data[0] = game_score;
	game.data[1] = game_run;
	while(can_send(&game, 0) == 0);

	
	while (1) 
    {
		/* Check if there is any goals */
		if(ir_detection(300) == 1){
			while(ir_detection(1500) == 1);
			game_score = game_score + 1;
		}
		
		/* Check game clock and if there is any games ongoing */
		if(game_clock >= 6000 && game_run == 1){ //game time = 60 sek
			game_run = 0;
			//for(uint8_t i  = 0; i < 10; i++){
				
			/* Send CAN message */
			game.id = 1;
			game.data_length = 2;
			game.data[0] = game_score;
			game.data[1] = game_run;			
			while(can_send(&game, 0) == 0);
			set_servo_pos(160);
			update_pos_ref(160);
		}
    }
}

