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
#include <avr/pgmspace.h>

#define Button_reg DDRB
#define Button_port PORTB
#define Button_joy_port_bit PINB1
#define Button_pin PINB
#define Button_joy_bit PB1
#define Button_rigth_bit PB3
#define Button_left_bit PB2

#define SPI_ext_reg DDRD
#define SPI_ext_port PORTD
#define SPI_SS_bit PIND3

#define LED_reg DDRD
#define LED_port PORTD
#define LED_error PIND5
#define LED_normal PIND4

#define set_bit(reg, bit) (reg |= (1 << bit))
#define clear_bit(reg, bit) (reg &= ~(1 << bit))
#define test_bit(reg, bit) (reg & (1 << bit))

uint8_t errorflag;

#endif /* CONFIG_H_ */