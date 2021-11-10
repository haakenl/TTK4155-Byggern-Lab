/*
 * GUI.c
 *
 * Created: 25.09.2021 11:29:45
 *  Author: haakenl
 */ 



#include "GUI.h"

/* Strings stored in program memory to save progmem:
https://www.nongnu.org/avr-libc/user-manual/pgmspace.html*/

const char str00[] PROGMEM = "Print high score";
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
const char str28[] PROGMEM = "";
const char str29[] PROGMEM = "";

PGM_P const string_table[] PROGMEM =
{
	str00, str01, str02, str03, str04, str05, str06, str07, str08, str09, 
	str10, str11, str12, str13, str14, str15, str16, str17, str18, str19, 
	str20, str21, str22, str23, str24, str25, str26, str27, str28, str29
};

char buffer[1];

			menu_t SPI_loopback = {"SPI loop back", 0, &SPI_loopback};	
			menu_t RS232_loopback = {"RS-232 loop back", 0, &RS232_loopback};
			menu_t SRAM_test_menu = {"SRAM test", 0, &SRAM_test_menu};
			menu_t OLED_test = {"OLED test", 0, &OLED_test};
			menu_t ADC_test = {"ADC test", 0, &ADC_test};
			menu_t Adjust_joy_deadband = {"Adjust Joy Deadband", 0, &Adjust_joy_deadband};
			menu_t auto_calibrate_joy = {"Auto Calibrate Joy", 0, &auto_calibrate_joy};
		menu_t settings = {"Settings", 7, NULL, {&auto_calibrate_joy, &Adjust_joy_deadband, &ADC_test, &OLED_test, &SRAM_test_menu, &RS232_loopback, &SPI_loopback}};
		menu_t clear_high_score = {"Clear High Score", 0, &clear_high_score};
		menu_t high_score = {"High Score", 0, &high_score};
		menu_t new_game = {"New Game", 0, &new_game};
		menu_t main_menu = {"Main Menu", 4, NULL, {&new_game, &high_score, &clear_high_score, &settings}};
	menu_t* current_menu;

void GUI_init(){
			
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
		new_game.parent = &main_menu;
	main_menu.parent = &main_menu;
	
	current_menu = &main_menu;
}

void GUI_print_menu(menu_t* print_menu){
	OLED_clear_all();
	for(int i=0; i<print_menu->number_of_childs; i++) {
		OLED_pos(i, 15);
		OLED_printf((print_menu->children[i])->name);
	}
}

void GUI_print_string(uint16_t i){
	strcpy_P(buffer, (PGM_P)pgm_read_word(&(string_table[i])));
	OLED_printf(buffer); //Print high score here
}

void GUI_print_arrow(int page){
		OLED_clear_arrow();
		OLED_pos(page, 0);
		OLED_printf("->");
}

int GUI_menu_down(int current_page){
	current_menu = current_menu->children[current_page];
	current_page = 0;
	OLED_pos(0,0);
	GUI_print_menu(current_menu);
	OLED_pos(0,0);
	GUI_print_arrow(current_page);
	return current_page;
}

int GUI_menu_up(int current_page){
	current_menu = current_menu->parent;
	current_page = 0;
	OLED_pos(0,0);
	GUI_print_menu(current_menu);
	OLED_pos(0,0);
	GUI_print_arrow(current_page);
	return current_page;
}

