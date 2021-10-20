/*
 * SPI.h
 *
 * Created: 06.10.2021 09:14:57
 *  Author: haakenl
 */ 


#ifndef SPI_H_
#define SPI_H_

#define SPI_CAN_SS PINB4
#define SPI_MOSI PINB5
#define SPI_MISO PINB6
#define SPI_SCK PINB7

void SPI_MasterInit(void);
void SPI_transmit(char cData);
char SPI_recive(void);
void SPI_enslaved_CAN(void);
void SPI_release_CAN(void);


#endif /* SPI_H_ */