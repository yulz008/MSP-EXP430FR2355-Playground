#include <msp430.h> 

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//-- Setup Ports
	P1DIR |= BIT0;              //  set PORT1.0 as output LED
	P1OUT &= ~BIT0;             // clear output
	PM5CTL0 &= ~LOCKLPM5;       // turn on GPIO

	//-- Setup Timer
	TB0CTL |= TBCLR;            // Reset timer
	TB0CTL |= TBSSEL__ACLK;     // set source clock as ACLK
	TB0CTL |= MC__CONTINUOUS;   // Mode= Continuous

	//-- Setup the Timer Overflow IRQ
	TB0CTL |= TBIE;             // local enable for TB0 overflow
	__enable_interrupt();       // enable maskable IRQs
	TB0CTL &= ~TBIFG;           // clear IRQ flag


	// -- Main Loop
	while(1){}                  // Loop forever

	return 0;
}

//--- ISRs -----//

#pragma vector = TIMER0_B1_VECTOR
__interrupt void ISR_TB0_Overflow(void)
{
    P1OUT ^= BIT0;              // Toggle LED1
    TB0CTL &= ~TBIFG;           // clear IRQ flag
}

//! This is a service routine not a subroutine
// ISR returns to the main program together with the PC and the Status Registers
