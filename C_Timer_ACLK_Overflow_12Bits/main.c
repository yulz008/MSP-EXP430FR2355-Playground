#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//--- setup ports
	P1DIR |= BIT0;              // set P1.0 as output LED1
	P1OUT &= ~BIT0;             // clear the P1.0 initially
	PM5CTL0 &= ~LOCKLPM5;       // turn on digital I/O

	//--- setup timer
	TB0CTL |= TBCLR;            // reset timer
	TB0CTL |= TBSSEL__ACLK;     // ACLK as source
	TB0CTL |= MC__CONTINUOUS;  // puts timer into continuous mode
	TB0CTL |= CNTL_1;           // 12-bit length

	//--- setup timer IRQ
	TB0CTL |= TBIE;             // local enable for overflow
	__enable_interrupt();       // global enable GIE in ISR
	TB0CTL &= ~TBIFG;           // clear the flag

	//--- main loop
	while(1){}                  // loop forever

	return 0;
}

// ----------ISRs-------------------------
#pragma vector = TIMER0_B1_VECTOR
__interrupt void ISR_TB0_Overflow(void)
{
    P1OUT ^= BIT0;              // toggle LED1
    TB0CTL &= ~TBIFG;           // clear the flag
}
