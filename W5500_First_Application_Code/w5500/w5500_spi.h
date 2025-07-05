/*
 * w5500_spi.h
 *
 *  Created on: May 19, 2025
 *      Author: Ulysses Andulte
 */

#ifndef W5500_W5500_SPI_H_
#define W5500_W5500_SPI_H_

#include <stdint.h>

void W5500Init();

void  wizchip_select(void);
void  wizchip_deselect(void);

uint8_t wizchip_read();
void  wizchip_write(int wb);

void wizchip_readburst(uint8_t* pBuf, uint16_t len);
void  wizchip_writeburst(uint8_t* pBuf, uint16_t len);

#endif /* W5500_W5500_SPI_H_ */
