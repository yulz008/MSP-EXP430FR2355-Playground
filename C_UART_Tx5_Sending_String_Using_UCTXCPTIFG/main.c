#include <msp430.h> 


/**
 * main.c
 */

char message[] = "Hello World ";
unsigned int position;


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//-- setup the UART A1
	UCA1CTLW0 |= UCSWRST;       // put UART A1 into SW reset

	UCA1CTLW0 |= UCSSEL__SMCLK; // BRCLK = SMCLK --> 115200 baud
	UCA1BRW = 8;                // prescalar = 0
	UCA1MCTLW = 0xD600;         // set low-freq mode +2nd mod stage

	// -- configure ports
	P4DIR &= ~BIT1;             // Make P4.1 in input (SW1)
	P4REN |= BIT1;              // Enables resistor
	P4OUT |= BIT1;              // Make it a pull UP
	P4IES |= BIT1;              // Make IRQ sens H-to-L


	P4SEL1 &= ~BIT3;            // Set P4.3 to use UART A1 Tx function
	P4SEL0 |= BIT3;

	PM5CTL0 &= ~LOCKLPM5;        // turn on I/O


	UCA1CTLW0 &= ~UCSWRST;       // take UART A1 out of SW reset

	// Enable IRQs
	P4IE |= BIT1;               // enables SW1 IRQ
	P4IFG &= ~BIT1;             // clears flag
	__enable_interrupt();       // global en IRQ


	while(1){}

	return 0;
}

//--------------------------------------------------
//-------------------------------------------------
//--- ISRs

#pragma vector = PORT4_VECTOR
__interrupt void ISR_Port4_S1(void)
{
    position = 0;
    UCA1IE |= UCTXCPTIE;                // turns on TX complete IRQ
    UCA1IFG &= ~UCTXCPTIFG;             // clears TX complete flag
    UCA1TXBUF = message[position];      // put first char from message into TX buf

    P4IFG &= ~BIT1;                     // clear flag for P4.1
}

#pragma vector = EUSCI_A1_VECTOR
__interrupt void ISR_EUSCI_A1(void)
{
   if (position == sizeof(message))
   {
        UCA1IE &= ~UCTXCPTIE;             // turns off TX complete IRQ
   }
   else
   {
        position++;
        UCA1TXBUF = message[position];      // put next char into Tx Buff
   }

   UCA1IFG &= ~UCTXCPTIFG;                // Clear the tx complete flag
}

