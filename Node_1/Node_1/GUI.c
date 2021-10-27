/*
 * GUI.c
 *
 * Created: 25.09.2021 11:29:45
 *  Author: haakenl
 */ 


#include "GUI.h"

	menu_t clear_high_score = {"Clear High Score", 0, &clear_high_score};
	menu_t Adjust_joy_deadband = {"Adjust Joy Deadband", 0, &Adjust_joy_deadband};
	menu_t auto_calibrate_joy = {"Auto Calibrate Joy", 0, &auto_calibrate_joy};
	menu_t settings = {"Settings", 3, NULL, {&auto_calibrate_joy, &Adjust_joy_deadband, &clear_high_score}};
	menu_t high_score = {"High Score", 0, &high_score};
	menu_t new_game = {"New Game", 0, &new_game};
	menu_t main_menu = {"Main Menu", 3, NULL, {&new_game, &high_score, &settings}};
	menu_t* current_menu;

void GUI_init(){
	clear_high_score.parent = &settings;
	Adjust_joy_deadband.parent = &settings;
	auto_calibrate_joy.parent = &settings;
	
	settings.parent = &main_menu;
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
		
		uint8_t stopp_trasmitting_ADC_values = 1;
		while(stopp_trasmitting_ADC_values){
		
		if(!(test_bit(PINB, PINB1))){
			Button_to_node2.id = 2;
			Button_to_node2.data_length = 1;
			Button_to_node2.data[0] = 1;
			CAN_message_send(&Button_to_node2);
			_delay_ms(50);
			while(!(test_bit(PINB, PINB1)));
			Button_to_node2.id = 2;
			Button_to_node2.data_length = 1;
			Button_to_node2.data[0] = 0;
			CAN_message_send(&Button_to_node2);
		}
		ADC_pos adc_pos = ADC_read();		
		ADC_to_node2.id = 3;
		ADC_to_node2.data_length = 2;
		ADC_to_node2.data[0] = adc_pos.joy_x ;
		ADC_to_node2.data[1] = adc_pos.joy_y; 			
		CAN_message_send(&ADC_to_node2);
		_delay_ms(16);
		}
		
		OLED_clear_all();
		OLED_pos(3, 39);
		OLED_printf("GAME ENDED");
		_delay_ms(1000);
	}
	else if(strcmp("High Score", current_child) == 0){
			OLED_pos(3, 24);
			OLED_printf("Print High Score"); //Print high score here
			_delay_ms(2000);		
	}
	else if (strcmp("Auto Calibrate Joy", current_child) == 0){
			OLED_pos(3, 14);
			OLED_printf("Calibrating Joystick"); 
			OLED_pos(4, 34);
			OLED_printf("DO NOT TOUCH");
			_delay_ms(2000);
			joystick_calibrate();
			_delay_ms(2000);
	}
	else if (strcmp("Adjust Joy Deadband", current_child) == 0){
		
		char joy_deadband_value[15];
		OLED_pos(0, 0);
		OLED_printf("Adjust Joy Deadband");
		OLED_pos(1, 0);
		OLED_printf("Move Joy up to Increase");
		OLED_pos(2, 0);
		OLED_printf("Move Joy down to decrease");
		OLED_pos(7, 0);
		OLED_printf("Move Joy Left to Exit");
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
		_delay_ms(100);
	}
	else if (strcmp("Clear High Score", current_child) == 0){
			OLED_pos(3, 19);
			OLED_printf("High Score Cleared");
			_delay_ms(2000);
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



	