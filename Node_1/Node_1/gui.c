/*
 * gui.c
 *
 * Created: 25.09.2021 11:29:45
 *  Author: haakenl
 */ 

#define F_CPU 4915200
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#include "gui.h"
#include "oled.h"
#include "adc.h"
#include "sram.h"
#include "uart.h"
#include "io.h"
#include "spi.h"

/* Strings stored in program memory to save progmem:
https://www.nongnu.org/avr-libc/user-manual/pgmspace.html */

const char str00[] PROGMEM = "High score:";
const char str01[] PROGMEM = "High score cleared";
const char str02[] PROGMEM = "Calibrating Joystick";
const char str03[] PROGMEM = "DO NOT TOUCH";
const char str04[] PROGMEM = "Adjust Joy Deadband";
const char str05[] PROGMEM = "Move joy up to increase";
const char str06[] PROGMEM = "Move joy down to decrease";
const char str07[] PROGMEM = "Move joy left to exit";
const char str08[] PROGMEM = "0     Value     255";
const char str09[] PROGMEM = "Ch 0";
const char str10[] PROGMEM = "Ch 1";
const char str11[] PROGMEM = "Ch 2";
const char str12[] PROGMEM = "CH 3";
const char str13[] PROGMEM = "Joy    Left    Rigth";
const char str14[] PROGMEM = "Exit with left + right";
const char str15[] PROGMEM = "SRAM test";
const char str16[] PROGMEM = "NB! all data is deleted";
const char str17[] PROGMEM = "Move joy right to confirm";
const char str18[] PROGMEM = "Testing SRAM...";
const char str19[] PROGMEM = "SRAM test finished:";
const char str20[] PROGMEM = "RS-232 config:";
const char str21[] PROGMEM = "- Loop back mode";
const char str22[] PROGMEM = "- Baud 9600";
const char str23[] PROGMEM = "- 8 Data bits";
const char str24[] PROGMEM = "- 2 Stop bits";
const char str25[] PROGMEM = "'External' SPI config:";
const char str26[] PROGMEM = "- Slave";
const char str27[] PROGMEM = "- SS high";
const char str28[] PROGMEM = "Main Menu";
const char str29[] PROGMEM = "New Game";
const char str30[] PROGMEM = "High Score";
const char str31[] PROGMEM = "Clear High Score";
const char str32[] PROGMEM = "Settings";
const char str33[] PROGMEM = "Auto Calibrate Joy";
const char str34[] PROGMEM = "Adjust Joy Deadband";
const char str35[] PROGMEM = "ADC test";
const char str36[] PROGMEM = "OLED test";
const char str37[] PROGMEM = "SRAM test";
const char str38[] PROGMEM = "RS-232 loop back";
const char str39[] PROGMEM = "SPI loop back";
const char str40[] PROGMEM = "Score: %d";
const char str41[] PROGMEM = "deadband: %d";
const char str42[] PROGMEM = "HAVE FUN";
const char str43[] PROGMEM = "Seconds played: %d";
const char str44[] PROGMEM = "Alex";
const char str45[] PROGMEM = "Haaken";
const char str46[] PROGMEM = "Jo Arve";
const char str47[] PROGMEM = "Nikolai";
const char str48[] PROGMEM = "-";
const char str49[] PROGMEM = "%d";


PGM_P const string_table[] PROGMEM =
{
	str00, str01, str02, str03, str04, str05, str06, str07, str08, str09, 
	str10, str11, str12, str13, str14, str15, str16, str17, str18, str19, 
	str20, str21, str22, str23, str24, str25, str26, str27, str28, str29,
	str30, str31, str32, str33, str34, str35, str36, str37, str38, str39,
	str40, str41, str42, str43, str44, str45, str46, str47, str48, str49
};

char buffer[1];


