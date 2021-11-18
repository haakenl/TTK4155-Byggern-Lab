/*
 * io.h
 *
 * Created: 23.10.2021 15:18:08
 *  Author: haakenl
 */ 


#ifndef IO_H_
#define IO_H_

#include <avr/io.h>

#define button_reg DDRB
#define button_port PORTB
#define button_joy_port_bit PINB1
#define button_pin PINB
#define button_joy_bit PB1
#define button_rigth_bit PB3
#define button_left_bit PB2

#define adc_clk_reg DDRB
#define adc_clk_pin PB0

#define spi_can_reg DDRB
#define spi_can_port PORTB
#define spi_can_ss PINB4
#define spi_mosi PINB5
#define spi_miso PINB6
#define spi_sck PINB7

#define spi_ext_reg DDRD
#define spi_ext_port PORTD
#define spi_ss_bit PIND3

#define led_reg DDRD
#define led_port PORTD
#define led_error PIND5
#define led_normal PIND4

#define can_int_flag_reg PIND
#define can_int_flag_bit PD2


#define set_bit(reg, bit) (reg |= (1 << bit))
#define clear_bit(reg, bit) (reg &= ~(1 << bit))
#define test_bit(reg, bit) (reg & (1 << bit))
//#define loop_until_bit_is_set(reg, bit) while(!test_bit(bit,reg))
//#define loop_until_bit_is_clear(reg, bit) while(test_bit(reg, bit))

void io_init(void);


#endif /* IO_H_ */
