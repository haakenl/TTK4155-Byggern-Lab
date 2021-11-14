/*
 * Node_1.c
 *
 * Created: 01.09.2021 12:19:08
 * Author : haakenl
 */

#include "config.h"
#include "UART.h"
#include "SRAM.h"
#include "ADC.h"
#include "OLED.h"
#include "GUI.h"
#include "SPI.h"
#include "CAN.h"



int main(void)
{
	/*Indicator LED setup*/
	set_bit(LED_reg, LED_error);
	set_bit(LED_reg, LED_normal);
	
	/* Turn on set LEDS in normal "mode" */
	clear_bit(LED_port, LED_normal);
	set_bit(LED_port, LED_error);
	
	/* Enable internal pull-up on PB1 (joystick) */
	set_bit(Button_port, Button_joy_port_bit);
	set_bit(SPI_ext_port, SPI_SS_bit);
		
	/* Execute init's*/	
	_delay_ms(1000); //Wait for OLED controller to turn on.
	UART_init();
	SRAM_init();
	ADC_init();
	OLED_init();
	GUI_init();
	SPI_MasterInit();
	//CAN_init();
	errorflag = CAN_init();
	
	
	/* Print menu */
	GUI_print_menu(current_menu);
	GUI_print_arrow(0);
	
	can_message test_control;
	
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
			set_bit(LED_port, LED_normal);
			clear_bit(LED_port, LED_error);
		}
		GUI_menu();

		
	}
		return 0;
}

