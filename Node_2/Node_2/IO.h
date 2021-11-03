/*
 * IO.h
 *
 * Created: 10/13/2021 1:20:51 PM
 *  Author: HLunn
 */ 


#ifndef IO_H_
#define IO_H_

#include "sam.h"

/* Set up LEDS */
#define set_orange_LED PIOA -> PIO_SODR |= PIO_SODR_P19;	// Set P19 (D1)
#define clear_orange_LED PIOA -> PIO_CODR |= PIO_SODR_P19;	// Clear P19 (D1)
#define set_green_LED	PIOA -> PIO_SODR |= PIO_SODR_P20;	// Set P20 (D2)
#define clear_green_LED PIOA -> PIO_CODR |= PIO_SODR_P20;	// Clear P20 (D3)

/* Set up Solenoid */
#define deactivate_solenoid	PIOC -> PIO_SODR |= PIO_SODR_P12;	// Set P12 (solenoid)
#define activate_solenoid PIOC -> PIO_CODR |= PIO_SODR_P12;		// Clear P12 (solenoid)


/* Set up MJ1 */
#define disable_encoder	PIOD -> PIO_SODR |= PIO_SODR_P0;	// !OE enable encoder (Pin3)
#define enable_encoder PIOD -> PIO_CODR |= PIO_SODR_P0;		// !OE disable encoder (Pin3)
#define disable_encoder_reset PIOD -> PIO_SODR |= PIO_SODR_P1;	// !RST disable encoder (Pin4)
#define enable_encoder_reset PIOD -> PIO_CODR |= PIO_SODR_P1;	// !RST enable encoder (Pin4)
#define sel_LSB_encoder	PIOD -> PIO_SODR |= PIO_SODR_P2;	// SEL LSB encoder (Pin5)
#define sel_MSB_encoder PIOD -> PIO_CODR |= PIO_SODR_P2;	// SEL MSB encoder (Pin5)
#define enable_motor PIOD -> PIO_SODR |= PIO_SODR_P9;		// Enable motor (Pin6)
#define disable_motor PIOD -> PIO_CODR |= PIO_SODR_P9;		// disable motor (Pin6)
#define set_neg_motor_dir PIOD -> PIO_SODR |= PIO_SODR_P10;		// set pos dir motor (Pin7)
#define set_pos_motor_dir PIOD -> PIO_CODR |= PIO_SODR_P10;		// set neg dir motor (Pin7) Må muligens snus!

/* Set up MJ2 */
#define read_encoder_mask PIOC -> PIO_PDSR & 0x1FE			// read encoder data mask

void IO_Init(void);

#endif /* IO_H_ */