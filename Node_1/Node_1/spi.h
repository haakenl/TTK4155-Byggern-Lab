/*
 * spi.h
 *
 * Created: 06.10.2021 09:14:57
 *  Author: haakenl
 */ 


#ifndef SPI_H_
#define SPI_H_

void spi_master_init(void);
void spi_transmit(char cData);
char spi_recive(void);
void spi_enslaved_can(void);
void spi_release_can(void);


#endif /* SPI_H_ */