/* Menu structure with "childs"*/

			menu_t SPI_loopback = {39, 0, &SPI_loopback};	
			menu_t RS232_loopback = {38, 0, &RS232_loopback};
			menu_t SRAM_test_menu = {37, 0, &SRAM_test_menu};
			menu_t OLED_test = {36, 0, &OLED_test};
			menu_t ADC_test = {35, 0, &ADC_test};
			menu_t Adjust_joy_deadband = {34, 0, &Adjust_joy_deadband};
			menu_t auto_calibrate_joy = {33, 0, &auto_calibrate_joy};
		menu_t settings = {32, 7, NULL, {&auto_calibrate_joy, &Adjust_joy_deadband, &ADC_test, &OLED_test, &SRAM_test_menu, &RS232_loopback, &SPI_loopback}};
		menu_t clear_high_score = {31, 0, &clear_high_score};
		menu_t high_score = {30, 0, &high_score};
			menu_t user_4 = {47, 0, &user_4};
			menu_t user_3 = {46, 0, &user_3};
			menu_t user_2 = {45, 0, &user_2};
			menu_t user_1 = {44, 0, &user_1};
		menu_t new_game = {29, 4, NULL, {&user_1, &user_2, &user_3, &user_4}};
		//menu_t new_game = {29, 0, &new_game};
		menu_t main_menu = {28, 4, NULL, {&new_game, &high_score, &clear_high_score, &settings}};
	menu_t* current_menu;

/* Setup all "parents" */
void gui_init(){
			
			SPI_loopback.parent = &settings;
			RS232_loopback.parent = &settings;
			SRAM_test_menu.parent = &settings;
			OLED_test.parent = &settings;
			ADC_test.parent = &settings;
			Adjust_joy_deadband.parent = &settings;
			auto_calibrate_joy.parent = &settings;
		settings.parent = &main_menu;
		clear_high_score.parent = &main_menu;
		high_score.parent = &main_menu;
			user_4.parent = &main_menu;
			user_3.parent = &main_menu;
			user_2.parent = &main_menu;
			user_1.parent = &main_menu;
		new_game.parent = &main_menu;
	main_menu.parent = &main_menu;
	
	current_menu = &main_menu;
}

/* Print to OLED menu */
void gui_print_menu(menu_t* print_menu){
	oled_clear_all();
	for(int i=0; i<print_menu->number_of_childs; i++) {
		oled_pos(i, 15);
		strcpy_P(buffer, (PGM_P)pgm_read_word(&(string_table[(print_menu->children[i])->name])));
		oled_printf(buffer);
	}
}

/* Print single string to OLED */
void gui_print_string(uint16_t i){
	strcpy_P(buffer, (PGM_P)pgm_read_word(&(string_table[i])));
	oled_printf(buffer); 
}

/* Print navigation arrow to OLD */
void gui_print_arrow(int page){
		oled_clear_arrow();
		oled_pos(page, 0);
		oled_printf("->");
}

/* Step one menu down */
int gui_menu_down(int current_page){
	current_menu = current_menu->children[current_page];
	current_page = 0;
	gui_print_menu(current_menu);
	gui_print_arrow(current_page);
	return current_page;
}

/* Step one menu up */
int gui_menu_up(int current_page){
	current_menu = current_menu->parent;
	current_page = 0;
	gui_print_menu(current_menu);
	gui_print_arrow(current_page);
	return current_page;
}

