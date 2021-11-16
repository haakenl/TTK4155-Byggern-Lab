/*
 * uart.c
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


/* Set up USART for RS232 communication */
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
	
	fdevopen(uart_transmit_char, uart_receive_char);
}

/* Transmits 8-bit of data over USART */
int uart_transmit_char(char data, FILE* file){
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = data;
	return 0;
}

/* Receives 8-bit of data over USART */
int uart_receive_char(FILE* file){
	loop_until_bit_is_set(UCSR0A, RXC0);
	return UDR0;
}


// OLD
///* Transmits 8-bit of data over USART */
//void uart_transmit(unsigned char data){
	//loop_until_bit_is_set(UCSR0A, UDRE0);
	//UDR0 = data;
//}
//
///* Receives 8-bit of data over USART */
//unsigned char uart_receive(void){
	//loop_until_bit_is_set(UCSR0A, RXC0);
	//return UDR0;
//}
