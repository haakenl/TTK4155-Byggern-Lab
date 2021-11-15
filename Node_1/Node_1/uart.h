/*
 * UART.h
 *
 * Created: 01.09.2021 17:14:34
 *  Author: haakenl
 */ 


#ifndef UART_H_
#define UART_H_


void uart_transmit(unsigned char data);
unsigned char uart_receive(void);
void uart_init();

#endif /* UART_H_ */
