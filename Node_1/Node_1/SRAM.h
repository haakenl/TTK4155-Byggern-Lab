/*
 * SRAM.h
 *
 * Created: 08.09.2021 08:26:35
 *  Author: haakenl
 */ 


#ifndef SRAM_H_
#define SRAM_H_

#include "config.h"
#include "OLED.h"


void SRAM_init();
void SRAM_write(uint8_t data, int index);
uint8_t SRAM_read(int index);
void SRAM_test(void);
void SRAM_test_OLED_print(void);

#endif /* SRAM_H_ */