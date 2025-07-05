#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// -- Setup ports
	P1DIR |= BIT0;          // set P1.0 to output (LED1)
	P1OUT &= ~BIT0;         // clear P1.0 initially (LED1)
	PM5CTL0 &= ~LOCKLPM5;   // turn  on digital IO

	// -- Setup timer TB0
	TB0CTL |= TBCLR;            // reset TB0
	TB0CTL |= TBSSEL__SMCLK;    // SMCLK as a source
	TB0CTL |= MC__CONTINUOUS;   // mode = continuous

	// -- Setup overflow IRQ
	TB0CTL |= TBIE;             // local enable for overflow on TB0
	__enable_interrupt();       // global enable for maskable IRQa
	TB0CTL &= ~TBIFG;           // clear the flag

	// -- Main Loop
	while(1){}                  // Loop forever
	return 0;
}

// -----   ISRs ------
#pragma vector = TIMER0_B1_VECTOR
__interrupt void ISR_TB0_Overflow(void)
{
    P1OUT ^= BIT0;              // toggle the LED P1.0
    TB0CTL &= ~TBIFG;           // clear the flag
}

