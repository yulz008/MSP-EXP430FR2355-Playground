#include <msp430.h> 
/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	int i=0;
	int count=0;

	while(1)
	{
	  for(i=0; i<10 ; i++)
	  {
	    count = i;
	   }
	}

	// Since we are on the MCU we dont want to return to 0 \
	// cause we don't have an OS, Else we will crash
	return 0;
}
