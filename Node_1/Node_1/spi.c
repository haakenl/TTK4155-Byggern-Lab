/*
 * spi.c
 *
 * Created: 06.10.2021 09:15:25
 *  Author: haakenl
 */ 


#include "spi.h"
#include "io.h"

/* SPI inti */
void spi_master_init(void){
	// Set MOSI and SCK output, all others input 
	set_bit(spi_can_reg, spi_mosi);
	set_bit(spi_can_reg, spi_sck);
	set_bit(spi_can_reg, spi_can_ss);
	// Enable SPI, Master, set clock rate fck/16, SPI MODE 0
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

/* SPI transmit NB: SS is not set in this function  */
void spi_transmit(char cData){
	// Start transmission 
	SPDR = cData;
	// Wait for transmission complete 
	while(!(SPSR & (1<<SPIF)));
}

/* SPI receive NB: SS is read in this function */
char spi_recive(void){
	//Wait for transmission to complete 
	SPDR = 0x00;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}

/* CAN SPI SS enable */
void spi_enslaved_can(void){
	clear_bit(spi_can_port, spi_can_ss);
}

/* CAN SPI SS disable */
void spi_release_can(void){
	set_bit(spi_can_port, spi_can_ss); 
}
