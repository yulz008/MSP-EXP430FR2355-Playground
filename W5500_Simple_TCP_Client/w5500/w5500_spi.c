#include <msp430.h>
#include <stdint.h>
#include "wizchip_conf.h"
#include <stdio.h>

// Function Prototypes
uint8_t SPIReadWrite(uint8_t data);
void wizchip_select(void);
void wizchip_deselect(void);
uint8_t wizchip_read();
uint8_t wizchip_write(uint8_t wb);
void wizchip_readburst(uint8_t* pBuf, uint16_t len);
void wizchip_writeburst(uint8_t* pBuf, uint16_t len);
void W5500IOInit();
void W5500Init();

// SPI Single Byte Read/Write (Full Duplex)
uint8_t SPIReadWrite(uint8_t data) {
    while (!(UCA0IFG & UCTXIFG)); // Wait until TX buffer is ready
    UCA0TXBUF = data;             // Send data
    while (!(UCA0IFG & UCRXIFG)); // Wait for RX complete
    return UCA0RXBUF;             // Return received byte
}

// Chip Select Low
void wizchip_select(void) {
    P1OUT &= ~BIT3;
}

// Chip Select High
void wizchip_deselect(void) {
    P1OUT |= BIT3;
}

// Read Single Byte (Dummy write)
uint8_t wizchip_read() {
    return SPIReadWrite(0x00);
}

// Write Single Byte
uint8_t wizchip_write(uint8_t wb) {
    SPIReadWrite(wb);
    return 0; // Optional: return unused
}

// Burst Read
void wizchip_readburst(uint8_t* pBuf, uint16_t len) {
    int i = 0;
    for (i = 0; i < len; i++) {
        *pBuf++ = SPIReadWrite(0x00);
    }
}

// Burst Write
void wizchip_writeburst(uint8_t* pBuf, uint16_t len) {

    int i = 0;
    for (i = 0; i < len; i++) {
        SPIReadWrite(*pBuf++);
    }
}

// W5500 GPIO Initialization (CS, RESET)
void W5500IOInit() {
    // CS: P1.3, RESET: P1.2
    P1DIR |= BIT2 | BIT3;
    P1OUT |= BIT3;   // CS high
    P1OUT |= BIT2;   // RESET high

    // SPI Setup: UCB0 (P1.5 = SCLK, P1.6 = MISO, P1.7 = MOSI)
    P1SEL0 |= BIT5 | BIT6 | BIT7;
    P1SEL1 &= ~(BIT5 | BIT6 | BIT7);

    UCA0CTLW0 = UCSWRST;                      // Put eUSCI in reset
    UCA0CTLW0 |= UCSSEL__SMCLK | UCSYNC | UCMST | UCMSB | UCCKPH; // SPI Master, 3-pin, MSB, mode 0
    UCA0BRW = 2;                              // Clock prescaler (SMCLK/2)
    UCA0CTLW0 &= ~UCSWRST;                    // Release reset
    UCA0IE &= ~(UCRXIE | UCTXIE);             // Disable interrupts (polling)

    PM5CTL0 &= ~LOCKLPM5;
}

// Main Initialization
void W5500Init() {
    uint8_t tmp;
    uint8_t memsize[2][8] = {
        {2, 2, 2, 2, 2, 2, 2, 2},
        {2, 2, 2, 2, 2, 2, 2, 2}
    };

    W5500IOInit();


    /*I need to edit some values so the initialization of reset and CS are alignned for it to work
     * On the working STM32 waveform both the CS and the Reset  asert to zero and transitio back to 1 at the same time
     * Need to replicate that waveform, cause my init code is not working.... */

    // CS high by default
    wizchip_select();

    // Reset W5500
    P1OUT &= ~BIT2; // RESET low
    int i = 0;
    for (i = 0; i < 1000; i++); // Delay
    P1OUT |= BIT2;  // RESET high
    wizchip_deselect();

    // Register callbacks
    reg_wizchip_cs_cbfunc(wizchip_select, wizchip_deselect);
    reg_wizchip_spi_cbfunc(wizchip_read, wizchip_write);
    reg_wizchip_spiburst_cbfunc(wizchip_readburst, wizchip_writeburst);

    int res_init = ctlwizchip(CW_INIT_WIZCHIP, (void*) memsize);
    if (res_init == -1) {
        printf("WIZCHIP Initialized Failed.\r\n");
        while (1);
    }
    printf("WIZCHIP Initialization Success.\r\n");
}
