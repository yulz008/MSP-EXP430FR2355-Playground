#include <msp430.h> 

int Rx_Data;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//-- Setup A0 SPI
	UCA0CTLW0 |= UCSWRST;       // put A0 into SW reset

	UCA0CTLW0 |= UCSSEL__SMCLK; // choose SMCLK=1mhz
	UCA0BRW = 10;               // set prescale=10 to get SCLK=100khz

	UCA0CTLW0 |= UCSYNC;        // put into SPI
	UCA0CTLW0 |= UCMST;         // set as master

	//--Configure Ports
	P1DIR |= BIT0;              // set P1.0 (led1) to output
	P1OUT &= ~BIT0;             // LED1=OFF initially

	P6DIR |= BIT6;              // set P6.6 (led2) to output
	P6OUT &= ~BIT6;             // LED2=OFF initially

	P4DIR &= ~BIT1;             // set P4.1 (SW1) to input
	P4REN |= BIT1;              // turn on resistor
	P4OUT |= BIT1;              // makes resistor pullup
	P4IES |= BIT1;              // make sensitive to H-to-L


    P2DIR &= ~BIT3;             // set P2.3 (SW2) to input
    P2REN |= BIT3;              // turn on resistor
    P2OUT |= BIT3;              // makes resistor pullup
    P2IES |= BIT3;              // make sensitive to H-to-L


    P1SEL1 &= ~BIT5;            // P1.5 = SCLK (P1SEL1:P1SEL0 = 01)
    P1SEL0 |= BIT5;

    P1SEL1 &= ~BIT7;            // P1.7 = SIMO (P1SEL1:P1SEL0 = 01)
    P1SEL0 |= BIT7;

    P1SEL1 &= ~BIT6;            // P1.6 = SOMI (P1SEL1:P1SEL0 = 01)
    P1SEL0 |= BIT6;

    PM5CTL0 &= ~LOCKLPM5;       // turn on IO

    UCA0CTLW0 &= ~UCSWRST;      // take A0 out of SW reset


    //-- SETUP IRQs
    P4IE |= BIT1;               // enable P4.1 IRQ (SW1)
    P4IFG &= ~BIT1;             // clear flag

    P2IE |= BIT3;               // enable P2.3 IRQ (SW2)
    P2IFG &= ~BIT3;             // clear flag

    UCA0IE |= UCRXIE;           // enable SPI Rx IRQ
    UCA0IFG &= ~UCRXIFG;        // clear flag

    __enable_interrupt();       // enable maskable IRQs

    while(1){}                  // do nothing

	return 0;
}


//-------------------------------------------
//---ISR

#pragma vector = PORT4_VECTOR   // ISR for S1
__interrupt void ISR_Port4_S1(void)
{
    UCA0TXBUF = 0x10;           // Tx 0x10 out over SPI
    P4IFG &= ~BIT1;             // clear flag
}

#pragma vector = PORT2_VECTOR   // ISR for S2
__interrupt void ISR_Port2_S3(void)
{
    UCA0TXBUF = 0x66;           // Tx 0x66 out over SPI
    P2IFG &= ~BIT3;             // clear flag
}

#pragma vector = EUSCI_A0_VECTOR    // DATA is in A0 SPI buffer!
__interrupt void ISR_EUSCI_A0(void)
{
    Rx_Data = UCA0RXBUF;            // read RX buffer
    if (Rx_Data == 0x10)
    {
        P1OUT ^= BIT0;              // toggle Led1
    }
    else if (Rx_Data == 0x66)
    {
        P6OUT ^= BIT6;              // toggle Led2
    }
}
