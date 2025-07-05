#include <msp430.h> 


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//----- Setup ports


	P1DIR |= BIT0;     // Config P1.0 to an output  (LED1)
	P1OUT &= ~BIT0;    // Clear P1.0 initially (LED1)

	P4DIR &= ~BIT1;    // Config P4.1 as input (SW1)
	P4REN  |= BIT1;    // Enable resistor
	P4OUT  |= BIT1;    // Make Resistor a pull up
	P4IES  |= BIT1;    // Makes sensitivity H-to-L

	P2DIR &= ~BIT3;    // Config P2.3 as input (SW1)
	P2REN  |= BIT3;    // Enable resistor
	P2OUT  |= BIT3;    // Make Resistor a pull up
	P2IES  |= BIT3;    // Makes sensitivity H-to-L



	PM5CTL0 &= ~LOCKLPM5;   //Turn on Digital I/O

	//----- Setup IRQ
	P4IE  |= BIT1;          // Enable P4.1 IRQ
	P2IE  |= BIT3;          // Enable P2.3 IRQ

	__enable_interrupt();   // enables Maskable IRQs
	P4IFG &= ~BIT1;         // clear P4.1 IRQ flag
	P2IFG &= ~BIT3;         // clear P2.3 IRQ flag

	while(1){}              // Loop forever

	return 0;
}

//---- ISRs ---------------------------------------------//
#pragma vector = PORT4_VECTOR       // this tells the next line address will be put into the
                                    // Por4_Vector
__interrupt void ISR_Port4_S1(void)
{
    P1OUT ^= BIT0;          // Toggle LED
    P4IFG &= ~BIT1;         // clear P4.1 IRQ flag

}

#pragma vector = PORT2_VECTOR       // this tells the next line address will be put into the
                                    // Por2_Vector
__interrupt void ISR_Port2_S2(void)
{
    P1OUT ^= BIT0;          // Toggle LED
    P2IFG &= ~BIT3;         // clear P2.3 IRQ flag

}

