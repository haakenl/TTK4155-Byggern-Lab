/*
 * SRAM.c
 *
 * Created: 08.09.2021 08:26:19
 *  Author: haakenl
 */ 

#define F_CPU 4915200
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "sram.h"
#include "io.h"
#include "oled.h"


const char str0sram[] PROGMEM = "Write errors: %d";
const char str1sram[] PROGMEM = "Retrieval errors: %d";

PGM_P const string_table_sram[] PROGMEM =
{
	str0sram, str1sram
};

char buffer_sram[1];

void sram_init(){
	set_bit(MCUCR,SRE); // Setting SRE enables external SRAM with ALE, WR, RD. Override all other pin settings. Writing to zero disables. 
	set_bit(EMCUCR, SRW01); // Wait two cycles during Read/Write
	set_bit(SFIOR,XMM2); // Mask out JTAG. PC4-PC7. 
}

void sram_write(uint8_t data, int index){
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	ext_ram[index] = data;
}
uint8_t sram_read(int index){
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint8_t retreived_value = ext_ram[index];
	return retreived_value;
}


void sram_test_OLED_print(void)
{
	_delay_ms(100);
	volatile char *ext_ram = (char *) 0x1800; // Start address for the SRAM
	uint16_t ext_ram_size = 0x800;
	uint16_t write_errors = 0;
	uint16_t retrieval_errors = 0;
	// rand() stores some internal state, so calling this function in a loop will
	// yield different seeds each time (unless srand() is called before this function)
	uint16_t seed = rand();
	// Write phase: Immediately check that the correct value was stored
	srand(seed);
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		ext_ram[i] = some_value;
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			write_errors++;
		}
	}
	// Retrieval phase: Check that no values were changed during or after the write phase
	srand(seed);
	// reset the PRNG to the state it had before the write phase
	for (uint16_t i = 0; i < ext_ram_size; i++) {
		uint8_t some_value = rand();
		uint8_t retreived_value = ext_ram[i];
		if (retreived_value != some_value) {
			retrieval_errors++;
		}
	}
	
	_delay_ms(100);
	
	char write_errors_print[20];
	strcpy_P(buffer_sram, (PGM_P)pgm_read_word(&(string_table_sram[0])));
	sprintf(write_errors_print, buffer_sram, write_errors);
	oled_clear_line(1);
	oled_pos(1,0);
	oled_printf(write_errors_print);
	
	
	char retrieval_errors_print[20];
	strcpy_P(buffer_sram, (PGM_P)pgm_read_word(&(string_table_sram[1])));
	sprintf(retrieval_errors_print, buffer_sram, retrieval_errors);
	oled_clear_line(2);
	oled_pos(2,0);
	oled_printf(retrieval_errors_print);
}