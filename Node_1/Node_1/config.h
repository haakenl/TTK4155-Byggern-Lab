/*
 * config.h
 *
 * Created: 01.09.2021 17:12:17
 *  Author: haakenl
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

#define F_CPU 4915200
#define BAUD 9600
#define UBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include <stdbool.h>
#include <string.h>


#define reg_buttons PORTB
#define joy_button PINB1
#define rigth_button PINB2
#define left_button PINB3

#define LED_reg DDRD
#define LED_port PORTD
#define LED_error PIND5
#define LED_normal PIND4

#define set_bit(reg, bit) (reg |= (1 << bit))
#define clear_bit(reg, bit) (reg &= ~(1 << bit))
#define test_bit(reg, bit) (reg & (1 << bit))


#endif /* CONFIG_H_ */