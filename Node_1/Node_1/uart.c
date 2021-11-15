/*
 * UART.c
 *
 * Created: 01.09.2021 17:15:36
 *  Author: haakenl
 */ 
#define F_CPU 4915200
#define BAUD 9600
#define UBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <stdio.h>

#include "uart.h"

void uart_transmit(unsigned char data){
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = data;
}

unsigned char uart_receive(void){
	loop_until_bit_is_set(UCSR0A, RXC0);
	return UDR0;
}

void uart_init(){
	
	// UBRR : USART Baud rate register
	unsigned int ubrr = UBRR;
	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	
	//stop bit, set frame format 8bit packages
	// USBS0 : Stop bit register
	// UCSZ00 set 8 bit format
	UCSR0C = (1<<URSEL0)|(1 << USBS0)|(3 << UCSZ00);
	
	// Enable Transmitter and Receiver
	UCSR0B = (1<<TXEN0)|(1<<RXEN0);
	
	fdevopen(uart_transmit, uart_receive);
}
