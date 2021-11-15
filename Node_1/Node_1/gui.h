/*
 * GUI.h
 *
 * Created: 25.09.2021 11:29:27
 *  Author: haakenl
 */ 


#ifndef GUI_H_
#define GUI_H_

#include "can.h"


typedef struct menu_t{
	uint8_t name;
	uint8_t number_of_childs;
	struct menu_t* parent;
	struct menu_t* children[8];	
} menu_t;

menu_t* current_menu;

void gui_init();
void gui_print_menu(menu_t* print_menu);
void gui_print_arrow(int page);
int gui_menu_down(int current_page);
int gui_menu_up(int current_page);
void gui_menu_action(int current_page);
void gui_menu();

can_message ADC_to_node2;
can_message button_to_node2;
can_message game;
can_message game_ended;

#endif /* GUI_H_ */
