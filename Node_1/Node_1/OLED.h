/*
 * OLED.h
 *
 * Created: 22.09.2021 10:55:59
 *  Author: Haakenl
 */ 


#ifndef OLED_H_
#define OLED_H_

#include "config.h"


void OLED_write_command(char command);
void OLED_write_data(char data);
void OLED_init();
void OLED_print(char c);
void OLED_printf(char str[]);
void OLED_pos(uint8_t page, uint8_t seg);
void OLED_clear_line(uint8_t line);
void OLED_clear_line_from(uint8_t page, uint8_t seg);
void OLED_clear_arrow(void);
void OLED_clear_all();
void OLED_fill_all();


//void OLED_set_brightness(int lvl);

#endif /* OLED_H_ */