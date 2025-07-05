#include <msp430.h> 

int WhatICaptured=0;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//-- Setup Ports
	P1DIR |= BIT0;          // Set p1.0 as output (LED1)
	P1OUT &= ~BIT0;         // clear the output initially

	P4DIR &= ~BIT1;         // set P4.1 to input (SW1)
	P4REN |= BIT1;          // enable resistor on P4.1
	P4OUT |= BIT1;          // make resistor a pull up
	P4IES |= BIT1;          // set IRQ sensitivity to H-to-L

	PM5CTL0 &= ~PM5CTL0;    // turn on digital I/O

	//-- Setup port IRQ
	P4IE  |= BIT1;          // local enable for P4.1
	__enable_interrupt();   // enable maskable IRQs
	P4IFG &= ~BIT1;         // clear flag

	//-- Setup Timer
	TB0CTL |= TBCLR;            // reset the timer
	TB0CTL |= MC__CONTINUOUS;   // put into continuous mode
	TB0CTL |= TBSSEL__ACLK;     // choose ACLK
	TB0CTL |= ID__8;            // div-by-8 in pre-scalar

	//-- Setup Capture
	TB0CCTL0 |= CAP;            // put into capture mode
	TB0CCTL0 |= CM__BOTH;       // sensitivity to both edges
	TB0CCTL0 |= CCIS__GND;      // put capture input level at the GND



	while(1){}

	return 0;
}

//----------ISRs-----------------//
#pragma vector = PORT4_VECTOR
__interrupt void ISR_Port4_SW1(void)
{
    P1OUT ^= BIT0;              // Toggle LED
    TB0CCTL0 ^= CCIS0;          // switch back and forth between GND and VCC
    WhatICaptured = TB0CCR0;    // store off captured value
    P4IFG &= ~BIT1;             // clear P4.1 flag
}


