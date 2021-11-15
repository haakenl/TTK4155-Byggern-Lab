/*
 * IO.c
 *
 * Created: 23.10.2021 15:18:19
 *  Author: haakenl
 */ 

#include "io.h"

void io_init(void){
		/*Indicator LED setup*/
		set_bit(led_reg, led_error);
		set_bit(led_reg, led_normal);
		
		/* Turn on set LEDS in normal "mode" */
		clear_bit(led_port, led_normal);
		set_bit(led_port, led_error);
		
		/* Enable internal pull-up on PB1 (joystick) */
		set_bit(button_port, button_joy_port_bit);
		set_bit(spi_ext_port, spi_ss_bit);
	};
	

