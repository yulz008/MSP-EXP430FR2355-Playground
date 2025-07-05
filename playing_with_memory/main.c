#include <msp430.h>
#include <stdlib.h>

#define TOTAL_RAM 4096      // Approximate total RAM size (4 KB)
#define SAFE_USAGE 3686     // Use ~90% of RAM (~3.6 KB)

// Allocate around 75% of RAM for global/static variables
#define GLOBAL_SIZE 2048    // 2 KB for global
#define STATIC_SIZE 1024    // 1 KB for static
#define STACK_SIZE 10000      // 400 bytes for stack usage
#define HEAP_SIZE 214       // Remaining ~214 bytes for heap (malloc)

//Large global variable (Stored in RAM)
unsigned char ram_bloat_global[GLOBAL_SIZE]; // ~2 KB in RAM

// Large static variable (Stored in RAM)
static unsigned char ram_bloat_static[STATIC_SIZE]; // ~1 KB in RAM

void stack_bloat_function(int size) {
    //Controlled stack allocation (~400 bytes)
    volatile unsigned char stack_bloat[STACK_SIZE];
    int i = 0;
    for (i = 0; i < STACK_SIZE; i++) {
        stack_bloat[i] = i; // Simulate stack usage
        printf(stack_bloat[i]);
    }
}

void main(void) {
    WDTCTL = WDTPW | WDTHOLD;  // Stop watchdog timer

    //Heap Memory Allocation (~214 bytes)
    unsigned char *heap_bloat = (unsigned char*) malloc(HEAP_SIZE);
    if (heap_bloat) {
        int i = 0;
        for (i = 0; i < HEAP_SIZE; i++) {
            heap_bloat[i] = i; // Simulate heap usage
        }
    }

    // Call function to bloat stack
    stack_bloat_function(STACK_SIZE);

    while (1);
}
