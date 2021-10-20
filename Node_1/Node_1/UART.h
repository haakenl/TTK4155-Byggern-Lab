/*
 * UART.h
 *
 * Created: 01.09.2021 17:14:34
 *  Author: haakenl
 */ 


#ifndef UART_H_
#define UART_H_

#include "config.h"

void UART_transmit(unsigned char data);
unsigned char UART_receive(void);
void UART_init();

#endif /* UART_H_ */