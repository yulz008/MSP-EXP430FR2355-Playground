#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	int e = 0b1111111111110000;
	int f = 0x0001;


	while(1)
	{   // ~BIT0- 0000000000000001 -> 1111111111111110 this is the correct mask in the clear operation

	    e = ~e;                 // invert all bits in e    0000000000001111
	    e = e | BIT7;           // set bits 7 in e         0000000010001111
	    e = e & ~BIT0;          // clear bit0 in e         0000000010001110
	    e = e ^ BIT4;            // Toggle Bit4            0000000010011110

	    e |= BIT6;              // set bit6                0000000011011110
	    e &= ~BIT1;              // clear bit1              0000000011011100
	    e ^= BIT3;              // toggle bit3             0000000011010100

	    f = f << 1;
	    f = f << 2;
	    f = f >> 1;

	}
	return 0;
}
