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
#include "PWM.h"


CAN_MESSAGE test;

int main(void)
{
	/* Initialize the SAM system */
    SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS; //Disable Watchdog Timer
		
	configure_uart();
	can_init_def_tx_rx_mb(0x00290561);
	IO_Init();
	PWM_init();
	
	
	printf("Welcome PuTTY's\n\r");
	set_orange_LED;
	
	test.id = 1;
	test.data_length = 1;
	test.data[0] = 1;
	//can_send(&test, 0);
	
	set_green_LED;
	
	/* Replace with your application code */
    while (1) 
    {
		//set_servo_pos(255);
    }
}

