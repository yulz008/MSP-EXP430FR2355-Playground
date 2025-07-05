#include <msp430.h> 


void toggle_led(void);

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //--Setup Ports
    P1DIR |= BIT0;        // Set P1.0 to an output
    P1OUT &= ~BIT0;       // clear LED1

    P4DIR &= ~BIT1;      // Set P4.1 to input (SW1)
    P4REN |= BIT1;       // Enables Resistor
    P4OUT |= BIT1;       // Sets Resistor to PullUp

    PM5CTL0 &= ~LOCKLPM5;    // turn on Digital IO

    while(1)
    {
        toggle_led();
    }

    return 0;
}

void toggle_led(void)
{
     P1OUT ^= BIT0;
     int i = 0;
     // delay
     for (i=0; i<8000; i++)
     {
         //do nothing
     }
}
