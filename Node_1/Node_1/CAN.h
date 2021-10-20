/*
 * CAN.h
 *
 * Created: 06.10.2021 09:57:56
 *  Author: haakenl
 */ 


#ifndef CAN_H_
#define CAN_H_


typedef struct can_message{
	uint16_t id;
	uint8_t data_length;
	char data[8];
	}can_message;

uint8_t CAN_read(uint8_t adr);
void CAN_write(uint8_t adr, uint8_t data);
void CAN_bit_modify(uint8_t reg, uint8_t mask, uint8_t bit);
void CAN_request_to_send(uint8_t request_to_send);
uint8_t CAN_read_status(void);
void CAN_sw_reset(void);

uint8_t CAN_init(void);
void CAN_message_send(struct can_message* msg);
can_message CAN_message_receive(void);
void CAN_clear_RX0IF(void);

#endif /* CAN_H_ */