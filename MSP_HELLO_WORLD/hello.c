#include <stdio.h>
#include <msp430.h>


/**
 * hello.c
 */
void printString(char* str);


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	// Declare a string
    char message[] = "Hello, world!";

    // Pass the string to the function
    printString(message);

    return 0;
}

// Function definition
void printString(char* str)
{
    // Print the string
    printf("%s\n", str);
}
