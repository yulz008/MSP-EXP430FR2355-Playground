#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	// -- Setup UART A1 (Tx)
	UCA1CTLW0 |= UCSWRST;       // put UART A1 into SW Reset

	UCA1CTLW0 |= UCSSEL__SMCLK;  // BRCLK = SMCLK (1MHZ)
	UCA1BRW = 8;                // Prescalar = 8
	UCA1MCTLW = 0xD600;          // setup modulation

	P4SEL1 &= ~BIT3;            // P4.3 = UART A1 TX
	P4SEL0 |= BIT3;

	PM5CTL0 &=  ~LOCKLPM5;       // turn on I/O

	UCA1CTLW0 &= ~UCSWRST;       // put UART A1 into SW Reset

	char message[] = "Hello World ";

	int position;
	int i,j;

	while(1)
	{
	    for(position = 0; position < sizeof(message); position++)
	    {
	        UCA1TXBUF = message[position];
	        for(i=0;i<100;i++){} //delay between characters
	    }

	    for(j=0; j<30000;j++){}  //delay between strings

	}
	return 0;
}
