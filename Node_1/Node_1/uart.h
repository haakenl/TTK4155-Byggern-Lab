/*
 * uart.h
 *
 * Created: 01.09.2021 17:14:34
 *  Author: haakenl
 */ 


#ifndef UART_H_
#define UART_H_

#include <stdio.h>

//void uart_transmit(unsigned char data);
//unsigned char uart_receive(void);
int uart_transmit_char(char data, FILE* file);
int uart_receive_char(FILE* file);

void uart_init();

#endif /* UART_H_ */
