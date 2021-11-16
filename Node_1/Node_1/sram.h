/*
 * sram.h
 *
 * Created: 08.09.2021 08:26:35
 *  Author: haakenl
 */ 


#ifndef SRAM_H_
#define SRAM_H_

#include <avr/io.h>
#include <stdint.h>

void parallel_bus_init();
void sram_write(uint8_t data, int index);
uint8_t sram_read(int index);
void sram_test(void);
void sram_test_OLED_print(void);

#endif /* SRAM_H_ */
