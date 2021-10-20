/*
 * UART.c
 *
 * Created: 01.09.2021 17:15:36
 *  Author: haakenl
 */ 

#include "UART.h"

void UART_transmit(unsigned char data){
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = data;
}

unsigned char UART_receive(void){
	loop_until_bit_is_set(UCSR0A, RXC0);
	return UDR0;
}

void UART_init(){
	
	// UBRR : USART Baud rate register
	unsigned int ubrr = UBRR;
	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	
	//stop bit, set frame format 8bit packages
	// USBS0 : Stop bit register
	// UCSZ00 set 8 bit format
	UCSR0C = (1<<URSEL0)|(1 << USBS0) | (3 << UCSZ00);
	
	// Enable Transmitter and Receiver
	UCSR0B = (1<<TXEN0)|(1<<RXEN0);
	
	fdevopen(UART_transmit, UART_receive);
}