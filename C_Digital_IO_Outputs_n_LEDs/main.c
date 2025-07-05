#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// --- Setup Ports
	P1DIR |= BIT0;          // Configure P1.0 (LED1) as output
	P1OUT &= ~BIT0;         // Initialize LED to off
	PM5CTL0 &= ~LOCKLPM5;   // Turn on GPIO system

	int i = 0;
	// infinite Loop
	while(1)
	{
        P1OUT ^= BIT0;      // toggle LED1
        for(i=0; i < 0xFFFF; i++)
           {
            // do nothing
           }
	}

	return 0;
}
