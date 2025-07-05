#include <msp430.h> 


/**
 * main.c
 */
// int count[1680] = {0};

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	 int count = 0
	// static int count[1680] = {0};

	while(1)                    // do infinite loop
	{
	    count[1] = count[0] + 1;
	}

	return 0;
}