void GUI_menu_action(int current_page){
	ADC_direction current_direction;
	char*  current_child;
	current_child = current_menu->name;
	
	if(strcmp("New Game", current_child) == 0){
		OLED_pos(3, 43);
		OLED_printf("HAVE FUN");
		_delay_ms(1000); // INSERT GAME PLAY HERE
		
		uint8_t score = 0;
		
		game.id = 4;			// New game 
		game.data_length = 2;
		game.data[0] = 0;		// reset game score
		game.data[1] = 0;		// reset and game clock
		CAN_message_send(&game);
		
		uint8_t stopp_trasmitting_ADC_values = 0;
		while(stopp_trasmitting_ADC_values == 0){
			/* Shoot! */
			if(!(test_bit(PINB, PINB1))){
				Button_to_node2.id = 2;
				Button_to_node2.data_length = 1;
				Button_to_node2.data[0] = 1;
				CAN_message_send(&Button_to_node2);
				_delay_ms(50);
				while(!test_bit(Button_pin, Button_joy_bit));
				Button_to_node2.id = 2;
				Button_to_node2.data_length = 1;
				Button_to_node2.data[0] = 0;
				CAN_message_send(&Button_to_node2);
			}
			/* Update ADC pos */
			ADC_pos adc_pos = ADC_read();
			ADC_to_node2.id = 3;
			ADC_to_node2.data_length = 2;
			ADC_to_node2.data[0] = adc_pos.joy_x ;
			ADC_to_node2.data[1] = adc_pos.joy_y; 			
			CAN_message_send(&ADC_to_node2);
			/* Wait 16ms this gives ~60 ADC updates per seconded (same update frequency as digitizer on smart phones) */
			_delay_ms(16);	
			if(test_bit(CAN_int_flag_reg, CAN_int_flag_bit) == 0){
				game_ended = CAN_message_receive();
				if(game_ended.id == 1){
					score = game_ended.data[0];
					stopp_trasmitting_ADC_values = game_ended.data[1];
				}
			}
		}
		OLED_clear_line(0);
		OLED_pos(0,0);
		OLED_pos(3, 30);
		char score_print[1];
		sprintf(score_print, "Game Score: %d", score);
		OLED_printf(score_print);
		//OLED_printf("test");
		_delay_ms(2000);
		OLED_pos(7, 0);
		GUI_print_string(7); //Print Move joy left to exit"	
		while(current_direction != LEFT){
			current_direction = debounce_joystick_direction();
		}	
	
	}
	if(strcmp("High Score", current_child) == 0){
			OLED_pos(3, 24);
			GUI_print_string(0); //Print "high score here"
			_delay_ms(2000);		
	}
	else if (strcmp("Clear High Score", current_child) == 0){
			OLED_pos(3, 19);
			GUI_print_string(1); //Print "High Score Cleared"
			_delay_ms(2000);
	}
	else if (strcmp("Auto Calibrate Joy", current_child) == 0){
			OLED_pos(3, 14);
			GUI_print_string(2); //Print "Calibrating Joystick" 
			OLED_pos(4, 34);
			GUI_print_string(3); //Print "DO NOT TOUCH"
			_delay_ms(2000);
			joystick_calibrate();
			_delay_ms(2000);
	}
	else if (strcmp("Adjust Joy Deadband", current_child) == 0){
		char joy_deadband_value[15];
		OLED_pos(0, 0);
		GUI_print_string(4); //Print "Adjust Joy Deadband"
		OLED_pos(1, 0);
		GUI_print_string(5); //Print "Move joy up to increase"
		OLED_pos(2, 0);
		GUI_print_string(6); //Print "Move joy down to decrease"
		OLED_pos(7, 0);
		GUI_print_string(7); //Print Move joy left to exit"
		current_direction = debounce_joystick_direction();
		while(current_direction != LEFT){
			current_direction = debounce_joystick_direction();
			if(current_direction == UP){
				joy_deadband ++;
			}
			else if(current_direction == DOWN){
				joy_deadband --;	
			}		
			sprintf(joy_deadband_value, "deadband: %d", joy_deadband);
			OLED_clear_line(4);
			OLED_printf(joy_deadband_value);
		}
		_delay_ms(200);
	}
	else if (strcmp("ADC test", current_child) == 0){
		OLED_pos(0, 30); 
		GUI_print_string(8); //Print "0     Value     255"
		OLED_pos(1, 1);
		GUI_print_string(9); //Print "Ch 0"
		OLED_pos(2, 0);
		GUI_print_string(10); //Print "Ch 1"
		OLED_pos(3, 0);
		GUI_print_string(11); //Print "CH 2"
		OLED_pos(4, 0);
		GUI_print_string(12); //Print "CH 3"
		OLED_pos(6, 25);
		GUI_print_string(13); //Print "Joy    Left    Right"
		OLED_pos(7, 0);
		GUI_print_string(14); //Print "Exit with left + right;
		
		ADC_pos pos = ADC_read();
		while(!test_bit(Button_pin, Button_left_bit) || !test_bit(Button_pin, Button_rigth_bit)){
			pos = ADC_read();
			OLED_clear_line_from(1, 30);
			OLED_pos(1, (30+pos.joy_y/2.7));
			OLED_printf("|");
			OLED_clear_line_from(2, 30);
			OLED_pos(2, (30+pos.joy_x/2.7));
			OLED_printf("|");
			OLED_clear_line_from(3, 30);
			OLED_pos(3, (30+pos.slider_left/2.7));
			OLED_printf("|");
			OLED_clear_line_from(4, 30);
			OLED_pos(4, (30+pos.slider_right/2.7));
			OLED_printf("|");
			OLED_clear_line_from(5, 30);
			if(!test_bit(Button_pin, Button_joy_bit)){
				OLED_pos(5,30);
				OLED_printf("*");
			}
			if(test_bit(Button_pin, Button_left_bit)){
				OLED_pos(5,67);
				OLED_printf("*");
			}
			if(test_bit(Button_pin, Button_rigth_bit)){
				OLED_pos(5,110);
				OLED_printf("*");
			}
			_delay_ms(50);
		}
		_delay_ms(200);
	}	
	else if (strcmp("OLED test", current_child) == 0){
		OLED_fill_all();
		_delay_ms(100);
		current_direction = debounce_joystick_direction();
		while(current_direction != LEFT){
			current_direction = debounce_joystick_direction();
		}
	_delay_ms(200);
	}
	else if (strcmp("SRAM test", current_child) == 0){
		OLED_pos(0, 0);
		GUI_print_string(15); //Print "SRAM test");
		OLED_pos(1, 0);
		GUI_print_string(16); //Print "NB! all data is deleted"
		OLED_pos(6, 0);
		GUI_print_string(17); //Print "Move joy right to confirm"
		OLED_pos(7, 0);
		GUI_print_string(7); //Print Move joy left to exit"
		current_direction = debounce_joystick_direction();
		while(current_direction != LEFT){
			current_direction = debounce_joystick_direction();
			if(current_direction == RIGHT){
				OLED_clear_line(1);
				OLED_clear_line(6);
				OLED_clear_line(0);
				GUI_print_string(18); //Print "Starting SRAM test..."
				SRAM_test_OLED_print(); 
				OLED_clear_line(0);
				OLED_pos(0,0);
				GUI_print_string(19); //Print "SRAM Finished..."
				while(current_direction != LEFT){
					current_direction = debounce_joystick_direction();
				}
			}
		}
		_delay_ms(200);
	}
	else if (strcmp("RS-232 loop back", current_child) == 0){
		OLED_pos(0, 0);
		GUI_print_string(20); //Print "RS-232 config:"
		OLED_pos(1, 0);
		GUI_print_string(21); //Print "- Loop back mode"
		OLED_pos(2, 0);
		GUI_print_string(22); //Print "- Baud 9600"
		OLED_pos(3, 0);
		GUI_print_string(23); //Print "- 8 Data bits"
		OLED_pos(4, 0);
		GUI_print_string(24); //Print "- 2 Stop bits"
		OLED_pos(7, 0);
		GUI_print_string(7); //Print Move joy left to exit"
		current_direction = debounce_joystick_direction();
		while(current_direction != LEFT){
			current_direction = debounce_joystick_direction();
			if(test_bit(UCSR0A, RXC0)){
				UART_transmit(UDR0);
			}
		}
	_delay_ms(200);
	}
	else if (strcmp("SPI loop back", current_child) == 0){
		OLED_pos(0, 0);
		GUI_print_string(25); //Print "'External' SPI config:");
		OLED_pos(1, 0);
		GUI_print_string(21); //Print "- Loop back mode");
		OLED_pos(2, 0);
		GUI_print_string(26); //Print "- Slave");
		OLED_pos(3, 0);
		GUI_print_string(27); //Print "- SS high");
		OLED_pos(7, 0);
		GUI_print_string(7); //Print Move joy left to exit"
		current_direction = debounce_joystick_direction();
		while(current_direction != LEFT){
			current_direction = debounce_joystick_direction();
			if(test_bit(SPI_ext_reg, SPI_SS_bit)){
				SPI_transmit(SPI_recive());
			}
		}
	_delay_ms(200);
	}
}

void GUI_menu(){
	static ADC_direction previous_direction = NEUTRAL;
	static int current_page = 0;
	ADC_direction current_direction;
	 		
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
				GUI_print_arrow(current_page);
			break;
		
			case DOWN:
				if(current_page < (current_menu->number_of_childs)-1){
					current_page ++;
				}
				else {
					current_page = 0;
				}
				GUI_print_arrow(current_page);	
			break;
		
			case RIGHT:
				current_page = GUI_menu_down(current_page);
				if(current_menu->number_of_childs == 0){
					OLED_clear_all();
					GUI_menu_action(current_page);
					current_page = GUI_menu_up(current_page);
				}
			break;
		
			case LEFT:
				current_page = GUI_menu_up(current_page);	
			break;
			
			case NEUTRAL:
			break;
		}
		previous_direction = current_direction;	
	}	
}



	