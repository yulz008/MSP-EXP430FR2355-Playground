#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//-- Setup SPI A0
	UCA0CTLW0 |= UCSWRST;        // put A0 into SW Reset

	UCA0CTLW0 |= UCSSEL__SMCLK;  // Choose SMCLK
	UCA0BRW = 10;               // set prescalar to 10 to get SCLK = 1M/10 = 100KHz

	UCA0CTLW0 |= UCSYNC;        // PUt A0 into SPI Mode
	UCA0CTLW0 |= UCMST;         // put into SPI Master

	//-- Configure the ports
	P1SEL1 &= ~BIT5;                    //P1.5 use SCLK (01)
	P1SEL0 |= BIT5;

    P1SEL1 &= ~BIT7;                   //P1.7 use SIMO (01)
	P1SEL0 |= BIT7;

	P1SEL1 &= ~BIT6;                    //P1.6 use SOMI (01)
	P1SEL0 |= BIT6;

	PM5CTL0 &= ~LOCKLPM5;           // Turn on I/O

	UCA0CTLW0 &= ~UCSWRST;           // take A0 out of SW Reset

	int i;
	while(1)
	{
	    UCA0TXBUF = 0x4D;           // send x4D out over SPI
	    for (i=0; i<10000; i++) {}  // delay
	}
	return 0;
}
