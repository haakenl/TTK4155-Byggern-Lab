/*
 * oled.c
 *
 * Created: 22.09.2021 10:55:44
 *  Author: Haakenl
 */ 

#include <string.h>
#include "oled.h"
#include "fonts.h"

/* Send OLED command on the parallel bus */
void oled_write_command(char  command){
	volatile char *OLED_write = (char *) 0x1000;
	*OLED_write = command; // Removed [0] from OLED_write
}

/* Send OLED data on the parallel bus */
void oled_write_data(char data){
	volatile char *OLED_write = (char *) 0x1200;
	*OLED_write = data; // Removed [0] from OLED_write
}

/* OLED init. Cited OLED controller data sheet 22.09.21 */
void oled_init(){
	oled_write_command(0xae); // display off
	oled_write_command(0xa1); // segment remap
	oled_write_command(0xda); // common pads hardware: alternative
	oled_write_command(0x12);
	oled_write_command(0xc8); // common output scan direction:com63~com0
	oled_write_command(0xa8); // multiplex ration mode:63
	oled_write_command(0x3f);
	oled_write_command(0xd5); // display divide ratio/osc. freq. mode
	oled_write_command(0x80);
	oled_write_command(0x81); // contrast control
	oled_write_command(0x50);
	oled_write_command(0xd9); // set pre-charge period
	oled_write_command(0x21);
	oled_write_command(0x20); // Set Memory Addressing Mode
	oled_write_command(0x02);
	oled_write_command(0xdb); // VCOM deselect level mode
	oled_write_command(0x30);
	oled_write_command(0xad); // master configuration
	oled_write_command(0x00);
	oled_write_command(0xa4); // out follows RAM content
	oled_write_command(0xa6); // set normal display
	oled_write_command(0xaf); // display on
}

/* Prints characters to OLED form font 5 ascii table */
void oled_print(char c){
	for(uint8_t i = 0; i < font_size; i++){
		oled_write_data(pgm_read_byte(&font5[c - 32][i]));
	}
}

/* Prints string to OLED */
void oled_printf(char str[]){
	for(int i = 0; i < strlen(str); i++){
		oled_print(str[i]);
	}
}

/* Set OLED position */
// See table 8-1: command table in OLED controller datasheet (p.27). 
void oled_pos(uint8_t page, uint8_t seg){
	//Go to page  
	oled_write_command(page | (0xb0));
	// Go to segment
	oled_write_command(seg & 0x0f);
	oled_write_command(((seg & 0xf0) >> 4) | (0x10));
}

/* Clear single page on OLED */
void oled_clear_line(uint8_t page){
	oled_pos(page, 0);
	for (uint8_t i = 0; i < 128; i++){
		oled_write_data(0x0);
	}
}
/* Clear part of OLED from bottom left corner. */
void oled_clear_line_from(uint8_t page, uint8_t seg){
	oled_pos(page,seg);
	for (uint8_t i = seg; i < 128; i++){
		oled_write_data(0x0);
	}
}

/* Clear arrow used to indicate position in menu */
void oled_clear_arrow(void){
	oled_pos(0,0);
	for (uint8_t j = 0; j < 8; j++){
		oled_pos(j,0);
		for (uint8_t i = 0; i < 15; i++){
			oled_write_data(0x0);
		}
	}
}

/* Clear OLED */
void oled_clear_all(){
		oled_pos(0,0);
		for (uint8_t j = 0; j < 8; j++){
			oled_pos(j,0);
			for (uint8_t i = 0; i < 128; i++){
				oled_write_data(0x0);
			}
		}
}

/* Fill OLED */
void oled_fill_all(){
	oled_pos(0,0);
	for (uint8_t j = 0; j < 8; j++){
		oled_pos(j,0);
		for (uint8_t i = 0; i < 128; i++){
			oled_write_data(0xFF);
		}
	}
}