/* Depending on the current menu one specific tasks will run until stopped by user */
void gui_menu_action(int current_page){			
	adc_direction current_direction;
	uint8_t  current_child;
	current_child = current_menu->name;
	
	/* New game */
	if(current_child == 44){ //User 1
		game_play(0);
	}
	if(current_child == 45){ //User 2
		game_play(1);
	}
	if(current_child == 46){ //User 3
		game_play(2);
	}
	if(current_child == 47){ //User 4
		game_play(3);
	}
	
	/* High Score */
	else if(current_child == 30){ 
		oled_pos(0, 0);
		gui_print_string(0); //Print "high score:"
		for(uint8_t i = 0; i < 4; i++){
			oled_pos(i+2, 0);
			gui_print_string(48); //Print "-"
			oled_pos(i+2, 10);
			gui_print_string(44+i); //Print "users"			
			char high_score_print[20];
			strcpy_P(buffer, (PGM_P)pgm_read_word(&(string_table[49])));
			sprintf(high_score_print, buffer, sram_read(i));
			oled_pos(i+2, 100);
			oled_printf(high_score_print); //Print "high score"	
		}
		oled_pos(7, 0);
		gui_print_string(7); //Print "Move joy left to exit"
		current_direction = debounce_joystick_direction();
		while(current_direction != LEFT){
			current_direction = debounce_joystick_direction();
		}
		_delay_ms(200);		
	}
	
	/* Clear High Score */
	else if(current_child == 31){ 
		sram_clear();
		oled_pos(3, 19);
		gui_print_string(1); //Print "High Score Cleared"
		oled_pos(7, 0);
		gui_print_string(7); //Print "Move joy left to exit"
		current_direction = debounce_joystick_direction();
		while(current_direction != LEFT){
			current_direction = debounce_joystick_direction();
		}
		_delay_ms(200);
	}
	
	/* Auto Calibrate Joy */
	else if(current_child == 33){ 
			oled_pos(3, 14);
			gui_print_string(2); //Print "Calibrating Joystick" 
			oled_pos(4, 34);
			gui_print_string(3); //Print "DO NOT TOUCH"
			_delay_ms(2000);
			joystick_calibrate();
			_delay_ms(2000);
	}
	
	/* Adjust Joy Deadband */
	else if(current_child == 34){ 
		char joy_deadband_value[15];
		oled_pos(0, 0);
		gui_print_string(4); //Print "Adjust Joy Deadband"
		oled_pos(1, 0);
		gui_print_string(5); //Print "Move joy up to increase"
		oled_pos(2, 0);
		gui_print_string(6); //Print "Move joy down to decrease"
		oled_pos(7, 0);
		gui_print_string(7); //Print Move joy left to exit"
		current_direction = debounce_joystick_direction();
		while(current_direction != LEFT){
			current_direction = debounce_joystick_direction();
			if(current_direction == UP){
				if(joy_deadband < 80){
					joy_deadband ++;
				}
			}
			else if(current_direction == DOWN){
				if(joy_deadband > 40){
					joy_deadband --;	
				}
			}		
			strcpy_P(buffer, (PGM_P)pgm_read_word(&(string_table[41])));
			sprintf(joy_deadband_value, buffer, joy_deadband);
			oled_clear_line(4);
			oled_printf(joy_deadband_value);
		}
		_delay_ms(200);
	}
	
	/* ADC test */
	else if(current_child == 35){
		oled_pos(0, 30); 
		gui_print_string(8); //Print "0     Value     255"
		for(uint8_t i = 0; i < 4; i++){
			oled_pos(i+1,1);
			gui_print_string(i+9); //Print "Ch ?"
		}
		oled_pos(6, 25);
		gui_print_string(13); //Print "Joy    Left    Right"
		oled_pos(7, 0);
		gui_print_string(14); //Print "Exit with left + right;
		
		adc_pos pos = adc_read();
		while(!test_bit(button_pin, button_left_bit) || !test_bit(button_pin, button_rigth_bit)){
			pos = adc_read();
			oled_clear_line_from(1, 30);
			oled_pos(1, (30+pos.joy_y/2.7));
			oled_printf("|");
			oled_clear_line_from(2, 30);
			oled_pos(2, (30+pos.joy_x/2.7));
			oled_printf("|");
			oled_clear_line_from(3, 30);
			oled_pos(3, (30+pos.slider_left/2.7));
			oled_printf("|");
			oled_clear_line_from(4, 30);
			oled_pos(4, (30+pos.slider_right/2.7));
			oled_printf("|");
			oled_clear_line_from(5, 30);
			if(!test_bit(button_pin, button_joy_bit)){
				oled_pos(5,30);
				oled_printf("*");
			}
			if(test_bit(button_pin, button_left_bit)){
				oled_pos(5,67);
				oled_printf("*");
			}
			if(test_bit(button_pin, button_rigth_bit)){
				oled_pos(5,110);
				oled_printf("*");
			}
			_delay_ms(50);
		}
		_delay_ms(200);
	}	
	
	/* OLED test */
	else if(current_child == 36){
		oled_fill_all();
		_delay_ms(100);
		current_direction = debounce_joystick_direction();
		while(current_direction != LEFT){
			current_direction = debounce_joystick_direction();
		}
	_delay_ms(200);
	}
	
	/* SRAM test */
	else if(current_child == 37){
		oled_pos(0, 0);
		gui_print_string(15); //Print "SRAM test");
		oled_pos(1, 0);
		gui_print_string(16); //Print "NB! all data is deleted"
		oled_pos(6, 0);
		gui_print_string(17); //Print "Move joy right to confirm"
		oled_pos(7, 0);
		gui_print_string(7); //Print Move joy left to exit"
		current_direction = debounce_joystick_direction();
		while(current_direction != LEFT){
			current_direction = debounce_joystick_direction();
			if(current_direction == RIGHT){
				oled_clear_line(1);
				oled_clear_line(6);
				oled_clear_line(0);
				gui_print_string(18); //Print "Starting SRAM test..."
				sram_test_OLED_print(); 
				oled_clear_line(0);
				oled_pos(0,0);
				gui_print_string(19); //Print "SRAM Finished..."
				current_direction = debounce_joystick_direction();
				while(current_direction != LEFT){
					current_direction = debounce_joystick_direction();
				}
			}
		}
		_delay_ms(200);
	}
	
	/* RS-232 loop back */
	else if(current_child == 38){ 
		oled_pos(0, 0);
		gui_print_string(20); //Print "RS-232 config:"
		oled_pos(1, 0);
		gui_print_string(21); //Print "- Loop back mode"
		oled_pos(2, 0);
		gui_print_string(22); //Print "- Baud 9600"
		oled_pos(3, 0);
		gui_print_string(23); //Print "- 8 Data bits"
		oled_pos(4, 0);
		gui_print_string(24); //Print "- 2 Stop bits"
		oled_pos(7, 0);
		gui_print_string(7); //Print Move joy left to exit"
		current_direction = debounce_joystick_direction();
		while(current_direction != LEFT){
			current_direction = debounce_joystick_direction();
			if(test_bit(UCSR0A, RXC0)){
				uart_transmit_char(UDR0);
			}
		}
	_delay_ms(200);
	}
	
	/* SPI loop back */
	else if(current_child == 39){ 
		oled_pos(0, 0);
		gui_print_string(25); //Print "'External' SPI config:");
		oled_pos(1, 0);
		gui_print_string(21); //Print "- Loop back mode");
		oled_pos(2, 0);
		gui_print_string(26); //Print "- Slave");
		oled_pos(3, 0);
		gui_print_string(27); //Print "- SS high");
		oled_pos(7, 0);
		gui_print_string(7); //Print Move joy left to exit"
		current_direction = debounce_joystick_direction();
		while(current_direction != LEFT){
			current_direction = debounce_joystick_direction();
			if(test_bit(spi_ext_reg, spi_ss_bit)){
				spi_transmit(spi_recive());
			}
		}
	_delay_ms(200);
	}
}

