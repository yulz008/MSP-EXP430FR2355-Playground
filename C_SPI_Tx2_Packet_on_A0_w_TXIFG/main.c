#include <msp430.h> 


char packet [] = {0xDE, 0xAD, 0xBE, 0xEF};
unsigned int position;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	

	//-- Setup A0 for SPI

	UCA0CTLW0 |= UCSWRST;       // put A0 into SW Reset

	UCA0CTLW0 |= UCSSEL__SMCLK; // choose SMCLK
	UCA0BRW = 10;               // Set Prescalar to 10 to get SCLK = 100khz

	UCA0CTLW0 |= UCSYNC;        // Put A0 into SPI mode
	UCA0CTLW0 |= UCMST;         // put into SPI Master


	//-- Configure the ports

	P4DIR &= ~BIT1;             // make p4.1 an input (SW1)
	P4REN |= BIT1;              // enable resistor
	P4OUT |= BIT1;              // make a resistor pullup
	P4IES |= BIT1;              // sensitive to H-to-L


	P1SEL1 &= ~BIT5;             // P1.5 = SCLK (01)
	P1SEL0 |= BIT5;

	P1SEL1 &= ~BIT7;             // P1.7 = SIMO (01)
	P1SEL0 |= BIT7;

	P1SEL1 &= ~BIT6;             // P1.6 = SOMI (01)
	P1SEL0 |= BIT6;

	PM5CTL0 &= ~LOCKLPM5;       // turn on I/O


    UCA0CTLW0 &= ~UCSWRST;       // put A0 out of SW Reset


    //-- Enable IRQ
    P4IE |= BIT1;               // enable P4.1 IRQ
    P4IFG &= ~BIT1;             // Clear flag

    UCA0IE |= UCTXIE;           // enable A0 Tx IRQ
    UCA0IFG &= ~UCTXIFG;        // clear flag


    __enable_interrupt();       // enable global

    while(1){}

	return 0;
}

//--------------------------------------------------
//-- ISR

#pragma vector = PORT4_VECTOR
__interrupt void ISR_Port4_S1(void)
{
    position = 0;
    UCA0TXBUF = packet[position]; // send first byte

    P4IFG &= ~BIT1;
}

#pragma vector = EUSCI_A0_VECTOR
__interrupt void ISR_EUSCI_A0(void)
{
    position++;

    if (position <sizeof(packet))
    {
        UCA0TXBUF = packet[position];
    }
    else
    {
        UCA0IFG &= ~UCTXIFG;
    }

}
