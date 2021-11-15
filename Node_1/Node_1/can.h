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
	char data_length;
	char data[8];
	}can_message;

uint8_t can_read(uint8_t adr);
void can_write(uint8_t adr, uint8_t data);
void can_bit_modify(uint8_t reg, uint8_t mask, uint8_t bit);
void can_request_to_send(uint8_t request_to_send);
uint8_t can_read_status(void);
void can_sw_reset(void);

uint8_t can_init(void);
void can_message_send(struct can_message* msg);
can_message can_message_receive(uint8_t mailbox);
void can_clear_RX0IF(void);
void can_mailbox(void);

uint8_t can_mailbox_0_recive_flag;
uint8_t can_mailbox_1_recive_flag;

#endif /* CAN_H_ */
