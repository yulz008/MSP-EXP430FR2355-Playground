#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//-- setup ports
	P1DIR |= BIT0;              // set P1.0 as output LED1
	P1OUT |= BIT0;              // set LED1=1 initially
	PM5CTL0 &= ~LOCKLPM5;       // turn on digital IO


	//-- setup timer B0
	TB0CTL |= TBCLR;            // reset TB0
	TB0CTL |= MC__UP;           // put into UP mode for CCR0
	TB0CTL |= TBSSEL__ACLK;     // choose ACLK (32khz)
	TB0CCR0 = 32768;            // set PWM period
	TB0CCR1 = 1638;             // set PWM duty cycle


	//-- setup IRQs
	TB0CCTL0 |= CCIE;           // local enable for CCR0
	TB0CCTL1 |= CCIE;           // local enable for CCR1
	__enable_interrupt();       // enable maskable interrupts..
	TB0CCTL0 &= ~CCIFG;         // clear the flag for CCR0;
	TB0CCTL1 &= ~CCIFG;         // clear the flag for CCR1;

	//-- main loop
	while(1){}                  // loop forever

	return 0;
}

//--------------Interrupt Service Routines -------------------//
#pragma vector = TIMER0_B0_VECTOR  // ISR for period
// return with reti not ret thus _interrupt identifier
__interrupt void ISR_TB0_CCR0(void)
{
    P1OUT |= BIT0;          // Turn LED1 on
    TB0CCTL0 &= ~CCIFG;     // clear the flag for CCR0
}


#pragma vector = TIMER0_B1_VECTOR  // ISr for duty cycle
// return with reti not ret thus _interrupt identifier
__interrupt void ISR_TB0_CCR1(void)
{
    P1OUT &= ~BIT0;         // turn LED1 off
    TB0CCTL1 &= ~CCIFG;         // clear the flag for CCR1;
}
