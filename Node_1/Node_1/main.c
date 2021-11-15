/*
 * Node_1.c
 *
 * Created: 01.09.2021 12:19:08
 * Author : haakenl
 */

#define F_CPU 4915200
#include <avr/io.h>
#include <util/delay.h>

#include "io.h"
#include "uart.h"
#include "sram.h"
#include "adc.h"
#include "oled.h"
#include "gui.h"
#include "spi.h"
#include "can.h"

uint8_t errorflag;


int main(void)
{	
	_delay_ms(1000); //Wait for OLED controller to turn on.	
	
	/* Execute init's*/	
	io_init();
	uart_init();
	sram_init();
	adc_init();
	oled_init();
	gui_init();
	spi_master_init();
	errorflag = can_init();
	
	
	/* Print menu */
	gui_print_menu(current_menu);
	gui_print_arrow(0);
	
	//can_message test_control;
	
	while(1){
		/*
		clear_bit(LED_port, LED_error);
		_delay_ms(1000);
		set_bit(LED_port, LED_error);
		_delay_ms(1000);
		*/
		
		/*
		ADC_pos joystick_pos = ADC_read();
		ADC_direction direction;
		printf("\n");
		printf("ADC Ch1 read (joystick y-axis) %4d\n", ADC_to_prosent(joystick_pos.joy_x));
		printf("ADC Ch2 read (joystick x-axis) %4d\n", ADC_to_prosent(joystick_pos.joy_x));
		printf("ADC Ch3 read (right slider) %4d\n", ADC_to_prosent(joystick_pos.slider_right));
		printf("ADC Ch4 read (left slider) %4d\n", ADC_to_prosent(joystick_pos.slider_left));
		printf("Direction: %x\n", joystick_direction());
		_delay_ms(1000);
		*/
		
		/* Check error flag*/
		//if(test_bit(CAN_int_flag_reg, CAN_int_flag_bit) == 0){
		//CAN_mailbox();
		//if(CAN_mailbox_0_recive_flag == 1){
			//test_control = CAN_message_receive(0);
			//printf("mail 0 id %d\n", test_control.id);
			//printf("mail 0 length %d\n", test_control.data_length);
			//printf("mail 0 data 0 %d\n", test_control.data[0]);
			//printf("mail 0 data 1 %d\n", test_control.data[1]);
		//}
		//
		//if(CAN_mailbox_1_recive_flag == 1){
			//game_ended = CAN_message_receive(1);
			//printf("mail 1 id %d\n", test_control.id);
			//printf("mail 1 length %d\n", test_control.data_length);
			//printf("mail 1 data 0 %d\n", test_control.data[0]);
			//printf("mail 1 data 1 %d\n", test_control.data[1]);
			//}
		//}
			
		if(errorflag == 1){
			set_bit(led_port, led_normal);
			clear_bit(led_port, led_error);
		}
		gui_menu();

		
	}
		return 0;
}

