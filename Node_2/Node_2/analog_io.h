/*
 * analog_iO.h
 *
 * Created: 23.10.2021 11:45:09
 *  Author: haakenl
 */ 


#ifndef ANALOG_IO_H_
#define ANALOG_IO_H_

#include "sam.h"

#define Read_IR_VALUE ADC -> ADC_CDR[7]
#define Read_IR_LAST_VALUE ADC ->ADC_LCDR 


void analog_io_init(void);
uint8_t ir_detection(uint16_t threshold);
void set_analog_value(uint16_t value);


#endif /* ANALOG_IO_H_ */
