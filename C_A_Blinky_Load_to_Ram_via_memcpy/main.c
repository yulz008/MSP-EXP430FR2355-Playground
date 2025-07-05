#include <msp430.h>
#include <stdint.h>
#include <string.h>

#define FUNC_SIZE 64  // Adjust size based on function size in bytes

// Function to copy to RAM
void __attribute__((noinline)) toggle_led_template(void) {
    P1OUT ^= BIT0;
    volatile int i;
    for (i = 0; i < 8000; i++) {
        // delay
    }
}

uint8_t ram_function_buffer[FUNC_SIZE]; // RAM buffer

typedef void (*func_ptr_t)(void);

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    //--Setup Ports
    P1DIR |= BIT0;        // Set P1.0 to an output
    P1OUT &= ~BIT0;       // clear LED1

    P4DIR &= ~BIT1;      // Set P4.1 to input (SW1)
    P4REN |= BIT1;       // Enables Resistor
    P4OUT |= BIT1;       // Sets Resistor to PullUp

    PM5CTL0 &= ~LOCKLPM5;    // turn on Digital IO

    // Copy the function to RAM
    memcpy(ram_function_buffer, (const void *)toggle_led_template, FUNC_SIZE);

    // Cast the RAM buffer to function pointer
    func_ptr_t toggle_led_ram = (func_ptr_t)(ram_function_buffer);

    while (1) {
        toggle_led_ram();  // Call the function from RAM
    }

    return 0;
}
