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
	parallel_bus_init();
	adc_init();
	oled_init();
	gui_init();
	spi_master_init();
	errorflag = can_init();
	
	
	/* Print main menu */
	gui_print_menu(current_menu);
	gui_print_arrow(0);
	

	while(1){
		/* Check if errorflag is set */			
		if(errorflag == 1){
			set_bit(led_port, led_normal);
			clear_bit(led_port, led_error);
		}
		
		gui_menu();
		
	}
		return 0;
}

