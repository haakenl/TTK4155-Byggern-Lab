/*
 * OLED.c
 *
 * Created: 22.09.2021 10:55:44
 *  Author: Haakenl
 */ 

#include "OLED.h"
#include "fonts.h"


void OLED_write_command(char  command){
	volatile char *OLED_write = (char *) 0x1000;
	*OLED_write = command; // Removed [0] from OLED_write
}

void OLED_write_data(char data){
	volatile char *OLED_write = (char *) 0x1200;
	*OLED_write = data; // Removed [0] from OLED_write
}

void OLED_init(){
	// Cited datasheet OLED controller 22.09.21
	OLED_write_command(0xae); // display off
	OLED_write_command(0xa1); // segment remap
	OLED_write_command(0xda); // common pads hardware: alternative
	OLED_write_command(0x12);
	OLED_write_command(0xc8); // common output scan direction:com63~com0
	OLED_write_command(0xa8); // multiplex ration mode:63
	OLED_write_command(0x3f);
	OLED_write_command(0xd5); // display divide ratio/osc. freq. mode
	OLED_write_command(0x80);
	OLED_write_command(0x81); // contrast control
	OLED_write_command(0x50);
	OLED_write_command(0xd9); // set pre-charge period
	OLED_write_command(0x21);
	OLED_write_command(0x20); // Set Memory Addressing Mode
	OLED_write_command(0x02);
	OLED_write_command(0xdb); // VCOM deselect level mode
	OLED_write_command(0x30);
	OLED_write_command(0xad); // master configuration
	OLED_write_command(0x00);
	OLED_write_command(0xa4); // out follows RAM content
	OLED_write_command(0xa6); // set normal display
	OLED_write_command(0xaf); // display on
}

void OLED_print(char c){
	for(uint8_t i = 0; i < font_size; i++){
		OLED_write_data(pgm_read_byte(&font5[c - 32][i]));
	}
}

void OLED_printf(char str[]){
	for(int i = 0; i < strlen(str); i++){
		OLED_print(str[i]);
	}
}

void OLED_pos(uint8_t page, uint8_t seg){
	// Cited lauritsriple
	//Go to page
	OLED_write_command(page | (0xb0));
	// Go to segment
	OLED_write_command(seg & 0x0f);
	OLED_write_command(((seg & 0xf0) >> 4) | (0x10));
}

void OLED_clear_line(uint8_t line){
	OLED_pos(line, 0);
	for (uint8_t i = 0; i < 128; i++){
		OLED_write_data(0x0);
	}
}

void OLED_clear_arrow(void){
	OLED_pos(0,0);
	for (uint8_t j = 0; j < 8; j++){
		OLED_pos(j,0);
		for (uint8_t i = 0; i < 15; i++){
			OLED_write_data(0x0);
		}
	}
}

void OLED_clear_all(){
		OLED_pos(0,0);
		for (uint8_t j = 0; j < 8; j++){
			OLED_pos(j,0);
			for (uint8_t i = 0; i < 128; i++){
				OLED_write_data(0x0);
			}
		}
}


