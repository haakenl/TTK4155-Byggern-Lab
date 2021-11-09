/*
 * CAN.c
 *
 * Created: 06.10.2021 09:59:40
 *  Author: haakenl
 */ 

#include "CAN.h"


uint8_t CAN_read(uint8_t adr){
	uint8_t data;	
	
	SPI_enslaved_CAN();
	SPI_transmit(MCP_READ);
	SPI_transmit(adr);
	data = SPI_recive();
	SPI_release_CAN();
	
	return data;	
}

void CAN_write(uint8_t adr, uint8_t data){
	SPI_enslaved_CAN();
	SPI_transmit(MCP_WRITE);
	SPI_transmit(adr);
	SPI_transmit(data); 
	SPI_release_CAN();		
}

void CAN_bit_modify(uint8_t reg, uint8_t mask, uint8_t bit){
	SPI_enslaved_CAN();
	SPI_transmit(MCP_BITMOD);
	SPI_transmit(reg);
	SPI_transmit(mask);
	SPI_transmit(bit);
	SPI_release_CAN();
}

void CAN_request_to_send(uint8_t request_to_send){
	SPI_enslaved_CAN();
	SPI_transmit(request_to_send);
	SPI_release_CAN();	
}

uint8_t CAN_read_status(void){
	uint8_t data;
		
	SPI_enslaved_CAN();
	SPI_transmit(MCP_READ_STATUS);
	data = SPI_recive();
	SPI_release_CAN();
		
	return data;	
}

void CAN_sw_reset(void){
	SPI_enslaved_CAN();
	SPI_transmit(MCP_RESET);
	SPI_release_CAN();
}


// Can high level functions below
uint8_t CAN_init(void){
	uint8_t error_check;	
	CAN_sw_reset();
	_delay_ms(10);
	
	// Set config mode
	error_check = CAN_read(MCP_CANSTAT);
	if((error_check & MODE_MASK) != MODE_CONFIG){
		return 1;
	}		
	
	// Configure MCP 2514
	CAN_write(MCP_CNF3, 0x05);		//see can config sheet on github
	CAN_write(MCP_CNF2, 0xb1);		//see can config sheet on github
	CAN_write(MCP_CNF1, 0x03);		//see can config sheet on github
	CAN_write(MCP_CANINTE, MCP_RX_INT); //Turn on RX interrupt	
	
	// Set normal mode
	CAN_bit_modify(MCP_CANCTRL, MODE_POWERUP, MODE_NORMAL);
		error_check = CAN_read(MCP_CANSTAT);
		if((error_check & MODE_MASK) != MODE_NORMAL){
			return 1;
		}	
	return 0;
}


void CAN_message_send(struct can_message* msg){	
	uint8_t i;
	
	// set message id
	CAN_write(MCP_TXB0SIDH, msg->id /  8);
	CAN_write(MCP_TXB0SIDL, (msg->id % 8) << 5);

	// set message length 
	CAN_write(MCP_TXB0DL, msg->data_length);
	
	// transfer data
	for(i = 0; i < msg->data_length; i++){
		CAN_write(MCP_TXB0D0 + i, msg->data[i]);		
	}
	CAN_request_to_send(MCP_RTS_TX0);
}


can_message CAN_message_receive(void){
	can_message msg = {};

	// read message id
	msg.id = (CAN_read(MCP_RXB1SIDH) * 8) + (CAN_read(MCP_RXB1SIDL) >> 5);

	// read data length
	msg.data_length = CAN_read(MCP_RXB1DL);

	// read data
	for (int i = 0; i < msg.data_length; i++) {
		msg.data[i] = CAN_read(MCP_RXB1D0 + i);
	}
	// reset int RX1 flag
	CAN_bit_modify(MCP_CANINTF, MCP_RX1IF, 0);
	return msg;
}
