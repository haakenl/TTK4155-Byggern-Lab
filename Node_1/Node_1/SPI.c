/*
 * SPI.c
 *
 * Created: 06.10.2021 09:15:25
 *  Author: haakenl
 */ 


#include "SPI.h"

void SPI_MasterInit(void){
	// Set MOSI and SCK output, all others input 
	set_bit(DDRB, SPI_MOSI);
	set_bit(DDRB, SPI_SCK);
	set_bit(DDRB, SPI_CAN_SS);
	// Enable SPI, Master, set clock rate fck/16, SPI MODE 0
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_transmit(char cData){
	// Start transmission 
	SPDR = cData;
	// Wait for transmission complete 
	while(!(SPSR & (1<<SPIF)));
}

char SPI_recive(void){
	//Wait for transmission to complete 
	SPDR = 0x00;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

void SPI_enslaved_CAN(void){
	clear_bit(PORTB, SPI_CAN_SS);
}

void SPI_release_CAN(void){
	set_bit(PORTB, SPI_CAN_SS); 
}
