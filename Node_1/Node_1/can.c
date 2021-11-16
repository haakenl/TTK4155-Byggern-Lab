/*
 * can.c
 *
 * Created: 06.10.2021 09:59:40
 *  Author: haakenl
 */ 

#define F_CPU 4915200
#include <util/delay.h>
#include "io.h"
#include "can.h"
#include "spi.h"
#include "mcp2515.h"

/* Read CAN register */
uint8_t can_read(uint8_t adr){
	uint8_t data;	
	
	spi_enslaved_can();
	spi_transmit(MCP_READ);
	spi_transmit(adr);
	data = spi_recive();
	spi_release_can();
	
	return data;	
}

/* Write to CAN register */
void can_write(uint8_t adr, uint8_t data){
	spi_enslaved_can();
	spi_transmit(MCP_WRITE);
	spi_transmit(adr);
	spi_transmit(data); 
	spi_release_can();		
}

/* Modify single bit in CAN register */
void can_bit_modify(uint8_t reg, uint8_t mask, uint8_t bit){
	spi_enslaved_can();
	spi_transmit(MCP_BITMOD);
	spi_transmit(reg);
	spi_transmit(mask);
	spi_transmit(bit);
	spi_release_can();
}

/* CAN request to send message */
void can_request_to_send(uint8_t request_to_send){
	spi_enslaved_can();
	spi_transmit(request_to_send);
	spi_release_can();	
}
/* Read CAN status register */
uint8_t can_read_status(void){
	uint8_t data;
		
	spi_enslaved_can();
	spi_transmit(MCP_READ_STATUS);
	data = spi_recive();
	spi_release_can();
		
	return data;	
}

/* CAN controller SW reset */
void can_sw_reset(void){
	spi_enslaved_can();
	spi_transmit(MCP_RESET);
	spi_release_can();
}

/* CAN init */
uint8_t can_init(void){
	uint8_t error_check;	
	can_sw_reset();
	_delay_ms(10);
	
	// Set config mode
	error_check = can_read(MCP_CANSTAT);
	if((error_check & MODE_MASK) != MODE_CONFIG){
		return 1;
	}		
	
	// Configure MCP 2515
	can_write(MCP_CNF3, 0x05);		//see can config sheet on github
	can_write(MCP_CNF2, 0xb1);		//see can config sheet on github
	can_write(MCP_CNF1, 0x03);		//see can config sheet on github
	can_write(MCP_CANINTE, MCP_RX_INT); //Turn on RX interrupt	
	
	// Set normal mode
	can_bit_modify(MCP_CANCTRL, MODE_POWERUP, MODE_NORMAL);
		error_check = can_read(MCP_CANSTAT);
		if((error_check & MODE_MASK) != MODE_NORMAL){
			return 1;
		}	
	return 0;
}

/* Send can message from mailbox 0 */
void can_message_send(struct can_message* msg){	
	uint8_t i;
	
	// set message id
	can_write(MCP_TXB0SIDH, msg->id /  8);
	can_write(MCP_TXB0SIDL, (msg->id % 8) << 5);

	// set message length 
	can_write(MCP_TXB0DL, msg->data_length);
	
	// transfer data
	for(i = 0; i < msg->data_length; i++){
		can_write(MCP_TXB0D0 + i, msg->data[i]);		
	}
	can_request_to_send(MCP_RTS_TX0);
}

/* Receive CAN message from mailbox 0 or 1 */
can_message can_message_receive(uint8_t mailbox){
	can_message msg = {};
	uint8_t mailbox_offset = 0;
	if(mailbox == 1)
	{
		mailbox_offset = 10;
	}
	// read message id
	msg.id = (can_read(MCP_RXB0SIDH  + mailbox_offset) * 8) + (can_read(MCP_RXB0SIDL + mailbox_offset) >> 5);

	// read data length
	msg.data_length = can_read(MCP_RXB0DL + mailbox_offset);
	
	// read data
	if(msg.data_length > 8){
		msg.data_length = 8;
	}
	for (uint8_t i = 0; i < msg.data_length; i++) {
		msg.data[i] = can_read(MCP_RXB0D0 + mailbox_offset + i);
	}
	// reset int RX1 flag
	can_bit_modify(MCP_CANINTF, (MCP_RX0IF  + mailbox), 0);
	return msg;
}

/* Check mailbox receive interrupt flags */
void can_mailbox(void){
	uint8_t int_flag = can_read(MCP_CANINTF);
	can_mailbox_0_recive_flag = (int_flag & MCP_RX0IF);
	can_mailbox_1_recive_flag = (int_flag & MCP_RX1IF);
}
