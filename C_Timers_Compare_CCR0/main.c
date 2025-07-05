#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//-- setup of the ports
	P1DIR |= BIT0;              // set P1.0 to output (LeD1)
	P1OUT &= ~BIT0;             // clears output initially
	PM5CTL0 &= ~LOCKLPM5;       // turn on digital IO

	//-- setup timer
	TB0CTL |= TBCLR;            // resets tB0
	TB0CTL |= MC__UP;           // set to up mode for CCR0
	TB0CTL |= TBSSEL__ACLK;     // choose ACLK (32Khz)
	TB0CCR0 = 16384;            // set CCR0 =16384

	//-- setup the Timer Compare IRQs
	TB0CCTL0 |= CCIE;           // Local enable for CCR0
	__enable_interrupt();       // enable maskables.
	TB0CCTL0 &= ~CCIFG;         // clear the flag

	// -- main loop
	while(1){}                  // Loop forever

	return 0;
}

// --- ISRs --------------------
#pragma vector = TIMER0_B0_VECTOR
__interrupt void TB0_CCR0(void)
{
    P1OUT ^= BIT0;              // toggle LED1
    TB0CCTL0 &= ~CCIFG;         // clear the flag
}
