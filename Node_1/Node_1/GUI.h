/*
 * GUI.h
 *
 * Created: 25.09.2021 11:29:27
 *  Author: haakenl
 */ 


#ifndef GUI_H_
#define GUI_H_

#include "config.h"
#include "OLED.h"
#include "ADC.h"
#include "CAN.h"
#include "SRAM.h"
#include "UART.h"

typedef struct menu_t{
	const uint8_t name;
	const uint8_t number_of_childs;
	const struct menu_t* parent;
	const struct menu_t* children[8];	
} menu_t;

menu_t* current_menu;
//const menu_t PROGMEM main_menu; 
//menu_t new_game;
//menu_t high_score;
//menu_t settings; 
//menu_t auto_calibrate_joy; 
//menu_t clear_high_score; 

void GUI_init();
void GUI_print_menu(menu_t* print_menu);
void GUI_print_arrow(int page);
int GUI_menu_down(int current_page);
int GUI_menu_up(int current_page);
void GUI_menu_action(int current_page);
void GUI_menu();

can_message ADC_to_node2;
can_message Button_to_node2;
can_message game;
can_message game_ended;

#endif /* GUI_H_ */