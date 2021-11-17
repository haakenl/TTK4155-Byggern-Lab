/*
 * uart.h
 *
 * Created: 01.09.2021 17:14:34
 *  Author: haakenl
 */ 


#ifndef UART_H_
#define UART_H_

#include <stdio.h>

void uart_transmit_char(unsigned char data);
unsigned char uart_receive_char(void);


void uart_init();

#endif /* UART_H_ */
