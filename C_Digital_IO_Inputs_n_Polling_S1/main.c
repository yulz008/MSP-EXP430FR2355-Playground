#include <msp430.h> 

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//--Setup Ports
	P1DIR |= BIT0;        // Set P1.0 to an output
	P1OUT &= ~BIT0;       // clear LED1

	P4DIR &= ~BIT1;      // Set P4.1 to input (SW1)
	P4REN |= BIT1;       // Enables Resistor
	P4OUT |= BIT1;       // Sets Resistor to PullUp

	PM5CTL0 &= ~LOCKLPM5;    // turn on Digital IO

	int SW1;
	int i = 0;

	while(1)
	{
	    SW1 = P4IN;         // Read Port4
	    SW1 &= BIT1;        // clear all bits except SW1
	    if (SW1 == 0)
	    {
	        //P1OUT |= BIT0;
	        P1OUT ^= BIT0;
	    }

	    /*
	    else
	    {
	        P1OUT &= ~BIT0;
	    }
	    */



	    for (i=0; i<30000; i++)
	    {
	        //do nothing
	    }

	}


	return 0;
}
