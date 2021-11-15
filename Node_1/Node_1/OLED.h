/*
 * OLED.h
 *
 * Created: 22.09.2021 10:55:59
 *  Author: Haakenl
 */ 


#ifndef OLED_H_
#define OLED_H_

#include <avr/io.h>


void oled_write_command(char command);
void oled_write_data(char data);
void oled_init();
void oled_print(char c);
void oled_printf(char str[]);
void oled_pos(uint8_t page, uint8_t seg);
void oled_clear_line(uint8_t line);
void oled_clear_line_from(uint8_t page, uint8_t seg);
void oled_clear_arrow(void);
void oled_clear_all();
void oled_fill_all();


//void OLED_set_brightness(int lvl);

#endif /* OLED_H_ */