/* Navigate through the menu system based on the joystick position */
void gui_menu(){
	static adc_direction previous_direction = NEUTRAL;
	static int current_page = 0;
	adc_direction current_direction;
	 		
	current_direction = debounce_joystick_direction();
	if (current_direction != previous_direction){
		switch(current_direction){
			case UP:
				if(current_page > 0){
				current_page --;
				}
				else {
				current_page = (current_menu->number_of_childs)-1;
				} 
				gui_print_arrow(current_page);
			break;
		
			case DOWN:
				if(current_page < (current_menu->number_of_childs)-1){
					current_page ++;
				}
				else {
					current_page = 0;
				}
				gui_print_arrow(current_page);	
			break;
		
			case RIGHT:
				current_page = gui_menu_down(current_page);
				if(current_menu->number_of_childs == 0){
					oled_clear_all();
					gui_menu_action(current_page);
					current_page = gui_menu_up(current_page);
				}
			break;
		
			case LEFT:
				current_page = gui_menu_up(current_page);	
			break;
			
			case NEUTRAL:
			break;
		}
		previous_direction = current_direction;	
	}	
}



void game_play(uint8_t user){
	oled_pos(3, 43);
	gui_print_string(42); //Print "HAVE FUN"
	_delay_ms(1000);
	
	/*Clear any mail box interrupt flags */
	while(test_bit(can_int_flag_reg, can_int_flag_bit) == 0){
		can_mailbox();
		if(can_mailbox_0_recive_flag == 1){
			can_message_receive(0);
		}
		
		if(can_mailbox_1_recive_flag == 1){
			can_message_receive(1);
		}
	}	

	
	uint8_t game_score = 0;
	uint8_t game_run = 1;
	uint8_t game_clock = 0;
	
	game_to_node2.id = 4;					// New game
	game_to_node2.data_length = 3;
	game_to_node2.data[0] = game_score;		// reset game score
	game_to_node2.data[1] = game_clock;		// reset and game clock
	game_to_node2.data[2] = game_run;		// run game
	can_message_send(&game_to_node2);
	
	/* Print time to OLED */
	uint8_t game_clock_sek = 0;
	uint8_t game_clock_hundreds = 0;
	char time_print[20];
	oled_clear_line(3);
	strcpy_P(buffer, (PGM_P)pgm_read_word(&(string_table[43])));
	sprintf(time_print, buffer, game_clock_sek, game_clock_hundreds );
	oled_pos(3, 20);
	oled_printf(time_print);
		
	/* Repeat until game has ended */
	while(game_run == 1){
		/* Update and print time to OLED */
		game_clock_hundreds = game_clock_hundreds + 1;
		if(game_clock_hundreds == 94){ // The code uses normally a fraction more that 10ms to complete.
			game_clock_hundreds = 0;
			game_clock_sek = game_clock_sek + 1;
			char time_print[20];
			oled_clear_line(3);
			strcpy_P(buffer, (PGM_P)pgm_read_word(&(string_table[43])));
			sprintf(time_print, buffer, game_clock_sek);
			oled_pos(3, 20);
			oled_printf(time_print);
		}
		
		/* Shoot! */
		if(!(test_bit(button_pin, button_joy_bit))){
			button_to_node2.id = 2;
			button_to_node2.data_length = 1;
			button_to_node2.data[0] = 1;
			can_message_send(&button_to_node2);
			_delay_ms(10);
			while(!test_bit(button_pin, button_joy_bit));
			button_to_node2.id = 2;
			button_to_node2.data_length = 1;
			button_to_node2.data[0] = 0;
			can_message_send(&button_to_node2);
		}
		/* Update ADC pos */
		adc_pos adc_pos = adc_read();
		ADC_to_node2.id = 3;
		ADC_to_node2.data_length = 2;
		ADC_to_node2.data[0] = adc_pos.joy_x ;
		ADC_to_node2.data[1] = adc_pos.joy_y;
		can_message_send(&ADC_to_node2);
		/* Wait 10ms this gives ~100 ADC updates per seconded */
		_delay_ms(10);

		
		if(test_bit(can_int_flag_reg, can_int_flag_bit) == 0){
			can_mailbox();
			if(can_mailbox_0_recive_flag == 1){
				game_from_node2 = can_message_receive(0);
				if (game_from_node2.id  == 1){
					game_score = game_from_node2.data[0];
					game_run = game_from_node2.data[1];
				}
			}
			if(can_mailbox_1_recive_flag == 1){
				game_from_node2 = can_message_receive(1);
				if (game_from_node2.id  == 1){
					game_score = game_from_node2.data[0];
					game_run = game_from_node2.data[1];
				}
			}
		}
	}
	
	/* Save score in sram */
	if(sram_read(user) >  game_score){
		sram_write(game_score, user);
	}
	
	/* Print score to OLED */
	oled_clear_all();
	char score_print[20];
	strcpy_P(buffer, (PGM_P)pgm_read_word(&(string_table[40])));
	sprintf(score_print, buffer, game_score);
	oled_pos(3, 40);
	oled_printf(score_print);
	oled_pos(7, 0);
	gui_print_string(7); //Print "Move joy left to exit"
	adc_direction current_direction = debounce_joystick_direction();
	while(current_direction != LEFT){
		current_direction = debounce_joystick_direction();
	}
	_delay_ms(200);	
}