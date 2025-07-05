#include <msp430.h>
#include <stdio.h>

/**
 * main.c
 */

volatile unsigned char rxByte = 0;  // Variable to store the received byte

// UART interrupt service routine for receiving data
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
    switch(__even_in_range(UCA1IV, 4))
    {
        case 0: break;  // No interrupt
        case 2: // RX interrupt
            rxByte = UCA1RXBUF;  // Read received byte
            printf("Received: 0x%02X\n", rxByte);  // Print to CCS console
            break;
        default: break;
    }
}

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;    // Stop the watchdog timer

    // -- Setup the UART
    UCA1CTLW0 |= UCSWRST;        // Put UART A1 into SW reset

    UCA1CTLW0 |= UCSSEL__SMCLK;  // Choose SMCLK for UART A1
    UCA1BRW = 8;                 // Set Prescaler to 8
    UCA1MCTLW = 0xD600;          // Configure modulation settings + low freq

    // -- Setup Ports
    P4SEL1 &= ~BIT3;             // P4SEL1.3 : P4SEL0.3 = 01 (TX on P4.3)
    P4SEL0 |= BIT3;              // Configure TX

    P4SEL1 &= ~BIT4;             // P4SEL1.4 : P4SEL0.4 = 01 (RX on P4.4)
    P4SEL0 |= BIT4;              // Configure RX

    PM5CTL0 &= ~LOCKLPM5;        // Turn on I/O

    // Enable RX interrupt
    UCA1CTLW0 &= ~UCSWRST;       // Put UART A1 into SW reset
    UCA1IE |= UCRXIE;            // Enable receive interrupt

    __bis_SR_register(GIE);      // Enable global interrupts

    // ---------- Main loop
    while(1)
    {
        // Send the 4 bytes of 0xDEADBEEF
        UCA1TXBUF = 0xDE;         // Send the most significant byte (0xDE)
        while (!(UCA1IFG & UCTXIFG)); // Wait until buffer is ready for next byte

        UCA1TXBUF = 0xAD;         // Send the next byte (0xAD)
        while (!(UCA1IFG & UCTXIFG)); // Wait until buffer is ready for next byte

        UCA1TXBUF = 0xBE;         // Send the next byte (0xBE)
        while (!(UCA1IFG & UCTXIFG)); // Wait until buffer is ready for next byte

        UCA1TXBUF = 0xEF;         // Send the least significant byte (0xEF)
        while (!(UCA1IFG & UCTXIFG)); // Wait until buffer is ready for next byte

        // Add a delay between frames
        volatile int i;
        for(i = 0; i < 30000; i++) {}
    }

    return 0;
}
