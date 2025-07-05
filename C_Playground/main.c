#include <msp430.h>

int main(void) {
    //-- Setup General I/O
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;        // Disable the LOW POWER mode

    //-- Route MCLK to pin P3.0
    P3DIR |= BIT0;               // Make P3.0 an OUTPUT
    P3SEL1 &= ~BIT0;
    P3SEL0 |= BIT0;              // Switch P3.0 to MCLK

    //-- Change MCLK to 24MHz
    CSCTL1 |= DCORSEL_6;         // Change DCO Range to 24MHz (DCORSEL_5 for high-frequency range)

    CSCTL2 &= ~FLLD_1;           // Change FLLD to divide by 1
    CSCTL2 &= ~FLLN;             // Clear FLLN bits
    CSCTL2 |= 731;               // Set FLLN equal to 731 (for 24MHz)

    // Wait for the DCO to stabilize
    while (CSCTL7 & (FLLUNLOCK0 | FLLUNLOCK1)); // Wait for FLL to lock

    while(1){}                   // Loop forever

    return 0;
}
